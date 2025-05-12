#include <esp_now.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "qeue.h"
#include <math.h>

const char* ssid = "AndroidAP_9266";
const char* password = "22833788270";
const String serverName = "http://192.168.5.231";

// Structure example to receive data
// Must match the sender structure
// typedef struct struct_xyz {
//   int id;
//   float x;
//   float y;
//   float z;
// }struct_xyz;

typedef struct struct_heart {
  int id;
  float heartRate;
  int IR;
}struct_heart;

typedef struct struct_door {
    int id; // must be unique for each sender board
    String doorStatus;
} struct_door;

// Create a struct_message called myData
struct_xyz xyzData;
struct_heart heartData;
struct_door doorData;
static uint32_t heartTime = 0;
static uint32_t doorTime = 0;

void httpPost(String data, String path) {
  if(WiFi.status()== WL_CONNECTED){
      WiFiClient client;
      HTTPClient http;
    
      String serverPath = serverName + path;
      http.begin(client, serverPath.c_str());
      
      // Specify content-type header
      http.addHeader("Content-Type", "application/json");
              
      // Send HTTP POST request
      int httpResponseCode = http.POST(data);
      
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
        
      // Free resources
      http.end();
    }
}

// callback function that will be executed when data is received
void OnDataRecv(const uint8_t * mac_addr, const uint8_t *incomingData, int len) {
  char macStr[18];
  Serial.print("Packet received from: ");
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  Serial.println(macStr);
  Serial.printf("Board ID %u: %u bytes\n", incomingData[0], len);
  if (incomingData[0]==1) {
    memcpy(&xyzData, incomingData, sizeof(xyzData));
    Serial.printf("x value: %f \n", xyzData.x);
    Serial.printf("y value: %f \n", xyzData.y);
    Serial.printf("z value: %f \n", xyzData.z);
    Serial.println();
    enQueue(xyzData);
    struct_xyz last = deQueue();
    if((fabs(xyzData.x - last.x) + fabs(xyzData.y - last.y) + fabs(xyzData.z - last.z)) / 3 > 15) {
      xyzWarning();
    }
    httpPost("{\"id\":1, \"X\":$xyzData.x, \"Y\":$xyzData.y, \"Z\":$xyzData.z}", "/xyz");
  }
  if (incomingData[0]==2) {
    memcpy(&heartData, incomingData, sizeof(heartData));
    if (!(heartData.heartRate > 80 || heartData.heartRate < 60)) {
      heartTime = millis();
    }
    Serial.printf("heart rate value: %f \n", heartData.heartRate);
    httpPost("{\"id\":2, \"HeartBeat\":$heartData.heartRate}", "/heart");
  }
  if (incomingData[0]==3) {
    memcpy(&doorData, incomingData, sizeof(doorData));
    Serial.printf("door status: %s \n", doorData.doorStatus);
    doorTime = millis();
    httpPost("{\"id\":3, \"Door\":$doorData.doorStatus}", "/door");
  }

}

void heartWarning(){
  Serial.println("HEART WARNING");
}
void doorWarning(){
  Serial.println("DOOR WARNING");
}
void xyzWarning(){
  Serial.println("XYZ WARNING");
}
 
void setup() {
  //Initialize Serial Monitor
  Serial.begin(115200);
  
  //Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  //Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // Once ESPNow is successfully Init, we will register for recv CB to get recv packer info
  esp_now_register_recv_cb(esp_now_recv_cb_t(OnDataRecv));
}
 
void loop() {
  
  static uint32_t ms;
  ms = millis();
  if (ms - heartTime > 5000) {
    heartWarning();
  }
  if (ms - doorTime > 10000) {
    doorWarning();
  }
 
}
#include <WiFi.h>
#include <esp_now.h>

uint8_t hostAddress[] = {0x30, 0xC9, 0x22, 0x31, 0xF0, 0xAC};

const int LED = 0;
const int Mag = 16;
int value;
int status_now = 0;
int status_past = 0;
const int analogInPin = A0;
int i = 0;

typedef struct struct_message {
    int id; // must be unique for each sender board
    String doorStatus;
} struct_message;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
    if (status == ESP_NOW_SEND_SUCCESS) {
        Serial.println("Delivery Success");
        }
    else {
        Serial.println("Delivery Fail");
    }
    
  }

void setup() {
  Serial.begin(115200);

  pinMode(LED, OUTPUT);
  pinMode(Mag, INPUT);
   
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  memcpy(peerInfo.peer_addr, hostAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }

  }

void loop() {


status_now = digitalRead(Mag);
  
    if((status_now == 1) && (status_past == 1))
    {
        myData.id = 3;
  	myData.doorStatus = "OPEN";
  	esp_err_t result = esp_now_send(hostAddress, (uint8_t *) &myData, sizeof(myData));
   
  	if (result == ESP_OK) {
    		Serial.println("Sent success");
  	}
 	else {
    		Serial.println("Error sending the data");
  	}
      digitalWrite(LED, LOW);
      status_past = 0;
    }

    if((status_now == 0) && (status_past == 0)) 
    {
      	myData.id = 3;
  	myData.doorStatus = "CLOSE";
  	esp_err_t result = esp_now_send(hostAddress, (uint8_t *) &myData, sizeof(myData));
   
  	if (result == ESP_OK) {
    		Serial.println("Sent success");
  	}
 	else {
    		Serial.println("Error sending the data");
  	}
      digitalWrite(LED, HIGH);
      status_past = 1;  
    }
  

}
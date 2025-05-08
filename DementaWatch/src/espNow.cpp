#include <hal.h>

uint8_t hostAddress[] = {0x30, 0xC9, 0x22, 0x31, 0xF0, 0xAC};

// Structure example to send data
// Must match the receiver structure
typedef struct struct_message {
    int id; // must be unique for each sender board
    float x;
    float y;
    float z;
} struct_message;

// Create a struct_message called myData
struct_message myData;

// Create peer interface
esp_now_peer_info_t peerInfo;

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
    if (status == ESP_NOW_SEND_SUCCESS) {
        //Serial.println("Delivery Success");
        PowerController::connectionIsOk(millis());
    }
    else {
        //Serial.println("Delivery Fail");
    }
    
  }

void MyWatch::espNowInit() {

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

void MyWatch::espNowUpdate(uint32_t millis, uint32_t time_ms, float x, float y, float z) {
    static uint32_t Millis;

    if (millis - Millis > time_ms)
    {
        MyWatch::espNowSend(x, y, z);
        Millis = millis;
    }
}

void MyWatch::espNowSend(float x, float y, float z) {
  // Set values to send
  myData.id = 1;
  myData.x = x;
  myData.y = y;
  myData.z = z;

  // Send message via ESP-NOW
  esp_err_t result = esp_now_send(hostAddress, (uint8_t *) &myData, sizeof(myData));
   
  if (result == ESP_OK) {
    //Serial.println("Sent success");
  }
  else {
    Serial.println("Error sending the data");
  }
}

    
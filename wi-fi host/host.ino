#include <WiFi.h>
#include <WebServer.h>
#include <ArduinoJson.h>

//const char* ssid = "DIR-228";
//const char* password = "admin2003";
const char* ssid = "AndroidAP_9266";
const char* password = "22833788270";
IPAddress ip(192, 168, 5, 231);
IPAddress dns(192, 168, 5, 1);
IPAddress gateway(192, 168, 5, 1);
IPAddress subnet(255, 255, 255, 0);
WebServer server(80);
StaticJsonDocument<250> jsonDocument;
char buffer[250];

void setup_routing() {     
  server.on("/items", getItems);          
  server.on("/led", HTTP_POST, handlePost);    
  server.begin();    
}

void create_json(char *tag, char *value, char *unit) {  
  jsonDocument.clear();  
  jsonDocument["type"] = tag;
  jsonDocument["value"] = value;
  jsonDocument["unit"] = unit;
  serializeJson(jsonDocument, buffer);
}
 
void add_json_object(char *tag, char *value, char *unit) {
  JsonObject obj = jsonDocument.createNestedObject();
  obj["type"] = tag;
  obj["value"] = value;
  obj["unit"] = unit; 
}

void getItems() {
  Serial.println("Get items");
  create_json("items", "{\"name\":\"Cat\", \"age\":10}", "pp");
  server.send(200, "application/json", buffer);
}

void handlePost() {
  if (server.hasArg("plain") == false) {
  }
  String body = server.arg("plain");
  deserializeJson(jsonDocument, body);

  int red_value = jsonDocument["red"];

  Serial.println(red_value);

  server.send(200, "application/json", "{}");
}


void setup(){

    Serial.begin(115200);
    delay(1000);

    WiFi.mode(WIFI_STA); //Optional
    WiFi.config(ip, gateway, subnet, dns);
    WiFi.begin(ssid, password);
    Serial.println("\nConnecting");

    while(WiFi.status() != WL_CONNECTED){
        Serial.print(".");
        delay(100);
    }

    Serial.println("\nConnected to the WiFi network");
    Serial.print("Local ESP32 IP: ");
    Serial.println(WiFi.localIP());
    delay(1000);   
    setup_routing();
}

void loop(){
  server.handleClient(); 
}


// const int LED = 2;

// void setup() {
//   pinMode(LED, OUTPUT);
//   Serial.begin(115200);
// }
// 
// void loop() {
//   Serial.println("Hello");
//   delay(1000);
//   digitalWrite(LED, HIGH);
//   delay(1000);
//   digitalWrite(LED, LOW);
// }
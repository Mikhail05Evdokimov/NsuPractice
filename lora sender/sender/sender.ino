#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>  
 
#define DHTPIN 23
 
#define SCK     5    // GPIO5  -- SX1278's SCK
#define MISO    19   // GPIO19 -- SX1278's MISO
#define MOSI    27   // GPIO27 -- SX1278's MOSI
#define SS      18   // GPIO18 -- SX1278's CS
#define RST     14   // GPIO14 -- SX1278's RESET
#define DI0     26   // GPIO26 -- SX1278's IRQ(Interrupt Request)
#define BAND    915E6
 
unsigned int counter = 0;
 
String LoRaMessage = "";
 
void setup() {
 
  pinMode(2,OUTPUT);
   
  Serial.begin(115200);
  while (!Serial);
  Serial.println("LoRa Sender Test");
   
  SPI.begin(SCK,MISO,MOSI,SS);
  LoRa.setPins(SS,RST,DI0);
  while (!LoRa.begin(433E6))     //433E6 - Asia, 866E6 - Europe, 915E6 - North America
  {
    Serial.println(".");
    delay(500);
  
  }

  Serial.println("init ok");
   
  delay(1500);
}
 
void loop() {
  Serial.print("Sending packet: ");
  float h = 5.5; 
  float t = 5.5;
  LoRaMessage = "41F 440 438 432 435 442 0A";
  // send packet
  LoRa.beginPacket();
  LoRa.print(LoRaMessage);
  LoRa.endPacket();
 
  counter++;
  digitalWrite(2, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(2, LOW);    // turn the LED off by making the voltage LOW
  delay(2000);                       // wait for a second
}
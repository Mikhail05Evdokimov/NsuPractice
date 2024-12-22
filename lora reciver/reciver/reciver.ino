#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>  


#define SCK     5    // GPIO5  -- SX1278's SCK
#define MISO    19   // GPIO19 -- SX1278's MISO
#define MOSI    27   // GPIO27 -- SX1278's MOSI
#define SS      18   // GPIO18 -- SX1278's CS
#define RST     14   // GPIO14 -- SX1278's RESET
#define DI0     26   // GPIO26 -- SX1278's IRQ(Interrupt Request)
#define BAND    915E6
String data1;
String data2;

void setup() {
  
  
  Serial.begin(115200);
  while (!Serial);
  Serial.println("LoRa Receiver Callback");
  SPI.begin(SCK,MISO,MOSI,SS);
  LoRa.setPins(SS,RST,DI0);  
  while (!LoRa.begin(433E6))     //433E6 - Asia, 866E6 - Europe, 915E6 - North America
  {
    Serial.println(".");
    delay(500);
  }
  //LoRa.onReceive(cbk);
  LoRa.receive();
  Serial.println("init ok");
  
  delay(1500);
}

void loop() {
 
  
  int packetSize = LoRa.parsePacket();
  if (packetSize) { Serial.print("Received packet '");
 
    while (LoRa.available())              // read packet
    {
      String LoRaData = LoRa.readString();
      Serial.print(LoRaData);
      int pos1 = LoRaData.indexOf('1');
      int pos2 = LoRaData.indexOf('2');
      data1 = LoRaData;//.substring(pos1+1, pos2); 
      Serial.println(data1);
      //data2 = LoRaData.substring(pos2+1, LoRaData.length()); 
      if (data1 == "111") {
        digitalWrite(2, HIGH);
      }
    }
    Serial.print("' with RSSI ");         // print RSSI of packet
    Serial.println(LoRa.packetRssi());
    Serial.println(data1); 
    //Serial.println(data2); 
  }

}

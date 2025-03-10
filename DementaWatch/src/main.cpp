#include <Arduino.h>
#include <config.h>
#include <hal.h>

void setup() {
  // put your setup code here, to run once:
  MyWatch::HAL_Init();
  
  Serial.begin(115200); 
  //Serial.println("Hello T-Watch");
  
}

void loop() {
  MyWatch::HAL_Update();
  //Serial.println("Hello T-Watch");
  //digitalWrite(Motor, HIGH);
}

#include <Arduino.h>
#include <config.h>
#include <hal.h>

void setup() {

  Serial.begin(9600);
  MyWatch::HAL_Init();
  //Serial.println("Hello T-Watch");
  
}

void loop() {

  MyWatch::HAL_Update();
  
}
  
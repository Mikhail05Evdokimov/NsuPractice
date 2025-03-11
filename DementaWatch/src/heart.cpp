#include <hal.h>
#include "MAX30105.h"
#include "heartRate.h"


MAX30105 particleSensor;

static uint32_t cntH = 1;
static float measurementTime = 0;
static uint32_t lastBeat = 0;

void MyWatch::heartInit() {
  //Serial.begin(9600);//(115200);
  //Serial.println("Initializing...");

  // Initialize sensor
  if (particleSensor.begin() == false) {
    Serial.println("MAX30102 was not found. Please check wiring/power. ");
    while (1);
  }
  Serial.println("Place your index finger on the sensor with steady pressure.");

  particleSensor.setup(); //Configure sensor with default settings
  particleSensor.setPulseAmplitudeRed(0x0A); //Turn Red LED to low to indicate sensor is running
  
}

void MyWatch::heartLoop(uint32_t millis, uint32_t time_ms) {
  long irValue = particleSensor.getIR();

  if (irValue < 50000) {
    if (millis - lastBeat > 1000) {
      Serial.println("No finger?");
      lastBeat = millis;
      cntH = 1;
    }
  }
  else {
    if (checkForBeat(irValue)) {
      measurementTime = (millis - lastBeat) / 1000;
      cntH++; 
      Serial.println(cntH*60/measurementTime);
    }
  }
}
/*
  Serial.print("IR=");
  Serial.print(irValue);
  Serial.print(", BPM=");
  Serial.print(beatsPerMinute);
  Serial.print(", Avg BPM=");
  Serial.print(beatAvg);
}*/
    
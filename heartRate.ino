#include <Wire.h>
#include "MAX30105.h"
#include "heartRate.h"

MAX30105 particleSensor;

static uint32_t timer = 0;
static uint32_t cntH = 1;
static float measurementTime = 0;
static uint32_t contactTime = 0;
static float BPM = 0;

void setup() {
  Serial.begin(9600);

  // Initialize sensor
  if (particleSensor.begin() == false) {
    Serial.println("MAX30102 was not found. Please check wiring/power. ");
    while (1);
  }
  Serial.println("Place your index finger on the sensor with steady pressure.");

  particleSensor.setup(); //Configure sensor with default settings
  particleSensor.setPulseAmplitudeRed(0x0A); //Turn Red LED to low to indicate sensor is running
  
}

void loop() {
  long irValue = particleSensor.getIR();
  uint32_t millis_ = millis();
  if (irValue < 50000) {
    if (millis_ - contactTime > 1000) {
      Serial.println("No finger?");
      contactTime = millis_;
      cntH = 1;
    }
  }
  else {
    if (checkForBeat(irValue)) {
      measurementTime = (millis_ - contactTime) / 1000;
      cntH++;
      BPM = cntH*60/measurementTime;
    }
    if (millis_ - timer > 1000) {
      Serial.print("BPM: ");
      Serial.println(BPM);
      timer = millis_;
    }
  }
}
  
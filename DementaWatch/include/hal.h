#include <config.h>
#include <stdio.h>

#include <HardwareSerial.h>
#include <Wire.h>
#include <SPI.h>
#include "bma423.h"
#include "MAX30105.h"
#include "heartRate.h"
#include <esp_now.h>
#include <WiFi.h>

namespace MyWatch
{
    void HAL_Init();
    void HAL_Update();
    void HAL_Sleep();

    void Power_Init();
    void Power_Updata(uint32_t millis, uint32_t time_ms);
    
    void Motor_Init();
    void Motor_Shake(const uint32_t cnt, const uint32_t interval);
    void Motor_Loop(uint32_t millis);
    void Motor_Stop();


    /* Acceleration Sensor : bma423 */
    bool CheckAccSensor();
    void AccSensor_Init();
    void AccSensor_Interface_Init();
    void AccSensor_OnStep(bool Step, bool Reset);
    void AccSensor_Sleep(bool Acc, bool Step);
    void AccSensor_GetStepValue(int32_t *val);
    void AccSensor_Updata(uint32_t millis, uint32_t time_ms);
    float AccSensor_GetX();
    float AccSensor_GetY();
    float AccSensor_GetZ();
    uint32_t AccSensor_GetStep();

    void heartInit();
    void heartLoop(uint32_t millis, uint32_t time_ms);
    float getPulse();

    void espNowInit();
    void espNowSend(float x, float y, float z);
    void espNowUpdate(uint32_t millis, uint32_t time_ms, float x, float y, float z);

}

namespace PowerController
{
    void update(uint32_t millis, uint32_t time_ms);
    void connectionIsOk(uint32_t millis);
    void onArm(uint32_t millis);
} 

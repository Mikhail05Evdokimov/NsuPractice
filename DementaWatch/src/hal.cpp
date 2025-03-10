#include <hal.h>

void MyWatch::HAL_Init(void)
{
    Power_Init();
    Motor_Init();
    Motor_Shake(2, 50);

    AccSensor_Interface_Init();
    esp_sleep_wakeup_cause_t wakeup_reason = esp_sleep_get_wakeup_cause();
    Serial.printf("wakeup_reason:%d\r\n", wakeup_reason);
    if (wakeup_reason == 0) //Sleep wake up without initialization
    {
        AccSensor_Init();
    }

    heartInit();
}

void Debugloop(uint32_t millis, uint32_t time_ms)
{
    static uint32_t Millis;
    if (millis - Millis > time_ms)
    {
        log_d("Total heap: %d", ESP.getHeapSize());
        log_d("Free heap: %d", ESP.getFreeHeap());
        log_d("Total PSRAM: %d", ESP.getPsramSize());
        log_d("Free PSRAM: %d", ESP.getFreePsram());
        Millis = millis;
    }
}

void MyWatch::HAL_Update(void)
{
    static uint32_t ms;
    ms = millis();
    Motor_Loop(ms);
    AccSensor_Updata(ms, 100);
    heartLoop(ms, 200);
    
}

void MyWatch::HAL_Sleep()
{
    uint64_t mask;
    mask = 1ull << 32;
    pinMode(PWR_ON, OUTPUT);
    digitalWrite(PWR_ON, LOW);

    esp_sleep_enable_ext1_wakeup(mask, ESP_EXT1_WAKEUP_ALL_LOW); //Screen int
    esp_sleep_enable_ext0_wakeup(GPIO_NUM_0 /* BTN_0 */, LOW);
    esp_deep_sleep_start();
}

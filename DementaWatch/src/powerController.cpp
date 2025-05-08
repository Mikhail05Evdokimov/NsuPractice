#include <hal.h>
static uint32_t connectionTimeout;
static uint32_t armTimeout;
static bool sleepStatus = false;

void modemSleep() {
    Serial.println("Modem sleep");
    sleepStatus = true;
    WiFi.setSleep(true);
    setCpuFrequencyMhz(40);
}

void modemWakeUp() {
    Serial.println("Modem wake up");
    sleepStatus = false;
    WiFi.setSleep(false);
    setCpuFrequencyMhz(240);
}

void lightSleep() {
    Serial.println("Light sleep");
    esp_sleep_enable_timer_wakeup(5 * 1000 * 1000);
    esp_light_sleep_start();
}

void PowerController::update(uint32_t millis, uint32_t time_ms) {
    bool timeout = (millis - connectionTimeout > time_ms);
    if (timeout && !sleepStatus)
    {
        connectionTimeout = millis;
        modemSleep();
    }
    if (timeout && sleepStatus) {
        connectionTimeout = millis;
        modemWakeUp();
    }
    #ifdef HasHeartRate
    if (millis - armTimeout > time_ms)
    {
        armTimeout = millis;
        lightSleep();
    }
    #endif
    
}

void PowerController::connectionIsOk(uint32_t millis) {
    connectionTimeout = millis;
}

void PowerController::onArm(uint32_t millis) {
    armTimeout = millis;
}

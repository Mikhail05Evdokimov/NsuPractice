#include <hal.h>

static uint8_t Pow_percent;
void MyWatch::Power_Init()
{
    pinMode(PWR_ON, OUTPUT);
    digitalWrite(PWR_ON, HIGH);
    pinMode(BAT_ADC, INPUT);
}

void MyWatch::Power_Updata(uint32_t millis, uint32_t time_ms)
{
    static uint32_t Millis;
    static uint32_t power_sub;
    static uint8_t cnt;
    if (millis - Millis > time_ms)
    {
        if (cnt < 25)
        {
            power_sub += analogRead(BAT_ADC);
            cnt++;
        }
        else
        {
            uint32_t Pow = power_sub / cnt;
            float Volts = (Pow * 3.3 * 2 / 4096);
            Pow_percent = ((constrain(Volts, 3.7, 4.2) - 3.7) / 0.5) * 100;
            power_sub = cnt = 0;
            Serial.printf("Volts:%d\r\n", Pow);
        }

        Millis = millis;
    }
}


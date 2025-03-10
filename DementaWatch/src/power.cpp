#include <hal.h>

static uint8_t Pow_percent;
void MyWatch::Power_Init()
{
    pinMode(PWR_ON, OUTPUT);
    digitalWrite(PWR_ON, HIGH);
}

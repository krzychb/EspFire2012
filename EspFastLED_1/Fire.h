#ifndef _FIRE_H_
#define _FIRE_H_

#define FASTLED_ESP8266_RAW_PIN_ORDER
// ref. https://github.com/FastLED/FastLED/issues/306
// #define FASTLED_ALLOW_INTERRUPTS 0
#define FASTLED_INTERRUPT_RETRY_COUNT 3
#include <FastLED.h>

extern byte cooling;
extern byte sparking;
extern byte brightness;

void setupFire(void);
void keepFireAlive(void);

#endif //_FIRE_H_

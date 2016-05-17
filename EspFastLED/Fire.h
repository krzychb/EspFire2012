#ifndef _FIRE_H_
#define _FIRE_H_

#define FASTLED_ESP8266_RAW_PIN_ORDER
#include <FastLED.h>

extern byte cooling;
extern byte sparking;
extern byte brightness;

void setupFire(void);
void keepFireAlive(void);

#endif //_FIRE_H_

#ifndef _FIRE_H_
#define _FIRE_H_

#include <Adafruit_NeoPixel.h>
#include <FastLED.h>

extern byte cooling;
extern byte sparking;
extern byte brightness;

void setupFire(void);
void keepFireAlive(void);

#endif //_FIRE_H_

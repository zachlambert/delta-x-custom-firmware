#ifndef CONFIG_H
#define CONFIG_H

#include "pin.h"

extern PinImpl _led, _led2, _led3;
static Pin led = &_led;
static Pin led2 = &_led2;
static Pin led3 = &_led3;

#endif

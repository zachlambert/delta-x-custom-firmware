#ifndef STEPPER_H
#define STEPPER_H

#include <stdint.h>
#include <stdbool.h>
#include "pin.h"

typedef struct {
    Pin pin_pulse;
    Pin pin_dir;
    Pin pin_en;
    Pin pin_endstop;
    bool enabled;
    int target;
    int pos;
    int dir;
    bool zeroed;
} Stepper;

#endif

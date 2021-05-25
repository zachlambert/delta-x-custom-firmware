#ifndef STEPPER_H
#define STEPPER_H

#include <stdint.h>
#include "pin.h"

typedef struct {
    Pin pin_pulse;
    Pin pin_dir;
    Pin pin_en;
    Pin pin_endstop;
    uint8_t moving;
    uint8_t pulse_value;
    uint8_t dir;
    uint16_t pulse_half_period;
    int pos_steps;
    double pos;
    double vel;
} Stepper;

#endif

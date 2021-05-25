#include "stepper.h"

#include <avr/io.h>
#include <avr/interrupt.h>

#include "pin.h"

Stepper *stepper_1;
ISR(TIMER1_COMPA_vect)
{
    if (stepper_1->dir) {
        stepper_1->pos_steps++;
    } else {
        stepper_1->pos_steps--;
    }
    stepper_1->pulse_value = !stepper_1->pulse_value;
    pin_write(stepper_1->pin_pulse);
    OCR1A = stepper_1->pulse_half_period;
}

void stepper_attach_timer_1(Stepper *stepper)
{
    stepper_1 = stepper;
}

void stepper_set_velocity(Stepper *stepper)
{
    if (!stepper->moving) {

    }
}


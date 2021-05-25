#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdbool.h>

#include "robot.h"
#include "uart.h"
#include "pin.h"

Robot *g_robot;

uint8_t on = 0;
ISR(TIMER1_COMPA_vect)
{
    g_robot->counter++;
    on = !on;
    for (int i = 0; i < 3; i++) {
        Stepper *stepper = &g_robot->steppers[i];
        if (stepper->enabled) {
            pin_write(stepper->pin_pulse, on);
            stepper->pos += stepper->dir;
            if (!stepper->zeroed) continue;
            if (stepper->pos == stepper->target ||
                (stepper->pos > stepper->target && stepper->dir>0) ||
                (stepper->pos < stepper->target && stepper->dir<0))
            {
                stepper->enabled = false;
            }
        }
    }
}

void robot_init(Robot *robot)
{
    g_robot = robot;

    robot->counter = 0;

    // 54, 55, 38, 3
    robot->steppers[0].pin_pulse.port = PORT_F;
    robot->steppers[0].pin_pulse.n = 0;
    robot->steppers[0].pin_dir.port = PORT_F;
    robot->steppers[0].pin_dir.n =1;
    robot->steppers[0].pin_en.port = PORT_D;
    robot->steppers[0].pin_en.n = 7;
    robot->steppers[0].pin_endstop.port = PORT_E;
    robot->steppers[0].pin_endstop.n = 5;

    // 60, 61, 56, 14
    robot->steppers[1].pin_pulse.port = PORT_F;
    robot->steppers[1].pin_pulse.n = 6;
    robot->steppers[1].pin_dir.port = PORT_F;
    robot->steppers[1].pin_dir.n = 7;
    robot->steppers[1].pin_en.port = PORT_F;
    robot->steppers[1].pin_en.n = 2;
    robot->steppers[1].pin_endstop.port = PORT_J;
    robot->steppers[1].pin_endstop.n = 1;

    // 46, 48, 62, 18
    robot->steppers[2].pin_pulse.port = PORT_L;
    robot->steppers[2].pin_pulse.n = 3;
    robot->steppers[2].pin_dir.port = PORT_L;
    robot->steppers[2].pin_dir.n = 1;
    robot->steppers[2].pin_en.port = PORT_K;
    robot->steppers[2].pin_en.n = 0;
    robot->steppers[2].pin_endstop.port = PORT_D;
    robot->steppers[2].pin_endstop.n = 3;

    for (int i = 0; i < 3; i++) {
        pin_init_input_pullup(robot->steppers[i].pin_endstop);
        pin_init_output(robot->steppers[i].pin_pulse);
        pin_init_output(robot->steppers[i].pin_dir);
        pin_init_output(robot->steppers[i].pin_en);
    }

    // Configure timer 1 for CTC mode

    // Set to CTC mode
    reg_write_mask(&TCCR1A, WGM10, 0b11, 0b00);
    reg_write_mask(&TCCR1B, WGM12, 0b11, 0b01);

    // Clock select. Use no prescaling.
    reg_write_mask(&TCCR1B, CS10, 0b111, 1);

    // Set timer end (OCRnA)
    OCR1A = 3200;

    // Enable interrupts
    sei();
    reg_set(&TIMSK1, OCIE1A);


    for (int i = 0; i < 3; i++) {
        pin_write(robot->steppers[i].pin_en, 0);
        pin_write(robot->steppers[i].pin_dir, 0);
        robot->steppers[i].dir = -1;
        robot->steppers[i].enabled = true;
        robot->steppers[i].zeroed = false;
    }

    bool zeroed;
    while (true) {
        zeroed = true;
        for (int i = 0; i < 3; i++) {
            int endstop = pin_read(robot->steppers[i].pin_endstop);
            if (endstop == 1) { // Not pressed
                zeroed = false;
            } else {
                robot->steppers[i].enabled = false;
                robot->steppers[i].zeroed = true;
            }
        }
        if (zeroed) break;
    }

    for (int i = 0; i < 3; i++) {
        robot->steppers[i].pos = 0;
        robot->steppers[i].target = 1000;
        robot->steppers[i].dir = 1;
        pin_write(robot->steppers[i].pin_dir, 1);
        robot->steppers[i].enabled = true;
    }
}

void robot_loop(Robot *robot)
{
}

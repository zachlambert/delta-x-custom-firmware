#include <util/delay.h>
#include <avr/interrupt.h>

#include "robot.h"
#include "config.h"
#include "uart.h"

Robot *g_robot;

void robot_init(Robot *robot)
{
    g_robot = robot;
    pin_init_input_pullup(theta_1_endstop);
    pin_init_output(theta_1_pulse);
    pin_init_output(theta_1_dir);
    pin_init_output(theta_1_en);

    robot->endstop = 0;
    robot->counter = 0;

    pin_write(theta_1_en, 0);
    pin_write(theta_1_dir, 0);

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
}

uint8_t dir = 0;
uint8_t on = 0;
ISR(TIMER1_COMPA_vect)
{
    g_robot->counter++;
    on = !on;
    pin_write(theta_1_pulse, on);
    if (g_robot->counter == 1500) {
        g_robot->counter = 0;
        dir = !dir;
        pin_write(theta_1_dir, dir);
    }
}

void robot_loop(Robot *robot)
{
    robot->endstop = pin_read(theta_1_endstop);
    printf("Endstop: %d [%d]\n", robot->endstop, robot->counter);
}

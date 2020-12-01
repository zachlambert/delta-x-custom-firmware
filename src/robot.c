#include <util/delay.h>

#include "robot.h"
#include "config.h"
#include "uart.h"

void robot_init(Robot *robot)
{
    pin_init_input_pullup(theta_1_endstop);
    robot->endstop = 0;
}

void robot_loop(Robot *robot)
{
    robot->endstop = pin_read(theta_1_endstop);
    printf("Endstop: %d\n", robot->endstop);
    _delay_ms(100);
}

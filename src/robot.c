#include <util/delay.h>

#include "robot.h"
#include "config.h"

void robot_init(Robot *robot)
{
    init_output(led);
    init_output(led2);
    init_output(led3);

    robot->counter = 0;
}

void robot_loop(Robot *robot)
{
    robot -> counter++;
    if (robot->counter > 4) {
        robot->counter = 0;
        set(led);
        set(led2);
        set(led3);
    } else {
        clear(led);
        clear(led2);
        clear(led3);
    }
    _delay_ms(100);
}

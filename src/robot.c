#include <util/delay.h>

#include "robot.h"
#include "config.h"

void robot_init(void)
{
    init_output(led);
    init_output(led2);
    init_output(led3);
}

void robot_loop(void)
{
    set(led);
    set(led2);
    set(led3);
    _delay_ms(500);
    clear(led);
    clear(led2);
    clear(led3);
    _delay_ms(500);
}

#include "robot.h"
#include <stdbool.h>
#include <string.h>
#include <util/delay.h>

int main(void)
{

    static Robot robot;
    robot_init(&robot);
    while (1) {
        robot_loop(&robot);
    }
    return 0;
}

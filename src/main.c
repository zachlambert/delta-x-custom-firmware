#include "robot.h"

int main(void)
{
    robot_init();
    while (1) {
        robot_loop();
    }
    return 0;
}

#include "robot.h"

int main(void)
{
    // Can make static to see data usage at compile time.
    // Its going to be put on the stack at the start of the program anyway.
    static Robot robot;
    robot_init(&robot);
    while (1) {
        robot_loop(&robot);
    }
    return 0;
}

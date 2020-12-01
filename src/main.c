#include "robot.h"
#include "uart.h"

int main(void)
{
    UartConfig uart_config = uart_create_config();
    uart_init(&uart_config);

    printf("Starting\n");

    static Robot robot;
    robot_init(&robot);
    while (1) {
        robot_loop(&robot);
    }
    return 0;
}

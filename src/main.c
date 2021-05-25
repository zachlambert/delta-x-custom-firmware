#include "robot.h"
#include "uart.h"

int main(void)
{
    UartConfig uart_config = uart_create_config();
    uart_init(&uart_config);

    uint16_t cmd[5];
    while (1) {
        for (int i = 0; i < 5; i++) {
            cmd[i] = uart_read_uint16();
        }
        for (int i = 0; i < 5; i++) {
            uart_write_uint16(cmd[i]);
        }
    }

    return 0;

    // printf("Starting\n");

    static Robot robot;
    robot_init(&robot);
    while (1) {
        robot_loop(&robot);
    }
    return 0;
}

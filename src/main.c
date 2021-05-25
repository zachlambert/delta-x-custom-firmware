#include "robot.h"
#include "uart.h"
#include <stdbool.h>
#include <string.h>
#include <util/delay.h>

int main(void)
{
    UartConfig uart_config = uart_create_config();
    uart_init(&uart_config);

    _delay_ms(1000);

    uint8_t buffer[10];
    uart_read_bytes(buffer, 10);

    while (1) {
        for (int i = 0; i < 10; i++) {
            printf("0x%x\n", buffer[i]);
        }
    }


    return 0;

    static Robot robot;
    robot_init(&robot);
    while (1) {
        robot_loop(&robot);
    }
    return 0;
}

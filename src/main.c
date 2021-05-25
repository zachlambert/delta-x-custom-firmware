#include "robot.h"
#include "uart.h"
#include <stdbool.h>
#include <string.h>
#include <util/delay.h>

#define BUFFER_N 14
typedef struct {
    uint8_t data[BUFFER_N];
    int head;
    uint16_t special;
    uint16_t special2;
} Buffer;

Buffer buffer_create(void)
{
    Buffer buffer;
    memset(buffer.data, 0, BUFFER_N);
    buffer.head = 0;
    buffer.special = 0xF770;
    buffer.special2 = 0xE661;
    return buffer;
}

void buffer_update(Buffer *buffer)
{
    buffer->data[buffer->head] = uart_read_byte();
    buffer->head = (buffer->head+1)%BUFFER_N;
}

bool buffer_match(Buffer *buffer)
{
    int index = buffer->head;
    int index2 = (buffer->head+1)%BUFFER_N;
    uint16_t start = buffer->data[index2]<<8 | buffer->data[index];
    if (start != buffer->special) return false;
    index = (buffer->head-2)%BUFFER_N;
    index2 = (buffer->head-1)%BUFFER_N;
    uint16_t end = buffer->data[index2]<<8 | buffer->data[index];
    if (end != buffer->special2) return false;
    return true;
}

uint16_t buffer_read_value(Buffer *buffer, int i)
{
    int index = (buffer->head+2 + 2*i)%BUFFER_N;
    int index2 = (index+1)%BUFFER_N;
    return buffer->data[index2]<<8 | buffer->data[index];
}

int main(void)
{
    UartConfig uart_config = uart_create_config();
    uart_init(&uart_config);

    // Buffer buffer = buffer_create();

    // _delay_ms(1000);
    // for (int j = 0; j< 20; j++) {
    //     buffer_update(&buffer);
    //     if (buffer_match(&buffer)) break;
    // }

    static Robot robot;
    robot_init(&robot);
    while (1) {
        robot_loop(&robot);
    }
    return 0;
}

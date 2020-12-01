#ifndef ROBOT_H
#define ROBOT_H

#include <stdint.h>

typedef struct {
    uint8_t endstop;
    uint16_t counter;
} Robot;

// Since these functions are only used once, it makes sense
// or them to be static, but it only saves about 16 bytes of
// program memory, which isn't worth the reduced readability.
void robot_init(Robot *robot);
void robot_loop(Robot *robot);

#endif

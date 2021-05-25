#ifndef ROBOT_H
#define ROBOT_H

#include <stdint.h>
#include "stepper.h"

typedef struct {
    Stepper steppers[3];
} Robot;

// Since these functions are only used once, it makes sense
// for them to be static, but it only saves about 16 bytes of
// program memory, which isn't worth the reduced readability.
void robot_init(Robot *robot);
void robot_loop(Robot *robot);

#endif

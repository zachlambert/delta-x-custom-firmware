#ifndef ROBOT_H
#define ROBOT_H

typedef struct {
    int counter;
} Robot;

// Since these functions are only used once, it makes sense
// or them to be static, but it only saves about 16 bytes of
// program memory, which isn't worth the reduced readability.
void robot_init(Robot *robot);
void robot_loop(Robot *robot);

#endif

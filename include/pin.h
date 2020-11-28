#ifndef PIN_H
#define PIN_H

#include <stdint.h>
#include <avr/pgmspace.h>

typedef enum {
    PORT_A,
    PORT_B,
    PORT_C,
    PORT_D,
    PORT_E,
    PORT_F,
    PORT_G,
    PORT_H,
    PORT_J,
    PORT_K,
    PORT_L,
    PORT_COUNT
} Port;

typedef struct {
    uint8_t port: 4;
    uint8_t n: 3;
} PinImpl;

typedef const PinImpl *const Pin;

#define PIN_B5 { .port=PORT_B, .n=5 }
#define PIN_B6 { .port=PORT_B, .n=6 }
#define PIN_B7 { .port=PORT_B, .n=7 }

#define PREG(REG) (*(volatile uint8_t *const)(pgm_read_ptr(&REG)))

void init_output(Pin pin);
void set(Pin pin);
void clear(Pin pin);

#endif

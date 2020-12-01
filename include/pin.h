#ifndef PIN_H
#define PIN_H

#include <stdint.h>
#include <avr/pgmspace.h>
#include "regs.h"

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
} Pin;

#define PREG(REG) ((volatile uint8_t *const)(pgm_read_ptr(&REG)))

extern volatile uint8_t *const PORTx[] PROGMEM;
extern volatile uint8_t *const DDRx[] PROGMEM;
extern volatile uint8_t *const PINx[] PROGMEM;

inline void pin_init_output(Pin pin)
{
    reg_set(PREG(PORTx[pin.port]), pin.n);
    reg_set(PREG(DDRx[pin.port]), pin.n);
}

inline void pin_init_output_inverted(Pin pin)
{
    reg_clear(PREG(PORTx[pin.port]), pin.n);
    reg_set(PREG(DDRx[pin.port]), pin.n);
}

inline void pin_init_input(Pin pin)
{
    reg_clear(PREG(PORTx[pin.port]), pin.n);
    reg_clear(PREG(DDRx[pin.port]), pin.n);
}

inline void pin_init_input_pullup(Pin pin)
{
    reg_set(PREG(PORTx[pin.port]), pin.n);
    reg_clear(PREG(DDRx[pin.port]), pin.n);
}

inline void pin_set(Pin pin)
{
    reg_set(PREG(PORTx[pin.port]), pin.n);
}

inline void pin_clear(Pin pin)
{
    reg_clear(PREG(PORTx[pin.port]), pin.n);
}

inline void pin_write(Pin pin, uint8_t value)
{
    reg_write(PREG(PORTx[pin.port]), pin.n, value);
}

inline uint8_t pin_read(Pin pin)
{
    return reg_read(PREG(PINx[pin.port]), pin.n);
}

#endif

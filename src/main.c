#define TEST3

// Program: 544
// Program with inline void setup: 340
// Data: 8
#ifdef TEST1
#include <util/delay.h>
#include <avr/io.h>

volatile uint8_t *const PORTx[] = {&PORTA, &PORTB};
volatile uint8_t *const DDRx[] = {&DDRA, &DDRB};
typedef enum {
    PORT_A,
    PORT_B,
    PORT_COUNT
} Port;
typedef struct {
    uint8_t port: 4;
    uint8_t n: 3;
} PinImpl;
typedef const PinImpl *const Pin;

#define PIN_B7 { .port=PORT_A, .n=7 }
#define MAKE_PIN(NAME, PIN) \
    const PinImpl _NAME = PIN; \
    Pin NAME = &_NAME;

void setup(const Pin pin)
{
    *PORTx[pin->port] |= 1<<pin->n;
    *DDRx[pin->port] |= 1<<pin->n;
}

int main(void)
{
    MAKE_PIN(led, PIN_B7);
    setup(led);
    while (1) {
        *PORTx[led->port] |= 1<<led->n;
        _delay_ms(500);
        *PORTx[led->port] &= ~(1<<led->n);
        _delay_ms(500);
    }
    return 0;
}
#endif

// Without inline:
//   Program: 438
//   Data: 12
// With inline:
//   Program: 344
//   Data: 12
#ifdef TEST2
#include <util/delay.h>
#include <avr/io.h>

volatile uint8_t *const PORTx[] = {&PORTA, &PORTB};
volatile uint8_t *const DDRx[] = {&DDRA, &DDRB};
typedef enum {
    PORT_A,
    PORT_B,
    PORT_COUNT
} Port;
typedef struct {
    uint8_t port: 4;
    uint8_t n: 3;
} PinImpl;
typedef const PinImpl *const Pin;

#define PIN_B7 { .port=PORT_A, .n=7 }
#define MAKE_PIN(NAME, PIN) \
    const PinImpl _NAME = PIN; \
    Pin NAME = &_NAME;

inline void setup(const Pin pin)
{
    *PORTx[pin->port] |= 1<<pin->n;
    *DDRx[pin->port] |= 1<<pin->n;
}

MAKE_PIN(led, PIN_B7);
int main(void)
{
    setup(led);
    while (1) {
        *PORTx[led->port] |= 1<<led->n;
        _delay_ms(500);
        *PORTx[led->port] &= ~(1<<led->n);
        _delay_ms(500);
    }
    return 0;
}
#endif

// Without inline:
//   Program: 544
//   Data: 8
// With inline:
//   Program: 340
//   Data: 8
#ifdef TEST3
#include <util/delay.h>
#include <avr/io.h>

volatile uint8_t *const PORTx[] = {
    &PORTA, &PORTB, &PORTC, &PORTD, &PORTE, &PORTF, &PORTG, &PORTH,
    &PORTJ, &PORTK, &PORTL
};
volatile uint8_t *const DDRx[] = {
    &DDRA, &DDRB, &DDRC, &DDRD, &DDRE, &DDRF, &DDRG, &DDRH,
    &DDRJ, &DDRK, &DDRL
};

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

#define PIN_B7 { .port=PORT_A, .n=7 }
#define MAKE_PIN(NAME, PIN) \
    const PinImpl _NAME = PIN; \
    Pin NAME = &_NAME;

void setup(const Pin pin)
{
    *PORTx[pin->port] |= 1<<pin->n;
    *DDRx[pin->port] |= 1<<pin->n;
}

int main(void)
{
    MAKE_PIN(led, PIN_B7);
    setup(led);
    while (1) {
        *PORTx[led->port] |= 1<<led->n;
        _delay_ms(500);
        *PORTx[led->port] &= ~(1<<led->n);
        _delay_ms(500);
    }
    return 0;
}
#endif

#define TEST5

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
//   Program: 672
//   Data: 48
// With inline:
//   Program: 392
//   Data: 44
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

#define PIN_B5 { .port=PORT_B, .n=5 }
#define PIN_B6 { .port=PORT_B, .n=6 }
#define PIN_B7 { .port=PORT_B, .n=7 }

#define MAKE_PIN(NAME, IMPL, PIN) \
    const PinImpl IMPL = PIN; \
    Pin NAME = &IMPL;

inline void init_output(Pin pin)
{
    *PORTx[pin->port] |= 1<<pin->n;
    *DDRx[pin->port] |= 1<<pin->n;
}

inline void set(Pin pin)
{
    *PORTx[pin->port] |= 1<<pin->n;
}

inline void clear(Pin pin)
{
    *PORTx[pin->port] &= ~(1<<pin->n);
}

int main(void)
{
    MAKE_PIN(led, _led, PIN_B5);
    MAKE_PIN(led2, _led2, PIN_B6);
    MAKE_PIN(led3, _led3, PIN_B7);

    init_output(led);
    init_output(led2);
    init_output(led3);
    while (1) {
        set(led);
        set(led2);
        set(led3);
        _delay_ms(500);
        clear(led);
        clear(led2);
        clear(led3);
        _delay_ms(500);
    }
    return 0;
}
#endif

// Without inline:
//   Program: 650
//   Data: 54
// With inline:
//   Program: 402
//   Data: 54
#ifdef TEST4
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

#define PIN_B5 { .port=PORT_B, .n=5 }
#define PIN_B6 { .port=PORT_B, .n=6 }
#define PIN_B7 { .port=PORT_B, .n=7 }

#define MAKE_PIN(NAME, IMPL, PIN) \
    const PinImpl IMPL = PIN; \
    Pin NAME = &IMPL;

inline void init_output(Pin pin)
{
    *PORTx[pin->port] |= 1<<pin->n;
    *DDRx[pin->port] |= 1<<pin->n;
}

inline void set(Pin pin)
{
    *PORTx[pin->port] |= 1<<pin->n;
}

inline void clear(Pin pin)
{
    *PORTx[pin->port] &= ~(1<<pin->n);
}

MAKE_PIN(led, _led, PIN_B5);
MAKE_PIN(led2, _led2, PIN_B6);
MAKE_PIN(led3, _led3, PIN_B7);

int main(void)
{
    init_output(led);
    init_output(led2);
    init_output(led3);
    while (1) {
        set(led);
        set(led2);
        set(led3);
        _delay_ms(500);
        clear(led);
        clear(led2);
        clear(led3);
        _delay_ms(500);
    }
    return 0;
}
#endif

// Without inline:
//   Program: 672
//   Data: 4
// With inline:
//   Program: 494
//   Data: 0
#ifdef TEST5
#include <util/delay.h>
#include <avr/io.h>
#include <avr/pgmspace.h>

volatile uint8_t *const PORTx[] PROGMEM = {
    &PORTA, &PORTB, &PORTC, &PORTD, &PORTE, &PORTF, &PORTG, &PORTH,
    &PORTJ, &PORTK, &PORTL
};
volatile uint8_t *const DDRx[] PROGMEM = {
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

#define PIN_B5 { .port=PORT_B, .n=5 }
#define PIN_B6 { .port=PORT_B, .n=6 }
#define PIN_B7 { .port=PORT_B, .n=7 }

#define MAKE_PIN(NAME, IMPL, PIN) \
    const PinImpl IMPL = PIN; \
    Pin NAME = &IMPL;

#define PREG(REG) (*(volatile uint8_t *const)(pgm_read_ptr(&REG)))

void init_output(Pin pin)
{
    PREG(PORTx[pin->port]) |= 1<<pin->n;
    PREG(DDRx[pin->port]) |= 1<<pin->n;
}

void set(Pin pin)
{
    PREG(PORTx[pin->port]) |= 1<<pin->n;
}

void clear(Pin pin)
{
    PREG(PORTx[pin->port]) &= ~(1<<pin->n);
}

int main(void)
{
    MAKE_PIN(led, _led, PIN_B5);
    MAKE_PIN(led2, _led2, PIN_B6);
    MAKE_PIN(led3, _led3, PIN_B7);

    init_output(led);
    init_output(led2);
    init_output(led3);
    while (1) {
        set(led);
        set(led2);
        set(led3);
        _delay_ms(500);
        clear(led);
        clear(led2);
        clear(led3);
        _delay_ms(500);
    }
    return 0;
}
#endif

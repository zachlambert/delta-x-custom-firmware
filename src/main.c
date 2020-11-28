#include <util/delay.h>
#include <avr/io.h>

#define TEST4

// Program: 306
// Data: 0
#ifdef TEST1
int main(void)
{
    PORTB |= 1<<7;
    DDRB |= 1<<7;
    while (1) {
        PORTB |= 1<<7;
        _delay_ms(500);
        PORTB &= ~(1<<7);
        _delay_ms(500);
    }
    return 0;
}
#endif

// Program: 340
// Data: 8
#ifdef TEST2
volatile uint8_t *const PORTx[] = {&PORTA, &PORTB};
volatile uint8_t *const DDRx[] = {&DDRA, &DDRB};
typedef enum {
    PORT_A,
    PORT_B
} Port;
typedef struct {
    uint8_t port: 4;
    uint8_t n: 4;
} Pin;
int main(void)
{
    const Pin led = { .port=PORT_A, .n=7 };
    *PORTx[led.port] |= 1<<led.n;
    *DDRx[led.port] |= 1<<led.n;
    while (1) {
        *PORTx[led.port] |= 1<<led.n;
        _delay_ms(500);
        *PORTx[led.port] &= ~(1<<led.n);
        _delay_ms(500);
    }
    return 0;
}
#endif

// Program: 540
// Program with inline void setup: 340
// Data: 8
#ifdef TEST3

volatile uint8_t *const PORTx[] = {&PORTA, &PORTB};
volatile uint8_t *const DDRx[] = {&DDRA, &DDRB};
typedef enum {
    PORT_A,
    PORT_B
} Port;
typedef struct {
    uint8_t port: 4;
    uint8_t n: 4;
} Pin;

void setup(const Pin *pin)
{
    *PORTx[pin->port] |= 1<<pin->n;
    *DDRx[pin->port] |= 1<<pin->n;
}

int main(void)
{
    const Pin led = { .port=PORT_A, .n=7 };
    setup(&led);
    while (1) {
        *PORTx[led.port] |= 1<<led.n;
        _delay_ms(500);
        *PORTx[led.port] &= ~(1<<led.n);
        _delay_ms(500);
    }
    return 0;
}
#endif

// Program: 410
// Program with inline void setup: 340
// Data: 8
#ifdef TEST4

volatile uint8_t *const PORTx[] = {&PORTA, &PORTB};
volatile uint8_t *const DDRx[] = {&DDRA, &DDRB};
typedef enum {
    PORT_A,
    PORT_B
} Port;
typedef struct {
    uint8_t port: 4;
    uint8_t n: 4;
} Pin;

inline void setup(const Pin pin)
{
    *PORTx[pin.port] |= 1<<pin.n;
    *DDRx[pin.port] |= 1<<pin.n;
}

int main(void)
{
    const Pin led = { .port=PORT_A, .n=7 };
    setup(led);
    while (1) {
        *PORTx[led.port] |= 1<<led.n;
        _delay_ms(500);
        *PORTx[led.port] &= ~(1<<led.n);
        _delay_ms(500);
    }
    return 0;
}
#endif

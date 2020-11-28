#include "pin.h"
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

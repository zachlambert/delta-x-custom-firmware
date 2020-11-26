#include <avr/delay.h>
#include <avr/io.h>

int main(void)
{
    // LED: PB7

    // Configure as sourcing output
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

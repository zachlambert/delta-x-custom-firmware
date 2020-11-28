#ifndef REGS_H
#define REGS_H

#include <stdint.h>

inline void reg_write_bit(volatile uint8_t *reg, uint8_t bit, uint8_t value)
{
    if (value) {
        *reg |= 1<<bit;
    } else {
        *reg &= ~(1<<bit);
    }
}

inline uint8_t reg_read_bit(volatile uint8_t *reg, uint8_t bit)
{
    return (*reg >> bit) & 0x01;
}

inline void reg_write_mask(volatile uint8_t *reg, uint8_t shift, uint8_t mask, uint8_t value)
{
    *reg &= ~(mask << shift);
    *reg |= (value & mask) << shift;
}

inline uint8_t reg_read_mask(volatile uint8_t *reg, uint8_t shift, uint8_t mask)
{
    return (*reg & (mask << shift)) >> shift;
}

#endif

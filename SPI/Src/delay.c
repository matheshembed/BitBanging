/*
 * delay.c
 *
 *  Created on: 07-Jul-2026
 *      Author: mathe
 */

#include "delay.h"

void delay_cycles(volatile uint32_t cycles)
{
    while(cycles--)
    {
        __asm__("nop");
    }
}

void delay_us(uint32_t us)
{
    while(us--)
    {
        delay_cycles(4);
    }
}

void delay_ms(uint32_t ms)
{
    while(ms--)
    {
        delay_us(1000);
    }
}

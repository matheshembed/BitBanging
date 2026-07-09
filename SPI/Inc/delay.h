/*
 * delay.h
 *
 *  Created on: 07-Jul-2026
 *      Author: mathe
 */

#ifndef DELAY_H_
#define DELAY_H_

#include <stdint.h>

void delay_cycles(volatile uint32_t cycles);
void delay_us(uint32_t us);
void delay_ms(uint32_t ms);


#endif /* DELAY_H_ */

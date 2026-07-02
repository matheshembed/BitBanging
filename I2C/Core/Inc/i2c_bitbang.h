#ifndef I2C_BITBANG_H
#define I2C_BITBANG_H

#include <stdint.h>
#include "main.h"

void I2C_Init(void);

void I2C_WriteRegister(uint8_t deviceAddr,
                       uint8_t regAddr,
                       uint8_t data);

uint8_t I2C_ReadRegister(uint8_t deviceAddr,
                         uint8_t regAddr);

void I2C_ReadRegisters(uint8_t deviceAddr,
                       uint8_t startReg,
                       uint8_t *buffer,
                       uint16_t length);

#endif

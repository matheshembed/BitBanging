#ifndef I2C_BITBANG_H
#define I2C_BITBANG_H

#include "main.h"
#include "stm32f446xx.h"

#define SDA_PORT GPIOB
#define SDA_PIN  GPIO_PIN_6

#define SCL_PORT GPIOB
#define SCL_PIN  GPIO_PIN_7

uint8_t I2C_ReadRegister(uint8_t deviceAddr,
                         uint8_t regAddr);

void I2C_WriteRegister(uint8_t deviceAddr,
                       uint8_t regAddr,
                       uint8_t data);

void I2C_ReadRegisters(uint8_t deviceAddr,
                       uint8_t startReg,
                       uint8_t *buffer,
                       uint16_t length);

#endif

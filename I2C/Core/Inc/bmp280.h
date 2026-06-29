#ifndef BMP280_H
#define BMP280_H

#include "main.h"
#include <stdint.h>

#define BMP280_ADDRESS      0x76

#define BMP280_CHIP_ID      0xD0
#define BMP280_RESET        0xE0
#define BMP280_STATUS       0xF3
#define BMP280_CTRL_MEAS    0xF4
#define BMP280_CONFIG       0xF5

#define BMP280_PRESS_MSB    0xF7
#define BMP280_TEMP_MSB     0xFA

uint8_t BMP280_Init(void);

float BMP280_ReadTemperature(void);
float BMP280_ReadPressure(void);

#endif

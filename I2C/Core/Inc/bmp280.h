#ifndef BMP280_H
#define BMP280_H

#include <stdint.h>
#include "stm32f446xx.h"

#define BMP280_I2C_ADDRESS      0x76U

#define BMP280_CHIP_ID          0xD0U
#define BMP280_RESET            0xE0U
#define BMP280_STATUS           0xF3U
#define BMP280_CTRL_MEAS        0xF4U
#define BMP280_CONFIG           0xF5U

#define BMP280_PRESS_MSB        0xF7U
#define BMP280_TEMP_MSB         0xFAU

#define BMP280_CALIB_START      0x88U
#define BMP280_CALIB_LENGTH     24U

typedef enum
{
    BMP280_OK = 0,
    BMP280_ERROR
} BMP280_Status_t;

BMP280_Status_t BMP280_Init(void);

float BMP280_ReadTemperature(void);
float BMP280_ReadPressure(void);

#endif

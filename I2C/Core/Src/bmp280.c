/*
 * bmp280 driver using bit banged i2c api's
 * Author: mathesh
 * Date: 29/06/2026
 */
#include "bmp280.h"
#include "i2c_bitbang.h"

#include <stdint.h>
static uint16_t dig_T1;
static int16_t dig_T2;
static int16_t dig_T3;

static uint16_t dig_P1;
static int16_t dig_P2;
static int16_t dig_P3;
static int16_t dig_P4;
static int16_t dig_P5;
static int16_t dig_P6;
static int16_t dig_P7;
static int16_t dig_P8;
static int16_t dig_P9;

static int32_t t_fine;

static void BMP280_ReadCalibration(void);

static uint8_t BMP280_ReadChipID(void)
{
    return I2C_ReadRegister(BMP280_ADDRESS,
                            BMP280_CHIP_ID);
}

uint8_t BMP280_Init(void)
{
    uint8_t chipID;

    chipID = BMP280_ReadChipID();

    if(chipID != 0x58)
    {
        return 0;
    }

    I2C_WriteRegister(BMP280_ADDRESS,
                      BMP280_CTRL_MEAS,
                      0x27);

    HAL_Delay(100);

    BMP280_ReadCalibration();

    return 1;
}
static void BMP280_ReadCalibration(void)
{
    uint8_t calib[24];

    I2C_ReadRegisters(BMP280_ADDRESS, 0x88, calib, 24);

    dig_T1 = (uint16_t)(calib[1] << 8) | calib[0];
    dig_T2 = (int16_t)(calib[3] << 8) | calib[2];
    dig_T3 = (int16_t)(calib[5] << 8) | calib[4];

    dig_P1 = (uint16_t)(calib[7] << 8) | calib[6];
    dig_P2 = (int16_t)(calib[9] << 8) | calib[8];
    dig_P3 = (int16_t)(calib[11] << 8) | calib[10];
    dig_P4 = (int16_t)(calib[13] << 8) | calib[12];
    dig_P5 = (int16_t)(calib[15] << 8) | calib[14];
    dig_P6 = (int16_t)(calib[17] << 8) | calib[16];
    dig_P7 = (int16_t)(calib[19] << 8) | calib[18];
    dig_P8 = (int16_t)(calib[21] << 8) | calib[20];
    dig_P9 = (int16_t)(calib[23] << 8) | calib[22];
}

float BMP280_ReadTemperature(void)
{
    uint8_t tempRaw[3];
    uint32_t adc_T;
    int32_t var1;
    int32_t var2;
    int32_t T;

    I2C_ReadRegisters(BMP280_ADDRESS,
                      BMP280_TEMP_MSB,
                      tempRaw,
                      3);

    adc_T =
        ((uint32_t)tempRaw[0] << 12) |
        ((uint32_t)tempRaw[1] << 4)  |
        (tempRaw[2] >> 4);

    var1 = ((((adc_T >> 3) - ((int32_t)dig_T1 << 1))) *
            ((int32_t)dig_T2)) >> 11;

    var2 = (((((adc_T >> 4) - ((int32_t)dig_T1)) *
             ((adc_T >> 4) - ((int32_t)dig_T1))) >> 12) *
            ((int32_t)dig_T3)) >> 14;

    t_fine = var1 + var2;

    T = (t_fine * 5 + 128) >> 8;

    return T / 100.0f;
}

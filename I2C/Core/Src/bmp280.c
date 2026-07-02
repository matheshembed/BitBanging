/*
 * bmp280.c
 *
 * BMP280 Driver using Software Bit-Banged I2C
 *
 * Author : Mathesh
 */

#include "bmp280.h"
#include "i2c_bitbang.h"
#include "main.h"

#include <stdint.h>
#define BMP280_CHIP_ID_VALUE      0x58U
#define BMP280_CTRL_MEAS_VALUE    0x27U

/*--------------------------------------------------------------------------*/
/* Private Types                                                            */
/*--------------------------------------------------------------------------*/

typedef struct
{
    uint16_t dig_T1;
    int16_t  dig_T2;
    int16_t  dig_T3;

    uint16_t dig_P1;
    int16_t  dig_P2;
    int16_t  dig_P3;
    int16_t  dig_P4;
    int16_t  dig_P5;
    int16_t  dig_P6;
    int16_t  dig_P7;
    int16_t  dig_P8;
    int16_t  dig_P9;

} BMP280_Calibration_t;

/*--------------------------------------------------------------------------*/
/* Private Variables                                                        */
/*--------------------------------------------------------------------------*/

static BMP280_Calibration_t calib;

static int32_t t_fine;

/*--------------------------------------------------------------------------*/
/* Private Function Prototypes                                              */
/*--------------------------------------------------------------------------*/

static uint8_t BMP280_ReadChipID(void);
static void BMP280_ReadCalibration(void);

/*--------------------------------------------------------------------------*/
/* Private Functions                                                        */
/*--------------------------------------------------------------------------*/

static uint8_t BMP280_ReadChipID(void)
{
    return I2C_ReadRegister(BMP280_I2C_ADDRESS,
                            BMP280_CHIP_ID);
}

static void BMP280_ReadCalibration(void)
{
    uint8_t buffer[BMP280_CALIB_LENGTH];

    I2C_ReadRegisters(BMP280_I2C_ADDRESS,
                      BMP280_CALIB_START,
                      buffer,
                      BMP280_CALIB_LENGTH);

    calib.dig_T1 = (uint16_t)((buffer[1] << 8)  | buffer[0]);
    calib.dig_T2 = (int16_t) ((buffer[3] << 8)  | buffer[2]);
    calib.dig_T3 = (int16_t) ((buffer[5] << 8)  | buffer[4]);

    calib.dig_P1 = (uint16_t)((buffer[7] << 8)  | buffer[6]);
    calib.dig_P2 = (int16_t) ((buffer[9] << 8)  | buffer[8]);
    calib.dig_P3 = (int16_t) ((buffer[11] << 8) | buffer[10]);
    calib.dig_P4 = (int16_t) ((buffer[13] << 8) | buffer[12]);
    calib.dig_P5 = (int16_t) ((buffer[15] << 8) | buffer[14]);
    calib.dig_P6 = (int16_t) ((buffer[17] << 8) | buffer[16]);
    calib.dig_P7 = (int16_t) ((buffer[19] << 8) | buffer[18]);
    calib.dig_P8 = (int16_t) ((buffer[21] << 8) | buffer[20]);
    calib.dig_P9 = (int16_t) ((buffer[23] << 8) | buffer[22]);
}

/*--------------------------------------------------------------------------*/
/* Public Functions                                                         */
/*--------------------------------------------------------------------------*/

BMP280_Status_t BMP280_Init(void)
{
    uint8_t chipID;

    chipID = BMP280_ReadChipID();

    if(chipID != BMP280_CHIP_ID_VALUE)
    {
        return BMP280_ERROR;
    }

    /* Read factory calibration */
    BMP280_ReadCalibration();

    /* Configure sensor */
    I2C_WriteRegister(BMP280_I2C_ADDRESS,
                      BMP280_CTRL_MEAS,
                      BMP280_CTRL_MEAS_VALUE);

    HAL_Delay(10);

    return BMP280_OK;
}

float BMP280_ReadTemperature(void)
{
    uint8_t rawTemp[3];

    uint32_t adc_T;

    int32_t var1;
    int32_t var2;
    int32_t temperature;

    /* Read raw temperature registers */
    I2C_ReadRegisters(BMP280_I2C_ADDRESS,
                      BMP280_TEMP_MSB,
                      rawTemp,
                      3);

    /* Convert 3 bytes to 20-bit ADC value */
    adc_T = ((uint32_t)rawTemp[0] << 12) |
            ((uint32_t)rawTemp[1] << 4)  |
            ((uint32_t)rawTemp[2] >> 4);

    /* Bosch temperature compensation */
    var1 = ((((int32_t)(adc_T >> 3) -
              ((int32_t)calib.dig_T1 << 1))) *
              (int32_t)calib.dig_T2) >> 11;

    var2 = (((((int32_t)(adc_T >> 4) -
               (int32_t)calib.dig_T1) *
              ((int32_t)(adc_T >> 4) -
               (int32_t)calib.dig_T1)) >> 12) *
              (int32_t)calib.dig_T3) >> 14;

    t_fine = var1 + var2;

    temperature = (t_fine * 5 + 128) >> 8;

    return (float)temperature / 100.0f;
}

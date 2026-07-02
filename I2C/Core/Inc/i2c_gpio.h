/**
 ******************************************************************************
 * @file    i2c_gpio.h
 * @brief   GPIO Abstraction Layer for Software I2C
 * @author  Mathesh
 ******************************************************************************
 */

#ifndef I2C_GPIO_H
#define I2C_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "stm32f446xx.h"
#include "stm32f4xx_hal_gpio.h"

/*==========================================================================*/
/* GPIO Configuration                                                       */
/*==========================================================================*/

#define I2C_GPIO_PORT      GPIOB

#define SDA_PORT           I2C_GPIO_PORT
#define SDA_PIN            GPIO_PIN_6

#define SCL_PORT           I2C_GPIO_PORT
#define SCL_PIN            GPIO_PIN_7

#define I2C_WRITE          0U
#define I2C_READ           1U

/*==========================================================================*/
/* SDA Control                                                              */
/*==========================================================================*/

/**
 * @brief Release SDA line (HIGH)
 */
__STATIC_INLINE void SDA_HIGH(void)
{
    SDA_PORT->BSRR = SDA_PIN;
}

/**
 * @brief Drive SDA LOW
 */
__STATIC_INLINE void SDA_LOW(void)
{
    SDA_PORT->BSRR = ((uint32_t)SDA_PIN << 16U);
}

/**
 * @brief Read SDA state
 *
 * @retval 0 = LOW
 *         1 = HIGH
 */
__STATIC_INLINE uint8_t SDA_READ(void)
{
    return ((SDA_PORT->IDR & SDA_PIN) ? 1U : 0U);
}

/*==========================================================================*/
/* SCL Control                                                              */
/*==========================================================================*/

/**
 * @brief Release SCL line (HIGH)
 */
__STATIC_INLINE void SCL_HIGH(void)
{
    SCL_PORT->BSRR = SCL_PIN;
}

/**
 * @brief Drive SCL LOW
 */
__STATIC_INLINE void SCL_LOW(void)
{
    SCL_PORT->BSRR = ((uint32_t)SCL_PIN << 16U);
}

/**
 * @brief Read SCL state
 *
 * @retval 0 = LOW
 *         1 = HIGH
 */
__STATIC_INLINE uint8_t SCL_READ(void)
{
    return ((SCL_PORT->IDR & SCL_PIN) ? 1U : 0U);
}

/*==========================================================================*/
/* Optional GPIO Direction Control                                          */
/*==========================================================================*/
/*
 * These are not required for the BMP280 because the GPIO is configured
 * as Open-Drain Output with Pull-Up.
 *
 * They are included for future compatibility with devices that require
 * explicit direction changes.
 */

__STATIC_INLINE void SDA_OUTPUT(void)
{
    SDA_PORT->MODER &= ~(3U << (6U * 2U));
    SDA_PORT->MODER |=  (1U << (6U * 2U));
}

__STATIC_INLINE void SDA_INPUT(void)
{
    SDA_PORT->MODER &= ~(3U << (6U * 2U));
}

__STATIC_INLINE void SCL_OUTPUT(void)
{
    SCL_PORT->MODER &= ~(3U << (7U * 2U));
    SCL_PORT->MODER |=  (1U << (7U * 2U));
}

__STATIC_INLINE void SCL_INPUT(void)
{
    SCL_PORT->MODER &= ~(3U << (7U * 2U));
}

#ifdef __cplusplus
}
#endif

#endif /* I2C_GPIO_H */

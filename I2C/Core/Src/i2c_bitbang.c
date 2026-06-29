/*
 * i2c_bitbang.c
 *
 *  Created on: 28-Jun-2026
 *      Author: mathe
 */

#include "i2c_bitbang.h"

static void SDA_HIGH(void)
{
    HAL_GPIO_WritePin(SDA_PORT, SDA_PIN, GPIO_PIN_SET);
}

static void SDA_LOW(void)
{
    HAL_GPIO_WritePin(SDA_PORT, SDA_PIN, GPIO_PIN_RESET);
}

static void SCL_HIGH(void)
{
    HAL_GPIO_WritePin(SCL_PORT, SCL_PIN, GPIO_PIN_SET);
}

static void SCL_LOW(void)
{
    HAL_GPIO_WritePin(SCL_PORT, SCL_PIN, GPIO_PIN_RESET);
}

static void I2C_Delay(void)
{
	HAL_Delay(100);
}

static void I2C_Start(void)
{
    /* Bus Idle */

    SDA_HIGH();
    SCL_HIGH();

    I2C_Delay();

    /* START */

    SDA_LOW();

    I2C_Delay();

    SCL_LOW();

    I2C_Delay();
}

static void I2C_Stop(void)
{
    SDA_LOW();

    I2C_Delay();

    SCL_HIGH();

    I2C_Delay();

    SDA_HIGH();

    I2C_Delay();
}

static void I2C_WriteBit(uint8_t bit)
{
    if(bit)
        SDA_HIGH();
    else
        SDA_LOW();

    I2C_Delay();

    SCL_HIGH();

    I2C_Delay();

    SCL_LOW();

    I2C_Delay();
}

	static void I2C_WriteByte(uint8_t data)
	{
		for(int i = 7; i >= 0; i--)
		{
			I2C_WriteBit((data >> i) & 0x01);
		}
	}

	static uint8_t SDA_READ(void)
	{
		return HAL_GPIO_ReadPin(SDA_PORT, SDA_PIN);
	}

static uint8_t I2C_ReadACK(void)
{
    uint8_t ack;

    SDA_HIGH();

    I2C_Delay();

    SCL_HIGH();

    I2C_Delay();

    ack = SDA_READ();

    SCL_LOW();

    I2C_Delay();

    return ack;
}

static uint8_t I2C_ReadByte(void)
{
    uint8_t data = 0;

    SDA_HIGH();          // Release SDA

    for(int i = 7; i >= 0; i--)
    {
        I2C_Delay();

        SCL_HIGH();

        I2C_Delay();

        if(SDA_READ())
            data |= (1 << i);

        SCL_LOW();
    }

    return data;
}

static void I2C_SendNACK(void)
{
    SDA_HIGH();      // Release SDA (HIGH = NACK)

    I2C_Delay();

    SCL_HIGH();

    I2C_Delay();

    SCL_LOW();

    I2C_Delay();
}

void I2C_WriteRegister(uint8_t deviceAddr,uint8_t regAddr,uint8_t data)
{
    I2C_Start();

    /* Device Address + Write */
    I2C_WriteByte(deviceAddr << 1);
    I2C_ReadACK();

    /* Register Address */
    I2C_WriteByte(regAddr);
    I2C_ReadACK();

    /* Register Data */
    I2C_WriteByte(data);
    I2C_ReadACK();

    I2C_Stop();
}

uint8_t I2C_ReadRegister(uint8_t deviceAddr,uint8_t regAddr)
{
    uint8_t data;

    /* Write Phase */
    I2C_Start();

    I2C_WriteByte(deviceAddr << 1); // read = "0" after the device address
    I2C_ReadACK();

    I2C_WriteByte(regAddr);
    I2C_ReadACK();

    /* Repeated START */
    I2C_Start();

    /* Read Phase */
    I2C_WriteByte((deviceAddr << 1) | 0x01);
    I2C_ReadACK();

    data = I2C_ReadByte();

    /* Master sends NACK (last byte) */
    I2C_SendNACK();

    I2C_Stop();

    return data;
}

static void I2C_SendACK(void)
{
    /* Master pulls SDA LOW to ACK */
    SDA_LOW();

    I2C_Delay();

    SCL_HIGH();

    I2C_Delay();

    SCL_LOW();

    I2C_Delay();

    /* Release SDA after ACK */
    SDA_HIGH();
}

void I2C_ReadRegisters(uint8_t deviceAddr,uint8_t startReg,uint8_t *buffer,uint16_t length)
{
    /* Write Phase */
    I2C_Start();

    I2C_WriteByte(deviceAddr << 1);
    I2C_ReadACK();

    I2C_WriteByte(startReg);
    I2C_ReadACK();

    /* Repeated START */
    I2C_Start();

    I2C_WriteByte((deviceAddr << 1) | 0x01);
    I2C_ReadACK();

    /* Read N bytes */
    for(uint16_t i = 0; i < length; i++)
    {
        buffer[i] = I2C_ReadByte();

        if(i == (length - 1))
        {
            /* Last byte */
            I2C_SendNACK();
        }
        else
        {
            /* More bytes expected */
            I2C_SendACK();
        }
    }

    I2C_Stop();
}

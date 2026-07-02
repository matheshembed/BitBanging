/*
 ******************************************************************************
 * @file    i2c_bitbang.c
 * @brief   Software I2C Driver
 * @author  Mathesh
 ******************************************************************************
 */

#include "i2c_bitbang.h"
#include "i2c_gpio.h"

/*==========================================================================*/
/* Private Function Prototypes                                              */
/*==========================================================================*/

static void I2C_Delay(void);
static void I2C_Start(void);
static void I2C_Stop(void);

static void I2C_WriteBit(uint8_t bit);
static void I2C_WriteByte(uint8_t data);

static uint8_t I2C_ReadByte(void);
static uint8_t I2C_ReadACK(void);

static void I2C_SendACK(void);
static void I2C_SendNACK(void);

static void I2C_SetRegister(uint8_t deviceAddr,
                            uint8_t regAddr);

uint8_t I2C_ReadRegister(uint8_t deviceAddr,
                         uint8_t regAddr);

/*==========================================================================*/
/* Software Delay                                                           */
/*==========================================================================*/

static void I2C_Delay(void)
{
    for(volatile uint32_t i = 0; i < 5; i++)
    {
        __NOP();
    }
}

static void I2C_SetRegister(uint8_t deviceAddr,
                            uint8_t regAddr)
{
    I2C_Start();

    I2C_WriteByte(deviceAddr << 1);

    I2C_ReadACK();

    I2C_WriteByte(regAddr);

    I2C_ReadACK();
}


/*==========================================================================*/
/* Generate START Condition                                                 */
/*==========================================================================*/

static void I2C_Start(void)
{
    /* Bus Idle */
    SDA_HIGH();
    SCL_HIGH();

    I2C_Delay();

    /* SDA High -> Low while SCL High */
    SDA_LOW();

    I2C_Delay();

    /* Pull Clock Low */
    SCL_LOW();

    I2C_Delay();
}

/*==========================================================================*/
/* Generate STOP Condition                                                  */
/*==========================================================================*/

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
    {
        SDA_HIGH();
    }
    else
    {
        SDA_LOW();
    }

    I2C_Delay();

    SCL_HIGH();

    I2C_Delay();

    SCL_LOW();

    I2C_Delay();
}

/*==========================================================================*/
/* Write One Byte                                                           */
/*==========================================================================*/

static void I2C_WriteByte(uint8_t data)
{
    for(int8_t bit = 7; bit >= 0; bit--)
    {
        I2C_WriteBit((data >> bit) & 0x01U);
    }
}

	static uint8_t I2C_ReadBit(void)
	{
	    return SDA_READ();
	}

	static uint8_t I2C_ReadACK(void)
	{
	    uint8_t ack;

	    SDA_HIGH();

	    I2C_Delay();

	    SCL_HIGH();

	    I2C_Delay();

	    ack = I2C_ReadBit();

	    SCL_LOW();

	    I2C_Delay();

	    return ack;
	}

	/*==========================================================================*/
	/* Read One Byte                                                            */
	/*==========================================================================*/

	static uint8_t I2C_ReadByte(void)
	{
	    uint8_t data = 0;

	    /* Release SDA */
	    SDA_HIGH();

	    for(int8_t bit = 7; bit >= 0; bit--)
	    {
	        I2C_Delay();

	        SCL_HIGH();

	        I2C_Delay();

	        if(I2C_ReadBit())
	        {
	            data |= (1U << bit);
	        }

	        SCL_LOW();
	    }

	    return data;
	}
	/*==========================================================================*/
	/* Send NACK                                                                */
	/*==========================================================================*/

	static void I2C_SendNACK(void)
	{
	    SDA_HIGH();

	    I2C_Delay();

	    SCL_HIGH();

	    I2C_Delay();

	    SCL_LOW();

	    I2C_Delay();
	}
	void I2C_WriteRegister(uint8_t deviceAddr,
	                       uint8_t regAddr,
	                       uint8_t data)
	{
	    I2C_SetRegister(deviceAddr, regAddr);

	    I2C_WriteByte(data);

	    I2C_ReadACK();

	    I2C_Stop();
	}


/*==========================================================================*/
/* Send ACK                                                                 */
/*==========================================================================*/

static void I2C_SendACK(void)
{
    SDA_LOW();

    I2C_Delay();

    SCL_HIGH();

    I2C_Delay();

    SCL_LOW();

    SDA_HIGH();

    I2C_Delay();
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
uint8_t I2C_ReadRegister(uint8_t deviceAddr,
                         uint8_t regAddr)
{
    uint8_t data;

    I2C_SetRegister(deviceAddr, regAddr);

    I2C_Start();

    I2C_WriteByte((deviceAddr << 1) | I2C_READ);

    I2C_ReadACK();

    data = I2C_ReadByte();

    I2C_SendNACK();

    I2C_Stop();

    return data;
}




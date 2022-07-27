#include "24AA02XE48.h"

static HAL_StatusTypeDef MEM_24AA02XE48_WriteRegisters(MEM_24AA02XE48 *dev, uint8_t reg, uint8_t *data, uint8_t length);
static HAL_StatusTypeDef MEM_24AA02XE48_WriteRegister(MEM_24AA02XE48 *dev, uint8_t reg, uint8_t *data);
static HAL_StatusTypeDef MEM_24AA02XE48_ReadRegisters(MEM_24AA02XE48 *dev, uint8_t reg, uint8_t *data, uint8_t length);
static HAL_StatusTypeDef MEM_24AA02XE48_ReadRegister(MEM_24AA02XE48 *dev, uint8_t reg, uint8_t *data);

int8_t MEM_24AA02XE48_Init(MEM_24AA02XE48 *dev, I2C_HandleTypeDef * i2cHandle)
{
	dev->i2cHandle = i2cHandle;
	dev->isAvalible = false;    
	dev->MAC[0] = 0;
	dev->MAC[1] = 0;
	dev->MAC[2] = 0;
	dev->MAC[3] = 0;
	dev->MAC[4] = 0;
	dev->MAC[5] = 0;

	MEM_24AA02XE48_IsReady(dev);
	
	return 0;
}

HAL_StatusTypeDef MEM_24AA02XE48_GetMAC(MEM_24AA02XE48 *dev)
{
	HAL_StatusTypeDef err = HAL_ERROR;
	err = MEM_24AA02XE48_ReadRegisters(dev, MEM_24AA02XE48_MAC, dev->MAC, sizeof(dev->MAC)/sizeof(uint8_t));
	return err;
}

HAL_StatusTypeDef MEM_24AA02XE48_IsReady(MEM_24AA02XE48 *dev)
{
  HAL_StatusTypeDef err = HAL_ERROR;
	err = HAL_I2C_IsDeviceReady(dev->i2cHandle, MEM_24AA02XE48_I2C_ADDR, 1, MEM_24AA02XE48_WAIT_TIME_MAX);
	if (err == HAL_OK)
	{
		dev->isAvalible = true;
	}
	else
	{
		dev->isAvalible = false;
	}
	return err;
}

HAL_StatusTypeDef MEM_24AA02XE48_PrintOutRegisters(MEM_24AA02XE48 *dev)
{
	#include "stdio.h"
	for(uint16_t reg_no = 0; reg_no<= 0xFF; reg_no++)
	{
		uint8_t value_8;
		HAL_I2C_Mem_Read(dev->i2cHandle, MEM_24AA02XE48_I2C_ADDR, reg_no, I2C_MEMADD_SIZE_8BIT, &value_8, 1, MEM_24AA02XE48_WAIT_TIME_MAX);
		HAL_Delay(10);
		printf("REG %X val %X \n", reg_no, value_8);
	}
	HAL_Delay(50000);
}

static HAL_StatusTypeDef MEM_24AA025E48_WriteRegisters(MEM_24AA02XE48 *dev, uint8_t reg, uint8_t *data, uint8_t length)
{
	return HAL_I2C_Mem_Write(dev->i2cHandle, MEM_24AA02XE48_I2C_ADDR, reg, I2C_MEMADD_SIZE_8BIT, data, length, MEM_24AA02XE48_WAIT_TIME_MAX);
}

static HAL_StatusTypeDef MEM_24AA025E48_WriteRegister(MEM_24AA02XE48 *dev, uint8_t reg, uint8_t *data)
{
	return HAL_I2C_Mem_Write(dev->i2cHandle, MEM_24AA02XE48_I2C_ADDR, reg, I2C_MEMADD_SIZE_8BIT, data, 1, MEM_24AA02XE48_WAIT_TIME_MAX);
}

static HAL_StatusTypeDef MEM_24AA025E48_ReadRegisters(MEM_24AA02XE48 *dev, uint8_t reg, uint8_t *data, uint8_t length)
{
	return HAL_I2C_Mem_Read(dev->i2cHandle, MEM_24AA02XE48_I2C_ADDR, reg, I2C_MEMADD_SIZE_8BIT, data, length, MEM_24AA02XE48_WAIT_TIME_MAX);
}

static HAL_StatusTypeDef MEM_24AA025E48_ReadRegister(MEM_24AA02XE48 *dev, uint8_t reg, uint8_t *data)
{
	return HAL_I2C_Mem_Read(dev->i2cHandle, MEM_24AA02XE48_I2C_ADDR, reg, I2C_MEMADD_SIZE_8BIT, data, 1, MEM_24AA02XE48_WAIT_TIME_MAX);
}

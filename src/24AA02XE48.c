#include "24AA02XE48.h"

#define PAGE_SIZE_24AA02XE48 8

static void MEM_24AA02XE48_Delay(uint32_t msec);

int8_t MEM_24AA02XE48_Init(MEM_24AA02XE48 *dev, I2C_HandleTypeDef * i2cHandle)
{
	if(dev == NULL || i2cHandle == NULL)
	{
		return -1;
	}
	
	dev->i2cHandle = i2cHandle;
	dev->isAvalible = MEM_24AA02XE48_is_present(dev);		
	dev->MAC[0] = 0;
	dev->MAC[1] = 0;
	dev->MAC[2] = 0;
	dev->MAC[3] = 0;
	dev->MAC[4] = 0;
	dev->MAC[5] = 0;
	
	return 0;
}

int8_t MEM_24AA02XE48_GetMAC(MEM_24AA02XE48 *dev)
{
	if(dev == NULL)
	{
		return -1;
	}
	HAL_StatusTypeDef status =  MEM_24AA02XE48_ReadRegisters(dev, MEM_24AA02XE48_MAC, dev->MAC, 8);
	if(status != HAL_OK)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}

bool MEM_24AA02XE48_is_present(MEM_24AA02XE48 *dev)
{
	if(dev == NULL)
	{
		return false;
	}
	if (HAL_I2C_IsDeviceReady(dev->i2cHandle, MEM_24AA02XE48_I2C_ADDR, 1, MEM_24AA02XE48_WAIT_TIME_MAX) == HAL_OK)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int8_t MEM_24AA02XE48_PrintOutRegisters(MEM_24AA02XE48 *dev)
{
	if(dev == NULL)
	{
		return -1;
	}
	#include "stdio.h"
	for(uint16_t reg_no = 0; reg_no<= 0xFF; reg_no++)
	{
		uint8_t value_8 = 0x00;
		if(MEM_24AA02XE48_ReadRegister(dev, reg_no, &value_8)==HAL_OK)
		{
			MEM_24AA02XE48_Delay(10);
			printf("REG %X val %X \n", reg_no, value_8);
		}
	}
}

int8_t MEM_24AA02XE48_WriteRegisters(MEM_24AA02XE48 *dev, uint8_t reg, uint8_t *data, uint8_t length)
{
	if(dev == NULL || data == NULL || length > PAGE_SIZE_24AA02XE48)
	{
		return -1;
	}
	HAL_StatusTypeDef status =  HAL_I2C_Mem_Write(dev->i2cHandle, MEM_24AA02XE48_I2C_ADDR, reg, I2C_MEMADD_SIZE_8BIT, data, length, MEM_24AA02XE48_WAIT_TIME_MAX);
	if(status != HAL_OK)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}

int8_t MEM_24AA02XE48_WriteRegister(MEM_24AA02XE48 *dev, uint8_t reg, uint8_t *data)
{
	if(dev == NULL || data == NULL)
	{
		return -1;
	}
	HAL_StatusTypeDef status = HAL_I2C_Mem_Write(dev->i2cHandle, MEM_24AA02XE48_I2C_ADDR, reg, I2C_MEMADD_SIZE_8BIT, data, 1, MEM_24AA02XE48_WAIT_TIME_MAX);
	if(status != HAL_OK)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}

int8_t MEM_24AA02XE48_ReadRegisters(MEM_24AA02XE48 *dev, uint8_t reg, uint8_t *data, uint8_t length)
{
	if(dev == NULL || data == NULL || length <= 0)
	{
		return -1;
	}
	HAL_StatusTypeDef status = HAL_I2C_Mem_Read(dev->i2cHandle, MEM_24AA02XE48_I2C_ADDR, reg, I2C_MEMADD_SIZE_8BIT, data, length, MEM_24AA02XE48_WAIT_TIME_MAX);
	if(status != HAL_OK)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}

int8_t MEM_24AA02XE48_ReadRegister(MEM_24AA02XE48 *dev, uint8_t reg, uint8_t *data)
{
	if(dev == NULL || data == NULL)
	{
		return -1;
	}
	HAL_StatusTypeDef status = HAL_I2C_Mem_Read(dev->i2cHandle, MEM_24AA02XE48_I2C_ADDR, reg, I2C_MEMADD_SIZE_8BIT, data, 1, MEM_24AA02XE48_WAIT_TIME_MAX);
	if(status != HAL_OK)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}

/**
 * @brief  Creates time delay
 * @param  msec number of miliseconds to wait
 * @retval none
 */
static void MEM_24AA02XE48_Delay(uint32_t msec)
{
	HAL_Delay(msec);
	//osDelay(msec);
}
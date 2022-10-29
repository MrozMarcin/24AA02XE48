#ifndef MEM_24AA02XE48_DRIVER_H
#define MEM_24AA02XE48_DRIVER_H

#include "stm32h7XX_hal.h"
#include "stdbool.h"

#define MEM_24AA02XE48_I2C_ADDR	 			(0x50 << 1) /* 0b1010000x */

#define MEM_24AA02XE48_EEPROM		 			(0x00)
#define MEM_24AA02XE48_MAC						(0xFA)

#define MEM_24AA02XE48_WAIT_TIME_MAX	0xFFFF

typedef struct
{
		I2C_HandleTypeDef *i2cHandle;
		bool isAvalible;
		uint8_t MAC[8];
}MEM_24AA02XE48;

int8_t MEM_24AA02XE48_Init(MEM_24AA02XE48 *dev, I2C_HandleTypeDef * i2cHandle);
bool MEM_24AA02XE48_is_present(MEM_24AA02XE48 *dev);
int8_t MEM_24AA02XE48_GetMAC(MEM_24AA02XE48 *dev);
int8_t MEM_24AA02XE48_PrintOutRegisters(MEM_24AA02XE48 *dev);

int8_t MEM_24AA02XE48_WriteRegisters(MEM_24AA02XE48 *dev, uint8_t reg, uint8_t *data, uint8_t length);
int8_t MEM_24AA02XE48_WriteRegister(MEM_24AA02XE48 *dev, uint8_t reg, uint8_t *data);
int8_t MEM_24AA02XE48_ReadRegisters(MEM_24AA02XE48 *dev, uint8_t reg, uint8_t *data, uint8_t length);
int8_t MEM_24AA02XE48_ReadRegister(MEM_24AA02XE48 *dev, uint8_t reg, uint8_t *data);
#endif /* MEM_24AA02XE48_DRIVER_H */

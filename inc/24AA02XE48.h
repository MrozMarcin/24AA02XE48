#ifndef MEM_24AA02XE48_DRIVER_H
#define MEM_24AA02XE48_DRIVER_H

#include "stm32h7XX_hal.h"
#include "stdbool.h"

#define MEM_24AA02XE48_I2C_ADDR   		(0x50 << 1) /* 0b1010000x */

#define MEM_24AA02XE48_EEPROM     		(0x00)
#define MEM_24AA02XE48_MAC        		(0xFA)

#define MEM_24AA02XE48_WAIT_TIME_MAX 	3000

typedef struct
{
    I2C_HandleTypeDef *i2cHandle;
    bool isAvalible;
    uint8_t MAC[6];
}MEM_24AA02XE48;

int8_t MEM_24AA02XE48_Init(MEM_24AA02XE48 *dev, I2C_HandleTypeDef * i2cHandle);
HAL_StatusTypeDef MEM_24AA02XE48_IsReady(MEM_24AA02XE48 *dev);
HAL_StatusTypeDef MEM_24AA02XE48_GetMAC(MEM_24AA02XE48 *dev);
HAL_StatusTypeDef MEM_24AA02XE48_PrintOutRegisters(MEM_24AA02XE48 *dev);

#endif /* MEM_24AA02XE48_DRIVER_H */

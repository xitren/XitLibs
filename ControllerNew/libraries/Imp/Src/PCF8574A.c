#include "stm32f4xx_hal.h"
#include "PCF8574A.h"
#include "i2c.h"

#define PCF8574A_I2C_ADDR 0x70

extern I2C_HandleTypeDef hi2c2;
//extern uint8_t Z_out_switch;     // ������������� �����


void PCF8574A_set(uint8_t sw)
{
   uint8_t data[1];
   //uint8_t  temp;
   data[0] = sw;
   HAL_I2C_Master_Transmit_IT(&hi2c2, (uint16_t)PCF8574A_I2C_ADDR, (uint8_t *)data, 1);
   //temp = PCF8574A_get();
 }

uint8_t PCF8574A_get(void)
{
  uint8_t data[1];
  HAL_I2C_Master_Receive_IT(&hi2c2, (uint16_t)PCF8574A_I2C_ADDR, (uint8_t *)data, 1);
  return data[0];  
}

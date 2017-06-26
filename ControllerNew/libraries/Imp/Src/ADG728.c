#include "stm32f4xx_hal.h"
#include "ADG728.h"
#include "i2c.h"

#define ADG728_I2C_ADDR 0x98

extern I2C_HandleTypeDef hi2c2;
//extern uint8_t Rfb_switch;     // ������������� �����


void ADG728_set(uint8_t sw)
{
   uint8_t data[1];
   data[0] = sw;
   HAL_I2C_Master_Transmit_IT(&hi2c2, (uint16_t)ADG728_I2C_ADDR, (uint8_t *)data, 1);
 }

uint8_t ADG728_get(void)
{
  uint8_t data[1];
  HAL_I2C_Master_Receive_IT(&hi2c2, (uint16_t)ADG728_I2C_ADDR, (uint8_t *)data, 1);
  return data[0];  
}

void ADG728_reset(void)
{
   uint8_t data[1];
   data[0] = 0x0;
   HAL_I2C_Master_Transmit_IT(&hi2c2, (uint16_t)ADG728_I2C_ADDR, (uint8_t *)data, 1);
}


/* Local headers -------------------------------------------------------------*/
#include "ConfigMem.h"
/*============================================================================*/

/* Private variables ---------------------------------------------------------*/
uint32_t config_reg[CFG_SIZE];
/*============================================================================*/

/* Functions declaration -----------------------------------------------------*/
void InitCfgMem(void)
{
  config_reg[REG_Led_Ch_T1] = 1;
  config_reg[REG_Led_Ch_T2] = 2;
  config_reg[REG_Led_Ch_T3] = 3;
  
  config_reg[REG_Led_Q_T1_Red] = 0;
  config_reg[REG_Led_Q_T1_Green] = 100;
  config_reg[REG_Led_Q_T1_Blue] = 0;
  config_reg[REG_Led_Q_T2_Red] = 0;
  config_reg[REG_Led_Q_T2_Green] = 0;
  config_reg[REG_Led_Q_T2_Blue] = 100;
  config_reg[REG_Led_Q_T3_Red] = 100;
  config_reg[REG_Led_Q_T3_Green] = 0;
  config_reg[REG_Led_Q_T3_Blue] = 0;
  
  config_reg[REG_Led_Start] = 1;
  config_reg[REG_Led_Stop] = 0;
  
  config_reg[REG_Servo_1] = 50;
  config_reg[REG_Servo_2] = 50;
  
  config_reg[REG_Distance] = 0;
  config_reg[REG_Distance_Band] = 0;
  config_reg[REG_Distance_Auto_Band] = 0;
  
  config_reg[REG_CLK_Band] = 0;
  config_reg[REG_CLK_Auto_Band] = 0;
  
  config_reg[REG_Simple_link] = 1;
  
  config_reg[REG_EEG_PocketSize] = 16;
  config_reg[REG_EEG_Auto_Band] = 0;
  
  config_reg[REG_SERVO_1] = 0;
  config_reg[REG_SERVO_2] = 0;
  config_reg[REG_SERVO_3] = 0;
  config_reg[REG_SERVO_4] = 0;
  config_reg[REG_SERVO_5] = 0;
  config_reg[REG_SERVO_6] = 0;
  config_reg[REG_SERVO_7] = 0;
  config_reg[REG_SERVO_8] = 0;
  
  config_reg[REG_ACCEL_X] = 0;
  config_reg[REG_ACCEL_Y] = 0;
  config_reg[REG_ACCEL_Z] = 0;
  config_reg[REG_GYRO_X] = 0;
  config_reg[REG_GYRO_Y] = 0;
  config_reg[REG_GYRO_Z] = 0;
  config_reg[REG_TEMP] = 0;
  
  config_reg[REG_AD_GPIO] = 0x3F;
  config_reg[REG_AD_CONF] = 0;
  config_reg[REG_AD_RP] = 0;
  config_reg[REG_AD_GPIO2] = 0x3F;
  
  config_reg[REG_AD_CH1] = 0;
  config_reg[REG_AD_CH2] = 1;
  config_reg[REG_AD_CH3] = 2;
  config_reg[REG_AD_CH4] = 3;
  config_reg[REG_AD_CH5] = 4;
  config_reg[REG_AD_CH6] = 5;
  config_reg[REG_AD_CH7] = 6;
  config_reg[REG_AD_CH8] = 7;
  config_reg[REG_AD_CHB] = 2;
  
  config_reg[REG_AD_MODE] = 0x14000C;
  
  config_reg[REG_Imp_CH1] = 0;
  config_reg[REG_Imp_CH2] = 0;
  config_reg[REG_Imp_CH3] = 0;
  config_reg[REG_Imp_CH4] = 0;
  config_reg[REG_Imp_CH5] = 0;
  config_reg[REG_Imp_CH6] = 0;
  config_reg[REG_Imp_CH7] = 0;
  
  config_reg[REG_EEG_File] = 0;
  config_reg[REG_UPD_File] = 0;
  
  config_reg[REG_STREAM_REC] = 0;
  return;
}
void WriteMem(uint32_t _adr, uint32_t _val)
{
  if (_adr < CFG_SIZE)
  {
    config_reg[_adr] = _val;
  }
  return;
}
uint32_t ReadMem(uint32_t _adr)
{
  if (_adr < CFG_SIZE)
  {
    return config_reg[_adr];
  }
  return 0;
}
/*============================================================================*/
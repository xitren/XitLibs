
/* Local headers -------------------------------------------------------------*/
#include "ConfigMem.h"
#include "LogModule.h"
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
  
  config_reg[REG_Simple_link] = 0;
  
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
  
  config_reg[REG_ADC_REG1] = 0;
  config_reg[REG_ADC_REG2] = 0;
  config_reg[REG_ADC_REG3] = 0;
  config_reg[REG_ADC_REG4] = 0;
  config_reg[REG_ADC_REG5] = 0;
  config_reg[REG_ADC_REG6] = 0;
  config_reg[REG_ADC_REG7] = 0;
  config_reg[REG_ADC_REG8] = 0;
  config_reg[REG_ADC_REG9] = 0;
  config_reg[REG_ADC_REG10] = 0;
  config_reg[REG_ADC_REG11] = 0;
  config_reg[REG_ADC_REG12] = 0;
  config_reg[REG_ADC_REG13] = 0;
  config_reg[REG_ADC_REG14] = 0;
  config_reg[REG_ADC_REG15] = 0;
  config_reg[REG_ADC_REG16] = 0;
  config_reg[REG_ADC_REG17] = 0;
  config_reg[REG_ADC_REG18] = 0;
  config_reg[REG_ADC_REG19] = 0;
  config_reg[REG_ADC_REG20] = 0;
  config_reg[REG_ADC_REG21] = 0;
  config_reg[REG_ADC_REG22] = 0;
  
  config_reg[REG_ADC_ORDER] = 0x76543210;
  
  config_reg[REG_ADC_CH1] = 0;
  config_reg[REG_ADC_CH2] = 0;
  config_reg[REG_ADC_CH3] = 0;
  config_reg[REG_ADC_CH4] = 0;
  config_reg[REG_ADC_CH5] = 0;
  config_reg[REG_ADC_CH6] = 0;
  config_reg[REG_ADC_CH7] = 0;
  config_reg[REG_ADC_CH8] = 0;
  
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
  config_reg[REG_LOG_LVL] = 5;
  
  config_reg[REG_EYE_ThrH] = 0;
  config_reg[REG_EYE_ThrL] = 0;
  config_reg[REG_EYE_RGB] = 0;
  config_reg[REG_EYE_WIDTH] = 0;
  config_reg[REG_EYE_HEIGHT] = 0;
  config_reg[REG_EYE_FRAME_RATE] = 0;
  config_reg[REG_EYE_ThrH_READ] = 0;
  config_reg[REG_EYE_ThrL_READ] = 0;
  config_reg[REG_EYE_X1] = 0;
  config_reg[REG_EYE_X2] = 0;
  config_reg[REG_EYE_Y1] = 0;
  config_reg[REG_EYE_Y2] = 0;
  return;
}
inline void WriteMem(uint32_t _adr, uint32_t _val)
{
  char buf_local[60];
  if (_adr < CFG_SIZE)
  {
    config_reg[_adr] = _val;
  }
  else
    DBG_LOG_WARNING("Memory address greater than CFG");
  return;
}
inline uint32_t ReadMem(uint32_t _adr)
{
  char buf_local[60];
  if (_adr < CFG_SIZE)
  {
    return config_reg[_adr];
  }
  else
    DBG_LOG_WARNING("Memory address greater than CFG");
  return 0;
}
/*============================================================================*/
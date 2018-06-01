// ----------------------------------------------------------------------------
//
// ConfigMem.c - Contains configuration registers and system API
//
// ----------------------------------------------------------------------------
//
// A.Gusev 04.09.2017 - Original
//
// ----------------------------------------------------------------------------

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
  
  config_reg[REG_ADC_ORDER] = 0x76543298;
  
  config_reg[REG_ADC_CH1] = 0;
  config_reg[REG_ADC_CH2] = 0;
  config_reg[REG_ADC_CH3] = 0;
  config_reg[REG_ADC_CH4] = 0;
  config_reg[REG_ADC_CH5] = 0;
  config_reg[REG_ADC_CH6] = 0;
  config_reg[REG_ADC_CH7] = 0;
  config_reg[REG_ADC_CH8] = 0;
  config_reg[REG_ADC_CHA] = 0;
  config_reg[REG_ADC_CHB] = 0;
  config_reg[REG_ADC_CHC] = 0;
  
  config_reg[REG_Imp_CH1] = 0;
  config_reg[REG_Imp_CH2] = 0;
  config_reg[REG_Imp_CH3] = 0;
  config_reg[REG_Imp_CH4] = 0;
  config_reg[REG_Imp_CH5] = 0;
  config_reg[REG_Imp_CH6] = 0;
  config_reg[REG_Imp_CH7] = 0;
  config_reg[REG_Imp_CH8] = 0;
  config_reg[REG_Imp_CH9] = 0;
  config_reg[REG_Imp_CH10] = 0;
  
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
          
  config_reg[REG_NANOPZ_MOTOR] = 0;
  config_reg[REG_NANOPZ_SPEED] = 0;
  config_reg[REG_NANOPZ_TIME_MS] = 0;
  config_reg[REG_NANOPZ_STEPS] = 0;
  
  config_reg[REG_IMG_1] = 0x00008000;
  config_reg[REG_IMG_2] = 0x0000C000;
  config_reg[REG_IMG_3] = 0x0000E000;
  config_reg[REG_IMG_4] = 0x0000E000;
  config_reg[REG_IMG_5] = 0x00007600;
  config_reg[REG_IMG_6] = 0x00003E00;
  config_reg[REG_IMG_7] = 0x00001C00;
  config_reg[REG_IMG_8] = 0x00000800;
  config_reg[REG_SHOW_INTERNAL] = 0x00000001;
  
  config_reg[REG_IMP_STATE] = 0x00000000;
  config_reg[REG_IMP_STRAP1_ACTIVE_Z] = 0x00000000;
  config_reg[REG_IMP_STRAP1_REACTIVE_Z] = 0x00000000;
  config_reg[REG_IMP_STRAP1_TOTAL_Z] = 0x00000000;
  config_reg[REG_IMP_STRAP2_ACTIVE_Z] = 0x00000000;
  config_reg[REG_IMP_STRAP2_REACTIVE_Z] = 0x00000000;
  config_reg[REG_IMP_ECG_ACTIVE_Z] = 0x00000000;
  config_reg[REG_IMP_ECG_REACTIVE_Z] = 0x00000000;
  config_reg[REG_IMP_ECG_TOTAL_Z] = 0x00000000;
  config_reg[REG_IMP_EMG_ACTIVE_Z] = 0x00000000;
  config_reg[REG_IMP_EMG_REACTIVE_Z] = 0x00000000;
  config_reg[REG_IMP_EMG_TOTAL_Z] = 0x00000000;
  config_reg[REG_IMP_TEMP_CHIP] = 0x00000000;
  config_reg[REG_IMP_GAINFACTOR] = 0x00000000;
  config_reg[REG_IMP_PHASE_SYSTEM] = 0x00000000;
  config_reg[REG_IMP_RCAL_MAGNITUDE] = 0x00000000;
  config_reg[REG_IMP_A] = 0x00000000;
  config_reg[REG_IMP_B] = 0x00000000;
  
  config_reg[REG_AFE_MUX_STATE] = 0x00000000;
  config_reg[REG_AFE_MUX_LSB] = 0x00000000;
  config_reg[REG_AFE_MUX_MSB] = 0x00000000;
  config_reg[REG_AFE_GPIO_STATE] = 0x00000000;
  config_reg[REG_SHOW_INTERNAL1] = 0x00000000;
  config_reg[REG_SHOW_INTERNAL2] = 0x00000000;
  config_reg[REG_SHOW_INTERNAL3] = 0x00000000;
  config_reg[REG_SHOW_INTERNAL4] = 0x00000000;
  config_reg[REG_SHOW_INTERNAL5] = 0x00000000;
  
  config_reg[REG_IMP_MODE] = 0x00000000;
  config_reg[REG_AFE_MODE] = 0x00000000;
  config_reg[REG_SHOW_MODE] = 0x00000000;
  
  
  config_reg[REG_BOT_STAT] = 0x00000000;
  config_reg[REG_BOT_BATTERY] = 0x00000000;
  config_reg[REG_BOT_RED] = 0x00000000;
  config_reg[REG_BOT_RED_M] = 0x00000000;
  config_reg[REG_BOT_IR] = 0x00000000;
  config_reg[REG_BOT_IR_M] = 0x00000000;
  config_reg[REG_BOT_SPO2] = 0x00000000;
  config_reg[REG_BOT_PROXIMITY] = 0x00000000;
  config_reg[REG_BOT_RATIO] = 0x00000000;
  
  config_reg[REG_SHOW_TARG_NUM] = 4;
  config_reg[REG_SHOW_TARG_REP] = 20;
  config_reg[REG_SHOW_STIM_NUM] = 16;
  config_reg[REG_SHOW_STIM_LEN] = 400;
  config_reg[REG_SHOW_BTW_STIM] = 500;
  config_reg[REG_SHOW_BFR_TARG] = 2000;
  return;
}
inline void WriteMem(uint32_t _adr, uint32_t _val)
{
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
  if (_adr < CFG_SIZE)
  {
    return config_reg[_adr];
  }
  else
    DBG_LOG_WARNING("Memory address greater than CFG");
  return 0;
}
/*============================================================================*/
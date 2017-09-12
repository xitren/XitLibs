// ----------------------------------------------------------------------------
//
// ConfigMem.h - Contains configuration registers and system API
//
// ----------------------------------------------------------------------------

/* Global headers ------------------------------------------------------------*/
#include <stdio.h>
#include "xitlibtypes.h"
//#include "stm32f4xx_hal.h"
/*============================================================================*/

/* Public defines ------------------------------------------------------------*/
#define CFG_SIZE 0x70
#define MEMORY_CONFIG 4*CFG_SIZE
/*============================================================================*/

#ifndef __MEMORY_CONFIG_H__
#define __MEMORY_CONFIG_H__  

#ifdef __cplusplus
extern "C" {
#endif

/* Public types --------------------------------------------------------------*/
typedef enum
{
  REG_Led_Ch_T1          =       0x00000000,
  REG_Led_Ch_T2          =       0x00000001,
  REG_Led_Ch_T3          =       0x00000002,
  
  REG_Led_Q_T1_Red       =       0x00000003,
  REG_Led_Q_T1_Green     =       0x00000004,
  REG_Led_Q_T1_Blue      =       0x00000005,
  REG_Led_Q_T2_Red       =       0x00000006,
  REG_Led_Q_T2_Green     =       0x00000007,
  REG_Led_Q_T2_Blue      =       0x00000008,
  REG_Led_Q_T3_Red       =       0x00000009,
  REG_Led_Q_T3_Green     =       0x0000000A,
  REG_Led_Q_T3_Blue      =       0x0000000B,
    
  REG_Led_Stop           =       0x0000000C,
  REG_Led_Start          =       0x0000000D,
  
  REG_Servo_1            =       0x0000000E,
  REG_Servo_2            =       0x0000000F,
  
  REG_Distance           =       0x00000010,
  REG_Distance_Band      =       0x00000011,
  REG_Distance_Auto_Band =       0x00000012,
  
  REG_CLK_Band           =       0x00000013,
  REG_CLK_Auto_Band      =       0x00000014,
  
  REG_Simple_link        =       0x00000015,
          
  REG_EEG_PocketSize     =       0x00000016,
  REG_EEG_Auto_Band      =       0x00000017,
          
  REG_SERVO_1            =       0x00000018,
  REG_SERVO_2            =       0x00000019,
  REG_SERVO_3            =       0x0000001A,
  REG_SERVO_4            =       0x0000001B,
  REG_SERVO_5            =       0x0000001C,
  REG_SERVO_6            =       0x0000001D,
  REG_SERVO_7            =       0x0000001E,
  REG_SERVO_8            =       0x0000001F,
          
  REG_ACCEL_X            =       0x00000020,
  REG_ACCEL_Y            =       0x00000021,
  REG_ACCEL_Z            =       0x00000022,
  REG_GYRO_X             =       0x00000023,
  REG_GYRO_Y             =       0x00000024,
  REG_GYRO_Z             =       0x00000025,
  REG_TEMP               =       0x00000026,
          
  REG_ADC_REG1           =       0x00000027, //REG_ADS_CONFIG1
  REG_ADC_REG2           =       0x00000028, //REG_ADS_CONFIG2
  REG_ADC_REG3           =       0x00000029, //REG_ADS_CONFIG3
  REG_ADC_REG4           =       0x0000002A, //REG_ADS_LOFF
  REG_ADC_REG5           =       0x0000002B, //REG_ADS_BIAS_SENSP         
  REG_ADC_REG6           =       0x0000002C, //REG_ADS_BIAS_SENSN
  REG_ADC_REG7           =       0x0000002D, //REG_ADS_LOFF_SENSP
  REG_ADC_REG8           =       0x0000002E, //REG_ADS_LOFF_SENSN
  REG_ADC_REG9           =       0x0000002F, //REG_ADS_LOFF_FLIP
  REG_ADC_REG10          =       0x00000030, //REG_ADS_GPIO
  REG_ADC_REG11          =       0x00000031, //REG_ADS_MISC1
  REG_ADC_REG12          =       0x00000032, //REG_ADS_MISC2
  REG_ADC_REG13          =       0x00000033, //REG_ADS_CONFIG4
  REG_ADC_REG14          =       0x00000034, //REG_ADS_MODE
          
  REG_ADC_CH1            =       0x00000035,
  REG_ADC_CH2            =       0x00000036,
  REG_ADC_CH3            =       0x00000037,
  REG_ADC_CH4            =       0x00000038,
  REG_ADC_CH5            =       0x00000039,
  REG_ADC_CH6            =       0x0000003A,
  REG_ADC_CH7            =       0x0000003B,
  REG_ADC_CH8            =       0x0000003C,
          
  REG_EEG_File           =       0x0000003D,
  REG_UPD_File           =       0x0000003E,
  REG_STREAM_REC         =       0x0000003F,
  REG_LOG_LVL            =       0x00000040,
          
  REG_EYE_ThrH           =       0x00000041,
  REG_EYE_ThrL           =       0x00000042,
  REG_EYE_RGB            =       0x00000043,
  REG_EYE_WIDTH          =       0x00000044,
  REG_EYE_HEIGHT         =       0x00000045,
  REG_EYE_FRAME_RATE     =       0x00000046,
  REG_EYE_ThrH_READ      =       0x00000047,
  REG_EYE_ThrL_READ      =       0x00000048,
  REG_EYE_X1             =       0x00000049,
  REG_EYE_X2             =       0x0000004A,
  REG_EYE_Y1             =       0x0000004B,
  REG_EYE_Y2             =       0x0000004C,
          
  REG_Imp_CH1            =       0x0000004D,
  REG_Imp_CH2            =       0x0000004E,
  REG_Imp_CH3            =       0x0000004F,
  REG_Imp_CH4            =       0x00000050,
  REG_Imp_CH5            =       0x00000051,
  REG_Imp_CH6            =       0x00000052,
  REG_Imp_CH7            =       0x00000053,  
  REG_Imp_CH8            =       0x00000054,
  REG_Imp_CH9            =       0x00000055,          
  REG_Imp_CH10           =       0x00000056, 
          
  REG_ADC_ORDER          =       0x00000057,
  REG_ADC_REG15          =       0x00000058, //REG_ADS_CH1SET
  REG_ADC_REG16          =       0x00000059, //REG_ADS_CH2SET
  REG_ADC_REG17          =       0x0000005A, //REG_ADS_CH3SET
  REG_ADC_REG18          =       0x0000005B, //REG_ADS_CH4SET
  REG_ADC_REG19          =       0x0000005C, //REG_ADS_CH5SET
  REG_ADC_REG20          =       0x0000005D, //REG_ADS_CH6SET
  REG_ADC_REG21          =       0x0000005E, //REG_ADS_CH7SET
  REG_ADC_REG22          =       0x0000005F, //REG_ADS_CH8SET
          
  REG_POS_X              =       0x00000060,
  REG_POS_Y              =       0x00000061, 
  REG_POS_Z              =       0x00000062, 
  REG_POS_Alpha          =       0x00000063,
  REG_POS_Beta           =       0x00000064,
  REG_POS_Gamma          =       0x00000065
} RegDef;
/*============================================================================*/

/* Public function prototypes ------------------------------------------------*/
void InitCfgMem(void);
void WriteMem(uint32_t _adr, uint32_t _val);
uint32_t ReadMem(uint32_t _adr);
/*============================================================================*/

#ifdef __cplusplus
}
#endif

#endif
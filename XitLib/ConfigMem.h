
/* Global headers ------------------------------------------------------------*/
#include <stdio.h>
#include "xitlibtypes.h"
//#include "stm32f4xx_hal.h"
/*============================================================================*/

/* Public defines ------------------------------------------------------------*/
#define CFG_SIZE 0x40
#define MEMORY_CONFIG 4*CFG_SIZE
/*============================================================================*/

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
          
  REG_AD_GPIO            =       0x00000027,
  REG_AD_CONF            =       0x00000028,
  REG_AD_RP              =       0x00000029,
  REG_AD_GPIO2           =       0x0000002A,
          
  REG_AD_CH1             =       0x0000002B,
  REG_AD_CH2             =       0x0000002C,
  REG_AD_CH3             =       0x0000002D,
  REG_AD_CH4             =       0x0000002E,
  REG_AD_CH5             =       0x0000002F,
  REG_AD_CH6             =       0x00000030,
  REG_AD_CH7             =       0x00000031,
  REG_AD_CH8             =       0x00000032,
  REG_AD_CHB             =       0x00000033,
          
  REG_AD_MODE            =       0x00000034,
  
  REG_Imp_CH1            =       0x00000035,
  REG_Imp_CH2            =       0x00000036,
  REG_Imp_CH3            =       0x00000037,
  REG_Imp_CH4            =       0x00000038,
  REG_Imp_CH5            =       0x00000039,
  REG_Imp_CH6            =       0x0000003A,
  REG_Imp_CH7            =       0x0000003B,
          
  REG_EEG_File           =       0x0000003C,
  REG_UPD_File           =       0x0000003D,
  REG_STREAM_REC         =       0x0000003E
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
// ----------------------------------------------------------------------------
//
// PWMModule.c - Software PWM module
//
// ----------------------------------------------------------------------------
//
// A.Gusev 04.09.2017 - Original
//
// ----------------------------------------------------------------------------

/* Local headers -------------------------------------------------------------*/
#include "PWMModule.h"
#include "ConfigMem.h"
/*============================================================================*/

/* Private types -------------------------------------------------------------*/
typedef enum {
	REG_Led_Ch_T1 = 0x00000000,
	REG_Led_Ch_T2 = 0x00000001,
	REG_Led_Ch_T3 = 0x00000002,
	REG_Led_Q_T1_Red = 0x00000003,
	REG_Led_Q_T1_Green = 0x00000004,
	REG_Led_Q_T1_Blue = 0x00000005,
	REG_Led_Q_T2_Red = 0x00000006,
	REG_Led_Q_T2_Green = 0x00000007,
	REG_Led_Q_T2_Blue = 0x00000008,
	REG_Led_Q_T3_Red = 0x00000009,
	REG_Led_Q_T3_Green = 0x0000000A,
	REG_Led_Q_T3_Blue = 0x0000000B,
	REG_Led_Stop = 0x0000000C,
	REG_Led_Start = 0x0000000D,
	REG_Servo_1 = 0x0000000E,
	REG_Servo_2 = 0x0000000F
} RegDefBase;
/*============================================================================*/

/* Private variables ---------------------------------------------------------*/
uint8_t pwm_led_c_red = 0;
uint8_t pwm_led_c_green = 0;
uint8_t pwm_led_c_blue = 0;
uint8_t pwm_led_red = 0;
uint8_t pwm_led_green = 20;
uint8_t pwm_led_blue = 0;
uint8_t pwm_led_q_red = 0;
uint8_t pwm_led_q_green = 0;
uint8_t pwm_led_q_blue = 0;
uint8_t pwm_servo_1 = 50;
uint8_t pwm_servo_2 = 50;
uint8_t pwm_step = 0;
uint32_t pwm_cnt = 0;
/*============================================================================*/

/* Functions declaration -----------------------------------------------------*/
void ChangeLedsCode(void)
{
	pwm_cnt++;
	if (pwm_cnt > ReadMem(REG_Led_Ch_T1))
	{
		pwm_led_q_red = ReadMem(REG_Led_Q_T1_Red);
		pwm_led_q_green = ReadMem(REG_Led_Q_T1_Green);
		pwm_led_q_blue = ReadMem(REG_Led_Q_T1_Blue);
	}
	if (pwm_cnt > ReadMem(REG_Led_Ch_T2))
	{
		pwm_led_q_red = ReadMem(REG_Led_Q_T2_Red);
		pwm_led_q_green = ReadMem(REG_Led_Q_T2_Green);
		pwm_led_q_blue = ReadMem(REG_Led_Q_T2_Blue);
	}
	if (pwm_cnt > ReadMem(REG_Led_Ch_T3))
	{
		pwm_led_q_red = ReadMem(REG_Led_Q_T3_Red);
		pwm_led_q_green = ReadMem(REG_Led_Q_T3_Green);
		pwm_led_q_blue = ReadMem(REG_Led_Q_T3_Blue);
		pwm_cnt = 0;
	}
	pwm_servo_1 = ReadMem(REG_Servo_1);
	pwm_servo_2 = ReadMem(REG_Servo_2);
	return;
}

void IncPWM(void)
{
	pwm_step++;
	if (pwm_step > 100)
		pwm_step = 0;
	return;
}

void SetCStatLedsUnderPWM(uint8_t cred, uint8_t cgreen, uint8_t cblue)
{
	pwm_led_c_red = cred;
	pwm_led_c_green = cgreen;
	pwm_led_c_blue = cblue;
	return;
}

void SetServo1UnderPWM(uint8_t c)
{
	pwm_servo_1 = c;
	return;
}

void SetServo2UnderPWM(uint8_t c)
{
	pwm_servo_2 = c;
	return;
}

void SetLedsUnderPWM(void)
{
	//    SetLeds(pwm_step < pwm_led_q_green,
	//            pwm_step < pwm_led_q_red,
	//            pwm_step < pwm_led_q_blue);
	return;
}
/*============================================================================*/


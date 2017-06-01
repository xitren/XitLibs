
/* Local headers -------------------------------------------------------------*/
#include "PWMModule.h"
#include "ConfigMem.h"
#ifndef CPU
    #include "stm32f4xx_hal.h"
#endif
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
void SetCStatLedsUnderPWM(uint8_t cred,uint8_t cgreen,uint8_t cblue)
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
    #ifndef CPU
//        if (pwm_step < pwm_led_c_green)
//          HAL_GPIO_WritePin(GPIOJ, GPIO_PIN_12, GPIO_PIN_SET);
//        else
//          HAL_GPIO_WritePin(GPIOJ, GPIO_PIN_12, GPIO_PIN_RESET);
//        if (pwm_step < pwm_led_c_red)
//          HAL_GPIO_WritePin(GPIOJ, GPIO_PIN_13, GPIO_PIN_SET);
//        else
//          HAL_GPIO_WritePin(GPIOJ, GPIO_PIN_13, GPIO_PIN_RESET);
//        if (pwm_step < pwm_led_c_blue)
//          HAL_GPIO_WritePin(GPIOJ, GPIO_PIN_14, GPIO_PIN_SET);
//        else
//          HAL_GPIO_WritePin(GPIOJ, GPIO_PIN_14, GPIO_PIN_RESET);
//
        if (pwm_step < pwm_led_q_green)
          HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, GPIO_PIN_SET);
        else
          HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, GPIO_PIN_RESET);
        if (pwm_step < pwm_led_q_red)
          HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
        else
          HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
        if (pwm_step < pwm_led_q_blue)
          HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, GPIO_PIN_SET);
        else
          HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, GPIO_PIN_RESET);
//
//        if (pwm_step < pwm_led_green)
//          HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);
//        else
//          HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);
//        if (pwm_step < pwm_led_red)
//          HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);
//        else
//          HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);
//        if (pwm_step < pwm_led_blue)
//          HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET);
//        else
//          HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_RESET);
//
//        if (pwm_step < pwm_servo_1)
//          HAL_GPIO_WritePin(GPIOJ, GPIO_PIN_0, GPIO_PIN_SET);
//        else
//          HAL_GPIO_WritePin(GPIOJ, GPIO_PIN_0, GPIO_PIN_RESET);
//        if (pwm_step < pwm_servo_2)
//          HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_SET);
//        else
//          HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_RESET);
    #endif
    return;
}
/*============================================================================*/

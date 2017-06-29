/**
  ******************************************************************************
  * @file    stm32f4xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  *
  * COPYRIGHT(c) 2016 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "stm32f4xx.h"
#include "stm32f4xx_it.h"

/* USER CODE BEGIN 0 */

#include "Handler.h"
#include "main.h"
#include "spi.h"
#include "ImageVisualise.h"

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim7;
extern TIM_HandleTypeDef htim13;
extern TIM_HandleTypeDef htim14;
extern DMA_HandleTypeDef hdma_usart1_rx;
extern DMA_HandleTypeDef hdma_usart1_tx;
extern DMA_HandleTypeDef hdma_usart3_rx;
extern DMA_HandleTypeDef hdma_usart3_tx;
extern UART_HandleTypeDef huart1;
//extern IRDA_HandleTypeDef hirda2;
extern UART_HandleTypeDef huart3;

extern I2C_HandleTypeDef hi2c2;

/******************************************************************************/
/*            Cortex-M4 Processor Interruption and Exception Handlers         */ 
/******************************************************************************/

/**
* @brief This function handles Non maskable interrupt.
*/
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */
      HAL_UART_Transmit(&huart1, (uint8_t *) "hrd1", 4, 1000);

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */

  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
* @brief This function handles Hard fault interrupt.
*/
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */
      HAL_UART_Transmit(&huart1, (uint8_t *) "hrd2", 4, 1000);

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
  }
  /* USER CODE BEGIN HardFault_IRQn 1 */

  /* USER CODE END HardFault_IRQn 1 */
}

/**
* @brief This function handles Memory management fault.
*/
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */
      HAL_UART_Transmit(&huart1, (uint8_t *) "hrd3", 4, 1000);

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
  }
  /* USER CODE BEGIN MemoryManagement_IRQn 1 */

  /* USER CODE END MemoryManagement_IRQn 1 */
}

/**
* @brief This function handles Pre-fetch fault, memory access fault.
*/
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */
      HAL_UART_Transmit(&huart1, (uint8_t *) "hrd4", 4, 1000);

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
  }
  /* USER CODE BEGIN BusFault_IRQn 1 */

  /* USER CODE END BusFault_IRQn 1 */
}

/**
* @brief This function handles Undefined instruction or illegal state.
*/
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */
  HAL_UART_Transmit(&huart1, (uint8_t *) "hrd5", 4, 1000);

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
  }
  /* USER CODE BEGIN UsageFault_IRQn 1 */

  /* USER CODE END UsageFault_IRQn 1 */
}

/**
* @brief This function handles System service call via SWI instruction.
*/
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */
      HAL_UART_Transmit(&huart1, (uint8_t *) "hrd6", 4, 1000);

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
* @brief This function handles Debug monitor.
*/
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
* @brief This function handles Pendable request for system service.
*/
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
* @brief This function handles System tick timer.
*/
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  HAL_SYSTICK_IRQHandler();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f4xx.s).                    */
/******************************************************************************/

//void I2C2_EV_IRQHandler(void)
//{
//  /* USER CODE BEGIN I2C2_EV_IRQn 0 */
//
//  /* USER CODE END I2C2_EV_IRQn 0 */
//  HAL_I2C_EV_IRQHandler(&hi2c2);
//  /* USER CODE BEGIN I2C2_EV_IRQn 1 */
//
//  /* USER CODE END I2C2_EV_IRQn 1 */
//}
//
///**
//* @brief This function handles DMA1 stream1 global interrupt.
//*/
//void DMA1_Stream1_IRQHandler(void)
//{
//  /* USER CODE BEGIN DMA1_Stream1_IRQn 0 */
//
//  /* USER CODE END DMA1_Stream1_IRQn 0 */
//  HAL_DMA_IRQHandler(&hdma_usart3_rx);
//  /* USER CODE BEGIN DMA1_Stream1_IRQn 1 */
//
//  /* USER CODE END DMA1_Stream1_IRQn 1 */
//}
//
///**
//* @brief This function handles DMA1 stream3 global interrupt.
//*/
//void DMA1_Stream3_IRQHandler(void)
//{
//  /* USER CODE BEGIN DMA1_Stream3_IRQn 0 */
//
//  /* USER CODE END DMA1_Stream3_IRQn 0 */
//  HAL_DMA_IRQHandler(&hdma_usart3_tx);
//  /* USER CODE BEGIN DMA1_Stream3_IRQn 1 */
//
//  /* USER CODE END DMA1_Stream3_IRQn 1 */
//}
//
///**
//* @brief This function handles TIM2 global interrupt.
//*/
void TIM2_IRQHandler(void)/**/
{
    uint8_t rd;
    uint8_t cnt;
    uint16_t data_temp;
  /* USER CODE BEGIN TIM2_IRQn 0 */
//  HAL_UART_Transmit(&huart3,"TIM2.",5/*STRING_SIZE*/,100);

  /* USER CODE END TIM2_IRQn 0 */
  HAL_TIM_IRQHandler(&htim2);
  /* USER CODE BEGIN TIM2_IRQn 1 */  

//  SoftPWMHandler();
  if ((cnt%2) == 0)
    devp300showme();
  cnt++;
      
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_RESET);
    data_temp = ImgP[cycle_cnt%8][0];
    HAL_SPI_TransmitReceive(&hspi4, (uint8_t*) &(data_temp), 
                                                    (uint8_t*) &rd, 1, 10);
    data_temp = ImgP[cycle_cnt%8][1];
    HAL_SPI_TransmitReceive(&hspi4, (uint8_t*) &(data_temp), 
                                                    (uint8_t*) &rd, 1, 10);
    data_temp = ImgP[cycle_cnt%8][2];
    HAL_SPI_TransmitReceive(&hspi4, (uint8_t*) &(data_temp), 
                                                    (uint8_t*) &rd, 1, 10);
    data_temp = 1<<((cycle_cnt)%8);
    HAL_SPI_TransmitReceive(&hspi4, (uint8_t*) &(data_temp), 
                                                    (uint8_t*) &rd, 1, 10);
    HAL_GPIO_TogglePin(GPIOE,GPIO_PIN_11);
  
//        WriteMem(REG_ADC_CH8, ((((uint32_t)selection[3]) & 0x000000FF) << 24) |
//                            ((((uint32_t)selection[2]) & 0x000000FF) << 16) |
//                            ((((uint32_t)selection[1]) & 0x000000FF) << 8) |
//                            ((((uint32_t)selection[0]) & 0x000000FF)));
//        AddSample();
  /* USER CODE END TIM2_IRQn 1 */
}
//
///**
//* @brief This function handles USART1 global interrupt.
//*/
void USART1_IRQHandler(void)
{
  /* USER CODE BEGIN USART1_IRQn 0 */

  /* USER CODE END USART1_IRQn 0 */
  HAL_UART_IRQHandler(&huart1);
  /* USER CODE BEGIN USART1_IRQn 1 */

  /* USER CODE END USART1_IRQn 1 */
}
//
///**
//* @brief This function handles USART2 global interrupt.
//*/
//void USART2_IRQHandler(void)
//{
//  /* USER CODE BEGIN USART2_IRQn 0 */
//
//  /* USER CODE END USART2_IRQn 0 */
//  //HAL_IRDA_IRQHandler(&hirda2);
//  /* USER CODE BEGIN USART2_IRQn 1 */
//
//  /* USER CODE END USART2_IRQn 1 */
//}
//
///**
//* @brief This function handles USART3 global interrupt.
//*/
//void USART3_IRQHandler(void)
//{
//  /* USER CODE BEGIN USART3_IRQn 0 */
//
//  /* USER CODE END USART3_IRQn 0 */
//  HAL_UART_IRQHandler(&huart3);
//  /* USER CODE BEGIN USART3_IRQn 1 */
//
//  /* USER CODE END USART3_IRQn 1 */
//}
//
///**
//* @brief This function handles TIM1 trigger and commutation interrupts and TIM11 global interrupt.
//*/
//void TIM1_TRG_COM_TIM11_IRQHandler(void)
//{
//  /* USER CODE BEGIN TIM1_TRG_COM_TIM11_IRQn 0 */
//
//  /* USER CODE END TIM1_TRG_COM_TIM11_IRQn 0 */
////  HAL_TIM_IRQHandler(&htim11);
//  /* USER CODE BEGIN TIM1_TRG_COM_TIM11_IRQn 1 */
//
//  /* USER CODE END TIM1_TRG_COM_TIM11_IRQn 1 */
//}
//
///**
//* @brief This function handles TIM8 update interrupt and TIM13 global interrupt.
//*/
void TIM8_UP_TIM13_IRQHandler(void)
{
  /* USER CODE BEGIN TIM8_UP_TIM13_IRQn 0 */

  /* USER CODE END TIM8_UP_TIM13_IRQn 0 */
  HAL_TIM_IRQHandler(&htim13);
  /* USER CODE BEGIN TIM8_UP_TIM13_IRQn 1 */  

//  HAL_TIM_Base_Stop(&htim13);
//  UartReceiveCompleteHandler();
//  HAL_GPIO_TogglePin(GPIOG,GPIO_PIN_9); //my
  /* USER CODE END TIM8_UP_TIM13_IRQn 1 */
}
//
///**
//* @brief This function handles TIM8 trigger and commutation interrupts and TIM14 global interrupt.
//*/
void TIM8_TRG_COM_TIM14_IRQHandler(void)
{
  /* USER CODE BEGIN TIM8_TRG_COM_TIM14_IRQn 0 */
//  HAL_UART_Transmit(&huart3,"TIM14.",5/*STRING_SIZE*/,100);

  /* USER CODE END TIM8_TRG_COM_TIM14_IRQn 0 */
  HAL_TIM_IRQHandler(&htim14);
  /* USER CODE BEGIN TIM8_TRG_COM_TIM14_IRQn 1 */  

  SecClockHandler();
  StatChangeHandler();
//  HAL_GPIO_TogglePin(GPIOG,GPIO_PIN_9); //my

  /* USER CODE END TIM8_TRG_COM_TIM14_IRQn 1 */
}
//
///**
//* @brief This function handles TIM6 global interrupt, DAC1 and DAC2 underrun error interrupts.
//*/
//void TIM6_DAC_IRQHandler(void)
//{
//  /* USER CODE BEGIN TIM6_DAC_IRQn 0 */
////  HAL_UART_Transmit(&huart3,"TIM6.",5/*STRING_SIZE*/,100);
//
//  /* USER CODE END TIM6_DAC_IRQn 0 */
//  HAL_TIM_IRQHandler(&htim6);
//  /* USER CODE BEGIN TIM6_DAC_IRQn 1 */
//  
//  /* USER CODE END TIM6_DAC_IRQn 1 */
//}
//
///**
//* @brief This function handles DMA2 stream2 global interrupt.
//*/
void DMA2_Stream2_IRQHandler(void)
{
  /* USER CODE BEGIN DMA2_Stream2_IRQn 0 */

  /* USER CODE END DMA2_Stream2_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_usart1_rx);
  /* USER CODE BEGIN DMA2_Stream2_IRQn 1 */

  /* USER CODE END DMA2_Stream2_IRQn 1 */
}
//
///**
//* @brief This function handles DMA2 stream7 global interrupt.
//*/
void DMA2_Stream7_IRQHandler(void)
{
  /* USER CODE BEGIN DMA2_Stream7_IRQn 0 */

  /* USER CODE END DMA2_Stream7_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_usart1_tx);
  /* USER CODE BEGIN DMA2_Stream7_IRQn 1 */
  
  UartTransferCompleteHandler();

  /* USER CODE END DMA2_Stream7_IRQn 1 */
}


extern volatile int counter_for_irq;
/**
* @brief This function handles EXTI line[15:10] interrupts.
*/
void EXTI15_10_IRQHandler(void)
{
    /* USER CODE BEGIN EXTI15_10_IRQn 0 */

    /* USER CODE END EXTI15_10_IRQn 0 */
    HAL_GPIO_EXTI_IRQHandler(BCI_DRDY_Pin);
    /* USER CODE BEGIN EXTI15_10_IRQn 1 */
    
    if (ReadMem(REG_EEG_Auto_Band) > 0)
    {
        ADC_read_data_c();
        WriteMem(REG_ADC_CH8, ((((uint32_t)selection[3]) & 0x000000FF) << 24) |
                                ((((uint32_t)selection[2]) & 0x000000FF) << 16) |
                                ((((uint32_t)selection[1]) & 0x000000FF) << 8) |
                                ((((uint32_t)selection[0]) & 0x000000FF)));
        AddSample();
    }

    /* USER CODE END EXTI15_10_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

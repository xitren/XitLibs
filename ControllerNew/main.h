/**
  ******************************************************************************
  * File Name          : main.h
  * Description        : This file contains the common defines of the application
  ******************************************************************************
  *
  * COPYRIGHT(c) 2017 STMicroelectronics
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H
  /* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/

#define PRINT_MES(X) printf(X)//HAL_UART_Transmit(&huart1, (uint8_t *) X, sizeof(X), 1000)

#define SPI5_CS_Pin GPIO_PIN_6
#define SPI5_CS_GPIO_Port GPIOF
#define SPI5_SCLK_Pin GPIO_PIN_7
#define SPI5_SCLK_GPIO_Port GPIOF
#define BlueNRG_IRQ_Pin GPIO_PIN_10
#define BlueNRG_IRQ_GPIO_Port GPIOF
#define LED_R_SNS_STM_Pin GPIO_PIN_0
#define LED_R_SNS_STM_GPIO_Port GPIOC
#define LED_G_SNS_STM_Pin GPIO_PIN_1
#define LED_G_SNS_STM_GPIO_Port GPIOC
#define LED_B_SNS_STM_Pin GPIO_PIN_2
#define LED_B_SNS_STM_GPIO_Port GPIOC
#define SPI1_CS_Pin GPIO_PIN_4
#define SPI1_CS_GPIO_Port GPIOA
#define SPI1_SCLK_Pin GPIO_PIN_5
#define SPI1_SCLK_GPIO_Port GPIOA
#define SPI1_MISO_Pin GPIO_PIN_6
#define SPI1_MISO_GPIO_Port GPIOA
#define SPI1_MOSI_Pin GPIO_PIN_7
#define SPI1_MOSI_GPIO_Port GPIOA
#define GPIO1_Pin GPIO_PIN_4
#define GPIO1_GPIO_Port GPIOC
#define GPIO2_Pin GPIO_PIN_5
#define GPIO2_GPIO_Port GPIOC
#define VPI_DG_Pin GPIO_PIN_13
#define VPI_DG_GPIO_Port GPIOF
#define VPI_DF1_Pin GPIO_PIN_14
#define VPI_DF1_GPIO_Port GPIOF
#define VPI_DF0_Pin GPIO_PIN_15
#define VPI_DF0_GPIO_Port GPIOF
#define VPI_EF_Pin GPIO_PIN_0
#define VPI_EF_GPIO_Port GPIOG
#define VPI_TF_Pin GPIO_PIN_1
#define VPI_TF_GPIO_Port GPIOG
#define VPI_OE_R_Pin GPIO_PIN_7
#define VPI_OE_R_GPIO_Port GPIOE
#define VPI_OE_G_Pin GPIO_PIN_8
#define VPI_OE_G_GPIO_Port GPIOE
#define VPI_OE_B_Pin GPIO_PIN_9
#define VPI_OE_B_GPIO_Port GPIOE
#define VPI_DM_Pin GPIO_PIN_10
#define VPI_DM_GPIO_Port GPIOE
#define SPI4_CS_Pin GPIO_PIN_11
#define SPI4_CS_GPIO_Port GPIOE
#define SPI4_SCLK_Pin GPIO_PIN_12
#define SPI4_SCLK_GPIO_Port GPIOE
#define SPI2_CS_Pin GPIO_PIN_12
#define SPI2_CS_GPIO_Port GPIOB
#define SPI2_SCLK_Pin GPIO_PIN_13
#define SPI2_SCLK_GPIO_Port GPIOB
#define LED_CH1_SNS_STM_Pin GPIO_PIN_8
#define LED_CH1_SNS_STM_GPIO_Port GPIOD
#define LED_CH2_SNS_STM_Pin GPIO_PIN_9
#define LED_CH2_SNS_STM_GPIO_Port GPIOD
#define LED_CH3_SNS_STM_Pin GPIO_PIN_10
#define LED_CH3_SNS_STM_GPIO_Port GPIOD
#define LED_CH4_SNS_STM_Pin GPIO_PIN_11
#define LED_CH4_SNS_STM_GPIO_Port GPIOD
#define LED_CH5_SNS_STM_Pin GPIO_PIN_12
#define LED_CH5_SNS_STM_GPIO_Port GPIOD
#define LED_CH6_SNS_STM_Pin GPIO_PIN_13
#define LED_CH6_SNS_STM_GPIO_Port GPIOD
#define LED_CH7_SNS_STM_Pin GPIO_PIN_14
#define LED_CH7_SNS_STM_GPIO_Port GPIOD
#define LED_CH8_SNS_STM_Pin GPIO_PIN_15
#define LED_CH8_SNS_STM_GPIO_Port GPIOD
#define SPI6_CS_Pin GPIO_PIN_8
#define SPI6_CS_GPIO_Port GPIOG
#define USB_DM_Pin GPIO_PIN_11
#define USB_DM_GPIO_Port GPIOA
#define USB_DP_Pin GPIO_PIN_12
#define USB_DP_GPIO_Port GPIOA
#define JTAG_TMS_Pin GPIO_PIN_13
#define JTAG_TMS_GPIO_Port GPIOA
#define JTAG_TCK_Pin GPIO_PIN_14
#define JTAG_TCK_GPIO_Port GPIOA
#define JTAG_TDI_Pin GPIO_PIN_15
#define JTAG_TDI_GPIO_Port GPIOA
#define LED_USER_STM_Pin GPIO_PIN_9
#define LED_USER_STM_GPIO_Port GPIOG
#define BCI_RST_Pin GPIO_PIN_10
#define BCI_RST_GPIO_Port GPIOG
#define BCI_DRDY_Pin GPIO_PIN_11
#define BCI_DRDY_GPIO_Port GPIOG
#define SPI6_SCLK_Pin GPIO_PIN_13
#define SPI6_SCLK_GPIO_Port GPIOG
#define JTAG_TDO_Pin GPIO_PIN_3
#define JTAG_TDO_GPIO_Port GPIOB
#define JTAG_NRST_Pin GPIO_PIN_4
#define JTAG_NRST_GPIO_Port GPIOB
#define IrDA_ENABLE_Pin GPIO_PIN_4
#define IrDA_ENABLE_GPIO_Port GPIOI
#define IrDA_BAUD2_Pin GPIO_PIN_5
#define IrDA_BAUD2_GPIO_Port GPIOI
#define IrDA_RESET_Pin GPIO_PIN_6
#define IrDA_RESET_GPIO_Port GPIOI
#define IrDA_MODE_Pin GPIO_PIN_7
#define IrDA_MODE_GPIO_Port GPIOI

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

/**
  * @}
  */ 

/**
  * @}
*/ 

#endif /* __MAIN_H */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

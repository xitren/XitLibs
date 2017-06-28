
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ExtFunctions.h"
#include "Handler.h"
#include "ImageVisualise.h"

#include "usart.h"
#include "ads1299.h"

#define TXTIMEOUT 10
#ifdef EXTMEMSERVER
    #define PORT_BACK 5683
#else        
    #define PORT_BACK 5683
#endif
#define PORT 5683
#define NUM_BUFFER 20

/* Private variables ---------------------------------------------------------*/
/*============================================================================*/

/* Private constants ---------------------------------------------------------*/
/*============================================================================*/

/* Private function prototypes -----------------------------------------------*/
int TransferDMA(const uint8_t *data, const uint32_t datalen);
int TransferUDP(const uint8_t *data, const uint32_t datalen,
        const char* address, const uint32_t port);
int TransferBroadbandUDP(const uint8_t *data, const uint32_t datalen,
        const uint32_t port);
void SetLeds(uint8_t q_green,uint8_t q_red,uint8_t q_blue);
/*============================================================================*/

/* Functions declaration -----------------------------------------------------*/
inline void UserProtocolHandler(void) {
    ProtocolHandler();
    return;
}

static uint32_t power_array[NUM_BUFFER];
uint32_t max_power = 0;

uint8_t find_power(int32_t* in_power)
{
    int32_t i;
    uint32_t result_power;
    
    result_power = 0;
    
    for( i = 0; i < ReadMem(REG_EEG_PocketSize); i++ )
    {
        /* For mean */
        result_power = result_power + abs(in_power[1+i*BUFFER_SAMPLE_SIZE])/ReadMem(REG_EEG_PocketSize);
    }    
    return (uint8_t)(result_power >> 24);
}

inline void UserOperationHandler(void) {    int j, k = 0, l = 0,m;
   char buffer[STRING_SIZE];
    uint8_t val_temp;
    uint8_t* rvars;
    uint8_t vals1[17] =
    {
        ReadMem(REG_ADC_REG1),//REG_ADS_CONFIG1
        ReadMem(REG_ADC_REG2),//REG_ADS_CONFIG2
        ReadMem(REG_ADC_REG3),//REG_ADS_CONFIG3
        ReadMem(REG_ADC_REG4),//REG_ADS_LOFF
       
        ReadMem(REG_ADC_REG15),//REG_ADS_CH1SET
        ReadMem(REG_ADC_REG16),//REG_ADS_CH2SET
        ReadMem(REG_ADC_REG17),//REG_ADS_CH3SET
        ReadMem(REG_ADC_REG18),//REG_ADS_CH4SET
        ReadMem(REG_ADC_REG19),//REG_ADS_CH5SET
        ReadMem(REG_ADC_REG20),//REG_ADS_CH6SET
        ReadMem(REG_ADC_REG21),//REG_ADS_CH7SET
        ReadMem(REG_ADC_REG22),//REG_ADS_CH8SET
        
        ReadMem(REG_ADC_REG5),//REG_ADS_BIAS_SENSP 
        ReadMem(REG_ADC_REG6),//REG_ADS_BIAS_SENSN
        ReadMem(REG_ADC_REG7),//REG_ADS_LOFF_SENSP
        ReadMem(REG_ADC_REG8),//REG_ADS_LOFF_SENSN
        ReadMem(REG_ADC_REG9) //REG_ADS_LOFF_FLIP
    };
    uint8_t vals2[4] =
    {
        ReadMem(REG_ADC_REG10),//REG_ADS_GPIO
        ReadMem(REG_ADC_REG11),//REG_ADS_MISC1
        ReadMem(REG_ADC_REG12),//REG_ADS_MISC2
        ReadMem(REG_ADC_REG13) //REG_ADS_CONFIG4
    };
    uint8_t vals3[2] = {HIGH_RES_250_SPS, 0xD0};
    uint8_t vals4[8] = {0x05, 0x05, 0x05, 0x05,
                            0x05, 0x05, 0x05, 0x05};

    #ifdef PLATFORM_LINUX
        //VideoFrameHandler();
    #endif
    
    if( ReadMem(REG_ADC_REG14) > 0 )
    {
        m = sprintf((char*)buffer,"STOP\n");
        HAL_UART_Transmit(&huart1, (uint8_t *) buffer, m, 1000);
        HAL_NVIC_DisableIRQ(EXTI15_10_IRQn);
        ads1299_send_command(ADS_STOP);
        switch( ReadMem(REG_ADC_REG14) )
        {
            case 2:
                ads1299_reset();
                m = sprintf((char*)buffer,"Case 2\n");
                HAL_UART_Transmit(&huart1, (uint8_t *) buffer, m, 1000);
                ads1299_wreg(CONFIG1, vals3, 2); 
                ads1299_wreg(CH1SET, vals4, 8);
                rvars = ads1299_rreg(ID,24);
                while ((rvars[1] != vals3[0]) 
                        || (rvars[2] != vals3[1])){
                    m = sprintf((char*)buffer,"ERR1\n");
                    HAL_UART_Transmit(&huart1, (uint8_t *) buffer, m, 1000);
                    ads1299_wreg(CONFIG1, vals3, 2); 
                    ads1299_wreg(CH1SET, vals4, 8);
                    rvars = ads1299_rreg(ID,24);
                }
                EEGRecorderInit(1, 250);
                break;
            case 3:
                ads1299_reset();
                m = sprintf((char*)buffer,"Case 3\n");
                HAL_UART_Transmit(&huart1, (uint8_t *) buffer, m, 1000);
                EEGRecorderInit(3, 250);
                break;
            default: 
                ads1299_reset();
                m = sprintf((char*)buffer,"Case !2 & !3\n");
                HAL_UART_Transmit(&huart1, (uint8_t *) buffer, m, 1000);
                ads1299_wreg(CONFIG1, vals1, 17);
                rvars = ads1299_rreg(CONFIG1, 17);
//                while( ads1299_check(rvars, vals1, 17) != 0 )
//                {
                    m = sprintf((char*)buffer,"ERR1\n");
                    HAL_UART_Transmit(&huart1, (uint8_t *) buffer, m, 1000);
                    ads1299_wreg(CONFIG1, vals1, 17);
                    rvars = ads1299_rreg(CONFIG1, 17);
//                }
//                while( ads1299_check(rvars, vals1, 4) != 0 )
//                {
                    m = sprintf((char*)buffer,"ERR2\n");
                    HAL_UART_Transmit(&huart1, (uint8_t *) buffer, m, 1000);
                    ads1299_wreg(GPIO, vals1, 4);
                    rvars = ads1299_rreg(GPIO, 4);
//                }
                EEGRecorderInit(1, 250);
                break;
        }
        WriteMem(REG_ADC_REG14,0);
        m = sprintf((char*)buffer,"START\n");
        HAL_UART_Transmit(&huart1, (uint8_t *) buffer, m, 1000);
        ads1299_send_command(ADS_RDATAC);
        ads1299_send_command(ADS_START);
        HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
        WriteMem(REG_EEG_Auto_Band,1);
    }
    
    l = GetCnt();
    if ((ReadMem(REG_EEG_PocketSize) <= l) && (ReadMem(REG_EEG_Auto_Band) == 1))
    {
        l = GetDataReadyCnt((int32_t)ReadMem(REG_EEG_PocketSize), (int32_t*) scratch_raw);
        if (l > 0)
        {
            if ( (k = Packetize((uint8_t*) scratch_raw, l * 4, BUFFER_SAMPLE_SIZE * ReadMem(REG_EEG_PocketSize) + 22)) > 0 )
            {
                TransferDMA((uint8_t*) scratch_raw, k);
            }
        }
    }
    
//    if( (ReadMem(REG_EEG_PocketSize) <= l) && (ReadMem(REG_EEG_Auto_Band) == 2) )
//    {
//        //WriteMem(REG_EEG_PocketSize,256);
//        l = GetDataReadyCnt( (int32_t)ReadMem(REG_EEG_PocketSize), (int32_t*) scratch_raw );
//        if (l > 0)
//        {
//            val_temp = find_power( (int32_t*)scratch_raw );
//            TransferBand((uint8_t*) &val_temp, 1);
//        }
//    }

    //OperationHandler();
    return;
}

inline int32_t ADC_read_data_c(){
    int32_t* data = ads1299_read_data();
    WriteMem(REG_ADC_CH1,data[0]);
    WriteMem(REG_ADC_CH2,data[1]);
    WriteMem(REG_ADC_CH3,data[2]);
    WriteMem(REG_ADC_CH4,data[3]);
    WriteMem(REG_ADC_CH5,data[4]);
    WriteMem(REG_ADC_CH6,data[5]);
    WriteMem(REG_ADC_CH7,data[6]);
    WriteMem(REG_ADC_CH8,data[7]);
    AddSample();
    return 0;
}

int TransferDMA(const uint8_t *data, const uint32_t datalen) {
#ifndef CPU
    HAL_UART_Transmit_IT(&huart1, (uint8_t *) data, datalen);
#endif
    return 0;
}

int TransferUDP(const uint8_t *data, const uint32_t datalen,
        const char* address /* = "192.168.1.255" */,
        const uint32_t port /* = 5683 */) {
    return 0;
}

int TransferBroadbandUDP(const uint8_t *data, const uint32_t datalen,
        const uint32_t port /* = 5683 */) {
    return 0;
}

void SetLeds(uint8_t q_green,uint8_t q_red,uint8_t q_blue)
{
    #ifndef CPU
        if (q_green)
          HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, GPIO_PIN_SET);
        else
          HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, GPIO_PIN_RESET);
        if (q_red)
          HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
        else
          HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
        if (q_blue)
          HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, GPIO_PIN_SET);
        else
          HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, GPIO_PIN_RESET);
    #endif
    return;
}

/*============================================================================*/
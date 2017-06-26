#include "ads1299.h"
#include "main.h"
#include "spi.h"
#include "../XitLib/ConfigMem.h"
#include "usart.h"
#include <stm32f4xx_hal.h>
#include "stm32f4xx_it.h"

uint8_t register_value[30];

inline uint16_t spi_xfer(uint16_t data)
{
    uint8_t rd;
    HAL_SPI_TransmitReceive(&hspi6, (uint8_t*) &data, (uint8_t*) &rd, 1, 10);
    return(uint16_t)rd;
}
void ads1299_wreg(uint32_t reg, uint8_t* val, uint16_t num)
{
    int i = 0;
    ads1299_send_command(ADS_SDATAC);
    
    CS_DOWN();
        
    reg |= ADS_WREG;
    spi_xfer(reg);
    spi_xfer(num);
    for( i = 0; i < num; i++)
    {
        spi_xfer(val[i]);
    }
    
    CS_UP();
        
    ads1299_send_command(ADS_RDATAC);
}

uint8_t* ads1299_rreg(uint32_t reg, uint16_t num)
{
    int i = 0;
    
    ads1299_send_command(ADS_SDATAC);
    //ads1299_send_command(ADS_SDATAC);
        
    CS_DOWN();
    
    reg |= ADS_RREG; // convert to read address
    spi_xfer(reg); // send location to comm register
    spi_xfer(num);
    for (i = 0 ; i < num;i++)
    {
        register_value[i] = spi_xfer(0x00);
    }
    
    CS_UP();
    
    ads1299_send_command(ADS_RDATAC);
    
    return(register_value);
}

void ads1299_send_command(uint32_t command)
{
    HAL_Delay(10);
    
    CS_DOWN();
        
    spi_xfer(command);
    
    CS_UP();
    
    HAL_Delay(10);
}

int32_t* ads1299_read_data(void)
{
    static uint32_t status_data;
    static int32_t channel_data[8];
    
    CS_DOWN();
    
    status_data = (spi_xfer(0xFF) << 16);
    status_data |= (spi_xfer(0xFF) << 8);
    status_data |= spi_xfer(0xFF);
    channel_data[0] = ads1299_channel_convert();
    channel_data[1] = ads1299_channel_convert();
    channel_data[2] = ads1299_channel_convert();
    channel_data[3] = ads1299_channel_convert();
    channel_data[4] = ads1299_channel_convert();
    channel_data[5] = ads1299_channel_convert();
    channel_data[6] = ads1299_channel_convert();
    channel_data[7] = ads1299_channel_convert();
    
    CS_UP();

    return(channel_data);
}

inline int32_t ads1299_channel_convert(void)
{
    static union data
    {
       unsigned char char_[4];
       int32_t int_;
    } ch_data;
    
    ch_data.char_[3] = (unsigned char)spi_xfer(0xFF);
    ch_data.char_[2] = (unsigned char)spi_xfer(0xFF);
    ch_data.char_[1] = (unsigned char)spi_xfer(0xFF);
    if (ch_data.char_[3] > 0x7F)
    {
        ch_data.char_[0] = 0xFF;
    }
    else
    {
        ch_data.char_[0] = 0x00;
    }
    
    return(ch_data.int_);
}

int ads1299_setup(void)
{
    int i = 0;
    
    uint8_t* rvars;
    
    ads1299_reset();
    
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
    
    ads1299_wreg(CONFIG1, vals1, 17);
    rvars = ads1299_rreg(CONFIG1, 17);
    while( ads1299_check(rvars, vals1, 17) != 0 )
    {
        ads1299_wreg(CONFIG1, vals1, 17);
        rvars = ads1299_rreg(CONFIG1, 17);
    }
    
    ads1299_wreg(GPIO, vals2, 4);
    rvars = ads1299_rreg(GPIO, 4);
    while( ads1299_check(rvars, vals2, 4) != 0 )
    {
        ads1299_wreg(GPIO, vals2, 4);
        rvars = ads1299_rreg(GPIO, 4);
    }
    
    HAL_Delay(100);
        
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
    
    return(0);
}

int ads1299_check(uint8_t* read_vals, uint8_t* need_vals, uint16_t num)
{
    int i, l;
    char buffer[100];
    
    for(i = 0; i < num; i++)
    {
        if(read_vals[i] != need_vals[i])
        {
            l = sprintf( (char*)buffer, "Failed reg (%d og %d) %02X != %02X ", i, num, read_vals[i], need_vals[i] );
            HAL_UART_Transmit(&huart1, (uint8_t *) buffer, l, 1000);
            
            return(-1);
        }
    }
    return(0);
}

void ads1299_print(char *user_mesg, uint32_t *mesg )
{
    char buf[100];
    uint8_t length_buf = snprintf( buf, sizeof(buf), user_mesg, mesg );
    //HAL_UART_Transmit(&huart1, (uint8_t *) buf, length_buf, 1000);
}

void ads1299_reset(void)
{    
    /* Reset chip */
    HAL_GPIO_WritePin(GPIOG, BCI_RST_Pin, GPIO_PIN_RESET);
    HAL_Delay(100);
    HAL_GPIO_WritePin(GPIOG, BCI_RST_Pin, GPIO_PIN_SET);
    HAL_Delay(100);
}

void ads1299_read_regs(void)
{
    PRINT_MES("\r\n\rID: ");
    ads1299_rreg(ID,24);
}
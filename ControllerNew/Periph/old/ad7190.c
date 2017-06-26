#include "ad7190.h"
#include "spi.h"
#include "../XitLib/ConfigMem.h"

uint8_t ad_buffer[200];
uint8_t ad_id[8];

uint16_t spi_xfer(uint16_t data)
{
        uint8_t rd;
        HAL_SPI_TransmitReceive(&hspi5, (uint8_t*) &data, (uint8_t*) &rd, 1, 10);
	return rd;
}

void ad7190_wreg(uint32_t reg, uint32_t val)
{
        uint32_t data_length = 0;
     
        // determine data length
        switch (reg) {
            // 8 bit
            case ID_REG_FAST:
            case GPOCOM_REG_FAST:
                data_length = 1;
                break;
     
            // 24 bit
            case MODE_REG_FAST:
            case CONFIG_REG_FAST:
            case OFFSET_REG_FAST:
            case SCALE_REG_FAST:
                data_length = 3;
                break;
        }
     
        // send location to comm register
        spi_xfer(reg);
     
        // send the data
        if (data_length == 3) {
            spi_xfer((val & 0x00FF0000) >> 16);
            spi_xfer((val & 0x0000FF00) >> 8);
        }
        spi_xfer(val & 0x000000FF);
     
        return;
}
uint32_t ad7190_rreg(uint32_t reg)
{
        uint32_t data_length = 0;
        uint32_t register_value = 0;
        uint32_t rx_data[3] = {0, 0, 0};

        // determine data length
        switch (reg) {
            // 8 bit result
            case COM_STAT_REG_FAST:
            case ID_REG_FAST:
            case GPOCOM_REG_FAST:
                data_length = 1;
                break;
     
            // 24 bit result
            case MODE_REG_FAST:
            case CONFIG_REG_FAST:
            case DATA_REG_FAST:
            case OFFSET_REG_FAST:
            case SCALE_REG_FAST:
                data_length = 3;
                break;
        }

        // convert write address to read address
        reg |= 0x40;
     
        // send location to comm register
        spi_xfer(reg);
    
        // get the data
        if (data_length == 3) {
            rx_data[0] = spi_xfer(0xFF);
            rx_data[0] <<= 16;
            rx_data[1] = spi_xfer(0xFF);
            rx_data[1] <<= 8;
            rx_data[2] = spi_xfer(0xFF);
            register_value = 0x00000000 | rx_data[2] | rx_data[1] | rx_data[0];
        } else {
            register_value = spi_xfer(0xFF);
        }
        return (register_value);
}
uint32_t ad7190_read_data(void)
{
        uint32_t rx_data[4] = {0, 0, 0, 0};
     
        // send location to comm register
        // shouldn't have to use this for continuous read
        spi_xfer(DATA_REG_FAST | 0x40);
     
        // get the data
        rx_data[0] = spi_xfer(0xFF);   // data
        rx_data[1] = spi_xfer(0xFF);   // data
        rx_data[2] = spi_xfer(0xFF);   // data
        rx_data[3] = spi_xfer(0xFF);   // status
     
        rx_data[0] <<= 24;
        rx_data[1] <<= 16;
        rx_data[2] <<= 8;
     
        return (rx_data[3] | rx_data[2] | rx_data[1] | rx_data[0]);
}
void ad7190_reset(void)
{
        int i = 0;
        for (i = 0; i < 10; i++) {
              spi_xfer(0xFF);
        }
}
int MCP23S17_regs(void)
{
        HAL_Delay(500);
    uint8_t MCP_id[8];
        HAL_GPIO_WritePin(GPIOF,GPIO_PIN_6,GPIO_PIN_RESET); //CS
        //Change direction
        spi_xfer(0x41);
        spi_xfer(0x00);
        MCP_id[0] = spi_xfer(0x00);
        HAL_GPIO_WritePin(GPIOF,GPIO_PIN_6,GPIO_PIN_SET); //CS
        HAL_GPIO_WritePin(GPIOF,GPIO_PIN_6,GPIO_PIN_RESET); //CS
        //Change direction
        spi_xfer(0x41);
        spi_xfer(0x01);
        MCP_id[1] = spi_xfer(0x00);
        HAL_GPIO_WritePin(GPIOF,GPIO_PIN_6,GPIO_PIN_SET); //CS
        HAL_GPIO_WritePin(GPIOF,GPIO_PIN_6,GPIO_PIN_RESET); //CS
        //Change direction
        spi_xfer(0x41);
        spi_xfer(0x02);
        MCP_id[2] = spi_xfer(0x00);
        HAL_GPIO_WritePin(GPIOF,GPIO_PIN_6,GPIO_PIN_SET); //CS
        HAL_GPIO_WritePin(GPIOF,GPIO_PIN_6,GPIO_PIN_RESET); //CS
        //Change direction
        spi_xfer(0x41);
        spi_xfer(0x03);
        MCP_id[3] = spi_xfer(0x00);
        HAL_GPIO_WritePin(GPIOF,GPIO_PIN_6,GPIO_PIN_SET); //CS
        HAL_GPIO_WritePin(GPIOF,GPIO_PIN_6,GPIO_PIN_RESET); //CS
        //Change direction
        spi_xfer(0x41);
        spi_xfer(0x10);
        MCP_id[4] = spi_xfer(0x00);
        HAL_GPIO_WritePin(GPIOF,GPIO_PIN_6,GPIO_PIN_SET); //CS
        HAL_GPIO_WritePin(GPIOF,GPIO_PIN_6,GPIO_PIN_RESET); //CS
        //Change direction
        spi_xfer(0x41);
        spi_xfer(0x13);
        MCP_id[5] = spi_xfer(0x00);
        HAL_GPIO_WritePin(GPIOF,GPIO_PIN_6,GPIO_PIN_SET); //CS
        sprintf((char*)ad_buffer,
         "reg0h %X,reg1h %X,reg2h %X,reg3h %X,reg10h %X,reg13h %X.\r\n\r"
         ,MCP_id[0],MCP_id[1],MCP_id[2],MCP_id[3],MCP_id[4],MCP_id[5]);
        Transfer((uint8_t*)ad_buffer,strlen((char const *)ad_buffer),0);
        HAL_Delay(2000);
}

int ad7190_setup_all(void)
{
        int i = 0;
        HAL_GPIO_WritePin(GPIOC,GPIO_PIN_2,GPIO_PIN_RESET); //1
        HAL_GPIO_WritePin(GPIOC,GPIO_PIN_3,GPIO_PIN_RESET); //2
        HAL_GPIO_WritePin(GPIOH,GPIO_PIN_4,GPIO_PIN_RESET); //3
        HAL_GPIO_WritePin(GPIOH,GPIO_PIN_5,GPIO_PIN_RESET); //4
        
        HAL_GPIO_WritePin(GPIOF,GPIO_PIN_6,GPIO_PIN_SET); //CS
        
        //INIT
//        SetCStatLedsUnderPWM(0,0,100);
//        HAL_Delay(1000);
        //HAL_GPIO_WritePin(GPIOF,GPIO_PIN_6,GPIO_PIN_RESET); //CS
//        MCP23S17_regs();    
//        HAL_GPIO_WritePin(GPIOF,GPIO_PIN_6,GPIO_PIN_RESET); //CS
//        //Change direction
//        spi_xfer(0x40);
//        spi_xfer(0x01);
//        spi_xfer(0x00);
//        HAL_GPIO_WritePin(GPIOF,GPIO_PIN_6,GPIO_PIN_SET); //CS
//        MCP23S17_regs();    
        uint32_t CONFIGURATOR;
        uint32_t CONFIGURATOR_r;
        uint32_t CONF_FRQ;
        uint32_t CONF_GPIO;  
        CONFIGURATOR = ReadMem(REG_AD_CONF);
        CONF_FRQ = ReadMem(REG_AD_MODE);
        CONF_GPIO = ReadMem(REG_AD_GPIO);
        
        choose_ad(0x08);
        ad7190_wreg(CONFIG_REG_FAST, CONFIGURATOR);
        ad7190_wreg(GPOCOM_REG_FAST, CONF_GPIO); //
        ad7190_wreg(MODE_REG_FAST, CONF_FRQ); 
//        sprintf((char*)ad_buffer,
//                            "RLD device id %X.\r\n\r",ad7190_rreg(ID_REG_FAST));
//        Transfer((uint8_t*)ad_buffer,strlen((char const *)ad_buffer),0);
        choose_ad(0x10);
        
        HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_RESET); //RED
        for (i = 0; i < 8; i++) 
        {
            choose_ad(i); 
            ad_id[i] = ad7190_rreg(ID_REG_FAST);    
            choose_ad(0x10);
        }    
//        sprintf((char*)ad_buffer,
//         "D1_ID %X,D2_ID %X,D3_ID %X,D4_ID %X,D5_ID %X,D6_ID %X,D7_ID %X,D8_ID %X.\r\n\r"
//         ,ad_id[0],ad_id[1],ad_id[2],ad_id[3],ad_id[4],ad_id[5],ad_id[6],ad_id[7]);
//        Transfer((uint8_t*)ad_buffer,strlen((char const *)ad_buffer),0);
        CONF_GPIO = ReadMem(REG_AD_GPIO2);
        for (i = 0; i < 8; i++) 
        {
            if ((ad_id[i] != 0x00) && (ad_id[i] != 0xFF))
            {
                choose_ad(i);        
                ad7190_reset();    
                HAL_Delay(200);
                ad7190_wreg(CONFIG_REG_FAST, CONFIGURATOR);
                CONFIGURATOR_r = ad7190_rreg(CONFIG_REG_FAST);
                if (CONFIGURATOR_r != CONFIGURATOR)
                {
//                    sprintf((char*)ad_buffer,
//                                        "%d device cfg check failed.\r\n\r",i);
//                    Transfer((uint8_t*)ad_buffer,strlen((char const *)ad_buffer),0);
                }
                ad7190_wreg(GPOCOM_REG_FAST, CONF_GPIO); //
                ad7190_wreg(MODE_REG_FAST, CONF_FRQ); 
                choose_ad(0x10);
            }
        }    
        
        HAL_GPIO_WritePin(GPIOF,GPIO_PIN_6,GPIO_PIN_SET); //CS
        //INIT OVER
}
int ad7190_read_data_c(uint8_t dec)
{
    uint32_t temp;
    choose_ad(dec);
    temp = ad7190_read_data();
    choose_ad(0x10);
    return (int32_t)((temp & 0xFFFFFF00) + 2147483648);
}

void choose_ad(uint8_t dec)
{
    //Change CS
    HAL_GPIO_WritePin(GPIOF,GPIO_PIN_6,GPIO_PIN_RESET); //CS
//    spi_xfer(0x40);
//    spi_xfer(0x13);
    switch (dec)
    {
        case 0x00:
//            spi_xfer(0x10);
            HAL_GPIO_WritePin(GPIOH,GPIO_PIN_5,GPIO_PIN_RESET); //1
            HAL_GPIO_WritePin(GPIOH,GPIO_PIN_4,GPIO_PIN_RESET); //2
            HAL_GPIO_WritePin(GPIOC,GPIO_PIN_3,GPIO_PIN_RESET); //3
            HAL_GPIO_WritePin(GPIOC,GPIO_PIN_2,GPIO_PIN_RESET); //4
            break;
        case 0x01:
//            spi_xfer(0x11);
            HAL_GPIO_WritePin(GPIOH,GPIO_PIN_5,GPIO_PIN_SET); //1
            HAL_GPIO_WritePin(GPIOH,GPIO_PIN_4,GPIO_PIN_RESET); //2
            HAL_GPIO_WritePin(GPIOC,GPIO_PIN_3,GPIO_PIN_RESET); //3
            HAL_GPIO_WritePin(GPIOC,GPIO_PIN_2,GPIO_PIN_RESET); //4
            break;
        case 0x02:
//            spi_xfer(0x12);
            HAL_GPIO_WritePin(GPIOH,GPIO_PIN_5,GPIO_PIN_RESET); //1
            HAL_GPIO_WritePin(GPIOH,GPIO_PIN_4,GPIO_PIN_SET); //2
            HAL_GPIO_WritePin(GPIOC,GPIO_PIN_3,GPIO_PIN_RESET); //3
            HAL_GPIO_WritePin(GPIOC,GPIO_PIN_2,GPIO_PIN_RESET); //4
            break;
        case 0x03:
//            spi_xfer(0x13);
            HAL_GPIO_WritePin(GPIOH,GPIO_PIN_5,GPIO_PIN_SET); //1
            HAL_GPIO_WritePin(GPIOH,GPIO_PIN_4,GPIO_PIN_SET); //2
            HAL_GPIO_WritePin(GPIOC,GPIO_PIN_3,GPIO_PIN_RESET); //3
            HAL_GPIO_WritePin(GPIOC,GPIO_PIN_2,GPIO_PIN_RESET); //4
            break;
        case 0x04:
//            spi_xfer(0x14);
            HAL_GPIO_WritePin(GPIOH,GPIO_PIN_5,GPIO_PIN_RESET); //1
            HAL_GPIO_WritePin(GPIOH,GPIO_PIN_4,GPIO_PIN_RESET); //2
            HAL_GPIO_WritePin(GPIOC,GPIO_PIN_3,GPIO_PIN_SET); //3
            HAL_GPIO_WritePin(GPIOC,GPIO_PIN_2,GPIO_PIN_RESET); //4
            break;
        case 0x05:
//            spi_xfer(0x15);
            HAL_GPIO_WritePin(GPIOH,GPIO_PIN_5,GPIO_PIN_SET); //1
            HAL_GPIO_WritePin(GPIOH,GPIO_PIN_4,GPIO_PIN_RESET); //2
            HAL_GPIO_WritePin(GPIOC,GPIO_PIN_3,GPIO_PIN_SET); //3
            HAL_GPIO_WritePin(GPIOC,GPIO_PIN_2,GPIO_PIN_RESET); //4
            break;
        case 0x06:
//            spi_xfer(0x16);
            HAL_GPIO_WritePin(GPIOH,GPIO_PIN_5,GPIO_PIN_RESET); //1
            HAL_GPIO_WritePin(GPIOH,GPIO_PIN_4,GPIO_PIN_SET); //2
            HAL_GPIO_WritePin(GPIOC,GPIO_PIN_3,GPIO_PIN_SET); //3
            HAL_GPIO_WritePin(GPIOC,GPIO_PIN_2,GPIO_PIN_RESET); //4
            break;
        case 0x07:
//            spi_xfer(0x17);
            HAL_GPIO_WritePin(GPIOH,GPIO_PIN_5,GPIO_PIN_SET); //1
            HAL_GPIO_WritePin(GPIOH,GPIO_PIN_4,GPIO_PIN_SET); //2
            HAL_GPIO_WritePin(GPIOC,GPIO_PIN_3,GPIO_PIN_SET); //3
            HAL_GPIO_WritePin(GPIOC,GPIO_PIN_2,GPIO_PIN_RESET); //4
            break;
        case 0x08:
//            spi_xfer(0x18);
            HAL_GPIO_WritePin(GPIOH,GPIO_PIN_5,GPIO_PIN_RESET); //1
            HAL_GPIO_WritePin(GPIOH,GPIO_PIN_4,GPIO_PIN_RESET); //2
            HAL_GPIO_WritePin(GPIOC,GPIO_PIN_3,GPIO_PIN_RESET); //3
            HAL_GPIO_WritePin(GPIOC,GPIO_PIN_2,GPIO_PIN_SET); //4
            break;
        case 0x09:
//            spi_xfer(0x19);
            HAL_GPIO_WritePin(GPIOH,GPIO_PIN_5,GPIO_PIN_SET); //1
            HAL_GPIO_WritePin(GPIOH,GPIO_PIN_4,GPIO_PIN_RESET); //2
            HAL_GPIO_WritePin(GPIOC,GPIO_PIN_3,GPIO_PIN_RESET); //3
            HAL_GPIO_WritePin(GPIOC,GPIO_PIN_2,GPIO_PIN_SET); //4
            break;
        default:
//            spi_xfer(0x2F);
            HAL_GPIO_WritePin(GPIOH,GPIO_PIN_5,GPIO_PIN_SET); //1
            HAL_GPIO_WritePin(GPIOH,GPIO_PIN_4,GPIO_PIN_SET); //2
            HAL_GPIO_WritePin(GPIOC,GPIO_PIN_3,GPIO_PIN_SET); //3
            HAL_GPIO_WritePin(GPIOC,GPIO_PIN_2,GPIO_PIN_SET); //4
            HAL_GPIO_WritePin(GPIOF,GPIO_PIN_6,GPIO_PIN_SET); //CS
            break;
    }
//        MCP23S17_regs();    
}
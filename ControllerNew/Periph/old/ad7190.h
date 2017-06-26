#ifndef AD7190_H
#define AD7190_H

#include "../../XitLib/xitlibtypes.h"

#define COM_STAT_REG_FAST      0x00
#define MODE_REG_FAST        0x08
#define CONFIG_REG_FAST      0x10
#define DATA_REG_FAST        0x18
#define ID_REG_FAST          0x20
#define GPOCOM_REG_FAST      0x28
#define OFFSET_REG_FAST      0x30
#define SCALE_REG_FAST   0x38

extern uint8_t ad_id[8];

#ifdef __cplusplus
namespace AD7190 {
#endif

	enum COM_REG {
		// Communicative stat
		COM_WRITE_NOT_EN = 0x80,
		COM_COM_READ_BIT = 0x40,//040
		COM_CONTINUOUS_READ = 0x04,
                
		COM_REG_CONST = 0x00
	};
        
	enum STATUS_REG {
		// Communicative stat
		STATUS_DATA_RDY = 0x80,
		STATUS_ERROR_STATUS = 0x40,
		STATUS_NO_REF = 0x20,
		STATUS_PARITY = 0x10,
		STATUS_CHANNEL = 0x07,
                
		STATUS_REG_CONST = 0x00
	};
        
	enum MODE_REG {
		// Modes
		MODE_OPERATING = 0xE00000,
		MODE_STAT_TRANSMIT_EN = 0x100000,
		MODE_CLOCK = 0x0C0000,
		MODE_SINC3 = 0x008000,
		MODE_EN_PARITY = 0x002000,
		MODE_SINGLE = 0x000800,
		MODE_REJ60 = 0x000400,
		MODE_FILTER_OUTPUT_DATA_RATE = 0x0001FF,
                
		MODE_REG_CONST = 0x000000
	};
        
	enum OPERATING_MODES {
		// Operating
		OPERATING_CONTINUOUS = 0X00,
		OPERATING_SINGLE = 0X01,
		OPERATING_IDLE = 0X02,
		OPERATING_PWR_DOWN = 0X03,
		OPERATING_INTERNAL_ZERO = 0X04,
		OPERATING_INTERNAL_FULLSCALE = 0X05,
		OPERATING_SYSTEM_ZERO = 0X06,
		OPERATING_SYSTEM_FULLSCALE = 0X07
	};
        
	enum CONFIG_REG {
		// Modes
		CONFIG_CHOP = 0x800000,
		CONFIG_REFSEL = 0x100000,
		CONFIG_CHANNEL_SELECT = 0x00FF00,
		CONFIG_BURN = 0x000080,
		CONFIG_REFDET = 0x000040,
		CONFIG_BUF = 0x000010,
		CONFIG_UNIPOLAR = 0x000008,
		CONFIG_GAIN = 0x000007,
                
		CONFIG_REG_CONST = 0x000000
	};
        
	enum GAIN_MODE {
		// Modes
		AD_GAIN_1 = 0x00,
		AD_GAIN_8 = 0x03,
		AD_AD_GAIN_16 = 0x04,
		AD_GAIN_32 = 0x05,
		AD_GAIN_64 = 0x06,
		AD_GAIN_128 = 0x07
	};
        
	enum CHANNEL_MODE {
		// Modes
		CHANNEL_CH0 = 0x01,
		CHANNEL_CH1 = 0x02,
		CHANNEL_CH2 = 0x04,
		CHANNEL_CH3 = 0x08,
		CHANNEL_CH4 = 0x10,
		CHANNEL_CH5 = 0x20,
		CHANNEL_CH6 = 0x40,
		CHANNEL_CH7 = 0x80
	};
        
	enum GPOCON_REG {
		// Modes
		GPOCON_BPDSW = 0x40,
		GPOCON_GP32EN = 0x20,
		GPOCON_GP10EN = 0x10,
		GPOCON_P3DAT = 0x08,
		GPOCON_P2DAT = 0x04,
		GPOCON_P1DAT = 0x02,
		GPOCON_P0DAT = 0x01,
                
		GPOCON_REG_CONST = 0x00
	};        

	enum ad_reg {
                //Communications register during write, status register during read (8 bit)
		COM_STAT_REG = 0x00,
                
                //Mode register (24 bit)
		MODE_REG = 0x01,
                
                //Configuration register (24 bit)
		CONFIG_REG = 0x02,
                
                //Data register / data register + status inforation (24 bit/32 bit)
		DATA_REG = 0x03,
                
                //ID register (8 bit)
		ID_REG = 0x04,
                
                //GPOCOM register (8 bit)
		GPOCOM_REG = 0x05,
                
                //Offset register (24 bit)
		OFFSET_REG = 0x06,
                
                //Full-scale register (24 bit)
		SCALE_REG = 0x07,
	};

uint16_t spi_xfer(uint16_t data);
void ad7190_wreg(uint32_t reg, uint32_t val);
uint32_t ad7190_rreg(uint32_t reg);
uint32_t ad7190_read_data(void);
void ad7190_reset(void);
int ad7190_setup_all(void);
int ad7190_read_data_c(uint8_t dec);
void choose_ad(uint8_t dec);

#ifdef __cplusplus
}
#endif
#endif /* namespace AD7190 */
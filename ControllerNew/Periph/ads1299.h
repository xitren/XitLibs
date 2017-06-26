#ifndef ADS1299_H
#define ADS1299_H

#define TEST

#include "../../XitLib/xitlibtypes.h"

#define CS_UP() HAL_GPIO_WritePin(GPIOG, SPI6_CS_Pin, GPIO_PIN_SET)
#define CS_DOWN() HAL_GPIO_WritePin(GPIOG, SPI6_CS_Pin, GPIO_PIN_RESET)

#ifdef __cplusplus
namespace ADS1299 {
#endif

enum spi_command
{
    // system commands
    ADS_WAKEUP = 0x02,
    ADS_STANDBY = 0x04,
    ADS_RESET = 0x06,
    ADS_START = 0x08,
    ADS_STOP = 0x0a,

    // read commands
    ADS_RDATAC = 0x10,
    ADS_SDATAC = 0x11,
    ADS_RDATA = 0x12,

    // register commands
    ADS_RREG = 0x20,
    ADS_WREG = 0x40
};

enum reg {
    // device settings
    ID = 0x00,

    // global settings
    CONFIG1 = 0x01,
    CONFIG2 = 0x02,
    CONFIG3 = 0x03,
    LOFF = 0x04,

    // channel specific settings
    CHnSET = 0x04,
    CH1SET = CHnSET + 1,
    CH2SET = CHnSET + 2,
    CH3SET = CHnSET + 3,
    CH4SET = CHnSET + 4,
    CH5SET = CHnSET + 5,
    CH6SET = CHnSET + 6,
    CH7SET = CHnSET + 7,
    CH8SET = CHnSET + 8,
    BIAS_SENSP = 0x0d,
    BIAS_SENSN = 0x0e,
    LOFF_SENSP = 0x0f,
    LOFF_SENSN = 0x10,
    LOFF_FLIP = 0x11,

    // lead off status
    LOFF_STATP = 0x12,
    LOFF_STATN = 0x13,

    // other
    GPIO = 0x14,
    MISC1 = 0x15,
    MISC2 = 0x16,
    CONFIG4 = 0x17,
};

enum ID_bits
{
    DEV_ID7 = 0x80,
    DEV_ID6 = 0x40,
    DEV_ID5 = 0x20,
    DEV_ID3 = 0x08,
    DEV_ID2 = 0x04,
    DEV_ID1 = 0x02,
    DEV_ID0 = 0x01,

    ID_const = 0x10,
    ID_ADS1299 = (DEV_ID3 | DEV_ID2 | DEV_ID1),
};

enum CONFIG1_bits
{
    DAISY_EN = 0x40,
    CLK_EN = 0x20,
    DR2 = 0x04,
    DR1 = 0x02,
    DR0 = 0x01,

    CONFIG1_const = 0x90,
    HIGH_RES_16k_SPS = CONFIG1_const,
    HIGH_RES_8k_SPS = (CONFIG1_const | DR0),
    HIGH_RES_4k_SPS = (CONFIG1_const | DR1),
    HIGH_RES_2k_SPS = (CONFIG1_const | DR1 | DR0),
    HIGH_RES_1k_SPS = (CONFIG1_const | DR2),
    HIGH_RES_500_SPS = (CONFIG1_const | DR2 | DR0),
    HIGH_RES_250_SPS = (CONFIG1_const | DR2 | DR1),
};

enum CONFIG2_bits
{
    INT_CAL = 0x10,
    CAL_AMP0 = 0x04,
    CAL_FREQ1 = 0x02,
    CAL_FREQ0 = 0x01,

    CONFIG2_const = 0xC0,
    INT_TEST_SLOW = INT_CAL,
    INT_TEST_FAST = (INT_CAL | CAL_FREQ0),
    INT_TEST_DC = (INT_CAL | CAL_FREQ1 | CAL_FREQ0)
};

enum CONFIG3_bits
{
    PD_REFBUF = 0x80,
    BIAS_MEAS = 0x10,
    BIASREF_INT = 0x08,
    PD_BIAS = 0x04,
    BIAS_LOFF_SENS = 0x02,
    BIAS_STAT = 0x01,

    CONFIG3_const = 0x60
};

enum LOFF_bits
{
    COMP_TH2 = 0x80,
    COMP_TH1 = 0x40,
    COMP_TH0 = 0x20,
    VLEAD_OFF_EN = 0x10,
    ILEAD_OFF1 = 0x08,
    ILEAD_OFF0 = 0x04,
    FLEAD_OFF1 = 0x02,
    FLEAD_OFF0 = 0x01,

    LOFF_const = 0x00,

    COMP_TH_95 = 0x00,
    COMP_TH_92_5 = COMP_TH0,
    COMP_TH_90 = COMP_TH1,
    COMP_TH_87_5 = (COMP_TH1 | COMP_TH0),
    COMP_TH_85 = COMP_TH2,
    COMP_TH_80 = (COMP_TH2 | COMP_TH0),
    COMP_TH_75 = (COMP_TH2 | COMP_TH1),
    COMP_TH_70 = (COMP_TH2 | COMP_TH1 | COMP_TH0),

    ILEAD_OFF_6nA = 0x00,
    ILEAD_OFF_12nA = ILEAD_OFF0,
    ILEAD_OFF_18nA = ILEAD_OFF1,
    ILEAD_OFF_24nA = (ILEAD_OFF1 | ILEAD_OFF0),

    FLEAD_OFF_AC = FLEAD_OFF0,
    FLEAD_OFF_DC = (FLEAD_OFF1 | FLEAD_OFF0)
};

enum CHnSET_bits
{
    PDn = 0x80,
    SRB2 = 0x08,
    GAINn2 = 0x40,
    GAINn1 = 0x20,
    GAINn0 = 0x10,
    MUXn2 = 0x04,
    MUXn1 = 0x02,
    MUXn0 = 0x01,

    CHnSET_const = 0x00,

    GAIN_1X = 0x00,
    GAIN_2X = GAINn0,
    GAIN_3X = (GAINn1 | GAINn0),
    GAIN_4X = GAINn1,
    GAIN_6X = (GAINn1 | GAINn0),
    GAIN_8X = (GAINn2),
    GAIN_12X = (GAINn2 | GAINn0),
    GAIN_24X = (GAINn2 | GAINn1),

    ELECTRODE_INPUT = 0x00,
    SHORTED = MUXn0,
    CH_BIAS_MEAS = MUXn1,
    MVDD = (MUXn1 | MUXn0),
    TEMP = MUXn2,
    TEST_SIGNAL = (MUXn2 | MUXn0),
    BIAS_DRP = (MUXn2 | MUXn1),
    BIAS_DRN = (MUXn2 | MUXn1 | MUXn0)
};

enum CH1SET_bits
{
    PD_1 = 0x80,
    GAIN12 = 0x40,
    GAIN11 = 0x20,
    GAIN10 = 0x10,
    MUX12 = 0x04,
    MUX11 = 0x02,
    MUX10 = 0x01,

    CH1SET_const = 0x00
};

enum CH2SET_bits
{
    PD_2 = 0x80,
    GAIN22 = 0x40,
    GAIN21 = 0x20,
    GAIN20 = 0x10,
    MUX22 = 0x04,
    MUX21 = 0x02,
    MUX20 = 0x01,

    CH2SET_const = 0x00
};

enum CH3SET_bits
{
    PD_3 = 0x80,
    GAIN32 = 0x40,
    GAIN31 = 0x20,
    GAIN30 = 0x10,
    MUX32 = 0x04,
    MUX31 = 0x02,
    MUX30 = 0x01,

    CH3SET_const = 0x00
};

enum CH4SET_bits
{
    PD_4 = 0x80,
    GAIN42 = 0x40,
    GAIN41 = 0x20,
    GAIN40 = 0x10,
    MUX42 = 0x04,
    MUX41 = 0x02,
    MUX40 = 0x01,

    CH4SET_const = 0x00
};

enum CH5SET_bits
{
    PD_5 = 0x80,
    GAIN52 = 0x40,
    GAIN51 = 0x20,
    GAIN50 = 0x10,
    MUX52 = 0x04,
    MUX51 = 0x02,
    MUX50 = 0x01,

    CH5SET_const = 0x00
};

enum CH6SET_bits
{
    PD_6 = 0x80,
    GAIN62 = 0x40,
    GAIN61 = 0x20,
    GAIN60 = 0x10,
    MUX62 = 0x04,
    MUX61 = 0x02,
    MUX60 = 0x01,

    CH6SET_const = 0x00
};

enum CH7SET_bits
{
    PD_7 = 0x80,
    GAIN72 = 0x40,
    GAIN71 = 0x20,
    GAIN70 = 0x10,
    MUX72 = 0x04,
    MUX71 = 0x02,
    MUX70 = 0x01,

    CH7SET_const = 0x00
};

enum CH8SET_bits
{
    PD_8 = 0x80,
    GAIN82 = 0x40,
    GAIN81 = 0x20,
    GAIN80 = 0x10,
    MUX82 = 0x04,
    MUX81 = 0x02,
    MUX80 = 0x01,

    CH8SET_const = 0x00
};

enum BIAS_SENSP_bits
{
    BIAS8P = 0x80,
    BIAS7P = 0x40,
    BIAS6P = 0x20,
    BIAS5P = 0x10,
    BIAS4P = 0x08,
    BIAS3P = 0x04,
    BIAS2P = 0x02,
    BIAS1P = 0x01,

    BIAS_SENSP_const = 0x00
};

enum BIAS_SENSN_bits
{
    BIAS8N = 0x80,
    BIAS7N = 0x40,
    BIAS6N = 0x20,
    BIAS5N = 0x10,
    BIAS4N = 0x08,
    BIAS3N = 0x04,
    BIAS2N = 0x02,
    BIAS1N = 0x01,

    BIAS_SENSN_const = 0x00
};

enum LOFF_SENSP_bits
{
    LOFF8P = 0x80,
    LOFF7P = 0x40,
    LOFF6P = 0x20,
    LOFF5P = 0x10,
    LOFF4P = 0x08,
    LOFF3P = 0x04,
    LOFF2P = 0x02,
    LOFF1P = 0x01,

    LOFF_SENSP_const = 0x00
};

enum LOFF_SENSN_bits
{
    LOFF8N = 0x80,
    LOFF7N = 0x40,
    LOFF6N = 0x20,
    LOFF5N = 0x10,
    LOFF4N = 0x08,
    LOFF3N = 0x04,
    LOFF2N = 0x02,
    LOFF1N = 0x01,

    LOFF_SENSN_const = 0x00
};

enum LOFF_FLIP_bits
{
    LOFF_FLIP8 = 0x80,
    LOFF_FLIP7 = 0x40,
    LOFF_FLIP6 = 0x20,
    LOFF_FLIP5 = 0x10,
    LOFF_FLIP4 = 0x08,
    LOFF_FLIP3 = 0x04,
    LOFF_FLIP2 = 0x02,
    LOFF_FLIP1 = 0x01,

    LOFF_FLIP_const = 0x00
};

enum LOFF_STATP_bits
{
    IN8P_OFF = 0x80,
    IN7P_OFF = 0x40,
    IN6P_OFF = 0x20,
    IN5P_OFF = 0x10,
    IN4P_OFF = 0x08,
    IN3P_OFF = 0x04,
    IN2P_OFF = 0x02,
    IN1P_OFF = 0x01,

    LOFF_STATP_const = 0x00
};

enum LOFF_STATN_bits
{
    IN8N_OFF = 0x80,
    IN7N_OFF = 0x40,
    IN6N_OFF = 0x20,
    IN5N_OFF = 0x10,
    IN4N_OFF = 0x08,
    IN3N_OFF = 0x04,
    IN2N_OFF = 0x02,
    IN1N_OFF = 0x01,

    LOFF_STATN_const = 0x00
};

enum GPIO_bits
{
    GPIOD4 = 0x80,
    GPIOD3 = 0x40,
    GPIOD2 = 0x20,
    GPIOD1 = 0x10,
    GPIOC4 = 0x08,
    GPIOC3 = 0x04,
    GPIOC2 = 0x02,
    GPIOC1 = 0x01,

    GPIO_const = 0x00
};

enum CONFIG4_bits
{
    SINGLE_SHOT = 0x08,
    PD_LOFF_COMP = 0x02,
    CONFIG4_const = 0x00,
};

void ads1299_read_regs(void);
void ads1299_send_command(uint32_t command);
uint16_t spi_xfer(uint16_t data);
void ads1299_wreg(uint32_t reg, uint8_t* val, uint16_t num);
uint8_t* ads1299_rreg(uint32_t reg, uint16_t num);
int32_t* ads1299_read_data(void);
int ads1299_setup(void);
int32_t ads1299_channel_convert(void);
void ads1299_reset(void);
void ads1299_print(char *user_mesg, uint32_t *mesg );
int ads1299_check(uint8_t* read_vals, uint8_t* need_vals, uint16_t num);

#ifdef __cplusplus
}
#endif
#endif /* namespace AD7190 */
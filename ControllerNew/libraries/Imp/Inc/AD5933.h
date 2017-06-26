#include "stm32f4xx_hal.h"

#define AD5933_I2C_ADDRESS     0x1A  /// HAL �� ��������, ������� �������
#define BUFFER_IMP_SIZE    0x5
#define BUFFSIZE         2
#define INCREMENTS_MAX     5
#define pi 3.1415926535

#define cdc_log 0
#define usart_log 0

void impedance_init(void);
void impedance_measure(float *impedance, float *activeZ, float *reactiveZ);
void impedance_measure_uint16(uint16_t *impedance, uint16_t *activeZ, uint16_t *reactiveZ);


//void AD5933_WriteByte_LOG(uint8_t addr, uint8_t data);


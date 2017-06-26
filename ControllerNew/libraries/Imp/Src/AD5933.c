#include "stm32f4xx_hal.h"
#include <math.h>
#include "AD5933.h"
#include "PCF8574A.h"
#include "ADG728.h"
#include "main.h"

#if (cdc_log == 1)
#include "usbd_cdc_if.h"
uint8_t TX_buffer[64];
extern uint8_t host_connected;
#endif

#if (usart_log == 1)
#include "usart.h"
extern uint8_t TX_buffer[256];
#endif

extern I2C_HandleTypeDef hi2c2;


float phase_buffer[INCREMENTS_MAX];
float magnitude_buffer[INCREMENTS_MAX];
float phase_system[INCREMENTS_MAX];
float gainFactor_buffer[INCREMENTS_MAX];

float Z_calibrationMin = 10;
float Z_calibrationMax = 120;
float Z_calibration;

uint8_t PCF8574A_byte = 0;      // ���� �� PCF

uint8_t gain = 0x1;//0x1
uint8_t ext_clock = 0x0;//0x8
uint8_t range = 0x0;

static uint8_t AD5933_get_data(uint8_t *measurements_buffer);
static void AD5933_WriteByte(uint8_t addr, uint8_t data);
static int16_t AD_calculate(uint8_t data_high, uint8_t data_low);
static void LED_on(uint8_t led);
static void LED_off(uint8_t led);
static void set_channel(uint8_t channel);
static void enable_output(void);
static void disable_output(void);
static void AD5933_init(uint32_t frequency_code);

static float calcAvgFloat(float *DATA, uint8_t size);

static void AD5933_sweep(uint8_t increments_max, float *magnitude_buffer, float *phase_buffer);
static void AD5933_calibrate(uint8_t rfb, uint8_t rcal);

void impedance_init(void)
{
	enable_output();

	LED_on(1);

	AD5933_init(0x20C49);			//1 ���

	ADG728_reset();

	HAL_Delay(1);

	LED_on(2);

	AD5933_calibrate(0x40,0x1);	//

	LED_on(3);

	disable_output();
}


void AD5933_init(uint32_t frequency_code)
{
  uint8_t f_msb = (uint8_t)(frequency_code/0x10000);
  uint8_t f_sb = (uint8_t)(((uint32_t)frequency_code % 0x10000) / 0x100);
  uint8_t f_lsb = (uint8_t)((uint32_t)frequency_code % 0x100);
  
  AD5933_WriteByte(0x81, 0x10 + ext_clock); // Reset	(for ext_clock +0x8)
  
  HAL_Delay(10);

  AD5933_WriteByte(0x82, f_msb); // 
  AD5933_WriteByte(0x83, f_sb); // 
  AD5933_WriteByte(0x84, f_lsb); // 

  AD5933_WriteByte(0x85, 0x00); // Frequency increment      10 Hz 014F
  AD5933_WriteByte(0x86, 0xA7);
  AD5933_WriteByte(0x87, 0xC5); 
    
  AD5933_WriteByte(0x88, 0x00); // Number of increments
  AD5933_WriteByte(0x89, INCREMENTS_MAX);
  
  AD5933_WriteByte(0x8A, 0x00); // time cycles 03
  AD5933_WriteByte(0x8B, 0x02); // 01
  
  AD5933_WriteByte(0x81, 0x00+ext_clock); // External clock 08
  
  //AD5933_WriteByte(0x80, 0xB0+gain); // Standby  B1
  
  //AD5933_WriteByte(0x80, 0x11); // Initialize with start frequency
  //HAL_Delay(100); 
}


void AD5933_WriteByte(uint8_t addr, uint8_t data)
{
  uint8_t temp[1];
  temp[0]  = data;
  HAL_I2C_Mem_Write_IT(&hi2c2, (uint16_t)AD5933_I2C_ADDRESS, addr, I2C_MEMADD_SIZE_8BIT, temp, 1);
}

int16_t AD_calculate(uint8_t data_high, uint8_t data_low)
{
  uint16_t data;
  int16_t output;

  //data = data_high <<8;
  data = data_low;

  data = data + (data_high <<8);

    if(data > 0x7fff)
    {
    	output = -(0x10000-data);
    }	
    else
    {
    	output = data;
    }
    return output;
}

uint8_t AD5933_get_data(uint8_t *measurements_buffer)
{
  uint8_t temp_buffer[4];
  
  AD5933_WriteByte(0xB0, 0x8F);   // set pointer
  if (HAL_I2C_Master_Receive_IT(&hi2c2, (uint16_t)AD5933_I2C_ADDRESS, (uint8_t *)temp_buffer, 1) == HAL_OK)
  {
    if (temp_buffer[0] & 0x2)     //Status OK
    {
      AD5933_WriteByte(0xB0, 0x96);   // set pointer
      if (HAL_I2C_Master_Receive_IT(&hi2c2, (uint16_t)AD5933_I2C_ADDRESS, (uint8_t *)temp_buffer, 1) == HAL_OK)
      measurements_buffer[2] = temp_buffer[0];
                   
      AD5933_WriteByte(0xB0, 0x97);   // set pointer
      if (HAL_I2C_Master_Receive_IT(&hi2c2, (uint16_t)AD5933_I2C_ADDRESS, (uint8_t *)temp_buffer, 1) == HAL_OK)
      measurements_buffer[3] = temp_buffer[0];
                 
      AD5933_WriteByte(0xB0, 0x94);   // set pointer
      if (HAL_I2C_Master_Receive_IT(&hi2c2, (uint16_t)AD5933_I2C_ADDRESS, (uint8_t *)temp_buffer, 1) == HAL_OK)
      measurements_buffer[0] = temp_buffer[0];
                   
      AD5933_WriteByte(0xB0, 0x95);   // set pointer
      if (HAL_I2C_Master_Receive_IT(&hi2c2, (uint16_t)AD5933_I2C_ADDRESS, (uint8_t *)temp_buffer, 1) == HAL_OK)
      measurements_buffer[1] = temp_buffer[0];
      return 1;  
    } // Status OK
    else
    {
      return 0;
    }
  } // HAL_OK
  else
  {
    return 0;
  }
}

void AD5933_sweep(uint8_t increments_max, float *magnitude_buffer, float *phase_buffer)
{
  float temp;
  uint8_t increments = 0;
  uint8_t raw_data[5];
  int16_t Real, Imaginary;
 
  AD5933_WriteByte(0x80, 0xB0+range+gain); // Standby  
  //HAL_Delay(1); //10
  
  //AD5933_WriteByte(0x81, 0x10+ext_clock); // Reset
  //HAL_Delay(1000);
  
  AD5933_WriteByte(0x80, 0x10+range+gain); // Initialize with start frequency
  //HAL_Delay(1); //10
  AD5933_WriteByte(0x80, 0x20+range+gain); // Start Sweep
  //HAL_Delay(1); //10
      
  while(increments<increments_max)
  {
    if (AD5933_get_data(raw_data) != 0)
    {
       Real = AD_calculate(raw_data[0],raw_data[1]);     
        Imaginary = AD_calculate(raw_data[2],raw_data[3]);   
        magnitude_buffer[increments] = sqrt(Real*Real+Imaginary*Imaginary);     
    
        temp = atan((float)Imaginary/(float)Real);	// �������

        if (Real > 0)
        {
          if (Imaginary > 0)
          {
             phase_buffer[increments] = temp * 180 / pi;	// ������
          }
          else
          {
            phase_buffer[increments] = 360 + temp * 180 / pi;	// ��������
          }
        }
        else // Real <0
        {
          if (Imaginary > 0)
          {
            phase_buffer[increments] = 180 + temp * 180 / pi;	// ������
          }
          else
          {
            phase_buffer[increments] = 180 + temp * 180 / pi;	// ������
          }
        }
     //AD5933_WriteByte(0x80, 0x30+range+gain); // Increment
    //HAL_Delay(500); 
   AD5933_WriteByte(0x80, 0x40+range+gain); // Repeat
   //increments++;
    }   
    increments++;
  }// while increments
  AD5933_WriteByte(0x80, 0xB0+range+gain); // Standby  
 }


float calcAvgFloat(float *DATA, uint8_t size)
{
  double temp = 0;
  uint8_t count;
    for(count = 0; count<size; count++)
    {
      temp = temp + DATA[count];
    } 
  return (temp / size);
}

void AD5933_calibrate(uint8_t rfb, uint8_t rcal)
{
	uint8_t i;

	  ADG728_set(rfb);                //    Rfb
	  set_channel(rcal);				  // Rcal

	  //ADG728_set(0x80);               //    Rfb 68
	  //ADG728_set(0x40);             //    Rfb 10 		(62)
	  //ADG728_set(0x20);             //    Rfb 12,4
	  ADG728_set(0x10);             //    Rfb   		(11,3)

	  //ADG728_set(0x8);              //    Rfb 		(20)
	  //ADG728_set(0x4);              //    Rfb 750
	  //ADG728_set(0x2);              //    Rfb 75
	  //ADG728_set(0x1);              //    Rfb 7,5


	  //set_channel(0);                 //    Rcal 100 ���
	  //set_channel(1);                 //    Rcal 1 ���
	  //set_channel(3);                 //    Rcal 150 ���
	  set_channel(4);                 //    Rcal 360k
	  //set_channel(5);                 //    Rcal 1,2 ���
	  //set_channel(6);                 //    Rcal 280k
	  //set_channel(7);                 	//    Rcal 750k

	  Z_calibration = 360 + 102;


	  HAL_Delay(1);
	  AD5933_sweep(INCREMENTS_MAX, magnitude_buffer, phase_buffer);

	    for(i = 0; i < INCREMENTS_MAX; i++)
	    {
	      phase_system[i] = phase_buffer[i]; 	// �������
	      gainFactor_buffer[i] = (1 / Z_calibration) / magnitude_buffer[i];
	    }
}

void LED_on(uint8_t led)
{
  if ((led<=3)&&(led>0))
  {
  uint8_t temp = 8 - led;
  PCF8574A_byte |= (1<<temp);  //set to 1
  PCF8574A_set(PCF8574A_byte);      //
  }
}

void LED_off(uint8_t led)
{
  if ((led<=3)&&(led>0))
  {
  uint8_t temp = 8 - led;
  PCF8574A_byte &= ~(1<<temp); // set to 0
  PCF8574A_set(PCF8574A_byte);      //
  }
}

void set_channel(uint8_t channel)
{
  if (channel<=15)
  {
  PCF8574A_byte &= (0xF0);
  PCF8574A_byte |= channel;
  PCF8574A_set(PCF8574A_byte);      //
  }
}

void enable_output(void)
{
  PCF8574A_byte |= (1<<4);  //set to 1
  PCF8574A_set(PCF8574A_byte);      //
}

void disable_output(void)
{
  PCF8574A_byte &= ~(1<<4); // set to 0
  PCF8574A_set(PCF8574A_byte);      //
}


void impedance_measure(float *impedance, float *activeZ, float *reactiveZ)
{
	uint8_t channel, i;

	float impedance_buffer[INCREMENTS_MAX];
	double Zphase_buffer[INCREMENTS_MAX];
	float Zactive_buffer[INCREMENTS_MAX];
	float Zreactive_buffer[INCREMENTS_MAX];
	float impedanceTotalAvg;

	LED_off(1);

	enable_output();

	for(channel = 0;channel<7;channel++)
	{

	switch (channel)
	{
		case 0:
		 set_channel(10);
		// channel = 1;
		break;
		case 1:
		 set_channel(11);
		// channel = 2;
		break;
		case 2:
		 set_channel(12);
		// channel = 3;
		break;
		case 3:
		 set_channel(13);
		// channel = 4;
		break;
		case 4:
		 set_channel(14);
		// channel = 5;
		break;
		case 5:
		 set_channel(15);
		// channel = 6;
		 break;
		case 6:
		 set_channel(9);
		// channel = 0;
		 // end measure
		 break;
		default:
		set_channel(9);
		channel = 0;
		break;
	}// switch channel

	HAL_Delay(1);

	AD5933_sweep(INCREMENTS_MAX, magnitude_buffer, phase_buffer);

	for(i = 0; i < INCREMENTS_MAX; i++)
	{
	   Zphase_buffer[i] = (phase_buffer[i] - phase_system[i]) * pi / 180; 	// ������� -> �������

	   impedance_buffer[i]	= 1 / (magnitude_buffer[i] * gainFactor_buffer[i]);
	   Zactive_buffer[i] 	= fabs(impedance_buffer[i]) * cos(Zphase_buffer[i]);
	   Zreactive_buffer[i]	= fabs(impedance_buffer[i]) * sin(Zphase_buffer[i]);
	}

	activeZ[channel] =  calcAvgFloat(Zactive_buffer, INCREMENTS_MAX) - 102;
	reactiveZ[channel] = calcAvgFloat(Zreactive_buffer, INCREMENTS_MAX);
	impedanceTotalAvg = calcAvgFloat(impedance_buffer, INCREMENTS_MAX);
	impedance[channel] = impedanceTotalAvg - 102;


#if (cdc_log == 1)
	//  TX_buffer[76 + channel*41] = channel;										//1
	//  memcpy(TX_buffer + 77 + channel*41, &magnitude_buffer, 4*INCREMENTS_MAX);	//20
	//  memcpy(TX_buffer + 97 + channel*41, &phase_buffer, 4*INCREMENTS_MAX);		//20

	  sprintf((char *)TX_buffer,"Channel:%d Z:%+.1f ActiveZ:%+.1f ReactiveZ:%+.1f \n\r", channel, impedance[channel], activeZ[channel], reactiveZ[channel]);
	  if (host_connected == 1)
	  {
		 while(CDC_Transmit_FS(TX_buffer,64) !=USBD_OK);
	  }
#endif

#if (usart_log == 1)
	  sprintf((char *)TX_buffer,"Channel_%d Z:%+.1f  ActiveZ:%+.1f  ReactiveZ:%+.1f", channel, impedance[channel], activeZ[channel], reactiveZ[channel]);
	  while(HAL_UART_Transmit(&huart1, TX_buffer, 256 , 100) !=HAL_OK);
	  sprintf((char *)TX_buffer,"\n\r");
	  while(HAL_UART_Transmit(&huart1, TX_buffer, 2 , 100) !=HAL_OK);
#endif
	}// for

	disable_output();
	LED_on(1);

#if (cdc_log == 1)
	//  TX_buffer[76 + channel*41] = channel;										//1
	//  memcpy(TX_buffer + 77 + channel*41, &magnitude_buffer, 4*INCREMENTS_MAX);	//20
	//  memcpy(TX_buffer + 97 + channel*41, &phase_buffer, 4*INCREMENTS_MAX);		//20

	  sprintf((char *)TX_buffer,"\n");
	  if (host_connected == 1)
	  {
		  while(CDC_Transmit_FS(TX_buffer,1) !=USBD_OK);
	  }
#endif

#if (usart_log == 1)
	  sprintf((char *)TX_buffer,"\n");
	  while(HAL_UART_Transmit(&huart1, TX_buffer, 1 , 100) !=HAL_OK);
#endif

}

void impedance_measure_uint16(uint16_t *impedance, uint16_t *activeZ, uint16_t *reactiveZ)
{
	uint8_t channel, i;

	float impedance_buffer[INCREMENTS_MAX];
	double Zphase_buffer[INCREMENTS_MAX];
	float Zactive_buffer[INCREMENTS_MAX];
	float Zreactive_buffer[INCREMENTS_MAX];
	float impedanceTotalAvg;

	LED_off(1);

	enable_output();

	for(channel = 0;channel<7;channel++)
	{

	switch (channel)
	{
		case 0:
		 set_channel(10);
		// channel = 1;
		break;
		case 1:
		 set_channel(11);
		// channel = 2;
		break;
		case 2:
		 set_channel(12);
		// channel = 3;
		break;
		case 3:
		 set_channel(13);
		// channel = 4;
		break;
		case 4:
		 set_channel(14);
		// channel = 5;
		break;
		case 5:
		 set_channel(15);
		// channel = 6;
		 break;
		case 6:
		 set_channel(9);
		// channel = 0;
		 // end measure
		 break;
		default:
		set_channel(9);
		channel = 0;
		break;
	}// switch channel

	//HAL_Delay(1);

	AD5933_sweep(INCREMENTS_MAX, magnitude_buffer, phase_buffer);

	for(i = 0; i < INCREMENTS_MAX; i++)
	{
	   Zphase_buffer[i] = (phase_buffer[i] - phase_system[i]) * pi / 180; 	// ������� -> �������

	   impedance_buffer[i]	= 1 / (magnitude_buffer[i] * gainFactor_buffer[i]);
	   Zactive_buffer[i] 	= fabs(impedance_buffer[i]) * cos(Zphase_buffer[i]);
	   Zreactive_buffer[i]	= fabs(impedance_buffer[i]) * sin(Zphase_buffer[i]);
	}

	activeZ[channel]   = (uint16_t)(calcAvgFloat(Zactive_buffer, INCREMENTS_MAX) - 102);
	reactiveZ[channel] = (uint16_t)(calcAvgFloat(Zreactive_buffer, INCREMENTS_MAX));
	impedanceTotalAvg  = (uint16_t)(calcAvgFloat(impedance_buffer, INCREMENTS_MAX));
	impedance[channel] = (uint16_t)(impedanceTotalAvg - 102);


#if (cdc_log == 1)
	  sprintf((char *)TX_buffer,"Channel:%d Z:%+.1f ActiveZ:%+.1f ReactiveZ:%+.1f \n\r", channel, impedance[channel], activeZ[channel], reactiveZ[channel]);
	  if (host_connected == 1)
	  {
		 while(CDC_Transmit_FS(TX_buffer,64) !=USBD_OK);
	  }
#endif
	}// for

	disable_output();
	LED_on(1);

#if (cdc_log == 1)
	  sprintf((char *)TX_buffer,"\n");
	  if (host_connected == 1)
	  {
		  while(CDC_Transmit_FS(TX_buffer,1) !=USBD_OK);
	  }
#endif

}
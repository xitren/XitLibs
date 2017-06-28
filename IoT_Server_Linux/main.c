/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: xitre_000
 *
 * Created on 15 May 2016, 04:21
 */

#include<stdio.h> //printf
#include<string.h> //memset
#include<stdlib.h> //exit(0);
#include<arpa/inet.h>
#include<sys/socket.h>
#include <stdbool.h>
#include <strings.h>

#ifdef PI
    #include <linux/i2c-dev.h>
    #include <fcntl.h>
    #include <string.h>
    #include <sys/ioctl.h>
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <unistd.h>
#endif

#include "ImageVisualise.h"
#include "coap.h"
#include "Handler.h"
#include "CommandModule.h"

#define PORT 5683


#ifdef PI
    // Registers/etc.
    #define  __SUBADR1            0x02
    #define  __SUBADR2            0x03
    #define  __SUBADR3            0x04
    #define  __SUBADR4            0x05    //добавила четвертый моторчик
    #define  __MODE1              0x00
    #define  __PRESCALE           0xFE
    #define  __LED0_ON_L          0x06
    #define  __LED0_ON_H          0x07
    #define  __LED0_OFF_L         0x08
    #define  __LED0_OFF_H         0x09
    #define  __ALLLED_ON_L        0xFA
    #define  __ALLLED_ON_H        0xFB
    #define  __ALLLED_OFF_L       0xFC
    #define  __ALLLED_OFF_H       0xFD

    unsigned char buf_i2c[10];
    int fd_i2c;
    uint8_t read_i2c(uint8_t reg)
    {
        uint8_t ret;

        buf_i2c[0] = reg;													// This is the register we want to read from

        if ((write(fd_i2c, buf_i2c, 1)) != 1) {								// Send register we want to read from	
                printf("Error writing to i2c slave\n");
                exit(1);
        }

        if (read(fd_i2c, buf_i2c, 1) != 1) {								// Read back data into buf[]
                printf("Unable to read from slave\n");
                exit(1);
        }
        else {
                #ifdef DEBUG
                printf("**** PCA9685 read %02X from %02X****\n",buf_i2c[0],reg);		
                #endif		
                return buf_i2c[0];
        }


        return 0;
    }
    uint8_t write_i2c(uint8_t reg, uint8_t data)
    {
        uint8_t ret;

        buf_i2c[0] = reg;	
        buf_i2c[1] = data;													// This is the register we want to read from

        if ((write(fd_i2c, buf_i2c, 2)) != 2) {								// Send register we want to read from	
                printf("Error writing to i2c slave\n");
                exit(1);
        }
                #ifdef DEBUG
                printf("**** PCA9685 write %02X to %02X****\n",data,reg);		
                #endif		

        return 0;
    }

    void setPWM_i2c(uint8_t channel, uint16_t on, uint16_t off)
    {
        write_i2c(__LED0_ON_L+4*channel,on & 0xFF);
        write_i2c(__LED0_ON_H+4*channel,on >> 8);
        write_i2c(__LED0_OFF_L+4*channel,off & 0xFF);
        write_i2c(__LED0_OFF_H+4*channel,off >> 8);
    }				
#endif		
        
/*
 * 
 */
int main(int argc, char** argv) {

    InitUDP();
    InitImageP300();
    InitHandler(EEG);
    EEGRecorderInit(0,250);
    
    uint32_t amplitude[7] = {10000,10000,100000,1000000,100000,10000,10000};
    uint32_t frequency[7] = {10,20,10,10,30,100,5};
    printf("Command interface setted.\n");
    
//    #ifdef PI
//	printf("**** PCA9685 test program ****\n");
//											// File descrition
//	char *fileName_i2c = "/dev/i2c-1";								// Name of the port we will be using
//	int  address_i2c = 0x40;										// Buffer for data being read/ written on the i2c bus
//	
//	if ((fd_i2c = open(fileName_i2c, O_RDWR)) < 0) {					// Open port for reading and writing
//		printf("Failed to open i2c port\n");
//		exit(1);
//	}
//	
//	if (ioctl(fd_i2c, I2C_SLAVE, address_i2c) < 0) {					// Set the port options and set the address of the device we wish to speak to
//		printf("Unable to get bus access to talk to slave\n");
//		exit(1);
//	}
//        
//        uint8_t oldmode = read_i2c(__MODE1);
//        uint8_t newmode = (oldmode & 0x7F) | 0x10;
//        write_i2c(__MODE1, newmode);
//        read_i2c(__MODE1);
//        write_i2c(__MODE1, 0x00);
//        read_i2c(__MODE1);
//        write_i2c(__PRESCALE, 0x1E);
//        sleep(1);
//        
//        setPWM_i2c(0,0,150);
//        setPWM_i2c(1,0,150);
//        setPWM_i2c(2,0,150);
//        setPWM_i2c(3,0,150);
//        setPWM_i2c(4,0,150);           //ЗДЕСЬ
//	printf("**** PCA9685 set SERVO ****\n");
//    #endif
    
        function_beakon();
        //function_update();
        
    while(1)
    {
//        #ifdef PI
//            setPWM_i2c(1,0, ReadMem(REG_SERVO_1) );
//            setPWM_i2c(2,0, ReadMem(REG_SERVO_2) );
//            setPWM_i2c(3,0, ReadMem(REG_SERVO_4) );
//            setPWM_i2c(4,0, ReadMem(REG_SERVO_5) );  //И ЗДЕСЬ
//        #endif
        
        
        UserProtocolHandler();
        UserOperationHandler();
        CalculationHandler();
                
        //VideoFrameHandler();
    }
    return (EXIT_SUCCESS);
}


/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   newsimpletest.c
 * Author: gusev_a
 *
 * Created on 9 ноября 2018 г., 14:58
 */

#include <stdio.h>
#include <stdlib.h>
#include "CSMACD.h"

CSMACDController_t controller;
extern const uint16_t CRC16ANSIoTBL[256];

uint8_t msg[] = { 
    0x32, 0x33, 0x21, 0x68, 0xF2, 0x22, 
    0x32, 0x33, 0x21, 0x68, 0xF2, 0x22 
};

uint8_t Sender(uint8_t output)
{
    printf(" %02X",output);
    return output;
}

/*
 * Simple C Test Suite
 */

void test1() {
    uint16_t    CRC_MB = 0xFFFF;
    uint8_t     ID = 0;
    uint8_t     DATA[10];
    printf("recvtest test 1\n");
    csma_receiver(&controller,0x55);
    CRC_MB = (CRC_MB >> 8) ^ CRC16ANSIoTBL[(CRC_MB & 0xFF) ^ (0x55)];
    csma_receiver(&controller,0x20);
    CRC_MB = (CRC_MB >> 8) ^ CRC16ANSIoTBL[(CRC_MB & 0xFF) ^ (0x20)];
    csma_receiver(&controller,0x00);
    CRC_MB = (CRC_MB >> 8) ^ CRC16ANSIoTBL[(CRC_MB & 0xFF) ^ (0x00)];
    csma_receiver(&controller,0x01);
    CRC_MB = (CRC_MB >> 8) ^ CRC16ANSIoTBL[(CRC_MB & 0xFF) ^ (0x01)];
    csma_receiver(&controller,0x56);
    CRC_MB = (CRC_MB >> 8) ^ CRC16ANSIoTBL[(CRC_MB & 0xFF) ^ (0x56)];
    csma_receiver(&controller,((CRC_MB)/256)&255);
    csma_receiver(&controller,(CRC_MB)&255);
    csma_main_cycle(&controller,&ID,DATA);
    printf("Received %d %02X\n",ID,DATA[0]);
    if ( (ID != 0x20) 
            || (DATA[0] != 0x56) )    
        printf("%%TEST_FAILED%% time=0 testname=test1 (recvtest) message=error message sample\n");
}

void test2() {
    uint16_t    CRC_MB = 0xFFFF;
    uint8_t     ID = 0;
    uint8_t     DATA[10];
    printf("recvtest test 2\n");
    csma_receiver(&controller,0x55);
    CRC_MB = (CRC_MB >> 8) ^ CRC16ANSIoTBL[(CRC_MB & 0xFF) ^ (0x55)];
    csma_receiver(&controller,0x20);
    CRC_MB = (CRC_MB >> 8) ^ CRC16ANSIoTBL[(CRC_MB & 0xFF) ^ (0x20)];
    csma_receiver(&controller,0x00);
    CRC_MB = (CRC_MB >> 8) ^ CRC16ANSIoTBL[(CRC_MB & 0xFF) ^ (0x00)];
    csma_receiver(&controller,0x04);
    CRC_MB = (CRC_MB >> 8) ^ CRC16ANSIoTBL[(CRC_MB & 0xFF) ^ (0x04)];
    csma_receiver(&controller,0x56);
    CRC_MB = (CRC_MB >> 8) ^ CRC16ANSIoTBL[(CRC_MB & 0xFF) ^ (0x56)];
    csma_receiver(&controller,0x33);
    CRC_MB = (CRC_MB >> 8) ^ CRC16ANSIoTBL[(CRC_MB & 0xFF) ^ (0x33)];
    csma_receiver(&controller,0x54);
    CRC_MB = (CRC_MB >> 8) ^ CRC16ANSIoTBL[(CRC_MB & 0xFF) ^ (0x54)];
    csma_receiver(&controller,0x44);
    CRC_MB = (CRC_MB >> 8) ^ CRC16ANSIoTBL[(CRC_MB & 0xFF) ^ (0x44)];
    csma_receiver(&controller,((CRC_MB)/256)&255);
    csma_receiver(&controller,(CRC_MB)&255);
    csma_main_cycle(&controller,&ID,DATA);  //parser
    printf("Received %d m: %02X %02X %02X %02X\n",ID,DATA[0],DATA[1],DATA[2],DATA[3]);
    if ( (ID != 0x20) 
            || (DATA[0] != 0x56)
            || (DATA[1] != 0x33)
            || (DATA[2] != 0x54)
            || (DATA[3] != 0x44) )    
        printf("%%TEST_FAILED%% time=0 testname=test2 (recvtest) message=error message sample\n");
}

void test3() {
    printf("sendtest test 1\n");
    PacketizeToSend(&controller, msg, 0x21, 6);
    while (csma_sender(&controller) != CSMACD_WAIT);
    csma_clock_cycle(&controller);
    csma_clock_cycle(&controller);
    csma_clock_cycle(&controller);
    csma_clock_cycle(&controller);
}

void test4() {
    printf("sendtest test 2\n");
    PacketizeToSend(&controller, msg, 0x21, 12);
    while (csma_sender(&controller) != CSMACD_WAIT);
    csma_clock_cycle(&controller);
    csma_clock_cycle(&controller);
    csma_clock_cycle(&controller);
    csma_clock_cycle(&controller);
}

int main(int argc, char** argv) {
    printf("%%SUITE_STARTING%% \n");
    printf("%%SUITE_STARTED%%\n");
    
    csma_init(&controller,&Sender);

    printf("%%TEST_STARTED%% test1 (recvtest)\n");
    test1();
    printf("%%TEST_FINISHED%% time=0 test1 (recvtest) \n");

    printf("%%TEST_STARTED%% test2 (recvtest)\n");
    test2();
    printf("%%TEST_FINISHED%% time=0 test2 (recvtest) \n");
    
    csma_init(&controller,&Sender);

    printf("%%TEST_STARTED%% test3 (sendtest)\n");
    test3();
    printf("%%TEST_FINISHED%% time=0 test3 (sendtest) \n");

    printf("%%TEST_STARTED%% test4 (sendtest)\n");
    test4();
    printf("%%TEST_FINISHED%% time=0 test4 (sendtest) \n");

    printf("%%SUITE_FINISHED%% time=0\n");

    return (EXIT_SUCCESS);
}

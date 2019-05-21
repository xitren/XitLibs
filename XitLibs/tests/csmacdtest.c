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
#include "CRC16ANSI.h"
#include "coap_messages_example.h"

CSMACDController_t controller;
extern const uint16_t CRC16ANSIoTBL[256];

uint8_t msg[] = {
    0x32, 0x33, 0x21, 0x68, 0xF2, 0x22,
    0x32, 0x33, 0x21, 0x68, 0xF2, 0x22
};

uint8_t Sender(uint8_t output)
{
    printf(" %02X", output);
    return output;
}

/*
 * Simple C Test Suite
 */

void test1()
{
    uint16_t CRC_MB = 0xFFFF;
    uint8_t ID = 0;
    uint8_t DATA[10];
    printf("recvtest test 1\n");
    csma_receiver(&controller, 0x55);
    CRC_MB = (CRC_MB >> 8) ^ CRC16ANSIoTBL[(CRC_MB & 0xFF) ^ (0x55)];
    csma_receiver(&controller, 0x20);
    CRC_MB = (CRC_MB >> 8) ^ CRC16ANSIoTBL[(CRC_MB & 0xFF) ^ (0x20)];
    csma_receiver(&controller, 0x00);
    CRC_MB = (CRC_MB >> 8) ^ CRC16ANSIoTBL[(CRC_MB & 0xFF) ^ (0x00)];
    csma_receiver(&controller, 0x01);
    CRC_MB = (CRC_MB >> 8) ^ CRC16ANSIoTBL[(CRC_MB & 0xFF) ^ (0x01)];
    csma_receiver(&controller, 0x56);
    CRC_MB = (CRC_MB >> 8) ^ CRC16ANSIoTBL[(CRC_MB & 0xFF) ^ (0x56)];
    csma_receiver(&controller, ((CRC_MB) / 256)&255);
    csma_receiver(&controller, (CRC_MB)&255);
    csma_main_cycle(&controller, &ID, DATA);
    printf("Received %d %02X\n", ID, DATA[0]);
    if ((ID != 0x20)
            || (DATA[0] != 0x56))
        printf(" %%TEST_FAILED%% time=0 testname=test1 (recvtest) message=error message sample\n");
}

void test2()
{
    uint16_t CRC_MB = 0xFFFF;
    uint8_t ID = 0;
    uint8_t DATA[10];
    printf("recvtest test 2\n");
    csma_receiver(&controller, 0x55);
    CRC_MB = (CRC_MB >> 8) ^ CRC16ANSIoTBL[(CRC_MB & 0xFF) ^ (0x55)];
    csma_receiver(&controller, 0x20);
    CRC_MB = (CRC_MB >> 8) ^ CRC16ANSIoTBL[(CRC_MB & 0xFF) ^ (0x20)];
    csma_receiver(&controller, 0x00);
    CRC_MB = (CRC_MB >> 8) ^ CRC16ANSIoTBL[(CRC_MB & 0xFF) ^ (0x00)];
    csma_receiver(&controller, 0x04);
    CRC_MB = (CRC_MB >> 8) ^ CRC16ANSIoTBL[(CRC_MB & 0xFF) ^ (0x04)];
    csma_receiver(&controller, 0x56);
    CRC_MB = (CRC_MB >> 8) ^ CRC16ANSIoTBL[(CRC_MB & 0xFF) ^ (0x56)];
    csma_receiver(&controller, 0x33);
    CRC_MB = (CRC_MB >> 8) ^ CRC16ANSIoTBL[(CRC_MB & 0xFF) ^ (0x33)];
    csma_receiver(&controller, 0x54);
    CRC_MB = (CRC_MB >> 8) ^ CRC16ANSIoTBL[(CRC_MB & 0xFF) ^ (0x54)];
    csma_receiver(&controller, 0x44);
    CRC_MB = (CRC_MB >> 8) ^ CRC16ANSIoTBL[(CRC_MB & 0xFF) ^ (0x44)];
    csma_receiver(&controller, ((CRC_MB) / 256)&255);
    csma_receiver(&controller, (CRC_MB)&255);
    csma_main_cycle(&controller, &ID, DATA); //parser
    printf("Received %d m: %02X %02X %02X %02X\n", ID, DATA[0], DATA[1], DATA[2], DATA[3]);
    if ((ID != 0x20)
            || (DATA[0] != 0x56)
            || (DATA[1] != 0x33)
            || (DATA[2] != 0x54)
            || (DATA[3] != 0x44))
        printf(" %%TEST_FAILED%% time=0 testname=test2 (recvtest) message=error message sample\n");
}

void test3()
{
    printf("sendtest test 1\n");
    PacketizeToSend(&controller, msg, 0x21, 6);
    while (csma_sender(&controller) != CSMACD_WAIT);
    csma_clock_cycle(&controller);
    csma_clock_cycle(&controller);
    csma_clock_cycle(&controller);
    csma_clock_cycle(&controller);
    printf("\n");
}

void test4()
{
    printf("sendtest test 2\n");
    PacketizeToSend(&controller, msg, 0x21, 12);
    while (csma_sender(&controller) != CSMACD_WAIT);
    csma_clock_cycle(&controller);
    csma_clock_cycle(&controller);
    csma_clock_cycle(&controller);
    csma_clock_cycle(&controller);
    printf("\n");
}

void test5()
{
    uint8_t ID = 0;
    uint8_t DATA[1024];
    printf("recvtest test 5\n");
    uint32_t i;
    for (i = 0; i < 25; i++)
    {
        uint32_t j, k = 0;
        uint32_t *payload = msgs_streamer[i][0];
        uint16_t length = (uint16_t)msgs_streamer[i][1];
        uint8_t load[length];
        csma_main_cycle(&controller, &ID, DATA);
        csma_main_cycle(&controller, &ID, DATA);
        csma_main_cycle(&controller, &ID, DATA);
        csma_main_cycle(&controller, &ID, DATA);
        csma_main_cycle(&controller, &ID, DATA);
        csma_main_cycle(&controller, &ID, DATA);
        csma_main_cycle(&controller, &ID, DATA);
        csma_main_cycle(&controller, &ID, DATA);
        csma_main_cycle(&controller, &ID, DATA);
        csma_main_cycle(&controller, &ID, DATA);
        load[k++] = 0x55;
        load[k++] = 0x20;
        load[k++] = 0x00;
        load[k++] = (uint8_t)length;
        printf("--------- length : %02X\n", (uint8_t)length);
        for (j = 0; j < msgs_streamer[i][1]; j++)
        {
            printf("--------- : %02X\n", (uint8_t)payload[j]);
        }
        csma_receiver(&controller, load[0]);
        csma_main_cycle(&controller, &ID, DATA);
        csma_main_cycle(&controller, &ID, DATA);
        csma_main_cycle(&controller, &ID, DATA);
        csma_main_cycle(&controller, &ID, DATA);
        csma_receiver(&controller, load[1]);
        csma_main_cycle(&controller, &ID, DATA);
        csma_main_cycle(&controller, &ID, DATA);
        csma_receiver(&controller, load[2]);
        csma_receiver(&controller, load[3]);
        csma_main_cycle(&controller, &ID, DATA);
        csma_main_cycle(&controller, &ID, DATA);
        csma_main_cycle(&controller, &ID, DATA);
        csma_main_cycle(&controller, &ID, DATA);
        for (j = 0; j < length; j++)
        {
            load[k++] = (uint8_t)payload[j];
            csma_receiver(&controller, (uint8_t)payload[j]);
        }
        uint16_t CRC = CRC16ANSI(load, length + 4);
        csma_receiver(&controller, (uint8_t)((CRC >> 8) & 0xFF) );
        csma_receiver(&controller, (uint8_t)(CRC & 0xFF) );
        csma_main_cycle(&controller, &ID, DATA);
        printf("--------- CRC : 0x%04X\n", CRC );
        printf("Received %d %02X\n", ID, DATA[0]);
        printf("Packet number of %d: length packet is %d\n", i, msgs_streamer[i][1]);
        printf("ID = 0x%02X\n", ID);
        printf("DATA[0] = 0x%02X\n", DATA[0]);
        if ((ID != 0x20)
                || (DATA[0] != payload[0])
                || (DATA[3] != payload[3])
                || (DATA[5] != payload[5]))
        {
            printf(" %%TEST_FAILED%% time=0 testname=test5 (recvtest) message=Packet number of %d: length packet is %d\n", i, msgs_streamer[i][1]);
        }
    }
}

int main(int argc, char** argv)
{
    printf("%%SUITE_STARTING%% csmacdtest\n");
    printf("%%SUITE_STARTED%%\n");

    csma_init(&controller, &Sender);

    printf("%%TEST_STARTED%% test1 (csmacdtest)\n");
    test1();
    printf("%%TEST_FINISHED%% time=0 test1 (csmacdtest) \n");

    printf("%%TEST_STARTED%% test2 (csmacdtest)\n");
    test2();
    printf("%%TEST_FINISHED%% time=0 test2 (csmacdtest) \n");

    printf("%%TEST_STARTED%% test3 (csmacdtest)\n");
    test3();
    printf("%%TEST_FINISHED%% time=0 test3 (csmacdtest) \n");

    printf("%%TEST_STARTED%% test4 (csmacdtest)\n");
    test4();
    printf("%%TEST_FINISHED%% time=0 test4 (csmacdtest) \n");
    
    printf("%%TEST_STARTED%% test5 (csmacdtest)\n");
    test5();
    printf("%%TEST_FINISHED%% time=0 test5 (csmacdtest) \n");
	
    printf("%%SUITE_FINISHED%% time=0\n");

    return (EXIT_SUCCESS);
}

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   sendtest.c
 * Author: gusev_a
 *
 * Created on 9 октября 2018 г., 12:15
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "CSMACD.h"

CSMACDController_t controller;
uint8_t msg[] = { 
    0x32, 0x33, 0x21, 0x68, 0xF2, 0x22, 
    0x32, 0x33, 0x21, 0x68, 0xF2, 0x22 
};

/*
 * Simple C Test Suite
 */

void test1() {
    printf("sendtest test 1\n");
    PacketizeToSend(&controller, msg, 0x21, 6);
    while (csma_sender(&controller) != CSMACD_WAIT);
    csma_clock_cycle(&controller);
    csma_clock_cycle(&controller);
    csma_clock_cycle(&controller);
    csma_clock_cycle(&controller);
}

void test2() {
    printf("sendtest test 2\n");
    PacketizeToSend(&controller, msg, 0x21, 12);
    while (csma_sender(&controller) != CSMACD_WAIT);
    csma_clock_cycle(&controller);
    csma_clock_cycle(&controller);
    csma_clock_cycle(&controller);
    csma_clock_cycle(&controller);
}

int main(int argc, char** argv) {
    printf("%%SUITE_STARTING%% sendtest\n");
    printf("%%SUITE_STARTED%%\n");
    
    csma_init(&controller);

    printf("%%TEST_STARTED%% test1 (sendtest)\n");
    test1();
    printf("%%TEST_FINISHED%% time=0 test1 (sendtest) \n");

    printf("%%TEST_STARTED%% test2 (sendtest)\n");
    test2();
    printf("%%TEST_FINISHED%% time=0 test2 (sendtest) \n");

    printf("%%SUITE_FINISHED%% time=0\n");

    return (EXIT_SUCCESS);
}

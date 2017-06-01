/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   pocket_test.c
 * Author: xitre_000
 *
 * Created on 13 May 2016, 01:07
 */

#include <stdio.h>
#include <stdlib.h>
#include "../Packet.h"

/*
 * Simple C Test Suite
 */

uint8_t buffer[10] = {0x11, 0xf3, 0x32, 0x43, 0x54, 
                                0x11, 0x00, 0x00, 0x00, 0x00};
const uint8_t buffer2[10] = {0x11, 0xf3, 0x32, 0x43, 0x54, 
                                0x11, 0x00, 0x00, 0x00, 0x00};

void test1() {
    int i,j=0;
    if (!Packetize(buffer,6,10))
        printf("%%TEST_FAILED%% time=0 testname=test1 (pocket_test) message=Buffer too small\n");
    if (!DePacketize(buffer,10))
        printf("%%TEST_FAILED%% time=0 testname=test1 (pocket_test) message=Corrupted\n");
    for(i=0;i<10;i++)
        if (buffer[i] != buffer2[i]) j=1;
    if (j)
            printf("%%TEST_FAILED%% time=0 testname=test1 (pocket_test) message=Corrupted\n");
}

void test2() {
    int i,j=0;
    Packetize(buffer,6,10);
    Packetize(buffer,10,10);
    Packetize(buffer,14,10);
    DePacketize(buffer,18);
    DePacketize(buffer,14);
    DePacketize(buffer,10);
    for(i=0;i<10;i++)
        if (buffer[i] != buffer2[i]) j=1;
    if (j)
            printf("%%TEST_FAILED%% time=0 testname=test2 (pocket_test) message=Corrupted\n");
}

int main(int argc, char** argv) {
    printf("%%SUITE_STARTING%% pocket_test\n");
    printf("%%SUITE_STARTED%%\n");

    printf("%%TEST_STARTED%% test1 (pocket_test)\n");
    test1();
    printf("%%TEST_FINISHED%% time=0 test1 (pocket_test) \n");

    printf("%%TEST_STARTED%% test2 (pocket_test)\n");
    test2();
    printf("%%TEST_FINISHED%% time=0 test2 (pocket_test) \n");

    printf("%%SUITE_FINISHED%% time=0\n");

    return (EXIT_SUCCESS);
}

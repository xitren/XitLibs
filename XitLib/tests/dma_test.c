/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   dma_test.c
 * Author: xitre_000
 *
 * Created on 30 April 2016, 23:47
 */
#define CPU

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "DMAretransmitter.h"


/*
 * Simple C Test Suite
 */
DWORD dwStartTime;
DWORD dwElapsed;
int f1=0,f2=0,f3=0;

int func1(uint8_t *data,uint32_t len) {
    printf("Function1");
    int i;
    for (i=0;i < len;i++)
        printf(" %02X",data[i]);
    printf("\n");
    if ((len == 4) && (data[0] == 0x01) && (data[1] == 0x21) 
                    && (data[2] == 0x0B) && (data[3] == 0x56))
        f1=1;
    else
        f1=0;
    return 0;
}
int func2(uint8_t *data,uint32_t len) {
    printf("Function2");
    int i;
    for (i=0;i < len;i++)
        printf(" %02X",data[i]);
    printf("\n");
    if ((len == 1) && (data[0] == 0x12))
        f2=1;
    else
        f2=0;
    return 0;
}
int func3(uint8_t *data,uint32_t len) {
    printf("Function3");
    int i;
    for (i=0;i < len;i++)
        printf(" %02X",data[i]);
    printf("\n");
    if ((len == 3) && (data[0] == 0xB0) && (data[1] == 0x66) 
                    && (data[2] == 0x46))
        f3=1;
    else
        f3=0;
    return 0;
}

void AddQuery() {
    printf("dma_test test 1\n");
    
    DMAoccure_t test;
    test.bytes[0] = 0x00;
    test.bytes[1] = 0x20;
    test.bytes[2] = 0x0A;
    test.bytes[3] = 0x55;
    test.size = 4;
    test.tsize = 0;
    test.CallbackFunction = func1;
    DMAAddSample(&test);
    test.bytes[0] = 0x11;
    test.size = 1;
    test.tsize = 0;
    test.CallbackFunction = func2;
    DMAAddSample(&test);
    test.bytes[0] = 0xAF;
    test.bytes[1] = 0x65;
    test.bytes[2] = 0x45;
    test.size = 3;
    test.tsize = 0;
    test.CallbackFunction = func3;
    DMAAddSample(&test);
}

void ReadQuery() {
    printf("dma_test test 2\n");
        
    int i;
    uint8_t stat,tx_byte;
    for (i=0;i<20;i++)
    {
        tx_byte = DMAGetNext(&stat,tx_byte+1);
        if (stat)
            printf("%02X\n",tx_byte);
    }
    
    if (!((f1) && (f2) && (f3)))
        printf("%%TEST_FAILED%% time=0 testname=Execute_query_test (dma_test) message=error message sample\n");
}

int main(int argc, char** argv) {
    printf("%%SUITE_STARTING%% dma_test\n");
    printf("%%SUITE_STARTED%%\n");

    printf("%%TEST_STARTED%% Add_query_test (dma_test)\n");
    dwStartTime = GetTickCount();
    AddQuery();
    dwElapsed = GetTickCount() - dwStartTime;
    printf("%%TEST_FINISHED%% time=%d Add_query_test (dma_test) \n"
            , dwElapsed);

    printf("%%TEST_STARTED%% Execute_query_test (dma_test)\n");
    dwStartTime = GetTickCount();
    ReadQuery();
    dwElapsed = GetTickCount() - dwStartTime;
    printf("%%TEST_FINISHED%% time=%d Execute_query_test (dma_test) \n"
            , dwElapsed);

    printf("%%SUITE_FINISHED%% time=0\n");

    return (EXIT_SUCCESS);
}

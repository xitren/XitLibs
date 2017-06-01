/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   operation_test.c
 * Author: xitre_000
 *
 * Created on 07 July 2016, 00:01
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../XitLib/CommandModule.h"
#include "../XitLib/InOutBuffer.h"
#include "../XitLib/coap.h"
#include "../XitLib/ExtMemModule.h"
#include "../XitLib/StreamDataRecorder.h"
#include "../XitLib/DMAretransmitter.h"
#include "../XitLib/Handler.h"
#include <winsock2.h>

/*
 * Simple C Test Suite
 */
DWORD WINAPI ThreadFunc1s()
{
    while (1)
    {
        Sleep(1);
    }
    return 0;
}
DWORD WINAPI ThreadFunc250ms()
{
    while (1)
    {
        AddSample();
        Sleep(250);
//        printf("Sample\n");
    }
    return 0;
}

void test1() {
    printf("operation_test test 1\n");
    int i,j,k,l;
    int data[BUFFER_SAMPLE_SIZE*80];
    for (i=0;i<2000;i++)
    {
        l = GetDataReadyCnt(64,data);
        for (k=0;k<(l/BUFFER_SAMPLE_SIZE);k++)
        {
            if (k==0)
                printf("--------   --------   --------   --------   --------   --------   --------   --------   \n");
            for (j=0;j<BUFFER_SAMPLE_SIZE;j++)
            {
                printf("%08d   ",data[k*BUFFER_SAMPLE_SIZE+j]);
            }
            printf("\n");
        }
        Sleep(20);
    }
}

void test2() {
    printf("operation_test test 2\n");
    //printf("%%TEST_FAILED%% time=0 testname=test2 (operation_test) message=error message sample\n");
}

DWORD dwStartTime;
DWORD dwElapsed;

int main(int argc, char** argv) {
    
    DWORD IDThread; 
    HANDLE hThread; 
    
    InitHandler();
    EEGRecorderInit(0,250);
    
    uint32_t amplitude[7] = {10000,10000,100000,1000000,100000,10000,10000};
    uint32_t frequency[7] = {10,20,10,10,30,100,5};
    
    EEGTestInit(amplitude,frequency);
    
    printf("Command interface setted.\n");
        
    hThread = CreateThread(NULL, // default security attributes 
         0,                           // use default stack size 
         (LPTHREAD_START_ROUTINE) ThreadFunc1s, // thread function 
         NULL,                    // no thread function argument 
         0,                       // use default creation flags 
         &IDThread);              // returns thread identifier
    hThread = CreateThread(NULL, // default security attributes 
         0,                           // use default stack size 
         (LPTHREAD_START_ROUTINE) ThreadFunc250ms, // thread function 
         NULL,                    // no thread function argument 
         0,                       // use default creation flags 
         &IDThread);              // returns thread identifier
    
    Sleep(2500);
    
    printf("%%SUITE_STARTING%% ext_mem_test\n");
    printf("%%SUITE_STARTED%%\n");

    printf("%%TEST_STARTED%% test1 (test1)\n");
    dwStartTime = GetTickCount();
    test1();
    dwElapsed = GetTickCount() - dwStartTime;
    printf("%%TEST_FINISHED%% time=%d test1 (test1) \n", dwElapsed);

    printf("%%TEST_STARTED%% test2 (test2)\n");
    dwStartTime = GetTickCount();
    test2();
    dwElapsed = GetTickCount() - dwStartTime;
    printf("%%TEST_FINISHED%% time=%d test2 (test2) \n", dwElapsed);
    
    return (EXIT_SUCCESS);
}

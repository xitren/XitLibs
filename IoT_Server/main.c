/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: gusev_a
 *
 * Created on 31 Март 2016 г., 19:02
 */

#ifdef PLATFORM_WINDOWS
    #pragma comment ( lib, "ws2_32.lib" )
#endif
#include <stdio.h>
#include <stdlib.h>
#ifdef PLATFORM_WINDOWS
    #include <winsock2.h>
#endif
#include <stdbool.h>
#include <strings.h>

#include "ImageVisualise.h"
#include "coap.h"
#include "Handler.h"
#include "CommandModule.h"
#include "ExtFunctions.h"
#include "ImageVisualise.h"

char commandUpd[] = "/QUERY/UPDATE?repeat=3&type=0\0";

DWORD WINAPI ThreadFunc1s()
{
    while (1)
    {
        SecClockHandler();
        Sleep(1000);
    }
    return 0;
}
DWORD WINAPI ThreadFunc10s()
{
    while (1)
    {
//        function_beakon();
        //function_update();
        Sleep(10000);
    }
    return 0;
}
DWORD WINAPI ThreadFunc250ms()
{
    while (1)
    {
        SampleHandler();
        Sleep(4);
        devp300showme();
        //printf("%d, %d, %d ,%d\n",selection[0],selection[1],selection[2],selection[3]);
    }
    return 0;
}
DWORD WINAPI ThreadFunc500ms()
{
    while (1)
    {
        //devp300showme();
        Sleep(2);
    }
    return 0;
}
/*
 * 
 */
int main(int argc, char** argv) {

    DWORD IDThread; 
    HANDLE hThread; 
    
    InitUDP();
    printf("UDP ok.\n");
    InitImageP300();
    printf("Imager ok.\n");
    InitHandler(EEG);
    printf("Init XitLib ok.\n");
    EEGRecorderInit(0,250);
    printf("EEG recorder ok.\n");
    
    uint32_t amplitude[7] = {10000,10000,100000,1000000,100000,10000,10000};
    uint32_t frequency[7] = {10,20,10,10,30,100,5};
    
    EEGTestInit(amplitude,frequency);
    
    hThread = CreateThread(NULL, // default security attributes 
         0,                           // use default stack size 
         (LPTHREAD_START_ROUTINE) ThreadFunc1s, // thread function 
         NULL,                    // no thread function argument 
         0,                       // use default creation flags 
         &IDThread);              // returns thread identifier
    hThread = CreateThread(NULL, // default security attributes 
         0,                           // use default stack size 
         (LPTHREAD_START_ROUTINE) ThreadFunc10s, // thread function 
         NULL,                    // no thread function argument 
         0,                       // use default creation flags 
         &IDThread);              // returns thread identifier
    hThread = CreateThread(NULL, // default security attributes 
         0,                           // use default stack size 
         (LPTHREAD_START_ROUTINE) ThreadFunc250ms, // thread function 
         NULL,                    // no thread function argument 
         0,                       // use default creation flags 
         &IDThread);              // returns thread identifier
    hThread = CreateThread(NULL, // default security attributes 
         0,                           // use default stack size 
         (LPTHREAD_START_ROUTINE) ThreadFunc500ms, // thread function 
         NULL,                    // no thread function argument 
         0,                       // use default creation flags 
         &IDThread);              // returns thread identifier
    
//    function_update();
    //function_beakon();
    //CommandLineInterpreter(commandUpd);
    while(1)
    {
        UserProtocolHandler();
//        CalculationHandler();
        //umm_info(0,1);
    }
    return (EXIT_SUCCESS);
}


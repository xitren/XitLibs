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
#include <pthread.h>

#ifdef PI
    #include <linux/i2c-dev.h>
    #include <fcntl.h>
    #include <string.h>
    #include <sys/ioctl.h>
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <unistd.h>
#endif

/*
#include "ImageVisualise.h"
*/
#include "coap.h"
#include "Handler.h"
#include "CommandModule.h"

#define PORT 5683



uint32_t *ThreadFunc1s() {
    while (1) {
        SecClockHandler();
        usleep(1000000);
    }
    return 0;
}

uint32_t *ThreadFunc10s() {
    while (1) {
        //function_beakon();
/*
        function_update(0);
        usleep(100000); //usleep(10000000);
*/
    }
    return 0;
}

uint32_t *ThreadFunc250ms() {
    while (1) {
        AddSample();
        usleep(4000);
        //printf("Create third thread!");
    }
    return 0;
}
uint32_t *ThreadFuncUDP() {
    while (1) {
        UserProtocolHandlerThread();
    }
    return 0;
}
    
    
/*
 * 
 */
int main(int argc, char** argv) {
    uint32_t IDThread1,IDThread2,IDThread3,IDThread4; 
    //void *hThread;
    int result;
    pthread_t thread1;  //, thread2, thread3;
    pthread_t thread2;  //, thread2, thread3;
    pthread_t thread3;  //, thread2, thread3;
    pthread_t thread4;  //, thread2, thread3;
    
    InitUDP();
	printf("UDP ok.\n");
    //InitImageP300();
	printf("Imager ok.\n");
    InitHandler(BASESTATION);
	printf("Init XitLib ok.\n");
	SetVersion("32.0b");
    SetUpdateServer("10.10.30.40");
    EEGRecorderInit(0,250);
    printf("EEG recorder ok.\n");
    WriteMem(REG_LOG_LVL,5);
    
    AddCommand("/GET/PARTHASH", "</parthash>", PartHash); 
    AddCommand("/CALLBACK/PARTHASH", "</parthash>", CallbackPartHash);
    
    
    //WriteMem(REG_LOG_LVL,5);
    uint32_t amplitude[7] = {10000,10000,100000,1000000,100000,10000,10000};
    uint32_t frequency[7] = {10,20,10,10,30,100,5};
	
    printf("Command interface setted.\n");
    
	EEGTestInit(amplitude,frequency);
	
    result = pthread_create(&thread1,
            NULL, // default security attributes 
            ThreadFunc1s, // thread function 
            &IDThread1); // returns thread identifier
    if (result != 0) {
        printf("Create first thread!");
        return EXIT_FAILURE;
    }

    result = pthread_create(&thread2, // default security attributes 
            NULL, // use default stack size 
            ThreadFunc10s, // thread function 
            &IDThread2); // returns thread identifier
    if (result != 0) {
        printf("Create second thread!");
        return EXIT_FAILURE;
    }

    result = pthread_create(&thread3, // default security attributes 
            NULL, // use default stack size 
            ThreadFunc250ms, // thread function 
            &IDThread3); // returns thread identifier
    if (result != 0) {
        printf("Create third thread!");
        return EXIT_FAILURE;
    }
    
    result = pthread_create(&thread4,
            NULL, // default security attributes 
            ThreadFuncUDP, // thread function 
            &IDThread4); // returns thread identifier
    if (result != 0) {
        printf("Create first thread!");
        return EXIT_FAILURE;
    }
    
        function_beakon();
        setUpdateStatus(1);
        //PrintHashTable();
        //function_update();
        
    while(1)
    {

        
        UserOperationHandler();
        CalculationHandler();   
        UserProtocolHandler();
        //VideoFrameHandler();
        //ExecuteSchedule();
    }
    return (EXIT_SUCCESS);
}
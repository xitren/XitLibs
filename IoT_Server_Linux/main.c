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
#include <sys/socket.h>
#include <sys/uio.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <linux/netlink.h> 

#include "ImageVisualise.h"
#include "coap.h"
#include "Handler.h"
#include "CommandModule.h"

#define PORT 5683

uint32_t *ThreadFunc48ms() {
    while (1) {
        //printf("Create first thread!");
        //function_movement();
        usleep(48000);
    }
    return 0;
}
uint32_t *ThreadFunc1s() {
    while (1) {
        //printf("Create first thread!");
        SecClockHandler();
        usleep(1000000);
    }
    return 0;
}

uint32_t *ThreadFunc10s() {
    while (1) {
        //printf("Create second thread!");
        //function_beakon();
        //function_update(2);
        usleep(10000000); //10000
    }
    return 0;
}

uint32_t *ThreadFuncUDP() {
    while (1) {
        printf("UserProtocolHandlerThread\n");
        UserProtocolHandlerThread();
    }
    return 0;
}

uint32_t *ThreadFunc250ms() {
    while (1) {
        //printf("Create third thread!");
        AddSample();
        usleep(4000); //250
    }
    return 0;
}
        
/*
 * 
 */
int main(int argc, char** argv) {

    uint32_t IDThread1,IDThread2,IDThread3,IDThread4,IDThread5; 
    //void *hThread;
    int result;
    int thread1;  //, thread2, thread3;
    int thread2;  //, thread2, thread3;
    int thread3;  //, thread2, thread3;
    int thread4;  //, thread2, thread3;
    int thread5;  //, thread2, thread3;
    
    InitUDP();
    InitImageP300();
    InitHandler(BASESTATION);
    EEGRecorderInit(0,250);
    
    uint32_t amplitude[7] = {10000,10000,100000,1000000,100000,10000,10000};
    uint32_t frequency[7] = {10,20,10,10,30,100,5};
    printf("Command interface setted.\n");
    
    result = pthread_create(&thread4,
            NULL, // default security attributes 
            ThreadFunc48ms, // thread function 
            &IDThread4); // returns thread identifier
    if (result != 0) {
        printf("Create first thread!");
        return EXIT_FAILURE;
    }
    
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

    result = pthread_create(&thread5, // default security attributes 
            NULL, // use default stack size 
            ThreadFuncUDP, // thread function 
            &IDThread5); // returns thread identifier
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
    
    function_beakon();
    //function_update();
        
    while(1)
    {
        UserProtocolHandler();
        UserOperationHandler();
        CalculationHandler();
    }
    return (EXIT_SUCCESS);
}


/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   discovery_func_test.c
 * Author: xitre_000
 *
 * Created on 22 May 2016, 15:24
 */

#pragma comment ( lib, "ws2_32.lib" )
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "CommandModule.h"
#include "InOutBuffer.h"
#include "coap.h"
#include "ExtMemModule.h"
#include "StreamDataRecorder.h"
#include "DMAretransmitter.h"
#include "Handler.h"
#include <winsock2.h>

/*
 * Simple C Test Suite
 */

typedef unsigned char uint8_t;
#define PORT 5683
#define PORT_2 5684

int fd;

DWORD WINAPI StartSRVFunc()
{
//    #ifdef __INSIDE_CYGWIN__
//        system("start cmd /c ..\\IoT_Server\\dist\\Debug\\Cygwin-Windows\\iot_server.exe");
//    #else
//        system("start cmd /c ..\\IoT_Server\\dist\\Debug\\MinGW-Windows\\iot_server.exe");
//    #endif
    return 0;
}

DWORD WINAPI ThreadFunc()
{
    while (1)
    {
        ExtMemClock();
        coap_clock();
        Sleep(1000);
    }
    return 0;
}

DWORD WINAPI ThreadServer()
{
    #ifdef IPV6
        struct sockaddr_in6 servaddr, cliaddr;
    #else /* IPV6 */
        struct sockaddr_in servaddr, cliaddr;
    #endif /* IPV6 */

    #ifdef IPV6
        fd = socket(AF_INET6,SOCK_DGRAM,0);
    #else /* IPV6 */
        fd = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
        //printf("Socket create complete.\n");
    #endif /* IPV6 */

    #ifdef IPV6
        servaddr.sin6_family = AF_INET6;
        servaddr.sin6_addr = in6addr_any;
        servaddr.sin6_port = htons(PORT_2);
    #else /* IPV6 */
        servaddr.sin_family = AF_INET;
        servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
//        servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
        servaddr.sin_port = htons(PORT_2);
        memset(servaddr.sin_zero, '\0', sizeof(servaddr.sin_zero));
    #endif /* IPV6 */
    uint8_t buf[4096];
    uint8_t scratch_raw[4096];
    coap_rw_buffer_t scratch_buf = {scratch_raw, sizeof(scratch_raw)};
        
    int err = bind(fd,(struct sockaddr *)&servaddr, sizeof(servaddr));    
    printf("Socket bind complete %d port:%d.\n",err,PORT_2);
    
    while(1)
    {
        int n, rc;
        int len = sizeof(cliaddr);
        coap_packet_t pkt;

        n = recvfrom(fd, buf, sizeof(buf), 0, (struct sockaddr *)&cliaddr, &len);
                
        if (n >= 0)
        {
            #ifdef DEBUG
                printf("Received: ");
                coap_dump(buf, n, true);
                printf("\n");
            #endif
            if (0 != (rc = coap_parse(&pkt, buf, n)))
            {
                printf("Bad packet rc=%d\n", rc);
                coap_dumpHeader(&pkt.hdr);
            }
            else
            {
                size_t rsplen = sizeof(buf);
                coap_packet_t rsppkt;
                #ifdef DEBUG
                    coap_dumpPacket(&pkt);
                #endif
                coap_handle_req(&scratch_buf, &pkt, &rsppkt, 
                                CommandLineInterpreter, 
                                inet_ntoa(cliaddr.sin_addr));
                
                if (pkt.hdr.code < 5)
                {
                    if (0 != (rc = coap_build(buf, &rsplen, &rsppkt, NULL)))
                    {
                        //printf("coap_build failed rc=%d\n", rc);
                    }
                    else
                    {
                        #ifdef DEBUG
                            //printf("Sending: ");
                            //coap_dump(buf, rsplen, true);
                            //printf("\n");
                        #endif
                        #ifdef DEBUG
                            //coap_dumpPacket(&rsppkt);
                        #endif

                        sendto(fd, buf, rsplen, 0, (struct sockaddr *)&cliaddr, sizeof(cliaddr));
                    }
                }
            }
        }
    }
    return 0;
}

DWORD dwStartTime;
DWORD dwElapsed;
int f1=0,f2=0,f3=0;

/*
 * Simple C Test Suite
 */

void test1() {
    printf("discovery_func_test test 1\n");
    function_beakon();
}

void test2() {
    printf("discovery_func_test test 2\n");
    put_node_msg("10.9.91.10","</memory>;if=\"controller\",</clock>;if=\"controller\",</calculate/cycles/free>;if=\"controller\"");
//    put_node_msg("10.9.91.10","clock");
//    put_node_msg("10.9.91.10","extmemory");
//    put_node_msg("10.9.91.10","eeg");
//    print_node_and_func();
    put_node_msg("10.9.91.11","</memory>;if=\"controller\",</clock>;if=\"controller\",</extmemory>;if=\"controller\",</calculate/cycles/free>;if=\"controller\"");
//    put_node_msg("10.9.91.11","image");
//    print_node_and_func();
//    put_node_msg("10.9.91.15","image");
    print_node_and_func();
    //printf("%%TEST_FAILED%% time=0 testname=test2 (discovery_func_test) message=error message sample\n");
}

int main(int argc, char** argv) {
    char SERVERADDR[4];
    char buff[10*1014];

    printf("UDP Client Started\n");

    // Инициализация WinSock
    WORD wVersionRequested = MAKEWORD (2,2);
    WSADATA wsaData;
    int err = WSAStartup(wVersionRequested, &wsaData);
    if (err !=0) 
    {
        printf("WSAStartup error: %d\n",WSAGetLastError());
    }
    
    DWORD IDThread; 
    HANDLE hThread; 
    uint8_t *ter[10] = {"1Geurdo","2Geurdo","3Geurdo","4Geurdo","5Geurdo",
                        "6Geurdo","7Geurdo","8Geurdo","9Geurdo","10Geurdo"};
    uint32_t len[10] = {strlen(ter[0]), strlen(ter[1]), strlen(ter[2]), 
                        strlen(ter[3]), strlen(ter[4]), strlen(ter[5]), 
                        strlen(ter[6]), strlen(ter[7]), strlen(ter[8]), 
                        strlen(ter[9]) };
    uint32_t j,k;
    printf("Main\n");
    
    InitHandler();
    printf("Command interface setted.\n");
    
    hThread = CreateThread(NULL, // default security attributes 
         0,                           // use default stack size 
         (LPTHREAD_START_ROUTINE) ThreadFunc, // thread function 
         NULL,                    // no thread function argument 
         0,                       // use default creation flags 
         &IDThread);              // returns thread identifier
    hThread = CreateThread(NULL, // default security attributes 
         0,                           // use default stack size 
         (LPTHREAD_START_ROUTINE) ThreadServer, // thread function 
         NULL,                    // no thread function argument 
         0,                       // use default creation flags 
         &IDThread);              // returns thread identifier
           
    int i;
    Sleep(2000);
    
    printf("%%SUITE_STARTING%% discovery_func_test\n");
    printf("%%SUITE_STARTED%%\n");

    printf("%%TEST_STARTED%% test1 (discovery_func_test)\n");
    //test1();
    Sleep(2000);
    printf("%%TEST_FINISHED%% time=0 test1 (discovery_func_test) \n");

    printf("%%TEST_STARTED%% test2 (discovery_func_test)\n");
    test2();
    printf("%%TEST_FINISHED%% time=0 test2 (discovery_func_test) \n");

    printf("%%SUITE_FINISHED%% time=0\n");
    //ResetReq();

    return (EXIT_SUCCESS);
}

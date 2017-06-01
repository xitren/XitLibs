/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   ext_mem_test.c
 * Author: xitre_000
 *
 * Created on 01 May 2016, 00:29
 */

#pragma comment ( lib, "ws2_32.lib" )
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

typedef unsigned char uint8_t;
#define PORT 5683

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

//DWORD WINAPI ThreadServer()
//{    
//    int n, rc;
//    int len = sizeof(cliaddr);
//    coap_packet_t pkt;
//        
//    while(1)
//    {
//
//        n = recvfrom(fd, buf, sizeof(buf), 0, (struct sockaddr *)&cliaddr, &len);
//                
//        if (n >= 0)
//        {
//            #ifdef DEBUG
//                printf("Received: ");
//                coap_dump(buf, n, true);
//                printf("\n");
//            #endif
//            if (0 != (rc = coap_parse(&pkt, buf, n)))
//            {
//                printf("Bad packet rc=%d\n", rc);
//                coap_dumpHeader(&pkt.hdr);
//            }
//            else
//            {
//                size_t rsplen = sizeof(buf);
//                coap_packet_t rsppkt;
//                #ifdef DEBUG
//                    //coap_dumpPacket(&pkt);
//                #endif
//                coap_handle_req(&scratch_buf, &pkt, &rsppkt, 
//                                CommandLineInterpreter, 
//                                inet_ntoa(cliaddr.sin_addr));
//                
//                if (pkt.hdr.code < 5)
//                {
//                    if (0 != (rc = coap_build(buf, &rsplen, &rsppkt, NULL)))
//                    {
//                        //printf("coap_build failed rc=%d\n", rc);
//                    }
//                    else
//                    {
//                        #ifdef DEBUG
//                            //printf("Sending: ");
//                            //coap_dump(buf, rsplen, true);
//                            //printf("\n");
//                        #endif
//                        #ifdef DEBUG
//                            //coap_dumpPacket(&rsppkt);
//                        #endif
//
//                        sendto(fd, buf, rsplen, 0, (struct sockaddr *)&cliaddr, sizeof(cliaddr));
//                    }
//                }
//            }
//        }
//    }
//    return 0;
//}

DWORD dwStartTime;
DWORD dwElapsed;
int f1=0,f2=0,f3=0;

void test1() {
    uint32_t history_int_id = 10;
    uint32_t history_eeg_cnt = 0;
    int ret;
    //ClearExtMem();
    printf("ext_mem_test test 1\n");
    ret = CreateExtMemReq(0,&(history_eeg_cnt),history_int_id);
    if (ret < 0)
    {       
        dwElapsed = GetTickCount() - dwStartTime;
        printf("%%TEST_FAILED%% time=%d.%3d testname=create_and_delete_query (ext_mem_test) message=Server not responding\n"
            , dwElapsed/1000, dwElapsed - dwElapsed/1000);
        return;
    }
//    if (DeleteExtMemReq(history_int_id) < 0)
//    {
//        dwElapsed = GetTickCount() - dwStartTime;
//        printf("%%TEST_FAILED%% time=%d.%3d testname=create_and_delete_query (ext_mem_test) message=Record not found\n"
//            , dwElapsed/1000, dwElapsed - dwElapsed/1000);
//        return;
//    }
    f1 = 1;
}

void test2() {
    printf("ext_mem_test test 2\n");
    uint32_t stroke[1920];
    uint32_t strokelen = 1920;
    int i;
    int ret;
    ClearExtMem();
    for (i = 0; i < 1920; i++)
        stroke[i] = i;
    for (i = 0; i < 1680; i++)
    {
        ret = CreateExtMemReq((uint8_t *)stroke,&(strokelen),i+10);
        if (ret < 0)
        {       
            dwElapsed = GetTickCount() - dwStartTime;
            printf("%%TEST_FAILED%% time=%d.%3d testname=video_translation (ext_mem_test) message=Server not responding\n"
                , dwElapsed/1000, dwElapsed - dwElapsed/1000);
            return;
        }
        strokelen = 1920;
    }
    f2 = 1;
}

void test3() {
    printf("ext_mem_test test 3\n");
    int byN = 60;
    int i;
    uint32_t history_eeg[10];
    uint32_t history_eeg_cnt = 0;
    int intextid = 2;
    int32_t bufsa[14096];
    int ret;
    ClearExtMem();
    for (i = 0; i < 300; i++)
    {
            AddSample();
            if (GetCnt() >= byN)
            {
                int hlen = GetDataReadyCnt(byN,bufsa);
                hlen*=4;
                //EEG_dump((uint8_t *)bufsa, hlen);
                ret = CreateExtMemReq((uint8_t *)bufsa,&(hlen),
                        history_eeg[history_eeg_cnt++] = (intextid++));
                if (ret < 0)
                {       
                    dwElapsed = GetTickCount() - dwStartTime;
                    printf("%%TEST_FAILED%% time=%d.%3d testname=usial_eeg (ext_mem_test) message=Server not responding\n"
                        , dwElapsed/1000, dwElapsed - dwElapsed/1000);
                    return;
                }
                uint32_t _popid = AddHistoryExtId(intextid-1);
                history_eeg[history_eeg_cnt-1] = GetMemExtByInt(intextid-1);
                //DeleteExtMemReq(_popid);
            }
    }
    EEGPutExtMemReq((uint32_t*)history_eeg,history_eeg_cnt);
    f3 = 1;
}


void test4() {
    printf("ext_mem_test test 4\n");
    int ret;
//    if (!((f1) && (f2) && (f3)))
//    {       
//        dwElapsed = GetTickCount() - dwStartTime;
//        printf("%%TEST_FAILED%% time=%d.%3d testname=file_stored_eeg (ext_mem_test) message=Server not responding\n"
//            , dwElapsed/1000, dwElapsed - dwElapsed/1000);
//        return;
//    }
    ret = MakeEEGFromFile("220data.txt");
    if (ret < 0)
    {       
        dwElapsed = GetTickCount() - dwStartTime;
        printf("%%TEST_FAILED%% time=%d.%3d testname=file_stored_eeg (ext_mem_test) message=Server response error\n"
            , dwElapsed/1000, dwElapsed - dwElapsed/1000);
        return;
    }
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
         (LPTHREAD_START_ROUTINE) StartSRVFunc, // thread function 
         NULL,                    // no thread function argument 
         0,                       // use default creation flags 
         &IDThread);              // returns thread identifier
    
    Sleep(2000);
    
    hThread = CreateThread(NULL, // default security attributes 
         0,                           // use default stack size 
         (LPTHREAD_START_ROUTINE) ThreadFunc, // thread function 
         NULL,                    // no thread function argument 
         0,                       // use default creation flags 
         &IDThread);              // returns thread identifier
//    hThread = CreateThread(NULL, // default security attributes 
//         0,                           // use default stack size 
//         (LPTHREAD_START_ROUTINE) ThreadServer, // thread function 
//         NULL,                    // no thread function argument 
//         0,                       // use default creation flags 
//         &IDThread);              // returns thread identifier
    
    uint32_t amplitude[7] = {10000,10000,100000,1000000,100000,10000,10000};
    uint32_t frequency[7] = {10,20,10,10,30,100,5};
    
    EEGTestInit(amplitude,frequency);
           
    int i;
    
    printf("%%SUITE_STARTING%% ext_mem_test\n");
    printf("%%SUITE_STARTED%%\n");
    
    Interface_Callback();
    
    function_beakon();
    
    ProtocolHandler();
    ProtocolHandler();
    
    Interface_Memory();

//    //ResetExtMemReq();
//    Sleep(2000);
//    printf("%%TEST_STARTED%% test1 (ext_mem_test)\n");
//    dwStartTime = GetTickCount();
//    test1();
//    dwElapsed = GetTickCount() - dwStartTime;
//    printf("%%TEST_FINISHED%% time=%d create_and_delete_query (ext_mem_test) \n", dwElapsed);
//
//    ResetExtMemReq();
//    Sleep(2000);
//    printf("%%TEST_STARTED%% test2 (ext_mem_test)\n");
//    dwStartTime = GetTickCount();
//    //test2();
//    dwElapsed = GetTickCount() - dwStartTime;
//    printf("%%TEST_FINISHED%% time=%d video_translation (ext_mem_test) \n", dwElapsed);
//
//    ResetExtMemReq();
//    Sleep(2000);
//    printf("%%TEST_STARTED%% test3 (ext_mem_test)\n");
//    dwStartTime = GetTickCount();
//    //test3();
//    dwElapsed = GetTickCount() - dwStartTime;
//    printf("%%TEST_FINISHED%% time=%d usial_eeg (ext_mem_test) \n", dwElapsed);
//
//    ResetExtMemReq();
//    Sleep(2000);
//    printf("%%TEST_STARTED%% test4 (ext_mem_test)\n");
//    dwStartTime = GetTickCount();
//    //test4();
//    dwElapsed = GetTickCount() - dwStartTime;
//    printf("%%TEST_FINISHED%% time=%d file_stored_eeg (ext_mem_test) \n", dwElapsed);
//
//    printf("%%SUITE_FINISHED%% time=0\n");
    
    ResetReq();

    WSACleanup();
    return (EXIT_SUCCESS);
}

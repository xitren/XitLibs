/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   datasystem_test.c
 * Author: xitre
 *
 * Created on 29 июня 2017 г., 2:33
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "umm_malloc.h"
#include "CommandModule.h"
#include "LogModule.h"
#include "Handler.h"
#ifdef PLATFORM_WINDOWS
    #include <winsock2.h>
#endif

/*
 * Simple C Test Suite
 */
int count;

void work1() {
//    printf("work1\n");
    count += 1;
    return;
}
void work2() {
//    printf("work2\n");
    count += 2;
    return;
}
void work3() {
//    printf("work3\n");
    count += 3;
    return;
}

void test1() {
    printf("datasystem_test test 1\n");
    count = 0;
    AddToSchedule(work1);
    AddToSchedule(work2);
    AddToSchedule(work3);
    AddToSchedule(work3);
    AddToSchedule(work1);
    AddToSchedule(work2);
    AddToSchedule(work1);
    AddToSchedule(work2);
    ExecuteSchedule();
    if (count != 15)
        printf("%%TEST_FAILED%% time=0 testname=Schedule_Test (datasystem_test) message=Error\n");
    return;
}

void test2() {
    size_t i;
    int idx;
    int count_res = 0;
    printf("datasystem_test test 2\n");
    count = 0;
    
    for( idx=0; idx<3500; ++idx ) {
        switch( rand() % 4 ) {
            case  0:
                AddToSchedule(work1);
                count_res += 1;
                break;
            case  1:
                AddToSchedule(work2);
                count_res += 2;
                break;
            case  2:
                AddToSchedule(work3);
                count_res += 3;
                break;
            case  3:
                ExecuteSchedule();
                break;
            default: 
                break;
        }
    }
    ExecuteSchedule();
    if (count != count_res)
        printf("%%TEST_FAILED%% time=0 testname=Schedule_Random_Test (datasystem_test) message=Error\n");
    return;
}

void test3() {
    size_t i;
    int idx;
    int count_secs = 0;
    int count_samples = 0;
    printf("datasystem_test test 3\n");
    count = 0;
    
//    for( idx=0; idx<6553500; ++idx ) {
    for( idx=0; idx<3500; ++idx ) {
        switch( rand() % 16 ) {
            case  0:
            case  1:
            case  2:
            case  3:
            case  4:
            case  5:
            case  6:
                SecClockHandler();
                count_secs += 1;
                break;
            case  7:
            case  8:
            case  9:
            case  10:
            case  11:
            case  12:
            case  13:
            case  14:
                SampleHandler();
                count_samples += 1;
                break;
            case  15:
                ExecuteSchedule();
                break;
            default: 
                break;
        }
    }
    ExecuteSchedule();
    if (count_secs != GetClock())
        printf("%%TEST_FAILED%% time=0 testname=Schedule_Random_Work (datasystem_test) message=Clock_%d!=%d\n",
                count_secs,GetClock());
    if (count_samples != GetSamplesCnt())
        printf("%%TEST_FAILED%% time=0 testname=Schedule_Random_Work (datasystem_test) message=Samples_%d!=%d\n",
                count_samples,GetSamplesCnt());
    return;
}

void test4() {
    size_t i;
    int idx;
    int count_secs = 0;
    int count_samples = 0;
    ParameterList_t TempParam;
    printf("datasystem_test test 4\n");
    count = 0;
    
    TempParam.NumberofParameters = 4;
    TempParam.Params[0].strParam = "size";
    TempParam.Params[0].intParam = 0;
    TempParam.Params[1].strParam = "1024";
    TempParam.Params[1].intParam = 1024;
    TempParam.Params[2].strParam = "type";
    TempParam.Params[2].intParam = 0;
    TempParam.Params[3].strParam = "1";
    TempParam.Params[3].intParam = 1;
    Update(&TempParam);
    
    scratch_buf.len = 4096;
    if (opt_part.num == 0)
        printf("no parts\n");
    else
    {
//        coap_make_response(&scratch_buf, &rsppkt, &opt_part,
//            (uint8_t*) bufsa, size_parts_cur,
//            0, 0, 0, COAP_RSPCODE_CONTENT,
//            content_type);
        opt_part.num = 0;
    }
//    if (0 != (coap_build(scratch_raw, &rsplen, &rsppkt, NULL, NULL))) {
//        printf("coap_build failed\r\n\r");
//    } else {
        #ifdef DEBUG
            DBG_LOG_DEBUG("Sending: ");
            coap_dump(bufsa, size_parts_cur, 1);
        #endif
//    }
//    if (count_secs != GetClock())
//        printf("%%TEST_FAILED%% time=0 testname=Schedule_Update_Msg (datasystem_test) message=Clock_%d!=%d\n",
//                count_secs,GetClock());
//    if (count_samples != GetSamplesCnt())
//        printf("%%TEST_FAILED%% time=0 testname=Schedule_Update_Msg (datasystem_test) message=Samples_%d!=%d\n",
//                count_samples,GetSamplesCnt());
    return;
}

void test5() {
    size_t i;
    int idx;
    int count_secs = 0;
    int count_samples = 0;
    ParameterList_t TempParam;
    printf("datasystem_test test 5\n");
    count = 0;
    FILE *fp;
    
    while ((fp = fopen("Updater.sh","rb")) == NULL) {
    }
    printf("Updater.sh located\n");
    fclose(fp);
    usleep(3000); 
    printf("Updater.sh deleting\n");
    remove("Updater.sh");
    return;
}

uint32_t *ThreadFuncUDP() {
    while (1) {
//        printf("UserProtocolHandlerThread\n");
//        UserProtocolHandlerThread();
        usleep(10000); 
        function_update(0);
    }
    return 0;
}

uint32_t *ThreadFuncCycle() {
    while (1) {
        UserProtocolHandler();
        UserOperationHandler();
        CalculationHandler();
    }
    return 0;
}

int main(int argc, char** argv) {
    uint32_t IDThread1,IDThread2; 
    int result;
    int thread1;
    int thread2; 
    clock_t t,tl;
    
    InitUDP();
    InitHandler(BASESTATION);
    EEGRecorderInit(0,250);
    
    printf("%%SUITE_STARTING%% datasystem_test\n");
    printf("%%SUITE_STARTED%%\n");
    t = clock();

    printf("%%TEST_STARTED%% Schedule_Test (datasystem_test)\n");
    tl = clock();
    test1();
    tl = clock() - tl;
    printf("%%TEST_FINISHED%% time=%f Schedule_Test (datasystem_test) \n",
                                    ((float)tl)/CLOCKS_PER_SEC);

    printf("%%TEST_STARTED%% Schedule_Random_Test (datasystem_test)\n");
    tl = clock();
    test2();
    tl = clock() - tl;
    printf("%%TEST_FINISHED%% time=%f Schedule_Random_Test (datasystem_test) \n",
                                    ((float)tl)/CLOCKS_PER_SEC);

    printf("%%TEST_STARTED%% Schedule_Random_Work (datasystem_test)\n");
    tl = clock();
    test3();
    tl = clock() - tl;
    printf("%%TEST_FINISHED%% time=%f Schedule_Random_Work (datasystem_test) \n",
                                    ((float)tl)/CLOCKS_PER_SEC);

    printf("%%TEST_STARTED%% Schedule_Update_Msg (datasystem_test)\n");
    tl = clock();
    test4();
    tl = clock() - tl;
    printf("%%TEST_FINISHED%% time=%f Schedule_Update_Msg (datasystem_test) \n",
                                    ((float)tl)/CLOCKS_PER_SEC);

    WriteMem(REG_LOG_LVL,7);
    //startUpdate();
    updateStatus=1;
    WriteMem(REG_UPD_File,1);
    
    result = pthread_create(&thread1,
            NULL, // default security attributes 
            ThreadFuncCycle, // thread function 
            &IDThread1); // returns thread identifier
    if (result != 0) {
        printf("Create first thread!");
        return EXIT_FAILURE;
    }

    result = pthread_create(&thread2, // default security attributes 
            NULL, // use default stack size 
            ThreadFuncUDP, // thread function 
            &IDThread2); // returns thread identifier
    if (result != 0) {
        printf("Create second thread!");
        return EXIT_FAILURE;
    } 
    
    printf("%%TEST_STARTED%% Schedule_Update_File (datasystem_test)\n");
    tl = clock();
    test5();
    WriteMem(REG_LOG_LVL,7);
    tl = clock() - tl;
    printf("%%TEST_FINISHED%% time=%f Schedule_Update_File (datasystem_test) \n",
                                    ((float)tl)/CLOCKS_PER_SEC);

    t = clock() - t;
    printf("%%SUITE_FINISHED%% time=%f\n",
                                    ((float)tl)/CLOCKS_PER_SEC);

    return (EXIT_SUCCESS);
}

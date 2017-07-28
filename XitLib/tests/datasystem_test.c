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

int main(int argc, char** argv) {
    clock_t t,tl;
    
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

    t = clock() - t;
    printf("%%SUITE_FINISHED%% time=%f\n",
                                    ((float)tl)/CLOCKS_PER_SEC);

    return (EXIT_SUCCESS);
}

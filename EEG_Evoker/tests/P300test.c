/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   P300test.c
 * Author: xitren
 *
 * Created on 14 March 2017, 01:59
 */

#include <stdio.h>
#include <stdlib.h>

#include "ImageVisualise.h"
#include "Windows.h"

DWORD dwStartTime;
DWORD dwElapsed;
/*
 * Simple C Test Suite
 */

void test1() {
    printf("P300test test 1\n");
    InitImageP300();
//        printf("%%TEST_FAILED%% time=0 testname=Execute_query_test (dma_test) message=error message sample\n");
}

int main(int argc, char** argv) {
    printf("%%SUITE_STARTING%% P300test\n");
    printf("%%SUITE_STARTED%%\n");
    
    printf("Memory use: %d\n",MEM_USE);

    printf("%%TEST_STARTED%% test1 (P300test)\n");
    dwStartTime = GetTickCount();
    test1();
    dwElapsed = GetTickCount() - dwStartTime;
    printf("%%TEST_FINISHED%% time=%d test1 (P300test)\n",dwElapsed);

    printf("%%SUITE_FINISHED%% time=%d\n",dwElapsed);
    return (0);
}

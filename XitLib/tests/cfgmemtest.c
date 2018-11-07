/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   cfgmemtest.c
 * Author: gusev_a
 *
 * Created on 7 ноября 2018 г., 15:29
 */

#include <stdio.h>
#include <stdlib.h>
#include "ConfigMem.h"

/*
 * Simple C Test Suite
 */

void test1() {
    printf("cfgmemtest test 1\n");
    InitCfgMem();
    uint32_t val1 = ReadMem(REG_CRC);
    WriteMem(REG_SHOW_STIM_NUM,1000);
    WriteMem(REG_SHOW_TARG_NUM,18);
    WriteMem(REG_SHOW_STIM_NUM,16);
    WriteMem(REG_SHOW_TARG_NUM,4);
    uint32_t val2 = ReadMem(REG_CRC);
    if (val1 != val2)
        printf("%%TEST_FAILED%% time=0 testname=test1 (cfgmemtest) message=error message sample\n");
}

void test2() {
    printf("cfgmemtest test 2\n");
//    printf("%%TEST_FAILED%% time=0 testname=test2 (cfgmemtest) message=error message sample\n");
}

int main(int argc, char** argv) {
    printf("%%SUITE_STARTING%% cfgmemtest\n");
    printf("%%SUITE_STARTED%%\n");

    printf("%%TEST_STARTED%% test1 (cfgmemtest)\n");
    test1();
    printf("%%TEST_FINISHED%% time=0 test1 (cfgmemtest) \n");

    printf("%%TEST_STARTED%% test2 (cfgmemtest)\n");
    test2();
    printf("%%TEST_FINISHED%% time=0 test2 (cfgmemtest) \n");

    printf("%%SUITE_FINISHED%% time=0\n");

    return (EXIT_SUCCESS);
}

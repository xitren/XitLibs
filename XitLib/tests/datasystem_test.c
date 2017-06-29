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
#include "umm_malloc.h"
#include "ExtFunctions_datasystem.h"

/*
 * Simple C Test Suite
 */

void test1() {
    printf("datasystem_test test 1\n");
}

void test2() {
    printf("datasystem_test test 2\n");
    //printf("%%TEST_FAILED%% time=0 testname=test2 (datasystem_test) message=error message sample\n");
}

int main(int argc, char** argv) {
    printf("%%SUITE_STARTING%% datasystem_test\n");
    printf("%%SUITE_STARTED%%\n");

    printf("%%TEST_STARTED%% test1 (datasystem_test)\n");
    test1();
    printf("%%TEST_FINISHED%% time=0 test1 (datasystem_test) \n");

    printf("%%TEST_STARTED%% test2 (datasystem_test)\n");
    test2();
    printf("%%TEST_FINISHED%% time=0 test2 (datasystem_test) \n");

    printf("%%SUITE_FINISHED%% time=0\n");

    return (EXIT_SUCCESS);
}

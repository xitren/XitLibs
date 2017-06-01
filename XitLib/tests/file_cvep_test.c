/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   file_cvep_test.c
 * Author: xitre_000
 *
 * Created on 03 May 2016, 03:32
 */

#include <stdio.h>
#include <stdlib.h>
#include "../cVEP/cvepv4.h"
#include "StreamDataRecorder.h"

float successRes;
float falseRes;

/*
 * Simple C Test Suite
 */
int cvep_callback(int *data,uint32_t len) {
    signed char result; 
    int learn;
    cveprun(data, &result, &learn, &successRes, &falseRes);
    return 0;
}

void test1() {
    printf("file_cvep_test test 1\n");
    cvepv4_initialize();
    WorkEEGFromFile("220data.txt",cvep_callback);
    printf("Successed:%f, Failed:%f\n",
                        successRes,falseRes);
}
void test2() {
    printf("file_cvep_test test 2\n");
    cvepv4_initialize();
    WorkEEGFromFile("222data.txt",cvep_callback);
    printf("Successed:%f, Failed:%f\n",
                        successRes,falseRes);
}
void test3() {
    printf("file_cvep_test test 3\n");
    cvepv4_initialize();
    WorkEEGFromFile("257data.txt",cvep_callback);
    printf("Successed:%f, Failed:%f\n",
                        successRes,falseRes);
}

int main(int argc, char** argv) {
    printf("%%SUITE_STARTING%% file_cvep_test\n");
    printf("%%SUITE_STARTED%%\n");

    printf("%%TEST_STARTED%% test1 (file_cvep_test)\n");
    test1();
    printf("%%TEST_FINISHED%% time=0 record220 (file_cvep_test) \n");

    printf("%%TEST_STARTED%% test2 (file_cvep_test)\n");
    test2();
    printf("%%TEST_FINISHED%% time=0 record222 (file_cvep_test) \n");

    printf("%%TEST_STARTED%% test3 (file_cvep_test)\n");
    test3();
    printf("%%TEST_FINISHED%% time=0 record257 (file_cvep_test) \n");

    printf("%%SUITE_FINISHED%% time=0\n");

    return (EXIT_SUCCESS);
}

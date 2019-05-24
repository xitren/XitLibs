/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   distcalctest.c
 * Author: gusev_a
 *
 * Created on 12 ноября 2018 г., 18:49
 */

#include <stdio.h>
#include <stdlib.h>

#include "xitlibtypes.h"
#include "CommandModule.h"
#include "DistCalc.h"

uint8_t buffer_test[1000];
int size = 1000;
ParameterList_t params;

/*
 * Simple C Test Suite
 */

void test1() {
    printf("distcalctest test 1\n");
    size = 1000;
    ClockCommand(Method_GET,Media_XML,&params,buffer_test,(uint32_t *)&size,1000);
    printf((char *)buffer_test);
    printf("Message size: %d\n",size);
    ClockCommand(Method_PUT,Media_XML,&params,buffer_test,(uint32_t *)&size,1000);
    printf((char *)buffer_test);
    printf("Message size: %d\n",size);
    size = 1000;
    ClockCommand(Method_GET,Media_TEXT,&params,buffer_test,(uint32_t *)&size,1000);
    printf((char *)buffer_test);
    printf("Message size: %d\n",size);
    ClockCommand(Method_PUT,Media_TEXT,&params,buffer_test,(uint32_t *)&size,1000);
    printf((char *)buffer_test);
    printf("Message size: %d\n",size);
    size = 1000;
    ClockCommand(Method_GET,Media_BYTE,&params,buffer_test,(uint32_t *)&size,1000);
    printf((char *)buffer_test);
    printf("Message size: %d\n",size);
    ClockCommand(Method_PUT,Media_BYTE,&params,buffer_test,(uint32_t *)&size,1000);
    printf((char *)buffer_test);
    printf("Message size: %d\n",size);
    ClockCommand(Method_RESET,Media_XML,&params,buffer_test,(uint32_t *)&size,1000);
    printf((char *)buffer_test);
    printf("Message size: %d\n",size);
    ClockCommand(Method_RESET,Media_TEXT,&params,buffer_test,(uint32_t *)&size,1000);
    printf((char *)buffer_test);
    printf("Message size: %d\n",size);
    ClockCommand(Method_RESET,Media_BYTE,&params,buffer_test,(uint32_t *)&size,1000);
    printf((char *)buffer_test);
    printf("Message size: %d\n",size);
    ClockCommand(Method_GET,Media_JSON,&params,buffer_test,(uint32_t *)&size,1000);
    printf((char *)buffer_test);
    printf("Message size: %d\n",size);
}

void test2() {
    printf("distcalctest test 2\n");
    size = 1000;
    CalculationFreeCycles(Method_GET,Media_XML,&params,buffer_test,(uint32_t *)&size,1000);
    printf((char *)buffer_test);
    printf("Message size: %d\n",size);
    size = 1000;
    CalculationFreeCycles(Method_GET,Media_TEXT,&params,buffer_test,(uint32_t *)&size,1000);
    printf((char *)buffer_test);
    printf("Message size: %d\n",size);
    size = 1000;
    CalculationFreeCycles(Method_GET,Media_BYTE,&params,buffer_test,(uint32_t *)&size,1000);
    printf((char *)buffer_test);
    printf("Message size: %d\n",size);
    CalculationFreeCycles(Method_PUT,Media_BYTE,&params,buffer_test,(uint32_t *)&size,1000);
    printf((char *)buffer_test);
    printf("Message size: %d\n",size);
    CalculationFreeCycles(Method_RESET,Media_BYTE,&params,buffer_test,(uint32_t *)&size,1000);
    printf((char *)buffer_test);
    printf("Message size: %d\n",size);
}

void test3() {
    printf("distcalctest test 3\n");
    size = 1000;
    CalculationMaxCycles(Method_GET,Media_XML,&params,buffer_test,(uint32_t *)&size,1000);
    printf((char *)buffer_test);
    printf("Message size: %d\n",size);
    size = 1000;
    CalculationMaxCycles(Method_GET,Media_TEXT,&params,buffer_test,(uint32_t *)&size,1000);
    printf((char *)buffer_test);
    printf("Message size: %d\n",size);
    size = 1000;
    CalculationMaxCycles(Method_GET,Media_BYTE,&params,buffer_test,(uint32_t *)&size,1000);
    printf((char *)buffer_test);
    printf("Message size: %d\n",size);
    CalculationMaxCycles(Method_PUT,Media_BYTE,&params,buffer_test,(uint32_t *)&size,1000);
    printf((char *)buffer_test);
    printf("Message size: %d\n",size);
    CalculationMaxCycles(Method_RESET,Media_BYTE,&params,buffer_test,(uint32_t *)&size,1000);
    printf((char *)buffer_test);
    printf("Message size: %d\n",size);
}

void test4() {
    printf("distcalctest test 4\n");
    size = 1000;
    CalculationPercentCycles(Method_GET,Media_XML,&params,buffer_test,(uint32_t *)&size,1000);
    printf((char *)buffer_test);
    printf("Message size: %d\n",size);
    size = 1000;
    CalculationPercentCycles(Method_GET,Media_TEXT,&params,buffer_test,(uint32_t *)&size,1000);
    printf((char *)buffer_test);
    printf("Message size: %d\n",size);
    size = 1000;
    CalculationPercentCycles(Method_GET,Media_BYTE,&params,buffer_test,(uint32_t *)&size,1000);
    printf((char *)buffer_test);
    printf("Message size: %d\n",size);
    CalculationPercentCycles(Method_PUT,Media_BYTE,&params,buffer_test,(uint32_t *)&size,1000);
    printf((char *)buffer_test);
    printf("Message size: %d\n",size);
    CalculationPercentCycles(Method_RESET,Media_BYTE,&params,buffer_test,(uint32_t *)&size,1000);
    printf((char *)buffer_test);
    printf("Message size: %d\n",size);
}

int main(int argc, char** argv) {
    printf("%%SUITE_STARTING%% distcalctest\n");
    printf("%%SUITE_STARTED%%\n");

    printf("%%TEST_STARTED%% test1 (distcalctest)\n");
    test1();
    printf("%%TEST_FINISHED%% time=0 test1 (distcalctest) \n");

    printf("%%TEST_STARTED%% test2 (distcalctest)\n");
    test2();
    printf("%%TEST_FINISHED%% time=0 test2 (distcalctest) \n");

    printf("%%TEST_STARTED%% test3 (distcalctest)\n");
    test3();
    printf("%%TEST_FINISHED%% time=0 test3 (distcalctest) \n");

    printf("%%TEST_STARTED%% test4 (distcalctest)\n");
    test4();
    printf("%%TEST_FINISHED%% time=0 test4 (distcalctest) \n");

    printf("%%SUITE_FINISHED%% time=0\n");

    return (EXIT_SUCCESS);
}

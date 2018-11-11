/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   circlebuffertest.c
 * Author: xitre
 *
 * Created on 10 ноября 2018 г., 20:07
 */

#include <stdio.h>
#include <stdlib.h>
#include "circularbuffer.h"
#include "CommandModule.h"

CircularBuffer_t buffer;
uint8_t storage[2048];

/*
 * Simple C Test Suite
 */

void test1() {
    int i;
    printf("circlebuffertest test push\n");
    uint32_t Data_sample[8];
    for(i=0;i < 8;i++)
    {
        Data_sample[i] = ( circularbuffer_get_first_index(&buffer)+1 );
    }
    circularbuffer_push(&buffer,(void *)Data_sample);
}
void test2() {
    enum cc_stat ret;
    printf("circlebuffertest test pull\n");
    uint32_t Data_sample[8];
    ret = circularbuffer_pull(&buffer,(void *)Data_sample);
    if (ret == CC_OK)
        printf("%d %d %d %d %d %d %d %d \n",
                Data_sample[0],Data_sample[1],
                Data_sample[2],Data_sample[3],
                Data_sample[4],Data_sample[5],
                Data_sample[6],Data_sample[7]
                );
    else
        printf("buffer depleted\n");
}

int main(int argc, char** argv) {
    printf("%%SUITE_STARTING%% circlebuffertest\n");
    printf("%%SUITE_STARTED%%\n");
    
    int i;
    circularbuffer_new(
            &buffer,
            8 * sizeof(uint32_t),
            storage,
            sizeof(storage)
    );

    printf("%%TEST_STARTED%% test1 (circlebuffertest)\n");
    for(i=0;i < 1000;i++)
    {
        test1();
    }
    printf("%%TEST_FINISHED%% time=0 test1 (circlebuffertest) \n");

    printf("%%TEST_STARTED%% test2 (circlebuffertest)\n");
    for(i=0;i < 1001;i++)
    {
        test2();
    }
    printf("%%TEST_FINISHED%% time=0 test2 (circlebuffertest) \n");
    
    printf("%%TEST_STARTED%% test3 (circlebuffertest)\n");
    for(i=0;i < 1000;i++)
    {
        test1();
    }
    printf("%%TEST_FINISHED%% time=0 test3 (circlebuffertest) \n");

    printf("%%TEST_STARTED%% test4 (circlebuffertest)\n");
    for(i=0;i < 1001;i++)
    {
        test2();
    }
    printf("%%TEST_FINISHED%% time=0 test4 (circlebuffertest) \n");

    printf("%%SUITE_FINISHED%% time=0\n");

    return (EXIT_SUCCESS);
}

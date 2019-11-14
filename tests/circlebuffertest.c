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

CircularBuffer_t buffer_test;
CircularBufferItem_t storage[400];

/*
 * Simple C Test Suite
 */

void test1() {
	int i;
	printf("circlebuffertest test push\n");
	CircularBufferItem_t Data_sample;
	int ptr = circularbuffer_get_first_index(&buffer_test) + 1;
	printf("first_index %d\n", ptr);
	for (i = 0; i < 8; i++) {
		Data_sample.Channel[i] = ptr;
	}
	circularbuffer_push(&buffer_test, &Data_sample);
}

void test2() {
	enum cc_stat ret;
	printf("circlebuffertest test pull\n");
	CircularBufferItem_t Data_sample;
	ret = circularbuffer_pull(&buffer_test, &Data_sample);
	if (ret == CC_OK)
		printf("%d %d %d %d %d %d %d %d \n",
			Data_sample.Channel[0], Data_sample.Channel[1],
			Data_sample.Channel[2], Data_sample.Channel[3],
			Data_sample.Channel[4], Data_sample.Channel[5],
			Data_sample.Channel[6], Data_sample.Channel[7]
			);
	else
		printf("buffer depleted\n");
}

int main(int argc, char** argv) {
	printf("%%SUITE_STARTING%% circlebuffertest\n");
	printf("%%SUITE_STARTED%%\n");

	int i;
	circularbuffer_new(
			&buffer_test,
			(CircularBufferItem_t *) storage,
			20
			);

	printf("%%TEST_STARTED%% test1 (circlebuffertest)\n");
	for (i = 0; i < 1000; i++) {
		test1();
	}
	printf("%%TEST_FINISHED%% time=0 test1 (circlebuffertest) \n");

	printf("%%TEST_STARTED%% test2 (circlebuffertest)\n");
	for (i = 0; i < 1001; i++) {
		test2();
	}
	printf("%%TEST_FINISHED%% time=0 test2 (circlebuffertest) \n");

	printf("%%TEST_STARTED%% test3 (circlebuffertest)\n");
	for (i = 0; i < 1000; i++) {
		test1();
	}
	printf("%%TEST_FINISHED%% time=0 test3 (circlebuffertest) \n");

	printf("%%TEST_STARTED%% test4 (circlebuffertest)\n");
	for (i = 0; i < 1001; i++) {
		test2();
	}
	printf("%%TEST_FINISHED%% time=0 test4 (circlebuffertest) \n");

	printf("%%TEST_STARTED%% test5 (circlebuffertest)\n");
	for (i = 0; i < 3; i++) {
		test1();
		test2();
	}
	for (i = 0; i < 3; i++) {
		test1();
	}
	for (i = 0; i < 3; i++) {
		test2();
	}
	printf("%%TEST_FINISHED%% time=0 test5 (circlebuffertest) \n");

	printf("%%SUITE_FINISHED%% time=0\n");

	return (EXIT_SUCCESS);
}

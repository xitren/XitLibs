/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   streamtest.c
 * Author: xitre
 *
 * Created on 10 ноября 2018 г., 17:23
 */

#include <stdio.h>
#include <stdlib.h>

#include "xitlibtypes.h"
#include "CommandModule.h"
#include "StreamDataRecorder.h"

CircularBufferItem_t storage[48];
uint8_t buffer_str[100000];
uint32_t size = 100000;
ParameterList_t params;

/*
 * Simple C Test Suite
 */

void test1()
{
	printf("streamtest test 1\n");
	StreamRecorderCommand(Method_GET, Media_XML, &params, buffer_str, &size, 100000);
	printf((char *) buffer_str);
	printf("Message size: %ld\n", size);
}

void test2()
{
	printf("streamtest test 2\n");
	StreamRecorderCommand(Method_GET, Media_TEXT, &params, buffer_str, &size, 100000);
	printf((char *) buffer_str);
	printf("\n");
	printf("Message size: %ld\n", size);
}

void test3()
{
	printf("streamtest test 3\n");
	StreamRecorderCommand(Method_GET, Media_BYTE, &params, buffer_str, &size, 100000);
	printf("%d %d %d %d \n",
			buffer_str[0], buffer_str[1],
			buffer_str[2], buffer_str[3]
			);
	printf("Message size: %ld\n", size);
}

void test4()
{
	printf("streamtest test 4\n");
	StreamRecorderCommand(Method_GET, Media_JSON, &params, buffer_str, &size, 100000);
	printf((char *) buffer_str);
	printf("Message size: %ld\n", size);
}

int main(int argc, char** argv)
{
	printf("%%SUITE_STARTING%% streamtest\n");
	printf("%%SUITE_STARTED%%\n");

	int i;
	InitStreamRecorder(storage, 48, 250, 8, 1);
	for (i = 0; i < 1000; i++)
		AddSample();

	printf("%%TEST_STARTED%% test1 (streamtest)\n");
	test1();
	printf("%%TEST_FINISHED%% time=0 test1 (streamtest) \n");

	printf("%%TEST_STARTED%% test2 (streamtest)\n");
	test2();
	printf("%%TEST_FINISHED%% time=0 test2 (streamtest) \n");

	printf("%%TEST_STARTED%% test3 (streamtest)\n");
	test3();
	printf("%%TEST_FINISHED%% time=0 test3 (streamtest) \n");

	printf("%%TEST_STARTED%% test4 (streamtest)\n");
	test4();
	printf("%%TEST_FINISHED%% time=0 test4 (streamtest) \n");

	printf("%%SUITE_FINISHED%% time=0\n");

	return (EXIT_SUCCESS);
}


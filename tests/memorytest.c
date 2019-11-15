/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   memorytest.c
 * Author: xitre
 *
 * Created on 10 ноября 2018 г., 16:14
 */

#include <stdio.h>
#include <stdlib.h>

#include "ConfigMem.h"
#include "xitlibtypes.h"
#include "CommandModule.h"

uint8_t buffer_test[1000];
int size = 1000;
ParameterList_t params;

/*
 * Simple C Test Suite
 */

void test1()
{
	printf("memorytest test 1\n");
	size = 1000;
	MemoryCommand(Method_GET, Media_XML, &params, buffer_test, (uint32_t *) & size, 1000);
	printf((char *) buffer_test);
	printf("Message size: %d\n", size);
	MemoryCommand(Method_PUT, Media_XML, &params, buffer_test, (uint32_t *) & size, 1000);
}

void test2()
{
	printf("memorytest test 2\n");
	size = 1000;
	MemoryCommand(Method_GET, Media_TEXT, &params, buffer_test, (uint32_t *) & size, 1000);
	printf((char *) buffer_test);
	printf("\n");
	printf("Message size: %d\n", size);
	MemoryCommand(Method_PUT, Media_TEXT, &params, buffer_test, (uint32_t *) & size, 1000);
}

void test3()
{
	printf("memorytest test 3\n");
	size = 1000;
	MemoryCommand(Method_GET, Media_BYTE, &params, buffer_test, (uint32_t *) & size, 1000);
	printf("%02X %02X %02X %02X \n",
			(uint8_t) buffer_test[0], (uint8_t) buffer_test[1],
			(uint8_t) buffer_test[2], (uint8_t) buffer_test[3]
			);
	printf("Message size: %d\n", size);
}

void test4()
{
	printf("memorytest test 4\n");
	size = 1000;
	MemoryCommand(Method_GET, Media_JSON, &params, buffer_test, (uint32_t *) & size, 1000);
	printf((char *) buffer_test);
	printf("Message size: %d\n", size);
}

int main(int argc, char** argv)
{
	printf("%%SUITE_STARTING%% memorytest\n");
	printf("%%SUITE_STARTED%%\n");

	InitCfgMem();
	params.NumberofParameters = 0;
	add_parameter(&params, "address", REG_CRC);
	printf("%%TEST_STARTED%% test1 (memorytest)\n");
	test1();
	printf("%%TEST_FINISHED%% time=0 test1 (memorytest) \n");

	printf("%%TEST_STARTED%% test2 (memorytest)\n");
	test2();
	printf("%%TEST_FINISHED%% time=0 test2 (memorytest) \n");

	printf("%%TEST_STARTED%% test3 (memorytest)\n");
	test3();
	printf("%%TEST_FINISHED%% time=0 test3 (memorytest) \n");

	printf("%%TEST_STARTED%% test4 (memorytest)\n");
	test4();
	printf("%%TEST_FINISHED%% time=0 test4 (memorytest) \n");

	printf("%%SUITE_FINISHED%% time=0\n");

	return (EXIT_SUCCESS);
}

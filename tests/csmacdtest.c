/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   newsimpletest.c
 * Author: gusev_a
 *
 * Created on 9 ноября 2018 г., 14:58
 */

#include <stdio.h>
#include <stdlib.h>
#include "CSMACD.h"
#include "CRC16ANSI.h"
#include "coap_messages_example.h"

CSMACDController_t controller;
extern const uint16_t CRC16ANSIoTBL[256];

uint8_t msg[] = {
	0x32, 0x33, 0x21, 0x68, 0xF2, 0x22,
	0x32, 0x33, 0x21, 0x68, 0xF2, 0x22
};

uint8_t Sender(uint8_t output) {
	printf(" %02X", output);
	return output;
}

//static const uint32_t msg_test_get_wellknown[] = {
//    0x40, 0x01, 0xFD, 0x5A, 0xBB, 0x2E, 0x77, 0x65, 0x6C, 0x6C, 0x2D, 0x6B,
//    0x6E, 0x6F, 0x77, 0x6E, 0x04, 0x63, 0x6F, 0x72, 0x65, 0xC1, 0x06
//};

static const uint32_t msg_test_get_memory[] = {
	0x40, 0x01, 0x61, 0xBD, 0xB6, 0x6D, 0x65, 0x6D, 0x6F, 0x72, 0x79, 0xC1, 0x06
};

static const uint32_t msg_test_post_memory[] = {
	0x40, 0x02, 0x61, 0xBE, 0xB6, 0x6D, 0x65, 0x6D, 0x6F, 0x72, 0x79, 0xFF, 0x32
};

static const uint32_t msg_test_put_memory[] = {
	0x40, 0x03, 0x61, 0xBF, 0xB6, 0x6D, 0x65, 0x6D, 0x6F, 0x72, 0x79, 0xFF, 0x32
};

static const uint32_t msg_test_delete_memory[] = {
	0x40, 0x04, 0x61, 0xC0, 0xB6, 0x6D, 0x65, 0x6D, 0x6F, 0x72, 0x79
};

static const uint32_t msg_test_get_memory_addr_val[] = {
	0x40, 0x01, 0xDD, 0xE4, 0xB6, 0x6D, 0x65, 0x6D, 0x6F, 0x72, 0x79, 0x4C,
	0x61, 0x64, 0x64, 0x72, 0x65, 0x73, 0x73, 0x3D, 0x30, 0x78, 0x33, 0x45,
	0x07, 0x76, 0x61, 0x6C, 0x75, 0x65, 0x3D, 0x31, 0x81, 0x06
};
static const uint32_t msg_test_post_memory_addr_val[] = {
	0x40, 0x02, 0xDD, 0xE5, 0xB6, 0x6D, 0x65, 0x6D, 0x6F, 0x72, 0x79, 0x4C,
	0x61, 0x64, 0x64, 0x72, 0x65, 0x73, 0x73, 0x3D, 0x30, 0x78, 0x33, 0x45,
	0x07, 0x76, 0x61, 0x6C, 0x75, 0x65, 0x3D, 0x31, 0xFF, 0x32
};
static const uint32_t msg_test_put_memory_addr_val[] = {
	0x40, 0x03, 0xDD, 0xE6, 0xB6, 0x6D, 0x65, 0x6D, 0x6F, 0x72, 0x79, 0x4C,
	0x61, 0x64, 0x64, 0x72, 0x65, 0x73, 0x73, 0x3D, 0x30, 0x78, 0x33, 0x45,
	0x07, 0x76, 0x61, 0x6C, 0x75, 0x65, 0x3D, 0x31, 0xFF, 0x32
};
static const uint32_t msg_test_delete_memory_addr_val[] = {
	0x40, 0x04, 0xDD, 0xE7, 0xB6, 0x6D, 0x65, 0x6D, 0x6F, 0x72, 0x79, 0x4C,
	0x61, 0x64, 0x64, 0x72, 0x65, 0x73, 0x73, 0x3D, 0x30, 0x78, 0x33, 0x45,
	0x07, 0x76, 0x61, 0x6C, 0x75, 0x65, 0x3D, 0x31
};

static const uint32_t msg_test_get_stream[] = {
	0x40, 0x01, 0xFC, 0xB0, 0xBD, 0x05, 0x73, 0x74, 0x72, 0x65, 0x61, 0x6D,
	0x64, 0x61, 0x74, 0x61, 0x72, 0x65, 0x63, 0x6F, 0x72, 0x64, 0x65, 0x72,
	0xC1, 0x06
};
static const uint32_t msg_test_post_stream[] = {
	0x40, 0x02, 0xFC, 0xB1, 0xBD, 0x05, 0x73, 0x74, 0x72, 0x65, 0x61, 0x6D,
	0x64, 0x61, 0x74, 0x61, 0x72, 0x65, 0x63, 0x6F, 0x72, 0x64, 0x65, 0x72,
	0xFF, 0x32
};
static const uint32_t msg_test_put_stream[] = {
	0x40, 0x03, 0xFC, 0xB2, 0xBD, 0x05, 0x73, 0x74, 0x72, 0x65, 0x61, 0x6D,
	0x64, 0x61, 0x74, 0x61, 0x72, 0x65, 0x63, 0x6F, 0x72, 0x64, 0x65, 0x72,
	0xFF, 0x32
};
static const uint32_t msg_test_delete_stream[] = {
	0x40, 0x04, 0xFC, 0xB3, 0xBD, 0x05, 0x73, 0x74, 0x72, 0x65, 0x61, 0x6D,
	0x64, 0x61, 0x74, 0x61, 0x72, 0x65, 0x63, 0x6F, 0x72, 0x64, 0x65, 0x72
};

static const uint32_t msg_test_get_stream_current[] = {
	0x40, 0x01, 0x51, 0x36, 0xBD, 0x05, 0x73, 0x74, 0x72, 0x65, 0x61, 0x6D,
	0x64, 0x61, 0x74, 0x61, 0x72, 0x65, 0x63, 0x6F, 0x72, 0x64, 0x65, 0x72,
	0x07, 0x63, 0x75, 0x72, 0x72, 0x65, 0x6E, 0x74, 0xC1, 0x06
};
static const uint32_t msg_test_post_stream_current[] = {
	0x40, 0x02, 0x51, 0x37, 0xBD, 0x05, 0x73, 0x74, 0x72, 0x65, 0x61, 0x6D,
	0x64, 0x61, 0x74, 0x61, 0x72, 0x65, 0x63, 0x6F, 0x72, 0x64, 0x65, 0x72,
	0x07, 0x63, 0x75, 0x72, 0x72, 0x65, 0x6E, 0x74, 0xFF, 0x32
};
static const uint32_t msg_test_put_stream_current[] = {
	0x40, 0x03, 0x51, 0x38, 0xBD, 0x05, 0x73, 0x74, 0x72, 0x65, 0x61, 0x6D,
	0x64, 0x61, 0x74, 0x61, 0x72, 0x65, 0x63, 0x6F, 0x72, 0x64, 0x65, 0x72,
	0x07, 0x63, 0x75, 0x72, 0x72, 0x65, 0x6E, 0x74, 0xFF, 0x32
};
static const uint32_t msg_test_delete_stream_current[] = {
	0x40, 0x04, 0x51, 0x39, 0xBD, 0x05, 0x73, 0x74, 0x72, 0x65, 0x61, 0x6D,
	0x64, 0x61, 0x74, 0x61, 0x72, 0x65, 0x63, 0x6F, 0x72, 0x64, 0x65, 0x72,
	0x07, 0x63, 0x75, 0x72, 0x72, 0x65, 0x6E, 0x74
};

static const uint32_t msg_test_get_stream_last[] = {
	0x40, 0x01, 0xA6, 0x04, 0xBD, 0x05, 0x73, 0x74, 0x72, 0x65, 0x61, 0x6D,
	0x64, 0x61, 0x74, 0x61, 0x72, 0x65, 0x63, 0x6F, 0x72, 0x64, 0x65, 0x72,
	0x04, 0x6C, 0x61, 0x73, 0x74, 0xC1, 0x06
};

static const uint32_t msg_test_post_stream_last[] = {
	0x40, 0x02, 0xA6, 0x05, 0xBD, 0x05, 0x73, 0x74, 0x72, 0x65, 0x61, 0x6D,
	0x64, 0x61, 0x74, 0x61, 0x72, 0x65, 0x63, 0x6F, 0x72, 0x64, 0x65, 0x72,
	0x04, 0x6C, 0x61, 0x73, 0x74, 0xFF, 0x32
};
static const uint32_t msg_test_put_stream_last[] = {
	0x40, 0x03, 0xA6, 0x06, 0xBD, 0x05, 0x73, 0x74, 0x72, 0x65, 0x61, 0x6D,
	0x64, 0x61, 0x74, 0x61, 0x72, 0x65, 0x63, 0x6F, 0x72, 0x64, 0x65, 0x72,
	0x04, 0x6C, 0x61, 0x73, 0x74, 0xFF, 0x32
};

static const uint32_t msg_test_delete_stream_last[] = {
	0x40, 0x04, 0xA6, 0x07, 0xBD, 0x05, 0x73, 0x74, 0x72, 0x65, 0x61, 0x6D,
	0x64, 0x61, 0x74, 0x61, 0x72, 0x65, 0x63, 0x6F, 0x72, 0x64, 0x65, 0x72,
	0x04, 0x6C, 0x61, 0x73, 0x74
};

static const uint32_t msg_test_get_stream_from_to[] = {
	0x40, 0x01, 0x06, 0xE8, 0xBD, 0x05, 0x73, 0x74, 0x72, 0x65, 0x61, 0x6D,
	0x64, 0x61, 0x74, 0x61, 0x72, 0x65, 0x63, 0x6F, 0x72, 0x64, 0x65, 0x72,
	0x47, 0x66, 0x72, 0x6F, 0x6D, 0x3D, 0x31, 0x35, 0x05, 0x74, 0x6F, 0x3D,
	0x33, 0x30, 0x81, 0x06
};

static const uint32_t msg_test_post_stream_from_to[] = {
	0x40, 0x02, 0x06, 0xE9, 0xBD, 0x05, 0x73, 0x74, 0x72, 0x65, 0x61, 0x6D,
	0x64, 0x61, 0x74, 0x61, 0x72, 0x65, 0x63, 0x6F, 0x72, 0x64, 0x65, 0x72,
	0x47, 0x66, 0x72, 0x6F, 0x6D, 0x3D, 0x31, 0x35, 0x05, 0x74, 0x6F, 0x3D,
	0x33, 0x30, 0xFF, 0x32
};

static const uint32_t msg_test_put_stream_from_to[] = {
	0x40, 0x03, 0x06, 0xEA, 0xBD, 0x05, 0x73, 0x74, 0x72, 0x65, 0x61, 0x6D,
	0x64, 0x61, 0x74, 0x61, 0x72, 0x65, 0x63, 0x6F, 0x72, 0x64, 0x65, 0x72,
	0x47, 0x66, 0x72, 0x6F, 0x6D, 0x3D, 0x31, 0x35, 0x05, 0x74, 0x6F, 0x3D,
	0x33, 0x30, 0xFF, 0x32
};

static const uint32_t msg_test_delete_stream_from_to[] = {
	0x40, 0x04, 0x06, 0xEB, 0xBD, 0x05, 0x73, 0x74, 0x72, 0x65, 0x61, 0x6D,
	0x64, 0x61, 0x74, 0x61, 0x72, 0x65, 0x63, 0x6F, 0x72, 0x64, 0x65, 0x72,
	0x47, 0x66, 0x72, 0x6F, 0x6D, 0x3D, 0x31, 0x35, 0x05, 0x74, 0x6F, 0x3D,
	0x33, 0x30
};

uint32_t *msgs_streamer[25][2];

void init_strm(void) {
	msgs_streamer[0][0] = (uint32_t *) msg_test_get_memory;
	msgs_streamer[0][1] = (uint32_t *) (sizeof (msg_test_get_memory) / sizeof (uint32_t));
	msgs_streamer[1][0] = (uint32_t *) msg_test_post_memory;
	msgs_streamer[1][1] = (uint32_t *) (sizeof (msg_test_post_memory) / sizeof (uint32_t));
	msgs_streamer[2][0] = (uint32_t *) msg_test_put_memory;
	msgs_streamer[2][1] = (uint32_t *) (sizeof (msg_test_put_memory) / sizeof (uint32_t));
	msgs_streamer[3][0] = (uint32_t *) msg_test_delete_memory;
	msgs_streamer[3][1] = (uint32_t *) (sizeof (msg_test_delete_memory) / sizeof (uint32_t));

	msgs_streamer[4][0] = (uint32_t *) msg_test_get_memory_addr_val;
	msgs_streamer[4][1] = (uint32_t *) (sizeof (msg_test_get_memory_addr_val) / sizeof (uint32_t));
	msgs_streamer[5][0] = (uint32_t *) msg_test_post_memory_addr_val;
	msgs_streamer[5][1] = (uint32_t *) (sizeof (msg_test_post_memory_addr_val) / sizeof (uint32_t));
	msgs_streamer[6][0] = (uint32_t *) msg_test_put_memory_addr_val;
	msgs_streamer[6][1] = (uint32_t *) (sizeof (msg_test_put_memory_addr_val) / sizeof (uint32_t));
	msgs_streamer[7][0] = (uint32_t *) msg_test_delete_memory_addr_val;
	msgs_streamer[7][1] = (uint32_t *) (sizeof (msg_test_delete_memory_addr_val) / sizeof (uint32_t));

	msgs_streamer[8][0] = (uint32_t *) msg_test_get_stream;
	msgs_streamer[8][1] = (uint32_t *) (sizeof (msg_test_get_stream) / sizeof (uint32_t));
	msgs_streamer[9][0] = (uint32_t *) msg_test_post_stream;
	msgs_streamer[9][1] = (uint32_t *) (sizeof (msg_test_post_stream) / sizeof (uint32_t));
	msgs_streamer[10][0] = (uint32_t *) msg_test_put_stream;
	msgs_streamer[10][1] = (uint32_t *) (sizeof (msg_test_put_stream) / sizeof (uint32_t));
	msgs_streamer[11][0] = (uint32_t *) msg_test_delete_stream;
	msgs_streamer[11][1] = (uint32_t *) (sizeof (msg_test_delete_stream) / sizeof (uint32_t));

	msgs_streamer[12][0] = (uint32_t *) msg_test_get_stream_current;
	msgs_streamer[12][1] = (uint32_t *) (sizeof (msg_test_get_stream_current) / sizeof (uint32_t));
	msgs_streamer[13][0] = (uint32_t *) msg_test_post_stream_current;
	msgs_streamer[13][1] = (uint32_t *) (sizeof (msg_test_post_stream_current) / sizeof (uint32_t));
	msgs_streamer[14][0] = (uint32_t *) msg_test_put_stream_current;
	msgs_streamer[14][1] = (uint32_t *) (sizeof (msg_test_put_stream_current) / sizeof (uint32_t));
	msgs_streamer[15][0] = (uint32_t *) msg_test_delete_stream_current;
	msgs_streamer[15][1] = (uint32_t *) (sizeof (msg_test_delete_stream_current) / sizeof (uint32_t));

	msgs_streamer[16][0] = (uint32_t *) msg_test_get_stream_last;
	msgs_streamer[16][1] = (uint32_t *) (sizeof (msg_test_get_stream_last) / sizeof (uint32_t));
	msgs_streamer[17][0] = (uint32_t *) msg_test_post_stream_last;
	msgs_streamer[17][1] = (uint32_t *) (sizeof (msg_test_post_stream_last) / sizeof (uint32_t));
	msgs_streamer[18][0] = (uint32_t *) msg_test_put_stream_last;
	msgs_streamer[18][1] = (uint32_t *) (sizeof (msg_test_put_stream_last) / sizeof (uint32_t));
	msgs_streamer[19][0] = (uint32_t *) msg_test_delete_stream_last;
	msgs_streamer[19][1] = (uint32_t *) (sizeof (msg_test_delete_stream_last) / sizeof (uint32_t));

	msgs_streamer[20][0] = (uint32_t *) msg_test_get_stream_from_to;
	msgs_streamer[20][1] = (uint32_t *) (sizeof (msg_test_get_stream_from_to) / sizeof (uint32_t));
	msgs_streamer[21][0] = (uint32_t *) msg_test_post_stream_from_to;
	msgs_streamer[21][1] = (uint32_t *) (sizeof (msg_test_post_stream_from_to) / sizeof (uint32_t));
	msgs_streamer[22][0] = (uint32_t *) msg_test_put_stream_from_to;
	msgs_streamer[22][1] = (uint32_t *) (sizeof (msg_test_put_stream_from_to) / sizeof (uint32_t));
	msgs_streamer[23][0] = (uint32_t *) msg_test_delete_stream_from_to;
	msgs_streamer[23][1] = (uint32_t *) (sizeof (msg_test_delete_stream_from_to) / sizeof (uint32_t));
}

/*
 * Simple C Test Suite
 */

void test1() {
	uint16_t CRC_MB = 0xFFFF;
	uint8_t ID = 0;
	uint8_t DATA[10];
	printf("recvtest test 1\n");
	csma_receiver(&controller, 0x55);
	CRC_MB = (CRC_MB >> 8) ^ CRC16ANSIoTBL[(CRC_MB & 0xFF) ^ (0x55)];
	csma_receiver(&controller, 0x20);
	CRC_MB = (CRC_MB >> 8) ^ CRC16ANSIoTBL[(CRC_MB & 0xFF) ^ (0x20)];
	csma_receiver(&controller, 0x00);
	CRC_MB = (CRC_MB >> 8) ^ CRC16ANSIoTBL[(CRC_MB & 0xFF) ^ (0x00)];
	csma_receiver(&controller, 0x01);
	CRC_MB = (CRC_MB >> 8) ^ CRC16ANSIoTBL[(CRC_MB & 0xFF) ^ (0x01)];
	csma_receiver(&controller, 0x56);
	CRC_MB = (CRC_MB >> 8) ^ CRC16ANSIoTBL[(CRC_MB & 0xFF) ^ (0x56)];
	csma_receiver(&controller, ((CRC_MB) / 256)&255);
	csma_receiver(&controller, (CRC_MB)&255);
	csma_main_cycle(&controller, &ID, DATA);
	printf("Received %d %02X\n", ID, DATA[0]);
	if ((ID != 0x20)
			|| (DATA[0] != 0x56))
		printf(" %%TEST_FAILED%% time=0 testname=test1 (recvtest) message=error message sample\n");
}

void test2() {
	uint16_t CRC_MB = 0xFFFF;
	uint8_t ID = 0;
	uint8_t DATA[10];
	printf("recvtest test 2\n");
	csma_receiver(&controller, 0x55);
	CRC_MB = (CRC_MB >> 8) ^ CRC16ANSIoTBL[(CRC_MB & 0xFF) ^ (0x55)];
	csma_receiver(&controller, 0x20);
	CRC_MB = (CRC_MB >> 8) ^ CRC16ANSIoTBL[(CRC_MB & 0xFF) ^ (0x20)];
	csma_receiver(&controller, 0x00);
	CRC_MB = (CRC_MB >> 8) ^ CRC16ANSIoTBL[(CRC_MB & 0xFF) ^ (0x00)];
	csma_receiver(&controller, 0x04);
	CRC_MB = (CRC_MB >> 8) ^ CRC16ANSIoTBL[(CRC_MB & 0xFF) ^ (0x04)];
	csma_receiver(&controller, 0x56);
	CRC_MB = (CRC_MB >> 8) ^ CRC16ANSIoTBL[(CRC_MB & 0xFF) ^ (0x56)];
	csma_receiver(&controller, 0x33);
	CRC_MB = (CRC_MB >> 8) ^ CRC16ANSIoTBL[(CRC_MB & 0xFF) ^ (0x33)];
	csma_receiver(&controller, 0x54);
	CRC_MB = (CRC_MB >> 8) ^ CRC16ANSIoTBL[(CRC_MB & 0xFF) ^ (0x54)];
	csma_receiver(&controller, 0x44);
	CRC_MB = (CRC_MB >> 8) ^ CRC16ANSIoTBL[(CRC_MB & 0xFF) ^ (0x44)];
	csma_receiver(&controller, ((CRC_MB) / 256)&255);
	csma_receiver(&controller, (CRC_MB)&255);
	csma_main_cycle(&controller, &ID, DATA); //parser
	printf("Received %d m: %02X %02X %02X %02X\n", ID, DATA[0], DATA[1], DATA[2], DATA[3]);
	if ((ID != 0x20)
			|| (DATA[0] != 0x56)
			|| (DATA[1] != 0x33)
			|| (DATA[2] != 0x54)
			|| (DATA[3] != 0x44))
		printf(" %%TEST_FAILED%% time=0 testname=test2 (recvtest) message=error message sample\n");
}

void test3() {
	printf("sendtest test 1\n");
	PacketizeToSend(&controller, msg, 0x21, 6);
	while (csma_sender(&controller) != CSMACD_WAIT);
	csma_clock_cycle(&controller);
	csma_clock_cycle(&controller);
	csma_clock_cycle(&controller);
	csma_clock_cycle(&controller);
	printf("\n");
}

void test4() {
	printf("sendtest test 2\n");
	PacketizeToSend(&controller, msg, 0x21, 12);
	while (csma_sender(&controller) != CSMACD_WAIT);
	csma_clock_cycle(&controller);
	csma_clock_cycle(&controller);
	csma_clock_cycle(&controller);
	csma_clock_cycle(&controller);
	printf("\n");
}

void test5() {
	init_strm();
	uint8_t ID = 0;
	uint8_t DATA[1024];
	printf("recvtest test 5\n");
	uint32_t i;
	for (i = 0; i < 25; i++) {
		uint32_t j, k = 0;
		uint32_t *payload = msgs_streamer[i][0];
		uint16_t length = (uint16_t) msgs_streamer[i][1];
		uint8_t load[length];
		csma_main_cycle(&controller, &ID, DATA);
		csma_main_cycle(&controller, &ID, DATA);
		csma_main_cycle(&controller, &ID, DATA);
		csma_main_cycle(&controller, &ID, DATA);
		csma_main_cycle(&controller, &ID, DATA);
		csma_main_cycle(&controller, &ID, DATA);
		csma_main_cycle(&controller, &ID, DATA);
		csma_main_cycle(&controller, &ID, DATA);
		csma_main_cycle(&controller, &ID, DATA);
		csma_main_cycle(&controller, &ID, DATA);
		load[k++] = 0x55;
		load[k++] = 0x20;
		load[k++] = 0x00;
		load[k++] = (uint8_t) length;
		printf("--------- length : %02X\n", (uint8_t) length);
		for (j = 0; j < ((size_t) msgs_streamer[i][1]); j++) {
			printf("--------- : %02X\n", (uint8_t) payload[j]);
		}
		csma_receiver(&controller, load[0]);
		csma_main_cycle(&controller, &ID, DATA);
		csma_main_cycle(&controller, &ID, DATA);
		csma_main_cycle(&controller, &ID, DATA);
		csma_main_cycle(&controller, &ID, DATA);
		csma_receiver(&controller, load[1]);
		csma_main_cycle(&controller, &ID, DATA);
		csma_main_cycle(&controller, &ID, DATA);
		csma_receiver(&controller, load[2]);
		csma_receiver(&controller, load[3]);
		csma_main_cycle(&controller, &ID, DATA);
		csma_main_cycle(&controller, &ID, DATA);
		csma_main_cycle(&controller, &ID, DATA);
		csma_main_cycle(&controller, &ID, DATA);
		for (j = 0; j < length; j++) {
			load[k++] = (uint8_t) payload[j];
			csma_receiver(&controller, (uint8_t) payload[j]);
		}
		uint16_t CRC = CRC16ANSI(load, length + 4);
		csma_receiver(&controller, (uint8_t) ((CRC >> 8) & 0xFF));
		csma_receiver(&controller, (uint8_t) (CRC & 0xFF));
		csma_main_cycle(&controller, &ID, DATA);
		printf("--------- CRC : 0x%04X\n", CRC);
		printf("Received %d %02X\n", ID, DATA[0]);
		printf("Packet number of %d: length packet is %u\n", i, (uint32_t) msgs_streamer[i][1]);
		printf("ID = 0x%02X\n", ID);
		printf("DATA[0] = 0x%02X\n", DATA[0]);
		if ((ID != 0x20)
				|| (DATA[0] != payload[0])
				|| (DATA[3] != payload[3])
				|| (DATA[5] != payload[5])) {
			printf(" %%TEST_FAILED%% time=0 testname=test5 (recvtest) message=Packet number of %d: length packet is %u\n", i, (uint32_t) msgs_streamer[i][1]);
		}
	}
}

int main(int argc, char** argv) {
	uint8_t id = 0x10;
	printf("%%SUITE_STARTING%% csmacdtest\n");
	printf("%%SUITE_STARTED%%\n");

	csma_init(&controller, &Sender, &id);

	printf("%%TEST_STARTED%% test1 (csmacdtest)\n");
	test1();
	printf("%%TEST_FINISHED%% time=0 test1 (csmacdtest) \n");

	printf("%%TEST_STARTED%% test2 (csmacdtest)\n");
	test2();
	printf("%%TEST_FINISHED%% time=0 test2 (csmacdtest) \n");

	printf("%%TEST_STARTED%% test3 (csmacdtest)\n");
	test3();
	printf("%%TEST_FINISHED%% time=0 test3 (csmacdtest) \n");

	printf("%%TEST_STARTED%% test4 (csmacdtest)\n");
	test4();
	printf("%%TEST_FINISHED%% time=0 test4 (csmacdtest) \n");

	printf("%%TEST_STARTED%% test5 (csmacdtest)\n");
	test5();
	printf("%%TEST_FINISHED%% time=0 test5 (csmacdtest) \n");

	printf("%%SUITE_FINISHED%% time=0\n");

	return (EXIT_SUCCESS);
}



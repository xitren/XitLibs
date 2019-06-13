/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   coaptest.c
 * Author: gusev_a
 *
 * Created on 12 ноября 2018 г., 16:21
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stddef.h>
#include "coap.h"
#include "CommandModule.h"
#include "StreamDataRecorder.h"
#include "ConfigMem.h"

/*
 * Simple C Test Suite
 */

static uint8_t _msg_test_get_wellknown[] = {
    0x40, 0x01, 0xFD, 0x5A, 0xBB, 0x2E, 0x77, 0x65, 0x6C, 0x6C, 0x2D, 0x6B,
    0x6E, 0x6F, 0x77, 0x6E, 0x04, 0x63, 0x6F, 0x72, 0x65, 0xC1, 0x06
};

static uint8_t _msg_test_get_memory[] = {
    0x40, 0x01, 0x61, 0xBD, 0xB6, 0x6D, 0x65, 0x6D, 0x6F, 0x72, 0x79, 0xC1, 0x06
};

static uint8_t _msg_test_post_memory[] = {
    0x40, 0x02, 0x61, 0xBE, 0xB6, 0x6D, 0x65, 0x6D, 0x6F, 0x72, 0x79, 0xFF, 0x32
};

static uint8_t _msg_test_put_memory[] = {
    0x40, 0x03, 0x61, 0xBF, 0xB6, 0x6D, 0x65, 0x6D, 0x6F, 0x72, 0x79, 0xFF, 0x32
};

static uint8_t _msg_test_delete_memory[] = {
    0x40, 0x04, 0x61, 0xC0, 0xB6, 0x6D, 0x65, 0x6D, 0x6F, 0x72, 0x79
};

static uint8_t _msg_test_get_memory_addr_val[] = {
    0x40, 0x01, 0xDD, 0xE4, 0xB6, 0x6D, 0x65, 0x6D, 0x6F, 0x72, 0x79, 0x4C,
    0x61, 0x64, 0x64, 0x72, 0x65, 0x73, 0x73, 0x3D, 0x30, 0x78, 0x33, 0x45,
    0x07, 0x76, 0x61, 0x6C, 0x75, 0x65, 0x3D, 0x31, 0x81, 0x06
};

static uint8_t _msg_test_post_memory_addr_val[] = {
    0x40, 0x02, 0xDD, 0xE5, 0xB6, 0x6D, 0x65, 0x6D, 0x6F, 0x72, 0x79, 0x4C,
    0x61, 0x64, 0x64, 0x72, 0x65, 0x73, 0x73, 0x3D, 0x30, 0x78, 0x33, 0x45,
    0x07, 0x76, 0x61, 0x6C, 0x75, 0x65, 0x3D, 0x31, 0xFF, 0x32
};

static uint8_t _msg_test_put_memory_addr_val[] = {
    0x40, 0x03, 0xDD, 0xE6, 0xB6, 0x6D, 0x65, 0x6D, 0x6F, 0x72, 0x79, 0x4C,
    0x61, 0x64, 0x64, 0x72, 0x65, 0x73, 0x73, 0x3D, 0x30, 0x78, 0x33, 0x45,
    0x07, 0x76, 0x61, 0x6C, 0x75, 0x65, 0x3D, 0x31, 0xFF, 0x32
};

static uint8_t _msg_test_delete_memory_addr_val[] = {
    0x40, 0x04, 0xDD, 0xE7, 0xB6, 0x6D, 0x65, 0x6D, 0x6F, 0x72, 0x79, 0x4C,
    0x61, 0x64, 0x64, 0x72, 0x65, 0x73, 0x73, 0x3D, 0x30, 0x78, 0x33, 0x45,
    0x07, 0x76, 0x61, 0x6C, 0x75, 0x65, 0x3D, 0x31
};

static uint8_t _msg_test_get_stream[] = {
    0x40, 0x01, 0xFC, 0xB0, 0xBD, 0x05, 0x73, 0x74, 0x72, 0x65, 0x61, 0x6D,
    0x64, 0x61, 0x74, 0x61, 0x72, 0x65, 0x63, 0x6F, 0x72, 0x64, 0x65, 0x72,
    0xC1, 0x06
};
static uint8_t _msg_test_post_stream[] = {
    0x40, 0x02, 0xFC, 0xB1, 0xBD, 0x05, 0x73, 0x74, 0x72, 0x65, 0x61, 0x6D,
    0x64, 0x61, 0x74, 0x61, 0x72, 0x65, 0x63, 0x6F, 0x72, 0x64, 0x65, 0x72,
    0xFF, 0x32
};
static uint8_t _msg_test_put_stream[] = {
    0x40, 0x03, 0xFC, 0xB2, 0xBD, 0x05, 0x73, 0x74, 0x72, 0x65, 0x61, 0x6D,
    0x64, 0x61, 0x74, 0x61, 0x72, 0x65, 0x63, 0x6F, 0x72, 0x64, 0x65, 0x72,
    0xFF, 0x32
};

static uint8_t _msg_test_delete_stream[] = {
    0x40, 0x04, 0xFC, 0xB3, 0xBD, 0x05, 0x73, 0x74, 0x72, 0x65, 0x61, 0x6D,
    0x64, 0x61, 0x74, 0x61, 0x72, 0x65, 0x63, 0x6F, 0x72, 0x64, 0x65, 0x72
};

static uint8_t _msg_test_get_stream_current[] = {
    0x40, 0x01, 0x51, 0x36, 0xBD, 0x05, 0x73, 0x74, 0x72, 0x65, 0x61, 0x6D,
    0x64, 0x61, 0x74, 0x61, 0x72, 0x65, 0x63, 0x6F, 0x72, 0x64, 0x65, 0x72,
    0x07, 0x63, 0x75, 0x72, 0x72, 0x65, 0x6E, 0x74, 0xC1, 0x06
};

static uint8_t _msg_test_post_stream_current[] = {
    0x40, 0x02, 0x51, 0x37, 0xBD, 0x05, 0x73, 0x74, 0x72, 0x65, 0x61, 0x6D,
    0x64, 0x61, 0x74, 0x61, 0x72, 0x65, 0x63, 0x6F, 0x72, 0x64, 0x65, 0x72,
    0x07, 0x63, 0x75, 0x72, 0x72, 0x65, 0x6E, 0x74, 0xFF, 0x32
};

static uint8_t _msg_test_put_stream_current[] = {
    0x40, 0x03, 0x51, 0x38, 0xBD, 0x05, 0x73, 0x74, 0x72, 0x65, 0x61, 0x6D,
    0x64, 0x61, 0x74, 0x61, 0x72, 0x65, 0x63, 0x6F, 0x72, 0x64, 0x65, 0x72,
    0x07, 0x63, 0x75, 0x72, 0x72, 0x65, 0x6E, 0x74, 0xFF, 0x32
};

static uint8_t _msg_test_delete_stream_current[] = {
    0x40, 0x04, 0x51, 0x39, 0xBD, 0x05, 0x73, 0x74, 0x72, 0x65, 0x61, 0x6D,
    0x64, 0x61, 0x74, 0x61, 0x72, 0x65, 0x63, 0x6F, 0x72, 0x64, 0x65, 0x72,
    0x07, 0x63, 0x75, 0x72, 0x72, 0x65, 0x6E, 0x74
};

static uint8_t _msg_test_get_stream_last[] = {
    0x40, 0x01, 0xA6, 0x04, 0xBD, 0x05, 0x73, 0x74, 0x72, 0x65, 0x61, 0x6D,
    0x64, 0x61, 0x74, 0x61, 0x72, 0x65, 0x63, 0x6F, 0x72, 0x64, 0x65, 0x72,
    0x04, 0x6C, 0x61, 0x73, 0x74, 0xC1, 0x06
};

static uint8_t _msg_test_post_stream_last[] = {
    0x40, 0x02, 0xA6, 0x05, 0xBD, 0x05, 0x73, 0x74, 0x72, 0x65, 0x61, 0x6D,
    0x64, 0x61, 0x74, 0x61, 0x72, 0x65, 0x63, 0x6F, 0x72, 0x64, 0x65, 0x72,
    0x04, 0x6C, 0x61, 0x73, 0x74, 0xFF, 0x32
};

static uint8_t _msg_test_put_stream_last[] = {
    0x40, 0x03, 0xA6, 0x06, 0xBD, 0x05, 0x73, 0x74, 0x72, 0x65, 0x61, 0x6D,
    0x64, 0x61, 0x74, 0x61, 0x72, 0x65, 0x63, 0x6F, 0x72, 0x64, 0x65, 0x72,
    0x04, 0x6C, 0x61, 0x73, 0x74, 0xFF, 0x32
};

static uint8_t _msg_test_delete_stream_last[] = {
    0x40, 0x04, 0xA6, 0x07, 0xBD, 0x05, 0x73, 0x74, 0x72, 0x65, 0x61, 0x6D,
    0x64, 0x61, 0x74, 0x61, 0x72, 0x65, 0x63, 0x6F, 0x72, 0x64, 0x65, 0x72,
    0x04, 0x6C, 0x61, 0x73, 0x74
};

static uint8_t _msg_test_get_stream_from_to[] = {
    0x40, 0x01, 0x06, 0xE8, 0xBD, 0x05, 0x73, 0x74, 0x72, 0x65, 0x61, 0x6D,
    0x64, 0x61, 0x74, 0x61, 0x72, 0x65, 0x63, 0x6F, 0x72, 0x64, 0x65, 0x72,
    0x47, 0x66, 0x72, 0x6F, 0x6D, 0x3D, 0x31, 0x35, 0x05, 0x74, 0x6F, 0x3D,
    0x33, 0x30, 0x81, 0x06
};

static uint8_t _msg_test_post_stream_from_to[] = {
    0x40, 0x02, 0x06, 0xE9, 0xBD, 0x05, 0x73, 0x74, 0x72, 0x65, 0x61, 0x6D,
    0x64, 0x61, 0x74, 0x61, 0x72, 0x65, 0x63, 0x6F, 0x72, 0x64, 0x65, 0x72,
    0x47, 0x66, 0x72, 0x6F, 0x6D, 0x3D, 0x31, 0x35, 0x05, 0x74, 0x6F, 0x3D,
    0x33, 0x30, 0xFF, 0x32
};

static uint8_t _msg_test_put_stream_from_to[] = {
    0x40, 0x03, 0x06, 0xEA, 0xBD, 0x05, 0x73, 0x74, 0x72, 0x65, 0x61, 0x6D,
    0x64, 0x61, 0x74, 0x61, 0x72, 0x65, 0x63, 0x6F, 0x72, 0x64, 0x65, 0x72,
    0x47, 0x66, 0x72, 0x6F, 0x6D, 0x3D, 0x31, 0x35, 0x05, 0x74, 0x6F, 0x3D,
    0x33, 0x30, 0xFF, 0x32
};

static uint8_t _msg_test_delete_stream_from_to[] = {
    0x40, 0x04, 0x06, 0xEB, 0xBD, 0x05, 0x73, 0x74, 0x72, 0x65, 0x61, 0x6D,
    0x64, 0x61, 0x74, 0x61, 0x72, 0x65, 0x63, 0x6F, 0x72, 0x64, 0x65, 0x72,
    0x47, 0x66, 0x72, 0x6F, 0x6D, 0x3D, 0x31, 0x35, 0x05, 0x74, 0x6F, 0x3D,
    0x33, 0x30
};

static uint8_t _msg_test_get_reg1[] = {
    0x40, 0x01, 0x00, 0x01, 0xb6, 0x6d, 0x65, 0x6d, 0x6f, 0x72, 0x79, 0x4d,
    0x05, 0x61, 0x64, 0x64, 0x72, 0x65, 0x73, 0x73, 0x3d, 0x30, 0x78, 0x30,
    0x30, 0x30, 0x30, 0x30, 0x30, 0x33, 0x46
};
    
static uint8_t _msg_test_put_reg[] = {
    0x40, 0x03, 0x00, 0x01, 0xB6, 0x6D, 0x65, 0x6D, 0x6F, 0x72, 0x79, 0x4D, 0x0E,
    0x61, 0x64, 0x64, 0x72, 0x65, 0x73, 0x73, 0x3D, 0x30, 0x78, 0x30, 0x30, 0x30,
    0x30, 0x30, 0x30, 0x33, 0x46, 0x26, 0x76, 0x61, 0x6C, 0x75, 0x65, 0x3D, 0x31,
    0x30
};

static uint8_t _msg_test_get_reg2[] = {
    0x40, 0x03, 0x00, 0x01, 0xB6, 0x6D, 0x65, 0x6D, 0x6F, 0x72, 0x79, 0x4D, 0x0E,
    0x61, 0x64, 0x64, 0x72, 0x65, 0x73, 0x73, 0x3D, 0x30, 0x78, 0x30, 0x30, 0x30,
    0x30, 0x30, 0x30, 0x33, 0x46, 0x26, 0x76, 0x61, 0x6C, 0x75, 0x65, 0x3D, 0x31,
    0x30
};

uint32_t *msgs_streamer[28][2];

void init_strm(void)
{
	msgs_streamer[0][0] = (uint32_t *)_msg_test_get_wellknown;
	msgs_streamer[0][1] = (uint32_t *)(sizeof(_msg_test_get_wellknown)/sizeof(uint32_t));
	
	msgs_streamer[1][0] = (uint32_t *)_msg_test_get_memory;
	msgs_streamer[1][1] = (uint32_t *)(sizeof(_msg_test_get_memory)/sizeof(uint32_t));
	msgs_streamer[2][0] = (uint32_t *)_msg_test_post_memory;
	msgs_streamer[2][1] = (uint32_t *)(sizeof(_msg_test_post_memory)/sizeof(uint32_t));
	msgs_streamer[3][0] = (uint32_t *)_msg_test_put_memory;
	msgs_streamer[3][1] = (uint32_t *)(sizeof(_msg_test_put_memory)/sizeof(uint32_t));
	msgs_streamer[4][0] = (uint32_t *)_msg_test_delete_memory;
	msgs_streamer[4][1] = (uint32_t *)(sizeof(_msg_test_delete_memory)/sizeof(uint32_t));
	
	msgs_streamer[5][0] = (uint32_t *)_msg_test_get_memory_addr_val;
	msgs_streamer[5][1] = (uint32_t *)(sizeof(_msg_test_get_memory_addr_val)/sizeof(uint32_t));
	msgs_streamer[6][0] = (uint32_t *)_msg_test_post_memory_addr_val;
	msgs_streamer[6][1] = (uint32_t *)(sizeof(_msg_test_post_memory_addr_val)/sizeof(uint32_t));
	msgs_streamer[7][0] = (uint32_t *)_msg_test_put_memory_addr_val;
	msgs_streamer[7][1] = (uint32_t *)(sizeof(_msg_test_put_memory_addr_val)/sizeof(uint32_t));
	msgs_streamer[8][0] = (uint32_t *)_msg_test_delete_memory_addr_val;
	msgs_streamer[8][1] = (uint32_t *)(sizeof(_msg_test_delete_memory_addr_val)/sizeof(uint32_t));
	
	msgs_streamer[9][0] = (uint32_t *)_msg_test_get_stream;
	msgs_streamer[9][1] = (uint32_t *)(sizeof(_msg_test_get_stream)/sizeof(uint32_t));
	msgs_streamer[10][0] = (uint32_t *)_msg_test_post_stream;
	msgs_streamer[10][1] = (uint32_t *)(sizeof(_msg_test_post_stream)/sizeof(uint32_t));
	msgs_streamer[11][0] = (uint32_t *)_msg_test_put_stream;
	msgs_streamer[11][1] = (uint32_t *)(sizeof(_msg_test_put_stream)/sizeof(uint32_t));
	msgs_streamer[12][0] = (uint32_t *)_msg_test_delete_stream;
	msgs_streamer[12][1] = (uint32_t *)(sizeof(_msg_test_delete_stream)/sizeof(uint32_t));
	
	msgs_streamer[13][0] = (uint32_t *)_msg_test_get_stream_current;
	msgs_streamer[13][1] = (uint32_t *)(sizeof(_msg_test_get_stream_current)/sizeof(uint32_t));
	msgs_streamer[14][0] = (uint32_t *)_msg_test_post_stream_current;
	msgs_streamer[14][1] = (uint32_t *)(sizeof(_msg_test_post_stream_current)/sizeof(uint32_t));
	msgs_streamer[15][0] = (uint32_t *)_msg_test_put_stream_current;
	msgs_streamer[15][1] = (uint32_t *)(sizeof(_msg_test_put_stream_current)/sizeof(uint32_t));
	msgs_streamer[16][0] = (uint32_t *)_msg_test_delete_stream_current;
	msgs_streamer[16][1] = (uint32_t *)(sizeof(_msg_test_delete_stream_current)/sizeof(uint32_t));
	
	msgs_streamer[17][0] = (uint32_t *)_msg_test_get_stream_last;
	msgs_streamer[17][1] = (uint32_t *)(sizeof(_msg_test_get_stream_last)/sizeof(uint32_t));
	msgs_streamer[18][0] = (uint32_t *)_msg_test_post_stream_last;
	msgs_streamer[18][1] = (uint32_t *)(sizeof(_msg_test_post_stream_last)/sizeof(uint32_t));
	msgs_streamer[19][0] = (uint32_t *)_msg_test_put_stream_last;
	msgs_streamer[19][1] = (uint32_t *)(sizeof(_msg_test_put_stream_last)/sizeof(uint32_t));
	msgs_streamer[20][0] = (uint32_t *)_msg_test_delete_stream_last;
	msgs_streamer[20][1] = (uint32_t *)(sizeof(_msg_test_delete_stream_last)/sizeof(uint32_t));
	
	msgs_streamer[21][0] = (uint32_t *)_msg_test_get_stream_from_to;
	msgs_streamer[21][1] = (uint32_t *)(sizeof(_msg_test_get_stream_from_to)/sizeof(uint32_t));
	msgs_streamer[22][0] = (uint32_t *)_msg_test_post_stream_from_to;
	msgs_streamer[23][1] = (uint32_t *)(sizeof(_msg_test_post_stream_from_to)/sizeof(uint32_t));
	msgs_streamer[24][0] = (uint32_t *)_msg_test_put_stream_from_to;
	msgs_streamer[24][1] = (uint32_t *)(sizeof(_msg_test_put_stream_from_to)/sizeof(uint32_t));
	msgs_streamer[25][0] = (uint32_t *)_msg_test_delete_stream_from_to;
	msgs_streamer[25][1] = (uint32_t *)(sizeof(_msg_test_delete_stream_from_to)/sizeof(uint32_t));
	
	msgs_streamer[26][0] = (uint32_t *)_msg_test_get_reg1;
	msgs_streamer[26][1] = (uint32_t *)(sizeof(_msg_test_get_reg1)/sizeof(uint32_t));
	msgs_streamer[27][0] = (uint32_t *)_msg_test_put_reg;
	msgs_streamer[27][1] = (uint32_t *)(sizeof(_msg_test_put_reg)/sizeof(uint32_t));
	msgs_streamer[28][0] = (uint32_t *)_msg_test_get_reg2;
	msgs_streamer[28][1] = (uint32_t *)(sizeof(_msg_test_get_reg2)/sizeof(uint32_t));
}

coap_packet_t inpkt_test;
coap_packet_t outpkt_test;
uint8_t buffer_test[4096];
uint8_t scratch_b_test[4096];
uint8_t message_b_test[4096];
coap_rw_buffer_t scratch_test = {scratch_b_test, sizeof (scratch_b_test)};
coap_rw_buffer_t message_test = {message_b_test, sizeof (message_b_test)};

void test1()
{
	init_strm();
    int rc;
	uint32_t i, j;
    printf("**** ---------------------- coaptest test 1 ---------------------- ****\n");
    uint8_t media_option = COAP_CONTENTTYPE_APPLICATION_XML;
    for (i = 0; i < 28; i++)
    {
    printf("**** ---------------------- coaptest test 1: %d ---------------------- ****\n", i);
        memset((void *) &inpkt_test, 0, sizeof (coap_packet_t));
        /*==1= Parse package =================================================*/
        rc = coap_parse(
                &inpkt_test,
                (uint8_t *) msgs_streamer[i][0],
                msgs_streamer[i][1]);
        /*==2= Handle request ================================================*/
        if (rc == 0)
            rc = coap_handle_req(&scratch_test, &inpkt_test, &outpkt_test, 0, "127.0.0.1", 4567);
        /*==3= Build response content ========================================*/
        switch (current_coap_mediatype)
        {
            case Media_TEXT:
                media_option = COAP_CONTENTTYPE_TEXT_PLAIN;
                break;
            case Media_BYTE:
                media_option = COAP_CONTENTTYPE_APPLICATION_OCTECT_STREAM;
                break;
            case Media_XML:
                media_option = COAP_CONTENTTYPE_APPLICATION_XML;
                break;
            case Media_JSON:
                media_option = COAP_CONTENTTYPE_APPLICATION_JSON;
                break;
            case Media_LINK:
                media_option = COAP_CONTENTTYPE_APPLICATION_LINKFORMAT;
                break;
            default:
                media_option = COAP_CONTENTTYPE_APPLICATION_XML;
                break;
        }
        if (rc == 0)
        {
            if ((inpkt_test.hdr.code == COAP_METHOD_GET))
                coap_make_response(&scratch_test, &outpkt_test, 0,
                    (uint8_t*) scratch_test.p, scratch_test.len,
                    inpkt_test.hdr.id[0], inpkt_test.hdr.id[1],
                    inpkt_test.tok_p, inpkt_test.tok_len, COAP_RSPCODE_CONTENT,
                    media_option);
            else
                coap_make_response(&scratch_test, &outpkt_test, 0,
                    (uint8_t*) scratch_test.p, scratch_test.len,
                    inpkt_test.hdr.id[0], inpkt_test.hdr.id[1],
                    inpkt_test.tok_p, inpkt_test.tok_len, COAP_RSPCODE_CHANGED,
                    media_option);
        }
        else
        {
            switch (rc)
            {
                case INVALID_PARAMETERS_ERROR:
                    coap_make_response(&scratch_test, &outpkt_test, 0,
                            (uint8_t*) scratch_test.p, scratch_test.len,
                            inpkt_test.hdr.id[0], inpkt_test.hdr.id[1],
                            inpkt_test.tok_p, inpkt_test.tok_len, COAP_RSPCODE_BAD_REQUEST,
                            media_option);
                    break;
                case NO_COMMAND_ERROR:
                    coap_make_response(&scratch_test, &outpkt_test, 0,
                            (uint8_t*) scratch_test.p, scratch_test.len,
                            inpkt_test.hdr.id[0], inpkt_test.hdr.id[1],
                            inpkt_test.tok_p, inpkt_test.tok_len, COAP_RSPCODE_NOT_FOUND,
                            media_option);
                    break;
                default:
                    coap_make_response(&scratch_test, &outpkt_test, 0,
                            (uint8_t*) scratch_test.p, scratch_test.len,
                            inpkt_test.hdr.id[0], inpkt_test.hdr.id[1],
                            inpkt_test.tok_p, inpkt_test.tok_len, COAP_RSPCODE_BAD_REQUEST,
                            media_option);
                    break;
            }
        }
        /*==4= Build response package ========================================*/
        message_test.len = 4096;
        rc = coap_build(message_test.p, &message_test.len, &outpkt_test, NULL, NULL);
        /*==5= Transmitt package =============================================*/
        printf("\n\r\n\r\n\r");
        if (rc == 0)
        {
            printf("Dump:");
            for (j = 0; j < message_test.len; j++)
            {
                printf(" %02X", message_test.p[j]);
            }
            printf("\n");
        }
    }
}

void test2()
{
    printf("coaptest test 2\n");
}

CircularBufferItem_t file[48];

int main(int argc, char** argv)
{
    printf("%%SUITE_STARTING%% coaptest\n");
    printf("%%SUITE_STARTED%%\n");

    InitCommands();
    InitStreamRecorder(file, 48, 250, 8, 1);
//    for (i = 0; i < 1000; i++)
//        if (i == 263)
//            AddSample();
//        else
//            AddSample();

    AddCommand(
            Method_GET | Method_PUT | Method_POST | Method_RESET,
            global_link_memory[0], global_link_memory[1],
            &MemoryCommand);
    AddCommand(
            Method_GET | Method_RESET,
            global_link_streamer[0][0], global_link_streamer[0][1],
            &StreamRecorderCommand);
    AddCommand(
            Method_GET,
            global_link_streamer[1][0], global_link_streamer[1][1],
            &StreamRecorderCurrentCommand);
    AddCommand(
            Method_GET,
            global_link_streamer[2][0], global_link_streamer[2][1],
            &StreamRecorderLastCommand);

    printf("%%TEST_STARTED%% test1 (coaptest)\n");
    test1();
    printf("%%TEST_FINISHED%% time=0 test1 (coaptest) \n");

    printf("%%TEST_STARTED%% test2 (coaptest)\n");
    test2();
    printf("%%TEST_FINISHED%% time=0 test2 (coaptest) \n");

    printf("%%SUITE_FINISHED%% time=0\n");

    return (EXIT_SUCCESS);
}
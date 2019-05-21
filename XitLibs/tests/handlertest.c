/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>
#include <stdlib.h>
#include "coap.h"
#include "CommandModule.h"
#include "StreamDataRecorder.h"
#include "Handler.h"
#include "coap_messages_example.h"

/*uint8_t msg_test_get_wellknown[] = {
    0x40, 0x01, 0xFD, 0x5A, 0xBB, 0x2E, 0x77, 0x65, 0x6C, 0x6C, 0x2D, 0x6B,
    0x6E, 0x6F, 0x77, 0x6E, 0x04, 0x63, 0x6F, 0x72, 0x65, 0xC1, 0x06
};

uint8_t msg_test_get_memory[] = {
    0x40, 0x01, 0x61, 0xBD, 0xB6, 0x6D, 0x65, 0x6D, 0x6F, 0x72, 0x79, 0xC1, 0x06
};

uint8_t msg_test_post_memory[] = {
    0x40, 0x02, 0x61, 0xBE, 0xB6, 0x6D, 0x65, 0x6D, 0x6F, 0x72, 0x79, 0xFF, 0x32
};

uint8_t msg_test_put_memory[] = {
    0x40, 0x03, 0x61, 0xBF, 0xB6, 0x6D, 0x65, 0x6D, 0x6F, 0x72, 0x79, 0xFF, 0x32
};

uint8_t msg_test_delete_memory[] = {
    0x40, 0x04, 0x61, 0xC0, 0xB6, 0x6D, 0x65, 0x6D, 0x6F, 0x72, 0x79
};

uint8_t msg_test_get_memory_addr_val[] = {
    0x40, 0x01, 0xDD, 0xE4, 0xB6, 0x6D, 0x65, 0x6D, 0x6F, 0x72, 0x79, 0x4C,
    0x61, 0x64, 0x64, 0x72, 0x65, 0x73, 0x73, 0x3D, 0x30, 0x78, 0x33, 0x45,
    0x07, 0x76, 0x61, 0x6C, 0x75, 0x65, 0x3D, 0x31, 0x81, 0x06
};
uint8_t msg_test_post_memory_addr_val[] = {
    0x40, 0x02, 0xDD, 0xE5, 0xB6, 0x6D, 0x65, 0x6D, 0x6F, 0x72, 0x79, 0x4C,
    0x61, 0x64, 0x64, 0x72, 0x65, 0x73, 0x73, 0x3D, 0x30, 0x78, 0x33, 0x45,
    0x07, 0x76, 0x61, 0x6C, 0x75, 0x65, 0x3D, 0x31, 0xFF, 0x32
};
uint8_t msg_test_put_memory_addr_val[] = {
    0x40, 0x03, 0xDD, 0xE6, 0xB6, 0x6D, 0x65, 0x6D, 0x6F, 0x72, 0x79, 0x4C,
    0x61, 0x64, 0x64, 0x72, 0x65, 0x73, 0x73, 0x3D, 0x30, 0x78, 0x33, 0x45,
    0x07, 0x76, 0x61, 0x6C, 0x75, 0x65, 0x3D, 0x31, 0xFF, 0x32
};
uint8_t msg_test_delete_memory_addr_val[] = {
    0x40, 0x04, 0xDD, 0xE7, 0xB6, 0x6D, 0x65, 0x6D, 0x6F, 0x72, 0x79, 0x4C,
    0x61, 0x64, 0x64, 0x72, 0x65, 0x73, 0x73, 0x3D, 0x30, 0x78, 0x33, 0x45,
    0x07, 0x76, 0x61, 0x6C, 0x75, 0x65, 0x3D, 0x31
};

uint8_t msg_test_get_stream[] = {
    0x40, 0x01, 0xFC, 0xB0, 0xBD, 0x05, 0x73, 0x74, 0x72, 0x65, 0x61, 0x6D,
    0x64, 0x61, 0x74, 0x61, 0x72, 0x65, 0x63, 0x6F, 0x72, 0x64, 0x65, 0x72,
    0xC1, 0x06
};
uint8_t msg_test_post_stream[] = {
    0x40, 0x02, 0xFC, 0xB1, 0xBD, 0x05, 0x73, 0x74, 0x72, 0x65, 0x61, 0x6D,
    0x64, 0x61, 0x74, 0x61, 0x72, 0x65, 0x63, 0x6F, 0x72, 0x64, 0x65, 0x72,
    0xFF, 0x32
};
uint8_t msg_test_put_stream[] = {
    0x40, 0x03, 0xFC, 0xB2, 0xBD, 0x05, 0x73, 0x74, 0x72, 0x65, 0x61, 0x6D,
    0x64, 0x61, 0x74, 0x61, 0x72, 0x65, 0x63, 0x6F, 0x72, 0x64, 0x65, 0x72,
    0xFF, 0x32
};
uint8_t msg_test_delete_stream[] = {
    0x40, 0x04, 0xFC, 0xB3, 0xBD, 0x05, 0x73, 0x74, 0x72, 0x65, 0x61, 0x6D,
    0x64, 0x61, 0x74, 0x61, 0x72, 0x65, 0x63, 0x6F, 0x72, 0x64, 0x65, 0x72
};

uint8_t msg_test_get_stream_current[] = {
    0x40, 0x01, 0x51, 0x36, 0xBD, 0x05, 0x73, 0x74, 0x72, 0x65, 0x61, 0x6D,
    0x64, 0x61, 0x74, 0x61, 0x72, 0x65, 0x63, 0x6F, 0x72, 0x64, 0x65, 0x72,
    0x07, 0x63, 0x75, 0x72, 0x72, 0x65, 0x6E, 0x74, 0xC1, 0x06
};
uint8_t msg_test_post_stream_current[] = {
    0x40, 0x02, 0x51, 0x37, 0xBD, 0x05, 0x73, 0x74, 0x72, 0x65, 0x61, 0x6D,
    0x64, 0x61, 0x74, 0x61, 0x72, 0x65, 0x63, 0x6F, 0x72, 0x64, 0x65, 0x72,
    0x07, 0x63, 0x75, 0x72, 0x72, 0x65, 0x6E, 0x74, 0xFF, 0x32
};
uint8_t msg_test_put_stream_current[] = {
    0x40, 0x03, 0x51, 0x38, 0xBD, 0x05, 0x73, 0x74, 0x72, 0x65, 0x61, 0x6D,
    0x64, 0x61, 0x74, 0x61, 0x72, 0x65, 0x63, 0x6F, 0x72, 0x64, 0x65, 0x72,
    0x07, 0x63, 0x75, 0x72, 0x72, 0x65, 0x6E, 0x74, 0xFF, 0x32
};
uint8_t msg_test_delete_stream_current[] = {
    0x40, 0x04, 0x51, 0x39, 0xBD, 0x05, 0x73, 0x74, 0x72, 0x65, 0x61, 0x6D,
    0x64, 0x61, 0x74, 0x61, 0x72, 0x65, 0x63, 0x6F, 0x72, 0x64, 0x65, 0x72,
    0x07, 0x63, 0x75, 0x72, 0x72, 0x65, 0x6E, 0x74
};

uint8_t msg_test_get_stream_last[] = {
    0x40, 0x01, 0xA6, 0x04, 0xBD, 0x05, 0x73, 0x74, 0x72, 0x65, 0x61, 0x6D,
    0x64, 0x61, 0x74, 0x61, 0x72, 0x65, 0x63, 0x6F, 0x72, 0x64, 0x65, 0x72,
    0x04, 0x6C, 0x61, 0x73, 0x74, 0xC1, 0x06
};

uint8_t msg_test_post_stream_last[] = {
    0x40, 0x02, 0xA6, 0x05, 0xBD, 0x05, 0x73, 0x74, 0x72, 0x65, 0x61, 0x6D,
    0x64, 0x61, 0x74, 0x61, 0x72, 0x65, 0x63, 0x6F, 0x72, 0x64, 0x65, 0x72,
    0x04, 0x6C, 0x61, 0x73, 0x74, 0xFF, 0x32
};
uint8_t msg_test_put_stream_last[] = {
    0x40, 0x03, 0xA6, 0x06, 0xBD, 0x05, 0x73, 0x74, 0x72, 0x65, 0x61, 0x6D,
    0x64, 0x61, 0x74, 0x61, 0x72, 0x65, 0x63, 0x6F, 0x72, 0x64, 0x65, 0x72,
    0x04, 0x6C, 0x61, 0x73, 0x74, 0xFF, 0x32
};

uint8_t msg_test_delete_stream_last[] = {
    0x40, 0x04, 0xA6, 0x07, 0xBD, 0x05, 0x73, 0x74, 0x72, 0x65, 0x61, 0x6D,
    0x64, 0x61, 0x74, 0x61, 0x72, 0x65, 0x63, 0x6F, 0x72, 0x64, 0x65, 0x72,
    0x04, 0x6C, 0x61, 0x73, 0x74
};

uint8_t msg_test_get_stream_from_to[] = {
    0x40, 0x01, 0x06, 0xE8, 0xBD, 0x05, 0x73, 0x74, 0x72, 0x65, 0x61, 0x6D,
    0x64, 0x61, 0x74, 0x61, 0x72, 0x65, 0x63, 0x6F, 0x72, 0x64, 0x65, 0x72,
    0x47, 0x66, 0x72, 0x6F, 0x6D, 0x3D, 0x31, 0x35, 0x05, 0x74, 0x6F, 0x3D,
    0x33, 0x30, 0x81, 0x06
};

uint8_t msg_test_post_stream_from_to[] = {
    0x40, 0x02, 0x06, 0xE9, 0xBD, 0x05, 0x73, 0x74, 0x72, 0x65, 0x61, 0x6D,
    0x64, 0x61, 0x74, 0x61, 0x72, 0x65, 0x63, 0x6F, 0x72, 0x64, 0x65, 0x72,
    0x47, 0x66, 0x72, 0x6F, 0x6D, 0x3D, 0x31, 0x35, 0x05, 0x74, 0x6F, 0x3D,
    0x33, 0x30, 0xFF, 0x32
};

uint8_t msg_test_put_stream_from_to[] = {
    0x40, 0x03, 0x06, 0xEA, 0xBD, 0x05, 0x73, 0x74, 0x72, 0x65, 0x61, 0x6D,
    0x64, 0x61, 0x74, 0x61, 0x72, 0x65, 0x63, 0x6F, 0x72, 0x64, 0x65, 0x72,
    0x47, 0x66, 0x72, 0x6F, 0x6D, 0x3D, 0x31, 0x35, 0x05, 0x74, 0x6F, 0x3D,
    0x33, 0x30, 0xFF, 0x32
};

uint8_t msg_test_delete_stream_from_to[] = {
    0x40, 0x04, 0x06, 0xEB, 0xBD, 0x05, 0x73, 0x74, 0x72, 0x65, 0x61, 0x6D,
    0x64, 0x61, 0x74, 0x61, 0x72, 0x65, 0x63, 0x6F, 0x72, 0x64, 0x65, 0x72,
    0x47, 0x66, 0x72, 0x6F, 0x6D, 0x3D, 0x31, 0x35, 0x05, 0x74, 0x6F, 0x3D,
    0x33, 0x30
};

uint32_t msgs_streamer[][2] = {
    {(uint32_t) msg_test_get_wellknown, sizeof (msg_test_get_wellknown)},

    {(uint32_t) msg_test_get_memory, sizeof (msg_test_get_memory)},
    {(uint32_t) msg_test_post_memory, sizeof (msg_test_post_memory)},
    {(uint32_t) msg_test_put_memory, sizeof (msg_test_put_memory)},
    {(uint32_t) msg_test_delete_memory, sizeof (msg_test_delete_memory)},

    {(uint32_t) msg_test_get_memory_addr_val, sizeof (msg_test_get_memory_addr_val)},
    {(uint32_t) msg_test_post_memory_addr_val, sizeof (msg_test_post_memory_addr_val)},
    {(uint32_t) msg_test_put_memory_addr_val, sizeof (msg_test_put_memory_addr_val)},
    {(uint32_t) msg_test_delete_memory_addr_val, sizeof (msg_test_delete_memory_addr_val)},

    {(uint32_t) msg_test_get_stream, sizeof (msg_test_get_stream)},
    {(uint32_t) msg_test_post_stream, sizeof (msg_test_post_stream)},
    {(uint32_t) msg_test_put_stream, sizeof (msg_test_put_stream)},
    {(uint32_t) msg_test_delete_stream, sizeof (msg_test_delete_stream)},

    {(uint32_t) msg_test_get_stream_current, sizeof (msg_test_get_stream_current)},
    {(uint32_t) msg_test_post_stream_current, sizeof (msg_test_post_stream_current)},
    {(uint32_t) msg_test_put_stream_current, sizeof (msg_test_put_stream_current)},
    {(uint32_t) msg_test_delete_stream_current, sizeof (msg_test_delete_stream_current)},

    {(uint32_t) msg_test_get_stream_last, sizeof (msg_test_get_stream_last)},
    {(uint32_t) msg_test_post_stream_last, sizeof (msg_test_post_stream_last)},
    {(uint32_t) msg_test_put_stream_last, sizeof (msg_test_put_stream_last)},
    {(uint32_t) msg_test_delete_stream_last, sizeof (msg_test_delete_stream_last)},

    {(uint32_t) msg_test_get_stream_from_to, sizeof (msg_test_get_stream_from_to)},
    {(uint32_t) msg_test_post_stream_from_to, sizeof (msg_test_post_stream_from_to)},
    {(uint32_t) msg_test_put_stream_from_to, sizeof (msg_test_put_stream_from_to)},
    {(uint32_t) msg_test_delete_stream_from_to, sizeof (msg_test_delete_stream_from_to)}
};*/

/*
 * Simple C Test Suite
 */

void testCoap_make_response()
{
    /*coap_rw_buffer_t *buff;
    for (int i = 0; i < 25; i++)
    {
        buff = MessageHandler((const uint8_t *)msgs_streamer[i][0], msgs_streamer[i][1], "127.0.0.1", 4567);
        if (buff != NULL)
        {
            continue;
        }
        printf(" %%TEST_FAILED%% time=0 testname=test2 (recvtest) message=error message sample\n");
    }*/
}

int main(int argc, char** argv)
{
    printf("%%SUITE_STARTING%% handlertest\n");
    printf("%%SUITE_STARTED%%\n");
    InitHandler(250, 8);

    printf("%%TEST_STARTED%%  testCoap_make_response (handlertest)\n");
    testCoap_make_response();
    printf("%%TEST_FINISHED%% time=0 testCoap_make_response (handlertest)\n");

    printf("%%SUITE_FINISHED%% time=0\n");

    return (EXIT_SUCCESS);
}

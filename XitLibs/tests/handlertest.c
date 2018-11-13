/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>
#include <stdlib.h>
#include "src/coap/coap.h"
#include "CommandModule.h"
#include "StreamDataRecorder.h"
#include "extension/ext_handler.h"

#include "coap_messages_example.h"
/*
 * Simple C Test Suite
 */

void testCoap_make_response()
{
    coap_rw_buffer_t *buff;
    for (int i = 0; i < 25; i++)
    {
        buff = ext_handler((const uint8_t *)msgs_streamer[i][0], msgs_streamer[i][1], "127.0.0.1", 4567);
        if (buff != NULL)
        {
            continue;
        }
        printf(" %%TEST_FAILED%% time=0 testname=test2 (recvtest) message=error message sample\n");
    }
}

int main(int argc, char** argv)
{
    printf("%%SUITE_STARTING%% handlertest\n");
    printf("%%SUITE_STARTED%%\n");
    ext_init_handler(250, 8);

    printf("%%TEST_STARTED%%  testCoap_make_response (handlertest)\n");
    testCoap_make_response();
    printf("%%TEST_FINISHED%% time=0 testCoap_make_response (handlertest)\n");

    printf("%%SUITE_FINISHED%% time=0\n");

    return (EXIT_SUCCESS);
}

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

#include "coap_messages_example.h"

/*
 * Simple C Test Suite
 */

coap_packet_t inpkt;
coap_packet_t outpkt;
uint8_t buffer[4096];
uint8_t scratch_b[4096];
uint8_t message_b[4096];
coap_rw_buffer_t scratch = {scratch_b, sizeof (scratch_b)};
coap_rw_buffer_t message = {message_b, sizeof (message_b)};

void test1()
{
    int rc, i, j;
    printf("coaptest test 1\n");
    uint8_t media_option = COAP_CONTENTTYPE_APPLICATION_XML;
    for (i = 0; i < 25; i++)
    {
        memset((void *) &inpkt, 0, sizeof (coap_packet_t));
        /*==1= Parse package =================================================*/
        rc = coap_parse(
                &inpkt,
                (uint8_t *) msgs_streamer[i][0],
                msgs_streamer[i][1] );
        /*==2= Handle request ================================================*/
        if (rc == 0)
            rc = coap_handle_req(&scratch, &inpkt, &outpkt, 0, "127.0.0.1", 4567);
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
            if ((inpkt.hdr.code == COAP_METHOD_GET))
                coap_make_response(&scratch, &outpkt, 0,
                    (uint8_t*) scratch.p, scratch.len,
                    inpkt.hdr.id[0], inpkt.hdr.id[1],
                    inpkt.tok_p, inpkt.tok_len, COAP_RSPCODE_CONTENT,
                    media_option);
            else
                coap_make_response(&scratch, &outpkt, 0,
                    (uint8_t*) scratch.p, scratch.len,
                    inpkt.hdr.id[0], inpkt.hdr.id[1],
                    inpkt.tok_p, inpkt.tok_len, COAP_RSPCODE_CHANGED,
                    media_option);
        }
        else
        {
            switch (rc)
            {
                case INVALID_PARAMETERS_ERROR:
                    coap_make_response(&scratch, &outpkt, 0,
                            (uint8_t*) scratch.p, scratch.len,
                            inpkt.hdr.id[0], inpkt.hdr.id[1],
                            inpkt.tok_p, inpkt.tok_len, COAP_RSPCODE_BAD_REQUEST,
                            media_option);
                    break;
                case NO_COMMAND_ERROR:
                    coap_make_response(&scratch, &outpkt, 0,
                            (uint8_t*) scratch.p, scratch.len,
                            inpkt.hdr.id[0], inpkt.hdr.id[1],
                            inpkt.tok_p, inpkt.tok_len, COAP_RSPCODE_NOT_FOUND,
                            media_option);
                    break;
                default:
                    coap_make_response(&scratch, &outpkt, 0,
                            (uint8_t*) scratch.p, scratch.len,
                            inpkt.hdr.id[0], inpkt.hdr.id[1],
                            inpkt.tok_p, inpkt.tok_len, COAP_RSPCODE_BAD_REQUEST,
                            media_option);
                    break;
            }
        }
        /*==4= Build response package ========================================*/
        message.len = 4096;
        rc = coap_build(message.p, &message.len, &outpkt, NULL, NULL);
        /*==5= Transmitt package =============================================*/
        if (rc == 0)
        {
            printf("Dump:");
            for (j = 0; j < message.len; j++)
            {
                printf(" %02X", message.p[j]);
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

    int i;
    InitCommands();
    InitStreamRecorder(file, 48, 250, 8);
    for (i = 0; i < 1000; i++)
        if (i == 263)
            AddSample();
        else
            AddSample();

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

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   coap_test.c
 * Author: xitre
 *
 * Created on 29 июня 2017 г., 2:28
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "umm_malloc.h"
#include "coap.h"
#include "array.h"
#include "LogModule.h"
#include "CommandModule.h"

Array *AwaitedAnswersArray;
/*
 * Simple C Test Suite
 */
int count1;
int count2;

int release1(ParameterList_t *TempParam)
{
   int  ret_val = 0;

    DBG_LOG_DEBUG("Into release1.\n");
    AddToTransmit("<release1>\r\n\r");
    /* First check to see if the parameters required for the execution of*/
    /* this function appear to be semi-valid.                            */
    if ((TempParam))
    {
        count1 += 1;
    }
    else
    {
        /* One or more of the necessary parameters are invalid.           */
        ret_val = INVALID_PARAMETERS_ERROR;
        AddToTransmit("<INVALID_PARAMETERS_ERROR/>\r\n\r");
        DBG_LOG_WARNING("Invalid parameters.\n");
    }
    AddToTransmit("</release1>\r\n\r");

    return(ret_val);
}
int release2(ParameterList_t *TempParam)
{
   int  ret_val = 0;

    DBG_LOG_DEBUG("Into release2.\n");
    AddToTransmit("<release2>\r\n\r");
    /* First check to see if the parameters required for the execution of*/
    /* this function appear to be semi-valid.                            */
    if ((TempParam))
    {
        count2 += 1;
    }
    else
    {
        /* One or more of the necessary parameters are invalid.           */
        ret_val = INVALID_PARAMETERS_ERROR;
        AddToTransmit("<INVALID_PARAMETERS_ERROR/>\r\n\r");
        DBG_LOG_WARNING("Invalid parameters.\n");
    }
    AddToTransmit("</release2>\r\n\r");

    return(ret_val);
}

void test1() {
    int idx;
    int count_res1 = 0;
    int count_res2 = 0;
    char *callback;
    char *release_cmd;
    coap_token_record *answer;
    printf("coap_test test 1\n");
    count1 = 0;
    count2 = 0;
//    AddCommand("/RELEASE1", "</RELEASE1>", release1);
//    AddCommand("/RELEASE2", "</RELEASE2>", release2);
    AwaitedAnswersArray = coap_get_waiting_list();
    
//    for( idx=0; idx<6553500; ++idx ) {
    for( idx=0; idx<3500; ++idx ) {
        callback = 0;
        release_cmd = 0;
        switch( rand() % 4 ) {
            case  0:
                coap_clock();
                break;
            case  1:
                callback = "/test";
                release_cmd = 0;
                break;
            case  2:
                callback = "/test";
                release_cmd = "/RELEASE1";
                count_res1 += 1;
                break;
            case  3:
                callback = "/test";
                release_cmd = "/RELEASE2";
                count_res2 += 1;
                break;
            default: 
                break;
        }
        if (callback)
        {
            answer = (coap_token_record *)umm_calloc(1,sizeof(coap_token_record));
            memcpy(answer->p,"test00",6);
            DBG_LOG_TRACE("add tkn %s clb %s.\n","test00",callback);
            if (release_cmd)
            {
                DBG_LOG_TRACE("release %s.\n",release_cmd);
            }
            answer->len = 6;
            answer->tok_wait = 4;
            answer->callback = callback;
            answer->used = 0;
            if (release_cmd)
            {
                strncpy(answer->release,release_cmd,MAXRELEASESTR);
            }
            else
                answer->release[0] = 0;
            if (array_add(AwaitedAnswersArray, (void *)answer) != 0)
            {
                umm_free((void *)answer);
                return -1;
            }
        }
    }
    for( idx=0; idx<10; ++idx ) {
        coap_clock();
    }
    if (count1 != count_res1)
        printf("%%TEST_FAILED%% time=0 testname=Waiting_Msg_Release_Test (coap_test) message=Error\n");
    if (count2 != count_res2)
        printf("%%TEST_FAILED%% time=0 testname=Waiting_Msg_Release_Test (coap_test) message=Error\n");
    return;
}

void test2() {
    printf("coap_test test 2\n");
    //printf("%%TEST_FAILED%% time=0 testname=test2 (coap_test) message=error message sample\n");
}

int main(int argc, char** argv) {
    clock_t t,tl;
    
    InitHandler(BASESTATION);
    EEGRecorderInit(0,250);
    
    printf("%%SUITE_STARTING%% coap_test\n");
    printf("%%SUITE_STARTED%%\n");
    t = clock();

    printf("%%TEST_STARTED%% Waiting_Msg_Release_Test (coap_test)\n");
    tl = clock();
    test1();
    tl = clock() - tl;
    printf("%%TEST_FINISHED%% time=%f Waiting_Msg_Release_Test (coap_test) \n",
                                    ((float)t)/CLOCKS_PER_SEC);

//    printf("%%TEST_STARTED%% test2 (coap_test)\n");
//    tl = clock();
//    test2();
//    tl = clock() - tl;
//    printf("%%TEST_FINISHED%% time=%f test2 (coap_test) \n",
//                                    ((float)t)/CLOCKS_PER_SEC);

    t = clock() - t;
    printf("%%SUITE_FINISHED%% time=%f\n",
                                    ((float)t)/CLOCKS_PER_SEC);

    return (EXIT_SUCCESS);
}

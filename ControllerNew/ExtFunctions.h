
/* Global headers ------------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "LibConfig.h"
#include "ConfigMem.h"
#include "InOutBuffer.h"
#include "CommandModule.h"
#include "StreamDataRecorder.h"
#ifndef CPU
    #include "tim.h"
    #include "usart.h"
#endif
/*============================================================================*/

#ifndef __EXTERNAL_H__
#define __EXTERNAL_H__  

#ifdef __cplusplus
extern "C" {
#endif
    
/* Public variables ----------------------------------------------------------*/
#ifdef CPU
    extern struct sockaddr_in cliaddr_hd;
    extern int fd_hd;
#endif
extern uint8_t buffer[STRING_SIZE];
extern uint8_t buffer2[10];
extern uint8_t scratch_raw[4096];
extern uint8_t id_out;
extern size_t pktlen;
extern uint8_t buffer2[10];
extern uint8_t buf[4096];
extern uint8_t content_type;
extern uint8_t bufsa[1024];
extern int size_parts;
extern int size_parts_cur;
/*============================================================================*/

/* Public function prototypes ------------------------------------------------*/
void InitUDP(void);
void SetLeds(uint8_t q_green,uint8_t q_red,uint8_t q_blue);
void UserOperationHandler(void);
void UserProtocolHandler(void);
int32_t ADC_read_data_c();
/*============================================================================*/

#ifdef __cplusplus
}
#endif

#endif
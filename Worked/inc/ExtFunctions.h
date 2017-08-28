/* Global headers ------------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "LibConfig.h"
#include "ConfigMem.h"
#include "InOutBuffer.h"
#include "CommandModule.h"
#include "coap.h"
#include "StreamDataRecorder.h"
//#ifndef CPU
//    #include "tim.h"
//    #include "usart.h"
//#endif
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
extern coap_rw_buffer_t scratch_buf;
extern size_t pktlen;
extern uint8_t buffer2[10];
extern coap_option_t opt;
extern coap_option_t opt_path;
extern coap_option_t opt_args;
extern coap_packet_t pkt;
extern coap_packet_t rsppkt;
extern uint8_t buf[4096];
extern uint8_t content_type;
extern coap_option_t opt_part;
extern int size_parts;
extern int size_parts_cur;
/*============================================================================*/

/* Public function prototypes ------------------------------------------------*/
void InitUDP(void);
int TransferUDP(const uint8_t *data, const uint32_t datalen,
        const char* address /* = "192.168.1.255" */,
        const uint32_t port /* = 5683 */);
int TransferBroadbandUDP(const uint8_t *data, const uint32_t datalen,
        const uint32_t port /* = 5683 */);
void SetLeds(uint8_t q_green,uint8_t q_red,uint8_t q_blue);
void UserOperationHandler(void);
void UserProtocolHandler(void);
void UserProtocolHandlerThread(void);
/*============================================================================*/

#ifdef __cplusplus
}
#endif

#endif

/* Global headers ------------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "LibConfig.h"
#include "PWMModule.h"
#include "ConfigMem.h"
#include "InOutBuffer.h"
#include "CommandModule.h"
#include "DMAretransmitter.h"
#include "Packet.h"
#include "DistCalc.h"
#include "coap.h"
#include "StreamDataRecorder.h"
#include "FunctionsDiscovery.h"
#include "UpdateModule.h"
#ifndef CPU
//    #include "tim.h"
//    #include "usart.h"
#endif
/*============================================================================*/

#ifndef __HANDLER_H__
#define __HANDLER_H__  

#ifdef __cplusplus
extern "C" {
#endif
    
/* Public variables ----------------------------------------------------------*/
#ifdef CPU
    extern struct sockaddr_in cliaddr_hd;
    extern int fd_hd;
#endif
extern uint8_t scratch_raw[4096];
#ifdef CPU
    extern uint8_t bufsa[4096];
#else    
    extern uint8_t bufsa[1024];
#endif
extern uint8_t id_out;
extern coap_rw_buffer_t scratch_buf;
extern size_t pktlen;
extern coap_option_t opt;
extern coap_option_t opt_path;
extern coap_option_t opt_args;
extern coap_packet_t pkt;
extern coap_packet_t rsppkt;
extern uint8_t content_type;
extern coap_option_t opt_part;
extern int size_parts;
extern int size_parts_cur;
/*============================================================================*/

/* Public function prototypes ------------------------------------------------*/
void InitHandler(DeviceTypeDef device);
void SampleHandler(void);
void ProtocolHandler(void);
void OperationHandler(void);
void CalculationHandler(void);
#ifdef PLATFORM_LINUX
    void VideoFrameHandler(void);
    void VideoFrameInitHandler(void);
    void VideoFrameDeInitHandler(void);
#endif
void UartDistanceHandler(void);
void UartProtocolHandler(char let);
void UartTransferCompleteHandler(void);
void UartReceiveCompleteHandler(void);
void SecClockHandler(void);
void SoftPWMHandler(void);
void StatChangeHandler(void);
int ResetReq();
int Update(ParameterList_t *TempParam);
int Transfer(const uint8_t *data, const uint32_t datalen, const char *_func);
int TransferTo(const uint8_t *data, const uint32_t datalen,
        const char* address /* = "192.168.1.255" */,
        const uint32_t port /* = 5683 */);
int TransferBand(const uint8_t *data, const uint32_t datalen);
void HandlerImage(void);

void SampleSheduler(void);
void SecClockSheduler(void);
/*============================================================================*/

#ifdef __cplusplus
}
#endif

#endif
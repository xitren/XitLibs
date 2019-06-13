/* Global headers ------------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "coap.h"
#include "LibConfig.h"
#include "ConfigMem.h"
#include "InOutBuffer.h"
#include "CommandModule.h"
#include "StreamDataRecorder.h"
#include "CSMACD.h"
#include "LogModule.h"

#ifndef __HANDLER_H__
#define __HANDLER_H__  

#ifdef __cplusplus
extern "C" {
#endif

void InitHandler(const uint32_t sample_frequency, const uint32_t sample_size);
coap_rw_buffer_t *MessageHandlerTextIP(const uint8_t *buf, size_t buflen, char *ip, uint32_t port);
coap_rw_buffer_t *MessageHandlerIntIP(const uint8_t *buf, size_t buflen, uint32_t ipi, uint32_t port);
coap_observer_buffer_t *StreamObserverHandler();
void timer1sHandler(CSMACDController_t *controller);
void timerSampleFreqHandler(void);

#ifdef __cplusplus
}
#endif

#endif
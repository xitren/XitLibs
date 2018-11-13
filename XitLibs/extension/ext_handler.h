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

#ifndef __EXTERNAL_H__
#define __EXTERNAL_H__  

#ifdef __cplusplus
extern "C" {
#endif

void ext_init_handler(const uint32_t sample_frequency, const uint32_t sample_size);
coap_rw_buffer_t *ext_handler(const uint8_t *buf, size_t buflen, char *ip, uint32_t port);

#ifdef __cplusplus
}
#endif

#endif
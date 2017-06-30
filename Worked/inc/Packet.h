
/* Global headers ------------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>
#include "xitlibtypes.h"             /* Application Header.            */
/*============================================================================*/

#ifndef __INPUTPOCKET_H__
#define __INPUTPOCKET_H__  

#ifdef __cplusplus
extern "C" {
#endif

/* Public function prototypes ------------------------------------------------*/
uint16_t Packetize(uint8_t *bytes,const uint16_t size, const uint16_t buffer_size);
uint16_t DePacketize(uint8_t *bytes,const uint16_t size);
int AddToPocketReceive(char str);
int ClearPocketBuffer(void);
char* GetPocketBuffer(unsigned char *size);
/*============================================================================*/

#ifdef __cplusplus
}
#endif

#endif


/* Global headers ------------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>
#include "LibConfig.h"
/*============================================================================*/

#ifndef __BUFFERMODULE_H__
#define __BUFFERMODULE_H__  

/* Public defines ------------------------------------------------------------*/
#define NO_BUFFER_ERROR                            (-1)  /* Denotes that no   */
                                                         /* error was         */
                                                         /* specified on the  */
                                                         /* buffer.           */
#define NO_BUFFER_RECORDS                          (-2)  /* Denotes that the  */
                                                         /* buffer does not   */
                                                         /* have a records to */
                                                         /* process.          */
#define NO_BUFFER_SPACE                            (-3)  /* Denotes that the  */
                                                         /* buffer specified  */
                                                         /* was no            */
                                                         /* space.            */
#define BUFFER_ERROR                               (-4)  /* Denotes that the  */
                                                         /* buffer specified  */
                                                         /* was no            */
                                                         /* space.            */
#define MEMORY_INOUT BUFFER_SIZE*STRING_SIZE+8
/*============================================================================*/

#ifdef __cplusplus
extern "C" {
#endif
  
/* Public function prototypes ------------------------------------------------*/
int InitBuffer();
int AddToTransmit(char *str);
int AddToReceive(const uint8_t *msg, uint32_t size, uint32_t ip, uint32_t port);
int ProceedReceive(uint8_t *msg, uint32_t *size, uint32_t *ip, uint32_t *port);
char* ProceedTransmit(uint32_t *num);
int ClearBuffer();
/*============================================================================*/

#ifdef __cplusplus
}
#endif

#endif
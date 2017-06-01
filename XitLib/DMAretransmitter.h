
/* Global headers ------------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>
#include "CommandModule.h"
/*============================================================================*/

#ifndef __DMARETRANSMITTER_H__
#define __DMARETRANSMITTER_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Public defines ------------------------------------------------------------*/
#define DMA_VECTOR 10
#define DMA_MAX 2
#define MEMORY_DMA sizeof(DMAoccure_t)*DMA_MAX+8
/*============================================================================*/
    
/* Public types --------------------------------------------------------------*/
typedef int (*CommandCallbackDMA_t)(uint8_t *vector,uint32_t _tsize);
typedef struct _tagDMAoccure_t
{
   uint8_t            bytes[DMA_VECTOR];
   uint32_t           tsize;
   uint32_t           size;
   CommandCallbackDMA_t  CallbackFunction;
} DMAoccure_t;
/*============================================================================*/
    
/* Public function prototypes ------------------------------------------------*/
uint8_t DMAGetNext(uint8_t *stat,uint8_t _in);
void DMAAddSample(DMAoccure_t *_other);
void DMAClear(void);
/*============================================================================*/

#ifdef __cplusplus
}
#endif

#endif

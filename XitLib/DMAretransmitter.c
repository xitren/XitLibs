// ----------------------------------------------------------------------------
//
// DMAretransmitter.c - DMA tables & API
//
// ----------------------------------------------------------------------------
//
// A.Gusev 04.09.2017 - Original
//
// ----------------------------------------------------------------------------

/* Local headers -------------------------------------------------------------*/
#include "DMAretransmitter.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
/*============================================================================*/

/* Private variables ---------------------------------------------------------*/
#ifdef AVR
static DMAoccure_t DMATable[DMA_MAX];
uint32_t DMA_samples_cnt = 0;
uint32_t DMA_readed_cnt = 0;
#endif
/*============================================================================*/

/* Functions declaration -----------------------------------------------------*/
uint8_t DMAGetNext(uint8_t *stat,uint8_t _in)
{
//#ifndef AVR
//    if (DMA_readed_cnt != DMA_samples_cnt)
//        *stat = 1;
//    else
//    {
//        *stat = 0;
//        return 0;
//    }
//    uint32_t _tadress = (DMA_readed_cnt)%DMA_MAX;
//    if (DMATable[_tadress].tsize > 0)
//        DMATable[_tadress].bytes
//                    [(DMATable[_tadress].tsize-1)] = _in;
//    if (DMATable[_tadress].tsize == 
//            DMATable[_tadress].size)
//    {
//        (*(DMATable[_tadress].CallbackFunction))
//                ((uint8_t *)DMATable[_tadress].bytes,
//                DMATable[_tadress].tsize);
//        DMA_readed_cnt++;
//    }
//    if ((DMATable[_tadress].tsize < 
//            DMATable[_tadress].size) 
//            && (DMA_readed_cnt != DMA_samples_cnt))
//    {
//        return DMATable[_tadress].bytes
//                [(DMATable[_tadress].tsize)++];
//    }
//    else
//        *stat = 0;
//#endif
    return 0;
}
void DMAAddSample(DMAoccure_t *_other)
{
//#ifndef AVR
//    DMATable[(DMA_samples_cnt++)%DMA_MAX] = *_other;
//    if ((DMA_samples_cnt - DMA_readed_cnt) > DMA_MAX)
//        DMA_readed_cnt = DMA_samples_cnt - DMA_MAX;
//#endif
    return;
}
void DMAClear(void)
{
//#ifndef AVR
//    DMA_samples_cnt = 0;
//    DMA_readed_cnt = 0;
//#endif
    return;
}
/*============================================================================*/
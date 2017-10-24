// ----------------------------------------------------------------------------
//
// DistCalc.c - API for distant calculation and perfomance measurement
//
// ----------------------------------------------------------------------------
//
// A.Gusev 04.09.2017 - Original
//
// ----------------------------------------------------------------------------

/* Local headers -------------------------------------------------------------*/
#include "DistCalc.h"
#include "Handler.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*============================================================================*/

/* Private defines -----------------------------------------------------------*/
#define MAXEXTMEM 4
#define EXTMEMTIMEOUT 10
#define EXTMEMBUFFER 20*4
/*============================================================================*/

/* Private extern ------------------------------------------------------------*/
extern coap_rw_buffer_t scratch_buf;
/*============================================================================*/

/* Private structures --------------------------------------------------------*/
#ifdef EXTMEMSERVER
    typedef struct _tagExtMemMapSrv_t
    {
       uint8_t *_ptr;
       uint32_t _dlen;
       uint32_t _extid;
       uint8_t  isSet;
       uint8_t  clock;
    } ExtMem_t;
#else
    typedef struct _tagExtMemMap_t
    {
       uint32_t _intid;
       uint32_t _extid;
       uint8_t  isSet;
       uint8_t  clock;
    } ExtMem_t;
#endif
/*============================================================================*/

/* Private variables ---------------------------------------------------------*/
uint32_t now_clock = 0;
uint32_t free_cycles = 0;
uint32_t max_free_cycles = 1;
uint32_t last_free_cycles = 0;
static char path_mem_buf[100];
static char path_arg_buf[100];
static ExtMem_t memMap[MAXEXTMEM];
uint32_t memMapCnt = 0;
static uint8_t memMapBuffer[EXTMEMBUFFER];
uint32_t memMapBufferCnt = 0;
#ifdef EXTMEMSERVER
    uint32_t extCnt = 1;
    uint8_t rc;
#endif
/*============================================================================*/
    
/* Private constants ---------------------------------------------------------*/
const char *path_mem="extmemory";
#ifdef EXTMEMSERVER
#else
    const char *path_mem_clb_cr="/CALLBACK/EXTMEMORY/CREATE";
    const char *path_mem_clb_ret="/CALLBACK/EXTMEMORY/RETURN";
#endif
/*============================================================================*/

/* Functions declaration -----------------------------------------------------*/
void ClearExtMem(void)
{
    memMapCnt = 0;
    return;
}
void ExtMemClock(void)
{
    int i;
    for (i=0;i<memMapCnt;i++)
        memMap[i].clock += 1;
    return;
}
void FreeCycle(void)
{
  free_cycles++;
  return;
}
uint32_t GetCycle(void)
{
  return last_free_cycles;
}
uint32_t GetMaxCycle(void)
{
  return max_free_cycles;
}
uint32_t GetPercent(void)
{
  return (last_free_cycles*100)/(abs(max_free_cycles)+1);
}
uint32_t GetClock(void)
{
  return now_clock;
}
void SetClock(int _clock)
{
  now_clock = _clock;
  return;
}
void ClockHandler(void)
{
  now_clock++;
  last_free_cycles = free_cycles;
  if (last_free_cycles > max_free_cycles)
    max_free_cycles = last_free_cycles;
  free_cycles = 0;
  ExtMemClock();
  return;
}
/*============================================================================*/
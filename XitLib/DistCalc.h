// ----------------------------------------------------------------------------
//
// DistCalc.h - API for distant calculation and perfomance measurement
//
// ----------------------------------------------------------------------------

/* Global headers ------------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>
#include "xitlibtypes.h"
#include "coap.h"
/*============================================================================*/

#ifndef __CALCMODULE_H__
#define __CALCMODULE_H__  

#ifdef __cplusplus
extern "C" {
#endif
    
/* Public defines ------------------------------------------------------------*/
/*============================================================================*/
    
/* External variable ---------------------------------------------------------*/
/*============================================================================*/

/* Public function prototypes ------------------------------------------------*/
void FreeCycle(void);
uint32_t GetCycle(void);
uint32_t GetMaxCycle(void);
uint32_t GetPercent(void);
void SetClock(int _clock);
uint32_t GetClock(void);
void ClockHandler(void);
int CalculationPercentCycles(uint8_t Method, uint8_t MediaType, 
        ParameterList_t *TempParam, uint8_t *data, uint32_t *data_size);
int ClockCommand(uint8_t Method, uint8_t MediaType, 
        ParameterList_t *TempParam, uint8_t *data, uint32_t *data_size);
int CalculationMaxCycles(uint8_t Method, uint8_t MediaType, 
        ParameterList_t *TempParam, uint8_t *data, uint32_t *data_size);
int CalculationFreeCycles(uint8_t Method, uint8_t MediaType, 
        ParameterList_t *TempParam, uint8_t *data, uint32_t *data_size);
/*============================================================================*/

#ifdef __cplusplus
}
#endif

#endif
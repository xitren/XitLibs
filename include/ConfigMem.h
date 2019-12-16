// ----------------------------------------------------------------------------
//
// ConfigMem.h - Contains configuration registers and system API
//
// ----------------------------------------------------------------------------

/* Global headers ------------------------------------------------------------*/
#include <stdio.h>
#include "xitlibtypes.h"
//#include "stm32f4xx_hal.h"
/*============================================================================*/

/* Public defines ------------------------------------------------------------*/
#define CFG_SIZE 0x100
#define MEMORY_CONFIG 4*CFG_SIZE
/*============================================================================*/

#ifndef __MEMORY_CONFIG_H__
#define __MEMORY_CONFIG_H__  

#ifdef __cplusplus
extern "C" {
#endif

/* Public variables ----------------------------------------------------------*/
extern const char* global_link_memory[2];
/*============================================================================*/

/* Public function prototypes ------------------------------------------------*/
void InitCfgMem(void);
void WriteMem(uint32_t _adr, uint32_t _val);
uint32_t ReadMem(uint32_t _adr);
int MemoryCommand(uint8_t Method, uint8_t MediaType, ParameterList_t *TempParam,
				uint8_t *data, uint32_t *data_size, uint32_t buffer_size);
/*============================================================================*/

#ifdef __cplusplus
}
#endif

#endif

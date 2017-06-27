
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
#define EXT_MEM_NO_FUNCTION_ERROR                  (-1)  /* Denotes that no   */
                                                         /* command was       */
                                                         /* specified to the  */
                                                         /* parser.           */
#define EXT_MEM_INVALID_COMMAND_ERROR              (-2)  /* Denotes that the  */
                                                         /* Command does not  */
                                                         /* exist for         */
                                                         /* processing.       */                  
#define EXT_MEM_TIMEOUT_ERROR                      (-3)  /* Denotes that the  */
                                                         /* Command specified */
                                                         /* was the Exit      */
                                                         /* Command.          */
#define EXT_MEM_FUNCTION_BUFFERSIZE_ERROR          (-4)  /* Denotes that an   */
                                                         /* error occurred in */
                                                         /* execution of the  */
                                                         /* Command Function. */
/*============================================================================*/
    
/* External variable ---------------------------------------------------------*/
extern coap_rw_buffer_t scratch_buf;
/*============================================================================*/

/* Public function prototypes ------------------------------------------------*/
void FreeCycle(void);
uint32_t GetCycle(void);
uint32_t GetMaxCycle(void);
uint32_t GetPercent(void);
void SetClock(int _clock);
uint32_t GetClock(void);
void ClockHandler(void);
uint32_t GetMemExtByInt(uint32_t _intid);
void ExtMemClock(void);
void ClearExtMem(void);
#ifdef EXTMEMSERVER
    uint8_t* GetPointer(uint32_t _extid);
    uint32_t GetSize(uint32_t _extid);
    int ExtMemCreateReq(ParameterList_t *TempParam);
    int ExtMemGetReq(ParameterList_t *TempParam);
    int ExtMemDeleteReq(ParameterList_t *TempParam);
    int ExtMemClearReq(ParameterList_t *TempParam);
#else
//    int DeleteExtMemReq(uint32_t _intid);
//    int CreateExtMemReq(uint8_t *data, uint32_t *datalen, uint32_t _intid);
//    int ResetExtMemReq();
//    int CallbackExtMemCreateReq(ParameterList_t *TempParam);
//    int GetExtMemReq(uint8_t *data, uint32_t *datalen, uint32_t _intid);
//    int CallbackExtMemGetReq(ParameterList_t *TempParam);
#endif
/*============================================================================*/

#ifdef __cplusplus
}
#endif

#endif
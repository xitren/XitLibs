
/* Global headers ------------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>
#include "LibConfig.h"
#include "xitlibtypes.h"             /* Application Header.            */
/*============================================================================*/

#ifndef __LOGGERMODULE_H__
#define __LOGGERMODULE_H__    

/* Public defines ------------------------------------------------------------*/
#define NO_LOGGER_ERROR                            (-1)  /* Denotes that no   */
                                                         /* error was         */
                                                         /* specified on the  */
                                                         /* buffer.           */
#define NO_LOGGER_SPACE                            (-3)  /* Denotes that the  */
                                                         /* buffer specified  */
                                                         /* was no            */
                                                         /* space.            */
#define MEMORY_LOGGER LOGGER_SIZE*STRING_SIZE+8
/*============================================================================*/

#ifdef __cplusplus
extern "C" {
#endif
  
/* Public function prototypes ------------------------------------------------*/
int AddToLog(char *str, int lvl);
char* ProceedLog(uint32_t *num);
int ClearLog(void);
int LOGRead(ParameterList_t *TempParam);
/*============================================================================*/

#ifdef __cplusplus
}
#endif

#endif
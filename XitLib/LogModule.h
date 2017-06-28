
/* Global headers ------------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>
#include "LibConfig.h"
#include "xitlibtypes.h"             /* Application Header.            */
/*============================================================================*/

#ifndef __LOGGERMODULE_H__
#define __LOGGERMODULE_H__    

// ----------------------------------------------------------------------------
//
// There are macros to handle the following decreasing levels of detail:
//
// 6 = TRACE
// 5 = DEBUG
// 4 = CRITICAL
// 3 = ERROR
// 2 = WARNING
// 1 = INFO
// 0 = FORCE - The printf is always compiled in and is called only when
//              the first parameter to the macro is non-0
//
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
//
// FIXME: Currently the macros are defined at compile time, which means that
//        the debug level is fixed. It will be possible in later versions to
//        set up run time control of debug info at the expense of speed and
//        code size
// ----------------------------------------------------------------------------

#undef DBG_LOG_TRACE
#undef DBG_LOG_DEBUG
#undef DBG_LOG_CRITICAL
#undef DBG_LOG_ERROR
#undef DBG_LOG_WARNING
#undef DBG_LOG_INFO
#undef DBG_LOG_FORCE

// ----------------------------------------------------------------------------

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

#ifdef DEBUG
    #define DBG_LOG_TRACE( string ) AddToLog( string, 6 )
    #define DBG_LOG_DEBUG( string ) AddToLog( string, 5 )
    #define DBG_LOG_CRITICAL( string ) AddToLog( string, 4 )
    #define DBG_LOG_ERROR( string ) AddToLog( string, 3 )
    #define DBG_LOG_WARNING( string ) AddToLog( string, 2 )
    #define DBG_LOG_INFO( string ) AddToLog( string, 1 )
    #define DBG_LOG_FORCE( force, string ) {if(force) {AddToLog( string, 0 );}}
    #define DBG_LOG_PREPARE( buffer, max_size, format, ... ) {snprintf( buffer, max_size, format, ## __VA_ARGS__  );}
#else
    #define DBG_LOG_TRACE( string ) 
    #define DBG_LOG_DEBUG( string ) 
    #define DBG_LOG_CRITICAL( string ) 
    #define DBG_LOG_ERROR( string ) 
    #define DBG_LOG_WARNING( string ) 
    #define DBG_LOG_INFO( string ) 
    #define DBG_LOG_FORCE( force, string ) {if(force) {AddToLog( string, 0 );}}
    #define DBG_LOG_PREPARE( buffer, max_size, format, ... ) 
#endif
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
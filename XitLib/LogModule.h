
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
    #define DBG_LOG_TRACE( format, ... ) {size_glob = snprintf( buf_glob, STRING_SIZE, format, ## __VA_ARGS__  );AddToLog( buf_glob, size_glob, 6 );}
    #define DBG_LOG_DEBUG( format, ... ) {size_glob = snprintf( buf_glob, STRING_SIZE, format, ## __VA_ARGS__  );AddToLog( buf_glob, size_glob, 5 );}
    #define DBG_LOG_CRITICAL( format, ... ) {size_glob = snprintf( buf_glob, STRING_SIZE, format, ## __VA_ARGS__  );AddToLog( buf_glob, size_glob, 4 );}
    #define DBG_LOG_ERROR( format, ... ) {size_glob = snprintf( buf_glob, STRING_SIZE, format, ## __VA_ARGS__  );AddToLog( buf_glob, size_glob, 3 );}
    #define DBG_LOG_WARNING( format, ... ) {size_glob = snprintf( buf_glob, STRING_SIZE, format, ## __VA_ARGS__  );AddToLog( buf_glob, size_glob, 2 );}
    #define DBG_LOG_INFO( format, ... ) {size_glob = snprintf( buf_glob, STRING_SIZE, format, ## __VA_ARGS__  );AddToLog( buf_glob, size_glob, 1 );}
    #define DBG_LOG_FORCE( force, format, ... ) {if(force) {size_glob = snprintf( buf_glob, STRING_SIZE, format, ## __VA_ARGS__  );AddToLog( buf_glob, size_glob, 1 );}}
#else
    #define DBG_LOG_TRACE( format, ... ) 
    #define DBG_LOG_DEBUG( format, ... ) 
    #define DBG_LOG_CRITICAL( format, ... ) 
    #define DBG_LOG_ERROR( format, ... ) 
    #define DBG_LOG_WARNING( format, ... ) 
    #define DBG_LOG_INFO( format, ... ) 
    #define DBG_LOG_FORCE( force, format, ... ) {if(force) {size_glob = snprintf( buf_glob, STRING_SIZE, format, ## __VA_ARGS__  );AddToLog( buf_glob, size_glob, 1 );}}
#endif
/*============================================================================*/

#ifdef __cplusplus
extern "C" {
#endif
  
/* Public function prototypes ------------------------------------------------*/
extern char buf_glob[STRING_SIZE];
extern uint32_t size_glob;
/*============================================================================*/

/* Public function prototypes ------------------------------------------------*/
int AddToLog(const char *str, uint32_t N, int lvl);
char* ProceedLog(uint32_t *num);
int ClearLog(void);
int LOGRead(ParameterList_t *TempParam);
/*============================================================================*/

#ifdef __cplusplus
}
#endif

#endif
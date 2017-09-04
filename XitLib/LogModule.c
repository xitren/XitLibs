// ----------------------------------------------------------------------------
//
// LogModule.c - File and in meory logger with 7 levels
//
// ----------------------------------------------------------------------------
//
// A.Gusev 04.09.2017 - Original
//
// ----------------------------------------------------------------------------

/* Local headers -------------------------------------------------------------*/
#include <time.h>
#include <string.h>
#include "LogModule.h"
#include "ConfigMem.h"
#include "InOutBuffer.h"
/*============================================================================*/

/* Private variables ---------------------------------------------------------*/
#define BUFFER_LOGGER LOGGER_SIZE*STRING_SIZE
char log_buffer[LOGGER_SIZE][STRING_SIZE];
char* def_filename = "serverlog.log";
uint32_t LogCnt = 0;
char buf_glob[STRING_SIZE];
uint32_t size_glob;
/*============================================================================*/

/* Private functions defines -------------------------------------------------*/
int WriteToFile(char* filename);
/*============================================================================*/

/* Functions declaration -----------------------------------------------------*/
int AddToLog(const char *str, uint32_t N, int lvl)
{
    if ((str == NULL))
    {
        DBG_LOG_ERROR("AddToLog argument is NULL\n");
        return 0;
    }
    int ret_val = NO_LOGGER_ERROR;
    if (N > STRING_SIZE)
        N = STRING_SIZE;
    if ((uint32_t)lvl > ReadMem(REG_LOG_LVL))
    {
        return(ret_val);
    }
    #ifdef PLATFORM_WINDOWS
        printf("LOGGER<%d>:--//internal//-- %s",lvl,str);
    #else
        printf("LOGGER<%d>:--//internal//-- %s\r",lvl,str);
    #endif

    #ifdef CPU
        if ( ((LogCnt+N) + 1) >= BUFFER_LOGGER )
        {
            WriteToFile(def_filename);
            ClearLog();
        }
    #endif
   
    if ( ((LogCnt+N) + 1) < BUFFER_LOGGER )
    {
        strncpy((((char*)log_buffer)+LogCnt),(const char*)str,N-1);
        LogCnt += N-1;
        strncpy((((char*)log_buffer)+LogCnt),"\n",1);
        LogCnt += 1;
    }
    else
    {
        ret_val = NO_LOGGER_SPACE;
    }
   
    return(ret_val);
}

char* ProceedLog(uint32_t *num)
{
    if ((num == NULL))
    {
        DBG_LOG_ERROR("ProceedLog argument is NULL\n");
        return 0;
    }
    char* ret_val = 0;

    if (LogCnt)
    {
        (*num) = LogCnt;
        #ifdef CPU
            WriteToFile(def_filename);
        #endif
        LogCnt = 0;
        ret_val = (char*)log_buffer;
    }
    else
    {
        *num = 0;
        ret_val = (char*)log_buffer;
    }

    return(ret_val);
}

int ClearLog(void)
{
    int ret_val = NO_LOGGER_ERROR;
    LogCnt = 0;
    return(ret_val);
}

int WriteToFile(char* filename) {
    if ((filename == NULL))
    {
        DBG_LOG_ERROR("WriteToFile argument is NULL\n");
        return 0;
    }
    FILE *logFile = fopen(filename, "a+"); 
    // a+ (create + append) option will allow appending which is useful in a log file
    if (logFile == NULL) {
        DBG_LOG_ERROR("Cant open serverlog.log\n");
        DBG_LOG_ERROR("Cant save logs\n");
        return 0;
    }
    fwrite((char*)log_buffer, 1, LogCnt, logFile);
    fclose(logFile);
    return 1;
}
   /* The following function is responsible for reading data that was   */
   /* stored in memory.  The function reads a fixed number of bytes.    */
   /* This function returns zero if successful                          */
   /* and a negative value if an error occurred.                        */
int LOGRead(ParameterList_t *TempParam)
{
    int  ret_val = 0;
    int  Adress = -1;
    char buffer[STRING_SIZE];
    int i;
    char* log;
    uint32_t N;

    DBG_LOG_TRACE("Into LOGRead.\n");
    if ((TempParam == NULL))
    {
        DBG_LOG_ERROR("LOGRead argument is NULL\n");
        return 0;
    }
    AddToTransmit("<LOG>\r\n\r");
    /* First check to see if the parameters required for the execution of*/
    /* this function appear to be semi-valid.                            */
    if ((TempParam))
    {
        log = ProceedLog(&N);
        DBG_LOG_TRACE("N=%d.\n",N);
        log[N] = 0;
        AddToTransmit(log);
    }
    else
    {
        /* One or more of the necessary parameters are invalid.           */
        ret_val = -6;
        AddToTransmit("<INVALID_PARAMETERS_ERROR/>\r\n\r");
        DBG_LOG_WARNING("Invalid parameters.\n");
    }
    AddToTransmit("</LOG>\r\n\r");

    return(ret_val);
}
/*============================================================================*/
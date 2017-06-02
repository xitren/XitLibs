
/* Local headers -------------------------------------------------------------*/
#include <time.h>
#include <string.h>
#include "LogModule.h"
#include "ConfigMem.h"
/*============================================================================*/

/* Private variables ---------------------------------------------------------*/
char log_buffer[LOGGER_SIZE][STRING_SIZE];
char* def_filename = "serverlog.log";
uint32_t LogCnt = 0;
/*============================================================================*/

/* Private functions defines -------------------------------------------------*/
int WriteToFile(char* filename);
/*============================================================================*/

/* Functions declaration -----------------------------------------------------*/
int AddToLog(char *str, int lvl)
{
    int ret_val = NO_LOGGER_ERROR;
   
    if ((uint32_t)lvl > ReadMem(REG_LOG_LVL))
        return(ret_val);
    
    #ifdef PLATFORM_WINDOWS
        printf("LOGGER<%d>:--//internal//-- %s",lvl,str);
    #else
        printf("LOGGER<%d>:--//internal//-- %s\r",lvl,str);
    #endif

    #ifdef CPU
        if ( !(( ((LogCnt+strlen(str))/STRING_SIZE) + 1) < BUFFER_SIZE) )
        {
            WriteToFile(def_filename);
            ClearLog();
        }
    #endif
   
    if ( ( ((LogCnt+strlen(str))/STRING_SIZE) + 1) < BUFFER_SIZE)
    {
        strncpy(((char*)log_buffer)+LogCnt,(const char*)str,strlen(str));
        LogCnt += strlen(str);
    }
    else
    {
        ret_val = NO_LOGGER_SPACE;
    }
   
    return(ret_val);
}

char* ProceedLog(uint32_t *num)
{
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
        ret_val = 0;
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
    FILE *logFile = fopen(filename, "a+"); 
    // a+ (create + append) option will allow appending which is useful in a log file
    if (logFile == NULL) {
        perror("Ошибка при открытии serverlog.log - логи не будут сохранены.\r\n\r");
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

    AddToLog("Into LOGRead.\n", 1);
    AddToTransmit("<LOG>\r\n\r");
    /* First check to see if the parameters required for the execution of*/
    /* this function appear to be semi-valid.                            */
    if ((TempParam))
    {
        log = ProceedLog(&N);
        log[N] = 0;
        AddToTransmit(log);
    }
    else
    {
        /* One or more of the necessary parameters are invalid.           */
        ret_val = -6;
        AddToTransmit("<INVALID_PARAMETERS_ERROR/>\r\n\r");
        AddToLog("Invalid parameters.\n", 1);
    }
    AddToTransmit("</LOG>\r\n\r");

    return(ret_val);
}
/*============================================================================*/
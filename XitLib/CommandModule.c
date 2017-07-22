
/* Local headers -------------------------------------------------------------*/
#include <string.h>
#include <stdlib.h>
#include "LibConfig.h"
#include "CommandModule.h"
#include "InOutBuffer.h"
#include "ConfigMem.h"
#include "DistCalc.h"
#include "StreamDataRecorder.h"
#include "FunctionsDiscovery.h"
#include "UpdateModule.h"
#include "generatorModule.h"
#include "VideoModule.h"
#include "LogModule.h"
#include "array.h"
#include "deque.h"
#include "umm_malloc.h"
/*============================================================================*/                           

/* Private structures --------------------------------------------------------*/
   /* The following type definition represents the structure which holds*/
   /* information used in the interpretation and execution of Commands. */
typedef struct _tagCommandTable_t
{
   char                 *CommandName;
   char                 *Link;
   CommandFunction_t    CommandFunction;
} CommandTable_t;
/*============================================================================*/

/* Private variables ---------------------------------------------------------*/
   /* Internal Variables to this Module (Remember that all variables    */
   /* declared static are initialized to 0 automatically by the         */
   /* compiler as part of standard C/C++).                              */
static Array *CommandTableArray;
static Deque *ScheduleTableDeque;
/*============================================================================*/

extern uint8_t bufsa[1024];
extern coap_option_t opt_part;

/* Private function prototypes -----------------------------------------------*/
char *StringParser(char *String);
int CommandParser(UserCommand_t *TempCommand, char *Input);
int CommandInterpreter(UserCommand_t *TempCommand);
int Reset(ParameterList_t *TempParam);
int MEMRead(ParameterList_t *TempParam);
int MEMWrite(ParameterList_t *TempParam);
int DISTRead(ParameterList_t *TempParam);
int DISTWrite(ParameterList_t *TempParam);
int CLOCKSet(ParameterList_t *TempParam);
int CLOCKGet(ParameterList_t *TempParam);
int CALCFREECYCLESGet(ParameterList_t *TempParam);
int CALCMAXCYCLESGet(ParameterList_t *TempParam);
int CALCPERCENTCYCLESGet(ParameterList_t *TempParam);
CommandFunction_t FindCommand(char *Command);
/*============================================================================*/
    
/* Functions declaration -----------------------------------------------------*/
   /* The following function is responsible for choosing the user       */
   /* interface to memory map.                                          */
void Interface_Memory(void)
{
    if (deque_new(&ScheduleTableDeque) != 0)
        return;
    if (array_new(&CommandTableArray) != 0)
        return;
    ClearCommands();
    ClearSchedule();
    AddCommand("/RESET", "</reset>", Reset);
//    AddCommand("/QUERY/UPDATE", "</reset>", QueryUpdate);
    AddCommand("/GET/MEMORY", "</memory>", MEMRead);
    AddCommand("/PUT/MEMORY", "</memory>", MEMWrite);
    AddCommand("/GET/LOG", "</log>", LOGRead);
    AddCommand("/GET/.WELL-KNOWN/CORE", "</.well-known/core>", WELLKnown);
    AddCommand("/CALLBACK/.WELL-KNOWN/CORE", "</.well-known/core>", 
                                                        CallbackWELLKnown);
    AddCommand("/PUT/CLOCK", "</clock>", CLOCKSet);
    AddCommand("/GET/CLOCK", "</clock>", CLOCKGet);
    AddCommand("/GET/CALCULATE/CYCLES/FREE", "</calculate/cycles/free>", 
                                                        CALCFREECYCLESGet);
    AddCommand("/GET/CALCULATE/CYCLES/MAX", "</calculate/cycles/max>", 
                                                        CALCMAXCYCLESGet);
    AddCommand("/GET/CALCULATE/CYCLES/PERCENT", "</calculate/cycles/percent>", 
                                                        CALCPERCENTCYCLESGet); 
    AddCommand("/GET/QUERYNODES", "</querynodes>;if=\"dev_n\"", QueryNodes);
    if (signal_type == 2) 
    {
        AddCommand("/GET/MOVEMENT", "</movement>;if=\"accel\"", GetLastBlock);
    }
    else
    {
        AddCommand("/GET/EEG", "</eeg>;if=\"neuro\"", GetLastBlock); 
        AddCommand("/GET/EEGCONCRETEBLOCK", "</eegconcreteblock>;if=\"neuro\"", 
                GetConcreteBlock); //передача последнего блока семплов ЭЭГ
    }
    AddCommand("/GET/RUNGENERATOR", "</rungenerator>;if=\"generator\"", 
            RunGenerator); //запуск программы чтения файла на расберри
    AddCommand("/GET/STOPGENERATOR", "</stopgenerator>;if=\"generator\"", 
            StopGenerator); //выключение программы чтения файла на расберри
    #ifdef CPU
        AddCommand("/GET/SNAP", "</snap>;if=\"video\"", Snap);
        AddCommand("/GET/LIGHT", "</light>;if=\"lamp\"", Light);
        AddCommand("/GET/VIDEOTHREAD", "</videothread>;if=\"video\"", VIDEOThread);
        AddCommand("/GET/VERSION", "</version>", Version);
        AddCommand("/GET/UPDATE", "</update>", Update);
        AddCommand("/GET/UPDATEHASH", "</updatehash>", UpdateHash);
        AddCommand("/CALLBACK/UPDATE", "</update>", CallbackUpdate);
        AddCommand("/CALLBACK/UPDATEHASH", "</updatehash>", CallbackUpdateHash);
        AddCommand("/REQUERY/UPDATE", "</update>", QueryUpdate);
        AddCommand("/GET/TECHUPDATE", "</techupdate>", TechUpdate); 
        AddCommand("/REQUERY/UPDATEHASH", "</updatehash>", QueryUpdateHash); 
    #endif

    #ifdef PLATFORM_LINUX
/*
        AddCommand("/GET/VIDEOLINE", VIDEOLNRead);
        printf("\t/GET/VIDEOLINE\r\n\r");
*/
    #endif
   
}
int Reset(ParameterList_t *TempParam)
{
   int  ret_val = 0;

    DBG_LOG_DEBUG("Into Reset.\n");
    AddToTransmit("<RESET>\r\n\r");
    /* First check to see if the parameters required for the execution of*/
    /* this function appear to be semi-valid.                            */
    if ((TempParam))
    {
        #ifdef CPU
            exit(0);
        #else
            HAL_NVIC_SystemReset();
        #endif
    }
    else
    {
        /* One or more of the necessary parameters are invalid.           */
        ret_val = INVALID_PARAMETERS_ERROR;
        AddToTransmit("<INVALID_PARAMETERS_ERROR/>\r\n\r");
        DBG_LOG_WARNING("Invalid parameters.\n");
    }
    AddToTransmit("</RESET>\r\n\r");

    return(ret_val);
}
int CLOCKSet(ParameterList_t *TempParam)
{
    int  ret_val = 0;
    int  Clock = -1;
    int i;
    char buffer[STRING_SIZE];

    DBG_LOG_DEBUG("Into CLOCKSet.\n");
    AddToTransmit("<CLOCKSET>\r\n\r");
    /* First check to see if the parameters required for the execution of*/
    /* this function appear to be semi-valid.                            */
    if ((TempParam) && (TempParam->NumberofParameters > 1))
    {
        for (i=1;i<TempParam->NumberofParameters;i+=2)
        {
            sprintf((char*)buffer,"%s - %d\r\n\r",
                    TempParam->Params[i-1].strParam,
                    (unsigned int)(TempParam->Params[i].intParam));
            AddToTransmit((char*)buffer);
            if (!strcmp(TempParam->Params[i-1].strParam,"clock"))
            {
                 Clock = (unsigned int)(TempParam->Params[i].intParam);
            }
        }
        if (Clock >= 0)
        {
            SetClock(Clock);
            AddToTransmit(" <SET/>\r\n\r");
            DBG_LOG_WARNING("Invalid clock parameter.\n");
        }
    }
    else
    {
        /* One or more of the necessary parameters are invalid.           */
        ret_val = INVALID_PARAMETERS_ERROR;
        AddToTransmit("<INVALID_PARAMETERS_ERROR/>\r\n\r");
        DBG_LOG_WARNING("Invalid parameters.\n");
    }
    AddToTransmit("</CLOCKSET>\r\n\r");

    return(ret_val);
}
int CLOCKGet(ParameterList_t *TempParam)
{
    int  ret_val = 0;
    char buffer[STRING_SIZE];

    DBG_LOG_DEBUG("Into CLOCKGet.\n");
    AddToTransmit("<CLOCK>\r\n\r");
    /* First check to see if the parameters required for the execution of*/
    /* this function appear to be semi-valid.                            */
    if ((TempParam))
    {
        snprintf((char*)buffer,sizeof(buffer)," %d\r\n\r",(int)GetClock());
        AddToTransmit((char*)buffer);
    }
    else
    {
        /* One or more of the necessary parameters are invalid.           */
        ret_val = INVALID_PARAMETERS_ERROR;
        AddToTransmit("<INVALID_PARAMETERS_ERROR/>\r\n\r");
        DBG_LOG_ERROR("Invalid parameters.\n");
    }
    AddToTransmit("</CLOCK>\r\n\r");

    return(ret_val);
}

int CALCFREECYCLESGet(ParameterList_t *TempParam)
{
    int  ret_val = 0;
    char buffer[STRING_SIZE];

    DBG_LOG_DEBUG("Into CALCFREECYCLESGet.\n");
    AddToTransmit("<CALCFREECYCLES>\r\n\r");
    /* First check to see if the parameters required for the execution of*/
    /* this function appear to be semi-valid.                            */
    if ((TempParam))
    {
        snprintf((char*)buffer,sizeof(buffer)," %d\r\n\r",(int)GetCycle());
        AddToTransmit((char*)buffer);
    }
    else
    {
        /* One or more of the necessary parameters are invalid.           */
        ret_val = INVALID_PARAMETERS_ERROR;
        AddToTransmit("<INVALID_PARAMETERS_ERROR/>\r\n\r");
        DBG_LOG_WARNING("Invalid parameters.\n");
    }
    AddToTransmit("</CALCFREECYCLES>\r\n\r");

    return(ret_val);
}
int CALCMAXCYCLESGet(ParameterList_t *TempParam)
{
    int  ret_val = 0;
    char buffer[STRING_SIZE];

    DBG_LOG_DEBUG("Into CALCFREECYCLESGet.\n");
    AddToTransmit("<CALCMAXCYCLES>\r\n\r");
    /* First check to see if the parameters required for the execution of*/
    /* this function appear to be semi-valid.                            */
    if ((TempParam))
    {
        snprintf((char*)buffer,sizeof(buffer)," %d\r\n\r",(int)GetMaxCycle());
        AddToTransmit((char*)buffer);
    }
    else
    {
        /* One or more of the necessary parameters are invalid.           */
        ret_val = INVALID_PARAMETERS_ERROR;
        AddToTransmit("<INVALID_PARAMETERS_ERROR/>\r\n\r");
        DBG_LOG_WARNING("Invalid parameters.\n");
    }
    AddToTransmit("</CALCMAXCYCLES>\r\n\r");

    return(ret_val);
}
int CALCPERCENTCYCLESGet(ParameterList_t *TempParam)
{
    int  ret_val = 0;
    char buffer[STRING_SIZE];

    DBG_LOG_DEBUG("Into CALCFREECYCLESGet.\n");
    AddToTransmit("<CALCPERCENTCYCLES>\r\n\r");
    /* First check to see if the parameters required for the execution of*/
    /* this function appear to be semi-valid.                            */
    if ((TempParam))
    {
        snprintf((char*)buffer,sizeof(buffer)," %d\r\n\r",(int)GetPercent());
        AddToTransmit((char*)buffer);
    }
    else
    {
        /* One or more of the necessary parameters are invalid.           */
        ret_val = INVALID_PARAMETERS_ERROR;
        AddToTransmit("<INVALID_PARAMETERS_ERROR/>\r\n\r");
        DBG_LOG_WARNING("Invalid parameters.\n");
    }
    AddToTransmit("</CALCPERCENTCYCLES>\r\n\r");

    return(ret_val);
}

   /* The following function is responsible for reading data that was   */
   /* stored in memory.  The function reads a fixed number of bytes.    */
   /* This function returns zero if successful                          */
   /* and a negative value if an error occurred.                        */
int MEMRead(ParameterList_t *TempParam)
{
    int  ret_val = 0;
    int  Adress = -1;
    char buffer[STRING_SIZE];
    int i;

    DBG_LOG_DEBUG("Into MEMRead.\n");
    AddToTransmit("<MEMORY>\r\n\r");
    /* First check to see if the parameters required for the execution of*/
    /* this function appear to be semi-valid.                            */
    if ((TempParam) && (TempParam->NumberofParameters > 1))
    {
        for (i=1;i<TempParam->NumberofParameters;i+=2)
        {
            if (!strcmp(TempParam->Params[i-1].strParam,"address"))
            {
                Adress = (unsigned int)(TempParam->Params[i].intParam);
            }
        }
        if (Adress >= 0)
        {
            AddToTransmit(" <ADDRESS>\r\n\r");
            snprintf((char*)buffer,sizeof(buffer),"  %d\r\n\r",(int)Adress);
            AddToTransmit((char*)buffer);
            AddToTransmit(" </ADDRESS>\r\n\r");
            AddToTransmit(" <VALUE>\r\n\r");
            snprintf((char*)buffer,sizeof(buffer),"  %d\r\n\r",(int)ReadMem(Adress));
            AddToTransmit((char*)buffer);
            AddToTransmit(" <VALUE>\r\n\r");
        }
    }
    else
    {
        /* One or more of the necessary parameters are invalid.           */
        ret_val = INVALID_PARAMETERS_ERROR;
        AddToTransmit("<INVALID_PARAMETERS_ERROR/>\r\n\r");
        DBG_LOG_WARNING("Invalid parameters.\n");
    }
    AddToTransmit("</MEMORY>\r\n\r");

    return(ret_val);
}

   /* The following function is responsible for Writing Data to an memory.  */
   /* This function returns zero is successful or a negative                */
   /* return value if there was an error.                                   */
int MEMWrite(ParameterList_t *TempParam)
{
    int  ret_val = 0;
    int  Adress;
    int  Value;
    int  i;
    char buf_local[60];

    DBG_LOG_DEBUG("Into MEMWrite.\n");
    AddToTransmit("<MEMORY>\r\n\r");
    /* First check to see if the parameters required for the execution of*/
    /* this function appear to be semi-valid.                            */
    if ((TempParam) && (TempParam->NumberofParameters > 3))
    {
       for (i=1;i<TempParam->NumberofParameters;i+=2)
       {
          if (!strcmp(TempParam->Params[i-1].strParam,"address"))
          {
             Adress = (unsigned int)(TempParam->Params[i].intParam);
          }
          if (!strcmp(TempParam->Params[i-1].strParam,"value"))
          {
             Value = (unsigned int)(TempParam->Params[i].intParam);
          }
       }
       if (Adress >= 0)
       {
          WriteMem(Adress,Value);
          AddToTransmit("<WR/>\r\n\r");
          #ifdef DEBUG
             DBG_LOG_TRACE("Mem[%d] setted to %d.\r\n\r",Adress,Value);
          #endif
       }
    }
    else
    {
         /* One or more of the necessary parameters are invalid.           */
         ret_val = INVALID_PARAMETERS_ERROR;
         AddToTransmit("<INVALID_PARAMETERS_ERROR/>\r\n\r");
         DBG_LOG_WARNING("Invalid parameters.\n");
    }
    AddToTransmit("</MEMORY>\r\n\r");

    return(ret_val);
}
   /* The following function is responsible for reading data that was   */
   /* stored in memory.  The function reads a fixed number of bytes.    */
   /* This function returns zero if successful                          */
   /* and a negative value if an error occurred.                        */
int DISTRead(ParameterList_t *TempParam)
{
    int  ret_val = 0;
    char buffer[STRING_SIZE];

    DBG_LOG_DEBUG("Into DISTRead.\n");
    AddToTransmit("<DISTANCE>\r\n\r");
    /* First check to see if the parameters required for the execution of*/
    /* this function appear to be semi-valid.                            */
    if ((TempParam))
    {
        sprintf((char*)buffer," %d\r\n\r",(int)ReadMem(REG_Distance));
        AddToTransmit((char*)buffer);
    }
    else
    {
        /* One or more of the necessary parameters are invalid.           */
        ret_val = INVALID_PARAMETERS_ERROR;
        AddToTransmit("<INVALID_PARAMETERS_ERROR/>\r\n\r");
        DBG_LOG_WARNING("Invalid parameters.\n");
    }
    AddToTransmit("</DISTANCE>\r\n\r");

    return(ret_val);
}


   /* The following function is responsible for parsing user input      */
   /* and call appropriate command function.                            */
int CommandLineInterpreter(char *Command)
{
    int     		Result = !EXIT_CODE;
    uint8_t      	ret_val = 0;
    UserCommand_t 	TempCommand;
    char                buf_local[60];

    DBG_LOG_DEBUG("Into CommandLineInterpreter.\n");
    DBG_LOG_DEBUG("> %s\n",Command);
    /* The string input by the user contains a value, now run the string */
    /* through the Command Parser.                                       */
    if(CommandParser(&TempCommand, Command) >= 0)
    {
        /* The Command was successfully parsed run the Command.           */
        Result = CommandInterpreter(&TempCommand);
        switch(Result)
        {
            case INVALID_COMMAND_ERROR:
                DBG_LOG_WARNING("Invalid command.\n");
                ret_val = 0;
                break;
            case FUNCTION_ERROR:
                DBG_LOG_WARNING("Invalid function.\n");
                ret_val = 0;
                break;
            case EXIT_CODE:
                break;
            default:
                ret_val = 1;
                break;
        }
    }
    else
    {
        DBG_LOG_WARNING("INVALID_COMMAND_ERROR.\n");
    }

    DBG_LOG_DEBUG("Into END of CommandLineInterpreter.\n");
    return(ret_val);
}

   /* The following function is responsible for converting number       */
   /* strings to there unsigned integer equivalent.  This function can  */
   /* handle leading and tailing white space, however it does not handle*/
   /* signed or comma delimited values.  This function takes as its     */
   /* input the string which is to be converted.  The function returns  */
   /* zero if an error occurs otherwise it returns the value parsed from*/
   /* the string passed as the input parameter.                         */
unsigned long StringToUnsignedInteger(char *StringInteger)
{
   int           IsHex;
   unsigned int  Index;
   unsigned long ret_val = 0;

   /* Before proceeding make sure that the parameter that was passed as */
   /* an input appears to be at least semi-valid.                       */
   if((StringInteger) && (strlen(StringInteger)))
   {
      /* Initialize the variable.                                       */
      Index = 0;

      /* Next check to see if this is a hexadecimal number.             */
      if(strlen(StringInteger) > 2)
      {
         if((StringInteger[0] == '0') && ((StringInteger[1] == 'x') || (StringInteger[1] == 'X')))
         {
            IsHex = 1;

            /* Increment the String passed the Hexadecimal prefix.      */
            StringInteger += 2;
         }
         else
            IsHex = 0;
      }
      else
         IsHex = 0;

      /* Process the value differently depending on whether or not a    */
      /* Hexadecimal Number has been specified.                         */
      if(!IsHex)
      {
         /* Decimal Number has been specified.                          */
         while(1)
         {
            /* First check to make sure that this is a valid decimal    */
            /* digit.                                                   */
            if((StringInteger[Index] >= '0') && (StringInteger[Index] <= '9'))
            {
               /* This is a valid digit, add it to the value being      */
               /* built.                                                */
               ret_val += (StringInteger[Index] & 0xF);

               /* Determine if the next digit is valid.                 */
               if(((Index + 1) < strlen(StringInteger)) && (StringInteger[Index+1] >= '0') && (StringInteger[Index+1] <= '9'))
               {
                  /* The next digit is valid so multiply the current    */
                  /* return value by 10.                                */
                  ret_val *= 10;
               }
               else
               {
                  /* The next value is invalid so break out of the loop.*/
                  break;
               }
            }

            Index++;
         }
      }
      else
      {
         /* Hexadecimal Number has been specified.                      */
         while(1)
         {
            /* First check to make sure that this is a valid Hexadecimal*/
            /* digit.                                                   */
            if(((StringInteger[Index] >= '0') 
                    && (StringInteger[Index] <= '9')) 
                    || ((StringInteger[Index] >= 'a') 
                    && (StringInteger[Index] <= 'f')) 
                    || ((StringInteger[Index] >= 'A') 
                    && (StringInteger[Index] <= 'F')))
            {
               /* This is a valid digit, add it to the value being      */
               /* built.                                                */
               if((StringInteger[Index] >= '0') && (StringInteger[Index] <= '9'))
                  ret_val += (StringInteger[Index] & 0xF);
               else
               {
                  if((StringInteger[Index] >= 'a') 
                          && (StringInteger[Index] <= 'f'))
                     ret_val += (StringInteger[Index] - 'a' + 10);
                  else
                     ret_val += (StringInteger[Index] - 'A' + 10);
               }

               /* Determine if the next digit is valid.                 */
               if(((Index + 1) < strlen(StringInteger)) 
                       && (((StringInteger[Index+1] >= '0') 
                       && (StringInteger[Index+1] <= '9')) 
                       || ((StringInteger[Index+1] >= 'a') 
                       && (StringInteger[Index+1] <= 'f')) 
                       || ((StringInteger[Index+1] >= 'A') 
                       && (StringInteger[Index+1] <= 'F'))))
               {
                  /* The next digit is valid so multiply the current    */
                  /* return value by 16.                                */
                  ret_val *= 16;
               }
               else
               {
                  /* The next value is invalid so break out of the loop.*/
                  break;
               }
            }

            Index++;
         }
      }
   }

   return(ret_val);
}

   /* The following function is responsible for parsing strings into    */
   /* components.  The first parameter of this function is a pointer to */
   /* the String to be parsed.  This function will return the start of  */
   /* the string upon success and a NULL pointer on all errors.         */
char *StringParser(char *String)
{
   int   Index;
   char *ret_val = NULL;

   /* Before proceeding make sure that the string passed in appears to  */
   /* be at least semi-valid.                                           */
   if((String) && (strlen(String)))
   {
        /* The string appears to be at least semi-valid.  Search for the  */
        /* first space character and replace it with a NULL terminating   */
        /* character.                                                     */
        for(Index=0, ret_val=String;Index < strlen(String);Index++)
        {
            /* Is this the space character.                                */
            if((String[Index] == ' ') || (String[Index] == '\r') 
                                   || (String[Index] == '?') 
                                   || (String[Index] == '&') 
                                   || (String[Index] == '=') 
                                   || (String[Index] == ':') 
                                   || (String[Index] == '\"') 
                                   || (String[Index] == '\n') )
            {
                /* This is the space character, replace it with a NULL      */
                /* terminating character and set the return value to the    */
                /* begining character of the string.                        */
                String[Index] = '\0';
                break;
            }
        }
   }

   return(ret_val);
}

char* GetCommandLink(int N)
{   
    CommandTable_t *Comm;
    array_get_at(CommandTableArray, N, (void**)&Comm);
    return Comm->Link;
}
int GetCommandsNumber(void)
{
    return array_size(CommandTableArray);
}
   /* This function is responsable for taking command strings and       */
   /* parsing them into a command, param1, and param2.  After parsing   */
   /* this string the data is stored into a UserCommand_t structure to  */
   /* be used by the interpreter.  The first parameter of this function */
   /* is the structure used to pass the parsed command string out of the*/
   /* function.  The second parameter of this function is the string    */
   /* that is parsed into the UserCommand structure.  Successful        */
   /* execution of this function is denoted by a retrun value of zero.  */
   /* Negative return values denote an error in the parsing of the      */
   /* string parameter.                                                 */
int CommandParser(UserCommand_t *TempCommand, char *Input)
{
   int            ret_val;
   int            StringLength;
   char          *LastParameter;
   unsigned int   Count         = 0;

   /* Before proceeding make sure that the passed parameters appear to  */
   /* be at least semi-valid.                                           */ 
   if((TempCommand) && (Input) && (strlen(Input)))
   {                       
      /* First get the initial string length.                           */
      StringLength = strlen(Input);
           
      /* Retrieve the first token in the string, this should be the     */
      /* commmand.                                                      */
      TempCommand->Command = StringParser(Input);
           
      /* Flag that there are NO Parameters for this Command Parse.      */
      TempCommand->Parameters.NumberofParameters = 0;
           
       /* Check to see if there is a Command                            */
      if(TempCommand->Command)
      {
         /* Initialize the return value to zero to indicate success on  */
         /* commands with no parameters.                                */
         ret_val    = 0;

         /* Adjust the UserInput pointer and StringLength to remove the */
         /* Command from the data passed in before parsing the          */
         /* parameters.                                                 */
         Input        += strlen(TempCommand->Command)+1;
         StringLength  = strlen(Input);

         /* There was an available command, now parse out the parameters*/
         while((StringLength > 0) && ((LastParameter = StringParser(Input)) != NULL))
         {
            /* There is an available parameter, now check to see if     */
            /* there is room in the UserCommand to store the parameter  */
            if(Count < (sizeof(TempCommand->Parameters.Params)/sizeof(Parameter_t)))
            {
               /* Save the parameter as a string.                       */
               TempCommand->Parameters.Params[Count].strParam = LastParameter;

               /* Save the parameter as an unsigned int intParam will   */
               /* have a value of zero if an error has occurred.        */
               TempCommand->Parameters.Params[Count].intParam = StringToUnsignedInteger(LastParameter);

               Count++;
               Input        += strlen(LastParameter)+1;
               StringLength -= strlen(LastParameter)+1;

               ret_val = 0;
            }
            else
            {
               /* Be sure we exit out of the Loop.                      */
               StringLength = 0;

               ret_val      = TO_MANY_PARAMS;
            }
         }

         /* Set the number of parameters in the User Command to the     */
         /* number of found parameters                                  */
         TempCommand->Parameters.NumberofParameters = Count;
      }
      else
      {
         /* No command was specified                                    */
         ret_val = NO_COMMAND_ERROR;
      }
   }
   else
   {
      /* One or more of the passed parameters appear to be invalid.     */
      ret_val = INVALID_PARAMETERS_ERROR;
   }

   return(ret_val);
}

   /* This function is responsible for determining the command in which */
   /* the user entered and running the appropriate function associated  */
   /* with that command.  The first parameter of this function is a     */
   /* structure containing information about the command to be issued.  */
   /* This information includes the command name and multiple parameters*/
   /* which maybe be passed to the function to be executed.  Successful */
   /* execution of this function is denoted by a return value of zero.  */
   /* A negative return value implies that that command was not found   */
   /* and is invalid.                                                   */
int CommandInterpreter(UserCommand_t *TempCommand)
{
   int               i;
   int               ret_val;
   CommandFunction_t CommandFunction;

   /* If the command is not found in the table return with an invaild   */
   /* command error                                                     */
   ret_val = INVALID_COMMAND_ERROR;

   /* Let's make sure that the data passed to us appears semi-valid.    */
   if((TempCommand) && (TempCommand->Command))
   {
        /* Now, let's make the Command string all upper case so that we   */
        /* compare against it.                                            */
        for(i=0;i<strlen(TempCommand->Command);i++)
        {
           if((TempCommand->Command[i] >= 'a') && (TempCommand->Command[i] <= 'z'))
              TempCommand->Command[i] -= ('a' - 'A');
        }

        /* The command entered is not exit so search for command in    */
        /* table.                                                      */
        if((CommandFunction = FindCommand(TempCommand->Command)) != NULL)
        {
           /* The command was found in the table so call the command.  */
           if((ret_val = ((*CommandFunction)(&TempCommand->Parameters))) == 0)
           {
              /* Return success to the caller.                         */
              ret_val = 0;
           }
           else
           {
              if((ret_val != EXIT_CODE) && (ret_val != EXIT_MODE))
                 ret_val = FUNCTION_ERROR;
           }
        }
        else
        {
            DBG_LOG_WARNING("Command not found.\n");
        }
   }
   else
      ret_val = INVALID_PARAMETERS_ERROR;

   return(ret_val);
}

   /* The following function is provided to allow a means to            */
   /* programatically add Commands the Global (to this module) Command  */
   /* Table.  The Command Table is simply a mapping of Command Name     */
   /* (NULL terminated ASCII string) to a command function.  This       */
   /* function returns zero if successful, or a non-zero value if the   */
   /* command could not be added to the list.                           */
int AddCommand(char *CommandName, char *Link, CommandFunction_t CommandFunction)
{
    int ret_val = 0;
    CommandTable_t *comm;

    /* First, make sure that the parameters passed to us appear to be    */
    /* semi-valid.                                                       */
    if((CommandName) && (CommandFunction))
    {
        /* Next, make sure that we still have room in the Command Table   */
        /* to add commands.                                               */
        if(array_size(CommandTableArray) < MAX_SUPPORTED_COMMANDS)
        {
            /* Simply add the command data to the command table and        */
            /* increment the number of supported commands.                 */
            comm = (CommandTable_t *)umm_calloc(1,sizeof(CommandTable_t));
            comm->CommandName = CommandName;
            comm->Link = Link;
            comm->CommandFunction = CommandFunction;
            if (array_add(CommandTableArray, (void *)comm) != 0)
            {
                umm_free((void *)comm);
                return 1;
            }
            DBG_LOG_INFO("Command added. \n");
            DBG_LOG_INFO(comm->CommandName);

            /* Return success to the caller.                               */
            ret_val                                        = 0;
        }
        else
            ret_val = 1;
    }
    else
        ret_val = 1;

    return(ret_val);
}

   /* The following function searches the Command Table for the         */
   /* specified Command.  If the Command is found, this function returns*/
   /* a NON-NULL Command Function Pointer.  If the command is not found */
   /* this function returns NULL.                                       */
CommandFunction_t FindCommand(char *Command)
{
    unsigned int      Index;
    CommandFunction_t ret_val;
    CommandTable_t    *Comm;

    /* First, make sure that the command specified is semi-valid.        */
    if(Command)
    {
        /* Now loop through each element in the table to see if there is  */
        /* a match.                                                       */
        
//        printf("find\n");
        for(Index=0,ret_val=NULL;
                ((Index<array_size(CommandTableArray)) && (!ret_val));
                  Index++)
        {
            array_get_at(CommandTableArray, Index, (void**)&Comm);
//            printf("%d of %d\n",Index,array_size(CommandTableArray));
            if((strlen(Comm->CommandName) == strlen(Command)) 
                   && (memcmp(Command, Comm->CommandName, 
                              strlen(Comm->CommandName)) == 0))
                ret_val = Comm->CommandFunction;
        }
    }
    else
        ret_val = NULL;

    return(ret_val);
}

   /* The following function is provided to allow a means to clear out  */
   /* all available commands from the command table.                    */
void ClearCommands(void)
{
    /* Simply flag that there are no commands present in the table.      */
    array_remove_all_free(CommandTableArray);
    return;
}
void AddToSchedule(ScheduleFunction_t ScheduleFunction)
{
    ScheduleFunction_t *comm;
    comm = (ScheduleFunction_t *)umm_calloc(1,sizeof(ScheduleFunction_t));
    *comm = ScheduleFunction;
    if (deque_add_last(ScheduleTableDeque, (void *)comm) != 0)
    {
        umm_free((void *)comm);
        return 1;
    }
    DBG_LOG_INFO("Schedule updated now %d. \n",deque_size(ScheduleTableDeque));
    return;
}
void ClearSchedule(void)
{
    deque_remove_all_free(ScheduleTableDeque);
    return;
}
void ExecuteSchedule(void)
{
    ScheduleFunction_t  *Comm;

    while(deque_size(ScheduleTableDeque) > 0)
    {
        deque_remove_first(ScheduleTableDeque, (void**)&Comm);
        DBG_LOG_INFO("Schedule executing, %d left. \n",
                            deque_size(ScheduleTableDeque));
        (*(*Comm))();
        umm_free((void *)Comm);
    }
    return;
}
/*============================================================================*/

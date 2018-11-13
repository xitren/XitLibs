// ----------------------------------------------------------------------------
//
// CommandModule.c - Implements a command module with link API and shedule
//                   deque
//
// ----------------------------------------------------------------------------
//
// A.Gusev 04.09.2017 - Original
//
// ----------------------------------------------------------------------------

/* Local headers -------------------------------------------------------------*/
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "LibConfig.h"
#include "CommandModule.h"
#include "LogModule.h"
#include "array.h"
#include "umm_malloc.h"
#include "CRC16ANSI.h"
/*============================================================================*/                           

/* Private structures --------------------------------------------------------*/
   /* The following type definition represents the structure which holds*/
   /* information used in the interpretation and execution of Commands. */
   /* G - COAP_METHOD_GET                                               */
   /* U - COAP_METHOD_PUT                                               */
   /* P - COAP_METHOD_POST                                              */
   /* D - COAP_METHOD_DELETE                                            */
   /* R - COAP_METHOD_RESET                                             */
typedef struct _tagCommandTable_t
{
   uint16_t             UniCode;
   uint8_t              Methods; // |x|x|x|G|U|P|D|R|
   char                 *CommandName;
   char                 *Link;
   CommandFunction_t    CommandFunction;
} CommandTable_t;
/*============================================================================*/

/* Private variables ---------------------------------------------------------*/
static Array *CommandTableArray;
/*============================================================================*/
    
/* Functions declaration -----------------------------------------------------*/
void InitCommands(void)
{
    if (array_new(&CommandTableArray) != 0)
        return;
}

char* GetCommandLink(int N)
{   
    DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
                      __LINE__, __FILE__, __func__);
    CommandTable_t *Comm;
    array_get_at(CommandTableArray, N, (void**)&Comm);
    if ((Comm == NULL))
    {
        DBG_LOG_ERROR("Comm argument is NULL\n");
        return NULL;
    }
    return Comm->Link;
}

int GetCommandsNumber(void)
{
    DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
                      __LINE__, __FILE__, __func__);
    return array_size(CommandTableArray);
}

int AddCommand(uint8_t _Methods, const char *CommandName, 
                    const char *Link, CommandFunction_t CommandFunction)
{
    int ret_val = 0;
    CommandTable_t *comm;

    DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
                      __LINE__, __FILE__, __func__);
    /* First, make sure that the parameters passed to us appear to be    */
    /* semi-valid.                                                       */
    if((CommandName) && (Link) && (CommandFunction))
    {
        /* Next, make sure that we still have room in the Command Table   */
        /* to add commands.                                               */
        if(array_size(CommandTableArray) < MAX_SUPPORTED_COMMANDS)
        {
            /* Simply add the command data to the command table and        */
            /* increment the number of supported commands.                 */
            comm = (CommandTable_t *)umm_calloc(1,sizeof(CommandTable_t));
            if (comm == NULL){return 1;}
            comm->UniCode = CRC16ANSI(CommandName,strlen(CommandName));
            comm->Methods = _Methods;
            comm->CommandName = CommandName;
            comm->Link = Link;
            comm->CommandFunction = CommandFunction;
            if (array_add(CommandTableArray, (void *)comm) != 0)
            {
                umm_free((void *)comm);
                return 1;
            }
            DBG_LOG_INFO("%s\n",CommandName);
            DBG_LOG_INFO("Command added. \n");
            DBG_LOG_INFO((const char*)comm->CommandName);

            /* Return success to the caller.                               */
            ret_val = 0;
        }
        else
            ret_val = 1;
    }
    else
        ret_val = 1;

    return(ret_val);
}

CommandFunction_t FindCommand(const char *Command)
{
    uint16_t          crc;
    unsigned int      Index;
    CommandFunction_t ret_val;
    CommandTable_t    *Comm;

    DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
                      __LINE__, __FILE__, __func__);
    /* First, make sure that the command specified is semi-valid.        */
    if(Command)
    {
        crc = CRC16ANSI(Command,strlen(Command));
        /* Now loop through each element in the table to see if there is  */
        /* a match.                                                       */
        for(Index=0,ret_val=NULL;
                ((Index<array_size(CommandTableArray))/* && (!ret_val)*/);
                  Index++)
        {
            array_get_at(CommandTableArray, Index, (void**)&Comm);
            if (crc == Comm->UniCode)
                if((strlen(Comm->CommandName) == strlen(Command)) 
                       && (memcmp(Command, Comm->CommandName, 
                                  strlen(Comm->CommandName)) == 0))
                {
                    ret_val = Comm->CommandFunction;
                    break;
                }
        }
    }
    else
        ret_val = NULL;

    return(ret_val);
}

void ClearCommands(void)
{
    DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
                      __LINE__, __FILE__, __func__);
    /* Simply flag that there are no commands present in the table.      */
    if ((CommandTableArray == NULL))
    {
        return;
    }
    array_remove_all_free(CommandTableArray);
    return;
}

int add_parameter(ParameterList_t *params, char *strParam, uint32_t intParam)
{
    DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
                      __LINE__, __FILE__, __func__);
    if (params->NumberofParameters >= MAX_NUM_OF_PARAMETERS)
        return TO_MANY_PARAMS;
    params->Params[params->NumberofParameters].strParam = strParam;
    params->Params[params->NumberofParameters++].intParam = intParam;
    return 0;
}
int get_parameter(ParameterList_t *params, char *strParam, uint32_t *intParam)
{
    DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
                      __LINE__, __FILE__, __func__);
    int i;
    for (i=0;i < params->NumberofParameters;i++)
    {
        if (!strcmp(strParam,params->Params[i].strParam))
        {
            return ((*intParam) = params->Params[i].intParam); 
        }
    }
    return INVALID_PARAMETERS_ERROR;
}
#define SIZE_OF_PARAMETER sizeof(Parameter_t)
int delete_parameter(ParameterList_t *params, char *strParam)
{
    DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
                      __LINE__, __FILE__, __func__);
    int i;
    for (i=0;i < params->NumberofParameters;i++)
    {
        if (!strcmp(strParam,params->Params[i].strParam))
        {
            memcpy(
                    params->Params+i*SIZE_OF_PARAMETER,
                    params->Params+(i+1)*SIZE_OF_PARAMETER,
                    (params->NumberofParameters-(i+1))*SIZE_OF_PARAMETER
            );
            params->NumberofParameters--; 
            return 0; 
        }
    }
    return INVALID_PARAMETERS_ERROR;
}
/*============================================================================*/

// ----------------------------------------------------------------------------
//
// CommandModule.h - Implements a command module with link API and shedule
//                   deque
//
// ----------------------------------------------------------------------------

/* Global headers ------------------------------------------------------------*/
#include <stdio.h>
#include "xitlibtypes.h"             /* Application Header.            */
/*============================================================================*/

#ifndef __CMDMODULE_H__
#define __CMDMODULE_H__   

#ifdef __cplusplus
extern "C" {
#endif

/* Public structures ---------------------------------------------------------*/
typedef struct _tagUserCommand_t
{
   char            *Command;
   ParameterList_t  Parameters;
} UserCommand_t;
typedef int (*CommandFunction_t)(
            uint8_t Method, uint8_t MediaType, ParameterList_t *TempParam, 
            uint8_t *data, uint32_t *data_size
);    
typedef enum
{
  Method_GET           =       0x00000010,
  Method_PUT           =       0x00000008,
  Method_POST          =       0x00000004,
  Method_DELETE        =       0x00000002,
  Method_RESET         =       0x00000001
} MethodPermissionDef;
typedef enum
{
  Media_XML            =       0x00000000,
  Media_TEXT           =       0x00000001,
  Media_BYTE           =       0x00000002
} MediaTypeDef;
/*============================================================================*/

/* Public variables ----------------------------------------------------------*/
/*============================================================================*/

/* Public function prototypes ------------------------------------------------*/
void InitCommands(void);
int AddCommand(uint8_t _Methods, char *CommandName, 
                    char *Link, CommandFunction_t CommandFunction);
void ClearCommands(void);
char* GetCommandLink(int N);
int GetCommandsNumber(void);
int add_parameter(ParameterList_t *params, char *strParam, uint32_t intParam);
int get_parameter(ParameterList_t *params, char *strParam, uint32_t *intParam);
int delete_parameter(ParameterList_t *params, char *strParam);
/*============================================================================*/

#ifdef __cplusplus
}
#endif

#endif

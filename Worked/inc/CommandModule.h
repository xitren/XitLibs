
/* Global headers ------------------------------------------------------------*/
#include <stdio.h>
#include "xitlibtypes.h"             /* Application Header.            */
/*============================================================================*/

#ifndef __CMDMODULE_H__
#define __CMDMODULE_H__   

/* Public defines ------------------------------------------------------------*/
#define NO_COMMAND_ERROR                           (-1)  /* Denotes that no   */
                                                         /* command was       */
                                                         /* specified to the  */
                                                         /* parser.           */
#define INVALID_COMMAND_ERROR                      (-2)  /* Denotes that the  */
                                                         /* Command does not  */
                                                         /* exist for         */
                                                         /* processing.       */                                
#define EXIT_CODE                                  (-3)  /* Denotes that the  */
                                                         /* Command specified */
                                                         /* was the Exit      */
                                                         /* Command.          */
#define FUNCTION_ERROR                             (-4)  /* Denotes that an   */
                                                         /* error occurred in */
                                                         /* execution of the  */
                                                         /* Command Function. */
#define TO_MANY_PARAMS                             (-5)  /* Denotes that there*/
                                                         /* are more          */
                                                         /* parameters then   */
                                                         /* will fit in the   */
                                                         /* UserCommand.      */
#define INVALID_PARAMETERS_ERROR                   (-6)  /* Denotes that an   */
                                                         /* error occurred due*/
                                                         /* to the fact that  */
                                                         /* one or more of the*/
                                                         /* required          */
                                                         /* parameters were   */
                                                         /* invalid.          */
#define UNABLE_TO_INITIALIZE_STACK                 (-7)  /* Denotes that an   */
                                                         /* error occurred    */
                                                         /* while Initializing*/
                                                         /* the Bluetooth     */
                                                         /* Protocol Stack.   */
#define INVALID_STACK_ID_ERROR                     (-8)  /* Denotes that an   */
                                                         /* occurred due to   */
                                                         /* attempted         */
                                                         /* execution of a    */
                                                         /* Command when a    */
                                                         /* Bluetooth Protocol*/
                                                         /* Stack has not been*/
                                                         /* opened.           */
#define UNABLE_TO_REGISTER_SERVER                  (-9)  /* Denotes that an   */
                                                         /* error occurred    */
                                                         /* when trying to    */
                                                         /* create a Serial   */
                                                         /* Port Server.      */
#define EXIT_MODE                                  (-10) /* Flags exit from   */
                                                         /* any Mode.         */
#define MAX_SUPPORTED_COMMANDS                     (36)  /* Denotes the       */
                                                         /* maximum number of */
                                                         /* User Commands that*/
                                                         /* are supported by  */
                                                         /* this application. */
#define MEMORY_COMMAND sizeof(CommandFunction_t)+4
/*============================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/* Public structures ---------------------------------------------------------*/
   /* The following type definition represents the structure which holds*/
   /* the command and parameters to be executed.                        */
typedef struct _tagUserCommand_t
{
   char            *Command;
   ParameterList_t  Parameters;
} UserCommand_t;
   /* The following type definition represents the generic function     */
   /* pointer to be used by all commands that can be executed by the    */
   /* test program.                                                     */
typedef int (*CommandFunction_t)(ParameterList_t *TempParam);         
typedef int (*ScheduleFunction_t)(void);
/*============================================================================*/

/* Public variables ----------------------------------------------------------*/
extern int size_parts;
extern int size_parts_cur;
/*============================================================================*/

/* Public function prototypes ------------------------------------------------*/
void Interface_Memory(void);
int CommandLineInterpreter(char *Command);
int AddCommand(char *CommandName, char *Link, CommandFunction_t CommandFunction);
char* GetCommandLink(int N);
int GetCommandsNumber(void);
void ClearCommands(void);
unsigned long StringToUnsignedInteger(char *StringInteger);
void AddToSchedule(ScheduleFunction_t ScheduleFunction);
void ClearSchedule(void);
void ExecuteSchedule(void);
/*============================================================================*/

#ifdef __cplusplus
}
#endif

#endif


/* Global headers ------------------------------------------------------------*/
#include <stdio.h>
#include "LibConfig.h"
#include <stdint.h>
/*============================================================================*/

#ifndef __FUNCPARAMS_H__
#define __FUNCPARAMS_H__

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
/*============================================================================*/

/* Public types --------------------------------------------------------------*/
typedef unsigned char     uint8_t;
#ifdef PLATFORM_LINUX
    typedef unsigned int  uint32_t;
#else
    //typedef unsigned long  uint32_t;
#endif
/*============================================================================*/

/* Public types --------------------------------------------------------------*/

typedef union {
    unsigned char ui8[2];
    uint16_t ui16;
} conv_uint16_bytes_t;

typedef union {
    unsigned char ui8[4];
    uint32_t ui32;
    int32_t i32;
} conv_uint32_bytes_t;

typedef struct _tagParameter_t
{
   char     *strParam;
   uint32_t  intParam;
} Parameter_t;

typedef struct _tagParameterList_t
{
   int         NumberofParameters;
   Parameter_t Params[MAX_NUM_OF_PARAMETERS];
} ParameterList_t;

typedef enum
{
  BASESTATION            =       0x00000000,
  EEG                    =       0x00000001,
  MOVEMENT               =       0x00000002,
  CAMERA                 =       0x00000003,
  GENERATOR              =       0x00000004,
  POLYGRAPH              =       0x00000005,
  ROBOT                  =       0x00000006              
} DeviceTypeDef;
/*============================================================================*/

/* Public defines ------------------------------------------------------------*/
/*============================================================================*/
#endif

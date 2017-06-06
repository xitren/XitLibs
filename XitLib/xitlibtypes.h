
/* Global headers ------------------------------------------------------------*/
#include <stdio.h>
#include "LibConfig.h"
#include <stdint.h>
/*============================================================================*/

#ifndef __FUNCPARAMS_H__
#define __FUNCPARAMS_H__

/* Public types --------------------------------------------------------------*/
typedef unsigned char     uint8_t;
typedef unsigned short  uint16_t;
#ifdef PLATFORM_LINUX
    typedef unsigned int  uint32_t;
#else
    //typedef unsigned long  uint32_t;
#endif
/*============================================================================*/

/* Public defines ------------------------------------------------------------*/
/*============================================================================*/

/* Public types --------------------------------------------------------------*/
   /* The following type definition represents the structure which holds*/
   /* all information about the parameter, in particular the parameter  */
   /* as a string and the parameter as an unsigned int.                 */
typedef struct _tagParameter_t
{
   char     *strParam;
   uint32_t  intParam;
} Parameter_t;
   /* The following type definition represents the structure which holds*/
   /* a list of parameters that are to be associated with a command The */
   /* NumberofParameters variable holds the value of the number of      */
   /* parameters in the list.                                           */
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
  GENERATOR              =       0x00000004          
} DeviceTypeDef;
/*============================================================================*/

#endif

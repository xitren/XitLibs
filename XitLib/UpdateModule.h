
#ifndef UPDATEMODULE_H
#define UPDATEMODULE_H

#ifdef __cplusplus
extern "C" {
#endif
    
/* Global headers ------------------------------------------------------------*/
#include "xitlibtypes.h"             /* Application Header.            */
/*============================================================================*/
    
/* Public defines ------------------------------------------------------------*/
#define HASHES_MAX 10
/*============================================================================*/
    
/* Public types --------------------------------------------------------------*/
typedef enum
{
  BASESTATION            =       0x00000000,
  EEG                    =       0x00000001,
  MOVEMENT               =       0x00000002,
  CAMERA                 =       0x00000003,
  GENERATOR              =       0x00000004          
} DeviceTypeDef;

DeviceTypeDef DEVICE;
/*============================================================================*/
    
/* Public function prototypes ------------------------------------------------*/
void InitCfgDevType(void);
void function_update(int type);
int Update(ParameterList_t *TempParam);
int UpdateHash(ParameterList_t *TempParam);
int CallbackUpdate(ParameterList_t *TempParam);
int CallbackUpdateHash(ParameterList_t *TempParam);
int QueryUpdate(ParameterList_t *TempParam);
int QueryUpdateHash(ParameterList_t *TempParam);
int Version(ParameterList_t *TempParam);
int TechUpdate(ParameterList_t *TempParam);
int TechStart(ParameterList_t *TempParam);
/*============================================================================*/

#ifdef __cplusplus
}
#endif

#endif /* UPDATEMODULE_H */


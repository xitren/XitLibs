
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
int SetVersion(char *value);
int SetUpdateServer(char *value);
/*============================================================================*/

#ifdef __cplusplus
}
#endif

#endif /* UPDATEMODULE_H */


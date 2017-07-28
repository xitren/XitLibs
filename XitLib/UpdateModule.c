
/* Local headers -------------------------------------------------------------*/
#include "UpdateModule.h"
#include "coap.h"
#include "Handler.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "version.h"
#include "LogModule.h"
/*============================================================================*/

/* Private variables ---------------------------------------------------------*/
uint16_t hashes[HASHES_MAX];
uint32_t hashes_cnt = 0;
/*============================================================================*/

/* Private constants ---------------------------------------------------------*/
char tok_update[7];
const char *tok_update_hash="updhsh";
const char *path_update_reqry="/REQUERY/UPDATE";
char path_update_clb[50]="/CALLBACK/UPDATE?type=0";
char path_update_hash_clb[50]="/CALLBACK/UPDATEHASH?type=0";
//const char *updateserver = "10.9.91.105";
char *updateserver = "10.10.30.40";
//const char *updateserver = "10.10.30.35";
bool techServerFound = true;
const char *updatefile = "Updater.sh";
char *version = "1.3";
/*============================================================================*/
uint32_t config_dev_type[CFG_SIZE];
char updatefilepath[200]="Updater.sh";
/*============================================================================*/


/* Functions declaration -----------------------------------------------------*/
inline void InitCfgDevType(void) {
    config_dev_type[BASESTATION] = 0;
    config_dev_type[EEG] = 1;
    config_dev_type[MOVEMENT] = 2;
    config_dev_type[CAMERA] = 3;
    config_dev_type[GENERATOR] = 4;
}

#ifdef CPU
int QueryUpdate(ParameterList_t *TempParam)
{
    int ret_val = 0;
    return(ret_val);
}
int QueryUpdateHash(ParameterList_t *TempParam)
{
    int ret_val = 0;
    return(ret_val);
}


int Version(ParameterList_t *TempParam)
{
   int ret_val = 0;
   return(ret_val);
}

int SetVersion(char *value)
{
   int ret_val = 0;
   return(ret_val);
}

int SetUpdateServer(char *value)
{
   int ret_val = 0;
   return(ret_val);
}

   /* The following function is responsible for Giving current          */
   /* functions. This function returns zero is successful or a negative */
   /* return value if there was an error.                               */
int CallbackUpdate(ParameterList_t *TempParam)
{
    int  ret_val = 0;
    return(ret_val);
}
   /* The following function is responsible for Giving current          */
   /* functions. This function returns zero is successful or a negative */
   /* return value if there was an error.                               */
int CallbackUpdateHash(ParameterList_t *TempParam)
{
    int ret_val = 0;
    return(ret_val);
}

int TechUpdate(ParameterList_t *TempParam)
{
    int  ret_val = 0;
    return(ret_val);
}

void sendQueryNode(int type)
{
    return;
}

void function_update(int type)
{
    return;
}

int UpdateHash(ParameterList_t *TempParam)
{
    int  ret_val = 0;
    return(ret_val);
}

int Update(ParameterList_t *TempParam)
{
    int  ret_val = 0;
    return(ret_val);
}
#endif
/*============================================================================*/

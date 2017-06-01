
#ifndef FUNCTIONSDISCOVERY_H
#define FUNCTIONSDISCOVERY_H

#ifdef __cplusplus
extern "C" {
#endif
    
/* Global headers ------------------------------------------------------------*/
#include "xitlibtypes.h"             /* Application Header.            */
#include "LibConfig.h"
/*============================================================================*/
    
/* Public defines ------------------------------------------------------------*/
#define MEMORY_DMA sizeof(DMAoccure_t)*DMA_MAX+8
/*============================================================================*/

/* Public types --------------------------------------------------------------*/
typedef struct
{
    char name[25];
    uint32_t len;
} function_proto;
typedef struct
{
    char ip[15];
    function_proto proto[PROTO_MAX];
    uint32_t len;
} function_node;
/*============================================================================*/

/* Public defines ------------------------------------------------------------*/
#define MEMORY_CORE_WELLKNOWN sizeof(function_node)*NODE_MAX+4
/*============================================================================*/

/* Public function prototypes ------------------------------------------------*/
void put_node_msg(char *_ip,char *_name);
char* get_first_node_by_func(const char *_name);
void function_beakon(void);
void print_node_and_func(void);
int WELLKnown(ParameterList_t *TempParam);
int CallbackWELLKnown(ParameterList_t *TempParam);
int QueryNodes(ParameterList_t *TempParam);
int EEGWriteInFile(ParameterList_t *TempParam);
int EEGGetListFiles(ParameterList_t *TempParam);
int EEGGetFile(ParameterList_t *TempParam);
/*============================================================================*/

#ifdef __cplusplus
}
#endif

#endif /* FUNCTIONSDISCOVERY_H */


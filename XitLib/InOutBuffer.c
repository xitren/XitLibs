
/* Local headers -------------------------------------------------------------*/
#include "LibConfig.h"
#include "InOutBuffer.h"
#include <stdio.h>
#include <string.h>
#include "LogModule.h"
#include "deque.h"
#include "umm_malloc.h"
/*============================================================================*/

/* Private structures --------------------------------------------------------*/
typedef struct _tagReceiveDeque_t
{
   uint8_t              *Msg;
   uint32_t             Size;
   uint32_t             Ip;
   uint32_t             Port;
} ReceiveDeque_t;
/*============================================================================*/

/* Private variables ---------------------------------------------------------*/
#define BUFFER_INOUT BUFFER_SIZE*STRING_SIZE
char inout_buffer[BUFFER_INOUT];
uint32_t TxCnt = 0;
static Deque *ReceiveDeque;
/*============================================================================*/

/* Functions declaration -----------------------------------------------------*/
int InitBuffer()
{
    int ret_val = NO_BUFFER_ERROR;
    DBG_LOG_TRACE("Into InitBuffer.\n");
    TxCnt = 0;
    if (deque_new(&ReceiveDeque) != 0)
        return BUFFER_ERROR;
    return(ret_val);
}
int AddToReceive(uint8_t *msg, uint32_t size, uint32_t ip, uint32_t port)
{
   int ret_val = NO_BUFFER_ERROR;
   ReceiveDeque_t *comm;
   
    DBG_LOG_TRACE("Into AddToReceive.\n");
    if ((msg == NULL))
    {
        DBG_LOG_ERROR("msg argument is NULL\n");
        return 0;
    }
    if ((msg != 0) && (size > 0))
    {
        comm = (ReceiveDeque_t *)umm_calloc(1,sizeof(ReceiveDeque_t));
        comm->Msg = (uint8_t *)umm_calloc(size,sizeof(uint8_t));
        memcpy((void *)comm->Msg,(void *)msg,size);
        comm->Size = size;
        comm->Ip = ip;
        comm->Port = port;
        if (deque_add_last(ReceiveDeque, (void *)comm) != 0)
        {
            umm_free((void *)comm);
            return BUFFER_ERROR;
        }
        DBG_LOG_INFO("Message added. \n");
    }
    else
        return BUFFER_ERROR;
   
   return(ret_val);
}
int ProceedReceive(uint8_t *msg,uint32_t *size, uint32_t *ip, uint32_t *port)
{
    int ret_val = NO_BUFFER_ERROR;
    ReceiveDeque_t *comm;
   
    if ((msg == NULL) || (size == NULL) || (ip == NULL) || (port == NULL))
    {
        DBG_LOG_ERROR("ProceedReceive argument is NULL\n");
        return 0;
    }
    if ((ReceiveDeque == NULL))
    {
        DBG_LOG_ERROR("ReceiveDeque is NULL\n");
        return 0;
    }
    if (deque_size(ReceiveDeque) > 0)
    {
        DBG_LOG_INFO("Receive Proceed, %d left. \n",
                            deque_size(ReceiveDeque));
        deque_remove_first(ReceiveDeque, (void**)&comm);
        memcpy((void *)msg,(void *)comm->Msg,comm->Size);
        *size = comm->Size;
        *ip = comm->Ip;
        *port = comm->Port;
        umm_free((void *)comm->Msg);
        umm_free((void *)comm);
    }
    else
        return NO_BUFFER_RECORDS;
   
    return(ret_val);
}
int AddToTransmit(char *str)
{
   int ret_val = NO_BUFFER_ERROR;
   
   DBG_LOG_TRACE("Into AddToTransmit. -%s- (%d)\n",str,TxCnt);
   if ( (TxCnt+strlen(str)) < BUFFER_INOUT)
   {
      strncpy(((char*)inout_buffer)+TxCnt,(const char*)str,strlen(str));
      TxCnt += strlen(str);
   }
   else
   {
     ret_val = NO_BUFFER_SPACE;
   }
   
   return(ret_val);
}
int GetNPocket(char *str)
{
   int ret_val = STRING_SIZE-1;
   
   while (str[ret_val--] == 0);
   
   return (ret_val);
}
char* ProceedTransmit(uint32_t *num)
{
   char* ret_val = 0;
   
   DBG_LOG_TRACE("Into ProceedTransmit. Count %d.\r\n\r",TxCnt);
   if (TxCnt)
   {
     (*num) = TxCnt;
     TxCnt = 0;
     ret_val = (char*)inout_buffer;
   }
   else
   {
     *num = 0;
     ret_val = 0;
   }
   
   return(ret_val);
}
int ClearBuffer()
{
    int ret_val = NO_BUFFER_ERROR;
    DBG_LOG_TRACE("Into ClearBuffer.\n");
    TxCnt = 0;
    return(ret_val);
}
/*============================================================================*/

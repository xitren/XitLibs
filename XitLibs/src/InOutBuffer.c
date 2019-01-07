// ----------------------------------------------------------------------------
//
// InOutBuffer.c - Buffers
//
// ----------------------------------------------------------------------------
//
// A.Gusev 04.09.2017 - Original
//
// ----------------------------------------------------------------------------

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
typedef struct _tagTransmiteDeque_t
{
   uint8_t              *Msg;
   uint32_t             Size;
   uint32_t             Ip;
   uint32_t             Port;
} TransmiteDeque_t;
/*============================================================================*/

/* Private variables ---------------------------------------------------------*/
static Deque *ReceiveDeque;
static Deque *TransmiteDeque;
/*============================================================================*/

/* Functions declaration -----------------------------------------------------*/
int InitBuffer()
{
    DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
                      __LINE__, __FILE__, __func__);
    int ret_val = NO_BUFFER_ERROR;
    if (deque_new(&ReceiveDeque) != 0)
        return BUFFER_ERROR;
    if (deque_new(&TransmiteDeque) != 0)
        return BUFFER_ERROR;
    return(ret_val);
}
int AddToReceive(const uint8_t *msg, uint32_t size, uint32_t ip, uint32_t port)
{
    int ret_val = NO_BUFFER_ERROR;
    ReceiveDeque_t *comm;
   
    DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
                      __LINE__, __FILE__, __func__);
    if ((msg == NULL))
    {
        DBG_LOG_ERROR("msg argument is NULL\n");
        return 0;
    }
    if ((msg != 0) && (size > 0))
    {
        comm = (ReceiveDeque_t *)umm_calloc(1,sizeof(ReceiveDeque_t));
        DBG_LOG_TRACE("ReceiveDeque_t allocated.\n");
        comm->Msg = (uint8_t *)umm_calloc(size,sizeof(uint8_t));
        DBG_LOG_TRACE("Msg allocated %d.\n",size);
        memcpy((void *)comm->Msg,(void *)msg,size);
        DBG_LOG_TRACE("Memcpy completed.\n");
        comm->Size = size;
        comm->Ip = ip;
        comm->Port = port;
        DBG_LOG_TRACE("Parameters setted.\n");
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
   
    DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
                      __LINE__, __FILE__, __func__);
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
                            (int)deque_size(ReceiveDeque));
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
int AddToTransmite(const uint8_t *msg, uint32_t size, uint32_t ip, uint32_t port)
{
    int ret_val = NO_BUFFER_ERROR;
    TransmiteDeque_t *comm;
   
    DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
                      __LINE__, __FILE__, __func__);
    if ((msg == NULL))
    {
        DBG_LOG_ERROR("msg argument is NULL\n");
        return 0;
    }
    if ((msg != 0) && (size > 0))
    {
        comm = (TransmiteDeque_t *)umm_calloc(1,sizeof(TransmiteDeque_t));
        DBG_LOG_TRACE("ReceiveDeque_t allocated.\n");
        comm->Msg = (uint8_t *)umm_calloc(size,sizeof(uint8_t));
        DBG_LOG_TRACE("Msg allocated %d.\n",size);
        memcpy((void *)comm->Msg,(void *)msg,size);
        DBG_LOG_TRACE("Memcpy completed.\n");
        comm->Size = size;
        comm->Ip = ip;
        comm->Port = port;
        DBG_LOG_TRACE("Parameters setted.\n");
        if (deque_add_last(TransmiteDeque, (void *)comm) != 0)
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
int ProceedTransmite(uint8_t *msg,uint32_t *size, uint32_t *ip, uint32_t *port)
{
    int ret_val = NO_BUFFER_ERROR;
    TransmiteDeque_t *comm;
   
    DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
                      __LINE__, __FILE__, __func__);
    if ((msg == NULL) || (size == NULL) || (ip == NULL) || (port == NULL))
    {
        DBG_LOG_ERROR("ProceedReceive argument is NULL\n");
        return 0;
    }
    if ((TransmiteDeque == NULL))
    {
        DBG_LOG_ERROR("ReceiveDeque is NULL\n");
        return 0;
    }
    if (deque_size(TransmiteDeque) > 0)
    {
        DBG_LOG_INFO("Receive Proceed, %d left. \n",
                            (int)deque_size(TransmiteDeque));
        deque_remove_first(TransmiteDeque, (void**)&comm);
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
int ClearBuffer()
{
    int ret_val = NO_BUFFER_ERROR;
    DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
                      __LINE__, __FILE__, __func__);
    if ((ReceiveDeque == NULL))
    {
        return BUFFER_ERROR;
    }
    deque_remove_all_free(ReceiveDeque);
    if ((TransmiteDeque == NULL))
    {
        return BUFFER_ERROR;
    }
    deque_remove_all_free(TransmiteDeque);
    return(ret_val);
}
/*============================================================================*/

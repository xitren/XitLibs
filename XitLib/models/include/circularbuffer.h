/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   circularbuffer.h
 * Author: gusev_a
 *
 * Created on 6 ноября 2018 г., 21:14
 */

#ifndef COLLECTIONS_C_CIRCULARBUFFER_H
#define COLLECTIONS_C_CIRCULARBUFFER_H

#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Public types --------------------------------------------------------------*/
typedef int (*StreamDataCallback_t)(int *vector,uint32_t _tsize);
/*============================================================================*/

/* Public function prototypes ------------------------------------------------*/
enum cc_stat circularbuffer_new(CircularBuffer_t* st, uint32_t _item_size,
                                uint8_t* _storage, uint32_t _storage_size);
enum cc_stat circularbuffer_push(CircularBuffer_t* st, void *item);
enum cc_stat circularbuffer_pull(CircularBuffer_t* st, void *item);
enum cc_stat circularbuffer_remove_all(CircularBuffer_t* st);
/*============================================================================*/

/* Public defines ------------------------------------------------------------*/
#define CIRCULAR_BUFFER_SIZE 3000
/*============================================================================*/
    
/* Private structures --------------------------------------------------------*/
typedef struct _tagCircularBuffer_t
{
   uint8_t*             Storage;
   uint32_t             StorageSize;
   uint32_t             ItemSize;
   uint32_t             Head;
   uint32_t             Tail;
   uint32_t             SwapVal;
} CircularBuffer_t;
/*============================================================================*/

#ifdef __cplusplus
}
#endif

#endif /* COLLECTIONS_C_CIRCULARBUFFER_H */


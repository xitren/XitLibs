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
    
/* Private structures --------------------------------------------------------*/
typedef struct _tagCircularBufferItem_t
{
   uint32_t             Channel[8];
} CircularBufferItem_t;    
typedef struct _tagCircularBuffer_t
{
   CircularBufferItem_t*        Storage;
   uint32_t                     StorageSize;
   uint32_t                     Head;
   uint32_t                     Tail;
   uint32_t                     Cycle;
} CircularBuffer_t;
/*============================================================================*/

/* Public types --------------------------------------------------------------*/
/*============================================================================*/

/* Public function prototypes ------------------------------------------------*/
enum cc_stat circularbuffer_new(CircularBuffer_t* st,
                        CircularBufferItem_t* _storage, uint32_t _storage_size);
enum cc_stat circularbuffer_push(CircularBuffer_t* st, CircularBufferItem_t *item);
enum cc_stat circularbuffer_pull(CircularBuffer_t* st, CircularBufferItem_t *item);
enum cc_stat circularbuffer_remove_all(CircularBuffer_t* st);
enum cc_stat circularbuffer_get_at(CircularBuffer_t* st, int index, 
                                            CircularBufferItem_t *item);
int circularbuffer_get_last_index(CircularBuffer_t* st);
int circularbuffer_get_first_index(CircularBuffer_t* st);
int circularbuffer_unreaded_items_size(CircularBuffer_t* st);
/*============================================================================*/

/* Public defines ------------------------------------------------------------*/
/*============================================================================*/

#ifdef __cplusplus
}
#endif

#endif /* COLLECTIONS_C_CIRCULARBUFFER_H */


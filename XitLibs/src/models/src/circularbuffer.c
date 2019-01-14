/*
  Copyright (C) 2017-2018 Gusev Arsenty

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LogModule.h"
#include "circularbuffer.h"

/* Functions declaration -----------------------------------------------------*/
enum cc_stat circularbuffer_new(CircularBuffer_t* st,
                    CircularBufferItem_t* _storage, uint32_t _storage_size)
{
    DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
                      __LINE__, __FILE__, __func__);
    
    st->Head = 0;
    st->Tail = 0;
    st->Cycle = 0;
    st->Storage = _storage;
    st->StorageSize = _storage_size;
    return CC_OK;
}
enum cc_stat circularbuffer_push(CircularBuffer_t* st, CircularBufferItem_t *item)
{
    DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
                      __LINE__, __FILE__, __func__);
    int next;
    next = st->Head + 1;  // next is where head will point to after this write.
    if (next >= st->StorageSize)
    {
        next = 0;
        st->Cycle++;
    }
    if (next == st->Tail)  // if the head + 1 == tail, circular buffer is full
        st->Tail = st->Head;
    st->Storage[st->Head] = *item;  // Load data and then move
    st->Head = next;             // head to next data offset.
    return CC_OK;  // return success to indicate successful push.
}
enum cc_stat circularbuffer_pull(CircularBuffer_t* st, CircularBufferItem_t *item)
{
    DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
                      __LINE__, __FILE__, __func__);
    int next;
    if (st->Head == st->Tail)  // if the head == tail, we don't have any data
        return CC_ITER_END;
    next = st->Tail + 1;  // next is where tail will point to after this read.
    if(next >= st->StorageSize)
        next = 0;
    *item = st->Storage[st->Tail];  // Read data and then move
    st->Tail = next;              // tail to next offset.
    return CC_OK;  // return success to indicate successful push.
}
enum cc_stat circularbuffer_remove_all(CircularBuffer_t* st)
{
    DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
                      __LINE__, __FILE__, __func__);
    st->Head = 0;
    st->Tail = 0;
    st->Cycle = 0;
    return CC_OK;
}
enum cc_stat circularbuffer_get_at(CircularBuffer_t* st, int index, 
                                                CircularBufferItem_t *item)
{
    DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
                      __LINE__, __FILE__, __func__);
    int last = circularbuffer_get_last_index(st);
    int first = circularbuffer_get_first_index(st);
    if ( (index < last) || (first <= index) ){
        return CC_ERR_INVALID_RANGE;
        DBG_LOG_TRACE("CC_ERR_INVALID_RANGE\n");
    }
    *item = st->Storage[index % st->StorageSize];  // Read data
    return CC_OK;
}
int circularbuffer_get_last_index(CircularBuffer_t* st)
{
    DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
                      __LINE__, __FILE__, __func__);
    if ( st->Tail > st->Head )
        return ((st->Tail) + (st->Cycle - 1)*st->StorageSize);
    else
        return ((st->Tail) + (st->Cycle)*st->StorageSize);
}
void increment_last_index(CircularBuffer_t* st, uint32_t inc_value)
{
    DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
                      __LINE__, __FILE__, __func__);
    int i;
    int next;
    for (i=0;i < inc_value;i++)
    {
        if (st->Head == st->Tail)  // if the head == tail, we don't have any data
            return;
        next = st->Tail + 1;  // next is where tail will point to after this read.
        if(next >= st->StorageSize)
            next = 0;
        st->Tail = next;              // tail to next offset.
    }
}
int circularbuffer_get_first_index(CircularBuffer_t* st)
{
    DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
                      __LINE__, __FILE__, __func__);
    return ((st->Head) + st->Cycle*st->StorageSize);
}
int circularbuffer_unreaded_items_size(CircularBuffer_t* st)
{
//    DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
//                      __LINE__, __FILE__, __func__);
    if ( st->Tail > st->Head )
        return ( ((st->Head) + st->Cycle*st->StorageSize) 
                - ((st->Tail) + (st->Cycle - 1)*st->StorageSize) );
    else
        return ( ((st->Head) + st->Cycle*st->StorageSize) 
                - ((st->Tail) + (st->Cycle)*st->StorageSize) );
}
/*============================================================================*/

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
enum cc_stat circularbuffer_new(CircularBuffer_t* st, uint32_t _item_size,
                                uint8_t* _storage, uint32_t _storage_size)
{
    DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
                      __LINE__, __FILE__, __func__);
    st->Head = 0;
    st->Tail = 0;
    st->Storage = _storage;
    st->ItemSize = _item_size;
    st->StorageSize = _storage_size - (_storage_size % _item_size);
    st->SwapVal = ((uint32_t)(0xFFFFFFFF / _item_size)) * _item_size;
    return CC_OK;
}
enum cc_stat circularbuffer_push(CircularBuffer_t* st, void *item)
{
    DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
                      __LINE__, __FILE__, __func__);
    st->Head += st->ItemSize;
    if ( (st->Head - st->StorageSize) > st->Tail)
        st->Tail = st->Head - st->StorageSize;
    if (st->Head > st->SwapVal)
        st->Head -= st->SwapVal;
    if ( (st->Head % st->StorageSize) 
            < ((st->Head - st->ItemSize) % st->StorageSize) )
    {
        memcpy(
                st->Storage + ((st->Head - st->ItemSize) % st->StorageSize),
                item,
                st->ItemSize
        );
    }
    else
    {
        DBG_LOG_WARNING("circularbuffer_push %d >= %d",
                ((st->Head - st->ItemSize) % st->StorageSize),
                (st->Head % st->StorageSize));
    }
    return CC_OK;
}
enum cc_stat circularbuffer_pull(CircularBuffer_t* st, void *item)
{
    DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
                      __LINE__, __FILE__, __func__);
    if ( st->Head == st->Tail)
        return CC_ITER_END;
    st->Tail += st->ItemSize;
    if (st->Tail > st->SwapVal)
        st->Tail -= st->SwapVal;
    if ( (st->Tail % st->StorageSize) 
            < ((st->Tail - st->ItemSize) % st->StorageSize) )
    {
        memcpy(
                item,
                st->Storage + ((st->Tail - st->ItemSize) % st->StorageSize),
                st->ItemSize
        );
    }
    else
    {
        DBG_LOG_WARNING("circularbuffer_pull %d >= %d",
                ((st->Tail - st->ItemSize) % st->StorageSize),
                (st->Tail % st->StorageSize));
    }
    return CC_OK;
}
enum cc_stat circularbuffer_remove_all(CircularBuffer_t* st)
{
    DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
                      __LINE__, __FILE__, __func__);
    st->Head = 0;
    st->Tail = 0;
    return CC_OK;
}
enum cc_stat circularbuffer_get_at(CircularBuffer_t* st, size_t index, void *item)
{
    DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
                      __LINE__, __FILE__, __func__);
    size_t last = circularbuffer_get_last_index(st);
    size_t first = circularbuffer_get_first_index(st);
    uint32_t ind = index * st->ItemSize;
    if ( (last <= index) && (index <= first) )
        return CC_ERR_INVALID_RANGE;
    memcpy(item,st->Storage + (ind % st->StorageSize),st->ItemSize);
    return CC_OK;
}
size_t circularbuffer_get_last_index(CircularBuffer_t* st)
{
    DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
                      __LINE__, __FILE__, __func__);
    return ((st->Tail) % st->ItemSize);
}
size_t circularbuffer_get_first_index(CircularBuffer_t* st)
{
    DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
                      __LINE__, __FILE__, __func__);
    return ((st->Head) % st->ItemSize);
}
size_t circularbuffer_unreaded_items_size(CircularBuffer_t* st)
{
    DBG_LOG_TRACE("This is line %d of file %s (function %s)\n",
                      __LINE__, __FILE__, __func__);
    return ((st->Head - st->Tail) % st->ItemSize);
}
/*============================================================================*/

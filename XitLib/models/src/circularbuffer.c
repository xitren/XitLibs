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

#include "circularbuffer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LogModule.h"

#define COPY_OBJECT(Head,ItemSize,BufferSize) ( (Head % BufferSize) < ((Head-ItemSize) % BufferSize) )

/* Functions declaration -----------------------------------------------------*/
enum cc_stat circularbuffer_new(CircularBuffer_t* st, uint32_t _item_size,
                                uint8_t* _storage, uint32_t _storage_size)
{
    st->Head = 0;
    st->Tail = 0;
    st->Storage = _storage;
    st->ItemSize = _item_size;
    st->StorageSize = _storage_size - (_storage_size % _item_size);
    st->SwapVal = ((uint32_t)(0xFFFFFFFF / _item_size)) * _item_size;
}
enum cc_stat circularbuffer_push(CircularBuffer_t* st, void *item)
{
    st->Head += st->ItemSize;
    if ( (st->Head - st->StorageSize) > st->Tail)
        st->Tail = st->Head - st->StorageSize;
    if (st->Head > st->SwapVal)
        st->Head -= st->SwapVal;
    if ( (st->Head % st->StorageSize) < ((st->Head - st->ItemSize) % st->StorageSize) )
    {
        // To Do
    }
    else
    {
        // To Do
    }
}
enum cc_stat circularbuffer_pull(CircularBuffer_t* st, void *item)
{
    
}
enum cc_stat circularbuffer_remove_all(CircularBuffer_t* st)
{
    st->Head = 0;
    st->Tail = 0;
}
/*============================================================================*/

/*
  Copyright (C) 2013-2014 Srđan Panić

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

#ifndef COLLECTIONS_C_STACK_H
#define COLLECTIONS_C_STACK_H

#include "common.h"
#include "array.h"

/**
 * A LIFO (last in first out) structure. Supports constant time
 * insertion, removal and lookup.
 */
typedef struct stack_s Stack;

/**
 * Stack configuration structure. Used to initialize a new Stack
 * with specific attributes.
 */
typedef ArrayConf StackConf;

/**
 * Stack iterator structure. Used to iterate over the elements of
 * the Stack in an ascending order. The iterator also supports
 * operations for safely adding and removing elements during
 * iteration.
 */
typedef struct stack_iter_s {
    ArrayIter i;
} StackIter;

/**
 * Stack zip iterator structure. Used to iterate over the elements
 * of two Stacks in lockstep in an ascending order until one of the
 * Stacks is exhausted. The iterator also supports operations for
 * safely adding and removing elements during iteration.
 */
typedef struct stack_zip_iter_s {
    ArrayZipIter i;
} StackZipIter;


void          stack_conf_init       (StackConf *conf);
enum cc_stat  stack_new             (Stack **out);
enum cc_stat  stack_new_conf        (StackConf const * const conf, Stack **out);
void          stack_destroy         (Stack *stack);
void          stack_destroy_free    (Stack *stack);

enum cc_stat  stack_push            (Stack *stack, void *element);
enum cc_stat  stack_peek            (Stack *stack, void **out);
enum cc_stat  stack_pop             (Stack *stack, void **out);

size_t        stack_size            (Stack *stack);
void          stack_map             (Stack *stack, void (*fn) (void *));

void          stack_iter_init       (StackIter *iter, Stack *s);
enum cc_stat  stack_iter_next       (StackIter *iter, void **out);
enum cc_stat  stack_iter_replace    (StackIter *iter, void *element, void **out);

void          stack_zip_iter_init   (StackZipIter *iter, Stack *a1, Stack *a2);
enum cc_stat  stack_zip_iter_next   (StackZipIter *iter, void **out1, void **out2);
enum cc_stat  stack_zip_iter_replace(StackZipIter *iter, void *e1, void *e2, void **out1, void **out2);



#endif /* COLLECTIONS_C_STACK_H */

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

#ifndef COLLECTIONS_C_QUEUE_H
#define COLLECTIONS_C_QUEUE_H

#include "common.h"
#include "deque.h"

/**
 * A FIFO (first in first out) structure. Supports constant time
 * insertion, removal and lookup.
 */
typedef struct queue_s Queue;

/**
 * Queue configuration object.
 */
typedef DequeConf QueueConf;

/**
 * Queue iterator object. Used to iterate over the elements of a
 * queue in an ascending order.
 */
typedef struct queue_iter_s {
    DequeIter i;
} QueueIter;

/**
 * Queue zip iterator structure. Used to iterate over the elements of two
 * queues in lockstep in an ascending order until one of the queues is
 * exhausted. The iterator also supports operations for safely adding
 * and removing elements during iteration.
 */
typedef struct queue_zip_iter_s {
    DequeZipIter i;
} QueueZipIter;


void         queue_conf_init       (QueueConf *conf);
enum cc_stat queue_new             (Queue **q);
enum cc_stat queue_new_conf        (QueueConf const * const conf, Queue **q);
void         queue_destroy         (Queue *queue);
void         queue_destroy_free    (Queue *queue);

enum cc_stat queue_peek            (Queue const * const queue, void **out);
enum cc_stat queue_poll            (Queue *queue, void **out);
enum cc_stat queue_enqueue         (Queue *queue, void *element);

size_t       queue_size            (Queue const * const queue);
void         queue_foreach         (Queue *queue, void (*op) (void*));

void         queue_iter_init       (QueueIter *iter, Queue *queue);
enum cc_stat queue_iter_next       (QueueIter *iter, void **out);
enum cc_stat queue_iter_replace    (QueueIter *iter, void *replacement, void **out);

void         queue_zip_iter_init   (QueueZipIter *iter, Queue *q1, Queue *q2);
enum cc_stat queue_zip_iter_next   (QueueZipIter *iter, void **out1, void **out2);
enum cc_stat queue_zip_iter_replace(QueueZipIter *iter, void *e1, void *e2, void **out1, void **out2);

#endif /* COLLECTIONS_C_QUEUE_H */

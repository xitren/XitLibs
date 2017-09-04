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

#ifndef COLLECTIONS_C_TREESET_H
#define COLLECTIONS_C_TREESET_H

#include "common.h"
#include "treetable.h"

/**
 * An ordered set. The lookup, deletion, and insertion are
 * performed in logarithmic time.
 */
typedef struct treeset_s TreeSet;

/**
 * TreeSet configuration structure.
 */
typedef TreeTableConf TreeSetConf;

/**
 * TreeSet iterator structure. Used to iterate over the elements of the set.
 * The iterator also supports operations for safely removing elements
 * during iteration.
 */
typedef struct treeset_iter_s {
    TreeTableIter i;
} TreeSetIter;


void          treeset_conf_init        (TreeSetConf *conf);
enum cc_stat  treeset_new              (int (*cmp) (const void*, const void*), TreeSet **set);
enum cc_stat  treeset_new_conf         (TreeSetConf const * const conf, TreeSet **set);

void          treeset_destroy          (TreeSet *set);

enum cc_stat  treeset_add              (TreeSet *set, void *element);
enum cc_stat  treeset_remove           (TreeSet *set, void *element, void **out);
void          treeset_remove_all       (TreeSet *set);

enum cc_stat  treeset_get_first        (TreeSet *set, void **out);
enum cc_stat  treeset_get_last         (TreeSet *set, void **out);
enum cc_stat  treeset_get_greater_than (TreeSet *set, void *element, void **out);
enum cc_stat  treeset_get_lesser_than  (TreeSet *set, void *element, void **out);

bool          treeset_contains         (TreeSet *set, void *element);
size_t        treeset_size             (TreeSet *set);

void          treeset_foreach          (TreeSet *set, void (*op) (const void*));

void          treeset_iter_init        (TreeSetIter *iter, TreeSet *set);
enum cc_stat  treeset_iter_next        (TreeSetIter *iter, void **element);
enum cc_stat  treeset_iter_remove      (TreeSetIter *iter, void **out);

#endif /* COLLECTIONS_C_TREESET_H */

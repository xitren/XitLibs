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

#ifndef COLLECTIONS_C_HASHSET_H
#define COLLECTIONS_C_HASHSET_H

#include "common.h"
#include "hashtable.h"

/**
 * An unordered set. The lookup, deletion, and insertion are
 * performed in amortized constant time and in the worst case
 * in amortized linear time.
 */
typedef struct hashset_s HashSet;

/**
 * HashSet configuration object.
 */
typedef HashTableConf HashSetConf;

/**
 * HashSet iterator structure. Used to iterate over the elements
 * of the HashSet. The iterator also supports operations for safely
 * removing elements during iteration.
 */
typedef struct hashset_iter_s {
    HashTableIter iter;
} HashSetIter;

void          hashset_conf_init     (HashSetConf *conf);

enum cc_stat  hashset_new           (HashSet **hs);
enum cc_stat  hashset_new_conf      (HashSetConf const * const conf, HashSet **hs);
void          hashset_destroy       (HashSet *set);

enum cc_stat  hashset_add           (HashSet *set, void *element);
enum cc_stat  hashset_remove        (HashSet *set, void *element, void **out);
void          hashset_remove_all    (HashSet *set);

bool          hashset_contains      (HashSet *set, void *element);
size_t        hashset_size          (HashSet *set);
size_t        hashset_capacity      (HashSet *set);

void          hashset_foreach       (HashSet *set, void (*op) (const void*));

void          hashset_iter_init     (HashSetIter *iter, HashSet *set);
enum cc_stat  hashset_iter_next     (HashSetIter *iter, void **out);
enum cc_stat  hashset_iter_remove   (HashSetIter *iter, void **out);

#endif /* COLLECTIONS_C_HASHSET_H */

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

#ifndef COLLECTIONS_C_SLIST_H
#define COLLECTIONS_C_SLIST_H

#include "common.h"

/**
 * A singly linked list. List is a sequential structure that
 * supports constant time insertion, deletion  and lookup at
 * the beginning of the list, while the worst case for these
 * operations is linear time.
 */
typedef struct slist_s SList;

/**
 * SList node.
 *
 * @note Modifying the links may invalidate the list structure.
 */
typedef struct snode_s {
    void           *data;
    struct snode_s *next;
} SNode;

/**
 * SList iterator structure. Used to iterate over the elements
 * of the list in an ascending order. The iterator also supports
 * operations for safely adding and removing elements during iteration.
 */
typedef struct slist_iter_s {
    size_t  index;
    SList  *list;
    SNode   *next;
    SNode   *current;
    SNode   *prev;
} SListIter;

/**
 * SList zip iterator structure. Used to iterate over two SLists in
 * lockstep in an ascending order until one of the lists is exhausted.
 * The iterator also supports operations for safely adding and
 * removing elements during iteration.
 */
typedef struct slist_zip_iter_s {
    size_t index;
    SList *l1;
    SList *l2;
    SNode *l1_next;
    SNode *l2_next;
    SNode *l1_current;
    SNode *l2_current;
    SNode *l1_prev;
    SNode *l2_prev;
} SListZipIter;


/**
 * SList configuration structure. Used to initialize a new SList with
 * specific values.
 */
typedef struct slist_conf_s {
    void  *(*mem_alloc)  (size_t size);
    void  *(*mem_calloc) (size_t blocks, size_t size);
    void   (*mem_free)   (void *block);
} SListConf;


void          slist_conf_init       (SListConf *conf);
enum cc_stat  slist_new             (SList **list);
enum cc_stat  slist_new_conf        (SListConf const * const conf, SList **list);
void          slist_destroy         (SList *list);
void          slist_destroy_free    (SList *list);

enum cc_stat  slist_splice          (SList *list1, SList *list2);
enum cc_stat  slist_splice_at       (SList *list1, SList *list2, size_t index);

enum cc_stat  slist_add             (SList *list, void *element);
enum cc_stat  slist_add_at          (SList *list, void *element, size_t index);
enum cc_stat  slist_add_all         (SList *list1, SList *list2);
enum cc_stat  slist_add_all_at      (SList *list1, SList *list2, size_t index);
enum cc_stat  slist_add_first       (SList *list, void *element);
enum cc_stat  slist_add_last        (SList *list, void *element);

enum cc_stat  slist_remove          (SList *list, void *element, void **out);
enum cc_stat  slist_remove_first    (SList *list, void **out);
enum cc_stat  slist_remove_last     (SList *list, void **out);
enum cc_stat  slist_remove_at       (SList *list, size_t index, void **out);

enum cc_stat  slist_remove_all      (SList *list);
enum cc_stat  slist_remove_all_free (SList *list);

enum cc_stat  slist_get_at          (SList *list, size_t index, void **out);
enum cc_stat  slist_get_first       (SList *list, void **out);
enum cc_stat  slist_get_last        (SList *list, void **out);

enum cc_stat  slist_sublist         (SList *list, size_t from, size_t to, SList **out);
enum cc_stat  slist_copy_shallow    (SList *list, SList **out);
enum cc_stat  slist_copy_deep       (SList *list, void *(*cp) (void*), SList **out);

enum cc_stat  slist_replace_at      (SList *list, void *element, size_t index, void **out);

size_t        slist_contains        (SList *list, void *element);
size_t        slist_contains_value  (SList *list, void *element, int (*cmp) (const void*, const void*));
enum cc_stat  slist_index_of        (SList *list, void *element, size_t *index);
enum cc_stat  slist_to_array        (SList *list, void ***out);

void          slist_reverse         (SList *list);
enum cc_stat  slist_sort            (SList *list, int (*cmp) (void const*, void const*));
size_t        slist_size            (SList *list);

void          slist_foreach         (SList *list, void (*op) (void *));

enum cc_stat  slist_filter          (SList *list, bool (*predicate) (const void*), SList **out);
enum cc_stat  slist_filter_mut      (SList *list, bool (*predicate) (const void*));

void          slist_iter_init       (SListIter *iter, SList *list);
enum cc_stat  slist_iter_remove     (SListIter *iter, void **out);
enum cc_stat  slist_iter_add        (SListIter *iter, void *element);
enum cc_stat  slist_iter_replace    (SListIter *iter, void *element, void **out);
enum cc_stat  slist_iter_next       (SListIter *iter, void **out);
size_t        slist_iter_index      (SListIter *iter);

void          slist_zip_iter_init   (SListZipIter *iter, SList *l1, SList *l2);
enum cc_stat  slist_zip_iter_next   (SListZipIter *iter, void **out1, void **out2);
enum cc_stat  slist_zip_iter_add    (SListZipIter *iter, void *e1, void *e2);
enum cc_stat  slist_zip_iter_remove (SListZipIter *iter, void **out1, void **out2);
enum cc_stat  slist_zip_iter_replace(SListZipIter *iter, void *e1, void *e2, void **out1, void **out2);
size_t        slist_zip_iter_index  (SListZipIter *iter);


#endif /* COLLECTIONS_C_SLIST_H */

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

#ifndef COLLECTIONS_C_LIST_H
#define COLLECTIONS_C_LIST_H

#include "common.h"

/**
 * A doubly linked list. List is a sequential structure that
 * supports insertion, deletion and lookup from both ends in
 * constant time, while the worst case is O(n/2) at the middle
 * of the list.
 */
typedef struct list_s List;

/**
 * List node.
 *
 * @note Modifying the links may invalidate the list structure.
 */
typedef struct node_s {
    void          *data;
    struct node_s *next;
    struct node_s *prev;
} Node;

/**
 * List iterator structure. Used to iterate over the elements of the
 * list in an ascending or descending order. The iterator also supports
 * operations for safely adding and removing elements during iteration.
 */
typedef struct list_iter_s {
    /**
     * The current position of the iterator.*/
    size_t  index;

    /**
     * The list associated with this iterator */
    List   *list;

    /**
     * Last returned node */
    Node   *last;

    /**
     * Next node in the sequence. */
    Node   *next;
} ListIter;

/**
 * List zip iterator structure. Used to iterate over two Lists in
 * lockstep in an ascending order until one of the lists is exhausted.
 * The iterator also supports operations for safely adding and
 * removing elements during iteration.
 */
typedef struct list_zip_iter_s {
    List *l1;
    List *l2;
    Node *l1_last;
    Node *l2_last;
    Node *l1_next;
    Node *l2_next;
    size_t index;
} ListZipIter;


/**
 * List configuration structure. Used to initialize a new List with specific
 * values.
 */
typedef struct list_conf_s {
    void  *(*mem_alloc)  (size_t size);
    void  *(*mem_calloc) (size_t blocks, size_t size);
    void   (*mem_free)   (void *block);
} ListConf;


void          list_conf_init       (ListConf *conf);
enum cc_stat  list_new             (List **list);
enum cc_stat  list_new_conf        (ListConf const * const conf, List **list);
void          list_destroy         (List *list);
void          list_destroy_free    (List *list);

enum cc_stat  list_splice          (List *list1, List *list2);
enum cc_stat  list_splice_at       (List *list, List *list2, size_t index);

enum cc_stat  list_add             (List *list, void *element);
enum cc_stat  list_add_at          (List *list, void *element, size_t index);
enum cc_stat  list_add_all         (List *list1, List *list2);
enum cc_stat  list_add_all_at      (List *list, List *list2, size_t index);
enum cc_stat  list_add_first       (List *list, void *element);
enum cc_stat  list_add_last        (List *list, void *element);

enum cc_stat  list_remove          (List *list, void *element, void **out);
enum cc_stat  list_remove_first    (List *list, void **out);
enum cc_stat  list_remove_last     (List *list, void **out);
enum cc_stat  list_remove_at       (List *list, size_t index, void **out);

enum cc_stat  list_remove_all      (List *list);
enum cc_stat  list_remove_all_free (List *list);

enum cc_stat  list_get_at          (List *list, size_t index, void **out);
enum cc_stat  list_get_first       (List *list, void **out);
enum cc_stat  list_get_last        (List *list, void **out);

enum cc_stat  list_sublist         (List *list, size_t from, size_t to, List **out);
enum cc_stat  list_copy_shallow    (List *list, List **out);
enum cc_stat  list_copy_deep       (List *list, void *(*cp) (void*), List **out);

enum cc_stat  list_replace_at      (List *list, void *element, size_t index, void **out);

size_t        list_contains        (List *list, void *element);
size_t        list_contains_value  (List *list, void *element, int (*cmp) (const void*, const void*));
enum cc_stat  list_index_of        (List *list, void *element, int (*cmp) (const void*, const void*), size_t *index);
enum cc_stat  list_to_array        (List *list, void ***out);

void          list_reverse         (List *list);
enum cc_stat  list_sort            (List *list, int (*cmp) (void const*, void const*));
void          list_sort_in_place   (List *list, int (*cmp) (void const*, void const*));
size_t        list_size            (List *list);

void          list_foreach         (List *list, void (*op) (void *));

enum cc_stat  list_filter_mut      (List *list, bool (*predicate) (const void*));
enum cc_stat  list_filter          (List *list, bool (*predicate) (const void*), List **out);

void          list_iter_init       (ListIter *iter, List *list);
enum cc_stat  list_iter_remove     (ListIter *iter, void **out);
enum cc_stat  list_iter_add        (ListIter *iter,  void *element);
enum cc_stat  list_iter_replace    (ListIter *iter, void *element, void **out);
size_t        list_iter_index      (ListIter *iter);
enum cc_stat  list_iter_next       (ListIter *iter, void **out);

void          list_diter_init      (ListIter *iter, List *list);
enum cc_stat  list_diter_remove    (ListIter *iter, void **out);
enum cc_stat  list_diter_add       (ListIter *iter, void *element);
enum cc_stat  list_diter_replace   (ListIter *iter, void *element, void **out);
size_t        list_diter_index     (ListIter *iter);
enum cc_stat  list_diter_next      (ListIter *iter, void **out);

void          list_zip_iter_init   (ListZipIter *iter, List *l1, List *l2);
enum cc_stat  list_zip_iter_next   (ListZipIter *iter, void **out1, void **out2);
enum cc_stat  list_zip_iter_add    (ListZipIter *iter, void *e1, void *e2);
enum cc_stat  list_zip_iter_remove (ListZipIter *iter, void **out1, void **out2);
enum cc_stat  list_zip_iter_replace(ListZipIter *iter, void *e1, void *e2, void **out1, void **out2);
size_t        list_zip_iter_index  (ListZipIter *iter);

#endif /* COLLECTIONS_C_LIST_H */
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

#ifndef COLLECTIONS_C_TREETABLE_H
#define COLLECTIONS_C_TREETABLE_H

#include "common.h"

/**
 * An ordered key-value map. TreeTable supports logarithmic time
 * insertion, removal and lookup of values.
 */
typedef struct treetable_s TreeTable;

/**
 * Red-Black tree node.
 *
 * @note Modifying this structure may invalidate the table.
 */
typedef struct rbnode_s {
	/**
	 * Key in the table. */
	void *key;

	/**
	 * Value associated with the key */
	void *value;

	/**
	 * The color of this node */
	char color;

	/**
	 * Parent of this node */
	struct rbnode_s *parent;

	/**
	 * Left child node */
	struct rbnode_s *left;

	/**
	 * Right child node */
	struct rbnode_s *right;
} RBNode;

/**
 * TreeTable table entry.
 */
typedef struct tree_table_entry_s {
	void *key;
	void *value;
} TreeTableEntry;

/**
 * TreeTable iterator structure. Used to iterate over the entries
 * of the table. The iterator also supports operations for safely
 * removing elements during iteration.
 *
 * @note This structure should only be modified through the
 * iterator functions.
 */
typedef struct tree_table_iter_s {
	TreeTable *table;
	RBNode *current;
	RBNode *next;
} TreeTableIter;

/**
 * TreeTable configuration structure. Used to initialize a new
 * TreeTable with specific attributes.
 */
typedef struct treetable_conf_s {
	int (*cmp) (const void *k1, const void *k2);
	void *(*mem_alloc) (size_t size);
	void *(*mem_calloc) (size_t blocks, size_t size);
	void (*mem_free) (void *block);
} TreeTableConf;


void treetable_conf_init(TreeTableConf *conf);
enum cc_stat treetable_new(int (*cmp) (const void*, const void*), TreeTable **tt);
enum cc_stat treetable_new_conf(TreeTableConf const * const conf, TreeTable **tt);

void treetable_destroy(TreeTable *table);
enum cc_stat treetable_add(TreeTable *table, void *key, void *val);

enum cc_stat treetable_remove(TreeTable *table, void *key, void **out);
void treetable_remove_all(TreeTable *table);
enum cc_stat treetable_remove_first(TreeTable *table, void **out);
enum cc_stat treetable_remove_last(TreeTable *table, void **out);

enum cc_stat treetable_get(TreeTable const * const table, const void *key, void **out);
enum cc_stat treetable_get_first_value(TreeTable const * const table, void **out);
enum cc_stat treetable_get_first_key(TreeTable const * const table, void **out);
enum cc_stat treetable_get_last_value(TreeTable const * const table, void **out);
enum cc_stat treetable_get_last_key(TreeTable const * const table, void **out);
enum cc_stat treetable_get_greater_than(TreeTable const * const table, const void *key, void **out);
enum cc_stat treetable_get_lesser_than(TreeTable const * const table, const void *key, void **out);

size_t treetable_size(TreeTable const * const table);
bool treetable_contains_key(TreeTable const * const table, const void *key);
size_t treetable_contains_value(TreeTable const * const table, const void *value);

void treetable_foreach_key(TreeTable *table, void (*op) (const void*));
void treetable_foreach_value(TreeTable *table, void (*op) (void*));

void treetable_iter_init(TreeTableIter *iter, TreeTable *table);
enum cc_stat treetable_iter_next(TreeTableIter *iter, TreeTableEntry *entry);
enum cc_stat treetable_iter_remove(TreeTableIter *iter, void **out);

#ifdef DEBUG
#define RB_ERROR_CONSECUTIVE_RED 0
#define RB_ERROR_BLACK_HEIGHT    1
#define RB_ERROR_TREE_STRUCTURE  2
#define RB_ERROR_OK              4

int treetable_assert_rb_rules(TreeTable *table);
#endif /* DEBUG */

#endif /* COLLECTIONS_C_TREETABLE_H */

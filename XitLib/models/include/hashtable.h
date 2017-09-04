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

#ifndef COLLECTIONS_C_HASHTABLE_H
#define COLLECTIONS_C_HASHTABLE_H

#include "array.h"
#include "common.h"

#define KEY_LENGTH_VARIABLE  -1
#define KEY_LENGTH_POINTER   sizeof(void*)

/**
 * An unordered key-value map. HashTable supports best case amortized
 * constant time insertion, removal, and lookup of values. The worst
 * case complexity for these operations is amortized linear time.
 * The performance of the table depends greatly on the quality of the
 * hash function being used.
 */
typedef struct hashtable_s HashTable;

/**
 * A HashTable table entry.
 *
 * @note modifying this structure may invalidate the table.
 */
typedef struct table_entry_s {
    /**
     * A key in the table */
    void     *key;

    /**
     * Value associated with the key */
    void     *value;

    /**
     * Hash of the key */
    size_t    hash;

    /**
     * Pointer the next entry in the list. */
    struct table_entry_s *next;
} TableEntry;

/**
 * HashTable iterator object. Used to iterate over the entries of
 * the table in an undefined order. The iterator also supports operations
 * for safely removing elements during iteration.
 *
 * @note This structure should only be modified through the iterator functions.
 */
typedef struct hashtable_iter {
    HashTable  *table;
    size_t      bucket_index;
    TableEntry *prev_entry;
    TableEntry *next_entry;
} HashTableIter;

/**
 * HashTable configuration object. Used to initialize a new HashTable
 * with specific values.
 */
typedef struct hashtable_conf_s {
    /**
     * The load factor determines how the underlying
     * table array grows. For example if the load factor
     * is 0.5 and the arrays capacity is 100, the resize will
     * be triggered once the 50th entry is added. */
    float    load_factor;

    /**
     * The initial capacity of the table array. */
    size_t   initial_capacity;

    /**
     * Length of the key or -1 if the key length is
     * variable */
    int      key_length;

    /**
     * The hash seed passed to the hash function for
     * extra 'randomness'.*/
    uint32_t hash_seed;

    /**
     * Hash function used for hashing table keys */
    size_t (*hash)        (const void *key, int l, uint32_t seed);

    /**
     * The key comparator function */
    int    (*key_compare) (const void *key1, const void *key2);

    /**
     * Memory allocators used to allocate the HashTable structure
     * and for all internal memory allocations. */
    void  *(*mem_alloc)   (size_t size);
    void  *(*mem_calloc)  (size_t blocks, size_t size);
    void   (*mem_free)    (void *block);
} HashTableConf;


void          hashtable_conf_init       (HashTableConf *conf);
enum cc_stat  hashtable_new             (HashTable **out);
enum cc_stat  hashtable_new_conf        (HashTableConf const * const conf, HashTable **out);

void          hashtable_destroy         (HashTable *table);
enum cc_stat  hashtable_add             (HashTable *table, void *key, void *val);
enum cc_stat  hashtable_get             (HashTable *table, void *key, void **out);
enum cc_stat  hashtable_remove          (HashTable *table, void *key, void **out);
void          hashtable_remove_all      (HashTable *table);
bool          hashtable_contains_key    (HashTable *table, void *key);

size_t        hashtable_size            (HashTable *table);
size_t        hashtable_capacity        (HashTable *table);

enum cc_stat  hashtable_get_keys        (HashTable *table, Array **out);
enum cc_stat  hashtable_get_values      (HashTable *table, Array **out);

size_t        hashtable_hash_string     (const void *key, int len, uint32_t seed);
size_t        hashtable_hash            (const void *key, int len, uint32_t seed);
size_t        hashtable_hash_ptr        (const void *key, int len, uint32_t seed);

void          hashtable_foreach_key     (HashTable *table, void (*op) (const void *));
void          hashtable_foreach_value   (HashTable *table, void (*op) (void *));

void          hashtable_iter_init       (HashTableIter *iter, HashTable *table);
enum cc_stat  hashtable_iter_next       (HashTableIter *iter, TableEntry **out);
enum cc_stat  hashtable_iter_remove     (HashTableIter *iter, void **out);


#define GENERAL_HASH hashtable_hash
#define STRING_HASH  hashtable_hash_string
#define POINTER_HASH hashtable_hash_ptr


#endif /* COLLECTIONS_C_HASHTABLE_H */

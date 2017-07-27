#include <time.h>
#include <stdint.h>
#include <stdio.h>

#include "hashtable.h"

/* a dummy hash function used to force collisions */
static size_t collision_hash(const void *k, int l, uint32_t s);

static size_t zero_hash(const void *k, int l, uint32_t s);

TEST_GROUP_C_SETUP1();

TEST_GROUP_C_TEARDOWN1();

TEST_C_HashTableNew();

TEST_GROUP_C_SETUP2();

TEST_GROUP_C_TEARDOWN2();

TEST_C_HashTableAdd();

TEST_GROUP_C_SETUP3();

TEST_GROUP_C_TEARDOWN3();

TEST_C_HashTableCollisionGet();

TEST_C_HashTableCollisionRemove();

TEST_GROUP_C_SETUP4();

TEST_GROUP_C_TEARDOWN4();

TEST_C_HashTableAddStringWithNullKey();

TEST_C_HashTableRemoveStringWithNullKey();

TEST_C_HashTableGetStringWithNullKey();

TEST_C_HashTableRemove();

TEST_C_HashTableRemoveAll();

TEST_C_HashTableGet();

TEST_C_HashTableSize();

TEST_GROUP_C_SETUP5();

TEST_GROUP_C_TEARDOWN5();

TEST_C_HashTableCapacity();

TEST_C_HashTableContainsKey();

int cmp_k(const void *k1, const void *k2);

TEST_GROUP_C_SETUP6();

TEST_GROUP_C_TEARDOWN6();

TEST_C_HashTableTestsMemoryChunksAsKeys();

TEST_C_HashTableIterNext();

TEST_C_HashTableIterRemove();
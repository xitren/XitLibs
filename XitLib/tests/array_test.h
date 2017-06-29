#include <time.h>
#include <stdint.h>
#include <stdio.h>

#include "array.h"

int comp(void const *e1, void const *e2);

void *copy(void *val);

bool pred1(const void *e);

bool pred2(const void *e);

void reduce_add(void *e1, void *e2, void *result);

TEST_GROUP_C_SETUP(void);

TEST_GROUP_C_TEARDOWN(void);

TEST_C_ArrayAdd(void);

TEST_C_ArrayAddAt2(void);

TEST_C_ArrayReplaceAt(void);

TEST_C_ArrayRemove(void);

TEST_C_ArrayRemoveAt(void);

TEST_C_ArrayRemoveAll(void);

TEST_C_ArrayGetAt(void);

TEST_C_ArrayIndexOf(void);

TEST_C_ArraySubarray(void);

TEST_C_ArrayShallowCopy(void);

TEST_C_ArrayDeepCopy(void);

TEST_C_ArrayReverse(void);

TEST_C_ArrayContains(void);

TEST_C_ArraySort(void);

TEST_C_ArrayIterRemove(void);

TEST_C_ArrayIterAdd(void);

TEST_C_ArrayIterReplace(void);

TEST_C_ArrayZipIterNext(void);

TEST_C_ArrayZipIterRemove(void);

TEST_C_ArrayZipIterAdd(void);

TEST_C_ArrayZipIterReplace(void);

TEST_C_ArrayReduce(void);

TEST2_GROUP_C_SETUP(void);

TEST2_GROUP_C_TEARDOWN(void);

TEST_C_ArrayAddAt(void);

TEST_C_ArrayTrimCapacity(void);

TEST_C_ArrayCapacity(void);

TEST3_GROUP_C_SETUP(void);

TEST3_GROUP_C_TEARDOWN(void);

TEST_C_ArrayFilterMut1(void);

TEST_C_ArrayFilterMut2(void);

TEST_C_ArrayFilter1(void);

TEST_C_ArrayFilter2(void);

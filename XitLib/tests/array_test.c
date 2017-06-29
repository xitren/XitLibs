#include <time.h>
#include <stdint.h>
#include <stdio.h>

#include "array.h"

static Array *v1;
static Array *v2;
static int stat;
static ArrayConf vc;

int comp(void const *e1, void const *e2)
{
    int *i = *((int**) e1);
    int *j = *((int**) e2);

    if (*i < *j)
        return -1;
    if (*i > *j)
        return 1;
    return 0;
}

void *copy(void *val)
{
    int *N = (int*)malloc(sizeof(int));
    *N = *((int*)val);
    return N;
}

bool pred1(const void *e)
{
    return *(int*)e == 0;
}

bool pred2(const void *e)
{
    return *(int*)e != 0;
}

void reduce_add(void *e1, void *e2, void *result)
{
    int el1 = e1 ? *((int*)e1) : 0;
    int el2 = e2 ? *((int*)e2) : 0;
    *((int*)result) = el1 + el2;
}

TEST_GROUP_C_SETUP(void)
{
    stat = array_new(&v1);
}

TEST_GROUP_C_TEARDOWN(void)
{
    array_destroy(v1);
}

TEST_C_ArrayAdd(void)
{
    int a = 5;
    int b = 12;
    int c = 848;
    
    TEST_GROUP_C_SETUP();

    array_add(v1, &a);
    array_add(v1, &b);
    array_add(v1, &c);

    int *ar;
    int *br;
    int *cr;

    array_get_at(v1, 0, (void*)&ar);
    array_get_at(v1, 1, (void*)&br);
    array_get_at(v1, 2, (void*)&cr);

    if (a != (*ar))
        printf("%%TEST_FAILED%% time=0 testname=ArrayAdd (models_test) message=Error\n");
    if (b != (*br))
        printf("%%TEST_FAILED%% time=0 testname=ArrayAdd (models_test) message=Error\n");
    if (c != (*cr))
        printf("%%TEST_FAILED%% time=0 testname=ArrayAdd (models_test) message=Error\n");
    
    TEST_GROUP_C_TEARDOWN();
};

TEST_C_ArrayAddAt2(void)
{
    int a = 5;
    
    TEST_GROUP_C_SETUP();

    if (0 != array_size(v1))
        printf("%%TEST_FAILED%% time=0 testname=TEST_C_ArrayAddAt2 (models_test) message=Error\n");
    if (CC_ERR_OUT_OF_RANGE != array_add_at(v1, &a, 1))
        printf("%%TEST_FAILED%% time=0 testname=TEST_C_ArrayAddAt2 (models_test) message=Error\n");
    
    TEST_GROUP_C_TEARDOWN();
};

TEST_C_ArrayReplaceAt(void)
{
    int a = 23;
    int b = 32;
    int c = 55;
    
    TEST_GROUP_C_SETUP();

    int replacement = 11;

    array_add(v1, &a);
    array_add(v1, &b);
    array_add(v1, &c);

    array_replace_at(v1, &replacement, 2, NULL);

    int *repl;
    array_get_at(v1, 2, (void*)&repl);

    if (*repl == c)
        printf("%%TEST_FAILED%% time=0 testname=ArrayReplaceAt (models_test) message=Error\n");
    if (*repl != replacement)
        printf("%%TEST_FAILED%% time=0 testname=ArrayReplaceAt (models_test) message=Error\n");
    
    TEST_GROUP_C_TEARDOWN();
};

TEST_C_ArrayRemove(void)
{
    int a = 23;
    int b = 32;
    int c = 55;
    int e = 11;
    
    TEST_GROUP_C_SETUP();

    array_add(v1, &a);
    array_add(v1, &b);
    array_add(v1, &c);
    array_add(v1, &e);

    array_remove(v1, &c, NULL);

    if (3 != array_size(v1))
        printf("%%TEST_FAILED%% time=0 testname=ArrayRemove (models_test) message=Error\n");

    int *r;
    array_get_at(v1, 2, (void*)&r);

    if (r != &e)
        printf("%%TEST_FAILED%% time=0 testname=ArrayRemove (models_test) message=Error\n");
    
    TEST_GROUP_C_TEARDOWN();
};

TEST_C_ArrayRemoveAt(void)
{
    int a = 23;
    int b = 32;
    int c = 55;
    int e = 11;
    
    TEST_GROUP_C_SETUP();

    array_add(v1, &a);
    array_add(v1, &b);
    array_add(v1, &c);
    array_add(v1, &e);

    array_remove_at(v1, 2, NULL);

    if (3 != array_size(v1))
        printf("%%TEST_FAILED%% time=0 testname=ArrayRemoveAt (models_test) message=Error\n");

    int *r;
    array_get_at(v1, 2, (void*)&r);

    if (r != &e)
        printf("%%TEST_FAILED%% time=0 testname=ArrayRemoveAt (models_test) message=Error\n");
    
    TEST_GROUP_C_TEARDOWN();
};

TEST_C_ArrayRemoveAll(void)
{
    int a = 23;
    int b = 32;
    int c = 55;
    int e = 11;
    
    TEST_GROUP_C_SETUP();

    array_add(v1, &a);
    array_add(v1, &b);
    array_add(v1, &c);
    array_add(v1, &e);

    array_remove_all(v1);

    if (0 != array_size(v1))
        printf("%%TEST_FAILED%% time=0 testname=ArrayRemoveAll (models_test) message=Error\n");
    
    TEST_GROUP_C_TEARDOWN();
};

TEST_C_ArrayGetAt(void)
{
    int a = 23;
    int b = 32;
    int c = 55;
    int e = 11;
    
    TEST_GROUP_C_SETUP();

    array_add(v1, &a);
    array_add(v1, &b);
    array_add(v1, &c);
    array_add(v1, &e);

    int *ar;
    int *cr;
    array_get_at(v1, 0, (void*)&ar);
    array_get_at(v1, 2, (void*)&cr);

    if (a != (*ar))
        printf("%%TEST_FAILED%% time=0 testname=ArrayGetAt (models_test) message=Error\n");
    if (c != (*cr))
        printf("%%TEST_FAILED%% time=0 testname=ArrayGetAt (models_test) message=Error\n");
    
    TEST_GROUP_C_TEARDOWN();
};

TEST_C_ArrayIndexOf(void)
{
    int a = 23;
    int b = 32;
    int c = 55;
    
    TEST_GROUP_C_SETUP();

    array_add(v1, &a);
    array_add(v1, &b);
    array_add(v1, &c);

    size_t ai;
    array_index_of(v1, &a, &ai);

    size_t ci;
    array_index_of(v1, &c, &ci);

    if (0 != ai)
        printf("%%TEST_FAILED%% time=0 testname=ArrayIndexOf (models_test) message=Error\n");
    if (2 != ci)
        printf("%%TEST_FAILED%% time=0 testname=ArrayIndexOf (models_test) message=Error\n");
    
    TEST_GROUP_C_TEARDOWN();
};

TEST_C_ArraySubarray(void)
{
    int a = 23;
    int b = 32;
    int c = 55;
    int e = 11;
    int f = 43;
    
    TEST_GROUP_C_SETUP();

    array_add(v1, &a);
    array_add(v1, &b);
    array_add(v1, &c);
    array_add(v1, &e);
    array_add(v1, &f);


    Array *sub;
    array_subarray(v1, 1, 3, &sub);

    if (3 != array_size(sub))
        printf("%%TEST_FAILED%% time=0 testname=ArraySubarray (models_test) message=Error\n");

    int *s0;
    int *s1;
    int *s2;
    array_get_at(sub, 0, (void*)&s0);
    array_get_at(sub, 1, (void*)&s1);
    array_get_at(sub, 2, (void*)&s2);

    if (&b != s0)
        printf("%%TEST_FAILED%% time=0 testname=ArraySubarray (models_test) message=Error\n");
    if (&c != s1)
        printf("%%TEST_FAILED%% time=0 testname=ArraySubarray (models_test) message=Error\n");
    if (&e != s2)
        printf("%%TEST_FAILED%% time=0 testname=ArraySubarray (models_test) message=Error\n");

    array_destroy(sub);
    
    TEST_GROUP_C_TEARDOWN();
};

TEST_C_ArrayShallowCopy(void)
{
    int a = 5;
    int b = 12;
    int c = 848;
    
    TEST_GROUP_C_SETUP();

    array_add(v1, &a);
    array_add(v1, &b);
    array_add(v1, &c);

    // Array *cp;
    array_copy_shallow(v1, &v2);

    if (array_size(v2) != array_size(v1))
        printf("%%TEST_FAILED%% time=0 testname=ArrayShallowCopy (models_test) message=Error\n");

    int *ga;
    int *gb;
    array_get_at(v1, 2, (void*)&ga);
    array_get_at(v2, 2, (void*)&gb);

    if (*ga != *gb)
        printf("%%TEST_FAILED%% time=0 testname=ArrayShallowCopy (models_test) message=Error\n");

    array_destroy(v2);
    
    TEST_GROUP_C_TEARDOWN();
};

TEST_C_ArrayDeepCopy(void)
{
    int a = 5;
    int b = 12;
    int c = 848;
    
    TEST_GROUP_C_SETUP();

    array_add(v1, &a);
    array_add(v1, &b);
    array_add(v1, &c);

    array_copy_deep(v1, copy, &v2);

    if (array_size(v2) != array_size(v1))
        printf("%%TEST_FAILED%% time=0 testname=ArrayDeepCopy (models_test) message=Error\n");

    int *ca;
    array_get_at(v2, 0, (void*) &ca);

    if (a != (*ca))
        printf("%%TEST_FAILED%% time=0 testname=ArrayDeepCopy (models_test) message=Error\n");
    array_destroy_free(v2);
    
    TEST_GROUP_C_TEARDOWN();
};

TEST_C_ArrayReverse(void)
{
    int a = 5;
    int b = 12;
    int c = 848;
    
    TEST_GROUP_C_SETUP();

    array_add(v1, &a);
    array_add(v1, &b);
    array_add(v1, &c);

    array_reverse(v1);

    int *i0;
    int *i1;
    int *i2;
    array_get_at(v1, 0, (void*)&i0);
    array_get_at(v1, 1, (void*)&i1);
    array_get_at(v1, 2, (void*)&i2);

    if (c != (*i0))
        printf("%%TEST_FAILED%% time=0 testname=ArrayReverse (models_test) message=Error\n");
    if (b != (*i1))
        printf("%%TEST_FAILED%% time=0 testname=ArrayReverse (models_test) message=Error\n");
    if (a != (*i2))
        printf("%%TEST_FAILED%% time=0 testname=ArrayReverse (models_test) message=Error\n");
    
    TEST_GROUP_C_TEARDOWN();
};


TEST_C_ArrayContains(void)
{
    int a = 5;
    int b = 12;
    int c = 848;
    int d = 23;
    
    TEST_GROUP_C_SETUP();

    array_add(v1, &a);
    array_add(v1, &b);
    array_add(v1, &c);
    array_add(v1, &c);

    int cc = array_contains(v1, &c);
    int ca = array_contains(v1, &a);
    int cd = array_contains(v1, &d);

    if (2 != cc)
        printf("%%TEST_FAILED%% time=0 testname=ArrayContains (models_test) message=Error\n");
    if (1 != ca)
        printf("%%TEST_FAILED%% time=0 testname=ArrayContains (models_test) message=Error\n");
    if (0 != cd)
        printf("%%TEST_FAILED%% time=0 testname=ArrayContains (models_test) message=Error\n");
    
    TEST_GROUP_C_TEARDOWN();
};


TEST_C_ArraySort(void)
{
    srand(time(NULL));
    
    TEST_GROUP_C_SETUP();

    int size = 10;
    int i;
    for (i = 0; i < size; i++) {
        int *e = (int*)malloc(sizeof(int));
        *e = rand() % 100;
        array_add(v1, (void*)e);
    }
    array_sort(v1, comp);

    int *prev;
    array_get_at(v1, 0, (void**)&prev);
    for (i = 0; i < size; i++) {
        int *e;
        array_get_at(v1, i, (void*)&e);
        if (!(*prev <= *e))
            printf("%%TEST_FAILED%% time=0 testname=ArraySort (models_test) message=Error\n");
        prev = e;
    }
    
    TEST_GROUP_C_TEARDOWN();
};

TEST_C_ArrayIterRemove(void)
{
    int a = 5;
    int b = 12;
    int c = 848;
    int d = 23;
    
    TEST_GROUP_C_SETUP();

    array_add(v1, &a);
    array_add(v1, &b);
    array_add(v1, &c);
    array_add(v1, &d);

    ArrayIter iter;
    array_iter_init(&iter, v1);

    int *e;
    while (array_iter_next(&iter, (void*) &e) != CC_ITER_END) {
        if (*e == c)
            array_iter_remove(&iter, NULL);
    }

    if (0 != array_contains(v1, &c))
        printf("%%TEST_FAILED%% time=0 testname=ArrayIterRemove (models_test) message=Error\n");
    
    TEST_GROUP_C_TEARDOWN();
};

TEST_C_ArrayIterAdd(void)
{
    int a = 1;
    int b = 2;
    int c = 3;
    int d = 4;

    int N = 80;
    
    TEST_GROUP_C_SETUP();

    array_add(v1, &a);
    array_add(v1, &b);
    array_add(v1, &c);
    array_add(v1, &d);

    ArrayIter iter;
    array_iter_init(&iter, v1);

    int *e;
    while (array_iter_next(&iter, (void*) &e) != CC_ITER_END) {
        if (*e == 3)
            array_iter_add(&iter, &N);
    }

    if (5 != array_size(v1))
        printf("%%TEST_FAILED%% time=0 testname=ArrayIterAdd (models_test) message=Error\n");

    void *n;
    array_get_at(v1, 3, &n);
    if (N != *((int*)n))
        printf("%%TEST_FAILED%% time=0 testname=ArrayIterAdd (models_test) message=Error\n");
    if (1 != array_contains(v1, &N))
        printf("%%TEST_FAILED%% time=0 testname=ArrayIterAdd (models_test) message=Error\n");

    array_get_at(v1, 4, (void*)&n);
    if (4 != *((int*)n))
        printf("%%TEST_FAILED%% time=0 testname=ArrayIterAdd (models_test) message=Error\n");
    
    TEST_GROUP_C_TEARDOWN();
};

TEST_C_ArrayIterReplace(void)
{
    int a = 5;
    int b = 12;
    int c = 848;
    int d = 23;
    
    TEST_GROUP_C_SETUP();

    int replacement = 42;

    array_add(v1, &a);
    array_add(v1, &b);
    array_add(v1, &c);
    array_add(v1, &d);

    ArrayIter iter;
    array_iter_init(&iter, v1);

    int *e;
    int *old;
    while (array_iter_next(&iter, (void*) &e) != CC_ITER_END) {
        if (*e == c)
            array_iter_replace(&iter, (void*)&replacement, (void*)&old);
    }

    size_t index;
    array_index_of(v1, (void*) &replacement, &index);

    if (2 != index)
        printf("%%TEST_FAILED%% time=0 testname=ArrayIterReplace (models_test) message=Error\n");
    if (0 != array_contains(v1, &c))
        printf("%%TEST_FAILED%% time=0 testname=ArrayIterReplace (models_test) message=Error\n");
    
    TEST_GROUP_C_TEARDOWN();
};

TEST_C_ArrayZipIterNext(void)
{
    TEST_GROUP_C_SETUP();
    
    array_add(v1, "a");
    array_add(v1, "b");
    array_add(v1, "c");
    array_add(v1, "d");

    array_new(&v2);

    array_add(v2, "e");
    array_add(v2, "f");
    array_add(v2, "g");

    ArrayZipIter zip;
    array_zip_iter_init(&zip, v1, v2);

    size_t i = 0;

    void *e1, *e2;
    while (array_zip_iter_next(&zip, &e1, &e2) != CC_ITER_END) {
        if (i == 0) {
            if (!strcmp("a", (char*) e1))
                printf("%%TEST_FAILED%% time=0 testname=ArrayZipIterNext (models_test) message=Error\n");
            if (!strcmp("e", (char*) e2))
                printf("%%TEST_FAILED%% time=0 testname=ArrayZipIterNext (models_test) message=Error\n");
        }
        if (i == 2) {
            if (!strcmp("c", (char*) e1))
                printf("%%TEST_FAILED%% time=0 testname=ArrayZipIterNext (models_test) message=Error\n");
            if (!strcmp("g", (char*) e2))
                printf("%%TEST_FAILED%% time=0 testname=ArrayZipIterNext (models_test) message=Error\n");
        }
        i++;
    }
    if (3 != i)
        printf("%%TEST_FAILED%% time=0 testname=ArrayZipIterNext (models_test) message=Error\n");
    array_destroy(v2);
    
    TEST_GROUP_C_TEARDOWN();
};

TEST_C_ArrayZipIterRemove(void)
{
    TEST_GROUP_C_SETUP();
    array_add(v1, "a");
    array_add(v1, "b");
    array_add(v1, "c");
    array_add(v1, "d");

    array_new(&v2);

    array_add(v2, "e");
    array_add(v2, "f");
    array_add(v2, "g");

    ArrayZipIter zip;
    array_zip_iter_init(&zip, v1, v2);

    void *e1, *e2;
    void *r1, *r2;
    while (array_zip_iter_next(&zip, &e1, &e2) != CC_ITER_END) {
        if (strcmp((char*) e1, "b") == 0)
            array_zip_iter_remove(&zip, &r1, &r2);
    }
    if (!strcmp("b", (char*) r1))
        printf("%%TEST_FAILED%% time=0 testname=ArrayZipIterRemove (models_test) message=Error\n");
    if (0 != array_contains(v1, "b"))
        printf("%%TEST_FAILED%% time=0 testname=ArrayZipIterRemove (models_test) message=Error\n");
    if (0 != array_contains(v2, "f"))
        printf("%%TEST_FAILED%% time=0 testname=ArrayZipIterRemove (models_test) message=Error\n");
    if (3 != array_size(v1))
        printf("%%TEST_FAILED%% time=0 testname=ArrayZipIterRemove (models_test) message=Error\n");
    if (2 != array_size(v2))
        printf("%%TEST_FAILED%% time=0 testname=ArrayZipIterRemove (models_test) message=Error\n");

    array_destroy(v2);
    TEST_GROUP_C_TEARDOWN();
};

TEST_C_ArrayZipIterAdd(void)
{
    TEST_GROUP_C_SETUP();
    array_add(v1, "a");
    array_add(v1, "b");
    array_add(v1, "c");
    array_add(v1, "d");

    array_new(&v2);

    array_add(v2, "e");
    array_add(v2, "f");
    array_add(v2, "g");

    char *h = "h";
    char *i = "i";

    ArrayZipIter zip;
    array_zip_iter_init(&zip, v1, v2);

    void *e1, *e2;
    while (array_zip_iter_next(&zip, &e1, &e2) != CC_ITER_END) {
        if (strcmp((char*) e1, "b") == 0)
            array_zip_iter_add(&zip, h, i);
    }

    size_t index;

    if (CC_OK != array_index_of(v1, "h", &index))
        printf("%%TEST_FAILED%% time=0 testname=ArrayZipIterAdd (models_test) message=Error\n");
    if (2 != index)
        printf("%%TEST_FAILED%% time=0 testname=ArrayZipIterAdd (models_test) message=Error\n");
    if (CC_OK != array_index_of(v2, "i", &index))
        printf("%%TEST_FAILED%% time=0 testname=ArrayZipIterAdd (models_test) message=Error\n");
    if (2 != index)
        printf("%%TEST_FAILED%% time=0 testname=ArrayZipIterAdd (models_test) message=Error\n");
    if (CC_OK != array_index_of(v1, "c", &index))
        printf("%%TEST_FAILED%% time=0 testname=ArrayZipIterAdd (models_test) message=Error\n");
    if (3 != index)
        printf("%%TEST_FAILED%% time=0 testname=ArrayZipIterAdd (models_test) message=Error\n");
    if (1 != array_contains(v1, "h"))
        printf("%%TEST_FAILED%% time=0 testname=ArrayZipIterAdd (models_test) message=Error\n");
    if (1 != array_contains(v2, "i"))
        printf("%%TEST_FAILED%% time=0 testname=ArrayZipIterAdd (models_test) message=Error\n");
    if (5 != array_size(v1))
        printf("%%TEST_FAILED%% time=0 testname=ArrayZipIterAdd (models_test) message=Error\n");
    if (4 != array_size(v2))
        printf("%%TEST_FAILED%% time=0 testname=ArrayZipIterAdd (models_test) message=Error\n");

    array_destroy(v2);
    
    TEST_GROUP_C_TEARDOWN();
};

TEST_C_ArrayZipIterReplace(void)
{
    TEST_GROUP_C_SETUP();
    array_add(v1, "a");
    array_add(v1, "b");
    array_add(v1, "c");
    array_add(v1, "d");

    array_new(&v2);

    array_add(v2, "e");
    array_add(v2, "f");
    array_add(v2, "g");

    char *h = "h";
    char *i = "i";

    ArrayZipIter zip;
    array_zip_iter_init(&zip, v1, v2);

    void *e1, *e2;
    void *r1, *r2;
    while (array_zip_iter_next(&zip, &e1, &e2) != CC_ITER_END) {
        if (strcmp((char*) e1, "b") == 0) {
            array_zip_iter_replace(&zip, h, i, &r1, &r2);
        }
    }

    size_t index;

    if (CC_OK != array_index_of(v1, "h", &index))
        printf("%%TEST_FAILED%% time=0 testname=ArrayZipIterReplace (models_test) message=Error\n");
    if (1 != index)
        printf("%%TEST_FAILED%% time=0 testname=ArrayZipIterReplace (models_test) message=Error\n");
    if (CC_OK != array_index_of(v2, i, &index))
        printf("%%TEST_FAILED%% time=0 testname=ArrayZipIterReplace (models_test) message=Error\n");
    if (1 != index)
        printf("%%TEST_FAILED%% time=0 testname=ArrayZipIterReplace (models_test) message=Error\n");
    if (1 != array_contains(v1, "h"))
        printf("%%TEST_FAILED%% time=0 testname=ArrayZipIterReplace (models_test) message=Error\n");
    if (1 != array_contains(v2, "i"))
        printf("%%TEST_FAILED%% time=0 testname=ArrayZipIterReplace (models_test) message=Error\n");

    array_destroy(v2);
    TEST_GROUP_C_TEARDOWN();
};

TEST_C_ArrayReduce(void)
{
    int a = 1;
    int b = 78;
    int c = 12;
    int d = 2;
    int e = 8;
    
    TEST_GROUP_C_SETUP();

    array_add(v1, &a);
    int result;
    array_reduce(v1, reduce_add, (void*)&result);

    if (1 != result)
        printf("%%TEST_FAILED%% time=0 testname=ArrayReduce (models_test) message=Error\n");

    array_add(v1, &b);
    array_reduce(v1, reduce_add, (void*)&result);

    if (79 != result)
        printf("%%TEST_FAILED%% time=0 testname=ArrayReduce (models_test) message=Error\n");

    array_add(v1, &c);
    array_add(v1, &d);
    array_add(v1, &e);
    array_reduce(v1, reduce_add, (void*)&result);

    if (101 != result)
        printf("%%TEST_FAILED%% time=0 testname=ArrayReduce (models_test) message=Error\n");
    
    TEST_GROUP_C_TEARDOWN();
};

TEST2_GROUP_C_SETUP(void)
{
    array_conf_init(&vc);
    vc.capacity = 20;
    array_new_conf(&vc, &v1);

    ArrayConf vc1;
    array_conf_init(&vc1);
    vc1.capacity = 1;
    array_new_conf(&vc1, &v2);
};

TEST2_GROUP_C_TEARDOWN(void)
{
    array_destroy(v1);
    array_destroy(v2);
};

TEST_C_ArrayAddAt(void)
{
    int a = 5;
    int b = 12;
    int c = 848;
    int e = 233;

    int ins = 123;
    
    TEST2_GROUP_C_SETUP();

    array_add(v1, &a);
    array_add(v1, &b);
    array_add(v1, &c);
    array_add(v1, &e);

    array_add_at(v1, &ins, 1);

    int *i0;
    int *i1;
    int *i2;
    int *i3;
    int *i4;

    array_get_at(v1, 0, (void*)&i0);
    array_get_at(v1, 1, (void*)&i1);
    array_get_at(v1, 2, (void*)&i2);
    array_get_at(v1, 3, (void*)&i3);
    array_get_at(v1, 4, (void*)&i4);

    if (a != (*i0))
        printf("%%TEST_FAILED%% time=0 testname=ArrayAddAt (models_test) message=Error\n");
    if (ins != (*i1))
        printf("%%TEST_FAILED%% time=0 testname=ArrayAddAt (models_test) message=Error\n");
    if (b != (*i2))
        printf("%%TEST_FAILED%% time=0 testname=ArrayAddAt (models_test) message=Error\n");
    if (c != (*i3))
        printf("%%TEST_FAILED%% time=0 testname=ArrayAddAt (models_test) message=Error\n");
    
    TEST2_GROUP_C_TEARDOWN();
};

TEST_C_ArrayTrimCapacity(void)
{
    int a = 5;
    int b = 12;
    int c = 848;
    
    TEST2_GROUP_C_SETUP();

    array_add(v1, &a);
    array_add(v1, &b);
    array_add(v1, &c);

    if (20 != array_capacity(v1))
        printf("%%TEST_FAILED%% time=0 testname=ArrayTrimCapacity (models_test) message=Error\n");
    array_trim_capacity(v1);
    if (3 != array_capacity(v1))
        printf("%%TEST_FAILED%% time=0 testname=ArrayTrimCapacity (models_test) message=Error\n");
    TEST2_GROUP_C_TEARDOWN();
};

TEST_C_ArrayCapacity(void)
{
    int a = 5;
    int b = 12;
    
    TEST2_GROUP_C_SETUP();

    array_add(v2, (void*)&a);
    if (1 != array_capacity(v2))
        printf("%%TEST_FAILED%% time=0 testname=ArrayCapacity (models_test) message=Error\n");

    array_add(v2, (void*)&b);
    if (2 != array_capacity(v2))
        printf("%%TEST_FAILED%% time=0 testname=ArrayCapacity (models_test) message=Error\n");
    TEST2_GROUP_C_TEARDOWN();
};

TEST3_GROUP_C_SETUP(void)
{
    array_new(&v1);
    for(int i=0;i<20; i++) {
        int *v = (int*)malloc(sizeof(int));
        *v = i % 2;
        array_add(v1, (void*)v);
    }
};

TEST3_GROUP_C_TEARDOWN(void)
{
    array_destroy(v1);
};

TEST_C_ArrayFilterMut1(void)
{
    TEST3_GROUP_C_SETUP();
    int ret = array_filter_mut(v1, pred1);
    if (CC_OK != ret)
        printf("%%TEST_FAILED%% time=0 testname=ArrayFilterMut1 (models_test) message=Error\n");

    if (10 != array_size(v1))
        printf("%%TEST_FAILED%% time=0 testname=ArrayFilterMut1 (models_test) message=Error\n");

    ArrayIter i;
    array_iter_init(&i, v1);
    void *e;
    while (array_iter_next(&i, &e) != CC_ITER_END) {
        if (0 != *(int*)e)
            printf("%%TEST_FAILED%% time=0 testname=ArrayAdd (models_test) message=Error\n");
    }
    TEST3_GROUP_C_TEARDOWN();
};

TEST_C_ArrayFilterMut2(void)
{
    TEST3_GROUP_C_SETUP();
    array_filter_mut(v1, pred2);

    if (10 != array_size(v1))
        printf("%%TEST_FAILED%% time=0 testname=ArrayFilterMut2 (models_test) message=Error\n");

    ArrayIter i;
    array_iter_init(&i, v1);
    void *e;
    while(array_iter_next(&i, &e) != CC_ITER_END) {
        if (1 != *(int*)e)
            printf("%%TEST_FAILED%% time=0 testname=ArrayFilterMut2 (models_test) message=Error\n");
    }
    TEST3_GROUP_C_TEARDOWN();
};

TEST_C_ArrayFilter1(void)
{
    TEST3_GROUP_C_SETUP();
    array_filter(v1, pred1, &v2);

    if (10 != array_size(v2))
        printf("%%TEST_FAILED%% time=0 testname=ArrayFilter1 (models_test) message=Error\n");

    ArrayIter i;
    array_iter_init(&i, v2);
    void *e;
    while (array_iter_next(&i, &e) != CC_ITER_END) {
        if (0 != *(int*)e)
            printf("%%TEST_FAILED%% time=0 testname=ArrayFilter1 (models_test) message=Error\n");
    }

    array_destroy(v2);
    TEST3_GROUP_C_TEARDOWN();
};

TEST_C_ArrayFilter2(void)
{
    TEST3_GROUP_C_SETUP();
    if (20 != array_size(v1))
        printf("%%TEST_FAILED%% time=0 testname=ArrayFilter2 (models_test) message=Error\n");
    array_filter(v1, pred2, &v2);

    if (10 != array_size(v2))
        printf("%%TEST_FAILED%% time=0 testname=ArrayFilter2 (models_test) message=Error\n");

    ArrayIter i;
    array_iter_init(&i, v2);
    void *e;
    while(array_iter_next(&i, &e) != CC_ITER_END) {
        if (1 != *(int*)e)
            printf("%%TEST_FAILED%% time=0 testname=ArrayFilter2 (models_test) message=Error\n");
    }

    array_destroy(v2);
    TEST3_GROUP_C_TEARDOWN();
};

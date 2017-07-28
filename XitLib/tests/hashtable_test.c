
#include "hashtable_test.h"

static HashTableConf conf;
static HashTable *table;
int stat;

/* a dummy hash function used to force collisions */
static size_t collision_hash(const void *k, int l, uint32_t s)
{
    return 1;
}

static size_t zero_hash(const void *k, int l, uint32_t s)
{
    return 0;
}

TEST_GROUP_C_SETUP1()
{
    hashtable_conf_init(&conf);
    conf.initial_capacity = 7;
    stat = hashtable_new_conf(&conf, &table);
};

TEST_GROUP_C_TEARDOWN1()
{
    hashtable_destroy(table);
};

TEST_C_HashTableNew()
{
    TEST_GROUP_C_SETUP1();
    if (CC_OK != (stat))
        printf("%%TEST_FAILED%% time=0 testname=HashTableNew (models_test) message=Error\n");
    if (0 != hashtable_size(table))
        printf("%%TEST_FAILED%% time=0 testname=HashTableNew (models_test) message=Error\n");
    /* power of 2 rounding */
    if (8 != hashtable_capacity(table))
        printf("%%TEST_FAILED%% time=0 testname=HashTableNew (models_test) message=Error\n");
    TEST_GROUP_C_TEARDOWN1();
};

TEST_GROUP_C_SETUP2()
{
    hashtable_new(&table);
};

TEST_GROUP_C_TEARDOWN2()
{
    hashtable_destroy(table);
};

TEST_C_HashTableAdd()
{
    TEST_GROUP_C_SETUP2();
    char *a = "value";
    char *b = "cookies";
    char *c = "m31";

    hashtable_add(table, "key", a);
    hashtable_add(table, "randomstring", b);
    hashtable_add(table, "5", c);

    if (3 != hashtable_size(table))
        printf("%%TEST_FAILED%% time=0 testname=HashTableAdd (models_test) message=Error\n");

    char *r;
    hashtable_get(table, "key", (void*) &r);
    if (r != a)
        printf("%%TEST_FAILED%% time=0 testname=HashTableAdd (models_test) message=Error\n");
    TEST_GROUP_C_TEARDOWN2();
};

TEST_GROUP_C_SETUP3()
{
    hashtable_conf_init(&conf);
    conf.hash = collision_hash;
    hashtable_new_conf(&conf, &table);
};

TEST_GROUP_C_TEARDOWN3()
{
    hashtable_destroy(table);
};

TEST_C_HashTableCollisionGet()
{
    TEST_GROUP_C_SETUP3();
    char *a = "value";
    char *c = "m31";

    hashtable_add(table, "key", a);
    hashtable_add(table, "randomstring", c);

    if (2 != hashtable_size(table))
        printf("%%TEST_FAILED%% time=0 testname=HashTableCollisionGet (models_test) message=Error\n");

    char *r;
    hashtable_get(table, "randomstring", (void*) &r);
    if (r != c)
        printf("%%TEST_FAILED%% time=0 testname=HashTableCollisionGet (models_test) message=Error\n");
    TEST_GROUP_C_TEARDOWN3();
};

TEST_C_HashTableCollisionRemove()
{
    TEST_GROUP_C_SETUP3();
    char *a = "value";
    char *c = "m31";

    hashtable_add(table, "key", a);
    hashtable_add(table, "randomstring", c);
    hashtable_add(table, "5", c);

    char *rm;
    hashtable_remove(table, "randomstring", (void*) &rm);
    if (2 != hashtable_size(table))
        printf("%%TEST_FAILED%% time=0 testname=HashTableCollisionRemove (models_test) message=Error\n");
    void *g;
    if (CC_ERR_KEY_NOT_FOUND != hashtable_get(table, "randomstring", (void*) &g))
        printf("%%TEST_FAILED%% time=0 testname=HashTableCollisionRemove (models_test) message=Error\n");
    TEST_GROUP_C_TEARDOWN3();
};

TEST_GROUP_C_SETUP4()
{
    hashtable_conf_init(&conf);
    conf.hash = zero_hash;
    hashtable_new_conf(&conf, &table);
};

TEST_GROUP_C_TEARDOWN4()
{
    hashtable_destroy(table);
};

TEST_C_HashTableAddStringWithNullKey()
{
    TEST_GROUP_C_SETUP4();
    char *a = "value";
    char *b = "cookies";
    char *c = "m31";

    hashtable_add(table, "key", a);
    hashtable_add(table, NULL, c);
    hashtable_add(table, "randomstring", b);
    hashtable_add(table, "5", c);
    TEST_GROUP_C_TEARDOWN4();
};


TEST_C_HashTableRemoveStringWithNullKey()
{
    TEST_GROUP_C_SETUP4();
    char *a = "value";
    char *b = "cookies";
    char *c = "m31";

    hashtable_add(table, "key", a);
    hashtable_add(table, "randomstring", b);
    hashtable_add(table, NULL, c);
    hashtable_add(table, "5", c);

    hashtable_remove(table, "randomstring", NULL);
    TEST_GROUP_C_TEARDOWN4();
};


TEST_C_HashTableGetStringWithNullKey()
{
    TEST_GROUP_C_SETUP4();
    char *a = "value";
    char *b = "cookies";
    char *c = "m31";

    hashtable_add(table, "key", a);
    hashtable_add(table, "randomstring", b);
    hashtable_add(table, NULL, c);
    hashtable_add(table, "5", c);

    void *out;
    hashtable_get(table, "randomstring", &out);
    TEST_GROUP_C_TEARDOWN4();
};


TEST_C_HashTableRemove()
{
    TEST_GROUP_C_SETUP4();
    char *a = "value";
    char *b = "cookies";
    char *c = "m31";

    hashtable_add(table, "key", a);
    hashtable_add(table, "randomstring", b);
    hashtable_add(table, "5", c);

    char *rm;
    hashtable_remove(table, "randomstring", (void*) &rm);
    if (2 != hashtable_size(table))
        printf("%%TEST_FAILED%% time=0 testname=HashTableRemove (models_test) message=Error\n");

    char *g;
    if (CC_ERR_KEY_NOT_FOUND != hashtable_get(table, "randomstring", (void*) &g))
        printf("%%TEST_FAILED%% time=0 testname=HashTableRemove (models_test) message=Error\n");
    TEST_GROUP_C_TEARDOWN4();
};


TEST_C_HashTableRemoveAll()
{
    TEST_GROUP_C_SETUP4();
    hashtable_add(table, "key", "value");
    hashtable_add(table, "randomkey", "randomvalue");

    if (2 != hashtable_size(table))
        printf("%%TEST_FAILED%% time=0 testname=HashTableRemoveAll (models_test) message=Error\n");

    hashtable_remove_all(table);
    if (0 != hashtable_size(table))
        printf("%%TEST_FAILED%% time=0 testname=HashTableRemoveAll (models_test) message=Error\n");

    char *g;
    if (CC_ERR_KEY_NOT_FOUND != hashtable_get(table, "key", (void*) &g))
        printf("%%TEST_FAILED%% time=0 testname=HashTableRemoveAll (models_test) message=Error\n");
    TEST_GROUP_C_TEARDOWN4();
};


TEST_C_HashTableGet()
{
    TEST_GROUP_C_SETUP4();
    char *val = "567";

    hashtable_add(table, "key", "value");
    hashtable_add(table, "123", val);

    char *ret;
    hashtable_get(table, "123", (void*) &ret);

    if (strncmp(val, ret, 4) != 0)
        printf("%%TEST_FAILED%% time=0 testname=HashTableGet (models_test) message=Error\n");
    TEST_GROUP_C_TEARDOWN4();
};


TEST_C_HashTableSize()
{
    TEST_GROUP_C_SETUP4();
    hashtable_add(table, "key", "value");
    hashtable_add(table, "randomstring", "cookies");
    hashtable_add(table, "5", "asdf");

    if (3 != hashtable_size(table))
        printf("%%TEST_FAILED%% time=0 testname=HashTableSize (models_test) message=Error\n");
    TEST_GROUP_C_TEARDOWN4();
};


TEST_GROUP_C_SETUP5()
{
    hashtable_conf_init(&conf);

    conf.load_factor      = 0.5f;
    conf.initial_capacity = 2;
    hashtable_new_conf(&conf, &table);
};

TEST_GROUP_C_TEARDOWN5()
{
    hashtable_destroy(table);
};

TEST_C_HashTableCapacity()
{
    TEST_GROUP_C_SETUP5();
    hashtable_add(table, "a", NULL);
    if (2 != hashtable_capacity(table))
        printf("%%TEST_FAILED%% time=0 testname=HashTableCapacity (models_test) message=Error\n");

    hashtable_add(table, "b", NULL);
    if (4 != hashtable_capacity(table))
        printf("%%TEST_FAILED%% time=0 testname=HashTableCapacity (models_test) message=Error\n");

    hashtable_add(table, "c", NULL);
    hashtable_add(table, "d", NULL);
    if (8 != hashtable_capacity(table))
        printf("%%TEST_FAILED%% time=0 testname=HashTableCapacity (models_test) message=Error\n");
    TEST_GROUP_C_TEARDOWN5();
};


TEST_C_HashTableContainsKey()
{
    TEST_GROUP_C_SETUP5();
    hashtable_add(table, "key", "value");
    hashtable_add(table, "randomstring", "cookies");
    hashtable_add(table, "5", "m31");

    if (1 != hashtable_contains_key(table, "key"))
        printf("%%TEST_FAILED%% time=0 testname=HashTableContainsKey (models_test) message=Error\n");

    hashtable_remove(table, "key", NULL);
    if (0 != hashtable_contains_key(table, "key"))
        printf("%%TEST_FAILED%% time=0 testname=HashTableContainsKey (models_test) message=Error\n");
    TEST_GROUP_C_TEARDOWN5();
};

int cmp_k(const void *k1, const void *k2)
{
    char *key1 = (char*) k1;
    char *key2 = (char*) k2;
    int i;
    for (i = 0; i < (sizeof(int) * 7); i++) {
        if (*key1 != *key2)
            return 1;
        key1++;
        key2++;
    }
    return 0;
}

TEST_GROUP_C_SETUP6()
{
    hashtable_conf_init(&conf);

    conf.hash        = GENERAL_HASH;
    conf.key_length  = sizeof(int) * 7;
    conf.key_compare = cmp_k;

    hashtable_new_conf(&conf, &table);
};

TEST_GROUP_C_TEARDOWN6()
{
    hashtable_destroy(table);
};

TEST_C_HashTableTestsMemoryChunksAsKeys()
{
    TEST_GROUP_C_SETUP6();
    int array1[] = {1,2,3,4,5,6,7};
    int array2[] = {34,1,4,1111,456,234,0};
    int array3[] = {0,9,8,7,6,5,4};

    hashtable_add(table, array1, "one");
    hashtable_add(table, array2, "two");
    hashtable_add(table, array3, "three");

    char *a;
    char *b;

    hashtable_get(table, array1, (void*) &a);
    hashtable_get(table, array3, (void*) &b);

    if (strncmp("one", a, 4) != 0)
        printf("%%TEST_FAILED%% time=0 testname=HashTableTestsMemoryChunksAsKeys (models_test) message=Error\n");
    if (strncmp("three", b, 6) != 0)
        printf("%%TEST_FAILED%% time=0 testname=HashTableTestsMemoryChunksAsKeys (models_test) message=Error\n");
    TEST_GROUP_C_TEARDOWN6();
};

TEST_C_HashTableIterNext()
{
    TEST_GROUP_C_SETUP6();
    hashtable_add(table, "one", "1");
    hashtable_add(table, "two", "2");
    hashtable_add(table, "three", "3");
    hashtable_add(table, "four", "4");
    hashtable_add(table, "five", "5");

    int one   = 0;
    int two   = 0;
    int three = 0;
    int four  = 0;
    int five  = 0;

    HashTableIter iter;
    hashtable_iter_init(&iter, table);

    TableEntry *entry;
    while (hashtable_iter_next(&iter, &entry) != CC_ITER_END) {
        char const *key = entry->key;

        if (!strcmp(key, "one"))
            one++;

        if (!strcmp(key, "two"))
            two++;

        if (!strcmp(key, "three"))
            three++;

        if (!strcmp(key, "four"))
            four++;

        if (!strcmp(key, "five"))
            five++;
    }

    if (1 != one)
        printf("%%TEST_FAILED%% time=0 testname=HashTableIterNext (models_test) message=Error\n");
    if (1 != two)
        printf("%%TEST_FAILED%% time=0 testname=HashTableIterNext (models_test) message=Error\n");
    if (1 != three)
        printf("%%TEST_FAILED%% time=0 testname=HashTableIterNext (models_test) message=Error\n");
    if (1 != four)
        printf("%%TEST_FAILED%% time=0 testname=HashTableIterNext (models_test) message=Error\n");
    if (1 != five)
        printf("%%TEST_FAILED%% time=0 testname=HashTableIterNext (models_test) message=Error\n");
    TEST_GROUP_C_TEARDOWN6();
};

TEST_C_HashTableIterRemove()
{
    TEST_GROUP_C_SETUP6();
    char *a = "foo";
    char *b = "bar";
    char *c = "baz";

    hashtable_add(table, a, "a");
    hashtable_add(table, b, "a");
    hashtable_add(table, c, "a");

    HashTableIter iter;
    hashtable_iter_init(&iter, table);

    TableEntry *entry;
    while (hashtable_iter_next(&iter, &entry) != CC_ITER_END) {
        char const *key = entry->key;

        if (!strcmp(key, "bar"))
            hashtable_iter_remove(&iter, NULL);
    }

    if (2 != hashtable_size(table))
        printf("%%TEST_FAILED%% time=0 testname=HashTableIterRemove (models_test) message=Error\n");
    if (hashtable_contains_key(table, "bar"))
        printf("%%TEST_FAILED%% time=0 testname=HashTableIterRemove (models_test) message=Error\n");
    TEST_GROUP_C_TEARDOWN6();
};

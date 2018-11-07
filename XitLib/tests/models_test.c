/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   models_test.c
 * Author: xitre
 *
 * Created on 29 июня 2017 г., 2:29
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "umm_malloc.h"
#include "ExtFunctions.h"
#include "array_test.h"
#include "hashtable_test.h"

/*
 * Simple C Test Suite
 */

int main(int argc, char** argv) {
    clock_t t,tl;
    printf("%%SUITE_STARTING%% models_test\n");
    printf("%%SUITE_STARTED%%\n");
    t = clock();

    printf("%%TEST_STARTED%% ArrayAdd (models_test)\n");
    tl = clock();
    TEST_C_ArrayAdd();
    tl = clock() - tl;
    printf("%%TEST_FINISHED%% time=%f ArrayAdd (models_test) \n",
                                    ((float)tl)/CLOCKS_PER_SEC);

    printf("%%TEST_STARTED%% ArrayAddAt2 (models_test)\n");
    tl = clock();
    TEST_C_ArrayAddAt2();
    tl = clock() - tl;
    printf("%%TEST_FINISHED%% time=%f ArrayAddAt2 (models_test) \n",
                                    ((float)tl)/CLOCKS_PER_SEC);

    printf("%%TEST_STARTED%% ArrayReplaceAt (models_test)\n");
    tl = clock();
    TEST_C_ArrayReplaceAt();
    tl = clock() - tl;
    printf("%%TEST_FINISHED%% time=%f ArrayReplaceAt (models_test) \n",
                                    ((float)tl)/CLOCKS_PER_SEC);

    printf("%%TEST_STARTED%% ArrayRemove (models_test)\n");
    tl = clock(); 
    TEST_C_ArrayRemove();
    tl = clock() - tl;
    printf("%%TEST_FINISHED%% time=%f ArrayRemove (models_test) \n",
                                    ((float)tl)/CLOCKS_PER_SEC);

    printf("%%TEST_STARTED%% ArrayRemoveAt (models_test)\n");
    tl = clock();
    TEST_C_ArrayRemoveAt();
    tl = clock() - tl;
    printf("%%TEST_FINISHED%% time=%f ArrayRemoveAt (models_test) \n",
                                    ((float)tl)/CLOCKS_PER_SEC);

    printf("%%TEST_STARTED%% ArrayRemoveAll (models_test)\n");
    tl = clock();
    TEST_C_ArrayRemoveAll();
    tl = clock() - tl;
    printf("%%TEST_FINISHED%% time=%f ArrayRemoveAll (models_test) \n",
                                    ((float)tl)/CLOCKS_PER_SEC);

    printf("%%TEST_STARTED%% ArrayGetAt (models_test)\n");
    tl = clock();
    TEST_C_ArrayGetAt();
    tl = clock() - tl;
    printf("%%TEST_FINISHED%% time=%f ArrayGetAt (models_test) \n",
                                    ((float)tl)/CLOCKS_PER_SEC);

    printf("%%TEST_STARTED%% ArrayIndexOf (models_test)\n");
    tl = clock(); 
    TEST_C_ArrayIndexOf();
    tl = clock() - tl;
    printf("%%TEST_FINISHED%% time=%f ArrayIndexOf (models_test) \n",
                                    ((float)tl)/CLOCKS_PER_SEC);

    printf("%%TEST_STARTED%% ArraySubarray (models_test)\n");
    tl = clock();
    TEST_C_ArraySubarray();
    tl = clock() - tl;
    printf("%%TEST_FINISHED%% time=%f ArraySubarray (models_test) \n",
                                    ((float)tl)/CLOCKS_PER_SEC);

    printf("%%TEST_STARTED%% ArrayShallowCopy (models_test)\n");
    tl = clock();
    TEST_C_ArrayShallowCopy();
    tl = clock() - tl;
    printf("%%TEST_FINISHED%% time=%f ArrayShallowCopy (models_test) \n",
                                    ((float)tl)/CLOCKS_PER_SEC);

    printf("%%TEST_STARTED%% ArrayDeepCopy (models_test)\n");
    tl = clock(); 
    TEST_C_ArrayDeepCopy();
    tl = clock() - tl;
    printf("%%TEST_FINISHED%% time=%f ArrayDeepCopy (models_test) \n",
                                    ((float)tl)/CLOCKS_PER_SEC);

    printf("%%TEST_STARTED%% ArrayReverse (models_test)\n");
    tl = clock();
    TEST_C_ArrayReverse();
    tl = clock() - tl;
    printf("%%TEST_FINISHED%% time=%f ArrayReverse (models_test) \n",
                                    ((float)tl)/CLOCKS_PER_SEC);

    printf("%%TEST_STARTED%% ArrayContains (models_test)\n");
    tl = clock();
    TEST_C_ArrayContains();
    tl = clock() - tl;
    printf("%%TEST_FINISHED%% time=%f ArrayContains (models_test) \n",
                                    ((float)tl)/CLOCKS_PER_SEC);

    printf("%%TEST_STARTED%% ArraySort (models_test)\n");
    tl = clock(); 
    TEST_C_ArraySort();
    tl = clock() - tl;
    printf("%%TEST_FINISHED%% time=%f ArraySort (models_test) \n",
                                    ((float)tl)/CLOCKS_PER_SEC);

    printf("%%TEST_STARTED%% ArrayIterRemove (models_test)\n");
    tl = clock();
    TEST_C_ArrayIterRemove();
    tl = clock() - tl;
    printf("%%TEST_FINISHED%% time=%f ArrayIterRemove (models_test) \n",
                                    ((float)tl)/CLOCKS_PER_SEC);

    printf("%%TEST_STARTED%% ArrayIterAdd (models_test)\n");
    tl = clock();
    TEST_C_ArrayIterAdd();
    tl = clock() - tl; 
    printf("%%TEST_FINISHED%% time=%f ArrayIterAdd (models_test) \n",
                                    ((float)tl)/CLOCKS_PER_SEC);

    printf("%%TEST_STARTED%% ArrayIterReplace (models_test)\n");
    tl = clock();
    TEST_C_ArrayIterReplace();
    tl = clock() - tl;
    printf("%%TEST_FINISHED%% time=%f ArrayIterReplace (models_test) \n",
                                    ((float)tl)/CLOCKS_PER_SEC);

//    printf("%%TEST_STARTED%% ArrayZipIterNext (models_test)\n");
//    TEST_C_ArrayZipIterNext();
//    printf("%%TEST_FINISHED%% time=0 ArrayZipIterNext (models_test) \n");
//
//    printf("%%TEST_STARTED%% ArrayZipIterRemove (models_test)\n");
//    TEST_C_ArrayZipIterRemove();
//    printf("%%TEST_FINISHED%% time=0 ArrayZipIterRemove (models_test) \n");
//
//    printf("%%TEST_STARTED%% ArrayZipIterAdd (models_test)\n");
//    TEST_C_ArrayZipIterAdd();
//    printf("%%TEST_FINISHED%% time=0 ArrayZipIterAdd (models_test) \n");
//
//    printf("%%TEST_STARTED%% ArrayZipIterReplace (models_test)\n");
//    TEST_C_ArrayZipIterReplace();
//    printf("%%TEST_FINISHED%% time=0 ArrayZipIterReplace (models_test) \n");
//
    printf("%%TEST_STARTED%% ArrayReduce (models_test)\n");
    tl = clock();
    TEST_C_ArrayReduce();
    tl = clock() - tl; 
    printf("%%TEST_FINISHED%% time=%f ArrayReduce (models_test) \n",
                                    ((float)tl)/CLOCKS_PER_SEC);

    printf("%%TEST_STARTED%% ArrayAddAt (models_test)\n"); 
    tl = clock();
    TEST_C_ArrayAddAt();
    tl = clock() - tl;
    printf("%%TEST_FINISHED%% time=%f ArrayAddAt (models_test) \n",
                                    ((float)tl)/CLOCKS_PER_SEC);

    printf("%%TEST_STARTED%% ArrayTrimCapacity (models_test)\n");
    tl = clock();
    TEST_C_ArrayTrimCapacity();
    tl = clock() - tl;
    printf("%%TEST_FINISHED%% time=%f ArrayTrimCapacity (models_test) \n",
                                    ((float)tl)/CLOCKS_PER_SEC);

    printf("%%TEST_STARTED%% ArrayCapacity (models_test)\n");
    tl = clock();
    TEST_C_ArrayCapacity();
    tl = clock() - tl;
    printf("%%TEST_FINISHED%% time=%f ArrayCapacity (models_test) \n",
                                    ((float)tl)/CLOCKS_PER_SEC);

    printf("%%TEST_STARTED%% ArrayFilterMut1 (models_test)\n");
    tl = clock();
    TEST_C_ArrayFilterMut1();
    tl = clock() - tl; 
    printf("%%TEST_FINISHED%% time=%f ArrayFilterMut1 (models_test) \n",
                                    ((float)tl)/CLOCKS_PER_SEC);

    printf("%%TEST_STARTED%% ArrayFilterMut2 (models_test)\n");
    tl = clock();
    TEST_C_ArrayFilterMut2();
    tl = clock() - tl;
    printf("%%TEST_FINISHED%% time=%f ArrayFilterMut2 (models_test) \n",
                                    ((float)tl)/CLOCKS_PER_SEC);

    printf("%%TEST_STARTED%% ArrayFilter1 (models_test)\n");
    tl = clock(); 
    TEST_C_ArrayFilter1();
    tl = clock() - tl;
    printf("%%TEST_FINISHED%% time=%f ArrayFilter1 (models_test) \n",
                                    ((float)tl)/CLOCKS_PER_SEC);

    printf("%%TEST_STARTED%% ArrayFilter2 (models_test)\n");
    tl = clock(); 
    TEST_C_ArrayFilter2();
    tl = clock() - tl;
    printf("%%TEST_FINISHED%% time=%f ArrayFilter2 (models_test) \n",
                                    ((float)tl)/CLOCKS_PER_SEC);
    
 //=============================================================================

    printf("%%TEST_STARTED%% HashTableNew (models_test)\n");
    tl = clock();
    TEST_C_HashTableNew();
    tl = clock() - tl;
    printf("%%TEST_FINISHED%% time=%f HashTableNew (models_test) \n",
                                    ((float)tl)/CLOCKS_PER_SEC);

    printf("%%TEST_STARTED%% HashTableAdd (models_test)\n");
    tl = clock();
    TEST_C_HashTableAdd();
    tl = clock() - tl;  
    printf("%%TEST_FINISHED%% time=%f HashTableAdd (models_test) \n",
                                    ((float)tl)/CLOCKS_PER_SEC);

    printf("%%TEST_STARTED%% HashTableCollisionGet (models_test)\n");
    tl = clock();
    TEST_C_HashTableCollisionGet();
    tl = clock() - tl;
    printf("%%TEST_FINISHED%% time=%f HashTableCollisionGet (models_test) \n",
                                    ((float)tl)/CLOCKS_PER_SEC);

    printf("%%TEST_STARTED%% HashTableCollisionRemove (models_test)\n");
    tl = clock();
    TEST_C_HashTableCollisionRemove();
    tl = clock() - tl;
    printf("%%TEST_FINISHED%% time=%f HashTableCollisionRemove (models_test) \n",
                                    ((float)tl)/CLOCKS_PER_SEC);

    printf("%%TEST_STARTED%% HashTableAddStringWithNullKey (models_test)\n");
    tl = clock();
    TEST_C_HashTableAddStringWithNullKey();
    tl = clock() - tl;
    printf("%%TEST_FINISHED%% time=%f HashTableAddStringWithNullKey (models_test) \n",
                                    ((float)tl)/CLOCKS_PER_SEC);

    printf("%%TEST_STARTED%% HashTableAddStringWithNullKey (models_test)\n");
    tl = clock();
    TEST_C_HashTableAddStringWithNullKey();
    tl = clock() - tl;
    printf("%%TEST_FINISHED%% time=%f HashTableAddStringWithNullKey (models_test) \n",
                                    ((float)tl)/CLOCKS_PER_SEC);

    printf("%%TEST_STARTED%% HashTableRemoveStringWithNullKey (models_test)\n");
    tl = clock();
    TEST_C_HashTableRemoveStringWithNullKey();
    tl = clock() - tl;
    printf("%%TEST_FINISHED%% time=%f HashTableRemoveStringWithNullKey (models_test) \n",
                                    ((float)tl)/CLOCKS_PER_SEC);

    printf("%%TEST_STARTED%% HashTableGetStringWithNullKey (models_test)\n");
    tl = clock();
    TEST_C_HashTableGetStringWithNullKey();
    tl = clock() - tl; 
    printf("%%TEST_FINISHED%% time=%f HashTableGetStringWithNullKey (models_test) \n",
                                    ((float)tl)/CLOCKS_PER_SEC);

    printf("%%TEST_STARTED%% HashTableRemove (models_test)\n");
    tl = clock();
    TEST_C_HashTableRemove();
    tl = clock() - tl;
    printf("%%TEST_FINISHED%% time=%f HashTableRemove (models_test) \n",
                                    ((float)tl)/CLOCKS_PER_SEC);

    printf("%%TEST_STARTED%% HashTableRemoveAll (models_test)\n");
    tl = clock();
    TEST_C_HashTableRemoveAll();
    tl = clock() - tl;
    printf("%%TEST_FINISHED%% time=%f HashTableRemoveAll (models_test) \n",
                                    ((float)tl)/CLOCKS_PER_SEC);

    printf("%%TEST_STARTED%% HashTableGet (models_test)\n");
    tl = clock(); 
    TEST_C_HashTableGet();
    tl = clock() - tl;
    printf("%%TEST_FINISHED%% time=%f HashTableGet (models_test) \n",
                                    ((float)tl)/CLOCKS_PER_SEC);

    printf("%%TEST_STARTED%% HashTableSize (models_test)\n");
    tl = clock();
    TEST_C_HashTableSize();
    tl = clock() - tl;
    printf("%%TEST_FINISHED%% time=%f HashTableSize (models_test) \n",
                                    ((float)tl)/CLOCKS_PER_SEC);

    printf("%%TEST_STARTED%% HashTableCapacity (models_test)\n");
    tl = clock();
    TEST_C_HashTableCapacity();
    tl = clock() - tl;
    printf("%%TEST_FINISHED%% time=%f HashTableCapacity (models_test) \n",
                                    ((float)tl)/CLOCKS_PER_SEC);

    printf("%%TEST_STARTED%% HashTableContainsKey (models_test)\n");
    tl = clock();
    TEST_C_HashTableContainsKey();
    tl = clock() - tl;
    printf("%%TEST_FINISHED%% time=%f HashTableContainsKey (models_test) \n",
                                    ((float)tl)/CLOCKS_PER_SEC);

    printf("%%TEST_STARTED%% HashTableTestsMemoryChunksAsKeys (models_test)\n");
    tl = clock();
    TEST_C_HashTableTestsMemoryChunksAsKeys();
    tl = clock() - tl;
    printf("%%TEST_FINISHED%% time=%f HashTableTestsMemoryChunksAsKeys (models_test) \n",
                                    ((float)tl)/CLOCKS_PER_SEC);

    printf("%%TEST_STARTED%% HashTableIterNext (models_test)\n");
    tl = clock();
    TEST_C_HashTableIterNext();
    tl = clock() - tl;
    printf("%%TEST_FINISHED%% time=%f HashTableIterNext (models_test) \n",
                                    ((float)tl)/CLOCKS_PER_SEC);

    printf("%%TEST_STARTED%% HashTableIterRemove (models_test)\n");
    tl = clock();
    TEST_C_HashTableIterRemove();
    tl = clock() - tl;
    printf("%%TEST_FINISHED%% time=%f HashTableIterRemove (models_test) \n",
                                    ((float)tl)/CLOCKS_PER_SEC);

    t = clock() - t;
    printf("%%SUITE_FINISHED%% time=%f\n",((float)t)/CLOCKS_PER_SEC);

    return (EXIT_SUCCESS);
}

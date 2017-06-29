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
#include "umm_malloc.h"
#include "ExtFunctions_models.h"
#include "array_test.h"

/*
 * Simple C Test Suite
 */

int main(int argc, char** argv) {
    printf("%%SUITE_STARTING%% models_test\n");
    printf("%%SUITE_STARTED%%\n");

    printf("%%TEST_STARTED%% ArrayAdd (models_test)\n");
    TEST_C_ArrayAdd();
    printf("%%TEST_FINISHED%% time=0 ArrayAdd (models_test) \n");

    printf("%%TEST_STARTED%% ArrayAddAt2 (models_test)\n");
    TEST_C_ArrayAddAt2();
    printf("%%TEST_FINISHED%% time=0 ArrayAddAt2 (models_test) \n");

    printf("%%TEST_STARTED%% ArrayReplaceAt (models_test)\n");
    TEST_C_ArrayReplaceAt();
    printf("%%TEST_FINISHED%% time=0 ArrayReplaceAt (models_test) \n");

    printf("%%TEST_STARTED%% ArrayRemove (models_test)\n");
    TEST_C_ArrayRemove();
    printf("%%TEST_FINISHED%% time=0 ArrayRemove (models_test) \n");

    printf("%%TEST_STARTED%% ArrayRemoveAt (models_test)\n");
    TEST_C_ArrayRemoveAt();
    printf("%%TEST_FINISHED%% time=0 ArrayRemoveAt (models_test) \n");

    printf("%%TEST_STARTED%% ArrayRemoveAll (models_test)\n");
    TEST_C_ArrayRemoveAll();
    printf("%%TEST_FINISHED%% time=0 ArrayRemoveAll (models_test) \n");

    printf("%%TEST_STARTED%% ArrayGetAt (models_test)\n");
    TEST_C_ArrayGetAt();
    printf("%%TEST_FINISHED%% time=0 ArrayGetAt (models_test) \n");

    printf("%%TEST_STARTED%% ArrayIndexOf (models_test)\n");
    TEST_C_ArrayIndexOf();
    printf("%%TEST_FINISHED%% time=0 ArrayIndexOf (models_test) \n");

    printf("%%TEST_STARTED%% ArraySubarray (models_test)\n");
    TEST_C_ArraySubarray();
    printf("%%TEST_FINISHED%% time=0 ArraySubarray (models_test) \n");

    printf("%%TEST_STARTED%% ArrayShallowCopy (models_test)\n");
    TEST_C_ArrayShallowCopy();
    printf("%%TEST_FINISHED%% time=0 ArrayShallowCopy (models_test) \n");

//    printf("%%TEST_STARTED%% ArrayDeepCopy (models_test)\n");
//    TEST_C_ArrayDeepCopy();
//    printf("%%TEST_FINISHED%% time=0 ArrayDeepCopy (models_test) \n");
//
//    printf("%%TEST_STARTED%% ArrayReverse (models_test)\n");
//    TEST_C_ArrayReverse();
//    printf("%%TEST_FINISHED%% time=0 ArrayReverse (models_test) \n");
//
//    printf("%%TEST_STARTED%% ArrayContains (models_test)\n");
//    TEST_C_ArrayContains();
//    printf("%%TEST_FINISHED%% time=0 ArrayContains (models_test) \n");
//
//    printf("%%TEST_STARTED%% ArraySort (models_test)\n");
//    TEST_C_ArraySort();
//    printf("%%TEST_FINISHED%% time=0 ArraySort (models_test) \n");
//
//    printf("%%TEST_STARTED%% ArrayIterRemove (models_test)\n");
//    TEST_C_ArrayIterRemove();
//    printf("%%TEST_FINISHED%% time=0 ArrayIterRemove (models_test) \n");
//
//    printf("%%TEST_STARTED%% ArrayIterAdd (models_test)\n");
//    TEST_C_ArrayIterAdd();
//    printf("%%TEST_FINISHED%% time=0 ArrayIterAdd (models_test) \n");
//
//    printf("%%TEST_STARTED%% ArrayIterReplace (models_test)\n");
//    TEST_C_ArrayIterReplace();
//    printf("%%TEST_FINISHED%% time=0 ArrayIterReplace (models_test) \n");
//
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
//    printf("%%TEST_STARTED%% ArrayReduce (models_test)\n");
//    TEST_C_ArrayReduce();
//    printf("%%TEST_FINISHED%% time=0 ArrayReduce (models_test) \n");
//
//    printf("%%TEST_STARTED%% ArrayAddAt (models_test)\n");
//    TEST_C_ArrayAddAt();
//    printf("%%TEST_FINISHED%% time=0 ArrayAddAt (models_test) \n");
//
//    printf("%%TEST_STARTED%% ArrayTrimCapacity (models_test)\n");
//    TEST_C_ArrayTrimCapacity();
//    printf("%%TEST_FINISHED%% time=0 ArrayTrimCapacity (models_test) \n");
//
//    printf("%%TEST_STARTED%% ArrayCapacity (models_test)\n");
//    TEST_C_ArrayCapacity();
//    printf("%%TEST_FINISHED%% time=0 ArrayCapacity (models_test) \n");
//
//    printf("%%TEST_STARTED%% ArrayFilterMut1 (models_test)\n");
//    TEST_C_ArrayFilterMut1();
//    printf("%%TEST_FINISHED%% time=0 ArrayFilterMut1 (models_test) \n");
//
//    printf("%%TEST_STARTED%% ArrayFilterMut2 (models_test)\n");
//    TEST_C_ArrayFilterMut2();
//    printf("%%TEST_FINISHED%% time=0 ArrayFilterMut2 (models_test) \n");
//
//    printf("%%TEST_STARTED%% ArrayFilter1 (models_test)\n");
//    TEST_C_ArrayFilter1();
//    printf("%%TEST_FINISHED%% time=0 ArrayFilter1 (models_test) \n");
//
//    printf("%%TEST_STARTED%% ArrayFilter2 (models_test)\n");
//    TEST_C_ArrayFilter2();
//    printf("%%TEST_FINISHED%% time=0 ArrayFilter2 (models_test) \n");

    printf("%%SUITE_FINISHED%% time=0\n");

    return (EXIT_SUCCESS);
}

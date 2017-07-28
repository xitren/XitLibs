/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   malloc_test.c
 * Author: xitre
 *
 * Created on 29 июня 2017 г., 1:54
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "umm_malloc.h"

/*
 * Simple C Test Suite
 */

void test1() {
    printf("malloc_test test 1\n");
    
   void * ptr_array[256];

   size_t i;

   int idx;

//   printf( "Size of umm_heap is %i\n", sizeof(umm_heap)       );
//   printf( "Size of header   is %i\n", sizeof(umm_heap[0])    );
//   printf( "Size of nblock   is %i\n", sizeof(umm_heap[0].header.used.next) );
//   printf( "Size of pblock   is %i\n", sizeof(umm_heap[0].header.used.prev) );
//   printf( "Size of nfree    is %i\n", sizeof(umm_heap[0].body.free.next)   );
//   printf( "Size of pfree    is %i\n", sizeof(umm_heap[0].body.free.prev)   );

//   memset( umm_heap, 0, sizeof(umm_heap) );

   //umm_info( NULL, 1 );

   for( idx=0; idx<256; ++idx )
      ptr_array[idx] = (void *)NULL;

   for( idx=0; idx<6553500; ++idx ) {
      i = rand()%256;
      int n,oldn;
      n = (idx*10)/6553500;
      if (n != oldn)
        printf("Completed %02d0%%\n",n);
      oldn = n;

      switch( rand() % 16 ) {

         case  0:
         case  1:
         case  2:
         case  3:
         case  4:
         case  5:
         case  6: ptr_array[i] = umm_realloc(ptr_array[i], 0);
                  break;
         case  7:
         case  8: ptr_array[i] = umm_realloc(ptr_array[i], rand()%40 );
                  break;

         case  9:
         case 10:
         case 11:
         case 12: ptr_array[i] = umm_realloc(ptr_array[i], rand()%100 );
                  break;

         case 13:
         case 14: ptr_array[i] = umm_realloc(ptr_array[i], rand()%200 );
                  break;

         default: ptr_array[i] = umm_realloc(ptr_array[i], rand()%400 );
                  break;
      }

   }

//   umm_info( NULL, 1 );
}

void test2() {
    printf("malloc_test test 2\n");
    //printf("%%TEST_FAILED%% time=0 testname=test2 (malloc_test) message=error message sample\n");
}

int main(int argc, char** argv) {
    clock_t t,tl;
    printf("%%SUITE_STARTING%% malloc_test\n");
    printf("%%SUITE_STARTED%%\n");
    t = clock();

    printf("%%TEST_STARTED%% Random_memory_operations (malloc_test)\n");
    tl = clock();
    test1();
    tl = clock() - tl;
    printf("%%TEST_FINISHED%% time=%f Random_memory_operations (malloc_test) \n",
                                    ((float)tl)/CLOCKS_PER_SEC);

//    printf("%%TEST_STARTED%% Random_memory_operations (malloc_test)\n");
//    tl = clock();
//    test2();
//    tl = clock() - tl;
//    printf("%%TEST_FINISHED%% time=%f Random_memory_operations (malloc_test) \n",
//                                    ((float)tl)/CLOCKS_PER_SEC);

    t = clock() - t;
    printf("%%SUITE_FINISHED%% time=%f\n",
                                    ((float)t)/CLOCKS_PER_SEC);

    return (EXIT_SUCCESS);
}

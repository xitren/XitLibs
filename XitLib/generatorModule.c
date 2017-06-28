#include "generatorModule.h"
#include "coap.h"
#include "Handler.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include <pthread.h>
//
//uint32_t IDThread1; 
//pthread_t thread1;
//
//uint32_t *ThreadGenerator() {
//    while (1) {
//        printf ("Information sended on generator\r\n\r");
//        usleep(480000);
//    }
//    return 0;
//}

int RunGenerator(ParameterList_t *TempParam)
{
//   int result;
   int  ret_val = 0;
//   int freq = 8000;
//   int i=10;
//   #ifdef DEBUG
//      printf("--//internal//-- Into RunGenerator.\r\n\r");
//   #endif
//   printf("--//internal//-- Into RunGenerator.\r\n\r");
//   content_type = COAP_CONTENTTYPE_APPLICATION_LINKFORMAT;
//   AddToTransmit("<RUNGENERATOR>\r\n\r");
//   //здесь код программы
//   result = pthread_create(&thread1,
//            NULL, // default security attributes 
//            ThreadGenerator, // thread function 
//            &IDThread1); // returns thread identifier
//    if (result != 0) {
//        printf("Error while creating generator thread!");
//        return EXIT_FAILURE;
//    }
//   
//    //pthread_cancel(thread1);
//   AddToTransmit("Generator started!\r\n\r");
//   AddToTransmit("</RUNGENERATOR>\r\n\r");

   return(ret_val);
}

int StopGenerator(ParameterList_t *TempParam)
{
//   int result;
   int  ret_val = 0;
//   int freq = 8000;
//   int i=10;
//   #ifdef DEBUG
//      printf("--//internal//-- Into StopGenerator.\r\n\r");
//   #endif
//   content_type = COAP_CONTENTTYPE_APPLICATION_LINKFORMAT;
//   AddToTransmit("<STOPGENERATOR>\r\n\r");
//   //здесь код программы
//    pthread_cancel(thread1);
///*
//   for (i;i>0;i--) {
//       printf ("Information sended on generator\r\n\r");
//       usleep(freq);
//   }
//*/
//   AddToTransmit("Generator stoped!\r\n\r");
//   AddToTransmit("</STOPGENERATOR>\r\n\r");

   return(ret_val);
}
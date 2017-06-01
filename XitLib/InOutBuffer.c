
/* Local headers -------------------------------------------------------------*/
#include "LibConfig.h"
#include "InOutBuffer.h"
#include <stdio.h>
#include <string.h>
/*============================================================================*/

/* Private variables ---------------------------------------------------------*/
char inout_buffer[BUFFER_SIZE][STRING_SIZE];
uint32_t RxCnt = 0;
uint32_t TxCnt = 0;
/*============================================================================*/

/* Functions declaration -----------------------------------------------------*/
int AddToTransmit(char *str)
{
   int ret_val = NO_BUFFER_ERROR;
   
   #ifdef DEBUG
      printf("--//internal//-- Into AddToTransmit. -%s- (%d)\r\n\r",str,TxCnt);
   #endif
   if ((RxCnt+(((TxCnt+strlen(str))/STRING_SIZE)+1)) < BUFFER_SIZE)
   {
      strncpy(((char*)inout_buffer)+TxCnt,(const char*)str,strlen(str));
      TxCnt += strlen(str);
   }
   else
   {
     ret_val = NO_BUFFER_SPACE;
   }
   
   return(ret_val);
}
int AddToReceive(char *str,uint8_t size)
{
   int ret_val = NO_BUFFER_ERROR;
   
   if (((RxCnt+((TxCnt/STRING_SIZE)+1)) < BUFFER_SIZE) && (size < STRING_SIZE))
   {
     inout_buffer[(BUFFER_SIZE-1)-(RxCnt)][0] = size;
     memcpy(((char*)inout_buffer[(BUFFER_SIZE-1)-(RxCnt++)])+1,
             (const char*)str,size);
   }
   else
   {
     ret_val = NO_BUFFER_SPACE;
   }
   
   return(ret_val);
}
int GetNPocket(char *str)
{
   int ret_val = STRING_SIZE-1;
   
   while (str[ret_val--] == 0);
   
   return (ret_val);
}
int ProceedReceive(char *str,uint8_t *size)
{
   int ret_val = NO_BUFFER_ERROR;
   
   if (RxCnt && (RxCnt < (BUFFER_SIZE - ((TxCnt/STRING_SIZE)+1))))
   {
     *size = inout_buffer[(BUFFER_SIZE-1)-(--RxCnt)][0];
     memcpy(str,((const char*)inout_buffer[(BUFFER_SIZE-1)-(RxCnt)])+1,*size);
   }
   else
   {
     str[0] = '\0';
     ret_val = NO_BUFFER_RECORDS;
   }
   
   return(ret_val);
}
char* ProceedTransmit(uint32_t *num)
{
   char* ret_val = 0;
   
   #ifdef DEBUG
      printf("--//internal//-- Into ProceedTransmit. Count %d.\r\n\r",TxCnt);
   #endif
   if (TxCnt)
   {
     (*num) = TxCnt;
     TxCnt = 0;
     ret_val = (char*)inout_buffer;
   }
   else
   {
     *num = 0;
     ret_val = 0;
   }
   
   return(ret_val);
}
int ClearBuffer()
{
   int ret_val = NO_BUFFER_ERROR;
   RxCnt = 0;
   TxCnt = 0;
   return(ret_val);
}
/*============================================================================*/

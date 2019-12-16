/**
 * Author:          Arsenty GUSEV <xitren@ya.ru>
 */
#ifndef circular_PRINTF_H
#define circular_PRINTF_H

#include <errno.h>
#include <stdint.h>
#include <string.h>
#include "ringbuff.h"

#define BUFF_PRINT   10000

#define ISSPEC2(a)   ((a == 'l') || (a == 'h'))
#define ISDIGIT(a)   (('0' <= a) && (a <= '9'))
#define ISPOINT(a)   (('.' == a))
#define MAX(a, b)   ((b & ((a - b) >> 31)) | (a & (~(a - b) >> 31)))
#define MIN(a, b)   ((a & ((a - b) >> 31)) | (b & (~(a - b) >> 31)))

int circular_printf(circular_buff_t* buff, const char *format, ...);
void	bzero(void *s, size_t n);

#endif










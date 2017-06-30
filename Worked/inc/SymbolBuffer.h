/* 
 * File:   SymbolBuffer.h
 * Author: Toshiba
 *
 * Created on 7 Апрель 2017 г., 19:07
 */

#ifndef SYMBOLBUFFER_H
#define SYMBOLBUFFER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include "xitlibtypes.h"
    
char debug_t [400]; // log buffer
int log_position;

char* ReplaceNullSymb (char *buf1);
char* ReadBuf(char* debug_t, char* buf, int bufSize);
void AddToBuf(char* text, int textSize);
int SpaceLeft(char* buf, int bufferSize);
int BufLength(char* buf);
int WriteToFile(char* buf);
int ClearBuf(char* buf, int size);
void Log(char* text);

#ifdef __cplusplus
}
#endif

#endif /* SYMBOLBUFFER_H */


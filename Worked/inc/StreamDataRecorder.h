
/* Global headers ------------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>
#include "xitlibtypes.h"             /* Application Header.            */
#include "LibConfig.h"
/*============================================================================*/

#ifndef __EEGRECORDER_H__
#define __EEGRECORDER_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Public defines ------------------------------------------------------------*/
#define MEMORY_STREAM BUFFER_SAMPLE_SIZE*BUFFER_1ST_MAX*4+BUFFER_SAMPLE_SIZE*BUFFER_2ND_MAX*4+EEG_HISTORY_SIZE*4+20+(BUFFER_SAMPLE_SIZE-1)*8
/*============================================================================*/

/* Public types --------------------------------------------------------------*/
typedef int (*StreamDataCallback_t)(int *vector,uint32_t _tsize);
/*============================================================================*/

/* Public variables ----------------------------------------------------------*/
extern uint8_t signal_type;
/*============================================================================*/

/* Public function prototypes ------------------------------------------------*/
#ifdef EXTMEMSERVER
    int EEGPutExtMem(ParameterList_t *TempParam);    
#endif
int GetLastBlock(ParameterList_t *TempParam);
int GetConcreteBlock(ParameterList_t *TempParam);
int GetRecord(ParameterList_t *TempParam);
uint32_t GetDataPtrCnt(int32_t _pointer, int32_t _size, int32_t *_buffer);
uint32_t AddHistoryExtId(uint32_t _extid);
void EEG_dump(const uint8_t *buf, uint32_t buflen);
uint8_t EEGTestInit(uint32_t _signal_amplitude[7],uint32_t _signal_frequency[7]);
uint8_t EEGRecorderInit(uint8_t _signal_type,uint32_t _sample_frequency);
uint8_t MakeEEGSample(uint8_t _channel, int32_t _value);
#ifdef CPU
int MOVEMENTGet(ParameterList_t *TempParam);
uint32_t GetMovDataReadyCnt(int32_t _size,int32_t *_buffer);
int getMovement();
int MakeEEGFromFile(char *filename);
int WorkEEGFromFile(char *filename,StreamDataCallback_t _callback); 
#endif
uint32_t GetCnt();
uint32_t GetSamplesCnt();
uint32_t GetDataReady(int32_t *_buffer);
//uint32_t GetDataReady(int32_t _size,int32_t *_buffer);
uint32_t GetDataReadyCnt(int32_t _size,int32_t *_buffer);
void AddSample();
void Clear(void);
/*============================================================================*/

#ifdef __cplusplus
}
#endif

#endif

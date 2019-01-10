// ----------------------------------------------------------------------------
//
// StreamDataRecorder.h - Recorder to store and process stream data with speed
//                          more than 20 milliseconds.
//
// ----------------------------------------------------------------------------

/* Global headers ------------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>
#include "xitlibtypes.h"             /* Application Header.            */
#include "LibConfig.h"
#include "circularbuffer.h"
/*============================================================================*/

#ifndef __EEGRECORDER_H__
#define __EEGRECORDER_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Public defines ------------------------------------------------------------*/
#define MAX_SAMPLE_SIZE 8
/*============================================================================*/

/* Public types --------------------------------------------------------------*/
/*============================================================================*/

/* Public variables ----------------------------------------------------------*/
extern const char* global_link_streamer[][2];
/*============================================================================*/

/* Public function prototypes ------------------------------------------------*/
void InitStreamRecorder(CircularBufferItem_t* _storage, uint32_t _storage_size, 
        uint32_t _sample_frequency, uint32_t _sample_size);
void AddSample(void);
void ClearStreamRecorder(void);
int GetStreamDataReadyCnt(void);
int StreamRecorderCommand(uint8_t Method, uint8_t MediaType, 
        ParameterList_t *TempParam, uint8_t *data, 
        uint32_t *data_size, uint32_t buffer_size);
int StreamRecorderCurrentCommand(uint8_t Method, uint8_t MediaType, 
        ParameterList_t *TempParam, uint8_t *data, 
        uint32_t *data_size, uint32_t buffer_size);
int StreamRecorderLastCommand(uint8_t Method, uint8_t MediaType, 
        ParameterList_t *TempParam, uint8_t *data, 
        uint32_t *data_size, uint32_t buffer_size);
/*============================================================================*/

#ifdef __cplusplus
}
#endif

#endif

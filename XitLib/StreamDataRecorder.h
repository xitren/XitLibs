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
void InitStreamRecorder(void);
void AddSample(void);
void ClearStreamRecorder(void);
/*============================================================================*/

#ifdef __cplusplus
}
#endif

#endif

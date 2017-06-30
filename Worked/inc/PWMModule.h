
/* Global headers ------------------------------------------------------------*/
#include <stdio.h>
#include "xitlibtypes.h"
/*============================================================================*/

#ifndef __LEDCODE_H__
#define __LEDCODE_H__  
#ifdef __cplusplus
extern "C" {
#endif

/* Public function prototypes ------------------------------------------------*/
void SetLedsUnderPWM(void);
void IncPWM(void);
void ChangeLedsCode(void);
void SetCStatLedsUnderPWM(uint8_t qred,uint8_t qgreen,uint8_t qblue);
void SetServo1UnderPWM(uint8_t c);
void SetServo2UnderPWM(uint8_t c);
/*============================================================================*/

#ifdef __cplusplus
}
#endif
#endif
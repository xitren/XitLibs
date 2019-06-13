// ----------------------------------------------------------------------------
//
// ConfigMem.h - Contains configuration registers and system API
//
// ----------------------------------------------------------------------------

/* Global headers ------------------------------------------------------------*/
#include <stdio.h>
#include "xitlibtypes.h"
/*============================================================================*/

#ifndef __ANIMATION_LINE_H__
#define __ANIMATION_LINE_H__  

#ifdef __cplusplus
extern "C" {
#endif

/* Public defines ------------------------------------------------------------*/
#define LED_WIDTH 16
#define LED_HEIGHT 10
    
typedef struct _tagUserFigure_t
{
    char		size_type;	// 0 - full data	16 * 3 * 10
					// 1 - quarter data	8 * 3 * 5
					// 2 - area data	4 * 3 * 4
					// 3 - small area data	2 * 3 * 2
    char		*name;
    uint32_t		show_time;
    uint8_t		*data;
} UserFigure_t;

typedef int (*DrawFunction_t)(
            UserFigure_t *data
);    
/*============================================================================*/

/* Public types --------------------------------------------------------------*/
/*============================================================================*/

/* Public variables ----------------------------------------------------------*/
/*============================================================================*/

/* Public function prototypes ------------------------------------------------*/
/*============================================================================*/

#ifdef __cplusplus
}
#endif

#endif
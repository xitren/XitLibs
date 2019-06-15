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
    
#ifndef ANIM_SET_BIT
    #define ANIM_SET_BIT(REG, BIT)     ((REG) |= (0x01 << BIT))
#endif
#ifndef ANIM_CLEAR_BIT
    #define ANIM_CLEAR_BIT(REG, BIT)   ((REG) &= ~(0x01 << BIT))
#endif
#ifndef ANIM_READ_BIT
    #define ANIM_READ_BIT(REG, BIT)    ((REG) & (0x01 << BIT))
#endif
/*============================================================================*/

/* Public types --------------------------------------------------------------*/
typedef struct _tagUserFigure_t
{
    char		size_type;	// 0 - full data	16 * 10 * 3
					//	    uint8_t [2][10][3]
					// 1 - quarter data	8 * 5 * 3
					//	    uint8_t [1][5][3]
					// !!!!!ONLY SIZES BELOW COPIES THE DATA
					// 2 - area data	4 * 4 * 3
					//	    uint8_t [2][3]
					// 3 - small area data	2 * 2 * 3
					//	    uint8_t [2]
    char		*name;
    uint32_t		show_time;
    uint8_t		x;
    uint8_t		y;
    uint8_t		*data;
} UserFigure_t;

typedef int (*DrawFunction_t)(
            UserFigure_t *data
);    

enum timeline_mode {
    TIMELINE_INCREMENT_DRAW			= 0,
    TIMELINE_INDEPENDENT_CYCLE_DRAW		= 1,
};
/*============================================================================*/

/* Public variables ----------------------------------------------------------*/
/*============================================================================*/

/* Public function prototypes ------------------------------------------------*/
int AnimationLine(uint8_t Method, uint8_t MediaType, ParameterList_t *TempParam,
        uint8_t *data, uint32_t *data_size, uint32_t buffer_size);
int AddAnimationFigure(char _size_type, char *_name,
				uint32_t _show_time, uint8_t *_data, 
				uint8_t _x, uint8_t _y);
void InitCfgAnimLine(DrawFunction_t _func, uint8_t _mode);
void ResetAnimationTime(void);
void IncAnimationTime(void);
void MainAnimationCycle(void);
/*============================================================================*/

#ifdef __cplusplus
}
#endif

#endif
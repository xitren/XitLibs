
/* Global headers ------------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>
/*============================================================================*/

#ifndef __IMAGEVIS_H__
#define __IMAGEVIS_H__  
#ifdef __cplusplus
extern "C" {
#endif

/* Public types --------------------------------------------------------------*/
typedef unsigned char       uint8_t;
typedef unsigned short      uint16_t;
#ifdef PLATFORM_LINUX
    typedef unsigned int        uint32_t;
#else
    //typedef unsigned long       uint32_t;
#endif
typedef short               int16_t;
/*============================================================================*/

/* Public variables ----------------------------------------------------------*/
extern uint32_t MAXFRAMES;
extern uint32_t MAXSTEPS;
extern uint8_t ImgP[8][3];
extern unsigned char selection[4];
extern int cycle_cnt;
extern int t_counter;

#ifdef P300
    #define MEM_USE sizeof(float)*(640+1920+160+12800+6400+6400+320+320+960+40+960+40)
#endif
/*============================================================================*/

/* Public function prototypes ------------------------------------------------*/
//void InitImageCVEP(void);
//void devcvepshowme(void);
#ifdef P300
void InitImageP300(void);
void devp300showme(void);
#endif
/*============================================================================*/

#ifdef __cplusplus
}
#endif
#endif

/* Local headers -------------------------------------------------------------*/
#include "ImageVisualise.h"
//#include "cvepv4.h"
#ifdef P300
#include "p300v5.h"
#endif
/*============================================================================*/

/* Private variables ---------------------------------------------------------*/
uint32_t MAXSTEPS;
uint32_t MAXFRAMES;
uint8_t ImgP[8][3];
int cycle_cnt;
unsigned char patterns[256];
unsigned char selection[4];
uint32_t RGBY[8][4][4];
unsigned char image_flag;
int t_counter;
/*============================================================================*/

/* Functions declaration -----------------------------------------------------*/
void patterns_init()
{
    int i,j,l,k;
    t_counter = 0;
    for (l=0;l<4;l++)
    {
        for (i=0;i<8;i++)
        {
            for (j=0;j<3;j++)
            {
                ImgP[i][j] = 0;
                for (k=0;k<8;k++)
                {
                  ImgP[i][j] += (((patterns)[l*64+i+k*8] & (0x01 << j)) >> j) << k;
                }
            }
        }
        for (i=0;i<4;i++)
        {
            RGBY[i][0][l] = 0;
            RGBY[i][1][l] = 0;
            RGBY[i][2][l] = 0;
            RGBY[i][3][l] = 0;
            for (j=0;j<3;j++)
            {
                RGBY[i][2][l] += (ImgP[i][j] & 0xF0) << (j*8);
                RGBY[i][0][l] += (ImgP[i][j] & 0x0F) << (j*8);
            }
        }
        for (i=4;i<8;i++)
        {
            RGBY[i][0][l] = 0;
            RGBY[i][1][l] = 0;
            RGBY[i][2][l] = 0;
            RGBY[i][3][l] = 0;
            for (j=0;j<3;j++)
            {
                RGBY[i][3][l] += (ImgP[i][j] & 0xF0) << (j*8);
                RGBY[i][1][l] += (ImgP[i][j] & 0x0F) << (j*8);
            }
        }
    }
    return;
}	
//void devcvepshowme(void)
//{
//    int i,j,k;
//    selection[0] = 0;
//    selection[1] = 0;
//    selection[2] = 0;
//    selection[3] = 0;
//    cvepshow(t_counter++,selection);
//    for (i=0;i<8;i++)
//    {
//        for (j=0;j<3;j++)
//        {
//            uint32_t t = (RGBY[i][0][selection[0]]);
//            for (k=1;k<4;k++)
//            {
//                t = t | (RGBY[i][k][selection[k]]);
//            }
//            ImgP[i][j] = t >> (j*8);
//        }
//    }
//    return;
//}
//void InitImageCVEP(void)
//{
//    cvepv4_initialize();
//    cveppatterns(patterns);
//    MAXSTEPS = cvep_nStepSamples;  
//    MAXFRAMES = cvep_nFrameSamples;  
//    image_flag = 0;
//    patterns_init();
//    return;
//}
#ifdef P300
void devp300showme(void)
{
    int i,j,k;
    selection[0] = 0;
    selection[1] = 0;
    selection[2] = 0;
    selection[3] = 0;
    p300show(t_counter,selection);
    for (i=0;i<8;i++)
    {
        for (j=0;j<3;j++)
        {
            uint32_t t = (RGBY[i][0][selection[0]]);
            for (k=1;k<4;k++)
            {
                t = t | (RGBY[i][k][selection[k]]);
            }
            ImgP[i][j] = t >> (j*8);
        }
    }
    return;
}
void InitImageP300(void)
{
    p300v5_initialize();
    p300patterns(patterns);
    MAXSTEPS = p300_nStepSamples;  
    MAXFRAMES = p300_nFrameSamples; 
    image_flag = 0;
    patterns_init();
    return;
}
#endif
/*============================================================================*/

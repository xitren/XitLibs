/*
 * File: cvepv4.h
 *
 * MATLAB Coder version            : 2.6
 * C/C++ source code generated on  : 01-Dec-2015 14:35:47
 */

#ifndef __CVEPV4_H__
#define __CVEPV4_H__

/* Include files */
#include <float.h>
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rtwtypes.h"
#include "cvepv4_types.h"

/* Custom Header Code */
// cvep v4
#define cvep_nFrameSamples             8
#define cvep_nStepSamples              64

// p300 v5 & v6
#define p300_nFrameSamples             32
#define p300_nStepSamples              32

/* Function Declarations */
extern void cvepgenerate(int t, int data[5]);
extern boolean_T cvepinit(boolean_T learn);
extern void cveppatterns(unsigned char patterns[256]);
extern void cveprun(const int eegData[512], signed char *result, int *learn,
                    float *successRes, float *falseRes);
extern void cvepshow(int t, unsigned char selection[4]);
extern void cvepv4_initialize(void);
extern void cvepv4_terminate(void);

#endif

/*
 * File trailer for cvepv4.h
 *
 * [EOF]
 */

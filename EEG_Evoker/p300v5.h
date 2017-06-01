/*
 * File: p300v5.h
 *
 * MATLAB Coder version            : 2.6
 * C/C++ source code generated on  : 01-Dec-2015 14:36:16
 */

#ifndef __P300V5_H__
#define __P300V5_H__

/* Include files */
#include <float.h>
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rtwtypes.h"
#include "p300v5_types.h"

#ifdef P300
/* Custom Header Code */
// cvep v4
#define cvep_nFrameSamples             8
#define cvep_nStepSamples              64

// p300 v5
#define p300_nFrameSamples             32
#define p300_nStepSamples              32

/* Function Declarations */
extern void p300generate(int t, int data[5]);
extern boolean_T p300init(boolean_T learn);
extern void p300patterns(unsigned char patterns[256]);
extern void p300run(const int eegData[256], signed char *result, int *learn,
                    float *successRes, float *falseRes);
extern void p300show(int t, unsigned char selection[4]);
extern void p300v5_initialize(void);
extern void p300v5_terminate(void);

#endif
#endif

/*
 * File trailer for p300v5.h
 *
 * [EOF]
 */

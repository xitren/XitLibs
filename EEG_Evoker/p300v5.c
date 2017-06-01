/*
 * File: p300v5.c
 *
 * MATLAB Coder version            : 2.6
 * C/C++ source code generated on  : 01-Dec-2015 14:36:16
 */

/* Include files */
#include "p300v5.h"

/* Type Definitions */
#ifndef typedef_struct_T
#define typedef_struct_T

typedef struct {
  float weights[80];
  float threshold;
  float mu[2];
  float sigma[2];
} struct_T;

#endif                                 /*typedef_struct_T*/

/* Named Constants */
#define b_stepNo                       (0.0F)
#define b_showTarget                   ((signed char)-1)

/* Variable Definitions */
static float stepNo;
static float epoch[640];
static boolean_T epoch_not_empty;
static boolean_T A_not_empty;
static boolean_T B_not_empty;
static struct_T mdl;
static float buffer[1920];
static float successPerf;
static boolean_T successPerf_not_empty;
static float falsePerf;
static boolean_T falsePerf_not_empty;
static signed char showTarget;
static float X[160];
static float XX[12800];
static float count[2];
static boolean_T count_not_empty;

/* Function Declarations */
static void b_eml_xtrsm(const float A[6400], float B[80]);
static float b_erfc(float x);
static void b_sqrt(float x[2]);
static void eml_xswap(float x[6400], int ix0, int iy0);
static void eml_xtrsm(const float A[6400], float B[80]);
static void fishertrain(float features, float groups, float mdl_weights[80],
  float *mdl_threshold, float mdl_mu[2], float mdl_sigma[2]);
static void mrdivide(const float A[80], const float B[6400], float y[80]);
static float normcdf(float x, float varargin_1, float varargin_2);
static void p300process(const float eegData[640], signed char *result, int
  *learn, float *successRes, float *falseRes);
static void p300state(float c_stepNo, const unsigned char params_targets[40],
                      const unsigned char params_stimuli[960], float
                      params_nTrainTargets, float params_nTargetSteps, float
                      params_nStimuli, float params_nCycles, float
                      params_nTargets, float params_nPrestimulusCycles, unsigned
                      char *state_target, unsigned char *state_stimul, boolean_T
                      *state_learn, boolean_T *state_validate, boolean_T
                      *state_detect);
static float rt_remf(float u0, float u1);
static float rt_roundf(float u);

/* Function Definitions */

/*
 * Arguments    : const float A[6400]
 *                float B[80]
 * Return Type  : void
 */
static void b_eml_xtrsm(const float A[6400], float B[80])
{
  int j;
  int jAcol;
  int k;
  for (j = 79; j > -1; j += -1) {
    jAcol = 80 * j - 1;
    for (k = j + 2; k < 81; k++) {
      if (A[k + jAcol] != 0.0F) {
        B[j] -= A[k + jAcol] * B[k - 1];
      }
    }
  }
}

/*
 * Arguments    : float x
 * Return Type  : float
 */
static float b_erfc(float x)
{
  double absx;
  double s;
  double S;
  double R;
  int eint;

  /* ========================== COPYRIGHT NOTICE ============================ */
  /*  The algorithms for calculating ERF(X) and ERFC(X) are derived           */
  /*  from FDLIBM, which has the following notice:                            */
  /*                                                                          */
  /*  Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.       */
  /*                                                                          */
  /*  Developed at SunSoft, a Sun Microsystems, Inc. business.                */
  /*  Permission to use, copy, modify, and distribute this                    */
  /*  software is freely granted, provided that this notice                   */
  /*  is preserved.                                                           */
  /* =============================    END    ================================ */
  absx = fabs(x);
  if (absx < 0.84375) {
    if (absx < pow(2.0, -56.0)) {
      s = 1.0 - x;
    } else {
      s = (double)x * x;
      s = (0.12837916709551256 + s * (-0.3250421072470015 + s *
            (-0.02848174957559851 + s * (-0.0057702702964894416 + s *
              -2.3763016656650163E-5)))) / (1.0 + s * (0.39791722395915535 + s *
        (0.0650222499887673 + s * (0.0050813062818757656 + s *
        (0.00013249473800432164 + s * -3.9602282787753681E-6)))));
      if (x < 0.25F) {
        s = 1.0 - (x + x * s);
      } else {
        s = 0.5 - (x * s + (x - 0.5));
      }
    }
  } else if (absx < 1.25) {
    S = -0.0023621185607526594 + (absx - 1.0) * (0.41485611868374833 + (absx -
      1.0) * (-0.37220787603570132 + (absx - 1.0) * (0.31834661990116175 + (absx
      - 1.0) * (-0.11089469428239668 + (absx - 1.0) * (0.035478304325618236 +
      (absx - 1.0) * -0.0021663755948687908)))));
    s = 1.0 + (absx - 1.0) * (0.10642088040084423 + (absx - 1.0) *
      (0.540397917702171 + (absx - 1.0) * (0.071828654414196266 + (absx - 1.0) *
                                (0.12617121980876164 + (absx - 1.0) *
      (0.013637083912029051 + (absx - 1.0) * 0.011984499846799107)))));
    if (x >= 0.0F) {
      s = 0.15493708848953247 - S / s;
    } else {
      s = 1.0 + (0.84506291151046753 + S / s);
    }
  } else if (x < -6.0F) {
    s = 2.0;
  } else if (x >= 28.0F) {
    s = 0.0;
  } else {
    s = 1.0 / (absx * absx);
    if (absx < 2.8571414947509766) {
      R = -0.0098649440348471482 + s * (-0.69385857270718176 + s *
        (-10.558626225323291 + s * (-62.375332450326006 + s *
        (-162.39666946257347 + s * (-184.60509290671104 + s * (-81.2874355063066
        + s * -9.8143293441691455))))));
      S = 1.0 + s * (19.651271667439257 + s * (137.65775414351904 + s *
        (434.56587747522923 + s * (645.38727173326788 + s * (429.00814002756783
        + s * (108.63500554177944 + s * (6.5702497703192817 + s *
        -0.0604244152148581)))))));
    } else {
      R = -0.0098649429247001 + s * (-0.799283237680523 + s *
        (-17.757954917754752 + s * (-160.63638485582192 + s *
        (-637.56644336838963 + s * (-1025.0951316110772 + s * -483.5191916086514)))));
      S = 1.0 + s * (30.338060743482458 + s * (325.79251299657392 + s *
        (1536.729586084437 + s * (3199.8582195085955 + s * (2553.0504064331644 +
        s * (474.52854120695537 + s * -22.440952446585818))))));
    }

    s = frexp(absx, &eint);
    s = floor(s * 2.097152E+6) / 2.097152E+6 * pow(2.0, eint);
    s = exp(-s * s - 0.5625) * exp((s - absx) * (s + absx) + R / S) / absx;
    if (x < 0.0F) {
      s = 2.0 - s;
    }
  }

  return (float)s;
}

/*
 * Arguments    : float x[2]
 * Return Type  : void
 */
static void b_sqrt(float x[2])
{
  int k;
  for (k = 0; k < 2; k++) {
    x[k] = (real32_T)sqrt(x[k]);
  }
}

/*
 * Arguments    : float x[6400]
 *                int ix0
 *                int iy0
 * Return Type  : void
 */
static void eml_xswap(float x[6400], int ix0, int iy0)
{
  int ix;
  int iy;
  int k;
  float temp;
  ix = ix0 - 1;
  iy = iy0 - 1;
  for (k = 0; k < 80; k++) {
    temp = x[ix];
    x[ix] = x[iy];
    x[iy] = temp;
    ix += 80;
    iy += 80;
  }
}

/*
 * Arguments    : const float A[6400]
 *                float B[80]
 * Return Type  : void
 */
static void eml_xtrsm(const float A[6400], float B[80])
{
  int j;
  int jAcol;
  int k;
  for (j = 0; j < 80; j++) {
    jAcol = 80 * j;
    for (k = 0; k + 1 <= j; k++) {
      if (A[k + jAcol] != 0.0F) {
        B[j] -= A[k + jAcol] * B[k];
      }
    }

    B[j] *= 1.0F / A[j + jAcol];
  }
}

/*
 * Arguments    : float features
 *                float groups
 *                float mdl_weights[80]
 *                float *mdl_threshold
 *                float mdl_mu[2]
 *                float mdl_sigma[2]
 * Return Type  : void
 */
static void fishertrain(float features, float groups, float mdl_weights[80],
  float *mdl_threshold, float mdl_mu[2], float mdl_sigma[2])
{
  static float Z[6400];
  float tr;
  float b_mu[80];
  int k;
  int i;
  int l;
  float c_mu[2];
  float b_sigma[2];
  float stop;
  float maxPf3;
  float value;
  float pf3;

  /*  Находит веса Фишеровского классификатора */
  /*  fishertrain                                   инициализация обучения */
  /*  mdl = fishertrain(len)                        инициализация модели */
  /*  fishertrain(features,groups)                  сбор данных */
  /*  mdl = fishertrain                             вычисление весов */
  /*  mdl = fishertrain(nAverages,nGroups)          вычисление весов и порога */
  /*  mdl = fishertrain(nAverages,nGroups,mdl)      вычисление только порога */
  /*  */
  /*  вычисление весов */
  /*  вычисление среднего вектора и матрицы ковариации */
  memset(&Z[0], 0, 6400U * sizeof(float));

  /*  mdl.weights = mu'*pinv(Z); */
  /*  небольшая регуляризация Z */
  tr = 0.0F;
  for (k = 0; k < 80; k++) {
    b_mu[k] = X[80 + k] / count[1] - X[k] / count[0];
    for (i = 0; i < 2; i++) {
      for (l = 0; l < 80; l++) {
        Z[k + 80 * l] += (XX[(k + 80 * l) + 6400 * i] - X[k + 80 * i] * X[l + 80
                          * i] / count[i]) / (count[i] - 1.0F);
      }
    }

    tr += Z[k + 80 * k];
  }

  tr = 0.001F * tr / 80.0F;
  for (i = 0; i < 80; i++) {
    Z[i + 80 * i] += tr;
  }

  /*  алгоритм Фишера */
  mrdivide(b_mu, Z, mdl_weights);

  /*  вычисление оптимального порога */
  for (i = 0; i < 2; i++) {
    c_mu[i] = 0.0F;
    b_sigma[i] = 0.0F;
    for (k = 0; k < 80; k++) {
      c_mu[i] += X[k + 80 * i] / count[i] * mdl_weights[k];
      for (l = 0; l < 80; l++) {
        b_sigma[i] += (XX[(k + 80 * l) + 6400 * i] - X[k + 80 * i] * X[l + 80 *
                       i] / count[i]) / (count[i] - 1.0F) * mdl_weights[k] *
          mdl_weights[l];
      }
    }

    if (b_sigma[i] < 0.0F) {
      b_sigma[i] = 1.0F;
    }
  }

  tr = (real32_T)sqrt(features);
  b_sqrt(b_sigma);
  for (i = 0; i < 2; i++) {
    stop = b_sigma[i] / tr;
    if (stop == 0.0F) {
      stop = 0.01F;
    }

    b_sigma[i] = stop;
  }

  /*      if mu(2)<mu(1) */
  /*          fprintf(2,'Среднее значение классификатора целевого стимула меньше среднего значения классификатора нецелевого\n'); */
  /*      end */
  tr = c_mu[0] - 3.0F * b_sigma[0];
  stop = c_mu[1] + 3.0F * b_sigma[1];
  *mdl_threshold = 0.0F;
  maxPf3 = 0.0F;
  for (k = 0; k < 1001; k++) {
    value = tr + (float)k / 1000.0F * (stop - tr);

    /*  для одиночного стимула */
    /*  вероятность срабатывания нецелевого стимула */
    /*  вероятность срабатывания целевого стимула */
    /*  окончательный результат */
    pf3 = (1.0F - normcdf(value, c_mu[1], b_sigma[1])) * (real32_T)pow(1.0F -
      (1.0F - normcdf(value, c_mu[0], b_sigma[0])), groups - 1.0F);

    /*  вероятность правильного срабатывания */
    /*  максимум вероятности правильного срабатывания */
    if (pf3 > maxPf3) {
      *mdl_threshold = value;
      maxPf3 = pf3;
    } else {
      if (pf3 == maxPf3) {
        *mdl_threshold += 0.0005F * (stop - tr);
      }
    }
  }

  for (i = 0; i < 2; i++) {
    mdl_mu[i] = c_mu[i];
    mdl_sigma[i] = b_sigma[i];
  }
}

/*
 * Arguments    : const float A[80]
 *                const float B[6400]
 *                float y[80]
 * Return Type  : void
 */
static void mrdivide(const float A[80], const float B[6400], float y[80])
{
  static float b_A[6400];
  unsigned char ipiv[80];
  int i4;
  int j;
  int c;
  int jA;
  int ix;
  float temp;
  int jy;
  float s;
  int b_j;
  int ijA;
  memcpy(&b_A[0], &B[0], 6400U * sizeof(float));
  for (i4 = 0; i4 < 80; i4++) {
    ipiv[i4] = (unsigned char)(1 + i4);
  }

  for (j = 0; j < 79; j++) {
    c = j * 81;
    jA = 1;
    ix = c;
    temp = (real32_T)fabs(b_A[c]);
    for (jy = 2; jy <= 80 - j; jy++) {
      ix++;
      s = (real32_T)fabs(b_A[ix]);
      if (s > temp) {
        jA = jy;
        temp = s;
      }
    }

    if (b_A[(c + jA) - 1] != 0.0F) {
      if (jA - 1 != 0) {
        ipiv[j] = (unsigned char)(j + jA);
        eml_xswap(b_A, j + 1, j + jA);
      }

      i4 = (c - j) + 80;
      for (jA = c + 1; jA + 1 <= i4; jA++) {
        b_A[jA] /= b_A[c];
      }
    }

    jA = c;
    jy = c + 80;
    for (b_j = 1; b_j <= 79 - j; b_j++) {
      temp = b_A[jy];
      if (b_A[jy] != 0.0F) {
        ix = c + 1;
        i4 = (jA - j) + 160;
        for (ijA = 81 + jA; ijA + 1 <= i4; ijA++) {
          b_A[ijA] += b_A[ix] * -temp;
          ix++;
        }
      }

      jy += 80;
      jA += 80;
    }
  }

  memcpy(&y[0], &A[0], 80U * sizeof(float));
  eml_xtrsm(b_A, y);
  b_eml_xtrsm(b_A, y);
  for (jA = 78; jA > -1; jA += -1) {
    if (ipiv[jA] != jA + 1) {
      temp = y[jA];
      y[jA] = y[ipiv[jA] - 1];
      y[ipiv[jA] - 1] = temp;
    }
  }
}

/*
 * Arguments    : float x
 *                float varargin_1
 *                float varargin_2
 * Return Type  : float
 */
static float normcdf(float x, float varargin_1, float varargin_2)
{
  float p;
  if (varargin_2 == 0.0F) {
    if (x < varargin_1) {
      p = 0.0F;
    } else {
      p = 1.0F;
    }
  } else if (varargin_2 > 0.0F) {
    p = 0.5F * b_erfc(-((x - varargin_1) / varargin_2) / 1.41421354F);
  } else {
    p = 0.0F;
  }

  return p;
}

/*
 * Arguments    : const float eegData[640]
 *                signed char *result
 *                int *learn
 *                float *successRes
 *                float *falseRes
 * Return Type  : void
 */
static void p300process(const float eegData[640], signed char *result, int
  *learn, float *successRes, float *falseRes)
{
  static float features[80];
  int iy;
  int ixstart;
  float s;
  int k;
  float y[5];
  int j;
  int ix;
  static float a[80];
  float cv[5];
  boolean_T state_detect;
  boolean_T state_validate;
  boolean_T state_learn;
  unsigned char state_stimul;
  unsigned char state_target;
  static unsigned char t1_stimuli[960] = { 3U, 1U, 2U, 4U, 1U, 3U, 2U, 4U, 3U,
    2U, 4U, 1U, 2U, 3U, 4U, 1U, 2U, 4U, 1U, 3U, 2U, 4U, 3U, 1U, 4U, 3U, 1U, 2U,
    4U, 1U, 2U, 3U, 4U, 1U, 3U, 2U, 4U, 3U, 1U, 2U, 3U, 4U, 2U, 1U, 4U, 2U, 1U,
    3U, 2U, 1U, 3U, 4U, 1U, 2U, 3U, 4U, 1U, 2U, 4U, 3U, 1U, 4U, 2U, 3U, 1U, 2U,
    3U, 4U, 1U, 3U, 2U, 4U, 3U, 1U, 4U, 2U, 3U, 4U, 1U, 2U, 3U, 4U, 2U, 1U, 4U,
    3U, 1U, 2U, 3U, 4U, 2U, 1U, 4U, 3U, 1U, 2U, 3U, 4U, 2U, 1U, 4U, 2U, 1U, 3U,
    4U, 1U, 3U, 2U, 1U, 3U, 4U, 2U, 3U, 1U, 2U, 4U, 3U, 2U, 4U, 1U, 2U, 3U, 1U,
    4U, 2U, 1U, 4U, 3U, 1U, 2U, 3U, 4U, 1U, 3U, 4U, 2U, 1U, 3U, 2U, 4U, 1U, 2U,
    3U, 4U, 1U, 2U, 4U, 3U, 2U, 4U, 1U, 3U, 4U, 2U, 1U, 3U, 4U, 2U, 3U, 1U, 2U,
    4U, 1U, 3U, 4U, 2U, 3U, 1U, 4U, 2U, 1U, 3U, 2U, 1U, 4U, 3U, 2U, 1U, 3U, 4U,
    1U, 2U, 4U, 3U, 2U, 4U, 1U, 3U, 4U, 1U, 2U, 3U, 4U, 2U, 1U, 3U, 4U, 2U, 3U,
    1U, 2U, 4U, 1U, 3U, 2U, 1U, 3U, 4U, 2U, 3U, 4U, 1U, 2U, 4U, 3U, 1U, 2U, 3U,
    4U, 1U, 3U, 4U, 2U, 1U, 4U, 3U, 2U, 1U, 3U, 2U, 1U, 4U, 2U, 3U, 4U, 1U, 3U,
    4U, 1U, 2U, 4U, 3U, 1U, 2U, 4U, 3U, 2U, 1U, 3U, 2U, 4U, 1U, 3U, 4U, 2U, 1U,
    4U, 3U, 2U, 1U, 3U, 2U, 1U, 4U, 3U, 1U, 4U, 2U, 3U, 4U, 1U, 2U, 4U, 3U, 2U,
    1U, 4U, 2U, 3U, 1U, 4U, 2U, 1U, 3U, 4U, 1U, 2U, 3U, 1U, 4U, 2U, 3U, 4U, 1U,
    3U, 2U, 1U, 4U, 2U, 3U, 1U, 4U, 3U, 2U, 1U, 4U, 2U, 3U, 1U, 4U, 3U, 2U, 1U,
    3U, 2U, 4U, 3U, 1U, 2U, 4U, 3U, 1U, 4U, 2U, 3U, 4U, 1U, 2U, 3U, 1U, 2U, 4U,
    1U, 3U, 2U, 4U, 3U, 1U, 2U, 4U, 1U, 3U, 2U, 4U, 1U, 2U, 3U, 4U, 2U, 3U, 1U,
    4U, 3U, 1U, 2U, 4U, 3U, 2U, 4U, 1U, 2U, 4U, 3U, 1U, 4U, 2U, 3U, 1U, 2U, 4U,
    3U, 1U, 2U, 3U, 1U, 4U, 3U, 2U, 1U, 4U, 2U, 1U, 3U, 4U, 1U, 2U, 4U, 3U, 1U,
    4U, 2U, 3U, 1U, 2U, 3U, 4U, 1U, 2U, 4U, 3U, 1U, 4U, 2U, 3U, 4U, 1U, 2U, 3U,
    4U, 1U, 3U, 2U, 1U, 3U, 4U, 2U, 3U, 1U, 2U, 4U, 3U, 2U, 4U, 1U, 2U, 4U, 3U,
    1U, 4U, 3U, 2U, 1U, 3U, 2U, 4U, 1U, 3U, 4U, 1U, 2U, 3U, 4U, 2U, 1U, 4U, 3U,
    2U, 1U, 3U, 4U, 2U, 1U, 4U, 2U, 1U, 3U, 4U, 2U, 3U, 1U, 2U, 3U, 4U, 1U, 3U,
    2U, 1U, 4U, 3U, 1U, 4U, 2U, 1U, 4U, 2U, 3U, 4U, 1U, 3U, 2U, 4U, 3U, 2U, 1U,
    3U, 4U, 1U, 2U, 4U, 1U, 2U, 3U, 1U, 2U, 3U, 4U, 2U, 1U, 4U, 3U, 1U, 2U, 3U,
    4U, 1U, 3U, 4U, 2U, 3U, 4U, 1U, 2U, 4U, 1U, 3U, 2U, 4U, 3U, 2U, 1U, 3U, 4U,
    2U, 1U, 4U, 3U, 1U, 2U, 4U, 1U, 2U, 3U, 1U, 2U, 4U, 3U, 2U, 1U, 3U, 4U, 1U,
    3U, 4U, 2U, 1U, 4U, 3U, 2U, 1U, 4U, 2U, 3U, 1U, 2U, 4U, 3U, 2U, 4U, 3U, 1U,
    2U, 4U, 1U, 3U, 4U, 1U, 3U, 2U, 4U, 1U, 2U, 3U, 1U, 4U, 2U, 3U, 1U, 2U, 4U,
    3U, 2U, 4U, 1U, 3U, 4U, 2U, 3U, 1U, 2U, 4U, 3U, 1U, 4U, 2U, 3U, 1U, 4U, 2U,
    1U, 3U, 4U, 2U, 3U, 1U, 2U, 3U, 1U, 4U, 2U, 1U, 4U, 3U, 2U, 4U, 3U, 1U, 4U,
    3U, 1U, 2U, 4U, 3U, 2U, 1U, 3U, 2U, 4U, 1U, 2U, 4U, 1U, 3U, 2U, 4U, 3U, 1U,
    2U, 4U, 1U, 3U, 4U, 2U, 1U, 3U, 4U, 2U, 3U, 1U, 4U, 2U, 1U, 3U, 4U, 1U, 3U,
    2U, 1U, 4U, 3U, 2U, 1U, 3U, 2U, 4U, 3U, 1U, 4U, 2U, 1U, 3U, 2U, 4U, 3U, 1U,
    4U, 2U, 1U, 3U, 4U, 2U, 3U, 1U, 2U, 4U, 3U, 1U, 4U, 2U, 1U, 4U, 2U, 3U, 4U,
    2U, 3U, 1U, 2U, 4U, 1U, 3U, 4U, 2U, 3U, 1U, 2U, 4U, 3U, 1U, 4U, 2U, 1U, 3U,
    2U, 1U, 4U, 3U, 2U, 4U, 1U, 3U, 4U, 1U, 2U, 3U, 1U, 2U, 3U, 4U, 1U, 3U, 2U,
    4U, 1U, 2U, 4U, 3U, 1U, 4U, 2U, 3U, 4U, 1U, 3U, 2U, 1U, 3U, 2U, 4U, 3U, 2U,
    1U, 4U, 2U, 3U, 4U, 1U, 3U, 4U, 2U, 1U, 4U, 3U, 2U, 1U, 3U, 2U, 1U, 4U, 3U,
    1U, 2U, 4U, 1U, 2U, 4U, 3U, 1U, 2U, 3U, 4U, 1U, 3U, 2U, 4U, 3U, 2U, 1U, 4U,
    2U, 1U, 4U, 3U, 1U, 2U, 4U, 3U, 1U, 4U, 3U, 2U, 4U, 1U, 3U, 2U, 4U, 1U, 2U,
    3U, 1U, 2U, 3U, 4U, 2U, 1U, 3U, 4U, 2U, 3U, 1U, 4U, 2U, 1U, 3U, 4U, 2U, 1U,
    4U, 3U, 2U, 4U, 1U, 3U, 2U, 1U, 4U, 3U, 1U, 2U, 4U, 3U, 1U, 2U, 3U, 4U, 2U,
    1U, 3U, 4U, 1U, 3U, 4U, 2U, 1U, 4U, 2U, 3U, 4U, 1U, 2U, 3U, 4U, 1U, 3U, 2U,
    4U, 3U, 2U, 1U, 4U, 3U, 1U, 2U, 4U, 1U, 3U, 2U, 4U, 3U, 2U, 1U, 3U, 2U, 4U,
    1U, 2U, 3U, 1U, 4U, 2U, 1U, 4U, 3U, 2U, 1U, 3U, 4U, 1U, 3U, 4U, 2U, 3U, 1U,
    2U, 4U, 1U, 2U, 4U, 3U, 2U, 1U, 3U, 4U, 1U, 2U, 4U, 3U, 1U, 4U, 2U, 3U, 1U,
    4U, 3U, 2U, 4U, 3U, 1U, 2U, 4U, 3U, 2U, 1U, 4U, 2U, 1U, 3U, 2U, 4U, 1U, 3U,
    4U, 1U, 3U, 2U, 1U, 3U, 4U, 2U, 1U, 4U, 2U, 3U, 1U, 2U, 3U, 4U, 1U, 2U, 4U,
    3U };

  static unsigned char t1_targets[40] = { 3U, 1U, 2U, 4U, 1U, 3U, 2U, 4U, 3U, 2U,
    4U, 1U, 2U, 3U, 4U, 1U, 2U, 4U, 1U, 3U, 2U, 4U, 3U, 1U, 4U, 3U, 1U, 2U, 4U,
    1U, 2U, 3U, 4U, 1U, 3U, 2U, 4U, 3U, 1U, 2U };

  boolean_T groups;
  boolean_T guard1 = false;
  boolean_T x[2];
  boolean_T b_y;
  boolean_T exitg1;
  float b_s;
  static float c_y[320];
  static float d_y[320];
  float values[4];

  /*  result    номер детектированого стимула или 0 */
  /*  learn     если проводилось обучение, то количество сэмплов, или 0 */
  /*  successRes проценты правильных детектирований (после второго обучения) */
  /*  falseRes   проценты ложных детектирований (после второго обучения) */
  /*  вычисление фич */
  for (iy = 0; iy < 5; iy++) {
    for (ixstart = 0; ixstart < 16; ixstart++) {
      s = eegData[iy + 5 * (ixstart << 3)];
      for (k = 0; k < 7; k++) {
        s += eegData[iy + 5 * ((k + (ixstart << 3)) + 1)];
      }

      features[iy + 5 * ixstart] = s / 8.0F;
    }
  }

  iy = -1;
  ixstart = -1;
  for (j = 0; j < 5; j++) {
    ixstart++;
    ix = ixstart;
    s = features[ixstart];
    for (k = 0; k < 15; k++) {
      ix += 5;
      s += features[ix];
    }

    iy++;
    y[iy] = s;
  }

  for (iy = 0; iy < 5; iy++) {
    y[iy] /= 16.0F;
  }

  memcpy(&a[0], &features[0], 80U * sizeof(float));
  iy = 0;
  for (ixstart = 0; ixstart < 77; ixstart += 5) {
    for (k = 0; k < 5; k++) {
      cv[k] = a[iy + k] - y[k];
    }

    for (k = 0; k < 5; k++) {
      features[ixstart + k] = cv[k];
    }

    iy += 5;
  }

  /*  счетчик шагов */
  if ((stepNo == 0.0F) || (!falsePerf_not_empty) || (!successPerf_not_empty)) {
    stepNo = 0.0F;
    successPerf = 0.0F;
    successPerf_not_empty = true;
    falsePerf = 0.0F;
    falsePerf_not_empty = true;
    showTarget = -1;
    memset(&buffer[0], 0, 1920U * sizeof(float));

    /*  Находит веса Фишеровского классификатора */
    /*  fishertrain                                   инициализация обучения */
    /*  mdl = fishertrain(len)                        инициализация модели */
    /*  fishertrain(features,groups)                  сбор данных */
    /*  mdl = fishertrain                             вычисление весов */
    /*  mdl = fishertrain(nAverages,nGroups)          вычисление весов и порога */
    /*  mdl = fishertrain(nAverages,nGroups,mdl)      вычисление только порога */
    /*  */
    for (iy = 0; iy < 2; iy++) {
      count[iy] = 0.0F;
    }

    count_not_empty = true;
    for (iy = 0; iy < 80; iy++) {
      mdl.weights[iy] = 0.0F;
    }

    mdl.threshold = 0.0F;
    for (iy = 0; iy < 2; iy++) {
      mdl.mu[iy] = 0.0F;
      mdl.sigma[iy] = 0.0F;
    }
  }

  stepNo++;
  p300state(stepNo - 4.0F, t1_targets, t1_stimuli, 27.0F, 44.0F, 4.0F, 6.0F,
            40.0F, 5.0F, &state_target, &state_stimul, &state_learn,
            &state_validate, &state_detect);

  /*  сбор данных для обучения */
  if ((state_target != 0) && (state_stimul != 0)) {
    groups = (state_target == state_stimul);

    /*  Находит веса Фишеровского классификатора */
    /*  fishertrain                                   инициализация обучения */
    /*  mdl = fishertrain(len)                        инициализация модели */
    /*  fishertrain(features,groups)                  сбор данных */
    /*  mdl = fishertrain                             вычисление весов */
    /*  mdl = fishertrain(nAverages,nGroups)          вычисление весов и порога */
    /*  mdl = fishertrain(nAverages,nGroups,mdl)      вычисление только порога */
    /*  */
    /*  суммирование данных */
    guard1 = false;
    if (!count_not_empty) {
      guard1 = true;
    } else {
      for (iy = 0; iy < 2; iy++) {
        x[iy] = (count[iy] == 0.0F);
      }

      b_y = true;
      k = 0;
      exitg1 = false;
      while ((!exitg1) && (k < 2)) {
        if (x[k] == 0) {
          b_y = false;
          exitg1 = true;
        } else {
          k++;
        }
      }

      if (b_y) {
        guard1 = true;
      }
    }

    if (guard1) {
      /*  инициализирует начало обучения */
      memset(&X[0], 0, 160U * sizeof(float));
      memset(&XX[0], 0, 12800U * sizeof(float));
      for (iy = 0; iy < 2; iy++) {
        count[iy] = 0.0F;
      }

      count_not_empty = true;
    }

    count[(int)groups]++;
    for (k = 0; k < 80; k++) {
      X[k + 80 * groups] += features[k];
      for (iy = 0; iy < 80; iy++) {
        XX[(k + 80 * iy) + 6400 * groups] += features[k] * features[iy];
      }
    }
  }

  /*  добавление данных в кольцевой буффер */
  if (state_stimul != 0) {
    s = ((stepNo - 4.0F) - 1.0F) / 4.0F;
    if (s < 0.0F) {
      b_s = (real32_T)ceil(s);
    } else {
      b_s = (real32_T)floor(s);
    }

    iy = (int)(1.0F + rt_remf(b_s, 6.0F));
    memcpy(&buffer[80 * (state_stimul - 1) + 320 * (iy - 1)], &features[0], 80U *
           sizeof(float));
  }

  /*  классификация */
  *result = -1;
  if (state_validate || state_detect) {
    iy = -1;
    ixstart = -1;
    for (j = 0; j < 320; j++) {
      ixstart++;
      ix = ixstart;
      s = buffer[ixstart];
      for (k = 0; k < 5; k++) {
        ix += 320;
        s += buffer[ix];
      }

      iy++;
      c_y[iy] = s;
    }

    for (iy = 0; iy < 4; iy++) {
      for (ixstart = 0; ixstart < 80; ixstart++) {
        d_y[ixstart + 80 * iy] = c_y[ixstart + 80 * iy] / 6.0F;
      }

      values[iy] = 0.0F;
      for (ixstart = 0; ixstart < 80; ixstart++) {
        values[iy] += mdl.weights[ixstart] * d_y[ixstart + 80 * iy];
      }
    }

    s = values[0];
    iy = -1;
    for (ix = 0; ix < 3; ix++) {
      if (values[ix + 1] > s) {
        s = values[ix + 1];
        iy = ix;
      }
    }

    *result = (signed char)(iy + 2);
    if (s <= mdl.threshold) {
      *result = 0;

      /*  если ни один не определился */
    } else {
      for (iy = 0; iy < 4; iy++) {
        values[iy] = (float)(values[iy] > mdl.threshold);
      }

      s = values[0];
      for (k = 0; k < 3; k++) {
        s += values[k + 1];
      }

      if (s > 1.0F) {
        *result = 5;

        /*  если определилось слишком много */
      }
    }

    if (state_detect) {
      showTarget = *result;
    }
  }

  /*  валидация */
  if (state_validate && (*result >= 1) && (*result <= 4)) {
    if (*result == state_target) {
      successPerf += 7.69230747F;
    } else {
      falsePerf += 7.69230747F;
    }
  }

  /*  вычисление модели */
  *learn = (int)rt_roundf((stepNo - 1.0F) * 32.0F * (float)state_learn);
  if (state_learn) {
    fishertrain(6.0F, 4.0F, mdl.weights, &mdl.threshold, mdl.mu, mdl.sigma);
  }

  *successRes = successPerf;
  *falseRes = falsePerf;
}

/*
 * Arguments    : float c_stepNo
 *                const unsigned char params_targets[40]
 *                const unsigned char params_stimuli[960]
 *                float params_nTrainTargets
 *                float params_nTargetSteps
 *                float params_nStimuli
 *                float params_nCycles
 *                float params_nTargets
 *                float params_nPrestimulusCycles
 *                unsigned char *state_target
 *                unsigned char *state_stimul
 *                boolean_T *state_learn
 *                boolean_T *state_validate
 *                boolean_T *state_detect
 * Return Type  : void
 */
static void p300state(float c_stepNo, const unsigned char params_targets[40],
                      const unsigned char params_stimuli[960], float
                      params_nTrainTargets, float params_nTargetSteps, float
                      params_nStimuli, float params_nCycles, float
                      params_nTargets, float params_nPrestimulusCycles, unsigned
                      char *state_target, unsigned char *state_stimul, boolean_T
                      *state_learn, boolean_T *state_validate, boolean_T
                      *state_detect)
{
  float y;
  float stimulNo;
  float targetStepNo;

  /*  определяет состояние state по номеру шага stepNo */
  /*  нулевой момент времени - stepNo == 1 */
  *state_target = 0;

  /*  цель для обучения */
  *state_stimul = 0;

  /*  текущий показываемый стимул */
  *state_learn = false;

  /*  вычислять модель */
  *state_validate = false;

  /*  выполнять валидацию */
  *state_detect = false;

  /*  проводить детектирование */
  if (c_stepNo < 1.0F) {
  } else {
    y = (c_stepNo - 1.0F) / params_nTargetSteps;
    if (y < 0.0F) {
      y = (real32_T)ceil(y);
    } else {
      y = (real32_T)floor(y);
    }

    stimulNo = 0.0F;
    if ((1.0F + y >= 1.0F) && (1.0F + y <= params_nTargets)) {
      *state_target = params_targets[(int)(1.0F + y) - 1];
      targetStepNo = c_stepNo - ((1.0F + y) - 1.0F) * params_nTargetSteps;
      if (targetStepNo > params_nPrestimulusCycles * params_nStimuli) {
        stimulNo = (targetStepNo - params_nPrestimulusCycles * params_nStimuli)
          + ((1.0F + y) - 1.0F) * params_nCycles * params_nStimuli;
        *state_stimul = params_stimuli[(int)stimulNo - 1];
      }
    } else {
      stimulNo = 1.0F + rt_remf((c_stepNo - 1.0F) - params_nTargets *
        params_nTargetSteps, 960.0F);
      *state_stimul = params_stimuli[(int)(1.0F + rt_remf((c_stepNo - 1.0F) -
        params_nTargets * params_nTargetSteps, 960.0F)) - 1];
    }

    if ((stimulNo != 0.0F) && (rt_remf(stimulNo, params_nStimuli) == 0.0F) &&
        (c_stepNo > params_nTargets * params_nTargetSteps + (params_nCycles -
          1.0F) * params_nStimuli)) {
      *state_detect = true;
    }

    if (c_stepNo == params_nTrainTargets * params_nTargetSteps) {
      *state_learn = true;

      /*  для валидации */
    } else {
      if (c_stepNo == params_nTargets * params_nTargetSteps) {
        *state_learn = true;

        /*  основная модель */
      }
    }

    if ((1.0F + y <= params_nTargets) && (1.0F + y > params_nTrainTargets) &&
        (c_stepNo == (1.0F + y) * params_nTargetSteps)) {
      *state_validate = true;
    }
  }
}

/*
 * Arguments    : float u0
 *                float u1
 * Return Type  : float
 */
static float rt_remf(float u0, float u1)
{
  float y;
  float b_u1;
  float tr;
  if (u1 < 0.0F) {
    b_u1 = (real32_T)ceil(u1);
  } else {
    b_u1 = (real32_T)floor(u1);
  }

  if ((u1 != 0.0F) && (u1 != b_u1)) {
    tr = u0 / u1;
    if ((real32_T)fabs(tr - rt_roundf(tr)) <= FLT_EPSILON * (real32_T)fabs(tr))
    {
      y = 0.0F;
    } else {
      y = (real32_T)fmod(u0, u1);
    }
  } else {
    y = (real32_T)fmod(u0, u1);
  }

  return y;
}

/*
 * Arguments    : float u
 * Return Type  : float
 */
static float rt_roundf(float u)
{
  float y;
  if ((real32_T)fabs(u) < 8.388608E+6F) {
    if (u >= 0.5F) {
      y = (real32_T)floor(u + 0.5F);
    } else if (u > -0.5F) {
      y = 0.0F;
    } else {
      y = (real32_T)ceil(u - 0.5F);
    }
  } else {
    y = u;
  }

  return y;
}

/*
 * Arguments    : int t
 *                int data[5]
 * Return Type  : void
 */
void p300generate(int t, int data[5])
{
  int i;
  float b_t;
  boolean_T expl_temp;
  boolean_T b_expl_temp;
  boolean_T c_expl_temp;
  unsigned char state_stimul;
  unsigned char state_target;
  static unsigned char t2_stimuli[960] = { 3U, 1U, 2U, 4U, 1U, 3U, 2U, 4U, 3U,
    2U, 4U, 1U, 2U, 3U, 4U, 1U, 2U, 4U, 1U, 3U, 2U, 4U, 3U, 1U, 4U, 3U, 1U, 2U,
    4U, 1U, 2U, 3U, 4U, 1U, 3U, 2U, 4U, 3U, 1U, 2U, 3U, 4U, 2U, 1U, 4U, 2U, 1U,
    3U, 2U, 1U, 3U, 4U, 1U, 2U, 3U, 4U, 1U, 2U, 4U, 3U, 1U, 4U, 2U, 3U, 1U, 2U,
    3U, 4U, 1U, 3U, 2U, 4U, 3U, 1U, 4U, 2U, 3U, 4U, 1U, 2U, 3U, 4U, 2U, 1U, 4U,
    3U, 1U, 2U, 3U, 4U, 2U, 1U, 4U, 3U, 1U, 2U, 3U, 4U, 2U, 1U, 4U, 2U, 1U, 3U,
    4U, 1U, 3U, 2U, 1U, 3U, 4U, 2U, 3U, 1U, 2U, 4U, 3U, 2U, 4U, 1U, 2U, 3U, 1U,
    4U, 2U, 1U, 4U, 3U, 1U, 2U, 3U, 4U, 1U, 3U, 4U, 2U, 1U, 3U, 2U, 4U, 1U, 2U,
    3U, 4U, 1U, 2U, 4U, 3U, 2U, 4U, 1U, 3U, 4U, 2U, 1U, 3U, 4U, 2U, 3U, 1U, 2U,
    4U, 1U, 3U, 4U, 2U, 3U, 1U, 4U, 2U, 1U, 3U, 2U, 1U, 4U, 3U, 2U, 1U, 3U, 4U,
    1U, 2U, 4U, 3U, 2U, 4U, 1U, 3U, 4U, 1U, 2U, 3U, 4U, 2U, 1U, 3U, 4U, 2U, 3U,
    1U, 2U, 4U, 1U, 3U, 2U, 1U, 3U, 4U, 2U, 3U, 4U, 1U, 2U, 4U, 3U, 1U, 2U, 3U,
    4U, 1U, 3U, 4U, 2U, 1U, 4U, 3U, 2U, 1U, 3U, 2U, 1U, 4U, 2U, 3U, 4U, 1U, 3U,
    4U, 1U, 2U, 4U, 3U, 1U, 2U, 4U, 3U, 2U, 1U, 3U, 2U, 4U, 1U, 3U, 4U, 2U, 1U,
    4U, 3U, 2U, 1U, 3U, 2U, 1U, 4U, 3U, 1U, 4U, 2U, 3U, 4U, 1U, 2U, 4U, 3U, 2U,
    1U, 4U, 2U, 3U, 1U, 4U, 2U, 1U, 3U, 4U, 1U, 2U, 3U, 1U, 4U, 2U, 3U, 4U, 1U,
    3U, 2U, 1U, 4U, 2U, 3U, 1U, 4U, 3U, 2U, 1U, 4U, 2U, 3U, 1U, 4U, 3U, 2U, 1U,
    3U, 2U, 4U, 3U, 1U, 2U, 4U, 3U, 1U, 4U, 2U, 3U, 4U, 1U, 2U, 3U, 1U, 2U, 4U,
    1U, 3U, 2U, 4U, 3U, 1U, 2U, 4U, 1U, 3U, 2U, 4U, 1U, 2U, 3U, 4U, 2U, 3U, 1U,
    4U, 3U, 1U, 2U, 4U, 3U, 2U, 4U, 1U, 2U, 4U, 3U, 1U, 4U, 2U, 3U, 1U, 2U, 4U,
    3U, 1U, 2U, 3U, 1U, 4U, 3U, 2U, 1U, 4U, 2U, 1U, 3U, 4U, 1U, 2U, 4U, 3U, 1U,
    4U, 2U, 3U, 1U, 2U, 3U, 4U, 1U, 2U, 4U, 3U, 1U, 4U, 2U, 3U, 4U, 1U, 2U, 3U,
    4U, 1U, 3U, 2U, 1U, 3U, 4U, 2U, 3U, 1U, 2U, 4U, 3U, 2U, 4U, 1U, 2U, 4U, 3U,
    1U, 4U, 3U, 2U, 1U, 3U, 2U, 4U, 1U, 3U, 4U, 1U, 2U, 3U, 4U, 2U, 1U, 4U, 3U,
    2U, 1U, 3U, 4U, 2U, 1U, 4U, 2U, 1U, 3U, 4U, 2U, 3U, 1U, 2U, 3U, 4U, 1U, 3U,
    2U, 1U, 4U, 3U, 1U, 4U, 2U, 1U, 4U, 2U, 3U, 4U, 1U, 3U, 2U, 4U, 3U, 2U, 1U,
    3U, 4U, 1U, 2U, 4U, 1U, 2U, 3U, 1U, 2U, 3U, 4U, 2U, 1U, 4U, 3U, 1U, 2U, 3U,
    4U, 1U, 3U, 4U, 2U, 3U, 4U, 1U, 2U, 4U, 1U, 3U, 2U, 4U, 3U, 2U, 1U, 3U, 4U,
    2U, 1U, 4U, 3U, 1U, 2U, 4U, 1U, 2U, 3U, 1U, 2U, 4U, 3U, 2U, 1U, 3U, 4U, 1U,
    3U, 4U, 2U, 1U, 4U, 3U, 2U, 1U, 4U, 2U, 3U, 1U, 2U, 4U, 3U, 2U, 4U, 3U, 1U,
    2U, 4U, 1U, 3U, 4U, 1U, 3U, 2U, 4U, 1U, 2U, 3U, 1U, 4U, 2U, 3U, 1U, 2U, 4U,
    3U, 2U, 4U, 1U, 3U, 4U, 2U, 3U, 1U, 2U, 4U, 3U, 1U, 4U, 2U, 3U, 1U, 4U, 2U,
    1U, 3U, 4U, 2U, 3U, 1U, 2U, 3U, 1U, 4U, 2U, 1U, 4U, 3U, 2U, 4U, 3U, 1U, 4U,
    3U, 1U, 2U, 4U, 3U, 2U, 1U, 3U, 2U, 4U, 1U, 2U, 4U, 1U, 3U, 2U, 4U, 3U, 1U,
    2U, 4U, 1U, 3U, 4U, 2U, 1U, 3U, 4U, 2U, 3U, 1U, 4U, 2U, 1U, 3U, 4U, 1U, 3U,
    2U, 1U, 4U, 3U, 2U, 1U, 3U, 2U, 4U, 3U, 1U, 4U, 2U, 1U, 3U, 2U, 4U, 3U, 1U,
    4U, 2U, 1U, 3U, 4U, 2U, 3U, 1U, 2U, 4U, 3U, 1U, 4U, 2U, 1U, 4U, 2U, 3U, 4U,
    2U, 3U, 1U, 2U, 4U, 1U, 3U, 4U, 2U, 3U, 1U, 2U, 4U, 3U, 1U, 4U, 2U, 1U, 3U,
    2U, 1U, 4U, 3U, 2U, 4U, 1U, 3U, 4U, 1U, 2U, 3U, 1U, 2U, 3U, 4U, 1U, 3U, 2U,
    4U, 1U, 2U, 4U, 3U, 1U, 4U, 2U, 3U, 4U, 1U, 3U, 2U, 1U, 3U, 2U, 4U, 3U, 2U,
    1U, 4U, 2U, 3U, 4U, 1U, 3U, 4U, 2U, 1U, 4U, 3U, 2U, 1U, 3U, 2U, 1U, 4U, 3U,
    1U, 2U, 4U, 1U, 2U, 4U, 3U, 1U, 2U, 3U, 4U, 1U, 3U, 2U, 4U, 3U, 2U, 1U, 4U,
    2U, 1U, 4U, 3U, 1U, 2U, 4U, 3U, 1U, 4U, 3U, 2U, 4U, 1U, 3U, 2U, 4U, 1U, 2U,
    3U, 1U, 2U, 3U, 4U, 2U, 1U, 3U, 4U, 2U, 3U, 1U, 4U, 2U, 1U, 3U, 4U, 2U, 1U,
    4U, 3U, 2U, 4U, 1U, 3U, 2U, 1U, 4U, 3U, 1U, 2U, 4U, 3U, 1U, 2U, 3U, 4U, 2U,
    1U, 3U, 4U, 1U, 3U, 4U, 2U, 1U, 4U, 2U, 3U, 4U, 1U, 2U, 3U, 4U, 1U, 3U, 2U,
    4U, 3U, 2U, 1U, 4U, 3U, 1U, 2U, 4U, 1U, 3U, 2U, 4U, 3U, 2U, 1U, 3U, 2U, 4U,
    1U, 2U, 3U, 1U, 4U, 2U, 1U, 4U, 3U, 2U, 1U, 3U, 4U, 1U, 3U, 4U, 2U, 3U, 1U,
    2U, 4U, 1U, 2U, 4U, 3U, 2U, 1U, 3U, 4U, 1U, 2U, 4U, 3U, 1U, 4U, 2U, 3U, 1U,
    4U, 3U, 2U, 4U, 3U, 1U, 2U, 4U, 3U, 2U, 1U, 4U, 2U, 1U, 3U, 2U, 4U, 1U, 3U,
    4U, 1U, 3U, 2U, 1U, 3U, 4U, 2U, 1U, 4U, 2U, 3U, 1U, 2U, 3U, 4U, 1U, 2U, 4U,
    3U };

  static unsigned char t2_targets[40] = { 3U, 1U, 2U, 4U, 1U, 3U, 2U, 4U, 3U, 2U,
    4U, 1U, 2U, 3U, 4U, 1U, 2U, 4U, 1U, 3U, 2U, 4U, 3U, 1U, 4U, 3U, 1U, 2U, 4U,
    1U, 2U, 3U, 4U, 1U, 3U, 2U, 4U, 3U, 1U, 2U };

  /*  Генерация тестовых данных */
  /*    t - номер сэмпла тестовой последовательности */
  /*    data - показания 5-ти электродов */
  for (i = 0; i < 5; i++) {
    data[i] = 0;
  }

  if (t < 1) {
  } else {
    b_t = (real32_T)floor(((float)t - 1.0F) / 32.0F);
    p300state(1.0F + b_t, t2_targets, t2_stimuli, 27.0F, 44.0F, 4.0F, 6.0F,
              40.0F, 5.0F, &state_target, &state_stimul, &c_expl_temp,
              &b_expl_temp, &expl_temp);
    if (!(state_target != 0)) {
      state_target = 1;
    }

    if ((state_stimul != 0) && (state_target == state_stimul)) {
      b_t = ((float)t - ((1.0F + b_t) - 1.0F) * 32.0F) - 1.0F;
      for (i = 0; i < 5; i++) {
        data[i] += (int)rt_roundf(1000.0F * (real32_T)sin(b_t * 2.0F *
          3.14159274F / 32.0F * ((1.0F + (float)i) + 1.0F)));
      }
    }
  }
}

/*
 * Arguments    : boolean_T learn
 * Return Type  : boolean_T
 */
boolean_T p300init(boolean_T learn)
{
  boolean_T success;

  /*  инициализирует счетчик */
  /*  */
  /*  инициализирует счетчик */
  /*  */
  success = true;
  if (learn) {
    stepNo = 0.0F;
  } else if (stepNo * 32.0F < 56416.0F) {
    success = false;
  } else {
    stepNo = 1760.0F;
  }

  return success;
}

/*
 * Arguments    : unsigned char patterns[256]
 * Return Type  : void
 */
void p300patterns(unsigned char patterns[256])
{
  int i0;
  int i1;
  static const unsigned char y[64] = { 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 4U,
    4U, 0U, 0U, 4U, 4U, 0U, 0U, 4U, 4U, 0U, 0U, 4U, 4U, 0U, 0U, 0U, 0U, 0U, 0U,
    0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 4U, 4U, 0U, 0U, 4U, 4U, 0U,
    0U, 4U, 4U, 0U, 0U, 4U, 4U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U };

  static const unsigned char uv0[64] = { 3U, 3U, 3U, 3U, 3U, 3U, 3U, 3U, 3U, 4U,
    4U, 3U, 3U, 4U, 4U, 3U, 3U, 4U, 4U, 3U, 3U, 4U, 4U, 3U, 3U, 3U, 3U, 3U, 3U,
    3U, 3U, 3U, 3U, 3U, 3U, 3U, 3U, 3U, 3U, 3U, 3U, 4U, 4U, 3U, 3U, 4U, 4U, 3U,
    3U, 4U, 4U, 3U, 3U, 4U, 4U, 3U, 3U, 3U, 3U, 3U, 3U, 3U, 3U, 3U };

  static const unsigned char b_y[64] = { 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 2U,
    2U, 0U, 0U, 2U, 2U, 0U, 0U, 2U, 2U, 0U, 0U, 2U, 2U, 0U, 0U, 0U, 0U, 0U, 0U,
    0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 2U, 2U, 0U, 0U, 2U, 2U, 0U,
    0U, 2U, 2U, 0U, 0U, 2U, 2U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U };

  static const unsigned char uv1[64] = { 3U, 3U, 3U, 3U, 3U, 3U, 3U, 3U, 3U, 2U,
    2U, 3U, 3U, 2U, 2U, 3U, 3U, 2U, 2U, 3U, 3U, 2U, 2U, 3U, 3U, 3U, 3U, 3U, 3U,
    3U, 3U, 3U, 3U, 3U, 3U, 3U, 3U, 3U, 3U, 3U, 3U, 2U, 2U, 3U, 3U, 2U, 2U, 3U,
    3U, 2U, 2U, 3U, 3U, 2U, 2U, 3U, 3U, 3U, 3U, 3U, 3U, 3U, 3U, 3U };

  for (i0 = 0; i0 < 8; i0++) {
    for (i1 = 0; i1 < 8; i1++) {
      patterns[i1 + (i0 << 3)] = y[i1 + (i0 << 3)];
      patterns[64 + (i1 + (i0 << 3))] = uv0[i1 + (i0 << 3)];
      patterns[128 + (i1 + (i0 << 3))] = b_y[i1 + (i0 << 3)];
      patterns[192 + (i1 + (i0 << 3))] = uv1[i1 + (i0 << 3)];
    }
  }
}

/*
 * Arguments    : const int eegData[256]
 *                signed char *result
 *                int *learn
 *                float *successRes
 *                float *falseRes
 * Return Type  : void
 */
void p300run(const int eegData[256], signed char *result, int *learn, float
             *successRes, float *falseRes)
{
  float unusedU3;
  float unusedU2;
  int stride;
  signed char unusedU0;
  float atmp[32];
  int dim;
  int i2;
  int pagesize;
  int i;
  int pageroot;
  int j;
  int i1;
  static const boolean_T bv0[2] = { true, false };

  int k;
  int i3;

  /*  eegData - массив [8,params.nStepSamples] одного шага данных. Из этого */
  /*  массива выбираются строки 3:7. Несколько шагов стыкуются вместе, */
  /*  фильтруются и передаются в функцию process. */
  if ((!epoch_not_empty) || (!(stepNo != 0.0F)) || (!A_not_empty) ||
      (!B_not_empty)) {
    B_not_empty = true;
    A_not_empty = true;
    memset(&epoch[0], 0, 640U * sizeof(float));
    epoch_not_empty = true;
    p300process(epoch, &unusedU0, &stride, &unusedU2, &unusedU3);
  }

  /*  [eegData,boundary] = filter(B,A,eegData',boundary); */
  /*  eegData = eegData'; */
  stride = 1;
  for (dim = 0; dim < 2; dim++) {
    i2 = 5 + 123 * dim;
    pagesize = stride * i2;
    if ((dim << 5) > 0) {
      for (i = 1; i <= 128 + -127 * dim; i++) {
        pageroot = (i - 1) * pagesize;
        for (j = 0; j + 1 <= stride; j++) {
          i1 = pageroot + j;
          if (bv0[dim]) {
            for (k = 0; k + 1 <= (dim << 5); k++) {
              atmp[k] = epoch[i1 + ((k + i2) - (dim << 5)) * stride];
            }

            for (k = i2; k >= (dim << 5) + 1; k--) {
              epoch[i1 + (k - 1) * stride] = epoch[i1 + ((k - (dim << 5)) - 1) *
                stride];
            }

            for (k = 0; k + 1 <= (dim << 5); k++) {
              epoch[i1 + k * stride] = atmp[k];
            }
          } else {
            for (k = 0; k + 1 <= (dim << 5); k++) {
              atmp[k] = epoch[i1 + k * stride];
            }

            i3 = i2 - (dim << 5);
            for (k = 0; k + 1 <= i3; k++) {
              epoch[i1 + k * stride] = epoch[i1 + (k + (dim << 5)) * stride];
            }

            for (k = 0; k + 1 <= (dim << 5); k++) {
              epoch[i1 + ((k + i2) - (dim << 5)) * stride] = atmp[k];
            }
          }
        }
      }
    }

    stride = pagesize;
  }

  for (i2 = 0; i2 < 32; i2++) {
    for (i3 = 0; i3 < 5; i3++) {
      epoch[i3 + 5 * (96 + i2)] = (float)eegData[(i3 + (i2 << 3)) + 2];
    }
  }

  p300process(epoch, result, learn, successRes, falseRes);
}

/*
 * Arguments    : int t
 *                unsigned char selection[4]
 * Return Type  : void
 */
void p300show(int t, unsigned char selection[4])
{
  float targetStepNo;
  float x;
  boolean_T expl_temp;
  boolean_T b_expl_temp;
  boolean_T c_expl_temp;
  unsigned char state_stimul;
  unsigned char state_target;
  static unsigned char t0_stimuli[960] = { 3U, 1U, 2U, 4U, 1U, 3U, 2U, 4U, 3U,
    2U, 4U, 1U, 2U, 3U, 4U, 1U, 2U, 4U, 1U, 3U, 2U, 4U, 3U, 1U, 4U, 3U, 1U, 2U,
    4U, 1U, 2U, 3U, 4U, 1U, 3U, 2U, 4U, 3U, 1U, 2U, 3U, 4U, 2U, 1U, 4U, 2U, 1U,
    3U, 2U, 1U, 3U, 4U, 1U, 2U, 3U, 4U, 1U, 2U, 4U, 3U, 1U, 4U, 2U, 3U, 1U, 2U,
    3U, 4U, 1U, 3U, 2U, 4U, 3U, 1U, 4U, 2U, 3U, 4U, 1U, 2U, 3U, 4U, 2U, 1U, 4U,
    3U, 1U, 2U, 3U, 4U, 2U, 1U, 4U, 3U, 1U, 2U, 3U, 4U, 2U, 1U, 4U, 2U, 1U, 3U,
    4U, 1U, 3U, 2U, 1U, 3U, 4U, 2U, 3U, 1U, 2U, 4U, 3U, 2U, 4U, 1U, 2U, 3U, 1U,
    4U, 2U, 1U, 4U, 3U, 1U, 2U, 3U, 4U, 1U, 3U, 4U, 2U, 1U, 3U, 2U, 4U, 1U, 2U,
    3U, 4U, 1U, 2U, 4U, 3U, 2U, 4U, 1U, 3U, 4U, 2U, 1U, 3U, 4U, 2U, 3U, 1U, 2U,
    4U, 1U, 3U, 4U, 2U, 3U, 1U, 4U, 2U, 1U, 3U, 2U, 1U, 4U, 3U, 2U, 1U, 3U, 4U,
    1U, 2U, 4U, 3U, 2U, 4U, 1U, 3U, 4U, 1U, 2U, 3U, 4U, 2U, 1U, 3U, 4U, 2U, 3U,
    1U, 2U, 4U, 1U, 3U, 2U, 1U, 3U, 4U, 2U, 3U, 4U, 1U, 2U, 4U, 3U, 1U, 2U, 3U,
    4U, 1U, 3U, 4U, 2U, 1U, 4U, 3U, 2U, 1U, 3U, 2U, 1U, 4U, 2U, 3U, 4U, 1U, 3U,
    4U, 1U, 2U, 4U, 3U, 1U, 2U, 4U, 3U, 2U, 1U, 3U, 2U, 4U, 1U, 3U, 4U, 2U, 1U,
    4U, 3U, 2U, 1U, 3U, 2U, 1U, 4U, 3U, 1U, 4U, 2U, 3U, 4U, 1U, 2U, 4U, 3U, 2U,
    1U, 4U, 2U, 3U, 1U, 4U, 2U, 1U, 3U, 4U, 1U, 2U, 3U, 1U, 4U, 2U, 3U, 4U, 1U,
    3U, 2U, 1U, 4U, 2U, 3U, 1U, 4U, 3U, 2U, 1U, 4U, 2U, 3U, 1U, 4U, 3U, 2U, 1U,
    3U, 2U, 4U, 3U, 1U, 2U, 4U, 3U, 1U, 4U, 2U, 3U, 4U, 1U, 2U, 3U, 1U, 2U, 4U,
    1U, 3U, 2U, 4U, 3U, 1U, 2U, 4U, 1U, 3U, 2U, 4U, 1U, 2U, 3U, 4U, 2U, 3U, 1U,
    4U, 3U, 1U, 2U, 4U, 3U, 2U, 4U, 1U, 2U, 4U, 3U, 1U, 4U, 2U, 3U, 1U, 2U, 4U,
    3U, 1U, 2U, 3U, 1U, 4U, 3U, 2U, 1U, 4U, 2U, 1U, 3U, 4U, 1U, 2U, 4U, 3U, 1U,
    4U, 2U, 3U, 1U, 2U, 3U, 4U, 1U, 2U, 4U, 3U, 1U, 4U, 2U, 3U, 4U, 1U, 2U, 3U,
    4U, 1U, 3U, 2U, 1U, 3U, 4U, 2U, 3U, 1U, 2U, 4U, 3U, 2U, 4U, 1U, 2U, 4U, 3U,
    1U, 4U, 3U, 2U, 1U, 3U, 2U, 4U, 1U, 3U, 4U, 1U, 2U, 3U, 4U, 2U, 1U, 4U, 3U,
    2U, 1U, 3U, 4U, 2U, 1U, 4U, 2U, 1U, 3U, 4U, 2U, 3U, 1U, 2U, 3U, 4U, 1U, 3U,
    2U, 1U, 4U, 3U, 1U, 4U, 2U, 1U, 4U, 2U, 3U, 4U, 1U, 3U, 2U, 4U, 3U, 2U, 1U,
    3U, 4U, 1U, 2U, 4U, 1U, 2U, 3U, 1U, 2U, 3U, 4U, 2U, 1U, 4U, 3U, 1U, 2U, 3U,
    4U, 1U, 3U, 4U, 2U, 3U, 4U, 1U, 2U, 4U, 1U, 3U, 2U, 4U, 3U, 2U, 1U, 3U, 4U,
    2U, 1U, 4U, 3U, 1U, 2U, 4U, 1U, 2U, 3U, 1U, 2U, 4U, 3U, 2U, 1U, 3U, 4U, 1U,
    3U, 4U, 2U, 1U, 4U, 3U, 2U, 1U, 4U, 2U, 3U, 1U, 2U, 4U, 3U, 2U, 4U, 3U, 1U,
    2U, 4U, 1U, 3U, 4U, 1U, 3U, 2U, 4U, 1U, 2U, 3U, 1U, 4U, 2U, 3U, 1U, 2U, 4U,
    3U, 2U, 4U, 1U, 3U, 4U, 2U, 3U, 1U, 2U, 4U, 3U, 1U, 4U, 2U, 3U, 1U, 4U, 2U,
    1U, 3U, 4U, 2U, 3U, 1U, 2U, 3U, 1U, 4U, 2U, 1U, 4U, 3U, 2U, 4U, 3U, 1U, 4U,
    3U, 1U, 2U, 4U, 3U, 2U, 1U, 3U, 2U, 4U, 1U, 2U, 4U, 1U, 3U, 2U, 4U, 3U, 1U,
    2U, 4U, 1U, 3U, 4U, 2U, 1U, 3U, 4U, 2U, 3U, 1U, 4U, 2U, 1U, 3U, 4U, 1U, 3U,
    2U, 1U, 4U, 3U, 2U, 1U, 3U, 2U, 4U, 3U, 1U, 4U, 2U, 1U, 3U, 2U, 4U, 3U, 1U,
    4U, 2U, 1U, 3U, 4U, 2U, 3U, 1U, 2U, 4U, 3U, 1U, 4U, 2U, 1U, 4U, 2U, 3U, 4U,
    2U, 3U, 1U, 2U, 4U, 1U, 3U, 4U, 2U, 3U, 1U, 2U, 4U, 3U, 1U, 4U, 2U, 1U, 3U,
    2U, 1U, 4U, 3U, 2U, 4U, 1U, 3U, 4U, 1U, 2U, 3U, 1U, 2U, 3U, 4U, 1U, 3U, 2U,
    4U, 1U, 2U, 4U, 3U, 1U, 4U, 2U, 3U, 4U, 1U, 3U, 2U, 1U, 3U, 2U, 4U, 3U, 2U,
    1U, 4U, 2U, 3U, 4U, 1U, 3U, 4U, 2U, 1U, 4U, 3U, 2U, 1U, 3U, 2U, 1U, 4U, 3U,
    1U, 2U, 4U, 1U, 2U, 4U, 3U, 1U, 2U, 3U, 4U, 1U, 3U, 2U, 4U, 3U, 2U, 1U, 4U,
    2U, 1U, 4U, 3U, 1U, 2U, 4U, 3U, 1U, 4U, 3U, 2U, 4U, 1U, 3U, 2U, 4U, 1U, 2U,
    3U, 1U, 2U, 3U, 4U, 2U, 1U, 3U, 4U, 2U, 3U, 1U, 4U, 2U, 1U, 3U, 4U, 2U, 1U,
    4U, 3U, 2U, 4U, 1U, 3U, 2U, 1U, 4U, 3U, 1U, 2U, 4U, 3U, 1U, 2U, 3U, 4U, 2U,
    1U, 3U, 4U, 1U, 3U, 4U, 2U, 1U, 4U, 2U, 3U, 4U, 1U, 2U, 3U, 4U, 1U, 3U, 2U,
    4U, 3U, 2U, 1U, 4U, 3U, 1U, 2U, 4U, 1U, 3U, 2U, 4U, 3U, 2U, 1U, 3U, 2U, 4U,
    1U, 2U, 3U, 1U, 4U, 2U, 1U, 4U, 3U, 2U, 1U, 3U, 4U, 1U, 3U, 4U, 2U, 3U, 1U,
    2U, 4U, 1U, 2U, 4U, 3U, 2U, 1U, 3U, 4U, 1U, 2U, 4U, 3U, 1U, 4U, 2U, 3U, 1U,
    4U, 3U, 2U, 4U, 3U, 1U, 2U, 4U, 3U, 2U, 1U, 4U, 2U, 1U, 3U, 2U, 4U, 1U, 3U,
    4U, 1U, 3U, 2U, 1U, 3U, 4U, 2U, 1U, 4U, 2U, 3U, 1U, 2U, 3U, 4U, 1U, 2U, 4U,
    3U };

  static unsigned char t0_targets[40] = { 3U, 1U, 2U, 4U, 1U, 3U, 2U, 4U, 3U, 2U,
    4U, 1U, 2U, 3U, 4U, 1U, 2U, 4U, 1U, 3U, 2U, 4U, 3U, 1U, 4U, 3U, 1U, 2U, 4U,
    1U, 2U, 3U, 4U, 1U, 3U, 2U, 4U, 3U, 1U, 2U };

  int i;
  float b_targetStepNo;

  /*  t - номер текущего сэмпла */
  targetStepNo = ((float)t - 1.0F) / 32.0F;
  if (targetStepNo < 0.0F) {
    x = (real32_T)ceil(targetStepNo);
  } else {
    x = (real32_T)floor(targetStepNo);
  }

  p300state(1.0F + x, t0_targets, t0_stimuli, 27.0F, 44.0F, 4.0F, 6.0F, 40.0F,
            5.0F, &state_target, &state_stimul, &c_expl_temp, &b_expl_temp,
            &expl_temp);
  for (i = 0; i < 4; i++) {
    selection[i] = 0;
  }

  if (state_stimul != 0) {
    selection[state_stimul - 1] = 1;
  }

  if ((state_target != 0) && (!(state_stimul != 0))) {
    targetStepNo = ((1.0F + x) - 1.0F) / 44.0F;
    if (targetStepNo < 0.0F) {
      b_targetStepNo = (real32_T)ceil(targetStepNo);
    } else {
      b_targetStepNo = (real32_T)floor(targetStepNo);
    }

    targetStepNo = (1.0F + x) - b_targetStepNo * 44.0F;
    if ((targetStepNo <= 13.333333F) && (targetStepNo > 6.66666651F)) {
      selection[state_target - 1] = 2;
    } else {
      selection[state_target - 1] = 0;
    }
  }

  if (showTarget > 0) {
    selection[showTarget - 1] = (unsigned char)(selection[showTarget - 1] + 2);
  }
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void p300v5_initialize(void)
{
  count_not_empty = false;
  showTarget = b_showTarget;
  falsePerf_not_empty = false;
  successPerf_not_empty = false;
  B_not_empty = false;
  A_not_empty = false;
  epoch_not_empty = false;
  stepNo = b_stepNo;
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void p300v5_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for p300v5.c
 *
 * [EOF]
 */

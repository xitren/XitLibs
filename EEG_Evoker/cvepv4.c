/*
 * File: cvepv4.c
 *
 * MATLAB Coder version            : 2.6
 * C/C++ source code generated on  : 01-Dec-2015 14:35:47
 */

/* Include files */
#include "cvepv4.h"

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
static struct_T mdl;
static float buffer[3520];
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
static void b_cvepprocess(const float eegData[640], signed char *result, int
  *learn, float *successRes, float *falseRes);
static void b_eml_xtrsm(const float A[6400], float B[80]);
static float b_erfc(float x);
static void b_exp(creal32_T x[8]);
static void b_fishertrain(float features, float groups, float mdl_weights[80],
  float *mdl_threshold, float mdl_mu[2], float mdl_sigma[2]);
static void b_repmat(const creal32_T a[8], creal32_T b[40]);
static void b_sqrt(float x[2]);
static void cvepfeatures(float offset, const float epochs[640], float vects[80]);
static void cvepprocess(const float eegData[640]);
static void cvepstate(float c_stepNo, float params_nTrainTargets, const unsigned
                      char params_targets[40], float params_nTargets, float
                      params_nCycles, float params_nEpochSteps, float
                      params_nTargetSteps, float params_nPrestimulusCycles,
                      unsigned char *state_target, boolean_T *state_learn,
                      boolean_T *state_validate, boolean_T *state_detect);
static void eml_xswap(float x[6400], int ix0, int iy0);
static void eml_xtrsm(const float A[6400], float B[80]);
static void fft(const float x[640], creal32_T y[640]);
static void fishertrain(const float features[80], boolean_T groups);
static void mean(const float x[3520], float y[320]);
static void mrdivide(const float A[80], const float B[6400], float y[80]);
static float normcdf(float x, float varargin_1, float varargin_2);
static void repmat(float b[640]);
static float rt_remf(float u0, float u1);
static float rt_roundf(float u);

/* Function Definitions */

/*
 * Arguments    : const float eegData[640]
 *                signed char *result
 *                int *learn
 *                float *successRes
 *                float *falseRes
 * Return Type  : void
 */
static void b_cvepprocess(const float eegData[640], signed char *result, int
  *learn, float *successRes, float *falseRes)
{
  static float features[320];
  int i;
  static const signed char iv2[4] = { 0, 3, 8, 13 };

  boolean_T state_detect;
  boolean_T state_validate;
  boolean_T state_learn;
  unsigned char state_target;
  static unsigned char t0_targets[40] = { 3U, 1U, 2U, 4U, 1U, 3U, 2U, 4U, 3U, 2U,
    4U, 1U, 2U, 3U, 4U, 1U, 2U, 4U, 1U, 3U, 2U, 4U, 3U, 1U, 4U, 3U, 1U, 2U, 4U,
    1U, 2U, 3U, 4U, 1U, 3U, 2U, 4U, 3U, 1U, 2U };

  int ix;
  static float a[80];
  float values[4];
  float mtmp;

  /*  result    номер детектированого стимула или 0 */
  /*  learn     если проводилось обучение, то количество сэмплов, или 0 */
  /*  successRes проценты правильных детектирований (после второго обучения) */
  /*  falseRes   проценты ложных детектирований (после второго обучения) */
  /*  вычисление фич */
  for (i = 0; i < 4; i++) {
    cvepfeatures((stepNo - 1.0F) * 64.0F - (float)iv2[i] * 250.0F / 31.25F,
                 eegData, *(float (*)[80])&features[80 * i]);
  }

  /*  счетчик шагов */
  if ((stepNo == 0.0F) || (!falsePerf_not_empty) || (!successPerf_not_empty)) {
    stepNo = 0.0F;
    successPerf = 0.0F;
    successPerf_not_empty = true;
    falsePerf = 0.0F;
    falsePerf_not_empty = true;
    showTarget = -1;
    memset(&buffer[0], 0, 3520U * sizeof(float));

    /*  Находит веса Фишеровского классификатора */
    /*  fishertrain                                   инициализация обучения */
    /*  mdl = fishertrain(len)                        инициализация модели */
    /*  fishertrain(features,groups)                  сбор данных */
    /*  mdl = fishertrain                             вычисление весов */
    /*  mdl = fishertrain(nAverages,nGroups)          вычисление весов и порога */
    /*  mdl = fishertrain(nAverages,nGroups,mdl)      вычисление только порога */
    /*  */
    for (i = 0; i < 2; i++) {
      count[i] = 0.0F;
    }

    count_not_empty = true;
    for (i = 0; i < 80; i++) {
      mdl.weights[i] = 0.0F;
    }

    mdl.threshold = 0.0F;
    for (i = 0; i < 2; i++) {
      mdl.mu[i] = 0.0F;
      mdl.sigma[i] = 0.0F;
    }
  }

  stepNo++;
  cvepstate(stepNo, 27.0F, t0_targets, 40.0F, 6.0F, 2.0F, 16.0F, 2.0F,
            &state_target, &state_learn, &state_validate, &state_detect);

  /*  сбор данных для обучения */
  if (state_target != 0) {
    for (i = 0; i < 4; i++) {
      fishertrain(*(float (*)[80])&features[80 * i], 1 + i == state_target);
    }
  }

  /*  добавление данных в кольцевой буффер */
  i = (int)(1.0F + rt_remf(stepNo, 11.0F));
  for (ix = 0; ix < 4; ix++) {
    memcpy(&buffer[80 * ix + 320 * (i - 1)], &features[80 * ix], 80U * sizeof
           (float));
  }

  /*  детектирование */
  *result = -1;
  if (state_validate || state_detect) {
    for (i = 0; i < 80; i++) {
      a[i] = mdl.weights[i];
    }

    mean(buffer, features);
    for (i = 0; i < 4; i++) {
      values[i] = 0.0F;
      for (ix = 0; ix < 80; ix++) {
        values[i] += a[ix] * features[ix + 80 * i];
      }
    }

    mtmp = values[0];
    i = -1;
    for (ix = 0; ix < 3; ix++) {
      if (values[ix + 1] > mtmp) {
        mtmp = values[ix + 1];
        i = ix;
      }
    }

    *result = (signed char)(i + 2);
    if (mtmp <= mdl.threshold) {
      *result = 0;

      /*  если ни один не определился */
    } else {
      for (i = 0; i < 4; i++) {
        values[i] = (float)(values[i] > mdl.threshold);
      }

      mtmp = values[0];
      for (i = 0; i < 3; i++) {
        mtmp += values[i + 1];
      }

      if (mtmp > 1.0F) {
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
  *learn = (int)rt_roundf((stepNo - 1.0F) * 64.0F * (float)state_learn);
  if (state_learn) {
    b_fishertrain(11.0F, 4.0F, mdl.weights, &mdl.threshold, mdl.mu, mdl.sigma);
  }

  *successRes = successPerf;
  *falseRes = falsePerf;
}

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
 * Arguments    : creal32_T x[8]
 * Return Type  : void
 */
static void b_exp(creal32_T x[8])
{
  int k;
  float r;
  float x_im;
  float b_x_im;
  for (k = 0; k < 8; k++) {
    r = (real32_T)exp(x[k].re / 2.0F);
    x_im = x[k].im;
    b_x_im = x[k].im;
    x[k].re = r * (r * (real32_T)cos(x_im));
    x[k].im = r * (r * (real32_T)sin(b_x_im));
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
static void b_fishertrain(float features, float groups, float mdl_weights[80],
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
 * Arguments    : const creal32_T a[8]
 *                creal32_T b[40]
 * Return Type  : void
 */
static void b_repmat(const creal32_T a[8], creal32_T b[40])
{
  int jcol;
  int ibmat;
  int itilerow;
  for (jcol = 0; jcol < 8; jcol++) {
    ibmat = jcol * 5;
    for (itilerow = 0; itilerow < 5; itilerow++) {
      b[ibmat + itilerow] = a[jcol];
    }
  }
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
 * Arguments    : float offset
 *                const float epochs[640]
 *                float vects[80]
 * Return Type  : void
 */
static void cvepfeatures(float offset, const float epochs[640], float vects[80])
{
  static float sig[640];
  int i;
  static creal32_T fsig[640];
  creal32_T shift[8];
  static const float fv0[8] = { -6.28318548F, -12.566371F, -18.849556F,
    -25.1327419F, -31.4159279F, -37.6991119F, -43.9823F, -50.2654839F };

  float fsig_im;
  static creal32_T b_fsig[40];
  int i5;
  float fsig_re;
  creal32_T b_vects[40];

  /*  Возвращает фичи сигнала epochs */
  /*    epochs: [ каналы, время, цели ] */
  /*    vects: [ каналы * частоты * 2,  шаги, цели ] */
  repmat(sig);
  for (i = 0; i < 640; i++) {
    sig[i] *= epochs[i];
  }

  fft(sig, fsig);
  for (i = 0; i < 8; i++) {
    fsig_im = fv0[i] * offset;
    if (fsig_im == 0.0F) {
      shift[i].re = 0.0F;
      shift[i].im = 0.0F;
    } else {
      shift[i].re = 0.0F;
      shift[i].im = fsig_im / 128.0F;
    }
  }

  b_exp(shift);

  /*  ? */
  b_repmat(shift, b_fsig);
  for (i = 0; i < 8; i++) {
    for (i5 = 0; i5 < 5; i5++) {
      fsig_re = b_fsig[i5 + 5 * i].re;
      fsig_im = b_fsig[i5 + 5 * i].im;
      b_fsig[i5 + 5 * i].re = fsig[i5 + 5 * (1 + i)].re * fsig_re - fsig[i5 + 5 *
        (1 + i)].im * fsig_im;
      b_fsig[i5 + 5 * i].im = fsig[i5 + 5 * (1 + i)].re * fsig_im + fsig[i5 + 5 *
        (1 + i)].im * fsig_re;
    }
  }

  /* vects = vects(:,1:end,:,:); */
  /* vects = vects(:,2:end,:,:)./vects(:,1:end-1,:,:); */
  /* vects = vects./abs(vects); */
  for (i = 0; i < 40; i++) {
    b_vects[i] = b_fsig[i];
    vects[i] = b_vects[i].re;
  }

  for (i = 0; i < 40; i++) {
    vects[i + 40] = b_vects[i].im;
  }
}

/*
 * Arguments    : const float eegData[640]
 * Return Type  : void
 */
static void cvepprocess(const float eegData[640])
{
  static float features[320];
  int i;
  static const signed char iv1[4] = { 0, 3, 8, 13 };

  boolean_T state_detect;
  boolean_T state_validate;
  boolean_T state_learn;
  unsigned char state_target;
  static unsigned char t1_targets[40] = { 3U, 1U, 2U, 4U, 1U, 3U, 2U, 4U, 3U, 2U,
    4U, 1U, 2U, 3U, 4U, 1U, 2U, 4U, 1U, 3U, 2U, 4U, 3U, 1U, 4U, 3U, 1U, 2U, 4U,
    1U, 2U, 3U, 4U, 1U, 3U, 2U, 4U, 3U, 1U, 2U };

  int ix;
  signed char result;
  static float a[80];
  float values[4];
  float mtmp;

  /*  result    номер детектированого стимула или 0 */
  /*  learn     если проводилось обучение, то количество сэмплов, или 0 */
  /*  successRes проценты правильных детектирований (после второго обучения) */
  /*  falseRes   проценты ложных детектирований (после второго обучения) */
  /*  вычисление фич */
  for (i = 0; i < 4; i++) {
    cvepfeatures((stepNo - 1.0F) * 64.0F - (float)iv1[i] * 250.0F / 31.25F,
                 eegData, *(float (*)[80])&features[80 * i]);
  }

  /*  счетчик шагов */
  if ((stepNo == 0.0F) || (!falsePerf_not_empty) || (!successPerf_not_empty)) {
    stepNo = 0.0F;
    successPerf = 0.0F;
    successPerf_not_empty = true;
    falsePerf = 0.0F;
    falsePerf_not_empty = true;
    showTarget = -1;
    memset(&buffer[0], 0, 3520U * sizeof(float));

    /*  Находит веса Фишеровского классификатора */
    /*  fishertrain                                   инициализация обучения */
    /*  mdl = fishertrain(len)                        инициализация модели */
    /*  fishertrain(features,groups)                  сбор данных */
    /*  mdl = fishertrain                             вычисление весов */
    /*  mdl = fishertrain(nAverages,nGroups)          вычисление весов и порога */
    /*  mdl = fishertrain(nAverages,nGroups,mdl)      вычисление только порога */
    /*  */
    for (i = 0; i < 2; i++) {
      count[i] = 0.0F;
    }

    count_not_empty = true;
    for (i = 0; i < 80; i++) {
      mdl.weights[i] = 0.0F;
    }

    mdl.threshold = 0.0F;
    for (i = 0; i < 2; i++) {
      mdl.mu[i] = 0.0F;
      mdl.sigma[i] = 0.0F;
    }
  }

  stepNo++;
  cvepstate(stepNo, 27.0F, t1_targets, 40.0F, 6.0F, 2.0F, 16.0F, 2.0F,
            &state_target, &state_learn, &state_validate, &state_detect);

  /*  сбор данных для обучения */
  if (state_target != 0) {
    for (i = 0; i < 4; i++) {
      fishertrain(*(float (*)[80])&features[80 * i], 1 + i == state_target);
    }
  }

  /*  добавление данных в кольцевой буффер */
  i = (int)(1.0F + rt_remf(stepNo, 11.0F));
  for (ix = 0; ix < 4; ix++) {
    memcpy(&buffer[80 * ix + 320 * (i - 1)], &features[80 * ix], 80U * sizeof
           (float));
  }

  /*  детектирование */
  result = -1;
  if (state_validate || state_detect) {
    for (i = 0; i < 80; i++) {
      a[i] = mdl.weights[i];
    }

    mean(buffer, features);
    for (i = 0; i < 4; i++) {
      values[i] = 0.0F;
      for (ix = 0; ix < 80; ix++) {
        values[i] += a[ix] * features[ix + 80 * i];
      }
    }

    mtmp = values[0];
    i = -1;
    for (ix = 0; ix < 3; ix++) {
      if (values[ix + 1] > mtmp) {
        mtmp = values[ix + 1];
        i = ix;
      }
    }

    result = (signed char)(i + 2);
    if (mtmp <= mdl.threshold) {
      result = 0;

      /*  если ни один не определился */
    } else {
      for (i = 0; i < 4; i++) {
        values[i] = (float)(values[i] > mdl.threshold);
      }

      mtmp = values[0];
      for (i = 0; i < 3; i++) {
        mtmp += values[i + 1];
      }

      if (mtmp > 1.0F) {
        result = 5;

        /*  если определилось слишком много */
      }
    }

    if (state_detect) {
      showTarget = result;
    }
  }

  /*  валидация */
  if (state_validate && (result >= 1) && (result <= 4)) {
    if (result == state_target) {
      successPerf += 7.69230747F;
    } else {
      falsePerf += 7.69230747F;
    }
  }

  /*  вычисление модели */
  if (state_learn) {
    b_fishertrain(11.0F, 4.0F, mdl.weights, &mdl.threshold, mdl.mu, mdl.sigma);
  }
}

/*
 * Arguments    : float c_stepNo
 *                float params_nTrainTargets
 *                const unsigned char params_targets[40]
 *                float params_nTargets
 *                float params_nCycles
 *                float params_nEpochSteps
 *                float params_nTargetSteps
 *                float params_nPrestimulusCycles
 *                unsigned char *state_target
 *                boolean_T *state_learn
 *                boolean_T *state_validate
 *                boolean_T *state_detect
 * Return Type  : void
 */
static void cvepstate(float c_stepNo, float params_nTrainTargets, const unsigned
                      char params_targets[40], float params_nTargets, float
                      params_nCycles, float params_nEpochSteps, float
                      params_nTargetSteps, float params_nPrestimulusCycles,
                      unsigned char *state_target, boolean_T *state_learn,
                      boolean_T *state_validate, boolean_T *state_detect)
{
  float trainTargetNo;
  float x;

  /*  определяет состояние state по номеру шага stepNo */
  /*  нулевой момент времени - stepNo == 1 */
  *state_target = 0;

  /*  цель для обучения */
  *state_learn = false;

  /*  вычислять модель */
  *state_validate = false;

  /*  выполнять валидацию */
  *state_detect = false;

  /*  выполнять детектирование */
  trainTargetNo = 0.0F;
  if ((c_stepNo > 1.0F) && (c_stepNo - 1.0F <= params_nTargets *
       params_nTargetSteps)) {
    trainTargetNo = (c_stepNo - 2.0F) / params_nTargetSteps;
    if (trainTargetNo < 0.0F) {
      x = (real32_T)ceil(trainTargetNo);
    } else {
      x = (real32_T)floor(trainTargetNo);
    }

    trainTargetNo = 1.0F + x;
    if (c_stepNo - 1.0F >= ((1.0F + x) - 1.0F) * params_nTargetSteps + (1.0F +
         params_nPrestimulusCycles) * params_nEpochSteps) {
      *state_target = params_targets[(int)(1.0F + x) - 1];
    }
  }

  if (c_stepNo - 1.0F == params_nTrainTargets * params_nTargetSteps) {
    *state_learn = true;

    /*  для валидации */
  } else {
    if (c_stepNo - 1.0F == params_nTargets * params_nTargetSteps) {
      *state_learn = true;

      /*  основная модель */
    }
  }

  if ((trainTargetNo <= params_nTargets) && (trainTargetNo >
       params_nTrainTargets) && (c_stepNo - 1.0F == trainTargetNo *
       params_nTargetSteps)) {
    *state_validate = true;
  }

  if (c_stepNo - 1.0F >= params_nTargets * params_nTargetSteps + params_nCycles *
      params_nEpochSteps) {
    *state_detect = true;
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
 * Arguments    : const float x[640]
 *                creal32_T y[640]
 * Return Type  : void
 */
static void fft(const float x[640], creal32_T y[640])
{
  static float b[640];
  int iy;
  int j;
  static creal32_T b_y1[640];
  int ix;
  int chanStart;
  int ju;
  int i;
  boolean_T tst;
  float temp_re;
  float temp_im;
  int iDelta2;
  int k;
  int iheight;
  int ihi;
  static const float fv2[65] = { 0.0F, -0.0490676761F, -0.0980171412F,
    -0.146730468F, -0.195090324F, -0.242980197F, -0.290284663F, -0.336889863F,
    -0.382683456F, -0.427555084F, -0.471396744F, -0.514102757F, -0.555570245F,
    -0.59569931F, -0.634393334F, -0.671559F, -0.707106769F, -0.740951121F,
    -0.773010433F, -0.803207517F, -0.831469595F, -0.857728601F, -0.881921232F,
    -0.903989315F, -0.923879504F, -0.941544056F, -0.956940353F, -0.970031261F,
    -0.980785251F, -0.989176512F, -0.99518472F, -0.99879545F, -1.0F,
    -0.99879545F, -0.99518472F, -0.989176512F, -0.980785251F, -0.970031261F,
    -0.956940353F, -0.941544056F, -0.923879504F, -0.903989315F, -0.881921232F,
    -0.857728601F, -0.831469595F, -0.803207517F, -0.773010433F, -0.740951121F,
    -0.707106769F, -0.671559F, -0.634393334F, -0.59569931F, -0.555570245F,
    -0.514102757F, -0.471396744F, -0.427555084F, -0.382683456F, -0.336889863F,
    -0.290284663F, -0.242980197F, -0.195090324F, -0.146730468F, -0.0980171412F,
    -0.0490676761F, -0.0F };

  static const float fv3[65] = { 1.0F, 0.99879545F, 0.99518472F, 0.989176512F,
    0.980785251F, 0.970031261F, 0.956940353F, 0.941544056F, 0.923879504F,
    0.903989315F, 0.881921232F, 0.857728601F, 0.831469595F, 0.803207517F,
    0.773010433F, 0.740951121F, 0.707106769F, 0.671559F, 0.634393334F,
    0.59569931F, 0.555570245F, 0.514102757F, 0.471396744F, 0.427555084F,
    0.382683456F, 0.336889863F, 0.290284663F, 0.242980197F, 0.195090324F,
    0.146730468F, 0.0980171412F, 0.0490676761F, 0.0F, -0.0490676761F,
    -0.0980171412F, -0.146730468F, -0.195090324F, -0.242980197F, -0.290284663F,
    -0.336889863F, -0.382683456F, -0.427555084F, -0.471396744F, -0.514102757F,
    -0.555570245F, -0.59569931F, -0.634393334F, -0.671559F, -0.707106769F,
    -0.740951121F, -0.773010433F, -0.803207517F, -0.831469595F, -0.857728601F,
    -0.881921232F, -0.903989315F, -0.923879504F, -0.941544056F, -0.956940353F,
    -0.970031261F, -0.980785251F, -0.989176512F, -0.99518472F, -0.99879545F,
    -1.0F };

  for (iy = 0; iy < 5; iy++) {
    for (j = 0; j < 128; j++) {
      b[j + (iy << 7)] = x[iy + 5 * j];
    }
  }

  ix = 0;
  for (chanStart = 0; chanStart < 514; chanStart += 128) {
    ju = 0;
    iy = chanStart;
    for (i = 0; i < 127; i++) {
      b_y1[iy].re = b[ix];
      b_y1[iy].im = 0.0F;
      j = 128;
      tst = true;
      while (tst) {
        j >>= 1;
        ju ^= j;
        tst = ((ju & j) == 0);
      }

      iy = chanStart + ju;
      ix++;
    }

    b_y1[iy].re = b[ix];
    b_y1[iy].im = 0.0F;
    ix++;
    for (i = chanStart; i <= chanStart + 126; i += 2) {
      temp_re = b_y1[i + 1].re;
      temp_im = b_y1[i + 1].im;
      b_y1[i + 1].re = b_y1[i].re - b_y1[i + 1].re;
      b_y1[i + 1].im = b_y1[i].im - b_y1[i + 1].im;
      b_y1[i].re += temp_re;
      b_y1[i].im += temp_im;
    }

    ju = 2;
    iDelta2 = 4;
    k = 32;
    iheight = 125;
    while (k > 0) {
      i = chanStart;
      ihi = chanStart + iheight;
      while (i < ihi) {
        iy = i + ju;
        temp_re = b_y1[iy].re;
        temp_im = b_y1[iy].im;
        b_y1[i + ju].re = b_y1[i].re - b_y1[iy].re;
        b_y1[i + ju].im = b_y1[i].im - b_y1[iy].im;
        b_y1[i].re += temp_re;
        b_y1[i].im += temp_im;
        i += iDelta2;
      }

      iy = chanStart + 1;
      for (j = k; j < 64; j += k) {
        i = iy;
        ihi = iy + iheight;
        while (i < ihi) {
          temp_re = fv3[j] * b_y1[i + ju].re - fv2[j] * b_y1[i + ju].im;
          temp_im = fv3[j] * b_y1[i + ju].im + fv2[j] * b_y1[i + ju].re;
          b_y1[i + ju].re = b_y1[i].re - temp_re;
          b_y1[i + ju].im = b_y1[i].im - temp_im;
          b_y1[i].re += temp_re;
          b_y1[i].im += temp_im;
          i += iDelta2;
        }

        iy++;
      }

      k >>= 1;
      ju = iDelta2;
      iDelta2 <<= 1;
      iheight -= ju;
    }
  }

  for (iy = 0; iy < 128; iy++) {
    for (j = 0; j < 5; j++) {
      y[j + 5 * iy] = b_y1[iy + (j << 7)];
    }
  }
}

/*
 * Arguments    : const float features[80]
 *                boolean_T groups
 * Return Type  : void
 */
static void fishertrain(const float features[80], boolean_T groups)
{
  boolean_T guard1 = false;
  boolean_T x[2];
  int i;
  boolean_T y;
  boolean_T exitg1;
  int l;

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
    for (i = 0; i < 2; i++) {
      x[i] = (count[i] == 0.0F);
    }

    y = true;
    i = 0;
    exitg1 = false;
    while ((!exitg1) && (i < 2)) {
      if (x[i] == 0) {
        y = false;
        exitg1 = true;
      } else {
        i++;
      }
    }

    if (y) {
      guard1 = true;
    }
  }

  if (guard1) {
    /*  инициализирует начало обучения */
    memset(&X[0], 0, 160U * sizeof(float));
    memset(&XX[0], 0, 12800U * sizeof(float));
    for (i = 0; i < 2; i++) {
      count[i] = 0.0F;
    }

    count_not_empty = true;
  }

  count[(int)groups]++;
  for (i = 0; i < 80; i++) {
    X[i + 80 * groups] += features[i];
    for (l = 0; l < 80; l++) {
      XX[(i + 80 * l) + 6400 * groups] += features[i] * features[l];
    }
  }
}

/*
 * Arguments    : const float x[3520]
 *                float y[320]
 * Return Type  : void
 */
static void mean(const float x[3520], float y[320])
{
  int iy;
  int ixstart;
  int j;
  int ix;
  float s;
  int k;
  iy = -1;
  ixstart = -1;
  for (j = 0; j < 320; j++) {
    ixstart++;
    ix = ixstart;
    s = x[ixstart];
    for (k = 0; k < 10; k++) {
      ix += 320;
      s += x[ix];
    }

    iy++;
    y[iy] = s;
  }

  for (iy = 0; iy < 320; iy++) {
    y[iy] /= 11.0F;
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
  int i6;
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
  for (i6 = 0; i6 < 80; i6++) {
    ipiv[i6] = (unsigned char)(1 + i6);
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

      i6 = (c - j) + 80;
      for (jA = c + 1; jA + 1 <= i6; jA++) {
        b_A[jA] /= b_A[c];
      }
    }

    jA = c;
    jy = c + 80;
    for (b_j = 1; b_j <= 79 - j; b_j++) {
      temp = b_A[jy];
      if (b_A[jy] != 0.0F) {
        ix = c + 1;
        i6 = (jA - j) + 160;
        for (ijA = 81 + jA; ijA + 1 <= i6; ijA++) {
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
 * Arguments    : float b[640]
 * Return Type  : void
 */
static void repmat(float b[640])
{
  int jcol;
  int ibmat;
  int itilerow;
  static const float fv1[128] = { 0.0F, 0.000611791911F, 0.00244567031F,
    0.00549714779F, 0.0097587565F, 0.0152200675F, 0.0218677167F, 0.0296854358F,
    0.0386540927F, 0.0487517416F, 0.0599536672F, 0.0722324625F, 0.0855580792F,
    0.0998979F, 0.115216844F, 0.131477416F, 0.148639813F, 0.166662052F,
    0.185500026F, 0.205107644F, 0.225436911F, 0.246438071F, 0.268059731F,
    0.29024902F, 0.312951565F, 0.336111873F, 0.359673232F, 0.383578F,
    0.407767683F, 0.432183057F, 0.4567644F, 0.481451541F, 0.506184101F,
    0.530901492F, 0.555543244F, 0.580049098F, 0.60435909F, 0.628413677F,
    0.652153969F, 0.67552197F, 0.6984604F, 0.720913231F, 0.742825389F,
    0.764143348F, 0.784814835F, 0.804789424F, 0.824018061F, 0.842453837F,
    0.860051572F, 0.876768172F, 0.892562747F, 0.907396674F, 0.921233594F,
    0.934039712F, 0.945783675F, 0.956436753F, 0.965972781F, 0.974368572F,
    0.981603444F, 0.987659812F, 0.992522717F, 0.996180415F, 0.998623848F,
    0.999847054F, 0.999847054F, 0.998623848F, 0.996180415F, 0.992522717F,
    0.987659812F, 0.981603444F, 0.974368572F, 0.965972781F, 0.956436753F,
    0.945783675F, 0.934039712F, 0.921233594F, 0.907396674F, 0.892562747F,
    0.876768172F, 0.860051572F, 0.842453837F, 0.824018061F, 0.804789424F,
    0.784814835F, 0.764143348F, 0.742825389F, 0.720913231F, 0.6984604F,
    0.67552197F, 0.652153969F, 0.628413677F, 0.60435909F, 0.580049098F,
    0.555543244F, 0.530901492F, 0.506184101F, 0.481451541F, 0.4567644F,
    0.432183057F, 0.407767683F, 0.383578F, 0.359673232F, 0.336111873F,
    0.312951565F, 0.29024902F, 0.268059731F, 0.246438071F, 0.225436911F,
    0.205107644F, 0.185500026F, 0.166662052F, 0.148639813F, 0.131477416F,
    0.115216844F, 0.0998979F, 0.0855580792F, 0.0722324625F, 0.0599536672F,
    0.0487517416F, 0.0386540927F, 0.0296854358F, 0.0218677167F, 0.0152200675F,
    0.0097587565F, 0.00549714779F, 0.00244567031F, 0.000611791911F, 0.0F };

  for (jcol = 0; jcol < 128; jcol++) {
    ibmat = jcol * 5;
    for (itilerow = 0; itilerow < 5; itilerow++) {
      b[ibmat + itilerow] = fv1[jcol];
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
void cvepgenerate(int t, int data[5])
{
  int i;
  float b_t;
  static const unsigned char uv0[40] = { 3U, 1U, 2U, 4U, 1U, 3U, 2U, 4U, 3U, 2U,
    4U, 1U, 2U, 3U, 4U, 1U, 2U, 4U, 1U, 3U, 2U, 4U, 3U, 1U, 4U, 3U, 1U, 2U, 4U,
    1U, 2U, 3U, 4U, 1U, 3U, 2U, 4U, 3U, 1U, 2U };

  int i0;
  static const signed char iv0[4] = { 0, 3, 8, 13 };

  /*  Генерация тестовых данных */
  /*    t - номер сэмпла тестовой последовательности */
  /*    data - показания 5-ти электродов */
  for (i = 0; i < 5; i++) {
    data[i] = 0;
  }

  if (t < 1) {
  } else {
    b_t = (real32_T)floor(((float)t - 1.0F) / 1024.0F);
    if (1.0 + b_t <= 40.0) {
      i0 = uv0[(int)b_t];
    } else {
      i0 = 1;
    }

    b_t = (((float)t - (1.0F + b_t) * 1024.0F) - 1.0F) - (float)iv0[i0 - 1] *
      8.0F;
    for (i = 0; i < 5; i++) {
      data[i] += (int)rt_roundf(1000.0F * (real32_T)sin(b_t * 2.0F * 3.14159274F
        / 128.0F * ((1.0F + (float)i) + 1.0F)));
    }
  }
}

/*
 * Arguments    : boolean_T learn
 * Return Type  : boolean_T
 */
boolean_T cvepinit(boolean_T learn)
{
  boolean_T success;

  /*  инициализирует счетчик */
  /*  */
  /*  инициализирует счетчик */
  /*  */
  success = true;
  if (learn) {
    stepNo = 0.0F;
  } else if (stepNo * 64.0F < 40960.0F) {
    success = false;
  } else {
    stepNo = 640.0F;
  }

  return success;
}

/*
 * Arguments    : unsigned char patterns[256]
 * Return Type  : void
 */
void cveppatterns(unsigned char patterns[256])
{
  int i1;
  int i2;
  static const unsigned char uv1[64] = { 3U, 4U, 4U, 0U, 0U, 4U, 4U, 4U, 4U, 3U,
    3U, 0U, 0U, 4U, 3U, 4U, 4U, 4U, 4U, 0U, 0U, 4U, 4U, 4U, 0U, 0U, 0U, 0U, 0U,
    0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 4U, 4U, 4U, 0U, 0U, 4U, 4U, 4U,
    3U, 4U, 3U, 0U, 0U, 4U, 3U, 3U, 4U, 4U, 4U, 0U, 0U, 4U, 3U, 3U };

  static const unsigned char y[64] = { 2U, 2U, 2U, 0U, 0U, 2U, 2U, 2U, 2U, 2U,
    2U, 0U, 0U, 2U, 2U, 2U, 2U, 2U, 2U, 0U, 0U, 2U, 2U, 2U, 0U, 0U, 0U, 0U, 0U,
    0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 2U, 2U, 2U, 0U, 0U, 2U, 2U, 2U,
    2U, 2U, 2U, 0U, 0U, 2U, 2U, 2U, 2U, 2U, 2U, 0U, 0U, 2U, 2U, 2U };

  static const unsigned char uv2[64] = { 3U, 6U, 6U, 0U, 0U, 6U, 6U, 6U, 6U, 3U,
    3U, 0U, 0U, 6U, 3U, 6U, 6U, 6U, 6U, 0U, 0U, 6U, 6U, 6U, 0U, 0U, 0U, 0U, 0U,
    0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 6U, 6U, 6U, 0U, 0U, 6U, 6U, 6U,
    3U, 6U, 3U, 0U, 0U, 6U, 3U, 3U, 6U, 6U, 6U, 0U, 0U, 6U, 3U, 3U };

  memset(&patterns[0], 0, sizeof(unsigned char) << 8);
  for (i1 = 0; i1 < 8; i1++) {
    for (i2 = 0; i2 < 8; i2++) {
      patterns[64 + (i2 + (i1 << 3))] = uv1[i2 + (i1 << 3)];
      patterns[128 + (i2 + (i1 << 3))] = y[i2 + (i1 << 3)];
      patterns[192 + (i2 + (i1 << 3))] = uv2[i2 + (i1 << 3)];
    }
  }
}

/*
 * Arguments    : const int eegData[512]
 *                signed char *result
 *                int *learn
 *                float *successRes
 *                float *falseRes
 * Return Type  : void
 */
void cveprun(const int eegData[512], signed char *result, int *learn, float
             *successRes, float *falseRes)
{
  float atmp[64];
  int stride;
  int dim;
  int i3;
  int pagesize;
  int i;
  int pageroot;
  int j;
  int i1;
  static const boolean_T bv0[2] = { true, false };

  int k;
  int i4;

  /*  eegData - массив [8*params.nStepSamples] одного шага данных. Из этого */
  /*  массива выбираются строки 3:7. Несколько шагов стыкуются вместе и */
  /*  передаются в функцию process. */
  if ((!epoch_not_empty) || (!(stepNo != 0.0F))) {
    memset(&epoch[0], 0, 640U * sizeof(float));
    epoch_not_empty = true;
    cvepprocess(epoch);
  }

  stride = 1;
  for (dim = 0; dim < 2; dim++) {
    i3 = 5 + 123 * dim;
    pagesize = stride * i3;
    if ((dim << 6) > 0) {
      for (i = 1; i <= 128 + -127 * dim; i++) {
        pageroot = (i - 1) * pagesize;
        for (j = 0; j + 1 <= stride; j++) {
          i1 = pageroot + j;
          if (bv0[dim]) {
            for (k = 0; k + 1 <= (dim << 6); k++) {
              atmp[k] = epoch[i1 + ((k + i3) - (dim << 6)) * stride];
            }

            for (k = i3; k >= (dim << 6) + 1; k--) {
              epoch[i1 + (k - 1) * stride] = epoch[i1 + ((k - (dim << 6)) - 1) *
                stride];
            }

            for (k = 0; k + 1 <= (dim << 6); k++) {
              epoch[i1 + k * stride] = atmp[k];
            }
          } else {
            for (k = 0; k + 1 <= (dim << 6); k++) {
              atmp[k] = epoch[i1 + k * stride];
            }

            i4 = i3 - (dim << 6);
            for (k = 0; k + 1 <= i4; k++) {
              epoch[i1 + k * stride] = epoch[i1 + (k + (dim << 6)) * stride];
            }

            for (k = 0; k + 1 <= (dim << 6); k++) {
              epoch[i1 + ((k + i3) - (dim << 6)) * stride] = atmp[k];
            }
          }
        }
      }
    }

    stride = pagesize;
  }

  for (i3 = 0; i3 < 64; i3++) {
    for (i4 = 0; i4 < 5; i4++) {
      epoch[i4 + 5 * (64 + i3)] = (float)eegData[(i4 + (i3 << 3)) + 2];
    }
  }

  b_cvepprocess(epoch, result, learn, successRes, falseRes);
}

/*
 * Arguments    : int t
 *                unsigned char selection[4]
 * Return Type  : void
 */
void cvepshow(int t, unsigned char selection[4])
{
  float y;
  float b_y;
  int i;
  int i7;
  static const signed char iv3[64] = { 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1,
    1, 1, 0, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0,
    0, 0, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1 };

  static const unsigned char uv3[40] = { 3U, 1U, 2U, 4U, 1U, 3U, 2U, 4U, 3U, 2U,
    4U, 1U, 2U, 3U, 4U, 1U, 2U, 4U, 1U, 3U, 2U, 4U, 3U, 1U, 4U, 3U, 1U, 2U, 4U,
    1U, 2U, 3U, 4U, 1U, 3U, 2U, 4U, 3U, 1U, 2U };

  /*  t - номер текущего сэмпла */
  y = ((float)t - 1.0F) / 8.0F;
  if (y < 0.0F) {
    b_y = (real32_T)ceil(y);
  } else {
    b_y = (real32_T)floor(y);
  }

  i = (int)rt_remf((1.0F + b_y) - 1.0F, 16.0F);
  for (i7 = 0; i7 < 4; i7++) {
    selection[i7] = (unsigned char)iv3[i7 + (i << 2)];
  }

  y = ((float)t - 1.0F) / 1024.0F;
  if (y < 0.0F) {
    y = (real32_T)ceil(y);
  } else {
    y = (real32_T)floor(y);
  }

  if (1.0 + y <= 40.0) {
    if (t < ((1.0F + y) - 1.0F) * 1024.0F + 256.0F) {
      for (i = 0; i < 4; i++) {
        selection[i] = 0;
      }

      selection[uv3[(int)y] - 1] = 2;
    }
  } else {
    if (showTarget > 0) {
      selection[showTarget - 1] = (unsigned char)(selection[showTarget - 1] * 3);
    }
  }
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void cvepv4_initialize(void)
{
  count_not_empty = false;
  showTarget = b_showTarget;
  falsePerf_not_empty = false;
  successPerf_not_empty = false;
  epoch_not_empty = false;
  stepNo = b_stepNo;
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void cvepv4_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for cvepv4.c
 *
 * [EOF]
 */

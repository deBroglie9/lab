/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * log.c
 *
 * Code generation for function 'log'
 *
 */

/* Include files */
#include "log.h"
#include "IK_7DOF_rtwutil.h"
#include "rt_nonfinite.h"
#include "rt_defines.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Declarations */
static double rt_atan2d_snf(double u0, double u1);

/* Function Definitions */
static double rt_atan2d_snf(double u0, double u1)
{
  double y;
  int i;
  int i1;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = rtNaN;
  } else if (rtIsInf(u0) && rtIsInf(u1)) {
    if (u0 > 0.0) {
      i = 1;
    } else {
      i = -1;
    }
    if (u1 > 0.0) {
      i1 = 1;
    } else {
      i1 = -1;
    }
    y = atan2(i, i1);
  } else if (u1 == 0.0) {
    if (u0 > 0.0) {
      y = RT_PI / 2.0;
    } else if (u0 < 0.0) {
      y = -(RT_PI / 2.0);
    } else {
      y = 0.0;
    }
  } else {
    y = atan2(u0, u1);
  }
  return y;
}

void b_log(creal_T *x)
{
  double d;
  double d1;
  if (x->im == 0.0) {
    if (x->re < 0.0) {
      x->re = log(fabs(x->re));
      x->im = 3.1415926535897931;
    } else {
      x->re = log(fabs(x->re));
      x->im = 0.0;
    }
  } else if ((fabs(x->re) > 8.9884656743115785E+307) ||
             (fabs(x->im) > 8.9884656743115785E+307)) {
    d = x->re;
    d1 = x->im;
    x->re = log(rt_hypotd_snf(d / 2.0, d1 / 2.0)) + 0.69314718055994529;
    x->im = rt_atan2d_snf(d1, d);
  } else {
    d = x->re;
    d1 = x->im;
    x->re = log(rt_hypotd_snf(d, d1));
    x->im = rt_atan2d_snf(d1, d);
  }
}

/* End of code generation (log.c) */

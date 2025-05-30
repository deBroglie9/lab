/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * power.c
 *
 * Code generation for function 'power'
 *
 */

/* Include files */
#include "power.h"
#include "IK_7DOF_rtwutil.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */
creal_T power(const creal_T a)
{
  creal_T y;
  double absxi;
  double absxr;
  if (a.im == 0.0) {
    if (a.re < 0.0) {
      absxi = 0.0;
      absxr = sqrt(-a.re);
    } else {
      absxi = sqrt(a.re);
      absxr = 0.0;
    }
  } else if (a.re == 0.0) {
    if (a.im < 0.0) {
      absxi = sqrt(-a.im / 2.0);
      absxr = -absxi;
    } else {
      absxi = sqrt(a.im / 2.0);
      absxr = absxi;
    }
  } else if (rtIsNaN(a.re)) {
    absxi = rtNaN;
    absxr = rtNaN;
  } else if (rtIsNaN(a.im)) {
    absxi = rtNaN;
    absxr = rtNaN;
  } else if (rtIsInf(a.im)) {
    absxi = fabs(a.im);
    absxr = a.im;
  } else if (rtIsInf(a.re)) {
    if (a.re < 0.0) {
      absxi = 0.0;
      absxr = a.im * -a.re;
    } else {
      absxi = a.re;
      absxr = 0.0;
    }
  } else {
    absxr = fabs(a.re);
    absxi = fabs(a.im);
    if ((absxr > 4.4942328371557893E+307) ||
        (absxi > 4.4942328371557893E+307)) {
      absxr *= 0.5;
      absxi = rt_hypotd_snf(absxr, absxi * 0.5);
      if (absxi > absxr) {
        absxi = sqrt(absxi) * sqrt(absxr / absxi + 1.0);
      } else {
        absxi = sqrt(absxi) * 1.4142135623730951;
      }
    } else {
      absxi = sqrt((rt_hypotd_snf(absxr, absxi) + absxr) * 0.5);
    }
    if (a.re > 0.0) {
      absxr = 0.5 * (a.im / absxi);
    } else {
      if (a.im < 0.0) {
        absxr = -absxi;
      } else {
        absxr = absxi;
      }
      absxi = 0.5 * (a.im / absxr);
    }
  }
  y.re = absxi;
  y.im = absxr;
  return y;
}

/* End of code generation (power.c) */

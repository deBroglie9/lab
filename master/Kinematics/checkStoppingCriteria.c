/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * checkStoppingCriteria.c
 *
 * Code generation for function 'checkStoppingCriteria'
 *
 */

/* Include files */
#include "checkStoppingCriteria.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */
int checkStoppingCriteria(const double gradf[2], double relFactor,
                          double funDiff, const double x[2], const double dx[2],
                          int funcCount, boolean_T stepSuccessful, int *iter)
{
  double absx;
  double absxk;
  double b_y;
  double normGradF;
  double t;
  double y;
  int exitflag;
  int k;
  normGradF = 0.0;
  for (k = 0; k < 2; k++) {
    absx = fabs(gradf[k]);
    if (rtIsNaN(absx) || (absx > normGradF)) {
      normGradF = absx;
    }
  }
  if (normGradF <= 1.0E-10 * relFactor) {
    exitflag = 1;
  } else if (funcCount >= 400) {
    exitflag = 0;
  } else if (*iter >= 400) {
    exitflag = 0;
  } else {
    normGradF = 3.3121686421112381E-170;
    absx = 3.3121686421112381E-170;
    absxk = fabs(dx[0]);
    if (absxk > 3.3121686421112381E-170) {
      y = 1.0;
      normGradF = absxk;
    } else {
      t = absxk / 3.3121686421112381E-170;
      y = t * t;
    }
    absxk = fabs(x[0]);
    if (absxk > 3.3121686421112381E-170) {
      b_y = 1.0;
      absx = absxk;
    } else {
      t = absxk / 3.3121686421112381E-170;
      b_y = t * t;
    }
    absxk = fabs(dx[1]);
    if (absxk > normGradF) {
      t = normGradF / absxk;
      y = y * t * t + 1.0;
      normGradF = absxk;
    } else {
      t = absxk / normGradF;
      y += t * t;
    }
    absxk = fabs(x[1]);
    if (absxk > absx) {
      t = absx / absxk;
      b_y = b_y * t * t + 1.0;
      absx = absxk;
    } else {
      t = absxk / absx;
      b_y += t * t;
    }
    y = normGradF * sqrt(y);
    b_y = absx * sqrt(b_y);
    if (y < 1.0E-6 * (b_y + 1.4901161193847656E-8)) {
      exitflag = 4;
      if (!stepSuccessful) {
        (*iter)++;
      }
    } else if (funDiff <= 1.0E-6) {
      exitflag = 3;
    } else {
      exitflag = -5;
    }
  }
  return exitflag;
}

/* End of code generation (checkStoppingCriteria.c) */

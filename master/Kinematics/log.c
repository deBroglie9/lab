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
#include "rt_wutil.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */
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

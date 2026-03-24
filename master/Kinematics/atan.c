/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * atan.c
 *
 * Code generation for function 'atan'
 *
 */

/* Include files */
#include "atan.h"
#include "FK_7DOF_data.h"
#include "rt_wutil.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */
void b_atan(creal_T *x)
{
  double absz;
  double t;
  double t_im;
  double t_re;
  double xi;
  double xr;
  if (x->im == 0.0) {
    x->re = atan(x->re);
    x->im = 0.0;
  } else {
    t_re = -x->im;
    t_im = x->re;
    xr = fabs(t_re);
    xi = fabs(t_im);
    if ((xr > 3.3519519824856489E+153) || (xi > 3.3519519824856489E+153)) {
      if (xi == 0.0) {
        xr = 1.0 / xr;
      } else if (xr == 0.0) {
        xr = 0.0;
      } else if (xr > xi) {
        absz = xi / xr;
        xr = (absz * 0.0 + 1.0) / (xr + absz * xi);
      } else if (xi == xr) {
        xr = 0.5 / xr;
      } else {
        absz = xr / xi;
        xr = absz / (xi + absz * xr);
      }
      xi = 1.5707963267948966;
    } else if ((xr == 1.0) && (xi == 0.0)) {
      xr = rtInf;
    } else if (xr == 1.0) {
      xr = log(sqrt(sqrt(xi * xi + 4.0)) / sqrt(xi + 2.9833362924800834E-154));
      xi = (atan((xi + 2.9833362924800834E-154) / 2.0) + 1.5707963267948966) /
           2.0;
    } else if ((xi == 0.0) && (!(xr > 1.0))) {
      if (xr < 0.5) {
        t = xr + xr;
        t += t * (xr / (1.0 - xr));
        if (!(t < 2.2204460492503131E-16)) {
          t = log(t + 1.0) * (t / ((t + 1.0) - 1.0));
        }
        xr = t / 2.0;
      } else if (xr == 1.0) {
        xr = rtInf;
      } else {
        t = (xr + xr) / (1.0 - xr);
        if ((t > 4.503599627370496E+15) || rtIsNaN(t)) {
          t++;
          t = log(t);
        } else {
          t = log(t + 1.0) * (t / ((t + 1.0) - 1.0));
        }
        xr = t / 2.0;
      }
    } else {
      t = (xi + 2.9833362924800834E-154) * (xi + 2.9833362924800834E-154);
      xi = rt_atan2d_snf(2.0 * xi, (1.0 - xr) * (xr + 1.0) - t) / 2.0;
      t = 4.0 * (xr / ((1.0 - xr) * (1.0 - xr) + t));
      absz = fabs(t);
      if ((absz > 4.503599627370496E+15) || (rtIsInf(t) || rtIsNaN(t))) {
        t++;
        t = log(t);
      } else if (!(absz < 2.2204460492503131E-16)) {
        t = log(t + 1.0) * (t / ((t + 1.0) - 1.0));
      }
      xr = t / 4.0;
    }
    if (t_re < 0.0) {
      xr = -xr;
    }
    if ((t_im < 0.0) || ((t_im == 0.0) && (t_re < -1.0))) {
      xi = -xi;
    }
    x->re = xi;
    x->im = -xr;
  }
}

/* End of code generation (atan.c) */

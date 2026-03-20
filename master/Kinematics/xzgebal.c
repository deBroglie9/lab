/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * xzgebal.c
 *
 * Code generation for function 'xzgebal'
 *
 */

/* Include files */
#include "xzgebal.h"
#include "rt_nonfinite.h"
#include "xnrm2.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */
int xzgebal(double A_data[], const int A_size[2], int *ihi, double scale_data[],
            int *scale_size)
{
  double absxk;
  double c;
  double ca;
  double f;
  double r;
  double s;
  double scale;
  double t;
  double u0;
  int b_k;
  int c_tmp;
  int exitg1;
  int exitg2;
  int exitg4;
  int exitg5;
  int i;
  int ilo;
  int ix;
  int iy;
  int k;
  int kend;
  int n;
  int n_tmp;
  int temp_tmp;
  boolean_T converged;
  boolean_T exitg3;
  boolean_T exitg6;
  boolean_T exitg7;
  boolean_T notdone;
  n = A_size[0];
  *scale_size = A_size[0];
  kend = A_size[0];
  for (i = 0; i < kend; i++) {
    scale_data[i] = 1.0;
  }
  k = 0;
  *ihi = A_size[0];
  notdone = true;
  do {
    exitg5 = 0;
    if (notdone) {
      notdone = false;
      c_tmp = *ihi;
      do {
        exitg4 = 0;
        if (c_tmp > 0) {
          converged = false;
          ix = 0;
          exitg6 = false;
          while ((!exitg6) && (ix <= (unsigned char)*ihi - 1)) {
            if ((ix + 1 == c_tmp) ||
                (!(A_data[(c_tmp + A_size[0] * ix) - 1] != 0.0))) {
              ix++;
            } else {
              converged = true;
              exitg6 = true;
            }
          }
          if (converged) {
            c_tmp--;
          } else {
            scale_data[*ihi - 1] = c_tmp;
            if (c_tmp != *ihi) {
              ix = (c_tmp - 1) * n;
              iy = (*ihi - 1) * n;
              i = (unsigned char)*ihi;
              for (b_k = 0; b_k < i; b_k++) {
                temp_tmp = ix + b_k;
                scale = A_data[temp_tmp];
                n_tmp = iy + b_k;
                A_data[temp_tmp] = A_data[n_tmp];
                A_data[n_tmp] = scale;
              }
              for (b_k = 0; b_k < n; b_k++) {
                temp_tmp = b_k * n;
                n_tmp = (c_tmp + temp_tmp) - 1;
                scale = A_data[n_tmp];
                i = (*ihi + temp_tmp) - 1;
                A_data[n_tmp] = A_data[i];
                A_data[i] = scale;
              }
            }
            exitg4 = 1;
          }
        } else {
          exitg4 = 2;
        }
      } while (exitg4 == 0);
      if (exitg4 == 1) {
        if (*ihi == 1) {
          ilo = 1;
          *ihi = 1;
          exitg5 = 1;
        } else {
          (*ihi)--;
          notdone = true;
        }
      }
    } else {
      notdone = true;
      while (notdone) {
        notdone = false;
        c_tmp = k;
        exitg6 = false;
        while ((!exitg6) && (c_tmp + 1 <= *ihi)) {
          converged = false;
          ix = k;
          exitg7 = false;
          while ((!exitg7) && (ix + 1 <= *ihi)) {
            if ((ix + 1 == c_tmp + 1) ||
                (!(A_data[ix + A_size[0] * c_tmp] != 0.0))) {
              ix++;
            } else {
              converged = true;
              exitg7 = true;
            }
          }
          if (converged) {
            c_tmp++;
          } else {
            scale_data[k] = c_tmp + 1;
            if (c_tmp + 1 != k + 1) {
              ix = c_tmp * n;
              kend = k * n;
              i = (unsigned char)*ihi;
              for (b_k = 0; b_k < i; b_k++) {
                temp_tmp = ix + b_k;
                scale = A_data[temp_tmp];
                n_tmp = kend + b_k;
                A_data[temp_tmp] = A_data[n_tmp];
                A_data[n_tmp] = scale;
              }
              ix = kend + c_tmp;
              iy = kend + k;
              kend = n - k;
              for (b_k = 0; b_k < kend; b_k++) {
                temp_tmp = b_k * n;
                n_tmp = ix + temp_tmp;
                scale = A_data[n_tmp];
                i = iy + temp_tmp;
                A_data[n_tmp] = A_data[i];
                A_data[i] = scale;
              }
            }
            k++;
            notdone = true;
            exitg6 = true;
          }
        }
      }
      ilo = k + 1;
      converged = false;
      exitg5 = 2;
    }
  } while (exitg5 == 0);
  if (exitg5 != 1) {
    exitg3 = false;
    while ((!exitg3) && (!converged)) {
      converged = true;
      ix = k;
      do {
        exitg2 = 0;
        if (ix + 1 <= *ihi) {
          kend = *ihi - k;
          c_tmp = ix * n;
          c = xnrm2(kend, A_data, (c_tmp + k) + 1);
          iy = k * n + ix;
          r = 0.0;
          if (kend >= 1) {
            if (kend == 1) {
              r = fabs(A_data[iy]);
            } else {
              scale = 3.3121686421112381E-170;
              kend = (iy + (kend - 1) * n) + 1;
              for (b_k = iy + 1; n < 0 ? b_k >= kend : b_k <= kend; b_k += n) {
                absxk = fabs(A_data[b_k - 1]);
                if (absxk > scale) {
                  t = scale / absxk;
                  r = r * t * t + 1.0;
                  scale = absxk;
                } else {
                  t = absxk / scale;
                  r += t * t;
                }
              }
              r = scale * sqrt(r);
            }
          }
          kend = 1;
          if (*ihi > 1) {
            scale = fabs(A_data[c_tmp]);
            for (b_k = 2; b_k <= *ihi; b_k++) {
              s = fabs(A_data[(c_tmp + b_k) - 1]);
              if (s > scale) {
                kend = b_k;
                scale = s;
              }
            }
          }
          ca = fabs(A_data[(kend + A_size[0] * ix) - 1]);
          n_tmp = n - k;
          if (n_tmp < 1) {
            kend = 0;
          } else {
            kend = 1;
            if (n_tmp > 1) {
              scale = fabs(A_data[iy]);
              for (b_k = 2; b_k <= n_tmp; b_k++) {
                s = fabs(A_data[iy + (b_k - 1) * n]);
                if (s > scale) {
                  kend = b_k;
                  scale = s;
                }
              }
            }
          }
          scale = fabs(A_data[ix + A_size[0] * ((kend + k) - 1)]);
          if ((c == 0.0) || (r == 0.0)) {
            ix++;
          } else {
            absxk = r / 2.0;
            f = 1.0;
            s = c + r;
            do {
              exitg1 = 0;
              if (c < absxk) {
                if ((c >= ca) || rtIsNaN(ca)) {
                  t = c;
                } else {
                  t = ca;
                }
                if (f >= t) {
                  t = f;
                }
                if (t < 4.9896007738368E+291) {
                  if ((absxk <= scale) || rtIsNaN(scale)) {
                    t = absxk;
                  } else {
                    t = scale;
                  }
                  if (r <= t) {
                    t = r;
                  }
                  if (t > 2.0041683600089728E-292) {
                    if (rtIsNaN(((((c + f) + ca) + r) + absxk) + scale)) {
                      exitg1 = 1;
                    } else {
                      f *= 2.0;
                      c *= 2.0;
                      ca *= 2.0;
                      r /= 2.0;
                      absxk /= 2.0;
                      scale /= 2.0;
                    }
                  } else {
                    exitg1 = 2;
                  }
                } else {
                  exitg1 = 2;
                }
              } else {
                exitg1 = 2;
              }
            } while (exitg1 == 0);
            if (exitg1 == 1) {
              exitg2 = 2;
            } else {
              absxk = c / 2.0;
              exitg6 = false;
              while ((!exitg6) && (absxk >= r)) {
                if ((r >= scale) || rtIsNaN(scale)) {
                  t = r;
                } else {
                  t = scale;
                }
                if (t < 4.9896007738368E+291) {
                  if ((f <= c) || rtIsNaN(c)) {
                    u0 = f;
                  } else {
                    u0 = c;
                  }
                  if ((absxk <= ca) || rtIsNaN(ca)) {
                    t = absxk;
                  } else {
                    t = ca;
                  }
                  if (u0 <= t) {
                    t = u0;
                  }
                  if (t > 2.0041683600089728E-292) {
                    f /= 2.0;
                    c /= 2.0;
                    absxk /= 2.0;
                    ca /= 2.0;
                    r *= 2.0;
                    scale *= 2.0;
                  } else {
                    exitg6 = true;
                  }
                } else {
                  exitg6 = true;
                }
              }
              if ((!(c + r >= 0.95 * s)) &&
                  ((!(f < 1.0)) || (!(scale_data[ix] < 1.0)) ||
                   (!(f * scale_data[ix] <= 1.0020841800044864E-292))) &&
                  ((!(f > 1.0)) || (!(scale_data[ix] > 1.0)) ||
                   (!(scale_data[ix] >= 9.9792015476736E+291 / f)))) {
                scale = 1.0 / f;
                scale_data[ix] *= f;
                kend = iy + 1;
                i = (iy + n * (n_tmp - 1)) + 1;
                for (b_k = kend; n < 0 ? b_k >= i : b_k <= i; b_k += n) {
                  A_data[b_k - 1] *= scale;
                }
                i = c_tmp + *ihi;
                for (b_k = c_tmp + 1; b_k <= i; b_k++) {
                  A_data[b_k - 1] *= f;
                }
                converged = false;
              }
              ix++;
            }
          }
        } else {
          exitg2 = 1;
        }
      } while (exitg2 == 0);
      if (exitg2 != 1) {
        exitg3 = true;
      }
    }
  }
  return ilo;
}

/* End of code generation (xzgebal.c) */

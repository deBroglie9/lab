/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: xdlahqr.c
 *
 * MATLAB Coder version            : 23.2
 * C/C++ source code generated on  : 12-Jan-2026 15:07:11
 */

/* Include Files */
#include "xdlahqr.h"
#include "Jacobian_S_rtwutil.h"
#include "rt_nonfinite.h"
#include "xdlanv2.h"
#include "xnrm2.h"
#include <math.h>

/* Function Definitions */
/*
 * Arguments    : int ilo
 *                int ihi
 *                double h_data[]
 *                const int h_size[2]
 *                double wr_data[]
 *                int *wr_size
 *                double wi_data[]
 *                int *wi_size
 * Return Type  : int
 */
int xdlahqr(int ilo, int ihi, double h_data[], const int h_size[2],
            double wr_data[], int *wr_size, double wi_data[], int *wi_size)
{
  double d;
  double h21;
  double h22;
  double rt1r;
  double rt2r;
  double tr;
  double tst;
  int b_i;
  int b_k;
  int c_k;
  int i;
  int info;
  int j;
  int n;
  n = h_size[0];
  *wr_size = h_size[0];
  *wi_size = h_size[0];
  info = 0;
  i = (unsigned char)(ilo - 1);
  for (b_i = 0; b_i < i; b_i++) {
    wr_data[b_i] = h_data[b_i + h_size[0] * b_i];
    wi_data[b_i] = 0.0;
  }
  i = ihi + 1;
  for (b_i = i; b_i <= n; b_i++) {
    wr_data[b_i - 1] = h_data[(b_i + h_size[0] * (b_i - 1)) - 1];
    wi_data[b_i - 1] = 0.0;
  }
  if (ilo == ihi) {
    wr_data[ilo - 1] = h_data[(ilo + h_size[0] * (ilo - 1)) - 1];
    wi_data[ilo - 1] = 0.0;
  } else {
    double smlnum;
    int kdefl;
    int knt;
    boolean_T exitg1;
    i = ihi - 3;
    for (j = ilo; j <= i; j++) {
      knt = j + h_size[0] * (j - 1);
      h_data[knt + 1] = 0.0;
      h_data[knt + 2] = 0.0;
    }
    if (ilo <= ihi - 2) {
      h_data[(ihi + h_size[0] * (ihi - 3)) - 1] = 0.0;
    }
    smlnum = 2.2250738585072014E-308 *
             ((double)((ihi - ilo) + 1) / 2.2204460492503131E-16);
    kdefl = 0;
    b_i = ihi - 1;
    exitg1 = false;
    while ((!exitg1) && (b_i + 1 >= ilo)) {
      int its;
      int l;
      boolean_T converged;
      boolean_T exitg2;
      l = ilo;
      converged = false;
      its = 0;
      exitg2 = false;
      while ((!exitg2) && (its < 301)) {
        double aa;
        double s;
        int k;
        boolean_T exitg3;
        k = b_i;
        exitg3 = false;
        while ((!exitg3) && (k + 1 > l)) {
          i = k + h_size[0] * (k - 1);
          d = fabs(h_data[i]);
          if (d <= smlnum) {
            exitg3 = true;
          } else {
            knt = k + h_size[0] * k;
            h21 = fabs(h_data[knt]);
            aa = h_data[i - 1];
            tst = fabs(aa) + h21;
            if (tst == 0.0) {
              if (k - 1 >= ilo) {
                tst = fabs(h_data[(k + h_size[0] * (k - 2)) - 1]);
              }
              if (k + 2 <= ihi) {
                tst += fabs(h_data[(k + h_size[0] * k) + 1]);
              }
            }
            if (d <= 2.2204460492503131E-16 * tst) {
              tr = fabs(h_data[knt - 1]);
              tst = fabs(aa - h_data[knt]);
              aa = fmax(h21, tst);
              tst = fmin(h21, tst);
              s = aa + tst;
              if (fmin(d, tr) * (fmax(d, tr) / s) <=
                  fmax(smlnum, 2.2204460492503131E-16 * (tst * (aa / s)))) {
                exitg3 = true;
              } else {
                k--;
              }
            } else {
              k--;
            }
          }
        }
        l = k + 1;
        if (k + 1 > ilo) {
          h_data[k + h_size[0] * (k - 1)] = 0.0;
        }
        if (k + 1 >= b_i) {
          converged = true;
          exitg2 = true;
        } else {
          double v[3];
          int m;
          kdefl++;
          if (kdefl - kdefl / 20 * 20 == 0) {
            s = fabs(h_data[b_i + h_size[0] * (b_i - 1)]) +
                fabs(h_data[(b_i + h_size[0] * (b_i - 2)) - 1]);
            tst = 0.75 * s + h_data[b_i + h_size[0] * b_i];
            aa = -0.4375 * s;
            h21 = s;
            h22 = tst;
          } else if (kdefl - kdefl / 10 * 10 == 0) {
            knt = k + h_size[0] * k;
            s = fabs(h_data[knt + 1]) +
                fabs(h_data[(k + h_size[0] * (k + 1)) + 2]);
            tst = 0.75 * s + h_data[knt];
            aa = -0.4375 * s;
            h21 = s;
            h22 = tst;
          } else {
            knt = b_i + h_size[0] * (b_i - 1);
            tst = h_data[knt - 1];
            h21 = h_data[knt];
            aa = h_data[(b_i + h_size[0] * b_i) - 1];
            h22 = h_data[b_i + h_size[0] * b_i];
          }
          s = ((fabs(tst) + fabs(aa)) + fabs(h21)) + fabs(h22);
          if (s == 0.0) {
            rt1r = 0.0;
            h21 = 0.0;
            rt2r = 0.0;
            aa = 0.0;
          } else {
            tst /= s;
            h21 /= s;
            aa /= s;
            h22 /= s;
            tr = (tst + h22) / 2.0;
            tst = (tst - tr) * (h22 - tr) - aa * h21;
            h21 = sqrt(fabs(tst));
            if (tst >= 0.0) {
              rt1r = tr * s;
              rt2r = rt1r;
              h21 *= s;
              aa = -h21;
            } else {
              rt1r = tr + h21;
              rt2r = tr - h21;
              if (fabs(rt1r - h22) <= fabs(rt2r - h22)) {
                rt1r *= s;
                rt2r = rt1r;
              } else {
                rt2r *= s;
                rt1r = rt2r;
              }
              h21 = 0.0;
              aa = 0.0;
            }
          }
          m = b_i - 1;
          exitg3 = false;
          while ((!exitg3) && (m >= k + 1)) {
            knt = m + h_size[0] * (m - 1);
            tst = h_data[knt];
            tr = h_data[knt - 1];
            h22 = tr - rt2r;
            s = (fabs(h22) + fabs(aa)) + fabs(tst);
            tst /= s;
            knt = m + h_size[0] * m;
            v[0] = (tst * h_data[knt - 1] + h22 * (h22 / s)) - h21 * (aa / s);
            v[1] = tst * (((tr + h_data[knt]) - rt1r) - rt2r);
            v[2] = tst * h_data[knt + 1];
            s = (fabs(v[0]) + fabs(v[1])) + fabs(v[2]);
            v[0] /= s;
            v[1] /= s;
            v[2] /= s;
            if (m == k + 1) {
              exitg3 = true;
            } else {
              i = m + h_size[0] * (m - 2);
              if (fabs(h_data[i - 1]) * (fabs(v[1]) + fabs(v[2])) <=
                  2.2204460492503131E-16 * fabs(v[0]) *
                      ((fabs(h_data[i - 2]) + fabs(tr)) + fabs(h_data[knt]))) {
                exitg3 = true;
              } else {
                m--;
              }
            }
          }
          for (b_k = m; b_k <= b_i; b_k++) {
            int nr;
            knt = (b_i - b_k) + 2;
            if (knt >= 3) {
              nr = 3;
            } else {
              nr = knt;
            }
            if (b_k > m) {
              knt = ((b_k - 2) * n + b_k) - 1;
              for (c_k = 0; c_k < nr; c_k++) {
                v[c_k] = h_data[knt + c_k];
              }
            }
            aa = v[0];
            s = 0.0;
            if (nr > 0) {
              tst = b_xnrm2(nr - 1, v);
              if (tst != 0.0) {
                h21 = rt_hypotd_snf(v[0], tst);
                if (v[0] >= 0.0) {
                  h21 = -h21;
                }
                if (fabs(h21) < 1.0020841800044864E-292) {
                  knt = 0;
                  do {
                    knt++;
                    for (c_k = 2; c_k <= nr; c_k++) {
                      v[c_k - 1] *= 9.9792015476736E+291;
                    }
                    h21 *= 9.9792015476736E+291;
                    aa *= 9.9792015476736E+291;
                  } while ((fabs(h21) < 1.0020841800044864E-292) && (knt < 20));
                  h21 = rt_hypotd_snf(aa, b_xnrm2(nr - 1, v));
                  if (aa >= 0.0) {
                    h21 = -h21;
                  }
                  s = (h21 - aa) / h21;
                  tst = 1.0 / (aa - h21);
                  for (c_k = 2; c_k <= nr; c_k++) {
                    v[c_k - 1] *= tst;
                  }
                  for (c_k = 0; c_k < knt; c_k++) {
                    h21 *= 1.0020841800044864E-292;
                  }
                  aa = h21;
                } else {
                  s = (h21 - v[0]) / h21;
                  tst = 1.0 / (v[0] - h21);
                  for (c_k = 2; c_k <= nr; c_k++) {
                    v[c_k - 1] *= tst;
                  }
                  aa = h21;
                }
              }
            }
            if (b_k > m) {
              h_data[(b_k + h_size[0] * (b_k - 2)) - 1] = aa;
              i = b_k + h_size[0] * (b_k - 2);
              h_data[i] = 0.0;
              if (b_k < b_i) {
                h_data[i + 1] = 0.0;
              }
            } else if (m > k + 1) {
              h_data[(b_k + h_size[0] * (b_k - 2)) - 1] *= 1.0 - s;
            }
            d = v[1];
            tst = s * v[1];
            if (nr == 3) {
              tr = v[2];
              aa = s * v[2];
              for (j = b_k; j <= b_i + 1; j++) {
                i = b_k + h_size[0] * (j - 1);
                h22 = h_data[i - 1];
                rt2r = h_data[i];
                rt1r = h_data[i + 1];
                h21 = (h22 + d * rt2r) + tr * rt1r;
                h22 -= h21 * s;
                h_data[i - 1] = h22;
                rt2r -= h21 * tst;
                h_data[i] = rt2r;
                rt1r -= h21 * aa;
                h_data[i + 1] = rt1r;
              }
              if (b_k + 3 <= b_i + 1) {
                i = b_k;
              } else {
                i = b_i - 2;
              }
              for (j = k + 1; j <= i + 3; j++) {
                knt = (j + h_size[0] * (b_k - 1)) - 1;
                h22 = h_data[knt];
                nr = (j + h_size[0] * b_k) - 1;
                rt2r = h_data[nr];
                c_k = (j + h_size[0] * (b_k + 1)) - 1;
                rt1r = h_data[c_k];
                h21 = (h22 + d * rt2r) + tr * rt1r;
                h22 -= h21 * s;
                h_data[knt] = h22;
                rt2r -= h21 * tst;
                h_data[nr] = rt2r;
                rt1r -= h21 * aa;
                h_data[c_k] = rt1r;
              }
            } else if (nr == 2) {
              for (j = b_k; j <= b_i + 1; j++) {
                i = b_k + h_size[0] * (j - 1);
                tr = h_data[i - 1];
                h22 = h_data[i];
                h21 = tr + d * h22;
                tr -= h21 * s;
                h_data[i - 1] = tr;
                h22 -= h21 * tst;
                h_data[i] = h22;
              }
              for (j = k + 1; j <= b_i + 1; j++) {
                i = (j + h_size[0] * (b_k - 1)) - 1;
                tr = h_data[i];
                knt = (j + h_size[0] * b_k) - 1;
                h22 = h_data[knt];
                h21 = tr + d * h22;
                tr -= h21 * s;
                h_data[i] = tr;
                h22 -= h21 * tst;
                h_data[knt] = h22;
              }
            }
          }
          its++;
        }
      }
      if (!converged) {
        info = b_i + 1;
        exitg1 = true;
      } else {
        if (l == b_i + 1) {
          wr_data[b_i] = h_data[b_i + h_size[0] * b_i];
          wi_data[b_i] = 0.0;
        } else if (l == b_i) {
          i = b_i + h_size[0] * b_i;
          d = h_data[i - 1];
          knt = b_i + h_size[0] * (b_i - 1);
          tr = h_data[knt];
          h22 = h_data[i];
          wr_data[b_i - 1] =
              xdlanv2(&h_data[(b_i + h_size[0] * (b_i - 1)) - 1], &d, &tr, &h22,
                      &wi_data[b_i - 1], &rt2r, &rt1r, &tst, &h21);
          wr_data[b_i] = rt2r;
          wi_data[b_i] = rt1r;
          h_data[i - 1] = d;
          h_data[knt] = tr;
          h_data[i] = h22;
        }
        kdefl = 0;
        b_i = l - 2;
      }
    }
    if ((info != 0) && (n > 2)) {
      for (j = 3; j <= n; j++) {
        for (b_i = j; b_i <= n; b_i++) {
          h_data[(b_i + h_size[0] * (j - 3)) - 1] = 0.0;
        }
      }
    }
  }
  return info;
}

/*
 * File trailer for xdlahqr.c
 *
 * [EOF]
 */

/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * xdlahqr.c
 *
 * Code generation for function 'xdlahqr'
 *
 */

/* Include files */
#include "xdlahqr.h"
#include "rt_nonfinite.h"
#include "xdlanv2.h"
#include "xzlarfg.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */
int xdlahqr(int ilo, int ihi, double h_data[], const int h_size[2],
            double wr_data[], int *wr_size, double wi_data[], int *wi_size)
{
  double v[3];
  double aa;
  double d;
  double h12;
  double h22;
  double rt1r;
  double rt2r;
  double s;
  double smlnum;
  double tr;
  double tst;
  int b_i;
  int b_k;
  int c_k;
  int i;
  int info;
  int its;
  int j;
  int k;
  int kdefl;
  int l;
  int m;
  int n;
  int nr;
  int u0_tmp;
  boolean_T aa_tmp;
  boolean_T converged;
  boolean_T exitg1;
  boolean_T exitg2;
  boolean_T exitg3;
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
    i = ihi - 3;
    for (j = ilo; j <= i; j++) {
      u0_tmp = j + h_size[0] * (j - 1);
      h_data[u0_tmp + 1] = 0.0;
      h_data[u0_tmp + 2] = 0.0;
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
      l = ilo;
      converged = false;
      its = 0;
      exitg2 = false;
      while ((!exitg2) && (its < 301)) {
        k = b_i;
        exitg3 = false;
        while ((!exitg3) && (k + 1 > l)) {
          u0_tmp = k + h_size[0] * (k - 1);
          h22 = fabs(h_data[u0_tmp]);
          if (h22 <= smlnum) {
            exitg3 = true;
          } else {
            nr = k + h_size[0] * k;
            h12 = fabs(h_data[nr]);
            aa = h_data[u0_tmp - 1];
            tst = fabs(aa) + h12;
            if (tst == 0.0) {
              if (k - 1 >= ilo) {
                tst = fabs(h_data[(k + h_size[0] * (k - 2)) - 1]);
              }
              if (k + 2 <= ihi) {
                tst += fabs(h_data[(k + h_size[0] * k) + 1]);
              }
            }
            if (h22 <= 2.2204460492503131E-16 * tst) {
              tr = fabs(h_data[nr - 1]);
              tst = fabs(aa - h_data[nr]);
              aa_tmp = rtIsNaN(tst);
              if ((h12 >= tst) || aa_tmp) {
                aa = h12;
              } else {
                aa = tst;
              }
              if ((h12 <= tst) || aa_tmp) {
                tst = h12;
              }
              s = aa + tst;
              tst = 2.2204460492503131E-16 * (tst * (aa / s));
              aa_tmp = rtIsNaN(tr);
              if ((h22 <= tr) || aa_tmp) {
                d = h22;
              } else {
                d = tr;
              }
              if ((h22 >= tr) || aa_tmp) {
                tr = h22;
              }
              if ((smlnum >= tst) || rtIsNaN(tst)) {
                tst = smlnum;
              }
              if (d * (tr / s) <= tst) {
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
          kdefl++;
          if (kdefl - kdefl / 20 * 20 == 0) {
            s = fabs(h_data[b_i + h_size[0] * (b_i - 1)]) +
                fabs(h_data[(b_i + h_size[0] * (b_i - 2)) - 1]);
            tst = 0.75 * s + h_data[b_i + h_size[0] * b_i];
            h12 = -0.4375 * s;
            aa = s;
            h22 = tst;
          } else if (kdefl - kdefl / 10 * 10 == 0) {
            u0_tmp = k + h_size[0] * k;
            s = fabs(h_data[u0_tmp + 1]) +
                fabs(h_data[(k + h_size[0] * (k + 1)) + 2]);
            tst = 0.75 * s + h_data[u0_tmp];
            h12 = -0.4375 * s;
            aa = s;
            h22 = tst;
          } else {
            u0_tmp = b_i + h_size[0] * (b_i - 1);
            tst = h_data[u0_tmp - 1];
            aa = h_data[u0_tmp];
            h12 = h_data[(b_i + h_size[0] * b_i) - 1];
            h22 = h_data[b_i + h_size[0] * b_i];
          }
          s = ((fabs(tst) + fabs(h12)) + fabs(aa)) + fabs(h22);
          if (s == 0.0) {
            rt1r = 0.0;
            h12 = 0.0;
            rt2r = 0.0;
            aa = 0.0;
          } else {
            tst /= s;
            aa /= s;
            h12 /= s;
            h22 /= s;
            tr = (tst + h22) / 2.0;
            tst = (tst - tr) * (h22 - tr) - h12 * aa;
            h12 = sqrt(fabs(tst));
            if (tst >= 0.0) {
              rt1r = tr * s;
              rt2r = rt1r;
              h12 *= s;
              aa = -h12;
            } else {
              rt1r = tr + h12;
              rt2r = tr - h12;
              if (fabs(rt1r - h22) <= fabs(rt2r - h22)) {
                rt1r *= s;
                rt2r = rt1r;
              } else {
                rt2r *= s;
                rt1r = rt2r;
              }
              h12 = 0.0;
              aa = 0.0;
            }
          }
          m = b_i - 1;
          exitg3 = false;
          while ((!exitg3) && (m >= k + 1)) {
            u0_tmp = m + h_size[0] * (m - 1);
            tst = h_data[u0_tmp];
            tr = h_data[u0_tmp - 1];
            h22 = tr - rt2r;
            s = (fabs(h22) + fabs(aa)) + fabs(tst);
            tst /= s;
            u0_tmp = m + h_size[0] * m;
            v[0] =
                (tst * h_data[u0_tmp - 1] + h22 * (h22 / s)) - h12 * (aa / s);
            v[1] = tst * (((tr + h_data[u0_tmp]) - rt1r) - rt2r);
            v[2] = tst * h_data[u0_tmp + 1];
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
                      ((fabs(h_data[i - 2]) + fabs(tr)) +
                       fabs(h_data[u0_tmp]))) {
                exitg3 = true;
              } else {
                m--;
              }
            }
          }
          for (b_k = m; b_k <= b_i; b_k++) {
            u0_tmp = (b_i - b_k) + 2;
            if (u0_tmp >= 3) {
              nr = 3;
            } else {
              nr = u0_tmp;
            }
            if (b_k > m) {
              u0_tmp = ((b_k - 2) * n + b_k) - 1;
              for (c_k = 0; c_k < nr; c_k++) {
                v[c_k] = h_data[u0_tmp + c_k];
              }
            }
            tst = v[0];
            tr = xzlarfg(nr, &tst, v);
            if (b_k > m) {
              h_data[(b_k + h_size[0] * (b_k - 2)) - 1] = tst;
              i = b_k + h_size[0] * (b_k - 2);
              h_data[i] = 0.0;
              if (b_k < b_i) {
                h_data[i + 1] = 0.0;
              }
            } else if (m > k + 1) {
              h_data[(b_k + h_size[0] * (b_k - 2)) - 1] *= 1.0 - tr;
            }
            h22 = v[1];
            tst = tr * v[1];
            if (nr == 3) {
              rt2r = v[2];
              aa = tr * v[2];
              for (j = b_k; j <= b_i + 1; j++) {
                i = b_k + h_size[0] * (j - 1);
                rt1r = h_data[i - 1];
                s = h_data[i];
                d = h_data[i + 1];
                h12 = (rt1r + h22 * s) + rt2r * d;
                rt1r -= h12 * tr;
                h_data[i - 1] = rt1r;
                s -= h12 * tst;
                h_data[i] = s;
                d -= h12 * aa;
                h_data[i + 1] = d;
              }
              if (b_k + 3 <= b_i + 1) {
                i = b_k;
              } else {
                i = b_i - 2;
              }
              for (j = k + 1; j <= i + 3; j++) {
                u0_tmp = (j + h_size[0] * (b_k - 1)) - 1;
                rt1r = h_data[u0_tmp];
                nr = (j + h_size[0] * b_k) - 1;
                s = h_data[nr];
                c_k = (j + h_size[0] * (b_k + 1)) - 1;
                d = h_data[c_k];
                h12 = (rt1r + h22 * s) + rt2r * d;
                rt1r -= h12 * tr;
                h_data[u0_tmp] = rt1r;
                s -= h12 * tst;
                h_data[nr] = s;
                d -= h12 * aa;
                h_data[c_k] = d;
              }
            } else if (nr == 2) {
              for (j = b_k; j <= b_i + 1; j++) {
                i = b_k + h_size[0] * (j - 1);
                rt2r = h_data[i - 1];
                rt1r = h_data[i];
                h12 = rt2r + h22 * rt1r;
                rt2r -= h12 * tr;
                h_data[i - 1] = rt2r;
                rt1r -= h12 * tst;
                h_data[i] = rt1r;
              }
              for (j = k + 1; j <= b_i + 1; j++) {
                i = (j + h_size[0] * (b_k - 1)) - 1;
                rt2r = h_data[i];
                u0_tmp = (j + h_size[0] * b_k) - 1;
                rt1r = h_data[u0_tmp];
                h12 = rt2r + h22 * rt1r;
                rt2r -= h12 * tr;
                h_data[i] = rt2r;
                rt1r -= h12 * tst;
                h_data[u0_tmp] = rt1r;
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
          h22 = h_data[i - 1];
          u0_tmp = b_i + h_size[0] * (b_i - 1);
          rt2r = h_data[u0_tmp];
          rt1r = h_data[i];
          wr_data[b_i - 1] =
              xdlanv2(&h_data[(b_i + h_size[0] * (b_i - 1)) - 1], &h22, &rt2r,
                      &rt1r, &wi_data[b_i - 1], &s, &d, &tst, &h12);
          wr_data[b_i] = s;
          wi_data[b_i] = d;
          h_data[i - 1] = h22;
          h_data[u0_tmp] = rt2r;
          h_data[i] = rt1r;
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

/* End of code generation (xdlahqr.c) */

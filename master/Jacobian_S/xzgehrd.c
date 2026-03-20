/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: xzgehrd.c
 *
 * MATLAB Coder version            : 23.2
 * C/C++ source code generated on  : 12-Jan-2026 15:07:11
 */

/* Include Files */
#include "xzgehrd.h"
#include "Jacobian_S_rtwutil.h"
#include "rt_nonfinite.h"
#include "xnrm2.h"
#include <math.h>
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : double a_data[]
 *                const int a_size[2]
 *                int ilo
 *                int ihi
 * Return Type  : void
 */
void xzgehrd(double a_data[], const int a_size[2], int ilo, int ihi)
{
  double work_data[8];
  double tau_data[7];
  int b_i;
  int b_lastv;
  int ia;
  int iac;
  int im1n_tmp;
  int knt;
  int n;
  int ntau;
  n = a_size[0];
  ntau = a_size[0] - 1;
  if ((ihi - ilo) + 1 > 1) {
    int i;
    i = (unsigned char)(ilo - 1);
    if (i - 1 >= 0) {
      memset(&tau_data[0], 0, (unsigned int)i * sizeof(double));
    }
    if (ihi <= ntau) {
      memset(&tau_data[ihi + -1], 0,
             (unsigned int)((ntau - ihi) + 1) * sizeof(double));
    }
    ntau = a_size[0];
    if (ntau - 1 >= 0) {
      memset(&work_data[0], 0, (unsigned int)ntau * sizeof(double));
    }
    i = ihi - 1;
    for (b_i = ilo; b_i <= i; b_i++) {
      double alpha1;
      double beta1;
      double d;
      double temp;
      int alpha1_tmp;
      int exitg1;
      int i1;
      int i2;
      int in;
      int iv0_tmp;
      int jA;
      int lastc;
      int lastv;
      boolean_T exitg2;
      im1n_tmp = (b_i - 1) * n;
      in = b_i * n;
      alpha1_tmp = b_i + a_size[0] * (b_i - 1);
      alpha1 = a_data[alpha1_tmp];
      ntau = b_i + 2;
      if (ntau > n) {
        ntau = n;
      }
      ntau += im1n_tmp;
      lastv = ihi - b_i;
      tau_data[b_i - 1] = 0.0;
      if (lastv > 0) {
        temp = xnrm2(lastv - 1, a_data, ntau);
        if (temp != 0.0) {
          beta1 = rt_hypotd_snf(alpha1, temp);
          if (alpha1 >= 0.0) {
            beta1 = -beta1;
          }
          if (fabs(beta1) < 1.0020841800044864E-292) {
            knt = 0;
            i1 = (ntau + lastv) - 2;
            do {
              knt++;
              for (b_lastv = ntau; b_lastv <= i1; b_lastv++) {
                a_data[b_lastv - 1] *= 9.9792015476736E+291;
              }
              beta1 *= 9.9792015476736E+291;
              alpha1 *= 9.9792015476736E+291;
            } while ((fabs(beta1) < 1.0020841800044864E-292) && (knt < 20));
            beta1 = rt_hypotd_snf(alpha1, xnrm2(lastv - 1, a_data, ntau));
            if (alpha1 >= 0.0) {
              beta1 = -beta1;
            }
            tau_data[b_i - 1] = (beta1 - alpha1) / beta1;
            temp = 1.0 / (alpha1 - beta1);
            for (b_lastv = ntau; b_lastv <= i1; b_lastv++) {
              a_data[b_lastv - 1] *= temp;
            }
            for (b_lastv = 0; b_lastv < knt; b_lastv++) {
              beta1 *= 1.0020841800044864E-292;
            }
            alpha1 = beta1;
          } else {
            tau_data[b_i - 1] = (beta1 - alpha1) / beta1;
            temp = 1.0 / (alpha1 - beta1);
            i1 = (ntau + lastv) - 2;
            for (b_lastv = ntau; b_lastv <= i1; b_lastv++) {
              a_data[b_lastv - 1] *= temp;
            }
            alpha1 = beta1;
          }
        }
      }
      a_data[alpha1_tmp] = 1.0;
      iv0_tmp = b_i + im1n_tmp;
      im1n_tmp = in + 1;
      d = tau_data[b_i - 1];
      if (d != 0.0) {
        b_lastv = lastv;
        ntau = iv0_tmp + lastv;
        while ((b_lastv > 0) && (a_data[ntau - 1] == 0.0)) {
          b_lastv--;
          ntau--;
        }
        lastc = ihi;
        exitg2 = false;
        while ((!exitg2) && (lastc > 0)) {
          ntau = in + lastc;
          ia = ntau;
          do {
            exitg1 = 0;
            if ((n > 0) && (ia <= ntau + (b_lastv - 1) * n)) {
              if (a_data[ia - 1] != 0.0) {
                exitg1 = 1;
              } else {
                ia += n;
              }
            } else {
              lastc--;
              exitg1 = 2;
            }
          } while (exitg1 == 0);
          if (exitg1 == 1) {
            exitg2 = true;
          }
        }
      } else {
        b_lastv = 0;
        lastc = 0;
      }
      if (b_lastv > 0) {
        if (lastc != 0) {
          i1 = (unsigned char)lastc;
          memset(&work_data[0], 0, (unsigned int)i1 * sizeof(double));
          ntau = iv0_tmp;
          i1 = (in + n * (b_lastv - 1)) + 1;
          for (iac = im1n_tmp; n < 0 ? iac >= i1 : iac <= i1; iac += n) {
            i2 = (iac + lastc) - 1;
            for (ia = iac; ia <= i2; ia++) {
              knt = ia - iac;
              work_data[knt] += a_data[ia - 1] * a_data[ntau];
            }
            ntau++;
          }
        }
        if (!(-d == 0.0)) {
          jA = in;
          i1 = (unsigned char)b_lastv;
          for (knt = 0; knt < i1; knt++) {
            temp = a_data[iv0_tmp + knt];
            if (temp != 0.0) {
              temp *= -d;
              i2 = jA + 1;
              ntau = lastc + jA;
              for (im1n_tmp = i2; im1n_tmp <= ntau; im1n_tmp++) {
                a_data[im1n_tmp - 1] += work_data[(im1n_tmp - jA) - 1] * temp;
              }
            }
            jA += n;
          }
        }
      }
      jA = (b_i + in) + 1;
      if (d != 0.0) {
        ntau = iv0_tmp + lastv;
        while ((lastv > 0) && (a_data[ntau - 1] == 0.0)) {
          lastv--;
          ntau--;
        }
        lastc = (n - b_i) - 1;
        exitg2 = false;
        while ((!exitg2) && (lastc + 1 > 0)) {
          ntau = jA + lastc * n;
          ia = ntau;
          do {
            exitg1 = 0;
            if (ia <= (ntau + lastv) - 1) {
              if (a_data[ia - 1] != 0.0) {
                exitg1 = 1;
              } else {
                ia++;
              }
            } else {
              lastc--;
              exitg1 = 2;
            }
          } while (exitg1 == 0);
          if (exitg1 == 1) {
            exitg2 = true;
          }
        }
      } else {
        lastv = 0;
        lastc = -1;
      }
      if (lastv > 0) {
        if (lastc + 1 != 0) {
          if (lastc >= 0) {
            memset(&work_data[0], 0,
                   (unsigned int)(lastc + 1) * sizeof(double));
          }
          ntau = 0;
          i1 = jA + n * lastc;
          for (iac = jA; n < 0 ? iac >= i1 : iac <= i1; iac += n) {
            beta1 = 0.0;
            i2 = (iac + lastv) - 1;
            for (ia = iac; ia <= i2; ia++) {
              beta1 += a_data[ia - 1] * a_data[(iv0_tmp + ia) - iac];
            }
            work_data[ntau] += beta1;
            ntau++;
          }
        }
        if (!(-d == 0.0)) {
          for (knt = 0; knt <= lastc; knt++) {
            temp = work_data[knt];
            if (temp != 0.0) {
              temp *= -d;
              i1 = lastv + jA;
              for (im1n_tmp = jA; im1n_tmp < i1; im1n_tmp++) {
                a_data[im1n_tmp - 1] +=
                    a_data[(iv0_tmp + im1n_tmp) - jA] * temp;
              }
            }
            jA += n;
          }
        }
      }
      a_data[alpha1_tmp] = alpha1;
    }
  }
}

/*
 * File trailer for xzgehrd.c
 *
 * [EOF]
 */

/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * roots.c
 *
 * Code generation for function 'roots'
 *
 */

/* Include files */
#include "roots.h"
#include "rt_nonfinite.h"
#include "xdlahqr.h"
#include "xzgebal.h"
#include "xzgehrd.h"
#include "xzlascl.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

/* Function Definitions */
int roots(const double c[9], creal_T r_data[])
{
  creal_T eiga_data[8];
  double A_data[64];
  double a_data[64];
  double ctmp[9];
  double wi_data[8];
  double wr_data[8];
  double absxk;
  double anrm;
  double cfrom1;
  double cfromc;
  double cto1;
  double ctoc;
  double mul;
  int A_size[2];
  int b_i;
  int companDim;
  int i;
  int j;
  int k1;
  int k2;
  int loop_ub_tmp;
  int nTrailingZeros;
  int r_size;
  boolean_T exitg1;
  boolean_T exitg2;
  boolean_T guard1;
  boolean_T notdone;
  boolean_T scalea;
  memset(&r_data[0], 0, 8U * sizeof(creal_T));
  k1 = 1;
  while ((k1 <= 9) && (!(c[k1 - 1] != 0.0))) {
    k1++;
  }
  k2 = 9;
  while ((k2 >= k1) && (!(c[k2 - 1] != 0.0))) {
    k2--;
  }
  nTrailingZeros = 8 - k2;
  if (k1 < k2) {
    companDim = k2 - k1;
    exitg1 = false;
    while ((!exitg1) && (companDim > 0)) {
      j = 0;
      exitg2 = false;
      while ((!exitg2) && (j + 1 <= companDim)) {
        ctmp[j] = c[k1 + j] / c[k1 - 1];
        if (rtIsInf(fabs(ctmp[j]))) {
          exitg2 = true;
        } else {
          j++;
        }
      }
      if (j + 1 > companDim) {
        exitg1 = true;
      } else {
        k1++;
        companDim--;
      }
    }
    if (companDim < 1) {
      r_size = 9 - k2;
    } else {
      loop_ub_tmp = companDim * companDim;
      memset(&a_data[0], 0, (unsigned int)loop_ub_tmp * sizeof(double));
      for (k1 = 0; k1 <= companDim - 2; k1++) {
        j = companDim * k1;
        a_data[j] = -ctmp[k1];
        a_data[(k1 + j) + 1] = 1.0;
      }
      a_data[companDim * (companDim - 1)] = -ctmp[companDim - 1];
      if (nTrailingZeros >= 0) {
        memset(&r_data[0], 0,
               (unsigned int)(nTrailingZeros + 1) * sizeof(creal_T));
      }
      if (companDim == 1) {
        for (i = 0; i < companDim; i++) {
          eiga_data[i].re = a_data[i];
          eiga_data[i].im = 0.0;
        }
      } else {
        anrm = 0.0;
        k1 = 0;
        exitg1 = false;
        while ((!exitg1) && (k1 <= loop_ub_tmp - 1)) {
          absxk = fabs(a_data[k1]);
          if (rtIsNaN(absxk)) {
            anrm = rtNaN;
            exitg1 = true;
          } else {
            if (absxk > anrm) {
              anrm = absxk;
            }
            k1++;
          }
        }
        if (rtIsInf(anrm) || rtIsNaN(anrm)) {
          for (i = 0; i < companDim; i++) {
            eiga_data[i].re = rtNaN;
            eiga_data[i].im = 0.0;
          }
        } else {
          absxk = anrm;
          scalea = false;
          guard1 = false;
          if ((anrm > 0.0) && (anrm < 6.7178761075670888E-139)) {
            scalea = true;
            absxk = 6.7178761075670888E-139;
            guard1 = true;
          } else if (anrm > 1.4885657073574029E+138) {
            scalea = true;
            absxk = 1.4885657073574029E+138;
            guard1 = true;
          }
          if (guard1) {
            cfromc = anrm;
            ctoc = absxk;
            notdone = true;
            while (notdone) {
              cfrom1 = cfromc * 2.0041683600089728E-292;
              cto1 = ctoc / 4.9896007738368E+291;
              if ((cfrom1 > ctoc) && (ctoc != 0.0)) {
                mul = 2.0041683600089728E-292;
                cfromc = cfrom1;
              } else if (cto1 > cfromc) {
                mul = 4.9896007738368E+291;
                ctoc = cto1;
              } else {
                mul = ctoc / cfromc;
                notdone = false;
              }
              for (j = 0; j < companDim; j++) {
                k1 = j * companDim - 1;
                for (b_i = 0; b_i < companDim; b_i++) {
                  i = (k1 + b_i) + 1;
                  a_data[i] *= mul;
                }
              }
            }
          }
          A_size[0] = companDim;
          A_size[1] = companDim;
          memcpy(&A_data[0], &a_data[0],
                 (unsigned int)loop_ub_tmp * sizeof(double));
          nTrailingZeros = xzgebal(A_data, A_size, &k1, wr_data, &loop_ub_tmp);
          xzgehrd(A_data, A_size, nTrailingZeros, k1);
          k1 = xdlahqr(nTrailingZeros, k1, A_data, A_size, wr_data,
                       &loop_ub_tmp, wi_data, &j);
          if (scalea) {
            i = companDim - k1;
            xzlascl(absxk, anrm, i, wr_data, k1 + 1);
            xzlascl(absxk, anrm, i, wi_data, k1 + 1);
            if (k1 != 0) {
              xzlascl(absxk, anrm, nTrailingZeros - 1, wr_data, 1);
              xzlascl(absxk, anrm, nTrailingZeros - 1, wi_data, 1);
            }
          }
          if (k1 != 0) {
            for (b_i = nTrailingZeros; b_i <= k1; b_i++) {
              wr_data[b_i - 1] = rtNaN;
              wi_data[b_i - 1] = 0.0;
            }
          }
          for (i = 0; i < loop_ub_tmp; i++) {
            eiga_data[i].re = wr_data[i];
            eiga_data[i].im = wi_data[i];
          }
        }
      }
      for (k1 = 0; k1 < companDim; k1++) {
        r_data[(k1 - k2) + 9] = eiga_data[k1];
      }
      r_size = (companDim - k2) + 9;
    }
  } else {
    r_size = 9 - k2;
  }
  return r_size;
}

/* End of code generation (roots.c) */

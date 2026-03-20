/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * xzlarf.c
 *
 * Code generation for function 'xzlarf'
 *
 */

/* Include files */
#include "xzlarf.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void xzlarf(int iv0, double tau, double C[8], int ic0, double work[2])
{
  double c;
  int b_i;
  int exitg1;
  int i;
  int iac;
  int ijA;
  int lastc;
  int lastv;
  if (tau != 0.0) {
    lastv = 4;
    i = iv0 + 4;
    while ((lastv > 0) && (C[i - 2] == 0.0)) {
      lastv--;
      i--;
    }
    lastc = 1;
    i = ic0;
    do {
      exitg1 = 0;
      if (i <= (ic0 + lastv) - 1) {
        if (C[i - 1] != 0.0) {
          exitg1 = 1;
        } else {
          i++;
        }
      } else {
        lastc = 0;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  } else {
    lastv = 0;
    lastc = 0;
  }
  if (lastv > 0) {
    if (lastc != 0) {
      work[0] = 0.0;
      for (iac = ic0; iac <= ic0; iac += 4) {
        c = 0.0;
        b_i = (iac + lastv) - 1;
        for (i = iac; i <= b_i; i++) {
          c += C[i - 1] * C[((iv0 + i) - iac) - 1];
        }
        b_i = (iac - ic0) >> 2;
        work[b_i] += c;
      }
    }
    if (!(-tau == 0.0)) {
      i = ic0;
      for (iac = 0; iac < lastc; iac++) {
        c = work[0];
        if (c != 0.0) {
          c *= -tau;
          b_i = lastv + i;
          for (ijA = i; ijA < b_i; ijA++) {
            C[ijA - 1] += C[((iv0 + ijA) - i) - 1] * c;
          }
        }
        i += 4;
      }
    }
  }
}

/* End of code generation (xzlarf.c) */

/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * linearLeastSquares.c
 *
 * Code generation for function 'linearLeastSquares'
 *
 */

/* Include files */
#include "linearLeastSquares.h"
#include "rt_nonfinite.h"
#include "xnrm2.h"
#include "xzlarf.h"
#include "xzlarfg.h"
#include <math.h>
#include <string.h>

/* Function Definitions */
void linearLeastSquares(double lhs[8], double rhs[4], double dx[2])
{
  double jpvt[2];
  double vn1[2];
  double vn2[2];
  double work[2];
  double temp;
  double temp2;
  int b_i;
  int i;
  int ii;
  int ip1;
  int ix;
  int iy;
  int nfxd;
  jpvt[0] = 0.0;
  jpvt[1] = 0.0;
  nfxd = 0;
  for (ii = 0; ii < 2; ii++) {
    if (jpvt[ii] != 0.0) {
      nfxd++;
      if (ii + 1 != nfxd) {
        ix = ii << 2;
        iy = (nfxd - 1) << 2;
        temp = lhs[ix];
        lhs[ix] = lhs[iy];
        lhs[iy] = temp;
        temp = lhs[ix + 1];
        lhs[ix + 1] = lhs[iy + 1];
        lhs[iy + 1] = temp;
        temp = lhs[ix + 2];
        lhs[ix + 2] = lhs[iy + 2];
        lhs[iy + 2] = temp;
        temp = lhs[ix + 3];
        lhs[ix + 3] = lhs[iy + 3];
        lhs[iy + 3] = temp;
        jpvt[ii] = jpvt[nfxd - 1];
        jpvt[nfxd - 1] = (double)ii + 1.0;
      } else {
        jpvt[ii] = (double)ii + 1.0;
      }
    } else {
      jpvt[ii] = (double)ii + 1.0;
    }
    dx[ii] = 0.0;
    work[ii] = 0.0;
  }
  for (i = 0; i < nfxd; i++) {
    ii = (i << 2) + i;
    temp = lhs[ii];
    dx[i] = b_xzlarfg(4 - i, &temp, lhs, ii + 2);
    lhs[ii] = temp;
    if (i + 1 < 2) {
      lhs[ii] = 1.0;
      xzlarf(ii + 1, dx[0], lhs, ii + 5, work);
      lhs[ii] = temp;
    }
  }
  if (nfxd < 2) {
    work[0] = 0.0;
    vn1[0] = 0.0;
    vn2[0] = 0.0;
    work[1] = 0.0;
    vn1[1] = 0.0;
    vn2[1] = 0.0;
    b_i = nfxd + 1;
    for (ii = b_i; ii < 3; ii++) {
      temp = c_xnrm2(4 - nfxd, lhs, (nfxd + ((ii - 1) << 2)) + 1);
      vn1[ii - 1] = temp;
      vn2[ii - 1] = temp;
    }
    for (i = b_i; i < 3; i++) {
      ip1 = i + 1;
      nfxd = (i - 1) << 2;
      ii = (nfxd + i) - 1;
      iy = -1;
      if ((3 - i > 1) && (fabs(vn1[i]) > fabs(vn1[i - 1]))) {
        iy = 0;
      }
      iy += i;
      if (iy + 1 != i) {
        ix = iy << 2;
        temp = lhs[ix];
        lhs[ix] = lhs[nfxd];
        lhs[nfxd] = temp;
        temp = lhs[ix + 1];
        lhs[ix + 1] = lhs[nfxd + 1];
        lhs[nfxd + 1] = temp;
        temp = lhs[ix + 2];
        lhs[ix + 2] = lhs[nfxd + 2];
        lhs[nfxd + 2] = temp;
        temp = lhs[ix + 3];
        lhs[ix + 3] = lhs[nfxd + 3];
        lhs[nfxd + 3] = temp;
        temp = jpvt[iy];
        jpvt[iy] = jpvt[i - 1];
        jpvt[i - 1] = temp;
        vn1[iy] = vn1[i - 1];
        vn2[iy] = vn2[i - 1];
      }
      temp = lhs[ii];
      dx[i - 1] = b_xzlarfg(5 - i, &temp, lhs, ii + 2);
      lhs[ii] = temp;
      if (i < 2) {
        temp = lhs[ii];
        lhs[ii] = 1.0;
        xzlarf(ii + 1, dx[0], lhs, ii + 5, work);
        lhs[ii] = temp;
      }
      for (ii = ip1; ii < 3; ii++) {
        if (vn1[1] != 0.0) {
          temp = fabs(lhs[i + 3]) / vn1[1];
          temp = 1.0 - temp * temp;
          if (temp < 0.0) {
            temp = 0.0;
          }
          temp2 = vn1[1] / vn2[1];
          temp2 = temp * (temp2 * temp2);
          if (temp2 <= 1.4901161193847656E-8) {
            temp = c_xnrm2(4 - i, lhs, i + 5);
            vn1[1] = temp;
            vn2[1] = temp;
          } else {
            vn1[1] *= sqrt(temp);
          }
        }
      }
    }
  }
  for (ii = 0; ii < 2; ii++) {
    if (dx[ii] != 0.0) {
      temp = rhs[ii];
      b_i = ii + 2;
      for (i = b_i; i < 5; i++) {
        temp += lhs[(i + (ii << 2)) - 1] * rhs[i - 1];
      }
      temp *= dx[ii];
      if (temp != 0.0) {
        rhs[ii] -= temp;
        for (i = b_i; i < 5; i++) {
          rhs[i - 1] -= lhs[(i + (ii << 2)) - 1] * temp;
        }
      }
    }
  }
  nfxd = 0;
  temp = 8.8817841970012523E-15 * fabs(lhs[0]);
  while ((nfxd < 2) && (!(fabs(lhs[nfxd + (nfxd << 2)]) <= temp))) {
    nfxd++;
  }
  dx[0] = rhs[0];
  dx[1] = rhs[1];
  if (nfxd != 0) {
    for (ii = nfxd; ii >= 1; ii--) {
      iy = (ii + ((ii - 1) << 2)) - 1;
      dx[ii - 1] /= lhs[iy];
      for (i = 0; i <= ii - 2; i++) {
        dx[0] -= dx[ii - 1] * lhs[iy - 1];
      }
    }
  }
  if (nfxd + 1 > 2) {
    nfxd = 0;
    b_i = 0;
  } else {
    b_i = 2;
  }
  iy = b_i - nfxd;
  if (iy - 1 >= 0) {
    memset(&dx[nfxd], 0, (unsigned int)((iy + nfxd) - nfxd) * sizeof(double));
  }
  work[1] = dx[1];
  dx[(int)jpvt[0] - 1] = dx[0];
  dx[(int)jpvt[1] - 1] = work[1];
}

/* End of code generation (linearLeastSquares.c) */

/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: mrdivide_helper.c
 *
 * MATLAB Coder version            : 23.2
 * C/C++ source code generated on  : 12-Jan-2026 15:07:11
 */

/* Include Files */
#include "mrdivide_helper.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : const double A[9]
 *                const double B[9]
 *                double Y[9]
 * Return Type  : void
 */
void mrdiv(const double A[9], const double B[9], double Y[9])
{
  double b_A[9];
  double Y_tmp;
  double b_Y_tmp;
  double c_Y_tmp;
  double d_Y_tmp;
  int e_Y_tmp;
  int f_Y_tmp;
  int r2;
  int r3;
  memcpy(&b_A[0], &B[0], 9U * sizeof(double));
  r2 = 1;
  r3 = 2;
  b_A[1] = B[1] / B[0];
  b_A[2] = B[2] / B[0];
  b_A[4] = B[4] - b_A[1] * B[3];
  b_A[5] = B[5] - b_A[2] * B[3];
  b_A[7] = B[7] - b_A[1] * B[6];
  b_A[8] = B[8] - b_A[2] * B[6];
  if (fabs(b_A[5]) > fabs(b_A[4])) {
    r2 = 2;
    r3 = 1;
  }
  b_A[r3 + 3] /= b_A[r2 + 3];
  b_A[r3 + 6] -= b_A[r3 + 3] * b_A[r2 + 6];
  Y[0] = A[0] / b_A[0];
  Y[3 * r2] = A[3] - Y[0] * b_A[3];
  Y[3 * r3] = A[6] - Y[0] * b_A[6];
  Y_tmp = b_A[r2 + 3];
  Y[3 * r2] /= Y_tmp;
  b_Y_tmp = b_A[r2 + 6];
  Y[3 * r3] -= Y[3 * r2] * b_Y_tmp;
  c_Y_tmp = b_A[r3 + 6];
  Y[3 * r3] /= c_Y_tmp;
  d_Y_tmp = b_A[r3 + 3];
  Y[3 * r2] -= Y[3 * r3] * d_Y_tmp;
  Y[0] -= Y[3 * r3] * b_A[r3];
  Y[0] -= Y[3 * r2] * b_A[r2];
  Y[1] = A[1] / b_A[0];
  e_Y_tmp = 3 * r2 + 1;
  Y[e_Y_tmp] = A[4] - Y[1] * b_A[3];
  f_Y_tmp = 3 * r3 + 1;
  Y[f_Y_tmp] = A[7] - Y[1] * b_A[6];
  Y[e_Y_tmp] /= Y_tmp;
  Y[f_Y_tmp] -= Y[e_Y_tmp] * b_Y_tmp;
  Y[f_Y_tmp] /= c_Y_tmp;
  Y[e_Y_tmp] -= Y[f_Y_tmp] * d_Y_tmp;
  Y[1] -= Y[f_Y_tmp] * b_A[r3];
  Y[1] -= Y[e_Y_tmp] * b_A[r2];
  Y[2] = A[2] / b_A[0];
  e_Y_tmp = 3 * r2 + 2;
  Y[e_Y_tmp] = A[5] - Y[2] * b_A[3];
  f_Y_tmp = 3 * r3 + 2;
  Y[f_Y_tmp] = A[8] - Y[2] * b_A[6];
  Y[e_Y_tmp] /= Y_tmp;
  Y[f_Y_tmp] -= Y[e_Y_tmp] * b_Y_tmp;
  Y[f_Y_tmp] /= c_Y_tmp;
  Y[e_Y_tmp] -= Y[f_Y_tmp] * d_Y_tmp;
  Y[2] -= Y[f_Y_tmp] * b_A[r3];
  Y[2] -= Y[e_Y_tmp] * b_A[r2];
}

/*
 * File trailer for mrdivide_helper.c
 *
 * [EOF]
 */

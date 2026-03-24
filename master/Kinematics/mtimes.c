/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * mtimes.c
 *
 * Code generation for function 'mtimes'
 *
 */

/* Include files */
#include "mtimes.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void mtimes(const double A[9], const double B[9], double C[9])
{
  double d;
  double d1;
  double d2;
  int aoffset;
  int coffset;
  int i;
  int j;
  for (j = 0; j < 3; j++) {
    coffset = j * 3;
    d = B[j];
    d1 = B[j + 3];
    d2 = B[j + 6];
    for (i = 0; i < 3; i++) {
      aoffset = i * 3;
      C[coffset + i] =
          (A[aoffset] * d + A[aoffset + 1] * d1) + A[aoffset + 2] * d2;
    }
  }
}

/* End of code generation (mtimes.c) */

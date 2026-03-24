/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: combineVectorElements.c
 *
 * MATLAB Coder version            : 23.2
 * C/C++ source code generated on  : 12-Jan-2026 15:07:11
 */

/* Include Files */
#include "combineVectorElements.h"
#include "rt_nonfinite.h"

/* Function Definitions */
/*
 * Arguments    : const boolean_T x_data[]
 *                int x_size
 * Return Type  : int
 */
int combineVectorElements(const boolean_T x_data[], int x_size)
{
  int k;
  int y;
  if (x_size == 0) {
    y = 0;
  } else {
    y = x_data[0];
    for (k = 2; k <= x_size; k++) {
      y += x_data[k - 1];
    }
  }
  return y;
}

/*
 * File trailer for combineVectorElements.c
 *
 * [EOF]
 */

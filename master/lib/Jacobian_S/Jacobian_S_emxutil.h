/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: Jacobian_S_emxutil.h
 *
 * MATLAB Coder version            : 23.2
 * C/C++ source code generated on  : 12-Jan-2026 15:07:11
 */

#ifndef JACOBIAN_S_EMXUTIL_H
#define JACOBIAN_S_EMXUTIL_H

/* Include Files */
#include "Jacobian_S_types.h"
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
extern void emxEnsureCapacity_real_T(emxArray_real_T *emxArray, int oldNumel);

extern void emxFree_real_T(emxArray_real_T **pEmxArray);

extern void emxInit_real_T(emxArray_real_T **pEmxArray);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for Jacobian_S_emxutil.h
 *
 * [EOF]
 */

/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * checkStoppingCriteria.h
 *
 * Code generation for function 'checkStoppingCriteria'
 *
 */

#ifndef CHECKSTOPPINGCRITERIA_H
#define CHECKSTOPPINGCRITERIA_H

/* Include files */
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
int checkStoppingCriteria(const double gradf[2], double relFactor,
                          double funDiff, const double x[2], const double dx[2],
                          int funcCount, boolean_T stepSuccessful, int *iter);

#ifdef __cplusplus
}
#endif

#endif
/* End of code generation (checkStoppingCriteria.h) */

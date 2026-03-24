/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * computeFiniteDifferences.h
 *
 * Code generation for function 'computeFiniteDifferences'
 *
 */

#ifndef COMPUTEFINITEDIFFERENCES_H
#define COMPUTEFINITEDIFFERENCES_H

/* Include files */
#include "FK_7DOF_internal_types.h"
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
boolean_T computeFiniteDifferences(c_struct_T *obj, const double cEqCurrent[2],
                                   double xk[2], double JacCeqTrans[4]);

#ifdef __cplusplus
}
#endif

#endif
/* End of code generation (computeFiniteDifferences.h) */

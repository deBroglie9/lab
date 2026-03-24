/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * finDiffEvalAndChkErr.h
 *
 * Code generation for function 'finDiffEvalAndChkErr'
 *
 */

#ifndef FINDIFFEVALANDCHKERR_H
#define FINDIFFEVALANDCHKERR_H

/* Include files */
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
boolean_T finDiffEvalAndChkErr(double c_obj_nonlin_workspace_fun_work,
                               double d_obj_nonlin_workspace_fun_work,
                               double cEqPlus[2], int dim, double delta,
                               double xk[2], double *fplus);

#ifdef __cplusplus
}
#endif

#endif
/* End of code generation (finDiffEvalAndChkErr.h) */

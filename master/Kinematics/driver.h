/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * driver.h
 *
 * Code generation for function 'driver'
 *
 */

#ifndef DRIVER_H
#define DRIVER_H

/* Include files */
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
double driver(double fun_workspace_c5, double fun_workspace_c6, double x[2],
              double fCurrent[2], double *exitflag, double *output_iterations,
              double *output_funcCount, double *output_stepsize,
              double *output_firstorderopt, char output_algorithm[19],
              double lambda_lower[2], double lambda_upper[2],
              double jacobian[4]);

#ifdef __cplusplus
}
#endif

#endif
/* End of code generation (driver.h) */

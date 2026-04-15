/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * xdlahqr.h
 *
 * Code generation for function 'xdlahqr'
 *
 */

#ifndef XDLAHQR_H
#define XDLAHQR_H

/* Include files */
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
int xdlahqr(int ilo, int ihi, double h_data[], const int h_size[2],
            double wr_data[], int *wr_size, double wi_data[], int *wi_size);

#ifdef __cplusplus
}
#endif

#endif
/* End of code generation (xdlahqr.h) */

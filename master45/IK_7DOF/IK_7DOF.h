/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * IK_7DOF.h
 *
 * Code generation for function 'IK_7DOF'
 *
 */

#ifndef IK_7DOF_H
#define IK_7DOF_H

/* Include files */
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
extern void IK_7DOF(const double R[16], double phi, double l1, double l2,
                    double Px, double Py, double Pz, double *c1, double *c2,
                    double *c3, double *c4, double *c5, double *c6, double *c7);

#ifdef __cplusplus
}
#endif

#endif
/* End of code generation (IK_7DOF.h) */

/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * FK_7DOF_initialize.c
 *
 * Code generation for function 'FK_7DOF_initialize'
 *
 */

/* Include files */
#include "FK_7DOF_initialize.h"
#include "FK_7DOF_data.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void FK_7DOF_initialize(void)
{
  rt_InitInfAndNaN();
  isInitialized_FK_7DOF = true;
}

/* End of code generation (FK_7DOF_initialize.c) */

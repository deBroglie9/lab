/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * IK_7DOF_initialize.c
 *
 * Code generation for function 'IK_7DOF_initialize'
 *
 */

/* Include files */
#include "IK_7DOF_initialize.h"
#include "IK_7DOF_data.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void IK_7DOF_initialize(void)
{
  rt_InitInfAndNaN();
  isInitialized_IK_7DOF = true;
}

/* End of code generation (IK_7DOF_initialize.c) */

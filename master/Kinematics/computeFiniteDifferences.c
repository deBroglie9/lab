/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * computeFiniteDifferences.c
 *
 * Code generation for function 'computeFiniteDifferences'
 *
 */

/* Include files */
#include "computeFiniteDifferences.h"
#include "FK_7DOF_internal_types.h"
#include "finDiffEvalAndChkErr.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */
boolean_T computeFiniteDifferences(c_struct_T *obj, const double cEqCurrent[2],
                                   double xk[2], double JacCeqTrans[4])
{
  double d;
  double deltaX;
  int idx;
  boolean_T evalOK;
  boolean_T exitg1;
  boolean_T guard1;
  evalOK = true;
  obj->numEvals = 0;
  idx = 0;
  exitg1 = false;
  while ((!exitg1) && (idx < 2)) {
    deltaX = fabs(xk[idx]);
    if (!(deltaX >= 1.0)) {
      deltaX = 1.0;
    }
    deltaX *= 1.4901161193847656E-8 * (1.0 - 2.0 * (double)(xk[idx] < 0.0));
    evalOK = finDiffEvalAndChkErr(obj->nonlin.workspace.fun.workspace.c5,
                                  obj->nonlin.workspace.fun.workspace.c6,
                                  obj->cEq_1, idx + 1, deltaX, xk, &d);
    obj->numEvals++;
    guard1 = false;
    if (!evalOK) {
      deltaX = -deltaX;
      evalOK = finDiffEvalAndChkErr(obj->nonlin.workspace.fun.workspace.c5,
                                    obj->nonlin.workspace.fun.workspace.c6,
                                    obj->cEq_1, idx + 1, deltaX, xk, &d);
      obj->numEvals++;
      if (!evalOK) {
        exitg1 = true;
      } else {
        guard1 = true;
      }
    } else {
      guard1 = true;
    }
    if (guard1) {
      JacCeqTrans[idx] = (obj->cEq_1[0] - cEqCurrent[0]) / deltaX;
      JacCeqTrans[idx + 2] = (obj->cEq_1[1] - cEqCurrent[1]) / deltaX;
      idx++;
    }
  }
  return evalOK;
}

/* End of code generation (computeFiniteDifferences.c) */

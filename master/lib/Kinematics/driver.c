/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * driver.c
 *
 * Code generation for function 'driver'
 *
 */

/* Include files */
#include "driver.h"
#include "FK_7DOF_internal_types.h"
#include "checkStoppingCriteria.h"
#include "computeFiniteDifferences.h"
#include "linearLeastSquares.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */
double driver(double fun_workspace_c5, double fun_workspace_c6, double x[2],
              double fCurrent[2], double *exitflag, double *output_iterations,
              double *output_funcCount, double *output_stepsize,
              double *output_firstorderopt, char output_algorithm[19],
              double lambda_lower[2], double lambda_upper[2],
              double jacobian[4])
{
  static const char cv[19] = {'l', 'e', 'v', 'e', 'n', 'b', 'e', 'r', 'g', '-',
                              'm', 'a', 'r', 'q', 'u', 'a', 'r', 'd', 't'};
  c_struct_T FiniteDifferences;
  double augJacobian[8];
  double JacCeqTrans[4];
  double rhs[4];
  double a__3[2];
  double dx[2];
  double fNew[2];
  double f_temp[2];
  double gradf[2];
  double N1_tmp_tmp;
  double N2_tmp_tmp;
  double b_N1_tmp_tmp;
  double b_N2_tmp_tmp;
  double b_f_temp_tmp;
  double b_gamma;
  double c;
  double c_N1_tmp_tmp;
  double c_f_temp_tmp;
  double d_f_temp_tmp;
  double e_f_temp_tmp;
  double f_temp_tmp;
  double firstOrderOpt;
  double funDiff;
  double relFactor;
  double resnorm;
  double resnormNew;
  double sqrtGamma;
  double xp_idx_0;
  double xp_idx_1;
  int b_exitflag;
  int funcCount;
  int ia;
  int iac;
  int iter;
  boolean_T evalOK;
  boolean_T exitg1;
  boolean_T guard1;
  boolean_T stepSuccessful;
  for (b_exitflag = 0; b_exitflag < 19; b_exitflag++) {
    output_algorithm[b_exitflag] = cv[b_exitflag];
  }
  funDiff = rtInf;
  iter = 0;
  N1_tmp_tmp = sin(fun_workspace_c5);
  b_N1_tmp_tmp = cos(fun_workspace_c5);
  c = 1385.6406460551018 * b_N1_tmp_tmp * 0.0;
  f_temp_tmp = 2400.0 * b_N1_tmp_tmp;
  f_temp[0] = (((((((((((((((-2048.0 - 2400.0 * b_N1_tmp_tmp) + 2400.0) -
                           2400.0 * N1_tmp_tmp * 0.0) -
                          4156.9219381653056 * N1_tmp_tmp) -
                         f_temp_tmp) -
                        c) +
                       1385.6406460551018 * N1_tmp_tmp) -
                      800.0 * b_N1_tmp_tmp) -
                     1280.0 * b_N1_tmp_tmp * 0.0) -
                    800.0 * N1_tmp_tmp * 0.0) -
                   1280.0 * N1_tmp_tmp * 0.0 * 0.0) +
                  c) -
                 1385.6406460551018 * N1_tmp_tmp) +
                2217.0250336881627 * b_N1_tmp_tmp * 0.0 * 0.0) -
               2217.0250336881627 * N1_tmp_tmp * 0.0) +
              5248.0;
  N2_tmp_tmp = sin(fun_workspace_c6);
  b_N2_tmp_tmp = cos(fun_workspace_c6);
  c = 1385.6406460551018 * b_N2_tmp_tmp * 0.0;
  b_f_temp_tmp = 2400.0 * b_N2_tmp_tmp;
  f_temp[1] = ((((((((((((((352.0 - 2400.0 * b_N2_tmp_tmp) -
                           2400.0 * N2_tmp_tmp * 0.0) -
                          4156.9219381653056 * N2_tmp_tmp) -
                         b_f_temp_tmp) -
                        c) +
                       1385.6406460551018 * N2_tmp_tmp) -
                      800.0 * b_N2_tmp_tmp) +
                     1280.0 * b_N2_tmp_tmp * 0.0) -
                    800.0 * N2_tmp_tmp * 0.0) +
                   1280.0 * N2_tmp_tmp * 0.0 * 0.0) +
                  c) -
                 1385.6406460551018 * N2_tmp_tmp) -
                2217.0250336881627 * b_N2_tmp_tmp * 0.0 * 0.0) +
               2217.0250336881627 * N2_tmp_tmp * 0.0) +
              5248.0;
  /*  方程 */
  FiniteDifferences.nonlin.workspace.fun.workspace.c5 = fun_workspace_c5;
  FiniteDifferences.nonlin.workspace.fun.workspace.c6 = fun_workspace_c6;
  FiniteDifferences.numEvals = 0;
  dx[0] = rtInf;
  x[0] = 0.0;
  fCurrent[0] = f_temp[0];
  a__3[0] = 0.0;
  dx[1] = rtInf;
  x[1] = 0.0;
  fCurrent[1] = f_temp[1];
  resnorm = f_temp[0] * f_temp[0] + f_temp[1] * f_temp[1];
  a__3[1] = 0.0;
  computeFiniteDifferences(&FiniteDifferences, fCurrent, a__3, JacCeqTrans);
  augJacobian[0] = JacCeqTrans[0];
  augJacobian[1] = JacCeqTrans[2];
  augJacobian[4] = JacCeqTrans[1];
  augJacobian[5] = JacCeqTrans[3];
  funcCount = FiniteDifferences.numEvals + 1;
  jacobian[0] = JacCeqTrans[0];
  jacobian[1] = JacCeqTrans[2];
  jacobian[2] = JacCeqTrans[1];
  jacobian[3] = JacCeqTrans[3];
  b_gamma = 0.01;
  augJacobian[3] = 0.0;
  augJacobian[2] = 0.1;
  gradf[0] = 0.0;
  augJacobian[6] = 0.0;
  augJacobian[7] = 0.1;
  gradf[1] = 0.0;
  for (iac = 0; iac <= 2; iac += 2) {
    c = 0.0;
    b_exitflag = iac + 2;
    for (ia = iac + 1; ia <= b_exitflag; ia++) {
      c += jacobian[ia - 1] * fCurrent[(ia - iac) - 1];
    }
    b_exitflag = iac >> 1;
    gradf[b_exitflag] += c;
  }
  firstOrderOpt = 0.0;
  stepSuccessful = true;
  c = 0.0;
  for (b_exitflag = 0; b_exitflag < 2; b_exitflag++) {
    resnormNew = fabs(gradf[b_exitflag]);
    evalOK = rtIsNaN(resnormNew);
    if (evalOK || (resnormNew > firstOrderOpt)) {
      firstOrderOpt = resnormNew;
    }
    if (evalOK || (resnormNew > c)) {
      c = resnormNew;
    }
  }
  if (firstOrderOpt >= 1.0) {
    relFactor = firstOrderOpt;
  } else {
    relFactor = 1.0;
  }
  if (c <= 1.0E-10 * relFactor) {
    b_exitflag = 1;
  } else if (FiniteDifferences.numEvals + 1 >= 400) {
    b_exitflag = 0;
  } else {
    b_exitflag = -5;
  }
  exitg1 = false;
  while ((!exitg1) && (b_exitflag == -5)) {
    rhs[0] = -fCurrent[0];
    rhs[2] = 0.0;
    rhs[1] = -fCurrent[1];
    rhs[3] = 0.0;
    linearLeastSquares(augJacobian, rhs, dx);
    xp_idx_0 = x[0] + dx[0];
    xp_idx_1 = x[1] + dx[1];
    sqrtGamma = cos(xp_idx_0);
    firstOrderOpt = cos(xp_idx_1);
    resnormNew = sin(xp_idx_0);
    c_N1_tmp_tmp = sin(xp_idx_1);
    c = 2400.0 * firstOrderOpt * sqrtGamma;
    c_f_temp_tmp = 3840.0 * firstOrderOpt * resnormNew;
    d_f_temp_tmp = 1385.6406460551018 * firstOrderOpt;
    e_f_temp_tmp = d_f_temp_tmp * sqrtGamma;
    f_temp[0] =
        ((((((((((((((((((1280.0 * resnormNew - 2048.0 * sqrtGamma) -
                         2400.0 * b_N1_tmp_tmp) +
                        c) +
                       c_f_temp_tmp) -
                      2400.0 * N1_tmp_tmp * c_N1_tmp_tmp) -
                     4156.9219381653056 * N1_tmp_tmp) +
                    4156.9219381653056 * c_N1_tmp_tmp) -
                   f_temp_tmp * firstOrderOpt) -
                  1385.6406460551018 * b_N1_tmp_tmp * c_N1_tmp_tmp) +
                 1385.6406460551018 * firstOrderOpt * N1_tmp_tmp) -
                800.0 * b_N1_tmp_tmp * firstOrderOpt * sqrtGamma) -
               1280.0 * b_N1_tmp_tmp * firstOrderOpt * resnormNew) -
              800.0 * sqrtGamma * N1_tmp_tmp * c_N1_tmp_tmp) -
             1280.0 * N1_tmp_tmp * c_N1_tmp_tmp * resnormNew) +
            1385.6406460551018 * b_N1_tmp_tmp * sqrtGamma * c_N1_tmp_tmp) -
           e_f_temp_tmp * N1_tmp_tmp) +
          2217.0250336881627 * b_N1_tmp_tmp * c_N1_tmp_tmp * resnormNew) -
         2217.0250336881627 * firstOrderOpt * N1_tmp_tmp * resnormNew) +
        5248.0;
    f_temp[1] =
        ((((((((((((((((((c - 2048.0 * sqrtGamma) - 1280.0 * resnormNew) -
                        2400.0 * b_N2_tmp_tmp) -
                       c_f_temp_tmp) -
                      2400.0 * N2_tmp_tmp * c_N1_tmp_tmp) -
                     4156.9219381653056 * N2_tmp_tmp) +
                    4156.9219381653056 * c_N1_tmp_tmp) -
                   b_f_temp_tmp * firstOrderOpt) -
                  1385.6406460551018 * b_N2_tmp_tmp * c_N1_tmp_tmp) +
                 d_f_temp_tmp * N2_tmp_tmp) -
                800.0 * b_N2_tmp_tmp * firstOrderOpt * sqrtGamma) +
               1280.0 * b_N2_tmp_tmp * firstOrderOpt * resnormNew) -
              800.0 * sqrtGamma * N2_tmp_tmp * c_N1_tmp_tmp) +
             1280.0 * N2_tmp_tmp * c_N1_tmp_tmp * resnormNew) +
            1385.6406460551018 * b_N2_tmp_tmp * sqrtGamma * c_N1_tmp_tmp) -
           e_f_temp_tmp * N2_tmp_tmp) -
          2217.0250336881627 * b_N2_tmp_tmp * c_N1_tmp_tmp * resnormNew) +
         2217.0250336881627 * firstOrderOpt * N2_tmp_tmp * resnormNew) +
        5248.0;
    /*  方程 */
    resnormNew = 0.0;
    evalOK = true;
    for (b_exitflag = 0; b_exitflag < 2; b_exitflag++) {
      c = f_temp[b_exitflag];
      fNew[b_exitflag] = c;
      resnormNew += c * c;
      if ((!evalOK) || rtIsNaN(c)) {
        evalOK = false;
      }
    }
    funcCount++;
    guard1 = false;
    if ((resnormNew < resnorm) && evalOK) {
      iter++;
      funDiff = fabs(resnormNew - resnorm) / resnorm;
      resnorm = resnormNew;
      a__3[0] = xp_idx_0;
      a__3[1] = xp_idx_1;
      evalOK =
          computeFiniteDifferences(&FiniteDifferences, fNew, a__3, JacCeqTrans);
      funcCount += FiniteDifferences.numEvals;
      augJacobian[0] = JacCeqTrans[0];
      augJacobian[1] = JacCeqTrans[2];
      fCurrent[0] = fNew[0];
      augJacobian[4] = JacCeqTrans[1];
      augJacobian[5] = JacCeqTrans[3];
      fCurrent[1] = fNew[1];
      jacobian[0] = JacCeqTrans[0];
      jacobian[1] = JacCeqTrans[2];
      jacobian[2] = JacCeqTrans[1];
      jacobian[3] = JacCeqTrans[3];
      if (evalOK) {
        x[0] = xp_idx_0;
        x[1] = xp_idx_1;
        if (stepSuccessful) {
          b_gamma *= 0.1;
        }
        stepSuccessful = true;
        guard1 = true;
      } else {
        b_exitflag = 2;
        jacobian[0] = rtNaN;
        jacobian[1] = rtNaN;
        jacobian[2] = rtNaN;
        jacobian[3] = rtNaN;
        exitg1 = true;
      }
    } else {
      b_gamma *= 10.0;
      stepSuccessful = false;
      augJacobian[0] = jacobian[0];
      augJacobian[1] = jacobian[1];
      augJacobian[4] = jacobian[2];
      augJacobian[5] = jacobian[3];
      guard1 = true;
    }
    if (guard1) {
      sqrtGamma = sqrt(b_gamma);
      augJacobian[3] = 0.0;
      augJacobian[2] = sqrtGamma;
      gradf[0] = 0.0;
      augJacobian[6] = 0.0;
      augJacobian[7] = sqrtGamma;
      gradf[1] = 0.0;
      for (iac = 0; iac <= 2; iac += 2) {
        c = 0.0;
        b_exitflag = iac + 2;
        for (ia = iac + 1; ia <= b_exitflag; ia++) {
          c += jacobian[ia - 1] * fCurrent[(ia - iac) - 1];
        }
        b_exitflag = iac >> 1;
        gradf[b_exitflag] += c;
      }
      b_exitflag = checkStoppingCriteria(gradf, relFactor, funDiff, x, dx,
                                         funcCount, stepSuccessful, &iter);
      if (b_exitflag != -5) {
        exitg1 = true;
      }
    }
  }
  *exitflag = b_exitflag;
  *output_firstorderopt = 0.0;
  *output_iterations = iter;
  *output_funcCount = funcCount;
  firstOrderOpt = 0.0;
  resnormNew = 3.3121686421112381E-170;
  for (b_exitflag = 0; b_exitflag < 2; b_exitflag++) {
    c = fabs(gradf[b_exitflag]);
    if (rtIsNaN(c) || (c > *output_firstorderopt)) {
      *output_firstorderopt = c;
    }
    c = fabs(dx[b_exitflag]);
    if (c > resnormNew) {
      sqrtGamma = resnormNew / c;
      firstOrderOpt = firstOrderOpt * sqrtGamma * sqrtGamma + 1.0;
      resnormNew = c;
    } else {
      sqrtGamma = c / resnormNew;
      firstOrderOpt += sqrtGamma * sqrtGamma;
    }
    lambda_lower[b_exitflag] = 0.0;
    lambda_upper[b_exitflag] = 0.0;
  }
  *output_stepsize = resnormNew * sqrt(firstOrderOpt);
  return resnorm;
}

/* End of code generation (driver.c) */

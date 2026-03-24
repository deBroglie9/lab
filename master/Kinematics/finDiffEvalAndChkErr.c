/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * finDiffEvalAndChkErr.c
 *
 * Code generation for function 'finDiffEvalAndChkErr'
 *
 */

/* Include files */
#include "finDiffEvalAndChkErr.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */
boolean_T finDiffEvalAndChkErr(double c_obj_nonlin_workspace_fun_work,
                               double d_obj_nonlin_workspace_fun_work,
                               double cEqPlus[2], int dim, double delta,
                               double xk[2], double *fplus)
{
  double N1_tmp;
  double N1_tmp_tmp;
  double b_N1_tmp_tmp;
  double c_N1_tmp_tmp;
  double d;
  double d1;
  double d2;
  double d3;
  double d_N1_tmp_tmp;
  double e_N1_tmp_tmp;
  double temp_tmp;
  int idx;
  boolean_T evalOK;
  *fplus = 0.0;
  evalOK = true;
  temp_tmp = xk[dim - 1];
  xk[dim - 1] = temp_tmp + delta;
  N1_tmp_tmp = cos(xk[0]);
  b_N1_tmp_tmp = cos(xk[1]);
  c_N1_tmp_tmp = sin(xk[0]);
  N1_tmp = sin(c_obj_nonlin_workspace_fun_work);
  d_N1_tmp_tmp = sin(xk[1]);
  e_N1_tmp_tmp = cos(c_obj_nonlin_workspace_fun_work);
  d = 2400.0 * b_N1_tmp_tmp * N1_tmp_tmp;
  d1 = 3840.0 * b_N1_tmp_tmp * c_N1_tmp_tmp;
  d2 = 1385.6406460551018 * b_N1_tmp_tmp;
  d3 = d2 * N1_tmp_tmp;
  cEqPlus[0] =
      ((((((((((((((((((1280.0 * c_N1_tmp_tmp - 2048.0 * N1_tmp_tmp) -
                       2400.0 * e_N1_tmp_tmp) +
                      d) +
                     d1) -
                    2400.0 * N1_tmp * d_N1_tmp_tmp) -
                   4156.9219381653056 * N1_tmp) +
                  4156.9219381653056 * d_N1_tmp_tmp) -
                 2400.0 * e_N1_tmp_tmp * b_N1_tmp_tmp) -
                1385.6406460551018 * e_N1_tmp_tmp * d_N1_tmp_tmp) +
               1385.6406460551018 * b_N1_tmp_tmp * N1_tmp) -
              800.0 * e_N1_tmp_tmp * b_N1_tmp_tmp * N1_tmp_tmp) -
             1280.0 * e_N1_tmp_tmp * b_N1_tmp_tmp * c_N1_tmp_tmp) -
            800.0 * N1_tmp_tmp * N1_tmp * d_N1_tmp_tmp) -
           1280.0 * N1_tmp * d_N1_tmp_tmp * c_N1_tmp_tmp) +
          1385.6406460551018 * e_N1_tmp_tmp * N1_tmp_tmp * d_N1_tmp_tmp) -
         d3 * N1_tmp) +
        2217.0250336881627 * e_N1_tmp_tmp * d_N1_tmp_tmp * c_N1_tmp_tmp) -
       2217.0250336881627 * b_N1_tmp_tmp * N1_tmp * c_N1_tmp_tmp) +
      5248.0;
  N1_tmp = sin(d_obj_nonlin_workspace_fun_work);
  e_N1_tmp_tmp = cos(d_obj_nonlin_workspace_fun_work);
  cEqPlus[1] =
      ((((((((((((((((((d - 2048.0 * N1_tmp_tmp) - 1280.0 * c_N1_tmp_tmp) -
                      2400.0 * e_N1_tmp_tmp) -
                     d1) -
                    2400.0 * N1_tmp * d_N1_tmp_tmp) -
                   4156.9219381653056 * N1_tmp) +
                  4156.9219381653056 * d_N1_tmp_tmp) -
                 2400.0 * e_N1_tmp_tmp * b_N1_tmp_tmp) -
                1385.6406460551018 * e_N1_tmp_tmp * d_N1_tmp_tmp) +
               d2 * N1_tmp) -
              800.0 * e_N1_tmp_tmp * b_N1_tmp_tmp * N1_tmp_tmp) +
             1280.0 * e_N1_tmp_tmp * b_N1_tmp_tmp * c_N1_tmp_tmp) -
            800.0 * N1_tmp_tmp * N1_tmp * d_N1_tmp_tmp) +
           1280.0 * N1_tmp * d_N1_tmp_tmp * c_N1_tmp_tmp) +
          1385.6406460551018 * e_N1_tmp_tmp * N1_tmp_tmp * d_N1_tmp_tmp) -
         d3 * N1_tmp) -
        2217.0250336881627 * e_N1_tmp_tmp * d_N1_tmp_tmp * c_N1_tmp_tmp) +
       2217.0250336881627 * b_N1_tmp_tmp * N1_tmp * c_N1_tmp_tmp) +
      5248.0;
  /*  方程 */
  idx = 0;
  while (evalOK && (idx + 1 <= 2)) {
    evalOK = ((!rtIsInf(cEqPlus[idx])) && (!rtIsNaN(cEqPlus[idx])));
    idx++;
  }
  xk[dim - 1] = temp_tmp;
  return evalOK;
}

/* End of code generation (finDiffEvalAndChkErr.c) */

/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * FK_7DOF_internal_types.h
 *
 * Code generation for function 'FK_7DOF'
 *
 */

#ifndef FK_7DOF_INTERNAL_TYPES_H
#define FK_7DOF_INTERNAL_TYPES_H

/* Include files */
#include "FK_7DOF_types.h"
#include "rtwtypes.h"

/* Type Definitions */
#ifndef typedef_struct_T
#define typedef_struct_T
typedef struct {
  double c5;
  double c6;
} struct_T;
#endif /* typedef_struct_T */

#ifndef typedef_anonymous_function
#define typedef_anonymous_function
typedef struct {
  struct_T workspace;
} anonymous_function;
#endif /* typedef_anonymous_function */

#ifndef typedef_b_struct_T
#define typedef_b_struct_T
typedef struct {
  anonymous_function fun;
} b_struct_T;
#endif /* typedef_b_struct_T */

#ifndef typedef_b_anonymous_function
#define typedef_b_anonymous_function
typedef struct {
  b_struct_T workspace;
} b_anonymous_function;
#endif /* typedef_b_anonymous_function */

#ifndef typedef_c_struct_T
#define typedef_c_struct_T
typedef struct {
  b_anonymous_function nonlin;
  double cEq_1[2];
  int numEvals;
} c_struct_T;
#endif /* typedef_c_struct_T */

#endif
/* End of code generation (FK_7DOF_internal_types.h) */

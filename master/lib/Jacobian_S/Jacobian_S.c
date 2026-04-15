/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: Jacobian_S.c
 *
 * MATLAB Coder version            : 23.2
 * C/C++ source code generated on  : 12-Jan-2026 15:07:11
 */

/* Include Files */
#include "Jacobian_S.h"
#include "Jacobian_S_emxutil.h"
#include "Jacobian_S_types.h"
#include "combineVectorElements.h"
#include "mrdivide_helper.h"
#include "roots.h"
#include "rt_nonfinite.h"
#include "rt_defines.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Declarations */
static double rt_atan2d_snf(double u0, double u1);

/* Function Definitions */
/*
 * Arguments    : double u0
 *                double u1
 * Return Type  : double
 */
static double rt_atan2d_snf(double u0, double u1)
{
  double y;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = rtNaN;
  } else if (rtIsInf(u0) && rtIsInf(u1)) {
    int i;
    int i1;
    if (u0 > 0.0) {
      i = 1;
    } else {
      i = -1;
    }
    if (u1 > 0.0) {
      i1 = 1;
    } else {
      i1 = -1;
    }
    y = atan2(i, i1);
  } else if (u1 == 0.0) {
    if (u0 > 0.0) {
      y = RT_PI / 2.0;
    } else if (u0 < 0.0) {
      y = -(RT_PI / 2.0);
    } else {
      y = 0.0;
    }
  } else {
    y = atan2(u0, u1);
  }
  return y;
}

/*
 * Arguments    : double t1
 *                double t2
 *                double t3
 *                double c1
 *                double c2
 *                double c3
 *                double c4
 *                double *tr
 *                double *tp
 *                double *ty
 * Return Type  : void
 */
void Jacobian_S(double t1, double t2, double t3, double c1, double c2,
                double c3, double c4, double *tr, double *tp, double *ty)
{
  static const double b[16] = {1.0,
                               0.0,
                               0.0,
                               0.0,
                               0.0,
                               0.64278760968653936,
                               0.766044443118978,
                               0.0,
                               0.0,
                               -0.766044443118978,
                               0.64278760968653936,
                               0.0,
                               0.0,
                               0.0,
                               0.0,
                               1.0};
  static const double b_b[16] = {
      0.50000000000000011, 0.0, -0.8660254037844386, 0.0, 0.0, 1.0, 0.0, 0.0,
      0.8660254037844386,  0.0, 0.50000000000000011, 0.0, 0.0, 0.0, 0.0, 1.0};
  static const double c_b[16] = {0.82526879545537513,
                                 0.56474013072176321,
                                 0.0,
                                 0.0,
                                 -0.56474013072176321,
                                 0.82526879545537513,
                                 0.0,
                                 0.0,
                                 0.0,
                                 0.0,
                                 1.0,
                                 0.0,
                                 0.0,
                                 0.0,
                                 0.0,
                                 1.0};
  static const double d_b[16] = {1.0,
                                 0.0,
                                 0.0,
                                 0.0,
                                 0.0,
                                 0.53349364956842527,
                                 0.84580407061574392,
                                 0.0,
                                 0.0,
                                 -0.84580407061574392,
                                 0.53349364956842527,
                                 0.0,
                                 0.0,
                                 0.0,
                                 0.0,
                                 1.0};
  static const double B[9] = {
      0.86602540377173287, 1.562250329101289E-11, 0.50000000002200717,
      0.86602540409063378, -0.24999999988778313,  -0.43301270134461783,
      0.866025404077136,   0.24999999994797462,   -0.43301270133686148};
  emxArray_real_T *Y;
  creal_T YY_data[8];
  double T1[16];
  double e_T1_tmp[16];
  double f_T1_tmp[16];
  double g_T1_tmp[16];
  double a[9];
  double Ts[3];
  double D11;
  double D11_tmp_tmp;
  double D12;
  double D12_tmp;
  double D13;
  double D21;
  double D22;
  double D23;
  double D23_tmp;
  double E11;
  double E12;
  double E13;
  double E21;
  double E22;
  double E23;
  double F11;
  double F13;
  double F21;
  double F22;
  double F23;
  double T1_tmp;
  double a_tmp;
  double b_D11_tmp_tmp;
  double b_D23_tmp;
  double b_T1_tmp;
  double b_a_tmp;
  double c_D11_tmp_tmp;
  double c_T1_tmp;
  double c_a_tmp;
  double cy;
  double d_D11_tmp_tmp;
  double d_T1_tmp;
  double d_a_tmp;
  double e_D11_tmp_tmp;
  double e_a_tmp;
  double f_D11_tmp_tmp;
  double f_a_tmp;
  double g_a_tmp;
  double h_a_tmp;
  double i_a_tmp;
  double j_a_tmp;
  double k_a_tmp;
  double ks;
  double l_a_tmp;
  double m_a_tmp;
  double n_a_tmp;
  double phi1_idx_0;
  double *Y_data;
  int YY_size;
  int i;
  int i1;
  unsigned int k;
  int nz;
  boolean_T b_YY_data[8];
  (void)c4;
  /* 结果来源于"test4,m"此处将cr,cp,cy替换为0，以求得三力臂的初始角度,最新一次修改于2023.11.13
   */
  /* %此向量本来在c3坐标系中，为了便于下面的干涉检查计算，做统一坐标系处理 */
  /* 此向量本来在c3坐标系中，为了便于下面的干涉检查计算，做统一坐标系处理 */
  /*  eq1=w3(1)*v3(1)+w3(2)*v3(2)+w3(3)*v3(3)-R^2*cos(gama); */
  /*  persistent Y */
  /*  if isempty(Y) */
  /*      Y=zeros(8,1); */
  /*  end */
  /*  Yy=zeros(8,1); */
  /*  R=86.5; */
  /* 此L1是加了R的大臂总长度 */
  /*  Y=zeros(1,8); */
  D11_tmp_tmp = cos((c1 - 1.298210328476112) + 1.5707963267948966);
  b_D11_tmp_tmp = cos(c2 - 1.52502572060903);
  c_D11_tmp_tmp = sin((c1 - 1.298210328476112) + 1.5707963267948966);
  d_D11_tmp_tmp = sin(c2 - 1.52502572060903);
  e_D11_tmp_tmp = D11_tmp_tmp * d_D11_tmp_tmp;
  phi1_idx_0 = e_D11_tmp_tmp * 0.64278760968653936;
  f_D11_tmp_tmp = c_D11_tmp_tmp * b_D11_tmp_tmp;
  cy = f_D11_tmp_tmp * 0.64278760968653936;
  D11 = (phi1_idx_0 * 0.50000000000000011 * 0.766044443118978 *
             0.84580407061574392 -
         0.20823860156791746) -
        cy * 0.50000000000000011 * 0.766044443118978 * 0.84580407061574392;
  ks = D11_tmp_tmp * b_D11_tmp_tmp;
  D12_tmp = c_D11_tmp_tmp * d_D11_tmp_tmp;
  D12 = ks * 0.766044443118978 * 0.84580407061574392 +
        D12_tmp * 0.766044443118978 * 0.84580407061574392;
  D13 = (phi1_idx_0 * 0.53349364956842527 * 0.766044443118978 *
             0.8660254037844386 -
         0.22749997285668702) -
        cy * 0.53349364956842527 * 0.766044443118978 * 0.8660254037844386;
  E11 = ks * 0.50000000000000011 * 0.766044443118978 * 0.84580407061574392 +
        D12_tmp * 0.50000000000000011 * 0.766044443118978 * 0.84580407061574392;
  E12 = (0.41647720313583492 -
         phi1_idx_0 * 0.766044443118978 * 0.84580407061574392) +
        cy * 0.766044443118978 * 0.84580407061574392;
  E13 = ks * 0.53349364956842527 * 0.766044443118978 * 0.8660254037844386 +
        D12_tmp * 0.53349364956842527 * 0.766044443118978 * 0.8660254037844386;
  F11 = (e_D11_tmp_tmp * 0.58682408883346515 * 0.84580407061574392 *
             0.8660254037844386 +
         0.30264631904955869) -
        f_D11_tmp_tmp * 0.58682408883346515 * 0.84580407061574392 *
            0.8660254037844386;
  F13 = ((f_D11_tmp_tmp * 0.53349364956842527 * 0.50000000000000011 *
              0.58682408883346515 -
          0.1102133623809971) -
         e_D11_tmp_tmp * 0.53349364956842527 * 0.50000000000000011 *
             0.58682408883346515) -
        0.50000000000000011;
  e_D11_tmp_tmp = cos((c3 + 1.5707963267948966) - 0.30696770204475443);
  f_D11_tmp_tmp = sin((c3 + 1.5707963267948966) - 0.30696770204475443);
  phi1_idx_0 = c_D11_tmp_tmp * 0.64278760968653936 * 0.50000000000000011;
  cy = D11_tmp_tmp * 0.64278760968653936 * 0.50000000000000011;
  D21 = -e_D11_tmp_tmp * 0.84580407061574392 *
            (D11_tmp_tmp * 0.56474013072176321 +
             phi1_idx_0 * 0.82526879545537513) -
        f_D11_tmp_tmp * 0.84580407061574392 *
            (c_D11_tmp_tmp * 0.56474013072176321 - cy * 0.82526879545537513);
  D12_tmp = f_D11_tmp_tmp * 0.84580407061574392;
  D22 = e_D11_tmp_tmp * 0.84580407061574392 *
            (D11_tmp_tmp * 0.82526879545537513 -
             phi1_idx_0 * 0.56474013072176321) +
        D12_tmp *
            (c_D11_tmp_tmp * 0.82526879545537513 + cy * 0.56474013072176321);
  D23_tmp = D11_tmp_tmp * f_D11_tmp_tmp;
  b_D23_tmp = c_D11_tmp_tmp * e_D11_tmp_tmp;
  D23 =
      D23_tmp * 0.64278760968653936 * 0.53349364956842527 * 0.8660254037844386 -
      b_D23_tmp * 0.64278760968653936 * 0.53349364956842527 *
          0.8660254037844386;
  phi1_idx_0 = e_D11_tmp_tmp * 0.84580407061574392;
  cy = c_D11_tmp_tmp * 0.64278760968653936;
  ks = D11_tmp_tmp * 0.64278760968653936;
  E21 = phi1_idx_0 * (D11_tmp_tmp * 0.50000000000000011 * 0.82526879545537513 -
                      cy * 0.56474013072176321) +
        D12_tmp * (ks * 0.56474013072176321 +
                   c_D11_tmp_tmp * 0.50000000000000011 * 0.82526879545537513);
  E22 = phi1_idx_0 * (cy * 0.82526879545537513 +
                      D11_tmp_tmp * 0.50000000000000011 * 0.56474013072176321) -
        D12_tmp * (ks * 0.82526879545537513 -
                   c_D11_tmp_tmp * 0.50000000000000011 * 0.56474013072176321);
  E23 =
      D11_tmp_tmp * e_D11_tmp_tmp * 0.53349364956842527 * 0.8660254037844386 +
      c_D11_tmp_tmp * f_D11_tmp_tmp * 0.53349364956842527 * 0.8660254037844386;
  phi1_idx_0 =
      D23_tmp * 0.766044443118978 * 0.84580407061574392 * 0.8660254037844386;
  cy = b_D23_tmp * 0.766044443118978 * 0.84580407061574392 * 0.8660254037844386;
  F21 = phi1_idx_0 * 0.82526879545537513 - cy * 0.82526879545537513;
  F22 = phi1_idx_0 * 0.56474013072176321 - cy * 0.56474013072176321;
  F23 = (b_D23_tmp * 0.53349364956842527 * 0.50000000000000011 *
             0.766044443118978 -
         D23_tmp * 0.53349364956842527 * 0.50000000000000011 *
             0.766044443118978) -
        0.50000000000000011;
  cy = D12 - D13;
  ks = D22 - D23;
  D12_tmp = F22 - F23;
  e_D11_tmp_tmp = cy * D12_tmp - ks * -F13;
  f_D11_tmp_tmp = E12 - E13;
  phi1_idx_0 = E22 - E23;
  D23_tmp = cy * phi1_idx_0 - ks * f_D11_tmp_tmp;
  b_D23_tmp = f_D11_tmp_tmp * D12_tmp - phi1_idx_0 * -F13;
  D11_tmp_tmp = ((2.0 * F21 * cy - 2.0 * F11 * ks) - 2.0 * D21 * -F13) +
                2.0 * D11 * D12_tmp;
  c_D11_tmp_tmp =
      ((2.0 * E21 * cy - 2.0 * E11 * ks) - 2.0 * D21 * f_D11_tmp_tmp) +
      2.0 * D11 * phi1_idx_0;
  a_tmp = ((2.0 * F21 * f_D11_tmp_tmp - 2.0 * F11 * phi1_idx_0) -
           2.0 * E21 * -F13) +
          2.0 * E11 * D12_tmp;
  b_a_tmp = 4.0 * D11 * F21 - 4.0 * D21 * F11;
  c_a_tmp = 4.0 * D11 * E21 - 4.0 * D21 * E11;
  d_a_tmp = 4.0 * E11 * F21 - 4.0 * E21 * F11;
  e_a_tmp = F22 + F23;
  f_a_tmp = D22 + D23;
  g_a_tmp = D12 + D13;
  h_a_tmp = ((cy * e_a_tmp - ks * F13) - -F13 * f_a_tmp) + D12_tmp * g_a_tmp;
  i_a_tmp = E22 + E23;
  j_a_tmp = E12 + E13;
  D12_tmp = ((f_D11_tmp_tmp * e_a_tmp - phi1_idx_0 * F13) - -F13 * i_a_tmp) +
            D12_tmp * j_a_tmp;
  cy = ((cy * i_a_tmp - ks * j_a_tmp) - f_D11_tmp_tmp * f_a_tmp) +
       phi1_idx_0 * g_a_tmp;
  ks = ((2.0 * E21 * g_a_tmp - 2.0 * E11 * f_a_tmp) - 2.0 * D21 * j_a_tmp) +
       2.0 * D11 * i_a_tmp;
  f_D11_tmp_tmp =
      ((2.0 * F21 * g_a_tmp - 2.0 * F11 * f_a_tmp) - 2.0 * D21 * F13) +
      2.0 * D11 * e_a_tmp;
  phi1_idx_0 = ((2.0 * F21 * j_a_tmp - 2.0 * F11 * i_a_tmp) - 2.0 * E21 * F13) +
               2.0 * E11 * e_a_tmp;
  k_a_tmp = g_a_tmp * e_a_tmp - f_a_tmp * F13;
  f_a_tmp = g_a_tmp * i_a_tmp - f_a_tmp * j_a_tmp;
  e_a_tmp = j_a_tmp * e_a_tmp - i_a_tmp * F13;
  a[0] = (e_D11_tmp_tmp * e_D11_tmp_tmp - D23_tmp * D23_tmp) +
         b_D23_tmp * b_D23_tmp;
  g_a_tmp = 2.0 * D23_tmp;
  i_a_tmp = 2.0 * e_D11_tmp_tmp;
  j_a_tmp = 2.0 * b_D23_tmp;
  a[1] = (g_a_tmp * c_D11_tmp_tmp - i_a_tmp * D11_tmp_tmp) - j_a_tmp * a_tmp;
  l_a_tmp = 2.0 * c_a_tmp;
  m_a_tmp = 2.0 * b_a_tmp;
  n_a_tmp = 2.0 * d_a_tmp;
  a[2] = ((g_a_tmp * cy - i_a_tmp * h_a_tmp) - j_a_tmp * D12_tmp) +
         (((((D11_tmp_tmp * D11_tmp_tmp - c_D11_tmp_tmp * c_D11_tmp_tmp) +
             a_tmp * a_tmp) -
            l_a_tmp * D23_tmp) +
           m_a_tmp * e_D11_tmp_tmp) +
          n_a_tmp * b_D23_tmp);
  e_D11_tmp_tmp = 2.0 * a_tmp;
  D23_tmp = 2.0 * D11_tmp_tmp;
  b_D23_tmp = 2.0 * c_D11_tmp_tmp;
  a[3] = ((l_a_tmp * c_D11_tmp_tmp - m_a_tmp * D11_tmp_tmp) - n_a_tmp * a_tmp) +
         (((((D23_tmp * h_a_tmp - b_D23_tmp * cy) + e_D11_tmp_tmp * D12_tmp) -
            g_a_tmp * ks) +
           i_a_tmp * f_D11_tmp_tmp) +
          j_a_tmp * phi1_idx_0);
  a[4] = (((b_a_tmp * b_a_tmp - c_a_tmp * c_a_tmp) + d_a_tmp * d_a_tmp) +
          (((((l_a_tmp * cy - e_D11_tmp_tmp * phi1_idx_0) -
              D23_tmp * f_D11_tmp_tmp) -
             m_a_tmp * h_a_tmp) -
            n_a_tmp * D12_tmp) +
           b_D23_tmp * ks)) +
         (((((h_a_tmp * h_a_tmp + D12_tmp * D12_tmp) - g_a_tmp * f_a_tmp) +
            i_a_tmp * k_a_tmp) +
           j_a_tmp * e_a_tmp) -
          cy * cy);
  e_D11_tmp_tmp = 2.0 * f_a_tmp;
  D23_tmp = 2.0 * k_a_tmp;
  b_D23_tmp = 2.0 * e_a_tmp;
  a[5] = ((m_a_tmp * f_D11_tmp_tmp - l_a_tmp * ks) + n_a_tmp * phi1_idx_0) +
         (((((e_D11_tmp_tmp * c_D11_tmp_tmp - D23_tmp * D11_tmp_tmp) -
             b_D23_tmp * a_tmp) +
            2.0 * ks * cy) -
           2.0 * f_D11_tmp_tmp * h_a_tmp) -
          2.0 * phi1_idx_0 * D12_tmp);
  a[6] = (((((m_a_tmp * k_a_tmp - l_a_tmp * f_a_tmp) + n_a_tmp * e_a_tmp) -
            ks * ks) +
           f_D11_tmp_tmp * f_D11_tmp_tmp) +
          phi1_idx_0 * phi1_idx_0) +
         ((e_D11_tmp_tmp * cy - D23_tmp * h_a_tmp) - b_D23_tmp * D12_tmp);
  a[7] =
      (D23_tmp * f_D11_tmp_tmp - e_D11_tmp_tmp * ks) + b_D23_tmp * phi1_idx_0;
  a[8] = (k_a_tmp * k_a_tmp - f_a_tmp * f_a_tmp) + e_a_tmp * e_a_tmp;
  YY_size = roots(a, YY_data);
  /* Y=YY(imag(YY)==0); */
  for (i = 0; i < YY_size; i++) {
    b_YY_data[i] = (YY_data[i].im == 0.0);
  }
  nz = combineVectorElements(b_YY_data, YY_size);
  /*  预分配 */
  emxInit_real_T(&Y);
  i = Y->size[0];
  Y->size[0] = nz;
  emxEnsureCapacity_real_T(Y, i);
  Y_data = Y->data;
  for (i = 0; i < nz; i++) {
    Y_data[i] = 0.0;
  }
  /*  循环复制 */
  k = 1U;
  for (nz = 0; nz < YY_size; nz++) {
    if (YY_data[nz].im == 0.0) {
      Y_data[(int)k - 1] = YY_data[nz].re;
      k++;
    }
  }
  /*  phi2=zeros(1,2); */
  cy = Y_data[0] * Y_data[0];
  D12_tmp =
      (E11 * 2.0 * Y_data[0] / (cy + 1.0) + E12 * (1.0 - cy) / (cy + 1.0)) +
      E13;
  e_D11_tmp_tmp =
      (E21 * 2.0 * Y_data[0] / (cy + 1.0) + E22 * (1.0 - cy) / (cy + 1.0)) +
      E23;
  phi1_idx_0 = asin(
      (D12_tmp * ((F21 * 2.0 * Y_data[0] / (cy + 1.0) +
                   F22 * (1.0 - cy) / (cy + 1.0)) +
                  F23) -
       e_D11_tmp_tmp * ((F11 * 2.0 * Y_data[0] / (cy + 1.0) +
                         0.0 * (1.0 - cy) / (cy + 1.0)) +
                        F13)) /
      (((D11 * 2.0 * Y_data[0] / (cy + 1.0) + D12 * (1.0 - cy) / (cy + 1.0)) +
        D13) *
           e_D11_tmp_tmp -
       ((D21 * 2.0 * Y_data[0] / (cy + 1.0) + D22 * (1.0 - cy) / (cy + 1.0)) +
        D23) *
           D12_tmp));
  cy = Y_data[1] * Y_data[1];
  D12_tmp =
      (E11 * 2.0 * Y_data[1] / (cy + 1.0) + E12 * (1.0 - cy) / (cy + 1.0)) +
      E13;
  e_D11_tmp_tmp =
      (E21 * 2.0 * Y_data[1] / (cy + 1.0) + E22 * (1.0 - cy) / (cy + 1.0)) +
      E23;
  if (Y_data[0] <= Y_data[1]) {
    ks = 2.0 * atan(Y_data[0]);
  } else {
    phi1_idx_0 = asin(
        (D12_tmp * ((F21 * 2.0 * Y_data[1] / (cy + 1.0) +
                     F22 * (1.0 - cy) / (cy + 1.0)) +
                    F23) -
         e_D11_tmp_tmp * ((F11 * 2.0 * Y_data[1] / (cy + 1.0) +
                           0.0 * (1.0 - cy) / (cy + 1.0)) +
                          F13)) /
        (((D11 * 2.0 * Y_data[1] / (cy + 1.0) + D12 * (1.0 - cy) / (cy + 1.0)) +
          D13) *
             e_D11_tmp_tmp -
         ((D21 * 2.0 * Y_data[1] / (cy + 1.0) + D22 * (1.0 - cy) / (cy + 1.0)) +
          D23) *
             D12_tmp));
    ks = 2.0 * atan(Y_data[1]);
  }
  emxFree_real_T(&Y);
  T1_tmp = sin((c1 + 1.5707963267948966) - 1.298210328476112);
  b_T1_tmp = cos((c1 + 1.5707963267948966) - 1.298210328476112);
  c_T1_tmp = sin(phi1_idx_0);
  d_T1_tmp = cos(phi1_idx_0);
  e_T1_tmp[0] = b_T1_tmp;
  e_T1_tmp[4] = -T1_tmp;
  e_T1_tmp[8] = 0.0;
  e_T1_tmp[12] = 0.0;
  e_T1_tmp[1] = T1_tmp;
  e_T1_tmp[5] = b_T1_tmp;
  e_T1_tmp[9] = 0.0;
  e_T1_tmp[13] = 0.0;
  e_T1_tmp[2] = 0.0;
  e_T1_tmp[3] = 0.0;
  e_T1_tmp[6] = 0.0;
  e_T1_tmp[7] = 0.0;
  e_T1_tmp[10] = 1.0;
  e_T1_tmp[11] = 0.0;
  e_T1_tmp[14] = 0.0;
  e_T1_tmp[15] = 1.0;
  for (i = 0; i < 4; i++) {
    cy = e_T1_tmp[i];
    D12_tmp = e_T1_tmp[i + 4];
    e_D11_tmp_tmp = e_T1_tmp[i + 8];
    phi1_idx_0 = e_T1_tmp[i + 12];
    for (i1 = 0; i1 < 4; i1++) {
      nz = i1 << 2;
      f_T1_tmp[i + nz] =
          ((cy * b[nz] + D12_tmp * b[nz + 1]) + e_D11_tmp_tmp * b[nz + 2]) +
          phi1_idx_0 * b[nz + 3];
    }
  }
  e_T1_tmp[0] = d_T1_tmp;
  e_T1_tmp[4] = -c_T1_tmp;
  e_T1_tmp[8] = 0.0;
  e_T1_tmp[12] = 0.0;
  e_T1_tmp[1] = c_T1_tmp;
  e_T1_tmp[5] = d_T1_tmp;
  e_T1_tmp[9] = 0.0;
  e_T1_tmp[13] = 0.0;
  e_T1_tmp[2] = 0.0;
  e_T1_tmp[3] = 0.0;
  e_T1_tmp[6] = 0.0;
  e_T1_tmp[7] = 0.0;
  e_T1_tmp[10] = 1.0;
  e_T1_tmp[11] = 0.0;
  e_T1_tmp[14] = 0.0;
  e_T1_tmp[15] = 1.0;
  for (i = 0; i < 4; i++) {
    cy = f_T1_tmp[i];
    D12_tmp = f_T1_tmp[i + 4];
    e_D11_tmp_tmp = f_T1_tmp[i + 8];
    phi1_idx_0 = f_T1_tmp[i + 12];
    for (i1 = 0; i1 < 4; i1++) {
      nz = i1 << 2;
      g_T1_tmp[i + nz] = ((cy * e_T1_tmp[nz] + D12_tmp * e_T1_tmp[nz + 1]) +
                          e_D11_tmp_tmp * e_T1_tmp[nz + 2]) +
                         phi1_idx_0 * e_T1_tmp[nz + 3];
    }
    cy = g_T1_tmp[i];
    D12_tmp = g_T1_tmp[i + 4];
    e_D11_tmp_tmp = g_T1_tmp[i + 8];
    phi1_idx_0 = g_T1_tmp[i + 12];
    for (i1 = 0; i1 < 4; i1++) {
      nz = i1 << 2;
      T1[i + nz] = ((cy * b_b[nz] + D12_tmp * b_b[nz + 1]) +
                    e_D11_tmp_tmp * b_b[nz + 2]) +
                   phi1_idx_0 * b_b[nz + 3];
    }
  }
  cy = sin(ks);
  phi1_idx_0 = cos(ks);
  e_T1_tmp[0] = phi1_idx_0;
  e_T1_tmp[4] = -cy;
  e_T1_tmp[8] = 0.0;
  e_T1_tmp[12] = 0.0;
  e_T1_tmp[1] = cy;
  e_T1_tmp[5] = phi1_idx_0;
  e_T1_tmp[9] = 0.0;
  e_T1_tmp[13] = 0.0;
  e_T1_tmp[2] = 0.0;
  e_T1_tmp[3] = 0.0;
  e_T1_tmp[6] = 0.0;
  e_T1_tmp[7] = 0.0;
  e_T1_tmp[10] = 1.0;
  e_T1_tmp[11] = 0.0;
  e_T1_tmp[14] = 0.0;
  e_T1_tmp[15] = 1.0;
  for (i = 0; i < 4; i++) {
    cy = T1[i];
    D12_tmp = T1[i + 4];
    e_D11_tmp_tmp = T1[i + 8];
    phi1_idx_0 = T1[i + 12];
    for (i1 = 0; i1 < 4; i1++) {
      nz = i1 << 2;
      f_T1_tmp[i + nz] = ((cy * e_T1_tmp[nz] + D12_tmp * e_T1_tmp[nz + 1]) +
                          e_D11_tmp_tmp * e_T1_tmp[nz + 2]) +
                         phi1_idx_0 * e_T1_tmp[nz + 3];
    }
  }
  for (i = 0; i < 4; i++) {
    cy = f_T1_tmp[i];
    D12_tmp = f_T1_tmp[i + 4];
    e_D11_tmp_tmp = f_T1_tmp[i + 8];
    phi1_idx_0 = f_T1_tmp[i + 12];
    for (i1 = 0; i1 < 4; i1++) {
      nz = i1 << 2;
      YY_size = i + nz;
      g_T1_tmp[YY_size] = ((cy * c_b[nz] + D12_tmp * c_b[nz + 1]) +
                           e_D11_tmp_tmp * c_b[nz + 2]) +
                          phi1_idx_0 * c_b[nz + 3];
      e_T1_tmp[YY_size] = ((cy * d_b[nz] + D12_tmp * d_b[nz + 1]) +
                           e_D11_tmp_tmp * d_b[nz + 2]) +
                          phi1_idx_0 * d_b[nz + 3];
    }
    cy = g_T1_tmp[i];
    D12_tmp = g_T1_tmp[i + 4];
    e_D11_tmp_tmp = g_T1_tmp[i + 8];
    phi1_idx_0 = g_T1_tmp[i + 12];
    for (i1 = 0; i1 < 4; i1++) {
      nz = i1 << 2;
      f_T1_tmp[i + nz] = ((cy * d_b[nz] + D12_tmp * d_b[nz + 1]) +
                          e_D11_tmp_tmp * d_b[nz + 2]) +
                         phi1_idx_0 * d_b[nz + 3];
    }
  }
  for (i = 0; i < 3; i++) {
    a[i] = (T1[i] * 0.0 + T1[i + 4] * 0.0) + T1[i + 8];
    a[i + 3] = (e_T1_tmp[i] * 0.0 + e_T1_tmp[i + 4] * 0.0) + e_T1_tmp[i + 8];
    a[i + 6] = (f_T1_tmp[i] * 0.0 + f_T1_tmp[i + 4] * 0.0) + f_T1_tmp[i + 8];
  }
  double R[9];
  double J_tmp_tmp;
  double T1_tmp_tmp;
  double b_J_tmp_tmp;
  double c_J_tmp_tmp;
  double d_J_tmp_tmp;
  double e_J_tmp_tmp;
  double h_T1_tmp;
  double i_T1_tmp;
  double j_T1_tmp;
  double k_T1_tmp;
  double l_T1_tmp;
  double m_T1_tmp;
  double n_T1_tmp;
  double o_T1_tmp;
  double p_T1_tmp;
  double q_T1_tmp;
  double r_T1_tmp;
  double s_T1_tmp;
  double t_T1_tmp;
  double u_T1_tmp;
  double v_T1_tmp;
  double w_T1_tmp;
  mrdiv(a, B, R);
  ks = rt_atan2d_snf(R[1], R[0]);
  cy = rt_atan2d_snf(R[5], R[8]);
  phi1_idx_0 = rt_atan2d_snf(-R[2], sqrt(R[5] * R[5] + R[8] * R[8]));
  J_tmp_tmp = cos(phi1_idx_0);
  b_J_tmp_tmp = sin(phi1_idx_0);
  c_J_tmp_tmp = sin(cy);
  d_J_tmp_tmp = cos(cy);
  cy = cos(c1 - 1.298210328476112);
  e_J_tmp_tmp = cos(ks);
  D12_tmp = sin(c1 - 1.298210328476112);
  F13 = sin(ks);
  D21 = cos(c3 - 0.30696770204475443);
  E13 = sin(c3 - 0.30696770204475443);
  T1_tmp = J_tmp_tmp * J_tmp_tmp;
  b_T1_tmp = b_J_tmp_tmp * b_J_tmp_tmp;
  c_T1_tmp = F13 * F13;
  d_T1_tmp = e_J_tmp_tmp * e_J_tmp_tmp;
  F11 = c_J_tmp_tmp * c_J_tmp_tmp;
  E12 = d_T1_tmp * J_tmp_tmp;
  D11 = d_J_tmp_tmp * d_J_tmp_tmp;
  D12 = J_tmp_tmp * D11;
  D13 = 6.123233995736766E-17 * d_T1_tmp;
  E11 = 6.123233995736766E-17 * T1_tmp;
  h_T1_tmp = E11 * 0.86602540378443871;
  T1_tmp_tmp = T1_tmp * d_J_tmp_tmp;
  i_T1_tmp = T1_tmp_tmp * 0.86602540378443871;
  j_T1_tmp = cy * e_J_tmp_tmp;
  k_T1_tmp = 1.2246467991473532E-16 * J_tmp_tmp * d_J_tmp_tmp;
  l_T1_tmp = cy * 6.123233995736766E-17 * e_J_tmp_tmp;
  m_T1_tmp = D12_tmp * 6.123233995736766E-17;
  n_T1_tmp = D12_tmp * e_J_tmp_tmp;
  o_T1_tmp = 3.749399456654644E-33 * d_T1_tmp;
  p_T1_tmp = d_T1_tmp * d_J_tmp_tmp;
  q_T1_tmp = cy * 6.123233995736766E-17 * 0.766044443118978 * F13;
  r_T1_tmp = cy * d_J_tmp_tmp * 0.766044443118978 * F13;
  s_T1_tmp = m_T1_tmp * e_J_tmp_tmp * 0.766044443118978;
  t_T1_tmp = n_T1_tmp * d_J_tmp_tmp * 0.766044443118978;
  u_T1_tmp = l_T1_tmp * d_J_tmp_tmp * 0.766044443118978;
  v_T1_tmp = j_T1_tmp * 0.766044443118978;
  m_T1_tmp = m_T1_tmp * d_J_tmp_tmp * 0.766044443118978 * F13;
  w_T1_tmp = D12_tmp * 0.766044443118978 * F13;
  n_T1_tmp =
      ((((((((cy * J_tmp_tmp * 0.86602540378443871 * 0.766044443118978 * F13 -
              n_T1_tmp * J_tmp_tmp * 0.86602540378443871 * 0.766044443118978) -
             v_T1_tmp * c_J_tmp_tmp * 0.49999999999999994) +
            m_T1_tmp * 0.49999999999999994) -
           w_T1_tmp * c_J_tmp_tmp * 0.49999999999999994) +
          u_T1_tmp * 0.49999999999999994) +
         q_T1_tmp * b_J_tmp_tmp * c_J_tmp_tmp * 0.49999999999999994) +
        r_T1_tmp * b_J_tmp_tmp * 0.49999999999999994) -
       s_T1_tmp * b_J_tmp_tmp * c_J_tmp_tmp * 0.49999999999999994) -
      t_T1_tmp * b_J_tmp_tmp * 0.49999999999999994;
  e_a_tmp = J_tmp_tmp * 0.75000000000000011 * b_J_tmp_tmp;
  f_a_tmp = 0.64278760968653936 * J_tmp_tmp * 0.86602540378443871;
  g_a_tmp = E12 * 0.75000000000000011 * b_J_tmp_tmp;
  h_a_tmp = J_tmp_tmp * 0.75000000000000011 * c_T1_tmp * b_J_tmp_tmp;
  i_a_tmp = d_J_tmp_tmp * 0.86602540378443871;
  j_a_tmp = E12 * D11;
  k_a_tmp = d_T1_tmp * T1_tmp;
  l_a_tmp = k_a_tmp * d_J_tmp_tmp * 0.86602540378443871;
  m_a_tmp = p_T1_tmp * 0.86602540378443871;
  n_a_tmp = D12 * b_J_tmp_tmp * 0.24999999999999994;
  F23 = i_T1_tmp * 0.49999999999999994;
  F22 = d_J_tmp_tmp * 0.86602540378443871 * b_T1_tmp * 0.49999999999999994;
  E23 = m_a_tmp * b_T1_tmp * 0.49999999999999994;
  F21 = i_T1_tmp * c_T1_tmp * 0.49999999999999994;
  E22 = i_a_tmp * c_T1_tmp * b_T1_tmp * 0.49999999999999994;
  D22 = j_a_tmp * b_J_tmp_tmp * 0.24999999999999994;
  D23 = D12 * c_T1_tmp * b_J_tmp_tmp * 0.24999999999999994;
  E21 = l_a_tmp * 0.49999999999999994;
  a[0] =
      ((((((((((((((((((((((((((((((((e_a_tmp + f_a_tmp) - g_a_tmp) - h_a_tmp) +
                                   j_T1_tmp * 0.86602540378443871 *
                                       0.766044443118978 * b_J_tmp_tmp) +
                                  D12_tmp * 0.86602540378443871 *
                                      0.766044443118978 * F13 * b_J_tmp_tmp) +
                                 3.9359389436709931E-17 * b_J_tmp_tmp *
                                     c_J_tmp_tmp * 0.49999999999999994) +
                                0.64278760968653936 * d_J_tmp_tmp *
                                    b_J_tmp_tmp * 0.49999999999999994) -
                               n_a_tmp) -
                              3.749399456654644E-33 * J_tmp_tmp * b_J_tmp_tmp *
                                  F11 * 0.24999999999999994) -
                             h_T1_tmp * c_J_tmp_tmp * 0.49999999999999994) -
                            F23) +
                           5.3028761936245346E-17 * b_T1_tmp * c_J_tmp_tmp *
                               0.49999999999999994) +
                          F22) -
                         5.3028761936245346E-17 * c_T1_tmp * b_T1_tmp *
                             c_J_tmp_tmp * 0.49999999999999994) -
                        E22) +
                       o_T1_tmp * J_tmp_tmp * b_J_tmp_tmp * F11 *
                           0.24999999999999994) +
                      D22) +
                     D23) +
                    3.749399456654644E-33 * J_tmp_tmp * c_T1_tmp * b_J_tmp_tmp *
                        F11 * 0.24999999999999994) +
                   D13 * T1_tmp * 0.86602540378443871 * c_J_tmp_tmp *
                       0.49999999999999994) +
                  E21) -
                 D13 * 0.86602540378443871 * b_T1_tmp * c_J_tmp_tmp *
                     0.49999999999999994) +
                h_T1_tmp * c_T1_tmp * c_J_tmp_tmp * 0.49999999999999994) -
               E23) +
              F21) -
             k_T1_tmp * b_J_tmp_tmp * c_J_tmp_tmp * 0.24999999999999994) -
            l_T1_tmp * J_tmp_tmp * 0.766044443118978 * c_J_tmp_tmp *
                0.49999999999999994) -
           j_T1_tmp * J_tmp_tmp * d_J_tmp_tmp * 0.766044443118978 *
               0.49999999999999994) -
          D12_tmp * 6.123233995736766E-17 * J_tmp_tmp * 0.766044443118978 *
              F13 * c_J_tmp_tmp * 0.49999999999999994) -
         D12_tmp * J_tmp_tmp * d_J_tmp_tmp * 0.766044443118978 * F13 *
             0.49999999999999994) +
        1.2246467991473532E-16 * d_T1_tmp * J_tmp_tmp * d_J_tmp_tmp *
            b_J_tmp_tmp * c_J_tmp_tmp * 0.24999999999999994) +
       k_T1_tmp * c_T1_tmp * b_J_tmp_tmp * c_J_tmp_tmp * 0.24999999999999994) /
      n_T1_tmp;
  a[1] = 1.0;
  h_T1_tmp = D13 * D11;
  j_T1_tmp = o_T1_tmp * d_J_tmp_tmp;
  k_T1_tmp = 6.123233995736766E-17 * D11 * c_T1_tmp;
  l_T1_tmp = 3.749399456654644E-33 * d_J_tmp_tmp * c_T1_tmp;
  o_T1_tmp = 6.123233995736766E-17 * c_T1_tmp;
  cy = d_J_tmp_tmp * c_T1_tmp;
  ks = 6.123233995736766E-17 * J_tmp_tmp * d_J_tmp_tmp * 0.86602540378443871;
  D12_tmp = J_tmp_tmp * 0.86602540378443871;
  e_D11_tmp_tmp = E12 * 0.86602540378443871;
  f_D11_tmp_tmp = p_T1_tmp * c_J_tmp_tmp * 0.24999999999999994;
  phi1_idx_0 = T1_tmp_tmp * c_J_tmp_tmp * 0.24999999999999994;
  D23_tmp = cy * c_J_tmp_tmp * 0.24999999999999994;
  b_D23_tmp = J_tmp_tmp * 0.86602540378443871 * b_J_tmp_tmp * c_J_tmp_tmp *
              0.49999999999999994;
  D11_tmp_tmp = p_T1_tmp * b_T1_tmp * c_J_tmp_tmp * 0.24999999999999994;
  cy = cy * b_T1_tmp * c_J_tmp_tmp * 0.24999999999999994;
  c_D11_tmp_tmp =
      e_D11_tmp_tmp * b_J_tmp_tmp * c_J_tmp_tmp * 0.49999999999999994;
  a_tmp = D12_tmp * c_T1_tmp * b_J_tmp_tmp * c_J_tmp_tmp * 0.49999999999999994;
  a[2] =
      -(((((((((((((((((((((((((((((((((((3.9359389436709931E-17 * J_tmp_tmp *
                                              d_J_tmp_tmp *
                                              0.49999999999999994 -
                                          0.64278760968653936 * J_tmp_tmp *
                                              c_J_tmp_tmp *
                                              0.49999999999999994) +
                                         h_T1_tmp * 0.24999999999999994) -
                                        E11 * D11 * 0.24999999999999994) +
                                       j_T1_tmp * c_J_tmp_tmp *
                                           0.24999999999999994) -
                                      3.749399456654644E-33 * T1_tmp *
                                          d_J_tmp_tmp * c_J_tmp_tmp *
                                          0.24999999999999994) -
                                     D13 * F11 * 0.24999999999999994) +
                                    k_T1_tmp * 0.24999999999999994) +
                                   E11 * F11 * 0.24999999999999994) +
                                  l_T1_tmp * c_J_tmp_tmp *
                                      0.24999999999999994) -
                                 f_D11_tmp_tmp) +
                                phi1_idx_0) -
                               o_T1_tmp * F11 * 0.24999999999999994) -
                              D23_tmp) +
                             q_T1_tmp * c_J_tmp_tmp * 0.49999999999999994) +
                            r_T1_tmp * 0.49999999999999994) -
                           s_T1_tmp * c_J_tmp_tmp * 0.49999999999999994) -
                          t_T1_tmp * 0.49999999999999994) +
                         ks * b_J_tmp_tmp * 0.49999999999999994) -
                        b_D23_tmp) -
                       h_T1_tmp * b_T1_tmp * 0.24999999999999994) -
                      j_T1_tmp * b_T1_tmp * c_J_tmp_tmp * 0.24999999999999994) +
                     D13 * b_T1_tmp * F11 * 0.24999999999999994) -
                    k_T1_tmp * b_T1_tmp * 0.24999999999999994) -
                   l_T1_tmp * b_T1_tmp * c_J_tmp_tmp * 0.24999999999999994) +
                  D11_tmp_tmp) +
                 o_T1_tmp * b_T1_tmp * F11 * 0.24999999999999994) +
                cy) -
               D13 * J_tmp_tmp * d_J_tmp_tmp * 0.86602540378443871 *
                   b_J_tmp_tmp * 0.49999999999999994) -
              ks * c_T1_tmp * b_J_tmp_tmp * 0.49999999999999994) +
             c_D11_tmp_tmp) +
            a_tmp) +
           u_T1_tmp * b_J_tmp_tmp * 0.49999999999999994) -
          v_T1_tmp * b_J_tmp_tmp * c_J_tmp_tmp * 0.49999999999999994) +
         m_T1_tmp * b_J_tmp_tmp * 0.49999999999999994) -
        w_T1_tmp * b_J_tmp_tmp * c_J_tmp_tmp * 0.49999999999999994) /
      n_T1_tmp;
  D13 = i_a_tmp * 0.86602540378443871;
  D12 *= 0.75000000000000011;
  h_T1_tmp = -0.49999999999999978 * d_T1_tmp;
  E11 = -0.49999999999999978 * T1_tmp;
  j_T1_tmp = E11 * 0.86602540378443871;
  i_T1_tmp *= 0.86602540378443871;
  k_T1_tmp = b_D11_tmp_tmp * e_J_tmp_tmp;
  l_T1_tmp =
      -0.99999999999999956 * J_tmp_tmp * d_J_tmp_tmp * 0.86602540378443871;
  m_T1_tmp = b_D11_tmp_tmp * -0.49999999999999978 * e_J_tmp_tmp;
  n_T1_tmp = d_D11_tmp_tmp * -0.49999999999999978;
  o_T1_tmp = d_D11_tmp_tmp * e_J_tmp_tmp;
  q_T1_tmp = 0.24999999999999978 * d_T1_tmp;
  r_T1_tmp = h_T1_tmp * 0.86602540378443871;
  s_T1_tmp = -0.43301270189221919 * c_T1_tmp;
  t_T1_tmp = b_D11_tmp_tmp * -0.49999999999999978 * 0.766044443118978 * F13;
  u_T1_tmp = b_D11_tmp_tmp * d_J_tmp_tmp * 0.766044443118978 *
             0.86602540378443871 * F13;
  v_T1_tmp = n_T1_tmp * e_J_tmp_tmp * 0.766044443118978;
  w_T1_tmp = o_T1_tmp * d_J_tmp_tmp * 0.766044443118978 * 0.86602540378443871;
  i_a_tmp = r_T1_tmp * b_T1_tmp;
  ks = s_T1_tmp * b_T1_tmp;
  b_a_tmp = m_T1_tmp * d_J_tmp_tmp * 0.766044443118978;
  c_a_tmp = k_T1_tmp * 0.766044443118978 * 0.86602540378443871;
  n_T1_tmp = n_T1_tmp * d_J_tmp_tmp * 0.766044443118978 * F13;
  d_a_tmp = d_D11_tmp_tmp * 0.766044443118978 * 0.86602540378443871 * F13;
  o_T1_tmp =
      ((((((((b_D11_tmp_tmp * J_tmp_tmp * 0.86602540378443871 *
                  0.766044443118978 * F13 -
              o_T1_tmp * J_tmp_tmp * 0.86602540378443871 * 0.766044443118978) +
             c_a_tmp * c_J_tmp_tmp * 0.49999999999999994) +
            n_T1_tmp * 0.49999999999999994) +
           d_a_tmp * c_J_tmp_tmp * 0.49999999999999994) +
          b_a_tmp * 0.49999999999999994) +
         t_T1_tmp * b_J_tmp_tmp * c_J_tmp_tmp * 0.49999999999999994) -
        u_T1_tmp * b_J_tmp_tmp * 0.49999999999999994) -
       v_T1_tmp * b_J_tmp_tmp * c_J_tmp_tmp * 0.49999999999999994) +
      w_T1_tmp * b_J_tmp_tmp * 0.49999999999999994;
  a[3] =
      ((((((((((((((((((((((((((((((((e_a_tmp - f_a_tmp) - g_a_tmp) - h_a_tmp) +
                                   k_T1_tmp * 0.86602540378443871 *
                                       0.766044443118978 * b_J_tmp_tmp) +
                                  d_D11_tmp_tmp * 0.86602540378443871 *
                                      0.766044443118978 * F13 * b_J_tmp_tmp) -
                                 -0.32139380484326951 * b_J_tmp_tmp *
                                     c_J_tmp_tmp * 0.49999999999999994) +
                                0.64278760968653936 * d_J_tmp_tmp *
                                    0.86602540378443871 * b_J_tmp_tmp *
                                    0.49999999999999994) -
                               D12 * b_J_tmp_tmp * 0.24999999999999994) -
                              0.24999999999999978 * J_tmp_tmp * b_J_tmp_tmp *
                                  F11 * 0.24999999999999994) -
                             j_T1_tmp * c_J_tmp_tmp * 0.49999999999999994) +
                            i_T1_tmp * 0.49999999999999994) +
                           -0.43301270189221919 * b_T1_tmp * c_J_tmp_tmp *
                               0.49999999999999994) -
                          D13 * b_T1_tmp * 0.49999999999999994) -
                         ks * c_J_tmp_tmp * 0.49999999999999994) +
                        D13 * c_T1_tmp * b_T1_tmp * 0.49999999999999994) +
                       q_T1_tmp * J_tmp_tmp * b_J_tmp_tmp * F11 *
                           0.24999999999999994) +
                      j_a_tmp * 0.75000000000000011 * b_J_tmp_tmp *
                          0.24999999999999994) +
                     D12 * c_T1_tmp * b_J_tmp_tmp * 0.24999999999999994) +
                    0.24999999999999978 * J_tmp_tmp * c_T1_tmp * b_J_tmp_tmp *
                        F11 * 0.24999999999999994) +
                   h_T1_tmp * T1_tmp * 0.86602540378443871 * c_J_tmp_tmp *
                       0.49999999999999994) -
                  l_a_tmp * 0.86602540378443871 * 0.49999999999999994) -
                 i_a_tmp * c_J_tmp_tmp * 0.49999999999999994) +
                j_T1_tmp * c_T1_tmp * c_J_tmp_tmp * 0.49999999999999994) +
               m_a_tmp * 0.86602540378443871 * b_T1_tmp * 0.49999999999999994) -
              i_T1_tmp * c_T1_tmp * 0.49999999999999994) +
             l_T1_tmp * b_J_tmp_tmp * c_J_tmp_tmp * 0.24999999999999994) -
            m_T1_tmp * J_tmp_tmp * 0.766044443118978 * c_J_tmp_tmp *
                0.49999999999999994) +
           k_T1_tmp * J_tmp_tmp * d_J_tmp_tmp * 0.766044443118978 *
               0.86602540378443871 * 0.49999999999999994) -
          d_D11_tmp_tmp * -0.49999999999999978 * J_tmp_tmp * 0.766044443118978 *
              F13 * c_J_tmp_tmp * 0.49999999999999994) +
         d_D11_tmp_tmp * J_tmp_tmp * d_J_tmp_tmp * 0.766044443118978 *
             0.86602540378443871 * F13 * 0.49999999999999994) -
        -0.99999999999999956 * d_T1_tmp * J_tmp_tmp * d_J_tmp_tmp *
            0.86602540378443871 * b_J_tmp_tmp * c_J_tmp_tmp *
            0.24999999999999994) -
       l_T1_tmp * c_T1_tmp * b_J_tmp_tmp * c_J_tmp_tmp * 0.24999999999999994) /
      o_T1_tmp;
  a[4] = 1.0;
  D12 = h_T1_tmp * D11 * 0.86602540378443871;
  D13 = q_T1_tmp * d_J_tmp_tmp;
  i_T1_tmp = -0.49999999999999978 * D11 * 0.86602540378443871 * c_T1_tmp;
  k_T1_tmp = 0.24999999999999978 * d_J_tmp_tmp * c_T1_tmp;
  l_T1_tmp = p_T1_tmp * 0.75000000000000011;
  m_T1_tmp = d_J_tmp_tmp * 0.75000000000000011 * c_T1_tmp;
  p_T1_tmp =
      -0.49999999999999978 * J_tmp_tmp * d_J_tmp_tmp * 0.86602540378443871;
  q_T1_tmp = D12_tmp * 0.86602540378443871;
  a[5] =
      (((((((((((((((((((((((((((((((((((-0.32139380484326951 * J_tmp_tmp *
                                             d_J_tmp_tmp * 0.49999999999999994 +
                                         f_a_tmp * c_J_tmp_tmp *
                                             0.49999999999999994) +
                                        D12 * 0.24999999999999994) -
                                       E11 * D11 * 0.86602540378443871 *
                                           0.24999999999999994) -
                                      D13 * c_J_tmp_tmp * 0.24999999999999994) +
                                     0.24999999999999978 * T1_tmp *
                                         d_J_tmp_tmp * c_J_tmp_tmp *
                                         0.24999999999999994) -
                                    r_T1_tmp * F11 * 0.24999999999999994) +
                                   i_T1_tmp * 0.24999999999999994) +
                                  j_T1_tmp * F11 * 0.24999999999999994) -
                                 k_T1_tmp * c_J_tmp_tmp * 0.24999999999999994) +
                                l_T1_tmp * c_J_tmp_tmp * 0.24999999999999994) -
                               T1_tmp_tmp * 0.75000000000000011 * c_J_tmp_tmp *
                                   0.24999999999999994) -
                              s_T1_tmp * F11 * 0.24999999999999994) +
                             m_T1_tmp * c_J_tmp_tmp * 0.24999999999999994) -
                            t_T1_tmp * c_J_tmp_tmp * 0.49999999999999994) +
                           u_T1_tmp * 0.49999999999999994) +
                          v_T1_tmp * c_J_tmp_tmp * 0.49999999999999994) -
                         w_T1_tmp * 0.49999999999999994) -
                        p_T1_tmp * b_J_tmp_tmp * 0.49999999999999994) -
                       q_T1_tmp * b_J_tmp_tmp * c_J_tmp_tmp *
                           0.49999999999999994) -
                      D12 * b_T1_tmp * 0.24999999999999994) +
                     D13 * b_T1_tmp * c_J_tmp_tmp * 0.24999999999999994) +
                    i_a_tmp * F11 * 0.24999999999999994) -
                   i_T1_tmp * b_T1_tmp * 0.24999999999999994) +
                  k_T1_tmp * b_T1_tmp * c_J_tmp_tmp * 0.24999999999999994) -
                 l_T1_tmp * b_T1_tmp * c_J_tmp_tmp * 0.24999999999999994) +
                ks * F11 * 0.24999999999999994) -
               m_T1_tmp * b_T1_tmp * c_J_tmp_tmp * 0.24999999999999994) +
              h_T1_tmp * J_tmp_tmp * d_J_tmp_tmp * 0.86602540378443871 *
                  b_J_tmp_tmp * 0.49999999999999994) +
             p_T1_tmp * c_T1_tmp * b_J_tmp_tmp * 0.49999999999999994) +
            e_D11_tmp_tmp * 0.86602540378443871 * b_J_tmp_tmp * c_J_tmp_tmp *
                0.49999999999999994) +
           q_T1_tmp * c_T1_tmp * b_J_tmp_tmp * c_J_tmp_tmp *
               0.49999999999999994) -
          b_a_tmp * b_J_tmp_tmp * 0.49999999999999994) -
         c_a_tmp * b_J_tmp_tmp * c_J_tmp_tmp * 0.49999999999999994) -
        n_T1_tmp * b_J_tmp_tmp * 0.49999999999999994) -
       d_a_tmp * b_J_tmp_tmp * c_J_tmp_tmp * 0.49999999999999994) /
      o_T1_tmp;
  D12 = T1_tmp * 0.86602540378443871;
  D13 = D21 * J_tmp_tmp;
  h_T1_tmp = E13 * e_J_tmp_tmp;
  i_T1_tmp = h_T1_tmp * J_tmp_tmp;
  j_T1_tmp = 2.0 * J_tmp_tmp * d_J_tmp_tmp;
  k_T1_tmp = D21 * e_J_tmp_tmp;
  l_T1_tmp = k_T1_tmp * d_J_tmp_tmp;
  m_T1_tmp = E13 * d_J_tmp_tmp * F13;
  n_T1_tmp = E13 * F13;
  o_T1_tmp = D21 * d_J_tmp_tmp * F13;
  p_T1_tmp = h_T1_tmp * d_J_tmp_tmp;
  q_T1_tmp = D21 * F13;
  r_T1_tmp =
      ((((((((k_T1_tmp * J_tmp_tmp * 0.86602540378443871 +
              E13 * J_tmp_tmp * 0.86602540378443871 * F13) -
             o_T1_tmp * 0.49999999999999994 * 0.50000000000000011) +
            p_T1_tmp * 0.49999999999999994 * 0.50000000000000011) +
           q_T1_tmp * c_J_tmp_tmp * 0.49999999999999994 * -0.8660254037844386) -
          h_T1_tmp * c_J_tmp_tmp * 0.49999999999999994 * -0.8660254037844386) +
         l_T1_tmp * b_J_tmp_tmp * 0.49999999999999994 * -0.8660254037844386) +
        k_T1_tmp * b_J_tmp_tmp * c_J_tmp_tmp * 0.49999999999999994 *
            0.50000000000000011) +
       m_T1_tmp * b_J_tmp_tmp * 0.49999999999999994 * -0.8660254037844386) +
      n_T1_tmp * b_J_tmp_tmp * c_J_tmp_tmp * 0.49999999999999994 *
          0.50000000000000011;
  a[6] =
      -(((((((((((((((((((((((((((((e_a_tmp - g_a_tmp) - h_a_tmp) +
                                  D21 * 0.86602540378443871 * F13 *
                                      b_J_tmp_tmp) -
                                 h_T1_tmp * 0.86602540378443871 * b_J_tmp_tmp) -
                                J_tmp_tmp * b_J_tmp_tmp * F11 *
                                    0.24999999999999994 * 0.25000000000000011) -
                               n_a_tmp * 0.74999999999999989) -
                              F23 * -0.8660254037844386) -
                             D12 * c_J_tmp_tmp * 0.49999999999999994 *
                                 0.50000000000000011) +
                            F22 * -0.8660254037844386) +
                           0.86602540378443871 * b_T1_tmp * c_J_tmp_tmp *
                               0.49999999999999994 * 0.50000000000000011) -
                          E23 * -0.8660254037844386) -
                         d_T1_tmp * 0.86602540378443871 * b_T1_tmp *
                             c_J_tmp_tmp * 0.49999999999999994 *
                             0.50000000000000011) +
                        F21 * -0.8660254037844386) +
                       D12 * c_T1_tmp * c_J_tmp_tmp * 0.49999999999999994 *
                           0.50000000000000011) -
                      D13 * d_J_tmp_tmp * F13 * 0.49999999999999994 *
                          -0.8660254037844386) -
                     D13 * F13 * c_J_tmp_tmp * 0.49999999999999994 *
                         0.50000000000000011) +
                    i_T1_tmp * d_J_tmp_tmp * 0.49999999999999994 *
                        -0.8660254037844386) +
                   i_T1_tmp * c_J_tmp_tmp * 0.49999999999999994 *
                       0.50000000000000011) -
                  E22 * -0.8660254037844386) -
                 0.86602540378443871 * c_T1_tmp * b_T1_tmp * c_J_tmp_tmp *
                     0.49999999999999994 * 0.50000000000000011) +
                E12 * b_J_tmp_tmp * F11 * 0.24999999999999994 *
                    0.25000000000000011) +
               D22 * 0.74999999999999989) +
              D23 * 0.74999999999999989) +
             J_tmp_tmp * c_T1_tmp * b_J_tmp_tmp * F11 * 0.24999999999999994 *
                 0.25000000000000011) +
            E21 * -0.8660254037844386) +
           k_a_tmp * 0.86602540378443871 * c_J_tmp_tmp * 0.49999999999999994 *
               0.50000000000000011) -
          j_T1_tmp * b_J_tmp_tmp * c_J_tmp_tmp * 0.24999999999999994 *
              0.50000000000000011 * -0.8660254037844386) +
         2.0 * d_T1_tmp * J_tmp_tmp * d_J_tmp_tmp * b_J_tmp_tmp * c_J_tmp_tmp *
             0.24999999999999994 * 0.50000000000000011 * -0.8660254037844386) +
        j_T1_tmp * c_T1_tmp * b_J_tmp_tmp * c_J_tmp_tmp * 0.24999999999999994 *
            0.50000000000000011 * -0.8660254037844386) /
      r_T1_tmp;
  a[7] = 1.0;
  D12 = d_T1_tmp * D11;
  D13 = D11 * c_T1_tmp;
  i_T1_tmp = J_tmp_tmp * d_J_tmp_tmp * 0.86602540378443871;
  a[8] =
      -(((((((((((((((((((((((((((((((((l_T1_tmp * 0.49999999999999994 *
                                            -0.8660254037844386 +
                                        k_T1_tmp * c_J_tmp_tmp *
                                            0.49999999999999994 *
                                            0.50000000000000011) +
                                       m_T1_tmp * 0.49999999999999994 *
                                           -0.8660254037844386) +
                                      n_T1_tmp * c_J_tmp_tmp *
                                          0.49999999999999994 *
                                          0.50000000000000011) -
                                     f_D11_tmp_tmp * 0.25000000000000011) +
                                    phi1_idx_0 * 0.25000000000000011) -
                                   D23_tmp * 0.25000000000000011) +
                                  f_D11_tmp_tmp * 0.74999999999999989) -
                                 phi1_idx_0 * 0.74999999999999989) -
                                D12 * 0.24999999999999994 *
                                    0.50000000000000011 * -0.8660254037844386) +
                               T1_tmp * D11 * 0.24999999999999994 *
                                   0.50000000000000011 * -0.8660254037844386) +
                              D23_tmp * 0.74999999999999989) +
                             d_T1_tmp * F11 * 0.24999999999999994 *
                                 0.50000000000000011 * -0.8660254037844386) -
                            D13 * 0.24999999999999994 * 0.50000000000000011 *
                                -0.8660254037844386) -
                           T1_tmp * F11 * 0.24999999999999994 *
                               0.50000000000000011 * -0.8660254037844386) +
                          c_T1_tmp * F11 * 0.24999999999999994 *
                              0.50000000000000011 * -0.8660254037844386) -
                         o_T1_tmp * b_J_tmp_tmp * 0.49999999999999994 *
                             0.50000000000000011) +
                        p_T1_tmp * b_J_tmp_tmp * 0.49999999999999994 *
                            0.50000000000000011) +
                       q_T1_tmp * b_J_tmp_tmp * c_J_tmp_tmp *
                           0.49999999999999994 * -0.8660254037844386) -
                      h_T1_tmp * b_J_tmp_tmp * c_J_tmp_tmp *
                          0.49999999999999994 * -0.8660254037844386) -
                     i_T1_tmp * b_J_tmp_tmp * 0.49999999999999994 *
                         0.50000000000000011) +
                    b_D23_tmp * -0.8660254037844386) +
                   D11_tmp_tmp * 0.25000000000000011) +
                  cy * 0.25000000000000011) -
                 D11_tmp_tmp * 0.74999999999999989) +
                D12 * b_T1_tmp * 0.24999999999999994 * 0.50000000000000011 *
                    -0.8660254037844386) -
               cy * 0.74999999999999989) -
              d_T1_tmp * b_T1_tmp * F11 * 0.24999999999999994 *
                  0.50000000000000011 * -0.8660254037844386) +
             D13 * b_T1_tmp * 0.24999999999999994 * 0.50000000000000011 *
                 -0.8660254037844386) -
            c_T1_tmp * b_T1_tmp * F11 * 0.24999999999999994 *
                0.50000000000000011 * -0.8660254037844386) +
           E12 * d_J_tmp_tmp * 0.86602540378443871 * b_J_tmp_tmp *
               0.49999999999999994 * 0.50000000000000011) +
          i_T1_tmp * c_T1_tmp * b_J_tmp_tmp * 0.49999999999999994 *
              0.50000000000000011) -
         c_D11_tmp_tmp * -0.8660254037844386) -
        a_tmp * -0.8660254037844386) /
      r_T1_tmp;
  for (i = 0; i < 3; i++) {
    Ts[i] = (a[i] * t1 + a[i + 3] * t2) + a[i + 6] * t3;
  }
  *tr = Ts[0];
  *tp = Ts[1];
  *ty = Ts[2];
}

/*
 * File trailer for Jacobian_S.c
 *
 * [EOF]
 */

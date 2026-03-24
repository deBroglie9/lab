/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * FK_7DOF.c
 *
 * Code generation for function 'FK_7DOF'
 *
 */

/* Include files */
#include "FK_7DOF.h"
#include "FK_7DOF_data.h"
#include "FK_7DOF_initialize.h"
#include "rt_wutil.h"
#include "atan.h"
#include "driver.h"
#include "roots.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */
void FK_7DOF(const double c[7], double T[16])
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
  static const double dv[16] = {1.0,
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
  static const double dv1[16] = {0.82526879545537513,
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
  static const short e_b[16] = {1, 0, 0, 0, 0,   1, 0, 0,
                                0, 0, 1, 0, 320, 0, 0, 1};
  static const unsigned char f_b[16] = {1U, 0U, 0U, 0U, 0U,   1U, 0U, 0U,
                                        0U, 0U, 1U, 0U, 235U, 0U, 0U, 1U};
  static const signed char iv[4] = {1, 0, 0, 0};
  static const signed char iv1[4] = {0, 0, 0, 1};
  static const signed char iv2[4] = {0, 0, 1, 0};
  static const signed char d_b[3] = {0, 0, 1};
  creal_T T2_tmp[16];
  creal_T b_T1[16];
  creal_T b_T2_tmp[16];
  creal_T b_ks[16];
  creal_T A[9];
  creal_T Y[9];
  creal_T YY_data[8];
  creal_T Y_data[8];
  creal_T c_T1[3];
  creal_T c_T2_tmp[3];
  creal_T c_b[3];
  creal_T ks;
  double T1[16];
  double T1_tmp[16];
  double b_T1_tmp[16];
  double dv2[16];
  double Rot_shoulder[9];
  double jacob[4];
  double b_expl_temp[2];
  double c_expl_temp[2];
  double d1[2];
  double phi1[2];
  double D11;
  double D11_tmp;
  double D11_tmp_tmp;
  double D12;
  double D12_tmp;
  double D13;
  double D21;
  double D21_tmp;
  double D22;
  double D23;
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
  double a_tmp;
  double b_D11_tmp;
  double b_D11_tmp_tmp;
  double b_a_tmp;
  double c_D11_tmp;
  double c_a_tmp;
  double cp;
  double cr;
  double cy;
  double d_a_tmp;
  double e_a_tmp;
  double f_a_tmp;
  double g_a_tmp;
  double h_a_tmp;
  double i_a_tmp;
  double j_a_tmp;
  double k_a_tmp;
  double l_a_tmp;
  double m_a_tmp;
  double phi;
  int YY_size;
  int b_i;
  int i;
  int partialTrueCount;
  int trueCount;
  char expl_temp[19];
  signed char tmp_data[8];
  if (!isInitialized_FK_7DOF) {
    FK_7DOF_initialize();
  }
  /*  c1 = 95.174561; */
  /*  c2 = 85.770264; */
  /*  c3 = 82.4304198; */
  /* 结果来源于"test4,m"此处将cr,cp,cy替换为0，以求得三力臂的初始角度,最新一次修改于2023.11.13
   */
  /* %此向量本来在c3坐标系中，为了便于下面的干涉检查计算，做统一坐标系处理 */
  /* 此向量本来在c3坐标系中，为了便于下面的干涉检查计算，做统一坐标系处理 */
  /*  eq1=w3(1)*v3(1)+w3(2)*v3(2)+w3(3)*v3(3)-R^2*cos(gama); */
  /*  persistent phi */
  /*  if isempty(phi) */
  /*      phi=0; */
  /*  end */
  /*   */
  /*  persistent ks */
  /*  if isempty(ks) */
  /*      ks=0; */
  /*  end */
  /*  persistent Y */
  /*  if isempty(Y) */
  /*      Y=zeros(8,1); */
  /*  end */
  /*  Yy=zeros(8,1); */
  /*  R=86.5; */
  /* 此L1是加了R的大臂总长度 */
  /*  Y=zeros(1,8); */
  D11_tmp_tmp = cos((c[0] - 1.298210328476112) + 1.5707963267948966);
  phi = cos(c[1] - 1.52502572060903);
  b_D11_tmp_tmp = sin((c[0] - 1.298210328476112) + 1.5707963267948966);
  D11_tmp = sin(c[1] - 1.52502572060903);
  cp = D11_tmp_tmp * D11_tmp;
  b_D11_tmp = cp * 0.64278760968653936;
  cr = b_D11_tmp_tmp * phi;
  c_D11_tmp = cr * 0.64278760968653936;
  D11 =
      (b_D11_tmp * 0.50000000000000011 * 0.766044443118978 *
           0.84580407061574392 -
       0.20823860156791746) -
      c_D11_tmp * 0.50000000000000011 * 0.766044443118978 * 0.84580407061574392;
  D12_tmp = D11_tmp_tmp * phi;
  phi = b_D11_tmp_tmp * D11_tmp;
  D12 = D12_tmp * 0.766044443118978 * 0.84580407061574392 +
        phi * 0.766044443118978 * 0.84580407061574392;
  D13 =
      (b_D11_tmp * 0.53349364956842527 * 0.766044443118978 *
           0.8660254037844386 -
       0.22749997285668702) -
      c_D11_tmp * 0.53349364956842527 * 0.766044443118978 * 0.8660254037844386;
  E11 =
      D12_tmp * 0.50000000000000011 * 0.766044443118978 * 0.84580407061574392 +
      phi * 0.50000000000000011 * 0.766044443118978 * 0.84580407061574392;
  E12 = (0.41647720313583492 -
         b_D11_tmp * 0.766044443118978 * 0.84580407061574392) +
        c_D11_tmp * 0.766044443118978 * 0.84580407061574392;
  E13 = D12_tmp * 0.53349364956842527 * 0.766044443118978 * 0.8660254037844386 +
        phi * 0.53349364956842527 * 0.766044443118978 * 0.8660254037844386;
  F11 = (cp * 0.58682408883346515 * 0.84580407061574392 * 0.8660254037844386 +
         0.30264631904955869) -
        cr * 0.58682408883346515 * 0.84580407061574392 * 0.8660254037844386;
  F13 = ((cr * 0.53349364956842527 * 0.50000000000000011 * 0.58682408883346515 -
          0.1102133623809971) -
         cp * 0.53349364956842527 * 0.50000000000000011 * 0.58682408883346515) -
        0.50000000000000011;
  c_D11_tmp = cos((c[2] + 1.5707963267948966) - 0.30696770204475443);
  D12_tmp = sin((c[2] + 1.5707963267948966) - 0.30696770204475443);
  phi = b_D11_tmp_tmp * 0.64278760968653936 * 0.50000000000000011;
  D21_tmp = D11_tmp_tmp * 0.64278760968653936 * 0.50000000000000011;
  D21 =
      -c_D11_tmp * 0.84580407061574392 *
          (D11_tmp_tmp * 0.56474013072176321 + phi * 0.82526879545537513) -
      D12_tmp * 0.84580407061574392 *
          (b_D11_tmp_tmp * 0.56474013072176321 - D21_tmp * 0.82526879545537513);
  b_D11_tmp = D12_tmp * 0.84580407061574392;
  D22 = c_D11_tmp * 0.84580407061574392 *
            (D11_tmp_tmp * 0.82526879545537513 - phi * 0.56474013072176321) +
        b_D11_tmp * (b_D11_tmp_tmp * 0.82526879545537513 +
                     D21_tmp * 0.56474013072176321);
  cr = D11_tmp_tmp * D12_tmp;
  D21_tmp = b_D11_tmp_tmp * c_D11_tmp;
  D23 =
      cr * 0.64278760968653936 * 0.53349364956842527 * 0.8660254037844386 -
      D21_tmp * 0.64278760968653936 * 0.53349364956842527 * 0.8660254037844386;
  phi = c_D11_tmp * 0.84580407061574392;
  D11_tmp = b_D11_tmp_tmp * 0.64278760968653936;
  cp = D11_tmp_tmp * 0.64278760968653936;
  E21 = phi * (D11_tmp_tmp * 0.50000000000000011 * 0.82526879545537513 -
               D11_tmp * 0.56474013072176321) +
        b_D11_tmp * (cp * 0.56474013072176321 +
                     b_D11_tmp_tmp * 0.50000000000000011 * 0.82526879545537513);
  E22 = phi * (D11_tmp * 0.82526879545537513 +
               D11_tmp_tmp * 0.50000000000000011 * 0.56474013072176321) -
        b_D11_tmp * (cp * 0.82526879545537513 -
                     b_D11_tmp_tmp * 0.50000000000000011 * 0.56474013072176321);
  E23 = D11_tmp_tmp * c_D11_tmp * 0.53349364956842527 * 0.8660254037844386 +
        b_D11_tmp_tmp * D12_tmp * 0.53349364956842527 * 0.8660254037844386;
  phi = cr * 0.766044443118978 * 0.84580407061574392 * 0.8660254037844386;
  D11_tmp =
      D21_tmp * 0.766044443118978 * 0.84580407061574392 * 0.8660254037844386;
  F21 = phi * 0.82526879545537513 - D11_tmp * 0.82526879545537513;
  F22 = phi * 0.56474013072176321 - D11_tmp * 0.56474013072176321;
  F23 =
      (D21_tmp * 0.53349364956842527 * 0.50000000000000011 * 0.766044443118978 -
       cr * 0.53349364956842527 * 0.50000000000000011 * 0.766044443118978) -
      0.50000000000000011;
  phi = D12 - D13;
  D11_tmp = D22 - D23;
  cp = F22 - F23;
  b_D11_tmp = phi * cp - D11_tmp * -F13;
  c_D11_tmp = E12 - E13;
  D12_tmp = E22 - E23;
  cr = phi * D12_tmp - D11_tmp * c_D11_tmp;
  D21_tmp = c_D11_tmp * cp - D12_tmp * -F13;
  a_tmp = ((2.0 * F21 * phi - 2.0 * F11 * D11_tmp) - 2.0 * D21 * -F13) +
          2.0 * D11 * cp;
  cy = ((2.0 * E21 * phi - 2.0 * E11 * D11_tmp) - 2.0 * D21 * c_D11_tmp) +
       2.0 * D11 * D12_tmp;
  D11_tmp_tmp =
      ((2.0 * F21 * c_D11_tmp - 2.0 * F11 * D12_tmp) - 2.0 * E21 * -F13) +
      2.0 * E11 * cp;
  b_D11_tmp_tmp = 4.0 * D11 * F21 - 4.0 * D21 * F11;
  b_a_tmp = 4.0 * D11 * E21 - 4.0 * D21 * E11;
  c_a_tmp = 4.0 * E11 * F21 - 4.0 * E21 * F11;
  d_a_tmp = F22 + F23;
  e_a_tmp = D22 + D23;
  f_a_tmp = D12 + D13;
  g_a_tmp = ((phi * d_a_tmp - D11_tmp * F13) - -F13 * e_a_tmp) + cp * f_a_tmp;
  h_a_tmp = E22 + E23;
  i_a_tmp = E12 + E13;
  cp = ((c_D11_tmp * d_a_tmp - D12_tmp * F13) - -F13 * h_a_tmp) + cp * i_a_tmp;
  phi = ((phi * h_a_tmp - D11_tmp * i_a_tmp) - c_D11_tmp * e_a_tmp) +
        D12_tmp * f_a_tmp;
  D11_tmp =
      ((2.0 * E21 * f_a_tmp - 2.0 * E11 * e_a_tmp) - 2.0 * D21 * i_a_tmp) +
      2.0 * D11 * h_a_tmp;
  c_D11_tmp = ((2.0 * F21 * f_a_tmp - 2.0 * F11 * e_a_tmp) - 2.0 * D21 * F13) +
              2.0 * D11 * d_a_tmp;
  D12_tmp = ((2.0 * F21 * i_a_tmp - 2.0 * F11 * h_a_tmp) - 2.0 * E21 * F13) +
            2.0 * E11 * d_a_tmp;
  j_a_tmp = f_a_tmp * d_a_tmp - e_a_tmp * F13;
  e_a_tmp = f_a_tmp * h_a_tmp - e_a_tmp * i_a_tmp;
  d_a_tmp = i_a_tmp * d_a_tmp - h_a_tmp * F13;
  Rot_shoulder[0] = (b_D11_tmp * b_D11_tmp - cr * cr) + D21_tmp * D21_tmp;
  f_a_tmp = 2.0 * cr;
  h_a_tmp = 2.0 * b_D11_tmp;
  i_a_tmp = 2.0 * D21_tmp;
  Rot_shoulder[1] = (f_a_tmp * cy - h_a_tmp * a_tmp) - i_a_tmp * D11_tmp_tmp;
  k_a_tmp = 2.0 * b_a_tmp;
  l_a_tmp = 2.0 * b_D11_tmp_tmp;
  m_a_tmp = 2.0 * c_a_tmp;
  Rot_shoulder[2] = ((f_a_tmp * phi - h_a_tmp * g_a_tmp) - i_a_tmp * cp) +
                    (((((a_tmp * a_tmp - cy * cy) + D11_tmp_tmp * D11_tmp_tmp) -
                       k_a_tmp * cr) +
                      l_a_tmp * b_D11_tmp) +
                     m_a_tmp * D21_tmp);
  b_D11_tmp = 2.0 * D11_tmp_tmp;
  cr = 2.0 * a_tmp;
  D21_tmp = 2.0 * cy;
  Rot_shoulder[3] = ((k_a_tmp * cy - l_a_tmp * a_tmp) - m_a_tmp * D11_tmp_tmp) +
                    (((((cr * g_a_tmp - D21_tmp * phi) + b_D11_tmp * cp) -
                       f_a_tmp * D11_tmp) +
                      h_a_tmp * c_D11_tmp) +
                     i_a_tmp * D12_tmp);
  Rot_shoulder[4] =
      (((b_D11_tmp_tmp * b_D11_tmp_tmp - b_a_tmp * b_a_tmp) +
        c_a_tmp * c_a_tmp) +
       (((((k_a_tmp * phi - b_D11_tmp * D12_tmp) - cr * c_D11_tmp) -
          l_a_tmp * g_a_tmp) -
         m_a_tmp * cp) +
        D21_tmp * D11_tmp)) +
      (((((g_a_tmp * g_a_tmp + cp * cp) - f_a_tmp * e_a_tmp) +
         h_a_tmp * j_a_tmp) +
        i_a_tmp * d_a_tmp) -
       phi * phi);
  b_D11_tmp = 2.0 * e_a_tmp;
  cr = 2.0 * j_a_tmp;
  D21_tmp = 2.0 * d_a_tmp;
  Rot_shoulder[5] =
      ((l_a_tmp * c_D11_tmp - k_a_tmp * D11_tmp) + m_a_tmp * D12_tmp) +
      (((((b_D11_tmp * cy - cr * a_tmp) - D21_tmp * D11_tmp_tmp) +
         2.0 * D11_tmp * phi) -
        2.0 * c_D11_tmp * g_a_tmp) -
       2.0 * D12_tmp * cp);
  Rot_shoulder[6] =
      (((((l_a_tmp * j_a_tmp - k_a_tmp * e_a_tmp) + m_a_tmp * d_a_tmp) -
         D11_tmp * D11_tmp) +
        c_D11_tmp * c_D11_tmp) +
       D12_tmp * D12_tmp) +
      ((b_D11_tmp * phi - cr * g_a_tmp) - D21_tmp * cp);
  Rot_shoulder[7] = (cr * c_D11_tmp - b_D11_tmp * D11_tmp) + D21_tmp * D12_tmp;
  Rot_shoulder[8] = (j_a_tmp * j_a_tmp - e_a_tmp * e_a_tmp) + d_a_tmp * d_a_tmp;
  YY_size = roots(Rot_shoulder, YY_data);
  YY_size--;
  trueCount = 0;
  partialTrueCount = 0;
  for (i = 0; i <= YY_size; i++) {
    if (YY_data[i].im == 0.0) {
      trueCount++;
      tmp_data[partialTrueCount] = (signed char)i;
      partialTrueCount++;
    }
  }
  for (b_i = 0; b_i < trueCount; b_i++) {
    Y_data[b_i] = YY_data[tmp_data[b_i]];
  }
  /*  phi2=zeros(1,2); */
  cp = YY_data[tmp_data[0]].re;
  c_a_tmp = YY_data[tmp_data[0]].im;
  cy = cp * cp - c_a_tmp * c_a_tmp;
  D11_tmp_tmp = cp * c_a_tmp;
  D11_tmp_tmp += D11_tmp_tmp;
  d_a_tmp = E11 * 2.0 * cp;
  e_a_tmp = E11 * 2.0 * c_a_tmp;
  if (D11_tmp_tmp == 0.0) {
    if (e_a_tmp == 0.0) {
      D11_tmp = d_a_tmp / (cy + 1.0);
    } else if (d_a_tmp == 0.0) {
      D11_tmp = 0.0;
    } else {
      D11_tmp = d_a_tmp / (cy + 1.0);
    }
  } else if (cy + 1.0 == 0.0) {
    if (d_a_tmp == 0.0) {
      D11_tmp = e_a_tmp / D11_tmp_tmp;
    } else if (e_a_tmp == 0.0) {
      D11_tmp = 0.0;
    } else {
      D11_tmp = e_a_tmp / D11_tmp_tmp;
    }
  } else {
    b_D11_tmp = fabs(cy + 1.0);
    c_D11_tmp = fabs(D11_tmp_tmp);
    if (b_D11_tmp > c_D11_tmp) {
      b_D11_tmp = D11_tmp_tmp / (cy + 1.0);
      D11_tmp = (d_a_tmp + b_D11_tmp * e_a_tmp) /
                ((cy + 1.0) + b_D11_tmp * D11_tmp_tmp);
    } else if (c_D11_tmp == b_D11_tmp) {
      if (cy + 1.0 > 0.0) {
        c_D11_tmp = 0.5;
      } else {
        c_D11_tmp = -0.5;
      }
      if (D11_tmp_tmp > 0.0) {
        a_tmp = 0.5;
      } else {
        a_tmp = -0.5;
      }
      D11_tmp = (d_a_tmp * c_D11_tmp + e_a_tmp * a_tmp) / b_D11_tmp;
    } else {
      b_D11_tmp = (cy + 1.0) / D11_tmp_tmp;
      D11_tmp = (b_D11_tmp * d_a_tmp + e_a_tmp) /
                (D11_tmp_tmp + b_D11_tmp * (cy + 1.0));
    }
  }
  d_a_tmp = E12 * (1.0 - cy);
  e_a_tmp = E12 * (0.0 - D11_tmp_tmp);
  if (D11_tmp_tmp == 0.0) {
    if (e_a_tmp == 0.0) {
      phi = d_a_tmp / (cy + 1.0);
    } else if (d_a_tmp == 0.0) {
      phi = 0.0;
    } else {
      phi = d_a_tmp / (cy + 1.0);
    }
  } else if (cy + 1.0 == 0.0) {
    if (d_a_tmp == 0.0) {
      phi = e_a_tmp / D11_tmp_tmp;
    } else if (e_a_tmp == 0.0) {
      phi = 0.0;
    } else {
      phi = e_a_tmp / D11_tmp_tmp;
    }
  } else {
    b_D11_tmp = fabs(cy + 1.0);
    c_D11_tmp = fabs(D11_tmp_tmp);
    if (b_D11_tmp > c_D11_tmp) {
      b_D11_tmp = D11_tmp_tmp / (cy + 1.0);
      phi = (d_a_tmp + b_D11_tmp * e_a_tmp) /
            ((cy + 1.0) + b_D11_tmp * D11_tmp_tmp);
    } else if (c_D11_tmp == b_D11_tmp) {
      if (cy + 1.0 > 0.0) {
        c_D11_tmp = 0.5;
      } else {
        c_D11_tmp = -0.5;
      }
      if (D11_tmp_tmp > 0.0) {
        a_tmp = 0.5;
      } else {
        a_tmp = -0.5;
      }
      phi = (d_a_tmp * c_D11_tmp + e_a_tmp * a_tmp) / b_D11_tmp;
    } else {
      b_D11_tmp = (cy + 1.0) / D11_tmp_tmp;
      phi = (b_D11_tmp * d_a_tmp + e_a_tmp) /
            (D11_tmp_tmp + b_D11_tmp * (cy + 1.0));
    }
  }
  g_a_tmp = (D11_tmp + phi) + E13;
  d_a_tmp = E21 * 2.0 * cp;
  e_a_tmp = E21 * 2.0 * c_a_tmp;
  if (D11_tmp_tmp == 0.0) {
    if (e_a_tmp == 0.0) {
      D11_tmp = d_a_tmp / (cy + 1.0);
    } else if (d_a_tmp == 0.0) {
      D11_tmp = 0.0;
    } else {
      D11_tmp = d_a_tmp / (cy + 1.0);
    }
  } else if (cy + 1.0 == 0.0) {
    if (d_a_tmp == 0.0) {
      D11_tmp = e_a_tmp / D11_tmp_tmp;
    } else if (e_a_tmp == 0.0) {
      D11_tmp = 0.0;
    } else {
      D11_tmp = e_a_tmp / D11_tmp_tmp;
    }
  } else {
    b_D11_tmp = fabs(cy + 1.0);
    c_D11_tmp = fabs(D11_tmp_tmp);
    if (b_D11_tmp > c_D11_tmp) {
      b_D11_tmp = D11_tmp_tmp / (cy + 1.0);
      D11_tmp = (d_a_tmp + b_D11_tmp * e_a_tmp) /
                ((cy + 1.0) + b_D11_tmp * D11_tmp_tmp);
    } else if (c_D11_tmp == b_D11_tmp) {
      if (cy + 1.0 > 0.0) {
        c_D11_tmp = 0.5;
      } else {
        c_D11_tmp = -0.5;
      }
      if (D11_tmp_tmp > 0.0) {
        a_tmp = 0.5;
      } else {
        a_tmp = -0.5;
      }
      D11_tmp = (d_a_tmp * c_D11_tmp + e_a_tmp * a_tmp) / b_D11_tmp;
    } else {
      b_D11_tmp = (cy + 1.0) / D11_tmp_tmp;
      D11_tmp = (b_D11_tmp * d_a_tmp + e_a_tmp) /
                (D11_tmp_tmp + b_D11_tmp * (cy + 1.0));
    }
  }
  d_a_tmp = E22 * (1.0 - cy);
  e_a_tmp = E22 * (0.0 - D11_tmp_tmp);
  if (D11_tmp_tmp == 0.0) {
    if (e_a_tmp == 0.0) {
      phi = d_a_tmp / (cy + 1.0);
    } else if (d_a_tmp == 0.0) {
      phi = 0.0;
    } else {
      phi = d_a_tmp / (cy + 1.0);
    }
  } else if (cy + 1.0 == 0.0) {
    if (d_a_tmp == 0.0) {
      phi = e_a_tmp / D11_tmp_tmp;
    } else if (e_a_tmp == 0.0) {
      phi = 0.0;
    } else {
      phi = e_a_tmp / D11_tmp_tmp;
    }
  } else {
    b_D11_tmp = fabs(cy + 1.0);
    c_D11_tmp = fabs(D11_tmp_tmp);
    if (b_D11_tmp > c_D11_tmp) {
      b_D11_tmp = D11_tmp_tmp / (cy + 1.0);
      phi = (d_a_tmp + b_D11_tmp * e_a_tmp) /
            ((cy + 1.0) + b_D11_tmp * D11_tmp_tmp);
    } else if (c_D11_tmp == b_D11_tmp) {
      if (cy + 1.0 > 0.0) {
        c_D11_tmp = 0.5;
      } else {
        c_D11_tmp = -0.5;
      }
      if (D11_tmp_tmp > 0.0) {
        a_tmp = 0.5;
      } else {
        a_tmp = -0.5;
      }
      phi = (d_a_tmp * c_D11_tmp + e_a_tmp * a_tmp) / b_D11_tmp;
    } else {
      b_D11_tmp = (cy + 1.0) / D11_tmp_tmp;
      phi = (b_D11_tmp * d_a_tmp + e_a_tmp) /
            (D11_tmp_tmp + b_D11_tmp * (cy + 1.0));
    }
  }
  f_a_tmp = (D11_tmp + phi) + E23;
  d_a_tmp = F21 * 2.0 * cp;
  e_a_tmp = F21 * 2.0 * c_a_tmp;
  if (D11_tmp_tmp == 0.0) {
    if (e_a_tmp == 0.0) {
      D12_tmp = d_a_tmp / (cy + 1.0);
    } else if (d_a_tmp == 0.0) {
      D12_tmp = 0.0;
    } else {
      D12_tmp = d_a_tmp / (cy + 1.0);
    }
  } else if (cy + 1.0 == 0.0) {
    if (d_a_tmp == 0.0) {
      D12_tmp = e_a_tmp / D11_tmp_tmp;
    } else if (e_a_tmp == 0.0) {
      D12_tmp = 0.0;
    } else {
      D12_tmp = e_a_tmp / D11_tmp_tmp;
    }
  } else {
    b_D11_tmp = fabs(cy + 1.0);
    c_D11_tmp = fabs(D11_tmp_tmp);
    if (b_D11_tmp > c_D11_tmp) {
      b_D11_tmp = D11_tmp_tmp / (cy + 1.0);
      D12_tmp = (d_a_tmp + b_D11_tmp * e_a_tmp) /
                ((cy + 1.0) + b_D11_tmp * D11_tmp_tmp);
    } else if (c_D11_tmp == b_D11_tmp) {
      if (cy + 1.0 > 0.0) {
        c_D11_tmp = 0.5;
      } else {
        c_D11_tmp = -0.5;
      }
      if (D11_tmp_tmp > 0.0) {
        a_tmp = 0.5;
      } else {
        a_tmp = -0.5;
      }
      D12_tmp = (d_a_tmp * c_D11_tmp + e_a_tmp * a_tmp) / b_D11_tmp;
    } else {
      b_D11_tmp = (cy + 1.0) / D11_tmp_tmp;
      D12_tmp = (b_D11_tmp * d_a_tmp + e_a_tmp) /
                (D11_tmp_tmp + b_D11_tmp * (cy + 1.0));
    }
  }
  d_a_tmp = F22 * (1.0 - cy);
  e_a_tmp = F22 * (0.0 - D11_tmp_tmp);
  phi = F11 * 2.0 * cp;
  D11_tmp = F11 * 2.0 * c_a_tmp;
  if (D11_tmp_tmp == 0.0) {
    if (e_a_tmp == 0.0) {
      cr = d_a_tmp / (cy + 1.0);
    } else if (d_a_tmp == 0.0) {
      cr = 0.0;
    } else {
      cr = d_a_tmp / (cy + 1.0);
    }
    if (D11_tmp == 0.0) {
      D21_tmp = phi / (cy + 1.0);
    } else if (phi == 0.0) {
      D21_tmp = 0.0;
    } else {
      D21_tmp = phi / (cy + 1.0);
    }
  } else if (cy + 1.0 == 0.0) {
    if (d_a_tmp == 0.0) {
      cr = e_a_tmp / D11_tmp_tmp;
    } else if (e_a_tmp == 0.0) {
      cr = 0.0;
    } else {
      cr = e_a_tmp / D11_tmp_tmp;
    }
    if (phi == 0.0) {
      D21_tmp = D11_tmp / D11_tmp_tmp;
    } else if (D11_tmp == 0.0) {
      D21_tmp = 0.0;
    } else {
      D21_tmp = D11_tmp / D11_tmp_tmp;
    }
  } else {
    b_D11_tmp = fabs(cy + 1.0);
    c_D11_tmp = fabs(D11_tmp_tmp);
    if (b_D11_tmp > c_D11_tmp) {
      b_D11_tmp = D11_tmp_tmp / (cy + 1.0);
      cr = (d_a_tmp + b_D11_tmp * e_a_tmp) /
           ((cy + 1.0) + b_D11_tmp * D11_tmp_tmp);
    } else if (c_D11_tmp == b_D11_tmp) {
      if (cy + 1.0 > 0.0) {
        c_D11_tmp = 0.5;
      } else {
        c_D11_tmp = -0.5;
      }
      if (D11_tmp_tmp > 0.0) {
        a_tmp = 0.5;
      } else {
        a_tmp = -0.5;
      }
      cr = (d_a_tmp * c_D11_tmp + e_a_tmp * a_tmp) / b_D11_tmp;
    } else {
      b_D11_tmp = (cy + 1.0) / D11_tmp_tmp;
      cr = (b_D11_tmp * d_a_tmp + e_a_tmp) /
           (D11_tmp_tmp + b_D11_tmp * (cy + 1.0));
    }
    b_D11_tmp = fabs(cy + 1.0);
    c_D11_tmp = fabs(D11_tmp_tmp);
    if (b_D11_tmp > c_D11_tmp) {
      b_D11_tmp = D11_tmp_tmp / (cy + 1.0);
      D21_tmp =
          (phi + b_D11_tmp * D11_tmp) / ((cy + 1.0) + b_D11_tmp * D11_tmp_tmp);
    } else if (c_D11_tmp == b_D11_tmp) {
      if (cy + 1.0 > 0.0) {
        c_D11_tmp = 0.5;
      } else {
        c_D11_tmp = -0.5;
      }
      if (D11_tmp_tmp > 0.0) {
        a_tmp = 0.5;
      } else {
        a_tmp = -0.5;
      }
      D21_tmp = (phi * c_D11_tmp + D11_tmp * a_tmp) / b_D11_tmp;
    } else {
      b_D11_tmp = (cy + 1.0) / D11_tmp_tmp;
      D21_tmp =
          (b_D11_tmp * phi + D11_tmp) / (D11_tmp_tmp + b_D11_tmp * (cy + 1.0));
    }
  }
  d_a_tmp = 0.0 * (1.0 - cy);
  e_a_tmp = 0.0 * (0.0 - D11_tmp_tmp);
  phi = D11 * 2.0 * cp;
  D11_tmp = D11 * 2.0 * c_a_tmp;
  if (D11_tmp_tmp == 0.0) {
    if (e_a_tmp == 0.0) {
      b_D11_tmp_tmp = d_a_tmp / (cy + 1.0);
    } else if (d_a_tmp == 0.0) {
      b_D11_tmp_tmp = 0.0;
    } else {
      b_D11_tmp_tmp = rtNaN;
    }
    if (D11_tmp == 0.0) {
      b_a_tmp = phi / (cy + 1.0);
    } else if (phi == 0.0) {
      b_a_tmp = 0.0;
    } else {
      b_a_tmp = phi / (cy + 1.0);
    }
  } else if (cy + 1.0 == 0.0) {
    if (d_a_tmp == 0.0) {
      b_D11_tmp_tmp = e_a_tmp / D11_tmp_tmp;
    } else if (e_a_tmp == 0.0) {
      b_D11_tmp_tmp = 0.0;
    } else {
      b_D11_tmp_tmp = rtNaN;
    }
    if (phi == 0.0) {
      b_a_tmp = D11_tmp / D11_tmp_tmp;
    } else if (D11_tmp == 0.0) {
      b_a_tmp = 0.0;
    } else {
      b_a_tmp = D11_tmp / D11_tmp_tmp;
    }
  } else {
    b_D11_tmp = fabs(cy + 1.0);
    c_D11_tmp = fabs(D11_tmp_tmp);
    if (b_D11_tmp > c_D11_tmp) {
      b_D11_tmp = D11_tmp_tmp / (cy + 1.0);
      b_D11_tmp_tmp = (d_a_tmp + b_D11_tmp * e_a_tmp) /
                      ((cy + 1.0) + b_D11_tmp * D11_tmp_tmp);
    } else if (c_D11_tmp == b_D11_tmp) {
      if (cy + 1.0 > 0.0) {
        c_D11_tmp = 0.5;
      } else {
        c_D11_tmp = -0.5;
      }
      if (D11_tmp_tmp > 0.0) {
        a_tmp = 0.5;
      } else {
        a_tmp = -0.5;
      }
      b_D11_tmp_tmp = (d_a_tmp * c_D11_tmp + e_a_tmp * a_tmp) / b_D11_tmp;
    } else {
      b_D11_tmp = (cy + 1.0) / D11_tmp_tmp;
      b_D11_tmp_tmp = (b_D11_tmp * d_a_tmp + e_a_tmp) /
                      (D11_tmp_tmp + b_D11_tmp * (cy + 1.0));
    }
    b_D11_tmp = fabs(cy + 1.0);
    c_D11_tmp = fabs(D11_tmp_tmp);
    if (b_D11_tmp > c_D11_tmp) {
      b_D11_tmp = D11_tmp_tmp / (cy + 1.0);
      b_a_tmp =
          (phi + b_D11_tmp * D11_tmp) / ((cy + 1.0) + b_D11_tmp * D11_tmp_tmp);
    } else if (c_D11_tmp == b_D11_tmp) {
      if (cy + 1.0 > 0.0) {
        c_D11_tmp = 0.5;
      } else {
        c_D11_tmp = -0.5;
      }
      if (D11_tmp_tmp > 0.0) {
        a_tmp = 0.5;
      } else {
        a_tmp = -0.5;
      }
      b_a_tmp = (phi * c_D11_tmp + D11_tmp * a_tmp) / b_D11_tmp;
    } else {
      b_D11_tmp = (cy + 1.0) / D11_tmp_tmp;
      b_a_tmp =
          (b_D11_tmp * phi + D11_tmp) / (D11_tmp_tmp + b_D11_tmp * (cy + 1.0));
    }
  }
  d_a_tmp = D12 * (1.0 - cy);
  e_a_tmp = D12 * (0.0 - D11_tmp_tmp);
  phi = D21 * 2.0 * cp;
  D11_tmp = D21 * 2.0 * c_a_tmp;
  if (D11_tmp_tmp == 0.0) {
    if (e_a_tmp == 0.0) {
      cp = d_a_tmp / (cy + 1.0);
    } else if (d_a_tmp == 0.0) {
      cp = 0.0;
    } else {
      cp = d_a_tmp / (cy + 1.0);
    }
    if (D11_tmp == 0.0) {
      D11_tmp = phi / (cy + 1.0);
    } else if (phi == 0.0) {
      D11_tmp = 0.0;
    } else {
      D11_tmp = phi / (cy + 1.0);
    }
  } else if (cy + 1.0 == 0.0) {
    if (d_a_tmp == 0.0) {
      cp = e_a_tmp / D11_tmp_tmp;
    } else if (e_a_tmp == 0.0) {
      cp = 0.0;
    } else {
      cp = e_a_tmp / D11_tmp_tmp;
    }
    if (phi == 0.0) {
      D11_tmp /= D11_tmp_tmp;
    } else if (D11_tmp == 0.0) {
      D11_tmp = 0.0;
    } else {
      D11_tmp /= D11_tmp_tmp;
    }
  } else {
    b_D11_tmp = fabs(cy + 1.0);
    c_D11_tmp = fabs(D11_tmp_tmp);
    if (b_D11_tmp > c_D11_tmp) {
      b_D11_tmp = D11_tmp_tmp / (cy + 1.0);
      cp = (d_a_tmp + b_D11_tmp * e_a_tmp) /
           ((cy + 1.0) + b_D11_tmp * D11_tmp_tmp);
    } else if (c_D11_tmp == b_D11_tmp) {
      if (cy + 1.0 > 0.0) {
        c_D11_tmp = 0.5;
      } else {
        c_D11_tmp = -0.5;
      }
      if (D11_tmp_tmp > 0.0) {
        a_tmp = 0.5;
      } else {
        a_tmp = -0.5;
      }
      cp = (d_a_tmp * c_D11_tmp + e_a_tmp * a_tmp) / b_D11_tmp;
    } else {
      b_D11_tmp = (cy + 1.0) / D11_tmp_tmp;
      cp = (b_D11_tmp * d_a_tmp + e_a_tmp) /
           (D11_tmp_tmp + b_D11_tmp * (cy + 1.0));
    }
    b_D11_tmp = fabs(cy + 1.0);
    c_D11_tmp = fabs(D11_tmp_tmp);
    if (b_D11_tmp > c_D11_tmp) {
      b_D11_tmp = D11_tmp_tmp / (cy + 1.0);
      D11_tmp =
          (phi + b_D11_tmp * D11_tmp) / ((cy + 1.0) + b_D11_tmp * D11_tmp_tmp);
    } else if (c_D11_tmp == b_D11_tmp) {
      if (cy + 1.0 > 0.0) {
        c_D11_tmp = 0.5;
      } else {
        c_D11_tmp = -0.5;
      }
      if (D11_tmp_tmp > 0.0) {
        a_tmp = 0.5;
      } else {
        a_tmp = -0.5;
      }
      D11_tmp = (phi * c_D11_tmp + D11_tmp * a_tmp) / b_D11_tmp;
    } else {
      b_D11_tmp = (cy + 1.0) / D11_tmp_tmp;
      D11_tmp =
          (b_D11_tmp * phi + D11_tmp) / (D11_tmp_tmp + b_D11_tmp * (cy + 1.0));
    }
  }
  d_a_tmp = D22 * (1.0 - cy);
  e_a_tmp = D22 * (0.0 - D11_tmp_tmp);
  if (D11_tmp_tmp == 0.0) {
    if (e_a_tmp == 0.0) {
      phi = d_a_tmp / (cy + 1.0);
    } else if (d_a_tmp == 0.0) {
      phi = 0.0;
    } else {
      phi = d_a_tmp / (cy + 1.0);
    }
  } else if (cy + 1.0 == 0.0) {
    if (d_a_tmp == 0.0) {
      phi = e_a_tmp / D11_tmp_tmp;
    } else if (e_a_tmp == 0.0) {
      phi = 0.0;
    } else {
      phi = e_a_tmp / D11_tmp_tmp;
    }
  } else {
    b_D11_tmp = fabs(cy + 1.0);
    c_D11_tmp = fabs(D11_tmp_tmp);
    if (b_D11_tmp > c_D11_tmp) {
      b_D11_tmp = D11_tmp_tmp / (cy + 1.0);
      phi = (d_a_tmp + b_D11_tmp * e_a_tmp) /
            ((cy + 1.0) + b_D11_tmp * D11_tmp_tmp);
    } else if (c_D11_tmp == b_D11_tmp) {
      if (cy + 1.0 > 0.0) {
        c_D11_tmp = 0.5;
      } else {
        c_D11_tmp = -0.5;
      }
      if (D11_tmp_tmp > 0.0) {
        a_tmp = 0.5;
      } else {
        a_tmp = -0.5;
      }
      phi = (d_a_tmp * c_D11_tmp + e_a_tmp * a_tmp) / b_D11_tmp;
    } else {
      b_D11_tmp = (cy + 1.0) / D11_tmp_tmp;
      phi = (b_D11_tmp * d_a_tmp + e_a_tmp) /
            (D11_tmp_tmp + b_D11_tmp * (cy + 1.0));
    }
  }
  phi1[0] = asin(
      (g_a_tmp * ((D12_tmp + cr) + F23) -
       f_a_tmp * ((D21_tmp + b_D11_tmp_tmp) + F13)) /
      (((b_a_tmp + cp) + D13) * f_a_tmp - ((D11_tmp + phi) + D23) * g_a_tmp));
  if (YY_data[tmp_data[0]].re <= YY_data[tmp_data[1]].re) {
    ks = Y_data[0];
    b_atan(&ks);
  } else {
    ks = Y_data[1];
    b_atan(&ks);
  }
  cp = YY_data[tmp_data[1]].re;
  c_a_tmp = YY_data[tmp_data[1]].im;
  cy = cp * cp - c_a_tmp * c_a_tmp;
  D11_tmp_tmp = cp * c_a_tmp;
  D11_tmp_tmp += D11_tmp_tmp;
  d_a_tmp = E11 * 2.0 * cp;
  e_a_tmp = E11 * 2.0 * c_a_tmp;
  if (D11_tmp_tmp == 0.0) {
    if (e_a_tmp == 0.0) {
      D11_tmp = d_a_tmp / (cy + 1.0);
    } else if (d_a_tmp == 0.0) {
      D11_tmp = 0.0;
    } else {
      D11_tmp = d_a_tmp / (cy + 1.0);
    }
  } else if (cy + 1.0 == 0.0) {
    if (d_a_tmp == 0.0) {
      D11_tmp = e_a_tmp / D11_tmp_tmp;
    } else if (e_a_tmp == 0.0) {
      D11_tmp = 0.0;
    } else {
      D11_tmp = e_a_tmp / D11_tmp_tmp;
    }
  } else {
    b_D11_tmp = fabs(cy + 1.0);
    c_D11_tmp = fabs(D11_tmp_tmp);
    if (b_D11_tmp > c_D11_tmp) {
      b_D11_tmp = D11_tmp_tmp / (cy + 1.0);
      D11_tmp = (d_a_tmp + b_D11_tmp * e_a_tmp) /
                ((cy + 1.0) + b_D11_tmp * D11_tmp_tmp);
    } else if (c_D11_tmp == b_D11_tmp) {
      if (cy + 1.0 > 0.0) {
        c_D11_tmp = 0.5;
      } else {
        c_D11_tmp = -0.5;
      }
      if (D11_tmp_tmp > 0.0) {
        a_tmp = 0.5;
      } else {
        a_tmp = -0.5;
      }
      D11_tmp = (d_a_tmp * c_D11_tmp + e_a_tmp * a_tmp) / b_D11_tmp;
    } else {
      b_D11_tmp = (cy + 1.0) / D11_tmp_tmp;
      D11_tmp = (b_D11_tmp * d_a_tmp + e_a_tmp) /
                (D11_tmp_tmp + b_D11_tmp * (cy + 1.0));
    }
  }
  d_a_tmp = E12 * (1.0 - cy);
  e_a_tmp = E12 * (0.0 - D11_tmp_tmp);
  if (D11_tmp_tmp == 0.0) {
    if (e_a_tmp == 0.0) {
      phi = d_a_tmp / (cy + 1.0);
    } else if (d_a_tmp == 0.0) {
      phi = 0.0;
    } else {
      phi = d_a_tmp / (cy + 1.0);
    }
  } else if (cy + 1.0 == 0.0) {
    if (d_a_tmp == 0.0) {
      phi = e_a_tmp / D11_tmp_tmp;
    } else if (e_a_tmp == 0.0) {
      phi = 0.0;
    } else {
      phi = e_a_tmp / D11_tmp_tmp;
    }
  } else {
    b_D11_tmp = fabs(cy + 1.0);
    c_D11_tmp = fabs(D11_tmp_tmp);
    if (b_D11_tmp > c_D11_tmp) {
      b_D11_tmp = D11_tmp_tmp / (cy + 1.0);
      phi = (d_a_tmp + b_D11_tmp * e_a_tmp) /
            ((cy + 1.0) + b_D11_tmp * D11_tmp_tmp);
    } else if (c_D11_tmp == b_D11_tmp) {
      if (cy + 1.0 > 0.0) {
        c_D11_tmp = 0.5;
      } else {
        c_D11_tmp = -0.5;
      }
      if (D11_tmp_tmp > 0.0) {
        a_tmp = 0.5;
      } else {
        a_tmp = -0.5;
      }
      phi = (d_a_tmp * c_D11_tmp + e_a_tmp * a_tmp) / b_D11_tmp;
    } else {
      b_D11_tmp = (cy + 1.0) / D11_tmp_tmp;
      phi = (b_D11_tmp * d_a_tmp + e_a_tmp) /
            (D11_tmp_tmp + b_D11_tmp * (cy + 1.0));
    }
  }
  g_a_tmp = (D11_tmp + phi) + E13;
  d_a_tmp = E21 * 2.0 * cp;
  e_a_tmp = E21 * 2.0 * c_a_tmp;
  if (D11_tmp_tmp == 0.0) {
    if (e_a_tmp == 0.0) {
      D11_tmp = d_a_tmp / (cy + 1.0);
    } else if (d_a_tmp == 0.0) {
      D11_tmp = 0.0;
    } else {
      D11_tmp = d_a_tmp / (cy + 1.0);
    }
  } else if (cy + 1.0 == 0.0) {
    if (d_a_tmp == 0.0) {
      D11_tmp = e_a_tmp / D11_tmp_tmp;
    } else if (e_a_tmp == 0.0) {
      D11_tmp = 0.0;
    } else {
      D11_tmp = e_a_tmp / D11_tmp_tmp;
    }
  } else {
    b_D11_tmp = fabs(cy + 1.0);
    c_D11_tmp = fabs(D11_tmp_tmp);
    if (b_D11_tmp > c_D11_tmp) {
      b_D11_tmp = D11_tmp_tmp / (cy + 1.0);
      D11_tmp = (d_a_tmp + b_D11_tmp * e_a_tmp) /
                ((cy + 1.0) + b_D11_tmp * D11_tmp_tmp);
    } else if (c_D11_tmp == b_D11_tmp) {
      if (cy + 1.0 > 0.0) {
        c_D11_tmp = 0.5;
      } else {
        c_D11_tmp = -0.5;
      }
      if (D11_tmp_tmp > 0.0) {
        a_tmp = 0.5;
      } else {
        a_tmp = -0.5;
      }
      D11_tmp = (d_a_tmp * c_D11_tmp + e_a_tmp * a_tmp) / b_D11_tmp;
    } else {
      b_D11_tmp = (cy + 1.0) / D11_tmp_tmp;
      D11_tmp = (b_D11_tmp * d_a_tmp + e_a_tmp) /
                (D11_tmp_tmp + b_D11_tmp * (cy + 1.0));
    }
  }
  d_a_tmp = E22 * (1.0 - cy);
  e_a_tmp = E22 * (0.0 - D11_tmp_tmp);
  if (D11_tmp_tmp == 0.0) {
    if (e_a_tmp == 0.0) {
      phi = d_a_tmp / (cy + 1.0);
    } else if (d_a_tmp == 0.0) {
      phi = 0.0;
    } else {
      phi = d_a_tmp / (cy + 1.0);
    }
  } else if (cy + 1.0 == 0.0) {
    if (d_a_tmp == 0.0) {
      phi = e_a_tmp / D11_tmp_tmp;
    } else if (e_a_tmp == 0.0) {
      phi = 0.0;
    } else {
      phi = e_a_tmp / D11_tmp_tmp;
    }
  } else {
    b_D11_tmp = fabs(cy + 1.0);
    c_D11_tmp = fabs(D11_tmp_tmp);
    if (b_D11_tmp > c_D11_tmp) {
      b_D11_tmp = D11_tmp_tmp / (cy + 1.0);
      phi = (d_a_tmp + b_D11_tmp * e_a_tmp) /
            ((cy + 1.0) + b_D11_tmp * D11_tmp_tmp);
    } else if (c_D11_tmp == b_D11_tmp) {
      if (cy + 1.0 > 0.0) {
        c_D11_tmp = 0.5;
      } else {
        c_D11_tmp = -0.5;
      }
      if (D11_tmp_tmp > 0.0) {
        a_tmp = 0.5;
      } else {
        a_tmp = -0.5;
      }
      phi = (d_a_tmp * c_D11_tmp + e_a_tmp * a_tmp) / b_D11_tmp;
    } else {
      b_D11_tmp = (cy + 1.0) / D11_tmp_tmp;
      phi = (b_D11_tmp * d_a_tmp + e_a_tmp) /
            (D11_tmp_tmp + b_D11_tmp * (cy + 1.0));
    }
  }
  f_a_tmp = (D11_tmp + phi) + E23;
  d_a_tmp = F21 * 2.0 * cp;
  e_a_tmp = F21 * 2.0 * c_a_tmp;
  if (D11_tmp_tmp == 0.0) {
    if (e_a_tmp == 0.0) {
      D12_tmp = d_a_tmp / (cy + 1.0);
    } else if (d_a_tmp == 0.0) {
      D12_tmp = 0.0;
    } else {
      D12_tmp = d_a_tmp / (cy + 1.0);
    }
  } else if (cy + 1.0 == 0.0) {
    if (d_a_tmp == 0.0) {
      D12_tmp = e_a_tmp / D11_tmp_tmp;
    } else if (e_a_tmp == 0.0) {
      D12_tmp = 0.0;
    } else {
      D12_tmp = e_a_tmp / D11_tmp_tmp;
    }
  } else {
    b_D11_tmp = fabs(cy + 1.0);
    c_D11_tmp = fabs(D11_tmp_tmp);
    if (b_D11_tmp > c_D11_tmp) {
      b_D11_tmp = D11_tmp_tmp / (cy + 1.0);
      D12_tmp = (d_a_tmp + b_D11_tmp * e_a_tmp) /
                ((cy + 1.0) + b_D11_tmp * D11_tmp_tmp);
    } else if (c_D11_tmp == b_D11_tmp) {
      if (cy + 1.0 > 0.0) {
        c_D11_tmp = 0.5;
      } else {
        c_D11_tmp = -0.5;
      }
      if (D11_tmp_tmp > 0.0) {
        a_tmp = 0.5;
      } else {
        a_tmp = -0.5;
      }
      D12_tmp = (d_a_tmp * c_D11_tmp + e_a_tmp * a_tmp) / b_D11_tmp;
    } else {
      b_D11_tmp = (cy + 1.0) / D11_tmp_tmp;
      D12_tmp = (b_D11_tmp * d_a_tmp + e_a_tmp) /
                (D11_tmp_tmp + b_D11_tmp * (cy + 1.0));
    }
  }
  d_a_tmp = F22 * (1.0 - cy);
  e_a_tmp = F22 * (0.0 - D11_tmp_tmp);
  phi = F11 * 2.0 * cp;
  D11_tmp = F11 * 2.0 * c_a_tmp;
  if (D11_tmp_tmp == 0.0) {
    if (e_a_tmp == 0.0) {
      cr = d_a_tmp / (cy + 1.0);
    } else if (d_a_tmp == 0.0) {
      cr = 0.0;
    } else {
      cr = d_a_tmp / (cy + 1.0);
    }
    if (D11_tmp == 0.0) {
      D21_tmp = phi / (cy + 1.0);
    } else if (phi == 0.0) {
      D21_tmp = 0.0;
    } else {
      D21_tmp = phi / (cy + 1.0);
    }
  } else if (cy + 1.0 == 0.0) {
    if (d_a_tmp == 0.0) {
      cr = e_a_tmp / D11_tmp_tmp;
    } else if (e_a_tmp == 0.0) {
      cr = 0.0;
    } else {
      cr = e_a_tmp / D11_tmp_tmp;
    }
    if (phi == 0.0) {
      D21_tmp = D11_tmp / D11_tmp_tmp;
    } else if (D11_tmp == 0.0) {
      D21_tmp = 0.0;
    } else {
      D21_tmp = D11_tmp / D11_tmp_tmp;
    }
  } else {
    b_D11_tmp = fabs(cy + 1.0);
    c_D11_tmp = fabs(D11_tmp_tmp);
    if (b_D11_tmp > c_D11_tmp) {
      b_D11_tmp = D11_tmp_tmp / (cy + 1.0);
      cr = (d_a_tmp + b_D11_tmp * e_a_tmp) /
           ((cy + 1.0) + b_D11_tmp * D11_tmp_tmp);
    } else if (c_D11_tmp == b_D11_tmp) {
      if (cy + 1.0 > 0.0) {
        c_D11_tmp = 0.5;
      } else {
        c_D11_tmp = -0.5;
      }
      if (D11_tmp_tmp > 0.0) {
        a_tmp = 0.5;
      } else {
        a_tmp = -0.5;
      }
      cr = (d_a_tmp * c_D11_tmp + e_a_tmp * a_tmp) / b_D11_tmp;
    } else {
      b_D11_tmp = (cy + 1.0) / D11_tmp_tmp;
      cr = (b_D11_tmp * d_a_tmp + e_a_tmp) /
           (D11_tmp_tmp + b_D11_tmp * (cy + 1.0));
    }
    b_D11_tmp = fabs(cy + 1.0);
    c_D11_tmp = fabs(D11_tmp_tmp);
    if (b_D11_tmp > c_D11_tmp) {
      b_D11_tmp = D11_tmp_tmp / (cy + 1.0);
      D21_tmp =
          (phi + b_D11_tmp * D11_tmp) / ((cy + 1.0) + b_D11_tmp * D11_tmp_tmp);
    } else if (c_D11_tmp == b_D11_tmp) {
      if (cy + 1.0 > 0.0) {
        c_D11_tmp = 0.5;
      } else {
        c_D11_tmp = -0.5;
      }
      if (D11_tmp_tmp > 0.0) {
        a_tmp = 0.5;
      } else {
        a_tmp = -0.5;
      }
      D21_tmp = (phi * c_D11_tmp + D11_tmp * a_tmp) / b_D11_tmp;
    } else {
      b_D11_tmp = (cy + 1.0) / D11_tmp_tmp;
      D21_tmp =
          (b_D11_tmp * phi + D11_tmp) / (D11_tmp_tmp + b_D11_tmp * (cy + 1.0));
    }
  }
  d_a_tmp = 0.0 * (1.0 - cy);
  e_a_tmp = 0.0 * (0.0 - D11_tmp_tmp);
  phi = D11 * 2.0 * cp;
  D11_tmp = D11 * 2.0 * c_a_tmp;
  if (D11_tmp_tmp == 0.0) {
    if (e_a_tmp == 0.0) {
      b_D11_tmp_tmp = d_a_tmp / (cy + 1.0);
    } else if (d_a_tmp == 0.0) {
      b_D11_tmp_tmp = 0.0;
    } else {
      b_D11_tmp_tmp = rtNaN;
    }
    if (D11_tmp == 0.0) {
      b_a_tmp = phi / (cy + 1.0);
    } else if (phi == 0.0) {
      b_a_tmp = 0.0;
    } else {
      b_a_tmp = phi / (cy + 1.0);
    }
  } else if (cy + 1.0 == 0.0) {
    if (d_a_tmp == 0.0) {
      b_D11_tmp_tmp = e_a_tmp / D11_tmp_tmp;
    } else if (e_a_tmp == 0.0) {
      b_D11_tmp_tmp = 0.0;
    } else {
      b_D11_tmp_tmp = rtNaN;
    }
    if (phi == 0.0) {
      b_a_tmp = D11_tmp / D11_tmp_tmp;
    } else if (D11_tmp == 0.0) {
      b_a_tmp = 0.0;
    } else {
      b_a_tmp = D11_tmp / D11_tmp_tmp;
    }
  } else {
    b_D11_tmp = fabs(cy + 1.0);
    c_D11_tmp = fabs(D11_tmp_tmp);
    if (b_D11_tmp > c_D11_tmp) {
      b_D11_tmp = D11_tmp_tmp / (cy + 1.0);
      b_D11_tmp_tmp = (d_a_tmp + b_D11_tmp * e_a_tmp) /
                      ((cy + 1.0) + b_D11_tmp * D11_tmp_tmp);
    } else if (c_D11_tmp == b_D11_tmp) {
      if (cy + 1.0 > 0.0) {
        c_D11_tmp = 0.5;
      } else {
        c_D11_tmp = -0.5;
      }
      if (D11_tmp_tmp > 0.0) {
        a_tmp = 0.5;
      } else {
        a_tmp = -0.5;
      }
      b_D11_tmp_tmp = (d_a_tmp * c_D11_tmp + e_a_tmp * a_tmp) / b_D11_tmp;
    } else {
      b_D11_tmp = (cy + 1.0) / D11_tmp_tmp;
      b_D11_tmp_tmp = (b_D11_tmp * d_a_tmp + e_a_tmp) /
                      (D11_tmp_tmp + b_D11_tmp * (cy + 1.0));
    }
    b_D11_tmp = fabs(cy + 1.0);
    c_D11_tmp = fabs(D11_tmp_tmp);
    if (b_D11_tmp > c_D11_tmp) {
      b_D11_tmp = D11_tmp_tmp / (cy + 1.0);
      b_a_tmp =
          (phi + b_D11_tmp * D11_tmp) / ((cy + 1.0) + b_D11_tmp * D11_tmp_tmp);
    } else if (c_D11_tmp == b_D11_tmp) {
      if (cy + 1.0 > 0.0) {
        c_D11_tmp = 0.5;
      } else {
        c_D11_tmp = -0.5;
      }
      if (D11_tmp_tmp > 0.0) {
        a_tmp = 0.5;
      } else {
        a_tmp = -0.5;
      }
      b_a_tmp = (phi * c_D11_tmp + D11_tmp * a_tmp) / b_D11_tmp;
    } else {
      b_D11_tmp = (cy + 1.0) / D11_tmp_tmp;
      b_a_tmp =
          (b_D11_tmp * phi + D11_tmp) / (D11_tmp_tmp + b_D11_tmp * (cy + 1.0));
    }
  }
  d_a_tmp = D12 * (1.0 - cy);
  e_a_tmp = D12 * (0.0 - D11_tmp_tmp);
  phi = D21 * 2.0 * cp;
  D11_tmp = D21 * 2.0 * c_a_tmp;
  if (D11_tmp_tmp == 0.0) {
    if (e_a_tmp == 0.0) {
      cp = d_a_tmp / (cy + 1.0);
    } else if (d_a_tmp == 0.0) {
      cp = 0.0;
    } else {
      cp = d_a_tmp / (cy + 1.0);
    }
    if (D11_tmp == 0.0) {
      D11_tmp = phi / (cy + 1.0);
    } else if (phi == 0.0) {
      D11_tmp = 0.0;
    } else {
      D11_tmp = phi / (cy + 1.0);
    }
  } else if (cy + 1.0 == 0.0) {
    if (d_a_tmp == 0.0) {
      cp = e_a_tmp / D11_tmp_tmp;
    } else if (e_a_tmp == 0.0) {
      cp = 0.0;
    } else {
      cp = e_a_tmp / D11_tmp_tmp;
    }
    if (phi == 0.0) {
      D11_tmp /= D11_tmp_tmp;
    } else if (D11_tmp == 0.0) {
      D11_tmp = 0.0;
    } else {
      D11_tmp /= D11_tmp_tmp;
    }
  } else {
    b_D11_tmp = fabs(cy + 1.0);
    c_D11_tmp = fabs(D11_tmp_tmp);
    if (b_D11_tmp > c_D11_tmp) {
      b_D11_tmp = D11_tmp_tmp / (cy + 1.0);
      cp = (d_a_tmp + b_D11_tmp * e_a_tmp) /
           ((cy + 1.0) + b_D11_tmp * D11_tmp_tmp);
    } else if (c_D11_tmp == b_D11_tmp) {
      if (cy + 1.0 > 0.0) {
        c_D11_tmp = 0.5;
      } else {
        c_D11_tmp = -0.5;
      }
      if (D11_tmp_tmp > 0.0) {
        a_tmp = 0.5;
      } else {
        a_tmp = -0.5;
      }
      cp = (d_a_tmp * c_D11_tmp + e_a_tmp * a_tmp) / b_D11_tmp;
    } else {
      b_D11_tmp = (cy + 1.0) / D11_tmp_tmp;
      cp = (b_D11_tmp * d_a_tmp + e_a_tmp) /
           (D11_tmp_tmp + b_D11_tmp * (cy + 1.0));
    }
    b_D11_tmp = fabs(cy + 1.0);
    c_D11_tmp = fabs(D11_tmp_tmp);
    if (b_D11_tmp > c_D11_tmp) {
      b_D11_tmp = D11_tmp_tmp / (cy + 1.0);
      D11_tmp =
          (phi + b_D11_tmp * D11_tmp) / ((cy + 1.0) + b_D11_tmp * D11_tmp_tmp);
    } else if (c_D11_tmp == b_D11_tmp) {
      if (cy + 1.0 > 0.0) {
        c_D11_tmp = 0.5;
      } else {
        c_D11_tmp = -0.5;
      }
      if (D11_tmp_tmp > 0.0) {
        a_tmp = 0.5;
      } else {
        a_tmp = -0.5;
      }
      D11_tmp = (phi * c_D11_tmp + D11_tmp * a_tmp) / b_D11_tmp;
    } else {
      b_D11_tmp = (cy + 1.0) / D11_tmp_tmp;
      D11_tmp =
          (b_D11_tmp * phi + D11_tmp) / (D11_tmp_tmp + b_D11_tmp * (cy + 1.0));
    }
  }
  d_a_tmp = D22 * (1.0 - cy);
  e_a_tmp = D22 * (0.0 - D11_tmp_tmp);
  if (D11_tmp_tmp == 0.0) {
    if (e_a_tmp == 0.0) {
      phi = d_a_tmp / (cy + 1.0);
    } else if (d_a_tmp == 0.0) {
      phi = 0.0;
    } else {
      phi = d_a_tmp / (cy + 1.0);
    }
  } else if (cy + 1.0 == 0.0) {
    if (d_a_tmp == 0.0) {
      phi = e_a_tmp / D11_tmp_tmp;
    } else if (e_a_tmp == 0.0) {
      phi = 0.0;
    } else {
      phi = e_a_tmp / D11_tmp_tmp;
    }
  } else {
    b_D11_tmp = fabs(cy + 1.0);
    c_D11_tmp = fabs(D11_tmp_tmp);
    if (b_D11_tmp > c_D11_tmp) {
      b_D11_tmp = D11_tmp_tmp / (cy + 1.0);
      phi = (d_a_tmp + b_D11_tmp * e_a_tmp) /
            ((cy + 1.0) + b_D11_tmp * D11_tmp_tmp);
    } else if (c_D11_tmp == b_D11_tmp) {
      if (cy + 1.0 > 0.0) {
        c_D11_tmp = 0.5;
      } else {
        c_D11_tmp = -0.5;
      }
      if (D11_tmp_tmp > 0.0) {
        a_tmp = 0.5;
      } else {
        a_tmp = -0.5;
      }
      phi = (d_a_tmp * c_D11_tmp + e_a_tmp * a_tmp) / b_D11_tmp;
    } else {
      b_D11_tmp = (cy + 1.0) / D11_tmp_tmp;
      phi = (b_D11_tmp * d_a_tmp + e_a_tmp) /
            (D11_tmp_tmp + b_D11_tmp * (cy + 1.0));
    }
  }
  if (YY_data[tmp_data[0]].re <= YY_data[tmp_data[1]].re) {
    phi = phi1[0];
    ks = Y_data[0];
    b_atan(&ks);
    ks.re *= 2.0;
    ks.im *= 2.0;
  } else {
    phi = asin(
        (g_a_tmp * ((D12_tmp + cr) + F23) -
         f_a_tmp * ((D21_tmp + b_D11_tmp_tmp) + F13)) /
        (((b_a_tmp + cp) + D13) * f_a_tmp - ((D11_tmp + phi) + D23) * g_a_tmp));
    ks = Y_data[1];
    b_atan(&ks);
    ks.re *= 2.0;
    ks.im *= 2.0;
  }
  /*  PHI=phi; */
  /*  KS=ks; */
  D11_tmp = sin((c[0] + 1.5707963267948966) - 1.298210328476112);
  b_D11_tmp = cos((c[0] + 1.5707963267948966) - 1.298210328476112);
  D21_tmp = sin(phi);
  phi = cos(phi);
  T1[0] = b_D11_tmp;
  T1[4] = -D11_tmp;
  T1[8] = 0.0;
  T1[12] = 0.0;
  T1[1] = D11_tmp;
  T1[5] = b_D11_tmp;
  T1[9] = 0.0;
  T1[13] = 0.0;
  T1[2] = 0.0;
  T1[3] = 0.0;
  T1[6] = 0.0;
  T1[7] = 0.0;
  T1[10] = 1.0;
  T1[11] = 0.0;
  T1[14] = 0.0;
  T1[15] = 1.0;
  for (b_i = 0; b_i < 4; b_i++) {
    g_a_tmp = T1[b_i];
    f_a_tmp = T1[b_i + 4];
    cp = T1[b_i + 8];
    D11_tmp = T1[b_i + 12];
    for (i = 0; i < 4; i++) {
      YY_size = i << 2;
      T1_tmp[b_i + YY_size] =
          ((g_a_tmp * b[YY_size] + f_a_tmp * b[YY_size + 1]) +
           cp * b[YY_size + 2]) +
          D11_tmp * b[YY_size + 3];
    }
  }
  T1[0] = phi;
  T1[4] = -D21_tmp;
  T1[8] = 0.0;
  T1[12] = 0.0;
  T1[1] = D21_tmp;
  T1[5] = phi;
  T1[9] = 0.0;
  T1[13] = 0.0;
  T1[2] = 0.0;
  T1[3] = 0.0;
  T1[6] = 0.0;
  T1[7] = 0.0;
  T1[10] = 1.0;
  T1[11] = 0.0;
  T1[14] = 0.0;
  T1[15] = 1.0;
  for (b_i = 0; b_i < 4; b_i++) {
    g_a_tmp = T1_tmp[b_i];
    f_a_tmp = T1_tmp[b_i + 4];
    cp = T1_tmp[b_i + 8];
    D11_tmp = T1_tmp[b_i + 12];
    for (i = 0; i < 4; i++) {
      YY_size = i << 2;
      b_T1_tmp[b_i + YY_size] =
          ((g_a_tmp * T1[YY_size] + f_a_tmp * T1[YY_size + 1]) +
           cp * T1[YY_size + 2]) +
          D11_tmp * T1[YY_size + 3];
    }
  }
  for (b_i = 0; b_i < 4; b_i++) {
    g_a_tmp = b_T1_tmp[b_i];
    f_a_tmp = b_T1_tmp[b_i + 4];
    cp = b_T1_tmp[b_i + 8];
    D11_tmp = b_T1_tmp[b_i + 12];
    for (i = 0; i < 4; i++) {
      YY_size = i << 2;
      T1[b_i + YY_size] =
          ((g_a_tmp * b_b[YY_size] + f_a_tmp * b_b[YY_size + 1]) +
           cp * b_b[YY_size + 2]) +
          D11_tmp * b_b[YY_size + 3];
    }
  }
  if (ks.im == 0.0) {
    phi = sin(ks.re);
    D11_tmp = 0.0;
    g_a_tmp = ks.re;
    ks.re = cos(g_a_tmp);
    ks.im = 0.0;
  } else if (ks.re == 0.0) {
    phi = 0.0;
    D11_tmp = sinh(ks.im);
    g_a_tmp = ks.im;
    ks.re = cosh(g_a_tmp);
    ks.im = 0.0;
  } else {
    phi = sin(ks.re) * cosh(ks.im);
    D11_tmp = cos(ks.re) * sinh(ks.im);
    g_a_tmp = ks.re;
    f_a_tmp = ks.im;
    ks.re = cos(g_a_tmp) * cosh(f_a_tmp);
    ks.im = -sin(g_a_tmp) * sinh(f_a_tmp);
  }
  for (b_i = 0; b_i < 16; b_i++) {
    b_T1[b_i].re = T1[b_i];
    b_T1[b_i].im = 0.0;
  }
  b_ks[0] = ks;
  b_ks[4].re = -phi;
  b_ks[4].im = -D11_tmp;
  b_ks[8].re = 0.0;
  b_ks[8].im = 0.0;
  b_ks[12].re = 0.0;
  b_ks[12].im = 0.0;
  b_ks[1].re = phi;
  b_ks[1].im = D11_tmp;
  b_ks[5] = ks;
  b_ks[9].re = 0.0;
  b_ks[9].im = 0.0;
  b_ks[13].re = 0.0;
  b_ks[13].im = 0.0;
  b_ks[2].re = 0.0;
  b_ks[2].im = 0.0;
  b_ks[3].re = 0.0;
  b_ks[3].im = 0.0;
  b_ks[6].re = 0.0;
  b_ks[6].im = 0.0;
  b_ks[7].re = 0.0;
  b_ks[7].im = 0.0;
  b_ks[10].re = 1.0;
  b_ks[10].im = 0.0;
  b_ks[11].re = 0.0;
  b_ks[11].im = 0.0;
  b_ks[14].re = 0.0;
  b_ks[14].im = 0.0;
  b_ks[15].re = 1.0;
  b_ks[15].im = 0.0;
  for (b_i = 0; b_i < 4; b_i++) {
    phi = b_T1[b_i].re;
    D11_tmp = b_T1[b_i].im;
    cp = b_T1[b_i + 4].re;
    b_D11_tmp = b_T1[b_i + 4].im;
    c_D11_tmp = b_T1[b_i + 8].re;
    D12_tmp = b_T1[b_i + 8].im;
    cr = b_T1[b_i + 12].re;
    D21_tmp = b_T1[b_i + 12].im;
    for (i = 0; i < 4; i++) {
      YY_size = i << 2;
      cy = b_ks[YY_size].im;
      D11_tmp_tmp = b_ks[YY_size].re;
      b_D11_tmp_tmp = b_ks[YY_size + 1].im;
      b_a_tmp = b_ks[YY_size + 1].re;
      c_a_tmp = b_ks[YY_size + 2].im;
      d_a_tmp = b_ks[YY_size + 2].re;
      e_a_tmp = b_ks[YY_size + 3].im;
      a_tmp = b_ks[YY_size + 3].re;
      YY_size += b_i;
      T2_tmp[YY_size].re = (((phi * D11_tmp_tmp - D11_tmp * cy) +
                             (cp * b_a_tmp - b_D11_tmp * b_D11_tmp_tmp)) +
                            (c_D11_tmp * d_a_tmp - D12_tmp * c_a_tmp)) +
                           (cr * a_tmp - D21_tmp * e_a_tmp);
      T2_tmp[YY_size].im = (((phi * cy + D11_tmp * D11_tmp_tmp) +
                             (cp * b_D11_tmp_tmp + b_D11_tmp * b_a_tmp)) +
                            (c_D11_tmp * c_a_tmp + D12_tmp * d_a_tmp)) +
                           (cr * e_a_tmp + D21_tmp * a_tmp);
    }
  }
  for (b_i = 0; b_i < 16; b_i++) {
    b_T1[b_i].re = dv[b_i];
    b_T1[b_i].im = 0.0;
  }
  for (b_i = 0; b_i < 4; b_i++) {
    b_D11_tmp_tmp = T2_tmp[b_i].re;
    b_a_tmp = T2_tmp[b_i].im;
    c_a_tmp = T2_tmp[b_i + 4].re;
    d_a_tmp = T2_tmp[b_i + 4].im;
    e_a_tmp = T2_tmp[b_i + 8].re;
    a_tmp = T2_tmp[b_i + 8].im;
    phi = T2_tmp[b_i + 12].re;
    D11_tmp = T2_tmp[b_i + 12].im;
    for (i = 0; i < 4; i++) {
      YY_size = i << 2;
      cp = b_T1[YY_size].im;
      b_D11_tmp = b_T1[YY_size].re;
      c_D11_tmp = b_T1[YY_size + 1].im;
      D12_tmp = b_T1[YY_size + 1].re;
      cr = b_T1[YY_size + 2].im;
      D21_tmp = b_T1[YY_size + 2].re;
      cy = b_T1[YY_size + 3].im;
      D11_tmp_tmp = b_T1[YY_size + 3].re;
      YY_size += b_i;
      b_ks[YY_size].re = (((b_D11_tmp_tmp * b_D11_tmp - b_a_tmp * cp) +
                           (c_a_tmp * D12_tmp - d_a_tmp * c_D11_tmp)) +
                          (e_a_tmp * D21_tmp - a_tmp * cr)) +
                         (phi * D11_tmp_tmp - D11_tmp * cy);
      b_ks[YY_size].im = (((b_D11_tmp_tmp * cp + b_a_tmp * b_D11_tmp) +
                           (c_a_tmp * c_D11_tmp + d_a_tmp * D12_tmp)) +
                          (e_a_tmp * cr + a_tmp * D21_tmp)) +
                         (phi * cy + D11_tmp * D11_tmp_tmp);
    }
  }
  for (b_i = 0; b_i < 16; b_i++) {
    b_T1[b_i].re = dv1[b_i];
    b_T1[b_i].im = 0.0;
  }
  for (b_i = 0; b_i < 4; b_i++) {
    b_D11_tmp_tmp = T2_tmp[b_i].re;
    b_a_tmp = T2_tmp[b_i].im;
    c_a_tmp = T2_tmp[b_i + 4].re;
    d_a_tmp = T2_tmp[b_i + 4].im;
    e_a_tmp = T2_tmp[b_i + 8].re;
    a_tmp = T2_tmp[b_i + 8].im;
    phi = T2_tmp[b_i + 12].re;
    D11_tmp = T2_tmp[b_i + 12].im;
    for (i = 0; i < 4; i++) {
      YY_size = i << 2;
      cp = b_T1[YY_size].im;
      b_D11_tmp = b_T1[YY_size].re;
      c_D11_tmp = b_T1[YY_size + 1].im;
      D12_tmp = b_T1[YY_size + 1].re;
      cr = b_T1[YY_size + 2].im;
      D21_tmp = b_T1[YY_size + 2].re;
      cy = b_T1[YY_size + 3].im;
      D11_tmp_tmp = b_T1[YY_size + 3].re;
      YY_size += b_i;
      b_T2_tmp[YY_size].re = (((b_D11_tmp_tmp * b_D11_tmp - b_a_tmp * cp) +
                               (c_a_tmp * D12_tmp - d_a_tmp * c_D11_tmp)) +
                              (e_a_tmp * D21_tmp - a_tmp * cr)) +
                             (phi * D11_tmp_tmp - D11_tmp * cy);
      b_T2_tmp[YY_size].im = (((b_D11_tmp_tmp * cp + b_a_tmp * b_D11_tmp) +
                               (c_a_tmp * c_D11_tmp + d_a_tmp * D12_tmp)) +
                              (e_a_tmp * cr + a_tmp * D21_tmp)) +
                             (phi * cy + D11_tmp * D11_tmp_tmp);
    }
  }
  for (b_i = 0; b_i < 16; b_i++) {
    b_T1[b_i].re = dv[b_i];
    b_T1[b_i].im = 0.0;
  }
  for (b_i = 0; b_i < 4; b_i++) {
    b_D11_tmp_tmp = b_T2_tmp[b_i].re;
    b_a_tmp = b_T2_tmp[b_i].im;
    c_a_tmp = b_T2_tmp[b_i + 4].re;
    d_a_tmp = b_T2_tmp[b_i + 4].im;
    e_a_tmp = b_T2_tmp[b_i + 8].re;
    a_tmp = b_T2_tmp[b_i + 8].im;
    phi = b_T2_tmp[b_i + 12].re;
    D11_tmp = b_T2_tmp[b_i + 12].im;
    for (i = 0; i < 4; i++) {
      YY_size = i << 2;
      cp = b_T1[YY_size].im;
      b_D11_tmp = b_T1[YY_size].re;
      c_D11_tmp = b_T1[YY_size + 1].im;
      D12_tmp = b_T1[YY_size + 1].re;
      cr = b_T1[YY_size + 2].im;
      D21_tmp = b_T1[YY_size + 2].re;
      cy = b_T1[YY_size + 3].im;
      D11_tmp_tmp = b_T1[YY_size + 3].re;
      YY_size += b_i;
      T2_tmp[YY_size].re = (((b_D11_tmp_tmp * b_D11_tmp - b_a_tmp * cp) +
                             (c_a_tmp * D12_tmp - d_a_tmp * c_D11_tmp)) +
                            (e_a_tmp * D21_tmp - a_tmp * cr)) +
                           (phi * D11_tmp_tmp - D11_tmp * cy);
      T2_tmp[YY_size].im = (((b_D11_tmp_tmp * cp + b_a_tmp * b_D11_tmp) +
                             (c_a_tmp * c_D11_tmp + d_a_tmp * D12_tmp)) +
                            (e_a_tmp * cr + a_tmp * D21_tmp)) +
                           (phi * cy + D11_tmp * D11_tmp_tmp);
    }
  }
  for (b_i = 0; b_i < 3; b_i++) {
    c_b[b_i].re = d_b[b_i];
    c_b[b_i].im = 0.0;
    phi = b_ks[b_i].re * 0.0;
    D11_tmp = b_ks[b_i].im * 0.0;
    b_D11_tmp = b_ks[b_i + 4].re * 0.0;
    D21_tmp = b_ks[b_i + 4].im * 0.0;
    c_D11_tmp = b_ks[b_i + 8].re;
    D12_tmp = b_ks[b_i + 8].im;
    c_T2_tmp[b_i].re =
        ((phi - D11_tmp) + (b_D11_tmp - D21_tmp)) + (c_D11_tmp - D12_tmp * 0.0);
    c_T2_tmp[b_i].im =
        ((phi + D11_tmp) + (b_D11_tmp + D21_tmp)) + (c_D11_tmp * 0.0 + D12_tmp);
    c_T1[b_i].re = (T1[b_i] * 0.0 + T1[b_i + 4] * 0.0) + T1[b_i + 8];
    c_T1[b_i].im = 0.0;
  }
  b_i = (int)c_b[0].re;
  g_a_tmp = c_b[0].im;
  i = (int)c_b[1].re;
  f_a_tmp = c_b[1].im;
  YY_size = (int)c_b[2].re;
  cp = c_b[2].im;
  for (partialTrueCount = 0; partialTrueCount < 3; partialTrueCount++) {
    b_D11_tmp_tmp = T2_tmp[partialTrueCount].re;
    b_a_tmp = T2_tmp[partialTrueCount].im;
    c_a_tmp = T2_tmp[partialTrueCount + 4].re;
    d_a_tmp = T2_tmp[partialTrueCount + 4].im;
    e_a_tmp = T2_tmp[partialTrueCount + 8].re;
    a_tmp = T2_tmp[partialTrueCount + 8].im;
    A[partialTrueCount] = c_T1[partialTrueCount];
    A[partialTrueCount + 3] = c_T2_tmp[partialTrueCount];
    A[partialTrueCount + 6].re =
        ((b_D11_tmp_tmp * (double)b_i - b_a_tmp * g_a_tmp) +
         (c_a_tmp * (double)i - d_a_tmp * f_a_tmp)) +
        (e_a_tmp * (double)YY_size - a_tmp * cp);
    A[partialTrueCount + 6].im =
        ((b_D11_tmp_tmp * g_a_tmp + b_a_tmp * (double)b_i) +
         (c_a_tmp * f_a_tmp + d_a_tmp * (double)i)) +
        (e_a_tmp * cp + a_tmp * (double)YY_size);
  }
  if (A[0].im == 0.0) {
    Y[0].re = A[0].re / 0.86602540377173287;
    Y[0].im = 0.0;
  } else if (A[0].re == 0.0) {
    Y[0].re = 0.0;
    Y[0].im = A[0].im / 0.86602540377173287;
  } else {
    Y[0].re = A[0].re / 0.86602540377173287;
    Y[0].im = A[0].im / 0.86602540377173287;
  }
  Y[6].re = A[3].re - Y[0].re * 0.86602540409063378;
  Y[6].im = A[3].im - Y[0].im * 0.86602540409063378;
  Y[3].re = A[6].re - Y[0].re * 0.866025404077136;
  Y[3].im = A[6].im - Y[0].im * 0.866025404077136;
  if (Y[6].im == 0.0) {
    b_D11_tmp_tmp = Y[6].re / -0.93301270155074256;
    phi = 0.0;
  } else if (Y[6].re == 0.0) {
    b_D11_tmp_tmp = 0.0;
    phi = Y[6].im / -0.93301270155074256;
  } else {
    b_D11_tmp_tmp = Y[6].re / -0.93301270155074256;
    phi = Y[6].im / -0.93301270155074256;
  }
  Y[3].re -= b_D11_tmp_tmp * -0.93301270153519322;
  Y[3].im -= phi * -0.93301270153519322;
  if (Y[3].im == 0.0) {
    D11_tmp = Y[3].re / 0.49999999983159132;
    b_D11_tmp = 0.0;
  } else if (Y[3].re == 0.0) {
    D11_tmp = 0.0;
    b_D11_tmp = Y[3].im / 0.49999999983159132;
  } else {
    D11_tmp = Y[3].re / 0.49999999983159132;
    b_D11_tmp = Y[3].im / 0.49999999983159132;
  }
  Y[3].re = D11_tmp;
  Y[3].im = b_D11_tmp;
  Y[6].re = b_D11_tmp_tmp - D11_tmp * 0.2679491924256609;
  Y[6].im = phi - b_D11_tmp * 0.2679491924256609;
  Y[0].re -= D11_tmp * 1.8039312961228876E-11;
  Y[0].im -= b_D11_tmp * 1.8039312961228876E-11;
  Y[0].re -= Y[6].re * 0.577350269223508;
  Y[0].im -= Y[6].im * 0.577350269223508;
  if (A[1].im == 0.0) {
    Y[1].re = A[1].re / 0.86602540377173287;
    Y[1].im = 0.0;
  } else if (A[1].re == 0.0) {
    Y[1].re = 0.0;
    Y[1].im = A[1].im / 0.86602540377173287;
  } else {
    Y[1].re = A[1].re / 0.86602540377173287;
    Y[1].im = A[1].im / 0.86602540377173287;
  }
  Y[7].re = A[4].re - Y[1].re * 0.86602540409063378;
  Y[7].im = A[4].im - Y[1].im * 0.86602540409063378;
  Y[4].re = A[7].re - Y[1].re * 0.866025404077136;
  Y[4].im = A[7].im - Y[1].im * 0.866025404077136;
  if (Y[7].im == 0.0) {
    b_D11_tmp_tmp = Y[7].re / -0.93301270155074256;
    phi = 0.0;
  } else if (Y[7].re == 0.0) {
    b_D11_tmp_tmp = 0.0;
    phi = Y[7].im / -0.93301270155074256;
  } else {
    b_D11_tmp_tmp = Y[7].re / -0.93301270155074256;
    phi = Y[7].im / -0.93301270155074256;
  }
  Y[4].re -= b_D11_tmp_tmp * -0.93301270153519322;
  Y[4].im -= phi * -0.93301270153519322;
  if (Y[4].im == 0.0) {
    D11_tmp = Y[4].re / 0.49999999983159132;
    b_D11_tmp = 0.0;
  } else if (Y[4].re == 0.0) {
    D11_tmp = 0.0;
    b_D11_tmp = Y[4].im / 0.49999999983159132;
  } else {
    D11_tmp = Y[4].re / 0.49999999983159132;
    b_D11_tmp = Y[4].im / 0.49999999983159132;
  }
  Y[4].re = D11_tmp;
  Y[4].im = b_D11_tmp;
  Y[7].re = b_D11_tmp_tmp - D11_tmp * 0.2679491924256609;
  Y[7].im = phi - b_D11_tmp * 0.2679491924256609;
  Y[1].re -= D11_tmp * 1.8039312961228876E-11;
  Y[1].im -= b_D11_tmp * 1.8039312961228876E-11;
  Y[1].re -= Y[7].re * 0.577350269223508;
  Y[1].im -= Y[7].im * 0.577350269223508;
  if (A[2].im == 0.0) {
    Y[2].re = A[2].re / 0.86602540377173287;
    Y[2].im = 0.0;
  } else if (A[2].re == 0.0) {
    Y[2].re = 0.0;
    Y[2].im = A[2].im / 0.86602540377173287;
  } else {
    Y[2].re = A[2].re / 0.86602540377173287;
    Y[2].im = A[2].im / 0.86602540377173287;
  }
  Y[8].re = A[5].re - Y[2].re * 0.86602540409063378;
  Y[8].im = A[5].im - Y[2].im * 0.86602540409063378;
  Y[5].re = A[8].re - Y[2].re * 0.866025404077136;
  Y[5].im = A[8].im - Y[2].im * 0.866025404077136;
  if (Y[8].im == 0.0) {
    b_D11_tmp_tmp = Y[8].re / -0.93301270155074256;
    phi = 0.0;
  } else if (Y[8].re == 0.0) {
    b_D11_tmp_tmp = 0.0;
    phi = Y[8].im / -0.93301270155074256;
  } else {
    b_D11_tmp_tmp = Y[8].re / -0.93301270155074256;
    phi = Y[8].im / -0.93301270155074256;
  }
  Y[5].re -= b_D11_tmp_tmp * -0.93301270153519322;
  Y[5].im -= phi * -0.93301270153519322;
  if (Y[5].im == 0.0) {
    D11_tmp = Y[5].re / 0.49999999983159132;
    b_D11_tmp = 0.0;
  } else if (Y[5].re == 0.0) {
    D11_tmp = 0.0;
    b_D11_tmp = Y[5].im / 0.49999999983159132;
  } else {
    D11_tmp = Y[5].re / 0.49999999983159132;
    b_D11_tmp = Y[5].im / 0.49999999983159132;
  }
  Y[5].re = D11_tmp;
  Y[5].im = b_D11_tmp;
  Y[8].re = b_D11_tmp_tmp - D11_tmp * 0.2679491924256609;
  Y[8].im = phi - b_D11_tmp * 0.2679491924256609;
  Y[2].re -= D11_tmp * 1.8039312961228876E-11;
  Y[2].im -= b_D11_tmp * 1.8039312961228876E-11;
  Y[2].re -= Y[8].re * 0.577350269223508;
  Y[2].im -= Y[8].im * 0.577350269223508;
  for (b_i = 0; b_i < 9; b_i++) {
    Rot_shoulder[b_i] = Y[b_i].re;
  }
  cp = rt_atan2d_snf(Rot_shoulder[1], Rot_shoulder[0]);
  cy = rt_atan2d_snf(Rot_shoulder[5], Rot_shoulder[8]);
  cr = rt_atan2d_snf(-Rot_shoulder[2], sqrt(Rot_shoulder[5] * Rot_shoulder[5] +
                                            Rot_shoulder[8] * Rot_shoulder[8]));
  /*  根据问题背景调整初始值 */
  /*  设置求解选项 */
  /*  options = optimoptions('fsolve', 'Display', 'off', 'TolFun', 1e-12,
   * 'TolX', 1e-12); */
  /*  求解方程 */
  phi = driver(c[4], c[5], phi1, d1, &D11_tmp, &b_D11_tmp, &c_D11_tmp, &D12_tmp,
               &D21_tmp, expl_temp, b_expl_temp, c_expl_temp, jacob);
  if ((D11_tmp > 0.0) && (phi > 0.001)) {
    D11_tmp = -2.0;
  }
  /*  x=180/pi*x; */
  /*  输出结果 */
  if (D11_tmp > 0.0) {
    /*      fprintf('求解成功！\n'); */
    /*      fprintf('r = %.6f\n', x(1)); */
    /*      fprintf('p = %.6f\n', x(2)); */
    /*      fprintf('方程1的残差: %.2e\n', fval(1)); */
    /*      fprintf('方程2的残差: %.2e\n', fval(2)); */
    D11_tmp = phi1[0];
    phi = phi1[1];
  } else {
    D11_tmp = 0.0;
    phi = 0.0;
    /*  fprintf('wrong: %d\n', exitflag); */
  }
  /*  [cos(cp),-sin(cp),0,0;sin(cp),cos(cp),0,0;0,0,1,0;0,0,0,1]*[cos(cr),0,sin(cr),0;0,1,0,0;-sin(cr),0,cos(cr),0;0,0,0,1]*[1,0,0,0;0,cos(cy),-sin(cy),0;0,sin(cy),cos(cy),0;0,0,0,1]*[1,0,0,L1;0,1,0,0;0,0,1,0;0,0,0,1]*[cos(c4),-sin(c4),0,0;sin(c4),cos(c4),0,0;0,0,1,0;0,0,0,1]*[1,0,0,L2;0,1,0,0;0,0,1,0;0,0,0,1]
   */
  /*  [1,0,0,0;0,cos(cwy),sin(cwy),0;0,-sin(cwy),cos(cwy),0;0,0,0,1]*[cos(cwr),0,-sin(cwr),0;0,1,0,0;sin(cwr),0,cos(cwr),0;0,0,0,1]*[cos(cwp),sin(cwp),0,0;-sin(cwp),cos(cwp),0,0;0,0,1,0;0,0,0,1]
   */
  b_D11_tmp_tmp = sin(cp);
  D12_tmp = cos(cp);
  D21_tmp = sin(cr);
  b_D11_tmp = cos(cr);
  c_D11_tmp = sin(cy);
  cp = cos(cy);
  d_a_tmp = sin(c[3]);
  e_a_tmp = cos(c[3]);
  a_tmp = sin(phi);
  b_a_tmp = cos(phi);
  c_a_tmp = sin(D11_tmp);
  phi = cos(D11_tmp);
  cr = sin(c[6]);
  D11_tmp_tmp = cos(c[6]);
  T1[0] = D12_tmp;
  T1[4] = -b_D11_tmp_tmp;
  T1[8] = 0.0;
  T1[12] = 0.0;
  T1[1] = b_D11_tmp_tmp;
  T1[5] = D12_tmp;
  T1[9] = 0.0;
  T1[13] = 0.0;
  b_T1_tmp[0] = b_D11_tmp;
  b_T1_tmp[4] = 0.0;
  b_T1_tmp[8] = D21_tmp;
  b_T1_tmp[12] = 0.0;
  b_T1_tmp[2] = -D21_tmp;
  b_T1_tmp[6] = 0.0;
  b_T1_tmp[10] = b_D11_tmp;
  b_T1_tmp[14] = 0.0;
  T1[2] = 0.0;
  T1[3] = 0.0;
  b_T1_tmp[1] = 0.0;
  b_T1_tmp[3] = 0.0;
  T1[6] = 0.0;
  T1[7] = 0.0;
  b_T1_tmp[5] = 1.0;
  b_T1_tmp[7] = 0.0;
  T1[10] = 1.0;
  T1[11] = 0.0;
  b_T1_tmp[9] = 0.0;
  b_T1_tmp[11] = 0.0;
  T1[14] = 0.0;
  T1[15] = 1.0;
  b_T1_tmp[13] = 0.0;
  b_T1_tmp[15] = 1.0;
  dv2[1] = 0.0;
  dv2[5] = cp;
  dv2[9] = -c_D11_tmp;
  dv2[13] = 0.0;
  dv2[2] = 0.0;
  dv2[6] = c_D11_tmp;
  dv2[10] = cp;
  dv2[14] = 0.0;
  for (b_i = 0; b_i < 4; b_i++) {
    g_a_tmp = T1[b_i];
    f_a_tmp = T1[b_i + 4];
    cp = T1[b_i + 8];
    D11_tmp = T1[b_i + 12];
    for (i = 0; i < 4; i++) {
      YY_size = i << 2;
      T1_tmp[b_i + YY_size] =
          ((g_a_tmp * b_T1_tmp[YY_size] + f_a_tmp * b_T1_tmp[YY_size + 1]) +
           cp * b_T1_tmp[YY_size + 2]) +
          D11_tmp * b_T1_tmp[YY_size + 3];
    }
    i = b_i << 2;
    dv2[i] = iv[b_i];
    dv2[i + 3] = iv1[b_i];
  }
  for (b_i = 0; b_i < 4; b_i++) {
    g_a_tmp = T1_tmp[b_i];
    f_a_tmp = T1_tmp[b_i + 4];
    cp = T1_tmp[b_i + 8];
    D11_tmp = T1_tmp[b_i + 12];
    for (i = 0; i < 4; i++) {
      YY_size = i << 2;
      T1[b_i + YY_size] =
          ((g_a_tmp * dv2[YY_size] + f_a_tmp * dv2[YY_size + 1]) +
           cp * dv2[YY_size + 2]) +
          D11_tmp * dv2[YY_size + 3];
    }
    g_a_tmp = T1[b_i];
    f_a_tmp = T1[b_i + 4];
    cp = T1[b_i + 8];
    D11_tmp = T1[b_i + 12];
    for (i = 0; i < 4; i++) {
      YY_size = i << 2;
      b_T1_tmp[b_i + YY_size] = ((g_a_tmp * (double)e_b[YY_size] +
                                  f_a_tmp * (double)e_b[YY_size + 1]) +
                                 cp * (double)e_b[YY_size + 2]) +
                                D11_tmp * (double)e_b[YY_size + 3];
    }
  }
  T1[0] = e_a_tmp;
  T1[4] = -d_a_tmp;
  T1[8] = 0.0;
  T1[12] = 0.0;
  T1[1] = d_a_tmp;
  T1[5] = e_a_tmp;
  T1[9] = 0.0;
  T1[13] = 0.0;
  T1[2] = 0.0;
  T1[3] = 0.0;
  T1[6] = 0.0;
  T1[7] = 0.0;
  T1[10] = 1.0;
  T1[11] = 0.0;
  T1[14] = 0.0;
  T1[15] = 1.0;
  for (b_i = 0; b_i < 4; b_i++) {
    g_a_tmp = b_T1_tmp[b_i];
    f_a_tmp = b_T1_tmp[b_i + 4];
    cp = b_T1_tmp[b_i + 8];
    D11_tmp = b_T1_tmp[b_i + 12];
    for (i = 0; i < 4; i++) {
      YY_size = i << 2;
      T1_tmp[b_i + YY_size] =
          ((g_a_tmp * T1[YY_size] + f_a_tmp * T1[YY_size + 1]) +
           cp * T1[YY_size + 2]) +
          D11_tmp * T1[YY_size + 3];
    }
  }
  b_T1_tmp[0] = b_a_tmp;
  b_T1_tmp[4] = -a_tmp;
  b_T1_tmp[8] = 0.0;
  b_T1_tmp[12] = 0.0;
  b_T1_tmp[1] = a_tmp;
  b_T1_tmp[5] = b_a_tmp;
  b_T1_tmp[9] = 0.0;
  b_T1_tmp[13] = 0.0;
  for (b_i = 0; b_i < 4; b_i++) {
    g_a_tmp = T1_tmp[b_i];
    f_a_tmp = T1_tmp[b_i + 4];
    cp = T1_tmp[b_i + 8];
    D11_tmp = T1_tmp[b_i + 12];
    for (i = 0; i < 4; i++) {
      YY_size = i << 2;
      T1[b_i + YY_size] = ((g_a_tmp * (double)f_b[YY_size] +
                            f_a_tmp * (double)f_b[YY_size + 1]) +
                           cp * (double)f_b[YY_size + 2]) +
                          D11_tmp * (double)f_b[YY_size + 3];
    }
    YY_size = b_i << 2;
    b_T1_tmp[YY_size + 2] = iv2[b_i];
    b_T1_tmp[YY_size + 3] = iv1[b_i];
  }
  for (b_i = 0; b_i < 4; b_i++) {
    g_a_tmp = T1[b_i];
    f_a_tmp = T1[b_i + 4];
    cp = T1[b_i + 8];
    D11_tmp = T1[b_i + 12];
    for (i = 0; i < 4; i++) {
      YY_size = i << 2;
      T1_tmp[b_i + YY_size] =
          ((g_a_tmp * b_T1_tmp[YY_size] + f_a_tmp * b_T1_tmp[YY_size + 1]) +
           cp * b_T1_tmp[YY_size + 2]) +
          D11_tmp * b_T1_tmp[YY_size + 3];
    }
  }
  T1[0] = phi;
  T1[4] = 0.0;
  T1[8] = c_a_tmp;
  T1[12] = 0.0;
  T1[2] = -c_a_tmp;
  T1[6] = 0.0;
  T1[10] = phi;
  T1[14] = 0.0;
  T1[1] = 0.0;
  T1[3] = 0.0;
  T1[5] = 1.0;
  T1[7] = 0.0;
  T1[9] = 0.0;
  T1[11] = 0.0;
  T1[13] = 0.0;
  T1[15] = 1.0;
  dv2[1] = 0.0;
  dv2[5] = D11_tmp_tmp;
  dv2[9] = -cr;
  dv2[13] = 0.0;
  dv2[2] = 0.0;
  dv2[6] = cr;
  dv2[10] = D11_tmp_tmp;
  dv2[14] = 0.0;
  for (b_i = 0; b_i < 4; b_i++) {
    g_a_tmp = T1_tmp[b_i];
    f_a_tmp = T1_tmp[b_i + 4];
    cp = T1_tmp[b_i + 8];
    D11_tmp = T1_tmp[b_i + 12];
    for (i = 0; i < 4; i++) {
      YY_size = i << 2;
      b_T1_tmp[b_i + YY_size] =
          ((g_a_tmp * T1[YY_size] + f_a_tmp * T1[YY_size + 1]) +
           cp * T1[YY_size + 2]) +
          D11_tmp * T1[YY_size + 3];
    }
    i = b_i << 2;
    dv2[i] = iv[b_i];
    dv2[i + 3] = iv1[b_i];
  }
  for (b_i = 0; b_i < 4; b_i++) {
    g_a_tmp = b_T1_tmp[b_i];
    f_a_tmp = b_T1_tmp[b_i + 4];
    cp = b_T1_tmp[b_i + 8];
    D11_tmp = b_T1_tmp[b_i + 12];
    for (i = 0; i < 4; i++) {
      YY_size = i << 2;
      T[b_i + YY_size] =
          ((g_a_tmp * dv2[YY_size] + f_a_tmp * dv2[YY_size + 1]) +
           cp * dv2[YY_size + 2]) +
          D11_tmp * dv2[YY_size + 3];
    }
  }
  T[12] /= 1000.0;
  T[13] /= 1000.0;
  T[14] /= 1000.0;
}

/* End of code generation (FK_7DOF.c) */

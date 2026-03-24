/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * IK_7DOF.c
 *
 * Code generation for function 'IK_7DOF'
 *
 */

/* Include files */
#include <stdio.h>
#include "IK_7DOF.h"
#include "IK_7DOF_data.h"
#include "IK_7DOF_initialize.h"
#include "rt_wutil.h"
#include "exp.h"
#include "log.h"
#include "mtimes.h"
#include "norm.h"
#include "power.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */
void IK_7DOF(const double R[9], double phi, double Px, double Py, double Pz,
             double c[7], double *flag)
{
  static const signed char b[9] = {1, 0, 0, 0, 1, 0, 0, 0, 1};
  static const signed char a[3] = {0, 0, 1};
  creal_T b_a;
  creal_T b_c10_tmp;
  creal_T b_c10_tmp_tmp;
  creal_T b_c20_tmp;
  creal_T b_c30_tmp;
  creal_T b_c30_tmp_tmp;
  creal_T c10_tmp;
  creal_T c10_tmp_tmp;
  creal_T c20_tmp;
  creal_T c30_tmp;
  creal_T c30_tmp_tmp;
  creal_T c_c10_tmp;
  creal_T c_c10_tmp_tmp;
  creal_T c_c20_tmp;
  creal_T c_c30_tmp;
  creal_T c_c30_tmp_tmp;
  creal_T d_c10_tmp;
  creal_T d_c30_tmp;
  creal_T d_c30_tmp_tmp;
  creal_T dc;
  creal_T dc1;
  creal_T dc10;
  creal_T dc11;
  creal_T dc12;
  creal_T dc13;
  creal_T dc14;
  creal_T dc15;
  creal_T dc16;
  creal_T dc17;
  creal_T dc18;
  creal_T dc19;
  creal_T dc2;
  creal_T dc20;
  creal_T dc21;
  creal_T dc22;
  creal_T dc23;
  creal_T dc24;
  creal_T dc25;
  creal_T dc26;
  creal_T dc27;
  creal_T dc28;
  creal_T dc29;
  creal_T dc3;
  creal_T dc30;
  creal_T dc31;
  creal_T dc32;
  creal_T dc33;
  creal_T dc34;
  creal_T dc35;
  creal_T dc36;
  creal_T dc37;
  creal_T dc38;
  creal_T dc39;
  creal_T dc4;
  creal_T dc40;
  creal_T dc41;
  creal_T dc42;
  creal_T dc43;
  creal_T dc44;
  creal_T dc45;
  creal_T dc46;
  creal_T dc47;
  creal_T dc48;
  creal_T dc49;
  creal_T dc5;
  creal_T dc6;
  creal_T dc7;
  creal_T dc8;
  creal_T dc9;
  creal_T e_c10_tmp;
  creal_T e_c30_tmp;
  creal_T e_c30_tmp_tmp;
  creal_T f_c10_tmp;
  creal_T f_c30_tmp;
  creal_T g_c10_tmp;
  creal_T g_c30_tmp;
  creal_T h_c10_tmp;
  creal_T h_c30_tmp;
  creal_T i_c10_tmp;
  creal_T i_c30_tmp;
  creal_T j_c10_tmp;
  creal_T j_c30_tmp;
  creal_T k_c30_tmp;
  creal_T l_c30_tmp;
  creal_T m_c30_tmp;
  double As[9];
  double Aw[9];
  double Bs[9];
  double Bw[9];
  double Cs[9];
  double Pskew[9];
  double R130[9];
  double a_tmp[9];
  double w3[6];
  double OBL[3];
  double v2[3];
  double OBL_tmp_tmp;
  double ab_c51_idx_0_tmp;
  double ab_c51_idx_0_tmp_tmp;
  double b_OBL_tmp_tmp;
  double b_c51_idx_0_tmp;
  double b_c51_idx_0_tmp_tmp;
  double b_im;
  double b_re;
  double b_sc5_tmp_tmp;
  double bb_c51_idx_0_tmp_tmp;
  double c4;
  double c51_idx_0;
  double c51_idx_0_tmp;
  double c51_idx_0_tmp_tmp;
  double c51_idx_0_tmp_tmp_tmp;
  double c61_idx_0;
  double c_OBL_tmp_tmp;
  double c_c51_idx_0_tmp;
  double c_c51_idx_0_tmp_tmp;
  double c_im;
  double c_re;
  double c_sc5_tmp_tmp;
  double cb_c51_idx_0_tmp_tmp;
  double cc4;
  double ccp0;
  double ccr0;
  double cphi;
  double cps;
  double cpw;
  double crs;
  double crw;
  double cys;
  double cyw;
  double d;
  double d1;
  double d10;
  double d11;
  double d12;
  double d13;
  double d14;
  double d15;
  double d16;
  double d17;
  double d18;
  double d19;
  double d2;
  double d20;
  double d21;
  double d22;
  double d23;
  double d24;
  double d25;
  double d26;
  double d27;
  double d28;
  double d29;
  double d3;
  double d30;
  double d31;
  double d32;
  double d33;
  double d34;
  double d35;
  double d36;
  double d37;
  double d4;
  double d5;
  double d6;
  double d7;
  double d8;
  double d9;
  double d_OBL_tmp_tmp;
  double d_c51_idx_0_tmp;
  double d_c51_idx_0_tmp_tmp;
  double d_im;
  double d_re;
  double d_sc5_tmp_tmp;
  double db_c51_idx_0_tmp_tmp;
  double e_c51_idx_0_tmp;
  double e_c51_idx_0_tmp_tmp;
  double e_re;
  double e_sc5_tmp_tmp;
  double eb_c51_idx_0_tmp_tmp;
  double f_c51_idx_0_tmp;
  double f_c51_idx_0_tmp_tmp;
  double f_re;
  double f_sc5_tmp_tmp;
  double fb_c51_idx_0_tmp_tmp;
  double g_c51_idx_0_tmp;
  double g_c51_idx_0_tmp_tmp;
  double g_re;
  double gb_c51_idx_0_tmp_tmp;
  double h_c51_idx_0_tmp;
  double h_c51_idx_0_tmp_tmp;
  double h_re;
  double hb_c51_idx_0_tmp_tmp;
  double i_c51_idx_0_tmp;
  double i_c51_idx_0_tmp_tmp;
  double i_re;
  double ib_c51_idx_0_tmp_tmp;
  double im;
  double j_c51_idx_0_tmp;
  double j_c51_idx_0_tmp_tmp;
  double j_re;
  double jb_c51_idx_0_tmp_tmp;
  double k_c51_idx_0_tmp;
  double k_c51_idx_0_tmp_tmp;
  double k_re;
  double kb_c51_idx_0_tmp_tmp;
  double l_c51_idx_0_tmp;
  double l_c51_idx_0_tmp_tmp;
  double l_re;
  double lb_c51_idx_0_tmp_tmp;
  double m_c51_idx_0_tmp;
  double m_c51_idx_0_tmp_tmp;
  double m_re;
  double mb_c51_idx_0_tmp_tmp;
  double n_c51_idx_0_tmp;
  double n_c51_idx_0_tmp_tmp;
  double n_re;
  double nb_c51_idx_0_tmp_tmp;
  double o_c51_idx_0_tmp;
  double o_c51_idx_0_tmp_tmp;
  double ob_c51_idx_0_tmp_tmp;
  double p_c51_idx_0_tmp;
  double p_c51_idx_0_tmp_tmp;
  double pb_c51_idx_0_tmp_tmp;
  double q_c51_idx_0_tmp;
  double q_c51_idx_0_tmp_tmp;
  double r_c51_idx_0_tmp;
  double r_c51_idx_0_tmp_tmp;
  double re;
  double s_c51_idx_0_tmp;
  double s_c51_idx_0_tmp_tmp;
  double sc4;
  double sc5_tmp_tmp;
  double scp0;
  double scr0;
  double t_c51_idx_0_tmp;
  double t_c51_idx_0_tmp_tmp;
  double u_c51_idx_0_tmp;
  double u_c51_idx_0_tmp_tmp;
  double v1_idx_0;
  double v1_idx_1;
  double v3_idx_0;
  double v3_idx_2;
  double v_c51_idx_0_tmp;
  double v_c51_idx_0_tmp_tmp;
  double w1_idx_0;
  double w1_idx_1;
  double w1_idx_2;
  double w1_idx_3;
  double w2_idx_0;
  double w2_idx_1;
  double w2_idx_2;
  double w2_idx_3;
  double w_c51_idx_0_tmp;
  double w_c51_idx_0_tmp_tmp;
  double x_c51_idx_0_tmp;
  double x_c51_idx_0_tmp_tmp;
  double y_c51_idx_0_tmp;
  double y_c51_idx_0_tmp_tmp;
  int IM;
  int a_tmp_tmp;
  int i;
  int i1;
  int i2;
  boolean_T guard1;
  boolean_T guard2;
  boolean_T guard3;
  if (!isInitialized_IK_7DOF) {
    IK_7DOF_initialize();
  }
  Px *= 1000.0;
  Py *= 1000.0;
  Pz *= 1000.0;
  for (IM = 0; IM < 7; IM++) {
    c[IM] = 0.0;
  }
  /*  phi=-14.05*pi/180; */
  /*  */
  /*  R=[R(1,1),R(1,2),R(1,3);R(2,1),R(2,2),R(2,3);R(3,1),R(3,2),R(3,3)]; */
  /*  l3=145; */
  /*  P=[Px;Py;Pz]-R*[l3;0;0]; */
  /*  Px=P(1); */
  /*  Py=P(2); */
  /*  Pz=P(3); */
  /*  T17=[-0.0550   -0.9904    0.1270  316.1736; */
  /*        0.9179   -0.0001    0.3967  285.6146; */
  /*       -0.3929    0.1384    0.9091   46.9064; */
  /*             0         0         0    1.0000]; */
  /*  Px=T17(1,4); */
  /*  Py=T17(2,4); */
  /*  Pz=T17(3,4); */
  v3_idx_2 = (Px * Px + Py * Py) + Pz * Pz;
  cc4 = ((v3_idx_2 - 102400.0) - 55225.0) / 150400.0;
  ccp0 = cc4 * cc4;
  sc4 = sqrt(1.0 - ccp0);
  scr0 = -Pz / (235.0 * cc4 + 320.0);
  ccr0 = sqrt(1.0 - scr0 * scr0);
  /*  T150=[ccp0,-scp0,0,0;scp0,ccp0,0,0;0,0,1,0;0,0,0,1]*[ccr0,0,scr0,0;0,1,0,0;-scr0,0,ccr0,0;0,0,0,1]*[1,0,0,0;0,1,0,0;0,0,1,0;0,0,0,1]*[1,0,0,l1;0,1,0,0;0,0,1,0;0,0,0,1]*[cc4,-sc4,0,0;sc4,cc4,0,0;0,0,1,0;0,0,0,1]*[1,0,0,l2;0,1,0,0;0,0,1,0;0,0,0,1];
   */
  /*   */
  /*  eq1=T150(1,4)-Px; */
  /*  eq2=scp0^2+ccp0^2-1; */
  /*   */
  /*  [scp0,ccp0]=solve(eq1,eq2,[scp0,ccp0]); */
  /*  scp0=[((ccr0*l1*(l2*sc4*(- Px^2 + cc4^2*ccr0^2*l2^2 + 2*cc4*ccr0^2*l1*l2 +
   * ccr0^2*l1^2 + l2^2*sc4^2)^(1/2) + Px*ccr0*l1 +
   * Px*cc4*ccr0*l2))/(cc4^2*ccr0^2*l2^2 + 2*cc4*ccr0^2*l1*l2 + ccr0^2*l1^2 +
   * l2^2*sc4^2) - Px + (cc4*ccr0*l2*(l2*sc4*(- Px^2 + cc4^2*ccr0^2*l2^2 +
   * 2*cc4*ccr0^2*l1*l2 + ccr0^2*l1^2 + l2^2*sc4^2)^(1/2) + Px*ccr0*l1 +
   * Px*cc4*ccr0*l2))/(cc4^2*ccr0^2*l2^2 + 2*cc4*ccr0^2*l1*l2 + ccr0^2*l1^2 +
   * l2^2*sc4^2))/(l2*sc4); */
  /*  ((ccr0*l1*(Px*ccr0*l1 - l2*sc4*(- Px^2 + cc4^2*ccr0^2*l2^2 +
   * 2*cc4*ccr0^2*l1*l2 + ccr0^2*l1^2 + l2^2*sc4^2)^(1/2) +
   * Px*cc4*ccr0*l2))/(cc4^2*ccr0^2*l2^2 + 2*cc4*ccr0^2*l1*l2 + ccr0^2*l1^2 +
   * l2^2*sc4^2) - Px + (cc4*ccr0*l2*(Px*ccr0*l1 - l2*sc4*(- Px^2 +
   * cc4^2*ccr0^2*l2^2 + 2*cc4*ccr0^2*l1*l2 + ccr0^2*l1^2 + l2^2*sc4^2)^(1/2) +
   * Px*cc4*ccr0*l2))/(cc4^2*ccr0^2*l2^2 + 2*cc4*ccr0^2*l1*l2 + ccr0^2*l1^2 +
   * l2^2*sc4^2))/(l2*sc4)]; */
  /*   */
  /*  ccp0=[(l2*sc4*(- Px^2 + cc4^2*ccr0^2*l2^2 + 2*cc4*ccr0^2*l1*l2 +
   * ccr0^2*l1^2 + l2^2*sc4^2)^(1/2) + Px*ccr0*l1 +
   * Px*cc4*ccr0*l2)/(cc4^2*ccr0^2*l2^2 + 2*cc4*ccr0^2*l1*l2 + ccr0^2*l1^2 +
   * l2^2*sc4^2); */
  /*  (Px*ccr0*l1 - l2*sc4*(- Px^2 + cc4^2*ccr0^2*l2^2 + 2*cc4*ccr0^2*l1*l2 +
   * ccr0^2*l1^2 + l2^2*sc4^2)^(1/2) + Px*cc4*ccr0*l2)/(cc4^2*ccr0^2*l2^2 +
   * 2*cc4*ccr0^2*l1*l2 + ccr0^2*l1^2 + l2^2*sc4^2)]; */
  /*  scp0=[(Py - (l2*sc4*(Py*l2*sc4 + ccr0*l1*(- Py^2 + cc4^2*ccr0^2*l2^2 +
   * 2*cc4*ccr0^2*l1*l2 + ccr0^2*l1^2 + l2^2*sc4^2)^(1/2) + cc4*ccr0*l2*(- Py^2
   * + cc4^2*ccr0^2*l2^2 + 2*cc4*ccr0^2*l1*l2 + ccr0^2*l1^2 +
   * l2^2*sc4^2)^(1/2)))/(cc4^2*ccr0^2*l2^2 + 2*cc4*ccr0^2*l1*l2 + ccr0^2*l1^2 +
   * l2^2*sc4^2))/(ccr0*l1 + cc4*ccr0*l2) */
  /*  (Py + (l2*sc4*(ccr0*l1*(- Py^2 + cc4^2*ccr0^2*l2^2 + 2*cc4*ccr0^2*l1*l2 +
   * ccr0^2*l1^2 + l2^2*sc4^2)^(1/2) - Py*l2*sc4 + cc4*ccr0*l2*(- Py^2 +
   * cc4^2*ccr0^2*l2^2 + 2*cc4*ccr0^2*l1*l2 + ccr0^2*l1^2 +
   * l2^2*sc4^2)^(1/2)))/(cc4^2*ccr0^2*l2^2 + 2*cc4*ccr0^2*l1*l2 + ccr0^2*l1^2 +
   * l2^2*sc4^2))/(ccr0*l1 + cc4*ccr0*l2)]; */
  /*   */
  /*  ccp0=[(Py*l2*sc4 + ccr0*l1*(- Py^2 + cc4^2*ccr0^2*l2^2 +
   * 2*cc4*ccr0^2*l1*l2 + ccr0^2*l1^2 + l2^2*sc4^2)^(1/2) + cc4*ccr0*l2*(- Py^2
   * + cc4^2*ccr0^2*l2^2 + 2*cc4*ccr0^2*l1*l2 + ccr0^2*l1^2 +
   * l2^2*sc4^2)^(1/2))/(cc4^2*ccr0^2*l2^2 + 2*cc4*ccr0^2*l1*l2 + ccr0^2*l1^2 +
   * l2^2*sc4^2) */
  /*  -(ccr0*l1*(- Py^2 + cc4^2*ccr0^2*l2^2 + 2*cc4*ccr0^2*l1*l2 + ccr0^2*l1^2 +
   * l2^2*sc4^2)^(1/2) - Py*l2*sc4 + cc4*ccr0*l2*(- Py^2 + cc4^2*ccr0^2*l2^2 +
   * 2*cc4*ccr0^2*l1*l2 + ccr0^2*l1^2 + l2^2*sc4^2)^(1/2))/(cc4^2*ccr0^2*l2^2 +
   * 2*cc4*ccr0^2*l1*l2 + ccr0^2*l1^2 + l2^2*sc4^2)]; */
  cphi = ccr0 * ccr0;
  cphi = ((ccp0 * cphi * 55225.0 + 2.0 * cc4 * cphi * 320.0 * 235.0) +
          cphi * 102400.0) +
         55225.0 * (sc4 * sc4);
  scp0 =
      ((Py * ccr0 * 320.0 - Px * 235.0 * sc4) + Py * cc4 * ccr0 * 235.0) / cphi;
  ccp0 =
      ((Px * ccr0 * 320.0 + Py * 235.0 * sc4) + Px * cc4 * ccr0 * 235.0) / cphi;
  /*  cp01=acos(ccp0); */
  /*  cp02=asin(scp0); */
  /*  if cp01(1)>=-25*pi/180 && cp01(1)<=pi && cp02(1)>=-25*pi/180 &&
   * cp02(1)<=pi */
  /*     ccp0=ccp0(1); */
  /*     scp0=scp0(1); */
  /*     index=1; */
  /*  else */
  /*      ccp0=ccp0(2); */
  /*      scp0=scp0(2); */
  /*      index=2; */
  /*  end */
  /* 以上角度为在cy=0的情况下求得的 */
  Pskew[0] = ccp0;
  Pskew[3] = -scp0;
  Pskew[6] = 0.0;
  Pskew[1] = scp0;
  Pskew[4] = ccp0;
  Pskew[7] = 0.0;
  Cs[0] = ccr0;
  Cs[3] = 0.0;
  Cs[6] = scr0;
  Pskew[2] = 0.0;
  Cs[1] = 0.0;
  Pskew[5] = 0.0;
  Cs[4] = 1.0;
  Pskew[8] = 1.0;
  Cs[7] = 0.0;
  Cs[2] = -scr0;
  Cs[5] = 0.0;
  Cs[8] = ccr0;
  for (IM = 0; IM < 3; IM++) {
    c51_idx_0_tmp_tmp = Pskew[IM];
    b_c51_idx_0_tmp_tmp = Pskew[IM + 3];
    i = (int)Pskew[IM + 6];
    for (i1 = 0; i1 < 3; i1++) {
      Aw[IM + 3 * i1] = (c51_idx_0_tmp_tmp * Cs[3 * i1] +
                         b_c51_idx_0_tmp_tmp * Cs[3 * i1 + 1]) +
                        (double)i * Cs[3 * i1 + 2];
    }
    c51_idx_0_tmp_tmp = Aw[IM];
    b_c51_idx_0_tmp_tmp = Aw[IM + 3];
    c_c51_idx_0_tmp_tmp = Aw[IM + 6];
    for (i = 0; i < 3; i++) {
      R130[IM + 3 * i] = (c51_idx_0_tmp_tmp * (double)b[3 * i] +
                          b_c51_idx_0_tmp_tmp * (double)b[3 * i + 1]) +
                         c_c51_idx_0_tmp_tmp * (double)b[3 * i + 2];
    }
  }
  /*  Pskew=[0,-Pz/(Px^2+Py^2+Pz^2)^0.5,Py/(Px^2+Py^2+Pz^2)^0.5;Pz/(Px^2+Py^2+Pz^2)^0.5,0,-Px/(Px^2+Py^2+Pz^2)^0.5;-Py/(Px^2+Py^2+Pz^2)^0.5,Px/(Px^2+Py^2+Pz^2)^0.5,0];
   */
  ccp0 = sqrt(v3_idx_2);
  Pskew[0] = 0.0 / ccp0;
  Pskew[3] = -Pz / ccp0;
  Pskew[6] = Py / ccp0;
  Pskew[1] = Pz / ccp0;
  Pskew[4] = 0.0 / ccp0;
  Pskew[7] = -Px / ccp0;
  Pskew[2] = -Py / ccp0;
  Pskew[5] = Px / ccp0;
  Pskew[8] = 0.0 / ccp0;
  for (IM = 0; IM < 3; IM++) {
    c51_idx_0_tmp_tmp = Pskew[IM + 3];
    b_c51_idx_0_tmp_tmp = Pskew[IM + 6];
    for (i = 0; i < 3; i++) {
      i1 = 3 * i + 1;
      i2 = 3 * i + 2;
      a_tmp_tmp = IM + 3 * i;
      a_tmp[a_tmp_tmp] =
          (Pskew[IM] * Pskew[3 * i] + c51_idx_0_tmp_tmp * Pskew[i1]) +
          b_c51_idx_0_tmp_tmp * Pskew[i2];
      As[a_tmp_tmp] = (Pskew[IM] * R130[3 * i] + c51_idx_0_tmp_tmp * R130[i1]) +
                      b_c51_idx_0_tmp_tmp * R130[i2];
    }
  }
  for (IM = 0; IM < 9; IM++) {
    Pskew[IM] = -a_tmp[IM];
  }
  for (IM = 0; IM < 3; IM++) {
    c51_idx_0_tmp_tmp = Pskew[IM];
    b_c51_idx_0_tmp_tmp = Pskew[IM + 3];
    c_c51_idx_0_tmp_tmp = Pskew[IM + 6];
    for (i = 0; i < 3; i++) {
      Bs[IM + 3 * i] = (c51_idx_0_tmp_tmp * R130[3 * i] +
                        b_c51_idx_0_tmp_tmp * R130[3 * i + 1]) +
                       c_c51_idx_0_tmp_tmp * R130[3 * i + 2];
    }
  }
  for (IM = 0; IM < 9; IM++) {
    a_tmp[IM] += (double)b[IM];
  }
  ccp0 = sin(phi);
  cphi = cos(phi);
  /*  cp=atan(tcp); */
  /*  ccp=cos(cp);scp=sin(cp); */
  /*  ccr=(1-scr^2)^0.5; */
  /*  cy=atan(tcy); */
  /*  ccy=cos(cy);scy=sin(cy); */
  Pskew[0] = cc4;
  Pskew[3] = -sc4;
  Pskew[6] = 0.0;
  Pskew[1] = sc4;
  Pskew[4] = cc4;
  Pskew[7] = 0.0;
  for (IM = 0; IM < 3; IM++) {
    c51_idx_0_tmp_tmp = a_tmp[IM];
    b_c51_idx_0_tmp_tmp = a_tmp[IM + 3];
    c_c51_idx_0_tmp_tmp = a_tmp[IM + 6];
    for (i = 0; i < 3; i++) {
      Cs[IM + 3 * i] = (c51_idx_0_tmp_tmp * R130[3 * i] +
                        b_c51_idx_0_tmp_tmp * R130[3 * i + 1]) +
                       c_c51_idx_0_tmp_tmp * R130[3 * i + 2];
    }
    Pskew[3 * IM + 2] = a[IM];
  }
  R130[0] = R[0];
  R130[3] = R[3];
  R130[6] = R[6];
  R130[1] = R[1];
  R130[4] = R[4];
  R130[7] = R[7];
  R130[2] = R[2];
  R130[5] = R[5];
  R130[8] = R[8];
  mtimes(Pskew, As, a_tmp);
  for (IM = 0; IM < 3; IM++) {
    c51_idx_0_tmp_tmp = a_tmp[IM];
    b_c51_idx_0_tmp_tmp = a_tmp[IM + 3];
    c_c51_idx_0_tmp_tmp = a_tmp[IM + 6];
    for (i = 0; i < 3; i++) {
      Aw[IM + 3 * i] = (c51_idx_0_tmp_tmp * R130[3 * i] +
                        b_c51_idx_0_tmp_tmp * R130[3 * i + 1]) +
                       c_c51_idx_0_tmp_tmp * R130[3 * i + 2];
    }
  }
  mtimes(Pskew, Bs, a_tmp);
  for (IM = 0; IM < 3; IM++) {
    c51_idx_0_tmp_tmp = a_tmp[IM];
    b_c51_idx_0_tmp_tmp = a_tmp[IM + 3];
    c_c51_idx_0_tmp_tmp = a_tmp[IM + 6];
    for (i = 0; i < 3; i++) {
      Bw[IM + 3 * i] = (c51_idx_0_tmp_tmp * R130[3 * i] +
                        b_c51_idx_0_tmp_tmp * R130[3 * i + 1]) +
                       c_c51_idx_0_tmp_tmp * R130[3 * i + 2];
    }
  }
  mtimes(Pskew, Cs, a_tmp);
  for (IM = 0; IM < 3; IM++) {
    c51_idx_0_tmp_tmp = a_tmp[IM];
    b_c51_idx_0_tmp_tmp = a_tmp[IM + 3];
    c_c51_idx_0_tmp_tmp = a_tmp[IM + 6];
    for (i = 0; i < 3; i++) {
      Pskew[IM + 3 * i] = (c51_idx_0_tmp_tmp * R130[3 * i] +
                           b_c51_idx_0_tmp_tmp * R130[3 * i + 1]) +
                          c_c51_idx_0_tmp_tmp * R130[3 * i + 2];
    }
  }
  crs = asin((-As[2] * ccp0 - Bs[2] * cphi) - Cs[2]);
  cys = atan(((As[5] * ccp0 + Bs[5] * cphi) + Cs[5]) /
             ((As[8] * ccp0 + Bs[8] * cphi) + Cs[8]));
  cps = rt_atan2d_snf((As[1] * ccp0 + Bs[1] * cphi) + Cs[1],
                      (As[0] * ccp0 + Bs[0] * cphi) + Cs[0]);
  cpw = atan(((Aw[1] * ccp0 + Bw[1] * cphi) + Pskew[1]) /
             ((Aw[0] * ccp0 + Bw[0] * cphi) + Pskew[0]));
  crw = asin((-Aw[2] * ccp0 - Bw[2] * cphi) - Pskew[2]);
  cyw = atan(((Aw[5] * ccp0 + Bw[5] * cphi) + Pskew[5]) /
             ((Aw[8] * ccp0 + Bw[8] * cphi) + Pskew[8]));
  c4 = acos(cc4);
  sc5_tmp_tmp = cos(crw);
  b_sc5_tmp_tmp = cos(cpw);
  c_sc5_tmp_tmp = sin(crw);
  d_sc5_tmp_tmp = sin(cpw);
  sc4 = cos(2.0 * cpw);
  e_sc5_tmp_tmp = cos(2.0 * crw);
  cc4 = sin(2.0 * cpw);
  f_sc5_tmp_tmp = sin(2.0 * crw);
  c51_idx_0_tmp_tmp = cos(3.0 * cpw);
  b_c51_idx_0_tmp_tmp = cos(3.0 * crw);
  c_c51_idx_0_tmp_tmp = cos(4.0 * cpw);
  d_c51_idx_0_tmp_tmp = cos(4.0 * crw);
  scp0 = sin(3.0 * cpw);
  cphi = sin(3.0 * crw);
  scr0 = sin(4.0 * cpw);
  im = 5.8381403164454094E+31 * d_c51_idx_0_tmp_tmp;
  re = 4.7577974638953085E+33 * c51_idx_0_tmp_tmp;
  b_im = 1.3165759884703893E+33 * c_c51_idx_0_tmp_tmp;
  b_re = 2.8055965393075818E+33 * e_sc5_tmp_tmp;
  c_im = 7.230165143290478E+32 * b_c51_idx_0_tmp_tmp;
  c_re = 1.2013213277109155E+34 * sc4;
  d_re = 4.2421596723753285E+33 * cc4;
  e_re = 6.248394006115564E+33 * scp0;
  f_re = 2.2805102969368449E+33 * scr0;
  g_re = 5.755069824220681E+33 * f_sc5_tmp_tmp;
  h_re = 6.8604407893722155E+33 * cphi;
  ccr0 = sin(4.0 * crw);
  d_im = 7.4666930876448766E+31 * ccr0;
  i_re = 5.3827097350021916E+33 * b_sc5_tmp_tmp;
  ccp0 = 3.320119296E+32 * d_c51_idx_0_tmp_tmp;
  j_re = 5.4585717593756787E+34 * sc5_tmp_tmp;
  k_re = 5.7836147512096631E+34 * d_sc5_tmp_tmp;
  l_re = 3.4116073496097991E+34 * c_sc5_tmp_tmp;
  m_re = 4.4018717431374439E+34 * d_sc5_tmp_tmp * c_sc5_tmp_tmp;
  n_re = 4.2115871289802583E+32 * sc4 * sc5_tmp_tmp;
  OBL_tmp_tmp = 3.984961976290063E+34 * e_sc5_tmp_tmp * b_sc5_tmp_tmp;
  b_OBL_tmp_tmp = 1.0002055389144305E+34 * c51_idx_0_tmp_tmp * sc5_tmp_tmp;
  c_OBL_tmp_tmp = 2.1538820478179424E+33 * b_c51_idx_0_tmp_tmp * b_sc5_tmp_tmp;
  d_OBL_tmp_tmp = 2.851090864560278E+32 * c_c51_idx_0_tmp_tmp * sc5_tmp_tmp;
  c51_idx_0 = 9.584133931008E+32 * d_c51_idx_0_tmp_tmp * b_sc5_tmp_tmp;
  c61_idx_0 = 2.5138324558498092E+34 * sc4 * c_sc5_tmp_tmp;
  d = 1.5011763324084408E+34 * e_sc5_tmp_tmp * d_sc5_tmp_tmp;
  d1 = 4.5110938138299357E+34 * cc4 * sc5_tmp_tmp;
  d2 = 1.5970952038019443E+34 * f_sc5_tmp_tmp * b_sc5_tmp_tmp;
  d3 = 1.5461961503813042E+34 * c51_idx_0_tmp_tmp * c_sc5_tmp_tmp;
  d4 = 1.4484787331476195E+33 * b_c51_idx_0_tmp_tmp * d_sc5_tmp_tmp;
  d5 = 7.290286633136127E+33 * scp0 * sc5_tmp_tmp;
  d6 = 1.0050559156466503E+33 * cphi * b_sc5_tmp_tmp;
  d7 = 4.561745383296445E+32 * c_c51_idx_0_tmp_tmp * c_sc5_tmp_tmp;
  d8 = ccp0 * d_sc5_tmp_tmp;
  d9 = 1.6459815060994205E+32 * scr0 * sc5_tmp_tmp;
  d10 = 7.4937483091968E+32 * ccr0 * b_sc5_tmp_tmp;
  d11 = 5.1448096851990978E+34 * cc4 * c_sc5_tmp_tmp;
  d12 = 2.7279702322102641E+33 * f_sc5_tmp_tmp * d_sc5_tmp_tmp;
  d13 = 1.197697563497588E+34 * scp0 * c_sc5_tmp_tmp;
  d14 = 2.3986669841642266E+33 * cphi * d_sc5_tmp_tmp;
  d15 = 2.6335704097590729E+32 * scr0 * c_sc5_tmp_tmp;
  d16 = 2.5959714816E+32 * ccr0 * d_sc5_tmp_tmp;
  d17 = 7.6013589615016022E+33 * sc4 * e_sc5_tmp_tmp;
  d18 = 1.2652334671024526E+33 * sc4 * b_c51_idx_0_tmp_tmp;
  d19 = 6.5320207674613464E+33 * c51_idx_0_tmp_tmp * e_sc5_tmp_tmp;
  d20 = 2.1670445446114592E+32 * sc4 * d_c51_idx_0_tmp_tmp;
  d21 = 2.3312948427725356E+33 * c51_idx_0_tmp_tmp * b_c51_idx_0_tmp_tmp;
  d22 = 8.1087809380215283E+32 * c_c51_idx_0_tmp_tmp * e_sc5_tmp_tmp;
  d23 = 1.916759310336E+32 * c51_idx_0_tmp_tmp * d_c51_idx_0_tmp_tmp;
  d24 = 1.442837002176E+33 * c_c51_idx_0_tmp_tmp * b_c51_idx_0_tmp_tmp;
  d25 = 7.02514173312E+31 * c_c51_idx_0_tmp_tmp * d_c51_idx_0_tmp_tmp;
  d26 = 2.3239558679214674E+34 * sc4 * f_sc5_tmp_tmp;
  d27 = 2.175118764509379E+34 * e_sc5_tmp_tmp * cc4;
  d28 = 5.6690400989117193E+33 * sc4 * cphi;
  d29 = 8.894636240240254E+33 * c51_idx_0_tmp_tmp * f_sc5_tmp_tmp;
  d30 = 3.1751514780100186E+33 * e_sc5_tmp_tmp * scp0;
  d31 = 1.7704355146323878E+33 * b_c51_idx_0_tmp_tmp * cc4;
  d32 = 2.7715429305955123E+32 * sc4 * ccr0;
  d33 = 2.579873238604677E+33 * c51_idx_0_tmp_tmp * cphi;
  d34 = 1.6633396795941595E+33 * c_c51_idx_0_tmp_tmp * f_sc5_tmp_tmp;
  d35 = 1.4045644601378208E+33 * e_sc5_tmp_tmp * scr0;
  d36 = 2.1008624605599006E+33 * b_c51_idx_0_tmp_tmp * scp0;
  d37 = 1.1140092418990081E+32 * d_c51_idx_0_tmp_tmp * cc4;
  e_c51_idx_0_tmp_tmp = 1.4986969030656E+32 * c51_idx_0_tmp_tmp * ccr0;
  f_c51_idx_0_tmp_tmp = 1.520594684928E+32 * c_c51_idx_0_tmp_tmp * cphi;
  g_c51_idx_0_tmp_tmp = 8.32973459884416E+32 * b_c51_idx_0_tmp_tmp * scr0;
  h_c51_idx_0_tmp_tmp = ccp0 * scp0;
  i_c51_idx_0_tmp_tmp = 8.9848092672E+31 * c_c51_idx_0_tmp_tmp * ccr0;
  j_c51_idx_0_tmp_tmp = 1.216861632E+32 * d_c51_idx_0_tmp_tmp * scr0;
  k_c51_idx_0_tmp_tmp = 3.7357559421952747E+33 * cc4 * f_sc5_tmp_tmp;
  l_c51_idx_0_tmp_tmp = 4.4732281067087635E+33 * cc4 * cphi;
  m_c51_idx_0_tmp_tmp = 1.4315405241766194E+34 * scp0 * f_sc5_tmp_tmp;
  n_c51_idx_0_tmp_tmp = 1.42476279349248E+32 * cc4 * ccr0;
  o_c51_idx_0_tmp_tmp = 1.1261520652071705E+33 * scp0 * cphi;
  p_c51_idx_0_tmp_tmp = 2.8811578669493762E+33 * scr0 * f_sc5_tmp_tmp;
  q_c51_idx_0_tmp_tmp = 2.5959714816E+32 * scp0 * ccr0;
  r_c51_idx_0_tmp_tmp = 8.77864245147648E+31 * scr0 * cphi;
  s_c51_idx_0_tmp_tmp = 1.55630592E+32 * scr0 * ccr0;
  t_c51_idx_0_tmp_tmp = 5.6796146972541731E+34 * b_sc5_tmp_tmp * sc5_tmp_tmp;
  u_c51_idx_0_tmp_tmp = 4.1449201019212249E+34 * b_sc5_tmp_tmp * c_sc5_tmp_tmp;
  v_c51_idx_0_tmp_tmp = 6.2558774135182555E+34 * sc5_tmp_tmp * d_sc5_tmp_tmp;
  w_c51_idx_0_tmp_tmp = 3.5135919432E+18 * sc4;
  x_c51_idx_0_tmp_tmp = 5.685887301744E+18 * e_sc5_tmp_tmp;
  d_c51_idx_0_tmp_tmp *= 1.56128E+17;
  y_c51_idx_0_tmp_tmp = 1.166335856768E+19 * f_sc5_tmp_tmp;
  w2_idx_3 = 1.9968E+17 * ccr0;
  v3_idx_0 = 4.5825876776813044E+19 * d_sc5_tmp_tmp;
  w1_idx_2 = 3.2064E+18 * b_c51_idx_0_tmp_tmp * b_sc5_tmp_tmp;
  w1_idx_1 = 2.59391808E+18 * e_sc5_tmp_tmp * d_sc5_tmp_tmp;
  w1_idx_3 = 9.976608E+18 * cc4 * sc5_tmp_tmp;
  ccp0 = 3.3792E+17 * cphi * b_sc5_tmp_tmp;
  scp0 = 1.59625728E+19 * cc4 * c_sc5_tmp_tmp;
  scr0 = 5.3208576E+18 * f_sc5_tmp_tmp * d_sc5_tmp_tmp;
  ccr0 = 2.2464E+18 * sc4 * e_sc5_tmp_tmp;
  cphi = 4.608E+18 * sc4 * f_sc5_tmp_tmp;
  v3_idx_2 = 2.81663946288E+19 * b_sc5_tmp_tmp * sc5_tmp_tmp;
  w1_idx_0 = 4.506623140608E+19 * b_sc5_tmp_tmp * c_sc5_tmp_tmp;
    c51_idx_0_tmp = sqrt(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((c_re + re) + b_im) + b_re) + c_im) - im) + d_re) - e_re) + f_re) - g_re) + h_re) - d_im) + i_re) + j_re) - k_re) - l_re) - m_re) - n_re) + OBL_tmp_tmp) + b_OBL_tmp_tmp) + c_OBL_tmp_tmp) - d_OBL_tmp_tmp) - c51_idx_0) + c61_idx_0) + d) - d1) + d2) + d3) - d4) + d5) - d6) - d7) - d8) + d9) + d10) - d11) + d12) + d13) + d14) + d15) + d16) - d17) + d18) - d19) + d20) + d21) - d22) - d23) - d24) + d25) - d26) + d27) + d28) + d29) + d30) + d31) + d32) - d33) + d34) - d35) + d36) - d37) + e_c51_idx_0_tmp_tmp) + f_c51_idx_0_tmp_tmp) + g_c51_idx_0_tmp_tmp) - h_c51_idx_0_tmp_tmp) + i_c51_idx_0_tmp_tmp) + j_c51_idx_0_tmp_tmp) + k_c51_idx_0_tmp_tmp) + l_c51_idx_0_tmp_tmp) - m_c51_idx_0_tmp_tmp) - n_c51_idx_0_tmp_tmp) + o_c51_idx_0_tmp_tmp) + p_c51_idx_0_tmp_tmp) + q_c51_idx_0_tmp_tmp) - r_c51_idx_0_tmp_tmp) + s_c51_idx_0_tmp_tmp) - t_c51_idx_0_tmp_tmp) - u_c51_idx_0_tmp_tmp) + v_c51_idx_0_tmp_tmp) - 3.9051323059259638E+34) / ((((((((((((((((y_c51_idx_0_tmp_tmp - x_c51_idx_0_tmp_tmp) - d_c51_idx_0_tmp_tmp) - w_c51_idx_0_tmp_tmp) - w2_idx_3) + v3_idx_0) - w1_idx_2) - w1_idx_1) + w1_idx_3) + ccp0) + scp0) + scr0) - ccr0) + cphi) + v3_idx_2) + w1_idx_0) + 4.440199560734525E+19));
    b_c51_idx_0_tmp = 2.4E+9 * b_sc5_tmp_tmp * sc5_tmp_tmp;
    c_c51_idx_0_tmp = 3.84E+9 * b_sc5_tmp_tmp * c_sc5_tmp_tmp;
    ab_c51_idx_0_tmp_tmp =
        2.9999106E+7 * d_sc5_tmp_tmp - 1.73205E+7 * b_sc5_tmp_tmp;
    bb_c51_idx_0_tmp_tmp = 1.6E+7 * d_sc5_tmp_tmp * c_sc5_tmp_tmp;
    cb_c51_idx_0_tmp_tmp = 1.732E+7 * b_sc5_tmp_tmp * sc5_tmp_tmp;
    db_c51_idx_0_tmp_tmp = 2.7712E+7 * b_sc5_tmp_tmp * c_sc5_tmp_tmp;
    eb_c51_idx_0_tmp_tmp = 1.0E+7 * sc5_tmp_tmp * d_sc5_tmp_tmp;
    d_c51_idx_0_tmp =
        (((((4.15692E+9 * d_sc5_tmp_tmp - 2.048E+9 * sc5_tmp_tmp) +
            1.28E+9 * c_sc5_tmp_tmp) +
           b_c51_idx_0_tmp) +
          c_c51_idx_0_tmp) +
         5.247928481E+9) /
        (80.0 * (((((ab_c51_idx_0_tmp_tmp + bb_c51_idx_0_tmp_tmp) +
                    cb_c51_idx_0_tmp_tmp) +
                   db_c51_idx_0_tmp_tmp) +
                  eb_c51_idx_0_tmp_tmp) +
                 5.196E+7));
    v1_idx_0 = 1.4999553E+7 * b_sc5_tmp_tmp / 500000.0 +
               34641.0 * d_sc5_tmp_tmp / 2000.0;
    v1_idx_1 = 3464.0 * d_sc5_tmp_tmp * c_sc5_tmp_tmp / 125.0;
    w2_idx_0 = 10.0 * b_sc5_tmp_tmp * sc5_tmp_tmp;
    w2_idx_2 = 16.0 * b_sc5_tmp_tmp * c_sc5_tmp_tmp;
    w2_idx_1 = 433.0 * sc5_tmp_tmp * d_sc5_tmp_tmp / 25.0;
    e_c51_idx_0_tmp =
        1.5625E+15 *
        (((((v1_idx_0 - v1_idx_1) + w2_idx_0) + w2_idx_2) - w2_idx_1) + 30.0);
    fb_c51_idx_0_tmp_tmp = 1.463996643E+9 * sc4 / 100000.0;
    gb_c51_idx_0_tmp_tmp = 6.33910546419E+11 * cc4 / 2.5E+7;
    hb_c51_idx_0_tmp_tmp = 7.8716581390969E+16 * b_sc5_tmp_tmp / 5.0E+11;
    c51_idx_0_tmp_tmp = 4.31208690510321E+14 * d_sc5_tmp_tmp / 2.0E+9;
    c_c51_idx_0_tmp_tmp =
        1.925943032273E+12 * d_sc5_tmp_tmp * c_sc5_tmp_tmp / 1.5625E+7;
    f_c51_idx_0_tmp = (((((((gb_c51_idx_0_tmp_tmp - 9360.0 * e_sc5_tmp_tmp) -
                            fb_c51_idx_0_tmp_tmp) +
                           19200.0 * f_sc5_tmp_tmp) +
                          hb_c51_idx_0_tmp_tmp) -
                         61440.0 * sc5_tmp_tmp) +
                        c51_idx_0_tmp_tmp) +
                       38400.0 * c_sc5_tmp_tmp) -
                      c_c51_idx_0_tmp_tmp;
    g_c51_idx_0_tmp = 7.7951435732955246E+9 * c51_idx_0_tmp / 1.0E+12;
    h_c51_idx_0_tmp = 4.4998659E+7 * sc4 * sc5_tmp_tmp / 625.0;
    i_c51_idx_0_tmp = 20480.0 * e_sc5_tmp_tmp * b_sc5_tmp_tmp;
    j_c51_idx_0_tmp = 3.59989272E+8 * sc4 * c_sc5_tmp_tmp / 3125.0;
    k_c51_idx_0_tmp = 886784.0 * e_sc5_tmp_tmp * d_sc5_tmp_tmp / 25.0;
    l_c51_idx_0_tmp = 207846.0 * cc4 * sc5_tmp_tmp / 5.0;
    m_c51_idx_0_tmp = 9984.0 * f_sc5_tmp_tmp * b_sc5_tmp_tmp;
    n_c51_idx_0_tmp = 1.662768E+6 * cc4 * c_sc5_tmp_tmp / 25.0;
    o_c51_idx_0_tmp = 2.161536E+6 * f_sc5_tmp_tmp * d_sc5_tmp_tmp / 125.0;
    p_c51_idx_0_tmp = 9360.0 * sc4 * e_sc5_tmp_tmp;
    q_c51_idx_0_tmp = 19200.0 * sc4 * f_sc5_tmp_tmp;
    r_c51_idx_0_tmp = 405288.0 * e_sc5_tmp_tmp * cc4 / 25.0;
    s_c51_idx_0_tmp = 166272.0 * cc4 * f_sc5_tmp_tmp / 5.0;
    t_c51_idx_0_tmp = 3.1520557861E+10 * b_sc5_tmp_tmp * sc5_tmp_tmp / 500000.0;
    u_c51_idx_0_tmp =
        1.4847856961E+10 * b_sc5_tmp_tmp * c_sc5_tmp_tmp / 62500.0;
    v_c51_idx_0_tmp = 3.159162632273E+12 * sc5_tmp_tmp * d_sc5_tmp_tmp / 2.5E+7;
    w_c51_idx_0_tmp =
        55.154328932550712 * e_sc5_tmp_tmp * c51_idx_0_tmp / 125000.0;
    x_c51_idx_0_tmp =
        2.8284271247461903 * f_sc5_tmp_tmp * c51_idx_0_tmp / 3125.0;
    y_c51_idx_0_tmp =
        146969.31604249918 * d_sc5_tmp_tmp * c51_idx_0_tmp / 2.5E+7;
    b_c51_idx_0_tmp_tmp = 4.2426406871192857 * b_sc5_tmp_tmp * sc5_tmp_tmp;
    ab_c51_idx_0_tmp = b_c51_idx_0_tmp_tmp * c51_idx_0_tmp / 1250.0;
    ib_c51_idx_0_tmp_tmp = 16.970562748477143 * b_sc5_tmp_tmp * c_sc5_tmp_tmp;
    c51_idx_0_tmp = ib_c51_idx_0_tmp_tmp * c51_idx_0_tmp / 3125.0;
    c51_idx_0_tmp_tmp_tmp = 4.15692E+9 * d_sc5_tmp_tmp;
    jb_c51_idx_0_tmp_tmp =
        (c51_idx_0_tmp_tmp_tmp - 6.24E+8 * (sc5_tmp_tmp * sc5_tmp_tmp)) +
        b_c51_idx_0_tmp;
    kb_c51_idx_0_tmp_tmp = 1.28E+9 * sc5_tmp_tmp * c_sc5_tmp_tmp;
    lb_c51_idx_0_tmp_tmp =
        1.4999553E+7 * d_sc5_tmp_tmp - 8.66025E+6 * b_sc5_tmp_tmp;
    mb_c51_idx_0_tmp_tmp = 8.0E+6 * d_sc5_tmp_tmp * c_sc5_tmp_tmp;
    nb_c51_idx_0_tmp_tmp = 8.66E+6 * b_sc5_tmp_tmp * sc5_tmp_tmp;
    ob_c51_idx_0_tmp_tmp = 1.3856E+7 * b_sc5_tmp_tmp * c_sc5_tmp_tmp;
    pb_c51_idx_0_tmp_tmp = 5.0E+6 * sc5_tmp_tmp * d_sc5_tmp_tmp;
    b_sc5_tmp_tmp =
        249989.0 *
        (((jb_c51_idx_0_tmp_tmp + c_c51_idx_0_tmp) + kb_c51_idx_0_tmp_tmp) +
         5.823998881E+9) *
        (((((lb_c51_idx_0_tmp_tmp + mb_c51_idx_0_tmp_tmp) +
            nb_c51_idx_0_tmp_tmp) +
           ob_c51_idx_0_tmp_tmp) +
          pb_c51_idx_0_tmp_tmp) +
         2.598E+7);
    w1_idx_2 = sqrt(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((im - re) - b_im) - b_re) - c_im) - c_re) - d_re) + e_re) - f_re) - g_re) + h_re) - d_im) - i_re) - j_re) + k_re) - l_re) - m_re) + n_re) - OBL_tmp_tmp) - b_OBL_tmp_tmp) - c_OBL_tmp_tmp) + d_OBL_tmp_tmp) + c51_idx_0) + c61_idx_0) - d) + d1) + d2) + d3) + d4) - d5) - d6) - d7) + d8) - d9) + d10) - d11) + d12) + d13) + d14) + d15) + d16) + d17) - d18) + d19) - d20) - d21) + d22) + d23) + d24) - d25) - d26) - d27) + d28) + d29) - d30) - d31) + d32) - d33) + d34) + d35) - d36) + d37) + e_c51_idx_0_tmp_tmp) + f_c51_idx_0_tmp_tmp) - g_c51_idx_0_tmp_tmp) + h_c51_idx_0_tmp_tmp) + i_c51_idx_0_tmp_tmp) - j_c51_idx_0_tmp_tmp) + k_c51_idx_0_tmp_tmp) + l_c51_idx_0_tmp_tmp) - m_c51_idx_0_tmp_tmp) - n_c51_idx_0_tmp_tmp) + o_c51_idx_0_tmp_tmp) + p_c51_idx_0_tmp_tmp) + q_c51_idx_0_tmp_tmp) - r_c51_idx_0_tmp_tmp) + s_c51_idx_0_tmp_tmp) + t_c51_idx_0_tmp_tmp) - u_c51_idx_0_tmp_tmp) - v_c51_idx_0_tmp_tmp) + 3.9051323059259638E+34) / ((((((((((((((((w_c51_idx_0_tmp_tmp + x_c51_idx_0_tmp_tmp) + d_c51_idx_0_tmp_tmp) + y_c51_idx_0_tmp_tmp) - w2_idx_3) - v3_idx_0) + w1_idx_2) + w1_idx_1) - w1_idx_3) + ccp0) + scp0) + scr0) + ccr0) + cphi) - v3_idx_2) + w1_idx_0) - 4.440199560734525E+19));
    w1_idx_0 =
        1.5625E+15 *
        (((((v1_idx_0 + v1_idx_1) + w2_idx_0) - w2_idx_2) - w2_idx_1) + 30.0);
    cc4 = (((((((fb_c51_idx_0_tmp_tmp + 9360.0 * e_sc5_tmp_tmp) -
                gb_c51_idx_0_tmp_tmp) +
               19200.0 * f_sc5_tmp_tmp) -
              hb_c51_idx_0_tmp_tmp) +
             61440.0 * sc5_tmp_tmp) -
            c51_idx_0_tmp_tmp) +
           38400.0 * c_sc5_tmp_tmp) -
          c_c51_idx_0_tmp_tmp;
    v3_idx_2 = 7.7951435732955246E+9 * w1_idx_2 / 1.0E+12;
    sc4 = 55.154328932550712 * e_sc5_tmp_tmp * w1_idx_2 / 125000.0;
    cphi = 2.8284271247461903 * f_sc5_tmp_tmp * w1_idx_2 / 3125.0;
    ccr0 = 146969.31604249918 * d_sc5_tmp_tmp * w1_idx_2 / 2.5E+7;
    scr0 = b_c51_idx_0_tmp_tmp * w1_idx_2 / 1250.0;
    w1_idx_2 = ib_c51_idx_0_tmp_tmp * w1_idx_2 / 3125.0;
    scp0 = 249989.0 *
           (((jb_c51_idx_0_tmp_tmp - c_c51_idx_0_tmp) - kb_c51_idx_0_tmp_tmp) +
            5.823998881E+9) *
           (((((lb_c51_idx_0_tmp_tmp - mb_c51_idx_0_tmp_tmp) +
               nb_c51_idx_0_tmp_tmp) -
              ob_c51_idx_0_tmp_tmp) +
             pb_c51_idx_0_tmp_tmp) +
            2.598E+7);
    ccp0 = (((((2.048E+9 * sc5_tmp_tmp - c51_idx_0_tmp_tmp_tmp) +
               1.28E+9 * c_sc5_tmp_tmp) -
              b_c51_idx_0_tmp) +
             c_c51_idx_0_tmp) -
            5.247928481E+9) /
           (80.0 * (((((ab_c51_idx_0_tmp_tmp - bb_c51_idx_0_tmp_tmp) +
                       cb_c51_idx_0_tmp_tmp) -
                      db_c51_idx_0_tmp_tmp) +
                     eb_c51_idx_0_tmp_tmp) +
                    5.196E+7));
    c51_idx_0 =
        asin(d_c51_idx_0_tmp -
             e_c51_idx_0_tmp *
                 ((((((((((((((((((((((f_c51_idx_0_tmp + g_c51_idx_0_tmp) +
                                      h_c51_idx_0_tmp) -
                                     i_c51_idx_0_tmp) +
                                    j_c51_idx_0_tmp) +
                                   k_c51_idx_0_tmp) +
                                  l_c51_idx_0_tmp) -
                                 m_c51_idx_0_tmp) +
                                n_c51_idx_0_tmp) +
                               o_c51_idx_0_tmp) -
                              p_c51_idx_0_tmp) +
                             q_c51_idx_0_tmp) +
                            r_c51_idx_0_tmp) -
                           s_c51_idx_0_tmp) +
                          t_c51_idx_0_tmp) +
                         u_c51_idx_0_tmp) -
                        v_c51_idx_0_tmp) -
                       w_c51_idx_0_tmp) +
                      x_c51_idx_0_tmp) +
                     y_c51_idx_0_tmp) +
                    ab_c51_idx_0_tmp) +
                   c51_idx_0_tmp) +
                  214797.82086) /
                 b_sc5_tmp_tmp);
    c61_idx_0 =
        asin(w1_idx_0 *
                 ((((((((((((((((((((((cc4 - v3_idx_2) - h_c51_idx_0_tmp) +
                                     i_c51_idx_0_tmp) +
                                    j_c51_idx_0_tmp) -
                                   k_c51_idx_0_tmp) -
                                  l_c51_idx_0_tmp) -
                                 m_c51_idx_0_tmp) +
                                n_c51_idx_0_tmp) +
                               o_c51_idx_0_tmp) +
                              p_c51_idx_0_tmp) +
                             q_c51_idx_0_tmp) -
                            r_c51_idx_0_tmp) -
                           s_c51_idx_0_tmp) -
                          t_c51_idx_0_tmp) +
                         u_c51_idx_0_tmp) +
                        v_c51_idx_0_tmp) +
                       sc4) +
                      cphi) -
                     ccr0) -
                    scr0) +
                   w1_idx_2) -
                  214797.82086) /
                 scp0 -
             ccp0);
    if ((!(c51_idx_0 >= -1.0471975511965976)) ||
        (!(c51_idx_0 <= 0.47123889803846897))) {
      c51_idx_0 =
          asin(d_c51_idx_0_tmp -
               e_c51_idx_0_tmp *
                   ((((((((((((((((((((((f_c51_idx_0_tmp - g_c51_idx_0_tmp) +
                                        h_c51_idx_0_tmp) -
                                       i_c51_idx_0_tmp) +
                                      j_c51_idx_0_tmp) +
                                     k_c51_idx_0_tmp) +
                                    l_c51_idx_0_tmp) -
                                   m_c51_idx_0_tmp) +
                                  n_c51_idx_0_tmp) +
                                 o_c51_idx_0_tmp) -
                                p_c51_idx_0_tmp) +
                               q_c51_idx_0_tmp) +
                              r_c51_idx_0_tmp) -
                             s_c51_idx_0_tmp) +
                            t_c51_idx_0_tmp) +
                           u_c51_idx_0_tmp) -
                          v_c51_idx_0_tmp) +
                         w_c51_idx_0_tmp) -
                        x_c51_idx_0_tmp) -
                       y_c51_idx_0_tmp) -
                      ab_c51_idx_0_tmp) -
                     c51_idx_0_tmp) +
                    214797.82086) /
                   b_sc5_tmp_tmp);
    }
    if ((!(c61_idx_0 >= -1.0471975511965976)) ||
        (!(c61_idx_0 <= 0.47123889803846897))) {
      c61_idx_0 =
          asin(w1_idx_0 *
                   ((((((((((((((((((((((cc4 + v3_idx_2) - h_c51_idx_0_tmp) +
                                       i_c51_idx_0_tmp) +
                                      j_c51_idx_0_tmp) -
                                     k_c51_idx_0_tmp) -
                                    l_c51_idx_0_tmp) -
                                   m_c51_idx_0_tmp) +
                                  n_c51_idx_0_tmp) +
                                 o_c51_idx_0_tmp) +
                                p_c51_idx_0_tmp) +
                               q_c51_idx_0_tmp) -
                              r_c51_idx_0_tmp) -
                             s_c51_idx_0_tmp) -
                            t_c51_idx_0_tmp) +
                           u_c51_idx_0_tmp) +
                          v_c51_idx_0_tmp) -
                         sc4) -
                        cphi) +
                       ccr0) +
                      scr0) -
                     w1_idx_2) -
                    214797.82086) /
                   scp0 -
               ccp0);
    }
    /*  if round(c51(1)*1000)==round(c52(1)*1000) */
    /*      c5=c51(1); */
    /*  else */
    /*      c5=c51(2); */
    /*  end */
    /*   */
    /*  if round(c61(1)*1000)==round(c62(1)*1000) */
    /*      c6=c61(1); */
    /*  else */
    /*      c6=c61(2); */
    /*  end */
    /* 结果来源于"test4,m"此处将cr,cp,cy替换为0，以求得三力臂的初始角度,最新一次修改于2023.11.13
     */
    /* %此向量本来在c3坐标系中，为了便于下面的干涉检查计算，做统一坐标系处理 */
    /* 此向量本来在c3坐标系中，为了便于下面的干涉检查计算，做统一坐标系处理 */
    /*  eq1=w3(1)*v3(1)+w3(2)*v3(2)+w3(3)*v3(3)-R^2*cos(gama); */
    /* phi为连杆之间的干涉角 */
    c_OBL_tmp_tmp = sin(cys);
    OBL_tmp_tmp = cos(cys);
    d_OBL_tmp_tmp = sin(crs);
    b_OBL_tmp_tmp = cos(crs);
    c10_tmp_tmp.re = 0.0;
    c10_tmp_tmp.im = 0.0;
    b_exp(&c10_tmp_tmp);
    b_c10_tmp_tmp.re = 0.0;
    b_c10_tmp_tmp.im = 1.0471975511965976;
    b_exp(&b_c10_tmp_tmp);
    c10_tmp.re = crs * 0.0;
    c10_tmp.im = crs * 2.0;
    b_exp(&c10_tmp);
    b_c10_tmp.re = cys * 0.0;
    b_c10_tmp.im = cys;
    b_exp(&b_c10_tmp);
    c_c10_tmp.re = crs * 0.0;
    c_c10_tmp.im = crs;
    b_exp(&c_c10_tmp);
    d_c10_tmp.re = cys * 0.0;
    d_c10_tmp.im = cys * 2.0;
    b_exp(&d_c10_tmp);
    sc4 = 14964.5 * c_c10_tmp.re;
    cc4 = 14964.5 * c_c10_tmp.im;
    k_c51_idx_0_tmp_tmp = 7482.25 * c10_tmp.re;
    l_c51_idx_0_tmp_tmp = 7482.25 * c10_tmp.im;
    c_c10_tmp_tmp.re = 0.0;
    c_c10_tmp_tmp.im = 0.52359877559829882;
    b_exp(&c_c10_tmp_tmp);
    dc.re = crs * 0.0;
    dc.im = crs;
    b_exp(&dc);
    dc1.re = cys * 0.0;
    dc1.im = cys;
    b_exp(&dc1);
    m_c51_idx_0_tmp_tmp =
        7.3304908103362271E-12 * c10_tmp_tmp.re - 119716.0 * c10_tmp_tmp.im;
    n_c51_idx_0_tmp_tmp =
        7.3304908103362271E-12 * c10_tmp_tmp.im + 119716.0 * c10_tmp_tmp.re;
    k_re = m_c51_idx_0_tmp_tmp * dc.re - n_c51_idx_0_tmp_tmp * dc.im;
    d_im = m_c51_idx_0_tmp_tmp * dc.im + n_c51_idx_0_tmp_tmp * dc.re;
    l_re = k_re * dc1.re - d_im * dc1.im;
    d_im = k_re * dc1.im + d_im * dc1.re;
    g_c10_tmp.re = 0.64278760968653936 *
                   (l_re * c_c10_tmp_tmp.re - d_im * c_c10_tmp_tmp.im);
    g_c10_tmp.im = 0.64278760968653936 *
                   (l_re * c_c10_tmp_tmp.im + d_im * c_c10_tmp_tmp.re);
    dc.re = crs * 0.0;
    dc.im = crs;
    b_exp(&dc);
    dc1.re = cys * 0.0;
    dc1.im = cys;
    b_exp(&dc1);
    v3_idx_2 =
        3.6652454051681135E-12 * c10_tmp_tmp.re - 59858.0 * c10_tmp_tmp.im;
    w1_idx_0 =
        3.6652454051681135E-12 * c10_tmp_tmp.im + 59858.0 * c10_tmp_tmp.re;
    k_re = v3_idx_2 * dc.re - w1_idx_0 * dc.im;
    d_im = v3_idx_2 * dc.im + w1_idx_0 * dc.re;
    l_re = k_re * dc1.re - d_im * dc1.im;
    d_im = k_re * dc1.im + d_im * dc1.re;
    h_c10_tmp.re = 0.64278760968653936 *
                   (l_re * c_c10_tmp_tmp.re - d_im * c_c10_tmp_tmp.im);
    h_c10_tmp.im = 0.64278760968653936 *
                   (l_re * c_c10_tmp_tmp.im + d_im * c_c10_tmp_tmp.re);
    k_re = 3.6652454051681119E-12 * c10_tmp_tmp.re -
           59857.999999999978 * c10_tmp_tmp.im;
    d_im = 3.6652454051681119E-12 * c10_tmp_tmp.im +
           59857.999999999978 * c10_tmp_tmp.re;
    l_re = k_re * c_c10_tmp.re - d_im * c_c10_tmp.im;
    d_im = k_re * c_c10_tmp.im + d_im * c_c10_tmp.re;
    k_re = l_re * b_c10_tmp.re - d_im * b_c10_tmp.im;
    d_im = l_re * b_c10_tmp.im + d_im * b_c10_tmp.re;
    l_re =
        m_c51_idx_0_tmp_tmp * c_c10_tmp.re - n_c51_idx_0_tmp_tmp * c_c10_tmp.im;
    o_c51_idx_0_tmp_tmp =
        m_c51_idx_0_tmp_tmp * c_c10_tmp.im + n_c51_idx_0_tmp_tmp * c_c10_tmp.re;
    m_re = l_re * b_c10_tmp.re - o_c51_idx_0_tmp_tmp * b_c10_tmp.im;
    o_c51_idx_0_tmp_tmp =
        l_re * b_c10_tmp.im + o_c51_idx_0_tmp_tmp * b_c10_tmp.re;
    b_a.re =
        ((((k_re * c_c10_tmp_tmp.re - d_im * c_c10_tmp_tmp.im) -
           (m_re * c_c10_tmp_tmp.re - o_c51_idx_0_tmp_tmp * c_c10_tmp_tmp.im)) -
          0.86602540378443871 * g_c10_tmp.re * d_OBL_tmp_tmp) +
         c_OBL_tmp_tmp *
             (b_OBL_tmp_tmp * (6.123233995736766E-17 * g_c10_tmp.re)) *
             0.49999999999999994) +
        OBL_tmp_tmp * (b_OBL_tmp_tmp * g_c10_tmp.re) * 0.49999999999999994;
    b_a.im =
        ((((k_re * c_c10_tmp_tmp.im + d_im * c_c10_tmp_tmp.re) -
           (m_re * c_c10_tmp_tmp.im + o_c51_idx_0_tmp_tmp * c_c10_tmp_tmp.re)) -
          0.86602540378443871 * g_c10_tmp.im * d_OBL_tmp_tmp) +
         c_OBL_tmp_tmp *
             (b_OBL_tmp_tmp * (6.123233995736766E-17 * g_c10_tmp.im)) *
             0.49999999999999994) +
        OBL_tmp_tmp * (b_OBL_tmp_tmp * g_c10_tmp.im) * 0.49999999999999994;
    dc.re = crs * 0.0;
    dc.im = crs;
    b_exp(&dc);
    dc1.re = crs * 0.0;
    dc1.im = crs * 2.0;
    b_exp(&dc1);
    dc2.re = 0.0;
    dc2.im = 0.0;
    b_exp(&dc2);
    dc3.re = 0.0;
    dc3.im = 0.0;
    b_exp(&dc3);
    dc4.re = 0.0;
    dc4.im = 0.0;
    b_exp(&dc4);
    dc5.re = cys * 0.0;
    dc5.im = cys;
    b_exp(&dc5);
    dc6.re = 0.0;
    dc6.im = 0.0;
    b_exp(&dc6);
    dc7.re = cys * 0.0;
    dc7.im = cys * 2.0;
    b_exp(&dc7);
    dc8.re = 0.0;
    dc8.im = 0.0;
    b_exp(&dc8);
    dc9.re = crs * 0.0;
    dc9.im = crs * 2.0;
    b_exp(&dc9);
    dc10.re = cys * 0.0;
    dc10.im = cys;
    b_exp(&dc10);
    dc11.re = 0.0;
    dc11.im = 0.0;
    b_exp(&dc11);
    dc12.re = crs * 0.0;
    dc12.im = crs;
    b_exp(&dc12);
    dc13.re = cys * 0.0;
    dc13.im = cys * 2.0;
    b_exp(&dc13);
    dc14.re = 0.0;
    dc14.im = 0.0;
    b_exp(&dc14);
    dc15.re = crs * 0.0;
    dc15.im = crs * 2.0;
    b_exp(&dc15);
    dc16.re = cys * 0.0;
    dc16.im = cys * 2.0;
    b_exp(&dc16);
    dc17.re = cys * 0.0;
    dc17.im = cys;
    b_exp(&dc17);
    dc18.re = cys * 0.0;
    dc18.im = cys * 2.0;
    b_exp(&dc18);
    dc19.re = crs * 0.0;
    dc19.im = crs * 2.0;
    b_exp(&dc19);
    dc20.re = cys * 0.0;
    dc20.im = cys;
    b_exp(&dc20);
    dc21.re = crs * 0.0;
    dc21.im = crs;
    b_exp(&dc21);
    dc22.re = cys * 0.0;
    dc22.im = cys * 2.0;
    b_exp(&dc22);
    dc23.re = crs * 0.0;
    dc23.im = crs * 2.0;
    b_exp(&dc23);
    dc24.re = cys * 0.0;
    dc24.im = cys * 2.0;
    b_exp(&dc24);
    m_c51_idx_0_tmp_tmp = 0.0 * c_c10_tmp.im;
    n_c51_idx_0_tmp_tmp = 0.0 * c_c10_tmp.re;
    k_re = 0.766044443118978 * (k_c51_idx_0_tmp_tmp - 0.0 * c10_tmp.im);
    d_im = 0.766044443118978 * (l_c51_idx_0_tmp_tmp + 0.0 * c10_tmp.re);
    scp0 = 9.1631135129202838E-13 * c10_tmp_tmp.re;
    l_re = scp0 - 14964.5 * c10_tmp_tmp.im;
    ccp0 = 9.1631135129202838E-13 * c10_tmp_tmp.im;
    o_c51_idx_0_tmp_tmp = ccp0 + 14964.5 * c10_tmp_tmp.re;
    m_re = -7482.25 * c10_tmp_tmp.re - ccp0;
    kb_c51_idx_0_tmp_tmp = -7482.25 * c10_tmp_tmp.im + scp0;
    n_re = 0.766044443118978 *
           (m_re * d_c10_tmp.re - kb_c51_idx_0_tmp_tmp * d_c10_tmp.im);
    kb_c51_idx_0_tmp_tmp =
        0.766044443118978 *
        (m_re * d_c10_tmp.im + kb_c51_idx_0_tmp_tmp * d_c10_tmp.re);
    m_re = 14964.5 * dc.re - 0.0 * dc.im;
    lb_c51_idx_0_tmp_tmp = 14964.5 * dc.im + 0.0 * dc.re;
    i_re = 7482.25 * dc1.re - 0.0 * dc1.im;
    mb_c51_idx_0_tmp_tmp = 7482.25 * dc1.im + 0.0 * dc1.re;
    j_re = 0.766044443118978 *
           (i_re * b_c10_tmp_tmp.re - mb_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.im);
    mb_c51_idx_0_tmp_tmp =
        0.766044443118978 *
        (i_re * b_c10_tmp_tmp.im + mb_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.re);
    i_re = 9.1631135129202838E-13 * dc2.re - 14964.5 * dc2.im;
    nb_c51_idx_0_tmp_tmp = 9.1631135129202838E-13 * dc2.im + 14964.5 * dc2.re;
    h_c51_idx_0_tmp_tmp = i_re * c10_tmp.re - nb_c51_idx_0_tmp_tmp * c10_tmp.im;
    nb_c51_idx_0_tmp_tmp =
        i_re * c10_tmp.im + nb_c51_idx_0_tmp_tmp * c10_tmp.re;
    i_re = -14964.5 * c10_tmp_tmp.re - 1.8326227025840568E-12 * c10_tmp_tmp.im;
    c51_idx_0_tmp_tmp_tmp =
        -14964.5 * c10_tmp_tmp.im + 1.8326227025840568E-12 * c10_tmp_tmp.re;
    e_c51_idx_0_tmp_tmp =
        i_re * c_c10_tmp.re - c51_idx_0_tmp_tmp_tmp * c_c10_tmp.im;
    c51_idx_0_tmp_tmp_tmp =
        i_re * c_c10_tmp.im + c51_idx_0_tmp_tmp_tmp * c_c10_tmp.re;
    i_re = -7482.25 * dc3.re - 9.1631135129202838E-13 * dc3.im;
    f_c51_idx_0_tmp_tmp = -7482.25 * dc3.im + 9.1631135129202838E-13 * dc3.re;
    g_c51_idx_0_tmp_tmp = i_re * c10_tmp.re - f_c51_idx_0_tmp_tmp * c10_tmp.im;
    f_c51_idx_0_tmp_tmp = i_re * c10_tmp.im + f_c51_idx_0_tmp_tmp * c10_tmp.re;
    i_re = 0.766044443118978 * (g_c51_idx_0_tmp_tmp * d_c10_tmp.re -
                                f_c51_idx_0_tmp_tmp * d_c10_tmp.im);
    f_c51_idx_0_tmp_tmp =
        0.766044443118978 * (g_c51_idx_0_tmp_tmp * d_c10_tmp.im +
                             f_c51_idx_0_tmp_tmp * d_c10_tmp.re);
    g_c51_idx_0_tmp_tmp = 9.1631135129202838E-13 * dc4.re - 14964.5 * dc4.im;
    im = 9.1631135129202838E-13 * dc4.im + 14964.5 * dc4.re;
    re = g_c51_idx_0_tmp_tmp * dc5.re - im * dc5.im;
    im = g_c51_idx_0_tmp_tmp * dc5.im + im * dc5.re;
    g_c51_idx_0_tmp_tmp = -7482.25 * dc6.re - 9.1631135129202838E-13 * dc6.im;
    b_im = -7482.25 * dc6.im + 9.1631135129202838E-13 * dc6.re;
    b_re = g_c51_idx_0_tmp_tmp * dc7.re - b_im * dc7.im;
    b_im = g_c51_idx_0_tmp_tmp * dc7.im + b_im * dc7.re;
    g_c51_idx_0_tmp_tmp =
        0.766044443118978 * (b_re * b_c10_tmp_tmp.re - b_im * b_c10_tmp_tmp.im);
    b_im =
        0.766044443118978 * (b_re * b_c10_tmp_tmp.im + b_im * b_c10_tmp_tmp.re);
    b_re = 9.1631135129202838E-13 * dc8.re - 14964.5 * dc8.im;
    c_im = 9.1631135129202838E-13 * dc8.im + 14964.5 * dc8.re;
    c_re = b_re * dc9.re - c_im * dc9.im;
    c_im = b_re * dc9.im + c_im * dc9.re;
    b_re = c_re * dc10.re - c_im * dc10.im;
    c_im = c_re * dc10.im + c_im * dc10.re;
    c_re = -14964.5 * dc11.re - 1.8326227025840568E-12 * dc11.im;
    p_c51_idx_0_tmp_tmp = -14964.5 * dc11.im + 1.8326227025840568E-12 * dc11.re;
    f_re = c_re * dc12.re - p_c51_idx_0_tmp_tmp * dc12.im;
    p_c51_idx_0_tmp_tmp = c_re * dc12.im + p_c51_idx_0_tmp_tmp * dc12.re;
    c_re = f_re * dc13.re - p_c51_idx_0_tmp_tmp * dc13.im;
    p_c51_idx_0_tmp_tmp = f_re * dc13.im + p_c51_idx_0_tmp_tmp * dc13.re;
    f_re = -7482.25 * dc14.re - 9.1631135129202838E-13 * dc14.im;
    ib_c51_idx_0_tmp_tmp =
        -7482.25 * dc14.im + 9.1631135129202838E-13 * dc14.re;
    d_re = f_re * dc15.re - ib_c51_idx_0_tmp_tmp * dc15.im;
    ib_c51_idx_0_tmp_tmp = f_re * dc15.im + ib_c51_idx_0_tmp_tmp * dc15.re;
    f_re = d_re * dc16.re - ib_c51_idx_0_tmp_tmp * dc16.im;
    ib_c51_idx_0_tmp_tmp = d_re * dc16.im + ib_c51_idx_0_tmp_tmp * dc16.re;
    d_re = 0.766044443118978 *
           (f_re * b_c10_tmp_tmp.re - ib_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.im);
    ib_c51_idx_0_tmp_tmp =
        0.766044443118978 *
        (f_re * b_c10_tmp_tmp.im + ib_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.re);
    w1_idx_2 = 0.766044443118978 * k_c51_idx_0_tmp_tmp;
    v1_idx_0 = 0.766044443118978 * l_c51_idx_0_tmp_tmp;
    f_re = 0.766044443118978 *
           (-7482.25 * d_c10_tmp.re - 9.1631135129202838E-13 * d_c10_tmp.im);
    pb_c51_idx_0_tmp_tmp =
        0.766044443118978 *
        (-7482.25 * d_c10_tmp.im + 9.1631135129202838E-13 * d_c10_tmp.re);
    w1_idx_1 = 0.766044443118978 * (k_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.re -
                                    l_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.im);
    ccr0 = 0.766044443118978 * (k_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.im +
                                l_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.re);
    scp0 = 9.1631135129202838E-13 * c10_tmp.re;
    g_re = scp0 - 14964.5 * c10_tmp.im;
    ccp0 = 9.1631135129202838E-13 * c10_tmp.im;
    b_sc5_tmp_tmp = ccp0 + 14964.5 * c10_tmp.re;
    h_re = -14964.5 * c_c10_tmp.re - 1.8326227025840568E-12 * c_c10_tmp.im;
    x_c51_idx_0_tmp_tmp =
        -14964.5 * c_c10_tmp.im + 1.8326227025840568E-12 * c_c10_tmp.re;
    e_re = -7482.25 * c10_tmp.re - ccp0;
    d_c51_idx_0_tmp_tmp = -7482.25 * c10_tmp.im + scp0;
    jb_c51_idx_0_tmp_tmp =
        0.766044443118978 *
        (e_re * d_c10_tmp.re - d_c51_idx_0_tmp_tmp * d_c10_tmp.im);
    d_c51_idx_0_tmp_tmp =
        0.766044443118978 *
        (e_re * d_c10_tmp.im + d_c51_idx_0_tmp_tmp * d_c10_tmp.re);
    e_re = 9.1631135129202838E-13 * dc17.re - 14964.5 * dc17.im;
    b_c51_idx_0_tmp_tmp = 9.1631135129202838E-13 * dc17.im + 14964.5 * dc17.re;
    q_c51_idx_0_tmp_tmp = -7482.25 * dc18.re - 9.1631135129202838E-13 * dc18.im;
    y_c51_idx_0_tmp_tmp = -7482.25 * dc18.im + 9.1631135129202838E-13 * dc18.re;
    s_c51_idx_0_tmp_tmp =
        0.766044443118978 * (q_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.re -
                             y_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.im);
    y_c51_idx_0_tmp_tmp =
        0.766044443118978 * (q_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.im +
                             y_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.re);
    q_c51_idx_0_tmp_tmp = 9.1631135129202838E-13 * dc19.re - 14964.5 * dc19.im;
    t_c51_idx_0_tmp_tmp = 9.1631135129202838E-13 * dc19.im + 14964.5 * dc19.re;
    u_c51_idx_0_tmp_tmp =
        q_c51_idx_0_tmp_tmp * dc20.re - t_c51_idx_0_tmp_tmp * dc20.im;
    t_c51_idx_0_tmp_tmp =
        q_c51_idx_0_tmp_tmp * dc20.im + t_c51_idx_0_tmp_tmp * dc20.re;
    q_c51_idx_0_tmp_tmp = -14964.5 * dc21.re - 1.8326227025840568E-12 * dc21.im;
    v_c51_idx_0_tmp_tmp = -14964.5 * dc21.im + 1.8326227025840568E-12 * dc21.re;
    r_c51_idx_0_tmp_tmp =
        q_c51_idx_0_tmp_tmp * dc22.re - v_c51_idx_0_tmp_tmp * dc22.im;
    v_c51_idx_0_tmp_tmp =
        q_c51_idx_0_tmp_tmp * dc22.im + v_c51_idx_0_tmp_tmp * dc22.re;
    q_c51_idx_0_tmp_tmp = -7482.25 * dc23.re - 9.1631135129202838E-13 * dc23.im;
    w_c51_idx_0_tmp_tmp = -7482.25 * dc23.im + 9.1631135129202838E-13 * dc23.re;
    ob_c51_idx_0_tmp_tmp =
        q_c51_idx_0_tmp_tmp * dc24.re - w_c51_idx_0_tmp_tmp * dc24.im;
    w_c51_idx_0_tmp_tmp =
        q_c51_idx_0_tmp_tmp * dc24.im + w_c51_idx_0_tmp_tmp * dc24.re;
    q_c51_idx_0_tmp_tmp =
        0.766044443118978 * (ob_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.re -
                             w_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.im);
    w_c51_idx_0_tmp_tmp =
        0.766044443118978 * (ob_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.im +
                             w_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.re);
    ob_c51_idx_0_tmp_tmp = -(
        ((((((((((((((0.0 - (sc4 - m_c51_idx_0_tmp_tmp) * 0.766044443118978) +
                     (k_re * 0.0 - d_im)) -
                    4963.8290136870392) +
                   (l_re * b_c10_tmp.re - o_c51_idx_0_tmp_tmp * b_c10_tmp.im) *
                       0.766044443118978) +
                  (n_re * 0.0 - kb_c51_idx_0_tmp_tmp)) +
                 (m_re * b_c10_tmp_tmp.re -
                  lb_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.im) *
                     0.766044443118978) -
                (j_re * 0.0 - mb_c51_idx_0_tmp_tmp)) +
               (h_c51_idx_0_tmp_tmp * b_c10_tmp.re -
                nb_c51_idx_0_tmp_tmp * b_c10_tmp.im) *
                   0.766044443118978) -
              (e_c51_idx_0_tmp_tmp * d_c10_tmp.re -
               c51_idx_0_tmp_tmp_tmp * d_c10_tmp.im) *
                  0.766044443118978) -
             (i_re * 0.0 - f_c51_idx_0_tmp_tmp)) +
            (re * b_c10_tmp_tmp.re - im * b_c10_tmp_tmp.im) *
                0.766044443118978) -
           (g_c51_idx_0_tmp_tmp * 0.0 - b_im)) +
          (b_re * b_c10_tmp_tmp.re - c_im * b_c10_tmp_tmp.im) *
              0.766044443118978) +
         (c_re * b_c10_tmp_tmp.re - p_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.im) *
             0.766044443118978) +
        (d_re * 0.0 - ib_c51_idx_0_tmp_tmp));
    d_im = -(
        ((((((((((((((-5731.7360345269735 -
                      (cc4 + n_c51_idx_0_tmp_tmp) * 0.766044443118978) +
                     (k_re + d_im * 0.0)) +
                    2865.8680172634872) +
                   (l_re * b_c10_tmp.im + o_c51_idx_0_tmp_tmp * b_c10_tmp.re) *
                       0.766044443118978) +
                  (n_re + kb_c51_idx_0_tmp_tmp * 0.0)) +
                 (m_re * b_c10_tmp_tmp.im +
                  lb_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.re) *
                     0.766044443118978) -
                (j_re + mb_c51_idx_0_tmp_tmp * 0.0)) +
               (h_c51_idx_0_tmp_tmp * b_c10_tmp.im +
                nb_c51_idx_0_tmp_tmp * b_c10_tmp.re) *
                   0.766044443118978) -
              (e_c51_idx_0_tmp_tmp * d_c10_tmp.im +
               c51_idx_0_tmp_tmp_tmp * d_c10_tmp.re) *
                  0.766044443118978) -
             (i_re + f_c51_idx_0_tmp_tmp * 0.0)) +
            (re * b_c10_tmp_tmp.im + im * b_c10_tmp_tmp.re) *
                0.766044443118978) -
           (g_c51_idx_0_tmp_tmp + b_im * 0.0)) +
          (b_re * b_c10_tmp_tmp.im + c_im * b_c10_tmp_tmp.re) *
              0.766044443118978) +
         (c_re * b_c10_tmp_tmp.im + p_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.re) *
             0.766044443118978) +
        (d_re + ib_c51_idx_0_tmp_tmp * 0.0));
    scr0 =
        (((((((((((((sc4 * 0.766044443118978 + (w1_idx_2 * 0.0 - v1_idx_0)) -
                    4963.8290136870392) +
                   (9.1631135129202838E-13 * b_c10_tmp.re -
                    14964.5 * b_c10_tmp.im) *
                       0.766044443118978) +
                  (f_re * 0.0 - pb_c51_idx_0_tmp_tmp)) -
                 (sc4 * b_c10_tmp_tmp.re - cc4 * b_c10_tmp_tmp.im) *
                     0.766044443118978) -
                (w1_idx_1 * 0.0 - ccr0)) +
               (g_re * b_c10_tmp.re - b_sc5_tmp_tmp * b_c10_tmp.im) *
                   0.766044443118978) +
              (h_re * d_c10_tmp.re - x_c51_idx_0_tmp_tmp * d_c10_tmp.im) *
                  0.766044443118978) -
             (jb_c51_idx_0_tmp_tmp * 0.0 - d_c51_idx_0_tmp_tmp)) +
            (e_re * b_c10_tmp_tmp.re - b_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.im) *
                0.766044443118978) -
           (s_c51_idx_0_tmp_tmp * 0.0 - y_c51_idx_0_tmp_tmp)) +
          (u_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.re -
           t_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.im) *
              0.766044443118978) -
         (r_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.re -
          v_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.im) *
             0.766044443118978) +
        (q_c51_idx_0_tmp_tmp * 0.0 - w_c51_idx_0_tmp_tmp);
    v1_idx_0 =
        ((((((((((((((cc4 * 0.766044443118978 - 5731.7360345269735) +
                     (w1_idx_2 + v1_idx_0 * 0.0)) +
                    2865.8680172634872) +
                   (9.1631135129202838E-13 * b_c10_tmp.im +
                    14964.5 * b_c10_tmp.re) *
                       0.766044443118978) +
                  (f_re + pb_c51_idx_0_tmp_tmp * 0.0)) -
                 (sc4 * b_c10_tmp_tmp.im + cc4 * b_c10_tmp_tmp.re) *
                     0.766044443118978) -
                (w1_idx_1 + ccr0 * 0.0)) +
               (g_re * b_c10_tmp.im + b_sc5_tmp_tmp * b_c10_tmp.re) *
                   0.766044443118978) +
              (h_re * d_c10_tmp.im + x_c51_idx_0_tmp_tmp * d_c10_tmp.re) *
                  0.766044443118978) -
             (jb_c51_idx_0_tmp_tmp + d_c51_idx_0_tmp_tmp * 0.0)) +
            (e_re * b_c10_tmp_tmp.im + b_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.re) *
                0.766044443118978) -
           (s_c51_idx_0_tmp_tmp + y_c51_idx_0_tmp_tmp * 0.0)) +
          (u_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.im +
           t_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.re) *
              0.766044443118978) -
         (r_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.im +
          v_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.re) *
             0.766044443118978) +
        (q_c51_idx_0_tmp_tmp + w_c51_idx_0_tmp_tmp * 0.0);
    scp0 = b_a.re * b_a.re - b_a.im * b_a.im;
    ccp0 = b_a.re * b_a.im;
    ccp0 += ccp0;
    if (ccp0 == 0.0) {
      scp0 /= 4.0;
      ccp0 = 0.0;
    } else if (scp0 == 0.0) {
      scp0 = 0.0;
      ccp0 /= 4.0;
    } else {
      scp0 /= 4.0;
      ccp0 /= 4.0;
    }
    dc.re = (ob_c51_idx_0_tmp_tmp * scr0 - d_im * v1_idx_0) + scp0;
    dc.im = (ob_c51_idx_0_tmp_tmp * v1_idx_0 + d_im * scr0) + ccp0;
    g_c10_tmp = power(dc);
    i_c10_tmp.re = d_OBL_tmp_tmp * (0.86602540378443871 * h_c10_tmp.re);
    i_c10_tmp.im = d_OBL_tmp_tmp * (0.86602540378443871 * h_c10_tmp.im);
    j_c10_tmp.re = 0.49999999999999994 *
                   (c_OBL_tmp_tmp *
                    (b_OBL_tmp_tmp * (6.123233995736766E-17 * h_c10_tmp.re)));
    j_c10_tmp.im = 0.49999999999999994 *
                   (c_OBL_tmp_tmp *
                    (b_OBL_tmp_tmp * (6.123233995736766E-17 * h_c10_tmp.im)));
    w1_idx_2 = b_OBL_tmp_tmp * h_c10_tmp.re;
    v1_idx_0 = b_OBL_tmp_tmp * h_c10_tmp.im;
    h_c10_tmp.re = 0.49999999999999994 * (OBL_tmp_tmp * w1_idx_2);
    h_c10_tmp.im = 0.49999999999999994 * (OBL_tmp_tmp * v1_idx_0);
    i_c51_idx_0_tmp_tmp = 7482.25 * d_c10_tmp.re;
    j_c51_idx_0_tmp_tmp = 7482.25 * d_c10_tmp.im;
    dc.re = crs * 0.0;
    dc.im = crs;
    b_exp(&dc);
    dc1.re = cys * 0.0;
    dc1.im = cys;
    b_exp(&dc1);
    scp0 = -59857.999999999971 * c10_tmp_tmp.re -
           103677.09723945787 * c10_tmp_tmp.im;
    ccp0 = -59857.999999999971 * c10_tmp_tmp.im +
           103677.09723945787 * c10_tmp_tmp.re;
    k_re = scp0 * dc.re - ccp0 * dc.im;
    d_im = scp0 * dc.im + ccp0 * dc.re;
    l_re = k_re * dc1.re - d_im * dc1.im;
    d_im = k_re * dc1.im + d_im * dc1.re;
    b_c20_tmp.re = 0.64278760968653936 *
                   (l_re * c_c10_tmp_tmp.re - d_im * c_c10_tmp_tmp.im);
    b_c20_tmp.im = 0.64278760968653936 *
                   (l_re * c_c10_tmp_tmp.im + d_im * c_c10_tmp_tmp.re);
    dc.re = crs * 0.0;
    dc.im = crs;
    b_exp(&dc);
    dc1.re = cys * 0.0;
    dc1.im = cys;
    b_exp(&dc1);
    w1_idx_1 = -29928.999999999985 * c10_tmp_tmp.re -
               51838.548619728936 * c10_tmp_tmp.im;
    w1_idx_3 = -29928.999999999985 * c10_tmp_tmp.im +
               51838.548619728936 * c10_tmp_tmp.re;
    k_re = w1_idx_1 * dc.re - w1_idx_3 * dc.im;
    d_im = w1_idx_1 * dc.im + w1_idx_3 * dc.re;
    l_re = k_re * dc1.re - d_im * dc1.im;
    d_im = k_re * dc1.im + d_im * dc1.re;
    c_c20_tmp.re = 0.64278760968653936 *
                   (l_re * c_c10_tmp_tmp.re - d_im * c_c10_tmp_tmp.im);
    c_c20_tmp.im = 0.64278760968653936 *
                   (l_re * c_c10_tmp_tmp.im + d_im * c_c10_tmp_tmp.re);
    k_re = -29928.999999999975 * c10_tmp_tmp.re -
           51838.548619728914 * c10_tmp_tmp.im;
    d_im = -29928.999999999975 * c10_tmp_tmp.im +
           51838.548619728914 * c10_tmp_tmp.re;
    l_re = k_re * c_c10_tmp.re - d_im * c_c10_tmp.im;
    d_im = k_re * c_c10_tmp.im + d_im * c_c10_tmp.re;
    k_re = l_re * b_c10_tmp.re - d_im * b_c10_tmp.im;
    d_im = l_re * b_c10_tmp.im + d_im * b_c10_tmp.re;
    l_re = scp0 * c_c10_tmp.re - ccp0 * c_c10_tmp.im;
    o_c51_idx_0_tmp_tmp = scp0 * c_c10_tmp.im + ccp0 * c_c10_tmp.re;
    m_re = l_re * b_c10_tmp.re - o_c51_idx_0_tmp_tmp * b_c10_tmp.im;
    o_c51_idx_0_tmp_tmp =
        l_re * b_c10_tmp.im + o_c51_idx_0_tmp_tmp * b_c10_tmp.re;
    b_a.re =
        ((((k_re * c_c10_tmp_tmp.re - d_im * c_c10_tmp_tmp.im) -
           (m_re * c_c10_tmp_tmp.re - o_c51_idx_0_tmp_tmp * c_c10_tmp_tmp.im)) +
          0.86602540378443871 * b_c20_tmp.re * d_OBL_tmp_tmp) -
         c_OBL_tmp_tmp *
             (b_OBL_tmp_tmp * (-0.49999999999999978 * b_c20_tmp.re)) *
             0.49999999999999994) +
        0.86602540378443871 * (OBL_tmp_tmp * (b_OBL_tmp_tmp * b_c20_tmp.re)) *
            0.49999999999999994;
    b_a.im =
        ((((k_re * c_c10_tmp_tmp.im + d_im * c_c10_tmp_tmp.re) -
           (m_re * c_c10_tmp_tmp.im + o_c51_idx_0_tmp_tmp * c_c10_tmp_tmp.re)) +
          0.86602540378443871 * b_c20_tmp.im * d_OBL_tmp_tmp) -
         c_OBL_tmp_tmp *
             (b_OBL_tmp_tmp * (-0.49999999999999978 * b_c20_tmp.im)) *
             0.49999999999999994) +
        0.86602540378443871 * (OBL_tmp_tmp * (b_OBL_tmp_tmp * b_c20_tmp.im)) *
            0.49999999999999994;
    dc.re = crs * 0.0;
    dc.im = crs;
    b_exp(&dc);
    dc1.re = crs * 0.0;
    dc1.im = crs * 2.0;
    b_exp(&dc1);
    dc2.re = cys * 0.0;
    dc2.im = cys * 2.0;
    b_exp(&dc2);
    dc3.re = 0.0;
    dc3.im = 0.0;
    b_exp(&dc3);
    dc4.re = 0.0;
    dc4.im = 0.0;
    b_exp(&dc4);
    dc5.re = crs * 0.0;
    dc5.im = crs;
    b_exp(&dc5);
    dc6.re = 0.0;
    dc6.im = 0.0;
    b_exp(&dc6);
    dc7.re = crs * 0.0;
    dc7.im = crs * 2.0;
    b_exp(&dc7);
    dc8.re = 0.0;
    dc8.im = 0.0;
    b_exp(&dc8);
    dc9.re = cys * 0.0;
    dc9.im = cys;
    b_exp(&dc9);
    dc10.re = crs * 0.0;
    dc10.im = crs;
    b_exp(&dc10);
    dc11.re = cys * 0.0;
    dc11.im = cys * 2.0;
    b_exp(&dc11);
    dc12.re = crs * 0.0;
    dc12.im = crs * 2.0;
    b_exp(&dc12);
    dc13.re = cys * 0.0;
    dc13.im = cys * 2.0;
    b_exp(&dc13);
    dc14.re = 0.0;
    dc14.im = 0.0;
    b_exp(&dc14);
    dc15.re = crs * 0.0;
    dc15.im = crs * 2.0;
    b_exp(&dc15);
    dc16.re = cys * 0.0;
    dc16.im = cys;
    b_exp(&dc16);
    dc17.re = crs * 0.0;
    dc17.im = crs;
    b_exp(&dc17);
    dc18.re = crs * 0.0;
    dc18.im = crs * 2.0;
    b_exp(&dc18);
    dc19.re = cys * 0.0;
    dc19.im = cys;
    b_exp(&dc19);
    dc20.re = crs * 0.0;
    dc20.im = crs;
    b_exp(&dc20);
    dc21.re = cys * 0.0;
    dc21.im = cys * 2.0;
    b_exp(&dc21);
    dc22.re = crs * 0.0;
    dc22.im = crs * 2.0;
    b_exp(&dc22);
    dc23.re = cys * 0.0;
    dc23.im = cys * 2.0;
    b_exp(&dc23);
    dc24.re = crs * 0.0;
    dc24.im = crs * 2.0;
    b_exp(&dc24);
    dc25.re = cys * 0.0;
    dc25.im = cys;
    b_exp(&dc25);
    k_re = 0.766044443118978 * (i_c51_idx_0_tmp_tmp - 0.0 * d_c10_tmp.im);
    d_im = 0.766044443118978 * (j_c51_idx_0_tmp_tmp + 0.0 * d_c10_tmp.re);
    l_re = -7482.2500000000064 * c10_tmp_tmp.re -
           -12959.63715493223 * c10_tmp_tmp.im;
    o_c51_idx_0_tmp_tmp = -7482.2500000000064 * c10_tmp_tmp.im +
                          -12959.63715493223 * c10_tmp_tmp.re;
    m_re = -3741.1250000000032 * c10_tmp_tmp.re -
           -6479.8185774661151 * c10_tmp_tmp.im;
    kb_c51_idx_0_tmp_tmp = -3741.1250000000032 * c10_tmp_tmp.im +
                           -6479.8185774661151 * c10_tmp_tmp.re;
    n_re = 0.766044443118978 *
           (m_re * c10_tmp.re - kb_c51_idx_0_tmp_tmp * c10_tmp.im);
    kb_c51_idx_0_tmp_tmp =
        0.766044443118978 *
        (m_re * c10_tmp.im + kb_c51_idx_0_tmp_tmp * c10_tmp.re);
    m_re = -7482.2499999999964 * c10_tmp_tmp.re -
           12959.637154932234 * c10_tmp_tmp.im;
    lb_c51_idx_0_tmp_tmp = -7482.2499999999964 * c10_tmp_tmp.im +
                           12959.637154932234 * c10_tmp_tmp.re;
    i_re = 14964.5 * dc.re - 0.0 * dc.im;
    mb_c51_idx_0_tmp_tmp = 14964.5 * dc.im + 0.0 * dc.re;
    j_re = 7482.25 * dc1.re - 0.0 * dc1.im;
    nb_c51_idx_0_tmp_tmp = 7482.25 * dc1.im + 0.0 * dc1.re;
    h_c51_idx_0_tmp_tmp =
        0.766044443118978 *
        (j_re * d_c10_tmp.re - nb_c51_idx_0_tmp_tmp * d_c10_tmp.im);
    nb_c51_idx_0_tmp_tmp =
        0.766044443118978 *
        (j_re * d_c10_tmp.im + nb_c51_idx_0_tmp_tmp * d_c10_tmp.re);
    j_re = 7482.25 * dc2.re - 0.0 * dc2.im;
    c51_idx_0_tmp_tmp_tmp = 7482.25 * dc2.im + 0.0 * dc2.re;
    e_c51_idx_0_tmp_tmp =
        0.766044443118978 *
        (j_re * b_c10_tmp_tmp.re - c51_idx_0_tmp_tmp_tmp * b_c10_tmp_tmp.im);
    c51_idx_0_tmp_tmp_tmp =
        0.766044443118978 *
        (j_re * b_c10_tmp_tmp.im + c51_idx_0_tmp_tmp_tmp * b_c10_tmp_tmp.re);
    j_re = -7482.2499999999964 * dc3.re - 12959.637154932234 * dc3.im;
    f_c51_idx_0_tmp_tmp =
        -7482.2499999999964 * dc3.im + 12959.637154932234 * dc3.re;
    g_c51_idx_0_tmp_tmp = j_re * c10_tmp.re - f_c51_idx_0_tmp_tmp * c10_tmp.im;
    f_c51_idx_0_tmp_tmp = j_re * c10_tmp.im + f_c51_idx_0_tmp_tmp * c10_tmp.re;
    j_re = -7482.2500000000064 * dc4.re - -12959.63715493223 * dc4.im;
    im = -7482.2500000000064 * dc4.im + -12959.63715493223 * dc4.re;
    re = j_re * dc5.re - im * dc5.im;
    im = j_re * dc5.im + im * dc5.re;
    j_re = -3741.1250000000032 * dc6.re - -6479.8185774661151 * dc6.im;
    b_im = -3741.1250000000032 * dc6.im + -6479.8185774661151 * dc6.re;
    b_re = j_re * dc7.re - b_im * dc7.im;
    b_im = j_re * dc7.im + b_im * dc7.re;
    j_re =
        0.766044443118978 * (b_re * b_c10_tmp_tmp.re - b_im * b_c10_tmp_tmp.im);
    b_im =
        0.766044443118978 * (b_re * b_c10_tmp_tmp.im + b_im * b_c10_tmp_tmp.re);
    b_re = -7482.2499999999964 * dc8.re - 12959.637154932234 * dc8.im;
    c_im = -7482.2499999999964 * dc8.im + 12959.637154932234 * dc8.re;
    c_re = b_re * dc9.re - c_im * dc9.im;
    c_im = b_re * dc9.im + c_im * dc9.re;
    b_re = 14964.5 * dc10.re - 0.0 * dc10.im;
    p_c51_idx_0_tmp_tmp = 14964.5 * dc10.im + 0.0 * dc10.re;
    f_re = b_re * dc11.re - p_c51_idx_0_tmp_tmp * dc11.im;
    p_c51_idx_0_tmp_tmp = b_re * dc11.im + p_c51_idx_0_tmp_tmp * dc11.re;
    b_re = 7482.25 * dc12.re - 0.0 * dc12.im;
    ib_c51_idx_0_tmp_tmp = 7482.25 * dc12.im + 0.0 * dc12.re;
    d_re = b_re * dc13.re - ib_c51_idx_0_tmp_tmp * dc13.im;
    ib_c51_idx_0_tmp_tmp = b_re * dc13.im + ib_c51_idx_0_tmp_tmp * dc13.re;
    b_re = 0.766044443118978 *
           (d_re * b_c10_tmp_tmp.re - ib_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.im);
    ib_c51_idx_0_tmp_tmp =
        0.766044443118978 *
        (d_re * b_c10_tmp_tmp.im + ib_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.re);
    d_re = -7482.2499999999964 * dc14.re - 12959.637154932234 * dc14.im;
    pb_c51_idx_0_tmp_tmp =
        -7482.2499999999964 * dc14.im + 12959.637154932234 * dc14.re;
    g_re = d_re * dc15.re - pb_c51_idx_0_tmp_tmp * dc15.im;
    pb_c51_idx_0_tmp_tmp = d_re * dc15.im + pb_c51_idx_0_tmp_tmp * dc15.re;
    d_re = g_re * dc16.re - pb_c51_idx_0_tmp_tmp * dc16.im;
    pb_c51_idx_0_tmp_tmp = g_re * dc16.im + pb_c51_idx_0_tmp_tmp * dc16.re;
    ccp0 = 0.766044443118978 * i_c51_idx_0_tmp_tmp;
    cphi = 0.766044443118978 * j_c51_idx_0_tmp_tmp;
    g_re = 0.766044443118978 * (-3741.1250000000032 * c10_tmp.re -
                                -6479.8185774661151 * c10_tmp.im);
    b_sc5_tmp_tmp = 0.766044443118978 * (-3741.1250000000032 * c10_tmp.im +
                                         -6479.8185774661151 * c10_tmp.re);
    w1_idx_2 = 0.766044443118978 * (k_c51_idx_0_tmp_tmp * d_c10_tmp.re -
                                    l_c51_idx_0_tmp_tmp * d_c10_tmp.im);
    v1_idx_0 = 0.766044443118978 * (k_c51_idx_0_tmp_tmp * d_c10_tmp.im +
                                    l_c51_idx_0_tmp_tmp * d_c10_tmp.re);
    scp0 = 0.766044443118978 * (i_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.re -
                                j_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.im);
    ccr0 = 0.766044443118978 * (i_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.im +
                                j_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.re);
    h_re = -7482.2499999999964 * c10_tmp.re - 12959.637154932234 * c10_tmp.im;
    x_c51_idx_0_tmp_tmp =
        -7482.2499999999964 * c10_tmp.im + 12959.637154932234 * c10_tmp.re;
    e_re = -7482.2500000000064 * dc17.re - -12959.63715493223 * dc17.im;
    d_c51_idx_0_tmp_tmp =
        -7482.2500000000064 * dc17.im + -12959.63715493223 * dc17.re;
    jb_c51_idx_0_tmp_tmp =
        -3741.1250000000032 * dc18.re - -6479.8185774661151 * dc18.im;
    b_c51_idx_0_tmp_tmp =
        -3741.1250000000032 * dc18.im + -6479.8185774661151 * dc18.re;
    q_c51_idx_0_tmp_tmp =
        0.766044443118978 * (jb_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.re -
                             b_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.im);
    b_c51_idx_0_tmp_tmp =
        0.766044443118978 * (jb_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.im +
                             b_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.re);
    jb_c51_idx_0_tmp_tmp =
        -7482.2499999999964 * dc19.re - 12959.637154932234 * dc19.im;
    y_c51_idx_0_tmp_tmp =
        -7482.2499999999964 * dc19.im + 12959.637154932234 * dc19.re;
    s_c51_idx_0_tmp_tmp = 14964.5 * dc20.re;
    t_c51_idx_0_tmp_tmp = 14964.5 * dc20.im;
    u_c51_idx_0_tmp_tmp =
        s_c51_idx_0_tmp_tmp * dc21.re - t_c51_idx_0_tmp_tmp * dc21.im;
    t_c51_idx_0_tmp_tmp =
        s_c51_idx_0_tmp_tmp * dc21.im + t_c51_idx_0_tmp_tmp * dc21.re;
    s_c51_idx_0_tmp_tmp = 7482.25 * dc22.re;
    v_c51_idx_0_tmp_tmp = 7482.25 * dc22.im;
    r_c51_idx_0_tmp_tmp =
        s_c51_idx_0_tmp_tmp * dc23.re - v_c51_idx_0_tmp_tmp * dc23.im;
    v_c51_idx_0_tmp_tmp =
        s_c51_idx_0_tmp_tmp * dc23.im + v_c51_idx_0_tmp_tmp * dc23.re;
    s_c51_idx_0_tmp_tmp =
        0.766044443118978 * (r_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.re -
                             v_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.im);
    v_c51_idx_0_tmp_tmp =
        0.766044443118978 * (r_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.im +
                             v_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.re);
    r_c51_idx_0_tmp_tmp =
        -7482.2499999999964 * dc24.re - 12959.637154932234 * dc24.im;
    w_c51_idx_0_tmp_tmp =
        -7482.2499999999964 * dc24.im + 12959.637154932234 * dc24.re;
    ob_c51_idx_0_tmp_tmp =
        r_c51_idx_0_tmp_tmp * dc25.re - w_c51_idx_0_tmp_tmp * dc25.im;
    w_c51_idx_0_tmp_tmp =
        r_c51_idx_0_tmp_tmp * dc25.im + w_c51_idx_0_tmp_tmp * dc25.re;
    r_c51_idx_0_tmp_tmp = -(
        (((((((((((((((k_re * 0.0 - d_im) - 4963.8290136870382) -
                     (l_re * c_c10_tmp.re -
                      o_c51_idx_0_tmp_tmp * c_c10_tmp.im) *
                         0.766044443118978) +
                    (n_re * 0.0 - kb_c51_idx_0_tmp_tmp)) +
                   (m_re * b_c10_tmp.re - lb_c51_idx_0_tmp_tmp * b_c10_tmp.im) *
                       0.766044443118978) +
                  4963.8290136870419) -
                 (i_re * d_c10_tmp.re - mb_c51_idx_0_tmp_tmp * d_c10_tmp.im) *
                     0.766044443118978) -
                (h_c51_idx_0_tmp_tmp * 0.0 - nb_c51_idx_0_tmp_tmp)) -
               (e_c51_idx_0_tmp_tmp * 0.0 - c51_idx_0_tmp_tmp_tmp)) +
              (g_c51_idx_0_tmp_tmp * b_c10_tmp.re -
               f_c51_idx_0_tmp_tmp * b_c10_tmp.im) *
                  0.766044443118978) +
             (re * b_c10_tmp_tmp.re - im * b_c10_tmp_tmp.im) *
                 0.766044443118978) -
            (j_re * 0.0 - b_im)) +
           (c_re * b_c10_tmp_tmp.re - c_im * b_c10_tmp_tmp.im) *
               0.766044443118978) +
          (f_re * b_c10_tmp_tmp.re - p_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.im) *
              0.766044443118978) +
         (b_re * 0.0 - ib_c51_idx_0_tmp_tmp)) +
        (d_re * b_c10_tmp_tmp.re - pb_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.im) *
            0.766044443118978);
    d_im = -(
        (((((((((((((((k_re + d_im * 0.0) + 2865.868017263489) -
                     (l_re * c_c10_tmp.im +
                      o_c51_idx_0_tmp_tmp * c_c10_tmp.re) *
                         0.766044443118978) +
                    (n_re + kb_c51_idx_0_tmp_tmp * 0.0)) +
                   (m_re * b_c10_tmp.im + lb_c51_idx_0_tmp_tmp * b_c10_tmp.re) *
                       0.766044443118978) +
                  2865.8680172634845) -
                 (i_re * d_c10_tmp.im + mb_c51_idx_0_tmp_tmp * d_c10_tmp.re) *
                     0.766044443118978) -
                (h_c51_idx_0_tmp_tmp + nb_c51_idx_0_tmp_tmp * 0.0)) -
               (e_c51_idx_0_tmp_tmp + c51_idx_0_tmp_tmp_tmp * 0.0)) +
              (g_c51_idx_0_tmp_tmp * b_c10_tmp.im +
               f_c51_idx_0_tmp_tmp * b_c10_tmp.re) *
                  0.766044443118978) +
             (re * b_c10_tmp_tmp.im + im * b_c10_tmp_tmp.re) *
                 0.766044443118978) -
            (j_re + b_im * 0.0)) +
           (c_re * b_c10_tmp_tmp.im + c_im * b_c10_tmp_tmp.re) *
               0.766044443118978) +
          (f_re * b_c10_tmp_tmp.im + p_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.re) *
              0.766044443118978) +
         (b_re + ib_c51_idx_0_tmp_tmp * 0.0)) +
        (d_re * b_c10_tmp_tmp.im + pb_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.re) *
            0.766044443118978);
    scr0 = (((((((((((((((ccp0 * 0.0 - cphi) - 4963.8290136870382) +
                        (-7482.2500000000064 * c_c10_tmp.re -
                         -12959.63715493223 * c_c10_tmp.im) *
                            0.766044443118978) +
                       (g_re * 0.0 - b_sc5_tmp_tmp)) +
                      (-7482.2499999999964 * b_c10_tmp.re -
                       12959.637154932234 * b_c10_tmp.im) *
                          0.766044443118978) +
                     4963.8290136870419) +
                    (sc4 * d_c10_tmp.re - cc4 * d_c10_tmp.im) *
                        0.766044443118978) -
                   (w1_idx_2 * 0.0 - v1_idx_0)) -
                  (scp0 * 0.0 - ccr0)) +
                 (h_re * b_c10_tmp.re - x_c51_idx_0_tmp_tmp * b_c10_tmp.im) *
                     0.766044443118978) -
                (e_re * b_c10_tmp_tmp.re -
                 d_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.im) *
                    0.766044443118978) -
               (q_c51_idx_0_tmp_tmp * 0.0 - b_c51_idx_0_tmp_tmp)) +
              (jb_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.re -
               y_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.im) *
                  0.766044443118978) -
             (u_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.re -
              t_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.im) *
                 0.766044443118978) +
            (s_c51_idx_0_tmp_tmp * 0.0 - v_c51_idx_0_tmp_tmp)) +
           (ob_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.re -
            w_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.im) *
               0.766044443118978;
    cphi = (((((((((((((((ccp0 + cphi * 0.0) + 2865.868017263489) +
                        (-7482.2500000000064 * c_c10_tmp.im +
                         -12959.63715493223 * c_c10_tmp.re) *
                            0.766044443118978) +
                       (g_re + b_sc5_tmp_tmp * 0.0)) +
                      (-7482.2499999999964 * b_c10_tmp.im +
                       12959.637154932234 * b_c10_tmp.re) *
                          0.766044443118978) +
                     2865.8680172634845) +
                    (sc4 * d_c10_tmp.im + cc4 * d_c10_tmp.re) *
                        0.766044443118978) -
                   (w1_idx_2 + v1_idx_0 * 0.0)) -
                  (scp0 + ccr0 * 0.0)) +
                 (h_re * b_c10_tmp.im + x_c51_idx_0_tmp_tmp * b_c10_tmp.re) *
                     0.766044443118978) -
                (e_re * b_c10_tmp_tmp.im +
                 d_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.re) *
                    0.766044443118978) -
               (q_c51_idx_0_tmp_tmp + b_c51_idx_0_tmp_tmp * 0.0)) +
              (jb_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.im +
               y_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.re) *
                  0.766044443118978) -
             (u_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.im +
              t_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.re) *
                 0.766044443118978) +
            (s_c51_idx_0_tmp_tmp + v_c51_idx_0_tmp_tmp * 0.0)) +
           (ob_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.im +
            w_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.re) *
               0.766044443118978;
    scp0 = b_a.re * b_a.re - b_a.im * b_a.im;
    ccp0 = b_a.re * b_a.im;
    ccp0 += ccp0;
    if (ccp0 == 0.0) {
      scp0 /= 4.0;
      ccp0 = 0.0;
    } else if (scp0 == 0.0) {
      scp0 = 0.0;
      ccp0 /= 4.0;
    } else {
      scp0 /= 4.0;
      ccp0 /= 4.0;
    }
    dc.re = (r_c51_idx_0_tmp_tmp * scr0 - d_im * cphi) + scp0;
    dc.im = (r_c51_idx_0_tmp_tmp * cphi + d_im * scr0) + ccp0;
    b_c20_tmp = power(dc);
    b_a.re = d_OBL_tmp_tmp * (0.86602540378443871 * c_c20_tmp.re);
    b_a.im = d_OBL_tmp_tmp * (0.86602540378443871 * c_c20_tmp.im);
    e_c10_tmp.re = 0.49999999999999994 *
                   (c_OBL_tmp_tmp *
                    (b_OBL_tmp_tmp * (-0.49999999999999978 * c_c20_tmp.re)));
    e_c10_tmp.im = 0.49999999999999994 *
                   (c_OBL_tmp_tmp *
                    (b_OBL_tmp_tmp * (-0.49999999999999978 * c_c20_tmp.im)));
    ccp0 = OBL_tmp_tmp * (b_OBL_tmp_tmp * c_c20_tmp.re);
    cphi = OBL_tmp_tmp * (b_OBL_tmp_tmp * c_c20_tmp.im);
    c_c20_tmp.re = 0.49999999999999994 * (0.86602540378443871 * ccp0);
    c_c20_tmp.im = 0.49999999999999994 * (0.86602540378443871 * cphi);
    c30_tmp.re = 1.11968130125E+8 * c10_tmp.re;
    c30_tmp.im = 1.11968130125E+8 * c10_tmp.im;
    b_c30_tmp.re = crs * 0.0;
    b_c30_tmp.im = crs * 4.0;
    b_exp(&b_c30_tmp);
    c_c30_tmp.re = 5.59840650625E+7 * b_c30_tmp.re;
    c_c30_tmp.im = 5.59840650625E+7 * b_c30_tmp.im;
    c30_tmp_tmp.re = 0.0;
    c30_tmp_tmp.im = 2.0943951023931953;
    b_exp(&c30_tmp_tmp);
    d_c30_tmp.re = 2.2393626025E+8 * c10_tmp.re;
    d_c30_tmp.im = 2.2393626025E+8 * c10_tmp.im;
    b_c30_tmp_tmp.re = -0.0;
    b_c30_tmp_tmp.im = -2.0943951023931953;
    b_exp(&b_c30_tmp_tmp);
    c_c30_tmp_tmp.re = -0.0;
    c_c30_tmp_tmp.im = -1.0471975511965976;
    b_exp(&c_c30_tmp_tmp);
    e_c30_tmp.re = cys * 0.0;
    e_c30_tmp.im = cys * 4.0;
    b_exp(&e_c30_tmp);
    d_c30_tmp_tmp.re = -0.0;
    d_c30_tmp_tmp.im = -4.1887902047863905;
    b_exp(&d_c30_tmp_tmp);
    f_c30_tmp.re = cys * 0.0;
    f_c30_tmp.im = cys * 3.0;
    b_exp(&f_c30_tmp);
    e_c30_tmp_tmp.re = -0.0;
    e_c30_tmp_tmp.im = -3.1415926535897931;
    b_exp(&e_c30_tmp_tmp);
    g_c30_tmp.re = 5.59840650625E+7 * b_c10_tmp.re;
    g_c30_tmp.im = 5.59840650625E+7 * b_c10_tmp.im;
    h_c30_tmp.re = 3.35904390375E+8 * d_c10_tmp.re;
    h_c30_tmp.im = 3.35904390375E+8 * d_c10_tmp.im;
    i_c30_tmp.re = 5.59840650625E+7 * f_c30_tmp.re;
    i_c30_tmp.im = 5.59840650625E+7 * f_c30_tmp.im;
    j_c30_tmp.re = 5.59840650625E+7 * e_c30_tmp.re;
    j_c30_tmp.im = 5.59840650625E+7 * e_c30_tmp.im;
    k_c30_tmp.re = 1.11968130125E+8 * b_c30_tmp.re;
    k_c30_tmp.im = 1.11968130125E+8 * b_c30_tmp.im;
    l_c30_tmp.re = 7482.25 * c_c10_tmp.re;
    l_c30_tmp.im = 7482.25 * c_c10_tmp.im;
    m_c30_tmp.re = 7482.25 * b_c10_tmp.re;
    m_c30_tmp.im = 7482.25 * b_c10_tmp.im;
    /* 以上结果来源于代码"test4.m”,且将cp均替换为0,最近一次修改于2023.11.13，新机构确定a
     */
    dc.re = crs * 0.0;
    dc.im = crs;
    b_exp(&dc);
    dc1.re = crs * 0.0;
    dc1.im = crs * 2.0;
    b_exp(&dc1);
    dc2.re = cys * 0.0;
    dc2.im = cys;
    b_exp(&dc2);
    dc3.re = cys * 0.0;
    dc3.im = cys * 2.0;
    b_exp(&dc3);
    dc4.re = crs * 0.0;
    dc4.im = crs;
    b_exp(&dc4);
    dc5.re = crs * 0.0;
    dc5.im = crs * 2.0;
    b_exp(&dc5);
    dc6.re = crs * 0.0;
    dc6.im = crs * 2.0;
    b_exp(&dc6);
    dc7.re = cys * 0.0;
    dc7.im = cys;
    b_exp(&dc7);
    dc8.re = crs * 0.0;
    dc8.im = crs;
    b_exp(&dc8);
    dc9.re = cys * 0.0;
    dc9.im = cys * 2.0;
    b_exp(&dc9);
    dc10.re = crs * 0.0;
    dc10.im = crs * 2.0;
    b_exp(&dc10);
    dc11.re = cys * 0.0;
    dc11.im = cys * 2.0;
    b_exp(&dc11);
    dc12.re = cys * 0.0;
    dc12.im = cys;
    b_exp(&dc12);
    dc13.re = cys * 0.0;
    dc13.im = cys * 2.0;
    b_exp(&dc13);
    dc14.re = crs * 0.0;
    dc14.im = crs * 2.0;
    b_exp(&dc14);
    dc15.re = cys * 0.0;
    dc15.im = cys;
    b_exp(&dc15);
    dc16.re = crs * 0.0;
    dc16.im = crs;
    b_exp(&dc16);
    dc17.re = cys * 0.0;
    dc17.im = cys * 2.0;
    b_exp(&dc17);
    dc18.re = crs * 0.0;
    dc18.im = crs * 2.0;
    b_exp(&dc18);
    dc19.re = cys * 0.0;
    dc19.im = cys * 2.0;
    b_exp(&dc19);
    k_re = 1.832622702584056E-12 * c10_tmp_tmp.re -
           29928.999999999989 * c10_tmp_tmp.im;
    d_im = 1.832622702584056E-12 * c10_tmp_tmp.im +
           29928.999999999989 * c10_tmp_tmp.re;
    l_re = k_re * c_c10_tmp.re - d_im * c_c10_tmp.im;
    d_im = k_re * c_c10_tmp.im + d_im * c_c10_tmp.re;
    k_re = l_re * b_c10_tmp.re - d_im * b_c10_tmp.im;
    d_im = l_re * b_c10_tmp.im + d_im * b_c10_tmp.re;
    l_re = v3_idx_2 * c_c10_tmp.re - w1_idx_0 * c_c10_tmp.im;
    o_c51_idx_0_tmp_tmp = v3_idx_2 * c_c10_tmp.im + w1_idx_0 * c_c10_tmp.re;
    m_re = l_re * b_c10_tmp.re - o_c51_idx_0_tmp_tmp * b_c10_tmp.im;
    o_c51_idx_0_tmp_tmp =
        l_re * b_c10_tmp.im + o_c51_idx_0_tmp_tmp * b_c10_tmp.re;
    l_re = 14964.5 * dc.re;
    kb_c51_idx_0_tmp_tmp = 14964.5 * dc.im;
    n_re = 0.766044443118978 * (7482.25 * dc1.re);
    lb_c51_idx_0_tmp_tmp = 0.766044443118978 * (7482.25 * dc1.im);
    i_re = 0.766044443118978 *
           (-7482.25 * dc3.re - 9.1631135129202838E-13 * dc3.im);
    mb_c51_idx_0_tmp_tmp =
        0.766044443118978 *
        (-7482.25 * dc3.im + 9.1631135129202838E-13 * dc3.re);
    j_re = 14964.5 * dc4.re;
    nb_c51_idx_0_tmp_tmp = 14964.5 * dc4.im;
    h_c51_idx_0_tmp_tmp = 7482.25 * dc5.re;
    c51_idx_0_tmp_tmp_tmp = 7482.25 * dc5.im;
    e_c51_idx_0_tmp_tmp =
        0.766044443118978 * (h_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.re -
                             c51_idx_0_tmp_tmp_tmp * b_c10_tmp_tmp.im);
    c51_idx_0_tmp_tmp_tmp =
        0.766044443118978 * (h_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.im +
                             c51_idx_0_tmp_tmp_tmp * b_c10_tmp_tmp.re);
    h_c51_idx_0_tmp_tmp = 9.1631135129202838E-13 * dc6.re - 14964.5 * dc6.im;
    f_c51_idx_0_tmp_tmp = 9.1631135129202838E-13 * dc6.im + 14964.5 * dc6.re;
    g_c51_idx_0_tmp_tmp = -14964.5 * dc8.re - 1.8326227025840568E-12 * dc8.im;
    im = -14964.5 * dc8.im + 1.8326227025840568E-12 * dc8.re;
    re = -7482.25 * dc10.re - 9.1631135129202838E-13 * dc10.im;
    b_im = -7482.25 * dc10.im + 9.1631135129202838E-13 * dc10.re;
    b_re = 0.766044443118978 * (re * dc11.re - b_im * dc11.im);
    b_im = 0.766044443118978 * (re * dc11.im + b_im * dc11.re);
    re = 9.1631135129202838E-13 * dc12.re - 14964.5 * dc12.im;
    c_im = 9.1631135129202838E-13 * dc12.im + 14964.5 * dc12.re;
    c_re = -7482.25 * dc13.re - 9.1631135129202838E-13 * dc13.im;
    p_c51_idx_0_tmp_tmp = -7482.25 * dc13.im + 9.1631135129202838E-13 * dc13.re;
    f_re = 0.766044443118978 *
           (c_re * b_c10_tmp_tmp.re - p_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.im);
    p_c51_idx_0_tmp_tmp =
        0.766044443118978 *
        (c_re * b_c10_tmp_tmp.im + p_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.re);
    c_re = 9.1631135129202838E-13 * dc14.re - 14964.5 * dc14.im;
    ib_c51_idx_0_tmp_tmp = 9.1631135129202838E-13 * dc14.im + 14964.5 * dc14.re;
    d_re = c_re * dc15.re - ib_c51_idx_0_tmp_tmp * dc15.im;
    ib_c51_idx_0_tmp_tmp = c_re * dc15.im + ib_c51_idx_0_tmp_tmp * dc15.re;
    c_re = -14964.5 * dc16.re - 1.8326227025840568E-12 * dc16.im;
    pb_c51_idx_0_tmp_tmp =
        -14964.5 * dc16.im + 1.8326227025840568E-12 * dc16.re;
    g_re = c_re * dc17.re - pb_c51_idx_0_tmp_tmp * dc17.im;
    pb_c51_idx_0_tmp_tmp = c_re * dc17.im + pb_c51_idx_0_tmp_tmp * dc17.re;
    c_re = -7482.25 * dc18.re - 9.1631135129202838E-13 * dc18.im;
    b_sc5_tmp_tmp = -7482.25 * dc18.im + 9.1631135129202838E-13 * dc18.re;
    h_re = c_re * dc19.re - b_sc5_tmp_tmp * dc19.im;
    b_sc5_tmp_tmp = c_re * dc19.im + b_sc5_tmp_tmp * dc19.re;
    c_re = 0.766044443118978 *
           (h_re * b_c10_tmp_tmp.re - b_sc5_tmp_tmp * b_c10_tmp_tmp.im);
    b_sc5_tmp_tmp = 0.766044443118978 * (h_re * b_c10_tmp_tmp.im +
                                         b_sc5_tmp_tmp * b_c10_tmp_tmp.re);
    cc4 =
        ((((g_c10_tmp.re -
            (k_re * c_c10_tmp_tmp.re - d_im * c_c10_tmp_tmp.im)) +
           (m_re * c_c10_tmp_tmp.re - o_c51_idx_0_tmp_tmp * c_c10_tmp_tmp.im)) +
          i_c10_tmp.re) -
         j_c10_tmp.re) -
        h_c10_tmp.re;
    sc4 =
        ((((g_c10_tmp.im -
            (k_re * c_c10_tmp_tmp.im + d_im * c_c10_tmp_tmp.re)) +
           (m_re * c_c10_tmp_tmp.im + o_c51_idx_0_tmp_tmp * c_c10_tmp_tmp.re)) +
          i_c10_tmp.im) -
         j_c10_tmp.im) -
        h_c10_tmp.im;
    cphi =
        (((((((((((((l_re * 0.766044443118978 +
                     (n_re * 0.0 - lb_c51_idx_0_tmp_tmp)) -
                    4963.8290136870392) +
                   (9.1631135129202838E-13 * dc2.re - 14964.5 * dc2.im) *
                       0.766044443118978) +
                  (i_re * 0.0 - mb_c51_idx_0_tmp_tmp)) -
                 (j_re * b_c10_tmp_tmp.re -
                  nb_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.im) *
                     0.766044443118978) -
                (e_c51_idx_0_tmp_tmp * 0.0 - c51_idx_0_tmp_tmp_tmp)) +
               (h_c51_idx_0_tmp_tmp * dc7.re - f_c51_idx_0_tmp_tmp * dc7.im) *
                   0.766044443118978) +
              (g_c51_idx_0_tmp_tmp * dc9.re - im * dc9.im) *
                  0.766044443118978) -
             (b_re * 0.0 - b_im)) +
            (re * b_c10_tmp_tmp.re - c_im * b_c10_tmp_tmp.im) *
                0.766044443118978) -
           (f_re * 0.0 - p_c51_idx_0_tmp_tmp)) +
          (d_re * b_c10_tmp_tmp.re - ib_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.im) *
              0.766044443118978) -
         (g_re * b_c10_tmp_tmp.re - pb_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.im) *
             0.766044443118978) +
        (c_re * 0.0 - b_sc5_tmp_tmp);
    scr0 =
        ((((((((((((((kb_c51_idx_0_tmp_tmp * 0.766044443118978 -
                      5731.7360345269735) +
                     (n_re + lb_c51_idx_0_tmp_tmp * 0.0)) +
                    2865.8680172634872) +
                   (9.1631135129202838E-13 * dc2.im + 14964.5 * dc2.re) *
                       0.766044443118978) +
                  (i_re + mb_c51_idx_0_tmp_tmp * 0.0)) -
                 (j_re * b_c10_tmp_tmp.im +
                  nb_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.re) *
                     0.766044443118978) -
                (e_c51_idx_0_tmp_tmp + c51_idx_0_tmp_tmp_tmp * 0.0)) +
               (h_c51_idx_0_tmp_tmp * dc7.im + f_c51_idx_0_tmp_tmp * dc7.re) *
                   0.766044443118978) +
              (g_c51_idx_0_tmp_tmp * dc9.im + im * dc9.re) *
                  0.766044443118978) -
             (b_re + b_im * 0.0)) +
            (re * b_c10_tmp_tmp.im + c_im * b_c10_tmp_tmp.re) *
                0.766044443118978) -
           (f_re + p_c51_idx_0_tmp_tmp * 0.0)) +
          (d_re * b_c10_tmp_tmp.im + ib_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.re) *
              0.766044443118978) -
         (g_re * b_c10_tmp_tmp.im + pb_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.re) *
             0.766044443118978) +
        (c_re + b_sc5_tmp_tmp * 0.0);
    if (scr0 == 0.0) {
      if (sc4 == 0.0) {
        dc.re = cc4 / cphi;
        dc.im = 0.0;
      } else if (cc4 == 0.0) {
        dc.re = 0.0;
        dc.im = sc4 / cphi;
      } else {
        dc.re = cc4 / cphi;
        dc.im = sc4 / cphi;
      }
    } else if (cphi == 0.0) {
      if (cc4 == 0.0) {
        dc.re = sc4 / scr0;
        dc.im = 0.0;
      } else if (sc4 == 0.0) {
        dc.re = 0.0;
        dc.im = -(cc4 / scr0);
      } else {
        dc.re = sc4 / scr0;
        dc.im = -(cc4 / scr0);
      }
    } else {
      ccr0 = fabs(cphi);
      ccp0 = fabs(scr0);
      if (ccr0 > ccp0) {
        scp0 = scr0 / cphi;
        ccp0 = cphi + scp0 * scr0;
        dc.re = (cc4 + scp0 * sc4) / ccp0;
        dc.im = (sc4 - scp0 * cc4) / ccp0;
      } else if (ccp0 == ccr0) {
        if (cphi > 0.0) {
          scp0 = 0.5;
        } else {
          scp0 = -0.5;
        }
        if (scr0 > 0.0) {
          ccp0 = 0.5;
        } else {
          ccp0 = -0.5;
        }
        dc.re = (cc4 * scp0 + sc4 * ccp0) / ccr0;
        dc.im = (sc4 * scp0 - cc4 * ccp0) / ccr0;
      } else {
        scp0 = cphi / scr0;
        ccp0 = scr0 + scp0 * cphi;
        dc.re = (scp0 * cc4 + sc4) / ccp0;
        dc.im = (scp0 * sc4 - cc4) / ccp0;
      }
    }
    b_log(&dc);
    dc1.re = 0.0;
    dc1.im = 0.0;
    b_exp(&dc1);
    dc2.re = crs * 0.0;
    dc2.im = crs;
    b_exp(&dc2);
    dc3.re = cys * 0.0;
    dc3.im = cys;
    b_exp(&dc3);
    dc4.re = 0.0;
    dc4.im = 0.0;
    b_exp(&dc4);
    dc5.re = crs * 0.0;
    dc5.im = crs;
    b_exp(&dc5);
    dc6.re = cys * 0.0;
    dc6.im = cys;
    b_exp(&dc6);
    dc7.re = crs * 0.0;
    dc7.im = crs;
    b_exp(&dc7);
    dc8.re = crs * 0.0;
    dc8.im = crs * 2.0;
    b_exp(&dc8);
    dc9.re = cys * 0.0;
    dc9.im = cys;
    b_exp(&dc9);
    dc10.re = cys * 0.0;
    dc10.im = cys * 2.0;
    b_exp(&dc10);
    dc11.re = crs * 0.0;
    dc11.im = crs;
    b_exp(&dc11);
    dc12.re = crs * 0.0;
    dc12.im = crs * 2.0;
    b_exp(&dc12);
    dc13.re = crs * 0.0;
    dc13.im = crs * 2.0;
    b_exp(&dc13);
    dc14.re = cys * 0.0;
    dc14.im = cys;
    b_exp(&dc14);
    dc15.re = crs * 0.0;
    dc15.im = crs;
    b_exp(&dc15);
    dc16.re = cys * 0.0;
    dc16.im = cys * 2.0;
    b_exp(&dc16);
    dc17.re = crs * 0.0;
    dc17.im = crs * 2.0;
    b_exp(&dc17);
    dc18.re = cys * 0.0;
    dc18.im = cys * 2.0;
    b_exp(&dc18);
    dc19.re = cys * 0.0;
    dc19.im = cys;
    b_exp(&dc19);
    dc20.re = cys * 0.0;
    dc20.im = cys * 2.0;
    b_exp(&dc20);
    dc21.re = crs * 0.0;
    dc21.im = crs * 2.0;
    b_exp(&dc21);
    dc22.re = cys * 0.0;
    dc22.im = cys;
    b_exp(&dc22);
    dc23.re = crs * 0.0;
    dc23.im = crs;
    b_exp(&dc23);
    dc24.re = cys * 0.0;
    dc24.im = cys * 2.0;
    b_exp(&dc24);
    dc25.re = crs * 0.0;
    dc25.im = crs * 2.0;
    b_exp(&dc25);
    dc26.re = cys * 0.0;
    dc26.im = cys * 2.0;
    b_exp(&dc26);
    k_re = 1.832622702584056E-12 * dc1.re - 29928.999999999989 * dc1.im;
    d_im = 1.832622702584056E-12 * dc1.im + 29928.999999999989 * dc1.re;
    l_re = k_re * dc2.re - d_im * dc2.im;
    d_im = k_re * dc2.im + d_im * dc2.re;
    k_re = l_re * dc3.re - d_im * dc3.im;
    d_im = l_re * dc3.im + d_im * dc3.re;
    l_re = 3.6652454051681135E-12 * dc4.re - 59858.0 * dc4.im;
    o_c51_idx_0_tmp_tmp = 3.6652454051681135E-12 * dc4.im + 59858.0 * dc4.re;
    m_re = l_re * dc5.re - o_c51_idx_0_tmp_tmp * dc5.im;
    o_c51_idx_0_tmp_tmp = l_re * dc5.im + o_c51_idx_0_tmp_tmp * dc5.re;
    l_re = m_re * dc6.re - o_c51_idx_0_tmp_tmp * dc6.im;
    o_c51_idx_0_tmp_tmp = m_re * dc6.im + o_c51_idx_0_tmp_tmp * dc6.re;
    m_re = 0.766044443118978 * (7482.25 * dc8.re);
    kb_c51_idx_0_tmp_tmp = 0.766044443118978 * (7482.25 * dc8.im);
    n_re = 0.766044443118978 *
           (-7482.25 * dc10.re - 9.1631135129202838E-13 * dc10.im);
    lb_c51_idx_0_tmp_tmp =
        0.766044443118978 *
        (-7482.25 * dc10.im + 9.1631135129202838E-13 * dc10.re);
    i_re = 14964.5 * dc11.re;
    mb_c51_idx_0_tmp_tmp = 14964.5 * dc11.im;
    j_re = 7482.25 * dc12.re;
    nb_c51_idx_0_tmp_tmp = 7482.25 * dc12.im;
    h_c51_idx_0_tmp_tmp =
        0.766044443118978 *
        (j_re * b_c10_tmp_tmp.re - nb_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.im);
    nb_c51_idx_0_tmp_tmp =
        0.766044443118978 *
        (j_re * b_c10_tmp_tmp.im + nb_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.re);
    j_re = 9.1631135129202838E-13 * dc13.re - 14964.5 * dc13.im;
    c51_idx_0_tmp_tmp_tmp =
        9.1631135129202838E-13 * dc13.im + 14964.5 * dc13.re;
    e_c51_idx_0_tmp_tmp = -14964.5 * dc15.re - 1.8326227025840568E-12 * dc15.im;
    f_c51_idx_0_tmp_tmp = -14964.5 * dc15.im + 1.8326227025840568E-12 * dc15.re;
    g_c51_idx_0_tmp_tmp = -7482.25 * dc17.re - 9.1631135129202838E-13 * dc17.im;
    im = -7482.25 * dc17.im + 9.1631135129202838E-13 * dc17.re;
    re = 0.766044443118978 * (g_c51_idx_0_tmp_tmp * dc18.re - im * dc18.im);
    im = 0.766044443118978 * (g_c51_idx_0_tmp_tmp * dc18.im + im * dc18.re);
    g_c51_idx_0_tmp_tmp = 9.1631135129202838E-13 * dc19.re - 14964.5 * dc19.im;
    b_im = 9.1631135129202838E-13 * dc19.im + 14964.5 * dc19.re;
    b_re = -7482.25 * dc20.re - 9.1631135129202838E-13 * dc20.im;
    c_im = -7482.25 * dc20.im + 9.1631135129202838E-13 * dc20.re;
    c_re =
        0.766044443118978 * (b_re * b_c10_tmp_tmp.re - c_im * b_c10_tmp_tmp.im);
    c_im =
        0.766044443118978 * (b_re * b_c10_tmp_tmp.im + c_im * b_c10_tmp_tmp.re);
    b_re = 9.1631135129202838E-13 * dc21.re - 14964.5 * dc21.im;
    p_c51_idx_0_tmp_tmp = 9.1631135129202838E-13 * dc21.im + 14964.5 * dc21.re;
    f_re = b_re * dc22.re - p_c51_idx_0_tmp_tmp * dc22.im;
    p_c51_idx_0_tmp_tmp = b_re * dc22.im + p_c51_idx_0_tmp_tmp * dc22.re;
    b_re = -14964.5 * dc23.re - 1.8326227025840568E-12 * dc23.im;
    ib_c51_idx_0_tmp_tmp =
        -14964.5 * dc23.im + 1.8326227025840568E-12 * dc23.re;
    d_re = b_re * dc24.re - ib_c51_idx_0_tmp_tmp * dc24.im;
    ib_c51_idx_0_tmp_tmp = b_re * dc24.im + ib_c51_idx_0_tmp_tmp * dc24.re;
    b_re = -7482.25 * dc25.re - 9.1631135129202838E-13 * dc25.im;
    pb_c51_idx_0_tmp_tmp =
        -7482.25 * dc25.im + 9.1631135129202838E-13 * dc25.re;
    g_re = b_re * dc26.re - pb_c51_idx_0_tmp_tmp * dc26.im;
    pb_c51_idx_0_tmp_tmp = b_re * dc26.im + pb_c51_idx_0_tmp_tmp * dc26.re;
    b_re = 0.766044443118978 *
           (g_re * b_c10_tmp_tmp.re - pb_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.im);
    pb_c51_idx_0_tmp_tmp =
        0.766044443118978 *
        (g_re * b_c10_tmp_tmp.im + pb_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.re);
    cc4 = -(
        ((((g_c10_tmp.re +
            (k_re * c_c10_tmp_tmp.re - d_im * c_c10_tmp_tmp.im)) -
           (l_re * c_c10_tmp_tmp.re - o_c51_idx_0_tmp_tmp * c_c10_tmp_tmp.im)) -
          i_c10_tmp.re) +
         j_c10_tmp.re) +
        h_c10_tmp.re);
    sc4 = -(
        ((((g_c10_tmp.im +
            (k_re * c_c10_tmp_tmp.im + d_im * c_c10_tmp_tmp.re)) -
           (l_re * c_c10_tmp_tmp.im + o_c51_idx_0_tmp_tmp * c_c10_tmp_tmp.re)) -
          i_c10_tmp.im) +
         j_c10_tmp.im) +
        h_c10_tmp.im);
    cphi =
        (((((((((((((14964.5 * dc7.re * 0.766044443118978 +
                     (m_re * 0.0 - kb_c51_idx_0_tmp_tmp)) -
                    4963.8290136870392) +
                   (9.1631135129202838E-13 * dc9.re - 14964.5 * dc9.im) *
                       0.766044443118978) +
                  (n_re * 0.0 - lb_c51_idx_0_tmp_tmp)) -
                 (i_re * b_c10_tmp_tmp.re -
                  mb_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.im) *
                     0.766044443118978) -
                (h_c51_idx_0_tmp_tmp * 0.0 - nb_c51_idx_0_tmp_tmp)) +
               (j_re * dc14.re - c51_idx_0_tmp_tmp_tmp * dc14.im) *
                   0.766044443118978) +
              (e_c51_idx_0_tmp_tmp * dc16.re - f_c51_idx_0_tmp_tmp * dc16.im) *
                  0.766044443118978) -
             (re * 0.0 - im)) +
            (g_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.re - b_im * b_c10_tmp_tmp.im) *
                0.766044443118978) -
           (c_re * 0.0 - c_im)) +
          (f_re * b_c10_tmp_tmp.re - p_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.im) *
              0.766044443118978) -
         (d_re * b_c10_tmp_tmp.re - ib_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.im) *
             0.766044443118978) +
        (b_re * 0.0 - pb_c51_idx_0_tmp_tmp);
    scr0 =
        ((((((((((((((14964.5 * dc7.im * 0.766044443118978 -
                      5731.7360345269735) +
                     (m_re + kb_c51_idx_0_tmp_tmp * 0.0)) +
                    2865.8680172634872) +
                   (9.1631135129202838E-13 * dc9.im + 14964.5 * dc9.re) *
                       0.766044443118978) +
                  (n_re + lb_c51_idx_0_tmp_tmp * 0.0)) -
                 (i_re * b_c10_tmp_tmp.im +
                  mb_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.re) *
                     0.766044443118978) -
                (h_c51_idx_0_tmp_tmp + nb_c51_idx_0_tmp_tmp * 0.0)) +
               (j_re * dc14.im + c51_idx_0_tmp_tmp_tmp * dc14.re) *
                   0.766044443118978) +
              (e_c51_idx_0_tmp_tmp * dc16.im + f_c51_idx_0_tmp_tmp * dc16.re) *
                  0.766044443118978) -
             (re + im * 0.0)) +
            (g_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.im + b_im * b_c10_tmp_tmp.re) *
                0.766044443118978) -
           (c_re + c_im * 0.0)) +
          (f_re * b_c10_tmp_tmp.im + p_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.re) *
              0.766044443118978) -
         (d_re * b_c10_tmp_tmp.im + ib_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.re) *
             0.766044443118978) +
        (b_re + pb_c51_idx_0_tmp_tmp * 0.0);
    if (scr0 == 0.0) {
      if (sc4 == 0.0) {
        dc1.re = cc4 / cphi;
        dc1.im = 0.0;
      } else if (cc4 == 0.0) {
        dc1.re = 0.0;
        dc1.im = sc4 / cphi;
      } else {
        dc1.re = cc4 / cphi;
        dc1.im = sc4 / cphi;
      }
    } else if (cphi == 0.0) {
      if (cc4 == 0.0) {
        dc1.re = sc4 / scr0;
        dc1.im = 0.0;
      } else if (sc4 == 0.0) {
        dc1.re = 0.0;
        dc1.im = -(cc4 / scr0);
      } else {
        dc1.re = sc4 / scr0;
        dc1.im = -(cc4 / scr0);
      }
    } else {
      ccr0 = fabs(cphi);
      ccp0 = fabs(scr0);
      if (ccr0 > ccp0) {
        scp0 = scr0 / cphi;
        ccp0 = cphi + scp0 * scr0;
        dc1.re = (cc4 + scp0 * sc4) / ccp0;
        dc1.im = (sc4 - scp0 * cc4) / ccp0;
      } else if (ccp0 == ccr0) {
        if (cphi > 0.0) {
          scp0 = 0.5;
        } else {
          scp0 = -0.5;
        }
        if (scr0 > 0.0) {
          ccp0 = 0.5;
        } else {
          ccp0 = -0.5;
        }
        dc1.re = (cc4 * scp0 + sc4 * ccp0) / ccr0;
        dc1.im = (sc4 * scp0 - cc4 * ccp0) / ccr0;
      } else {
        scp0 = cphi / scr0;
        ccp0 = scr0 + scp0 * cphi;
        dc1.re = (scp0 * cc4 + sc4) / ccp0;
        dc1.im = (scp0 * sc4 - cc4) / ccp0;
      }
    }
    b_log(&dc1);
    k_re = dc.re * 0.0 - dc.im;
    l_re = dc1.re * 0.0 - dc1.im;
    dc.re = cys * 0.0;
    dc.im = cys * 2.0;
    b_exp(&dc);
    dc1.re = crs * 0.0;
    dc1.im = crs;
    b_exp(&dc1);
    dc2.re = crs * 0.0;
    dc2.im = crs * 2.0;
    b_exp(&dc2);
    dc3.re = cys * 0.0;
    dc3.im = cys;
    b_exp(&dc3);
    dc4.re = crs * 0.0;
    dc4.im = crs;
    b_exp(&dc4);
    dc5.re = cys * 0.0;
    dc5.im = cys * 2.0;
    b_exp(&dc5);
    dc6.re = crs * 0.0;
    dc6.im = crs * 2.0;
    b_exp(&dc6);
    dc7.re = cys * 0.0;
    dc7.im = cys * 2.0;
    b_exp(&dc7);
    dc8.re = cys * 0.0;
    dc8.im = cys * 2.0;
    b_exp(&dc8);
    dc9.re = crs * 0.0;
    dc9.im = crs * 2.0;
    b_exp(&dc9);
    dc10.re = cys * 0.0;
    dc10.im = cys;
    b_exp(&dc10);
    dc11.re = crs * 0.0;
    dc11.im = crs;
    b_exp(&dc11);
    dc12.re = crs * 0.0;
    dc12.im = crs * 2.0;
    b_exp(&dc12);
    dc13.re = cys * 0.0;
    dc13.im = cys;
    b_exp(&dc13);
    dc14.re = crs * 0.0;
    dc14.im = crs;
    b_exp(&dc14);
    dc15.re = cys * 0.0;
    dc15.im = cys * 2.0;
    b_exp(&dc15);
    dc16.re = crs * 0.0;
    dc16.im = crs * 2.0;
    b_exp(&dc16);
    dc17.re = cys * 0.0;
    dc17.im = cys * 2.0;
    b_exp(&dc17);
    dc18.re = crs * 0.0;
    dc18.im = crs * 2.0;
    b_exp(&dc18);
    dc19.re = cys * 0.0;
    dc19.im = cys;
    b_exp(&dc19);
    m_re = -14964.499999999987 * c10_tmp_tmp.re -
           25919.274309864457 * c10_tmp_tmp.im;
    d_im = -14964.499999999987 * c10_tmp_tmp.im +
           25919.274309864457 * c10_tmp_tmp.re;
    n_re = m_re * c_c10_tmp.re - d_im * c_c10_tmp.im;
    d_im = m_re * c_c10_tmp.im + d_im * c_c10_tmp.re;
    m_re = n_re * b_c10_tmp.re - d_im * b_c10_tmp.im;
    d_im = n_re * b_c10_tmp.im + d_im * b_c10_tmp.re;
    n_re = w1_idx_1 * c_c10_tmp.re - w1_idx_3 * c_c10_tmp.im;
    o_c51_idx_0_tmp_tmp = w1_idx_1 * c_c10_tmp.im + w1_idx_3 * c_c10_tmp.re;
    i_re = n_re * b_c10_tmp.re - o_c51_idx_0_tmp_tmp * b_c10_tmp.im;
    o_c51_idx_0_tmp_tmp =
        n_re * b_c10_tmp.im + o_c51_idx_0_tmp_tmp * b_c10_tmp.re;
    n_re = 0.766044443118978 * (7482.25 * dc.re);
    kb_c51_idx_0_tmp_tmp = 0.766044443118978 * (7482.25 * dc.im);
    j_re = 0.766044443118978 *
           (-3741.1250000000032 * dc2.re - -6479.8185774661151 * dc2.im);
    lb_c51_idx_0_tmp_tmp = 0.766044443118978 * (-3741.1250000000032 * dc2.im +
                                                -6479.8185774661151 * dc2.re);
    h_c51_idx_0_tmp_tmp = 14964.5 * dc4.re;
    mb_c51_idx_0_tmp_tmp = 14964.5 * dc4.im;
    e_c51_idx_0_tmp_tmp = 7482.25 * dc6.re;
    nb_c51_idx_0_tmp_tmp = 7482.25 * dc6.im;
    g_c51_idx_0_tmp_tmp = 0.766044443118978 * (e_c51_idx_0_tmp_tmp * dc7.re -
                                               nb_c51_idx_0_tmp_tmp * dc7.im);
    nb_c51_idx_0_tmp_tmp = 0.766044443118978 * (e_c51_idx_0_tmp_tmp * dc7.im +
                                                nb_c51_idx_0_tmp_tmp * dc7.re);
    e_c51_idx_0_tmp_tmp = 7482.25 * dc8.re;
    c51_idx_0_tmp_tmp_tmp = 7482.25 * dc8.im;
    re = 0.766044443118978 * (e_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.re -
                              c51_idx_0_tmp_tmp_tmp * b_c10_tmp_tmp.im);
    c51_idx_0_tmp_tmp_tmp =
        0.766044443118978 * (e_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.im +
                             c51_idx_0_tmp_tmp_tmp * b_c10_tmp_tmp.re);
    e_c51_idx_0_tmp_tmp =
        -7482.2499999999964 * dc9.re - 12959.637154932234 * dc9.im;
    f_c51_idx_0_tmp_tmp =
        -7482.2499999999964 * dc9.im + 12959.637154932234 * dc9.re;
    b_re = -7482.2500000000064 * dc11.re - -12959.63715493223 * dc11.im;
    im = -7482.2500000000064 * dc11.im + -12959.63715493223 * dc11.re;
    c_re = -3741.1250000000032 * dc12.re - -6479.8185774661151 * dc12.im;
    b_im = -3741.1250000000032 * dc12.im + -6479.8185774661151 * dc12.re;
    f_re =
        0.766044443118978 * (c_re * b_c10_tmp_tmp.re - b_im * b_c10_tmp_tmp.im);
    b_im =
        0.766044443118978 * (c_re * b_c10_tmp_tmp.im + b_im * b_c10_tmp_tmp.re);
    c_re = -7482.2499999999964 * dc13.re - 12959.637154932234 * dc13.im;
    c_im = -7482.2499999999964 * dc13.im + 12959.637154932234 * dc13.re;
    d_re = 14964.5 * dc14.re;
    p_c51_idx_0_tmp_tmp = 14964.5 * dc14.im;
    g_re = d_re * dc15.re - p_c51_idx_0_tmp_tmp * dc15.im;
    p_c51_idx_0_tmp_tmp = d_re * dc15.im + p_c51_idx_0_tmp_tmp * dc15.re;
    d_re = 7482.25 * dc16.re;
    ib_c51_idx_0_tmp_tmp = 7482.25 * dc16.im;
    h_re = d_re * dc17.re - ib_c51_idx_0_tmp_tmp * dc17.im;
    ib_c51_idx_0_tmp_tmp = d_re * dc17.im + ib_c51_idx_0_tmp_tmp * dc17.re;
    d_re = 0.766044443118978 *
           (h_re * b_c10_tmp_tmp.re - ib_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.im);
    ib_c51_idx_0_tmp_tmp =
        0.766044443118978 *
        (h_re * b_c10_tmp_tmp.im + ib_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.re);
    h_re = -7482.2499999999964 * dc18.re - 12959.637154932234 * dc18.im;
    pb_c51_idx_0_tmp_tmp =
        -7482.2499999999964 * dc18.im + 12959.637154932234 * dc18.re;
    e_re = h_re * dc19.re - pb_c51_idx_0_tmp_tmp * dc19.im;
    pb_c51_idx_0_tmp_tmp = h_re * dc19.im + pb_c51_idx_0_tmp_tmp * dc19.re;
    cc4 =
        ((((b_c20_tmp.re -
            (m_re * c_c10_tmp_tmp.re - d_im * c_c10_tmp_tmp.im)) +
           (i_re * c_c10_tmp_tmp.re - o_c51_idx_0_tmp_tmp * c_c10_tmp_tmp.im)) -
          b_a.re) +
         e_c10_tmp.re) -
        c_c20_tmp.re;
    sc4 =
        ((((b_c20_tmp.im -
            (m_re * c_c10_tmp_tmp.im + d_im * c_c10_tmp_tmp.re)) +
           (i_re * c_c10_tmp_tmp.im + o_c51_idx_0_tmp_tmp * c_c10_tmp_tmp.re)) -
          b_a.im) +
         e_c10_tmp.im) -
        c_c20_tmp.im;
    cphi =
        (((((((((((((((n_re * 0.0 - kb_c51_idx_0_tmp_tmp) -
                      4963.8290136870382) +
                     (-7482.2500000000064 * dc1.re -
                      -12959.63715493223 * dc1.im) *
                         0.766044443118978) +
                    (j_re * 0.0 - lb_c51_idx_0_tmp_tmp)) +
                   (-7482.2499999999964 * dc3.re -
                    12959.637154932234 * dc3.im) *
                       0.766044443118978) +
                  4963.8290136870419) +
                 (h_c51_idx_0_tmp_tmp * dc5.re -
                  mb_c51_idx_0_tmp_tmp * dc5.im) *
                     0.766044443118978) -
                (g_c51_idx_0_tmp_tmp * 0.0 - nb_c51_idx_0_tmp_tmp)) -
               (re * 0.0 - c51_idx_0_tmp_tmp_tmp)) +
              (e_c51_idx_0_tmp_tmp * dc10.re - f_c51_idx_0_tmp_tmp * dc10.im) *
                  0.766044443118978) -
             (b_re * b_c10_tmp_tmp.re - im * b_c10_tmp_tmp.im) *
                 0.766044443118978) -
            (f_re * 0.0 - b_im)) +
           (c_re * b_c10_tmp_tmp.re - c_im * b_c10_tmp_tmp.im) *
               0.766044443118978) -
          (g_re * b_c10_tmp_tmp.re - p_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.im) *
              0.766044443118978) +
         (d_re * 0.0 - ib_c51_idx_0_tmp_tmp)) +
        (e_re * b_c10_tmp_tmp.re - pb_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.im) *
            0.766044443118978;
    scr0 =
        (((((((((((((((n_re + kb_c51_idx_0_tmp_tmp * 0.0) + 2865.868017263489) +
                     (-7482.2500000000064 * dc1.im +
                      -12959.63715493223 * dc1.re) *
                         0.766044443118978) +
                    (j_re + lb_c51_idx_0_tmp_tmp * 0.0)) +
                   (-7482.2499999999964 * dc3.im +
                    12959.637154932234 * dc3.re) *
                       0.766044443118978) +
                  2865.8680172634845) +
                 (h_c51_idx_0_tmp_tmp * dc5.im +
                  mb_c51_idx_0_tmp_tmp * dc5.re) *
                     0.766044443118978) -
                (g_c51_idx_0_tmp_tmp + nb_c51_idx_0_tmp_tmp * 0.0)) -
               (re + c51_idx_0_tmp_tmp_tmp * 0.0)) +
              (e_c51_idx_0_tmp_tmp * dc10.im + f_c51_idx_0_tmp_tmp * dc10.re) *
                  0.766044443118978) -
             (b_re * b_c10_tmp_tmp.im + im * b_c10_tmp_tmp.re) *
                 0.766044443118978) -
            (f_re + b_im * 0.0)) +
           (c_re * b_c10_tmp_tmp.im + c_im * b_c10_tmp_tmp.re) *
               0.766044443118978) -
          (g_re * b_c10_tmp_tmp.im + p_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.re) *
              0.766044443118978) +
         (d_re + ib_c51_idx_0_tmp_tmp * 0.0)) +
        (e_re * b_c10_tmp_tmp.im + pb_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.re) *
            0.766044443118978;
    if (scr0 == 0.0) {
      if (sc4 == 0.0) {
        dc.re = cc4 / cphi;
        dc.im = 0.0;
      } else if (cc4 == 0.0) {
        dc.re = 0.0;
        dc.im = sc4 / cphi;
      } else {
        dc.re = cc4 / cphi;
        dc.im = sc4 / cphi;
      }
    } else if (cphi == 0.0) {
      if (cc4 == 0.0) {
        dc.re = sc4 / scr0;
        dc.im = 0.0;
      } else if (sc4 == 0.0) {
        dc.re = 0.0;
        dc.im = -(cc4 / scr0);
      } else {
        dc.re = sc4 / scr0;
        dc.im = -(cc4 / scr0);
      }
    } else {
      ccr0 = fabs(cphi);
      ccp0 = fabs(scr0);
      if (ccr0 > ccp0) {
        scp0 = scr0 / cphi;
        ccp0 = cphi + scp0 * scr0;
        dc.re = (cc4 + scp0 * sc4) / ccp0;
        dc.im = (sc4 - scp0 * cc4) / ccp0;
      } else if (ccp0 == ccr0) {
        if (cphi > 0.0) {
          scp0 = 0.5;
        } else {
          scp0 = -0.5;
        }
        if (scr0 > 0.0) {
          ccp0 = 0.5;
        } else {
          ccp0 = -0.5;
        }
        dc.re = (cc4 * scp0 + sc4 * ccp0) / ccr0;
        dc.im = (sc4 * scp0 - cc4 * ccp0) / ccr0;
      } else {
        scp0 = cphi / scr0;
        ccp0 = scr0 + scp0 * cphi;
        dc.re = (scp0 * cc4 + sc4) / ccp0;
        dc.im = (scp0 * sc4 - cc4) / ccp0;
      }
    }
    b_log(&dc);
    dc1.re = 0.0;
    dc1.im = 0.0;
    b_exp(&dc1);
    dc2.re = crs * 0.0;
    dc2.im = crs;
    b_exp(&dc2);
    dc3.re = cys * 0.0;
    dc3.im = cys;
    b_exp(&dc3);
    dc4.re = 0.0;
    dc4.im = 0.0;
    b_exp(&dc4);
    dc5.re = crs * 0.0;
    dc5.im = crs;
    b_exp(&dc5);
    dc6.re = cys * 0.0;
    dc6.im = cys;
    b_exp(&dc6);
    dc7.re = cys * 0.0;
    dc7.im = cys * 2.0;
    b_exp(&dc7);
    dc8.re = crs * 0.0;
    dc8.im = crs;
    b_exp(&dc8);
    dc9.re = crs * 0.0;
    dc9.im = crs * 2.0;
    b_exp(&dc9);
    dc10.re = cys * 0.0;
    dc10.im = cys;
    b_exp(&dc10);
    dc11.re = crs * 0.0;
    dc11.im = crs;
    b_exp(&dc11);
    dc12.re = cys * 0.0;
    dc12.im = cys * 2.0;
    b_exp(&dc12);
    dc13.re = crs * 0.0;
    dc13.im = crs * 2.0;
    b_exp(&dc13);
    dc14.re = cys * 0.0;
    dc14.im = cys * 2.0;
    b_exp(&dc14);
    dc15.re = cys * 0.0;
    dc15.im = cys * 2.0;
    b_exp(&dc15);
    dc16.re = crs * 0.0;
    dc16.im = crs * 2.0;
    b_exp(&dc16);
    dc17.re = cys * 0.0;
    dc17.im = cys;
    b_exp(&dc17);
    dc18.re = crs * 0.0;
    dc18.im = crs;
    b_exp(&dc18);
    dc19.re = crs * 0.0;
    dc19.im = crs * 2.0;
    b_exp(&dc19);
    dc20.re = cys * 0.0;
    dc20.im = cys;
    b_exp(&dc20);
    dc21.re = crs * 0.0;
    dc21.im = crs;
    b_exp(&dc21);
    dc22.re = cys * 0.0;
    dc22.im = cys * 2.0;
    b_exp(&dc22);
    dc23.re = crs * 0.0;
    dc23.im = crs * 2.0;
    b_exp(&dc23);
    dc24.re = cys * 0.0;
    dc24.im = cys * 2.0;
    b_exp(&dc24);
    dc25.re = crs * 0.0;
    dc25.im = crs * 2.0;
    b_exp(&dc25);
    dc26.re = cys * 0.0;
    dc26.im = cys;
    b_exp(&dc26);
    m_re = -14964.499999999987 * dc1.re - 25919.274309864457 * dc1.im;
    d_im = -14964.499999999987 * dc1.im + 25919.274309864457 * dc1.re;
    n_re = m_re * dc2.re - d_im * dc2.im;
    d_im = m_re * dc2.im + d_im * dc2.re;
    m_re = n_re * dc3.re - d_im * dc3.im;
    d_im = n_re * dc3.im + d_im * dc3.re;
    n_re = -29928.999999999985 * dc4.re - 51838.548619728936 * dc4.im;
    o_c51_idx_0_tmp_tmp =
        -29928.999999999985 * dc4.im + 51838.548619728936 * dc4.re;
    i_re = n_re * dc5.re - o_c51_idx_0_tmp_tmp * dc5.im;
    o_c51_idx_0_tmp_tmp = n_re * dc5.im + o_c51_idx_0_tmp_tmp * dc5.re;
    n_re = i_re * dc6.re - o_c51_idx_0_tmp_tmp * dc6.im;
    o_c51_idx_0_tmp_tmp = i_re * dc6.im + o_c51_idx_0_tmp_tmp * dc6.re;
    i_re = 0.766044443118978 * (7482.25 * dc7.re);
    kb_c51_idx_0_tmp_tmp = 0.766044443118978 * (7482.25 * dc7.im);
    j_re = 0.766044443118978 *
           (-3741.1250000000032 * dc9.re - -6479.8185774661151 * dc9.im);
    lb_c51_idx_0_tmp_tmp = 0.766044443118978 * (-3741.1250000000032 * dc9.im +
                                                -6479.8185774661151 * dc9.re);
    h_c51_idx_0_tmp_tmp = 14964.5 * dc11.re;
    mb_c51_idx_0_tmp_tmp = 14964.5 * dc11.im;
    e_c51_idx_0_tmp_tmp = 7482.25 * dc13.re;
    nb_c51_idx_0_tmp_tmp = 7482.25 * dc13.im;
    g_c51_idx_0_tmp_tmp = 0.766044443118978 * (e_c51_idx_0_tmp_tmp * dc14.re -
                                               nb_c51_idx_0_tmp_tmp * dc14.im);
    nb_c51_idx_0_tmp_tmp = 0.766044443118978 * (e_c51_idx_0_tmp_tmp * dc14.im +
                                                nb_c51_idx_0_tmp_tmp * dc14.re);
    e_c51_idx_0_tmp_tmp = 7482.25 * dc15.re;
    c51_idx_0_tmp_tmp_tmp = 7482.25 * dc15.im;
    re = 0.766044443118978 * (e_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.re -
                              c51_idx_0_tmp_tmp_tmp * b_c10_tmp_tmp.im);
    c51_idx_0_tmp_tmp_tmp =
        0.766044443118978 * (e_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.im +
                             c51_idx_0_tmp_tmp_tmp * b_c10_tmp_tmp.re);
    e_c51_idx_0_tmp_tmp =
        -7482.2499999999964 * dc16.re - 12959.637154932234 * dc16.im;
    f_c51_idx_0_tmp_tmp =
        -7482.2499999999964 * dc16.im + 12959.637154932234 * dc16.re;
    b_re = -7482.2500000000064 * dc18.re - -12959.63715493223 * dc18.im;
    im = -7482.2500000000064 * dc18.im + -12959.63715493223 * dc18.re;
    c_re = -3741.1250000000032 * dc19.re - -6479.8185774661151 * dc19.im;
    b_im = -3741.1250000000032 * dc19.im + -6479.8185774661151 * dc19.re;
    f_re =
        0.766044443118978 * (c_re * b_c10_tmp_tmp.re - b_im * b_c10_tmp_tmp.im);
    b_im =
        0.766044443118978 * (c_re * b_c10_tmp_tmp.im + b_im * b_c10_tmp_tmp.re);
    c_re = -7482.2499999999964 * dc20.re - 12959.637154932234 * dc20.im;
    c_im = -7482.2499999999964 * dc20.im + 12959.637154932234 * dc20.re;
    d_re = 14964.5 * dc21.re;
    p_c51_idx_0_tmp_tmp = 14964.5 * dc21.im;
    g_re = d_re * dc22.re - p_c51_idx_0_tmp_tmp * dc22.im;
    p_c51_idx_0_tmp_tmp = d_re * dc22.im + p_c51_idx_0_tmp_tmp * dc22.re;
    d_re = 7482.25 * dc23.re;
    ib_c51_idx_0_tmp_tmp = 7482.25 * dc23.im;
    h_re = d_re * dc24.re - ib_c51_idx_0_tmp_tmp * dc24.im;
    ib_c51_idx_0_tmp_tmp = d_re * dc24.im + ib_c51_idx_0_tmp_tmp * dc24.re;
    d_re = 0.766044443118978 *
           (h_re * b_c10_tmp_tmp.re - ib_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.im);
    ib_c51_idx_0_tmp_tmp =
        0.766044443118978 *
        (h_re * b_c10_tmp_tmp.im + ib_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.re);
    h_re = -7482.2499999999964 * dc25.re - 12959.637154932234 * dc25.im;
    pb_c51_idx_0_tmp_tmp =
        -7482.2499999999964 * dc25.im + 12959.637154932234 * dc25.re;
    e_re = h_re * dc26.re - pb_c51_idx_0_tmp_tmp * dc26.im;
    pb_c51_idx_0_tmp_tmp = h_re * dc26.im + pb_c51_idx_0_tmp_tmp * dc26.re;
    cc4 = -(
        ((((b_c20_tmp.re +
            (m_re * c_c10_tmp_tmp.re - d_im * c_c10_tmp_tmp.im)) -
           (n_re * c_c10_tmp_tmp.re - o_c51_idx_0_tmp_tmp * c_c10_tmp_tmp.im)) +
          b_a.re) -
         e_c10_tmp.re) +
        c_c20_tmp.re);
    sc4 = -(
        ((((b_c20_tmp.im +
            (m_re * c_c10_tmp_tmp.im + d_im * c_c10_tmp_tmp.re)) -
           (n_re * c_c10_tmp_tmp.im + o_c51_idx_0_tmp_tmp * c_c10_tmp_tmp.re)) +
          b_a.im) -
         e_c10_tmp.im) +
        c_c20_tmp.im);
    cphi =
        (((((((((((((((i_re * 0.0 - kb_c51_idx_0_tmp_tmp) -
                      4963.8290136870382) +
                     (-7482.2500000000064 * dc8.re -
                      -12959.63715493223 * dc8.im) *
                         0.766044443118978) +
                    (j_re * 0.0 - lb_c51_idx_0_tmp_tmp)) +
                   (-7482.2499999999964 * dc10.re -
                    12959.637154932234 * dc10.im) *
                       0.766044443118978) +
                  4963.8290136870419) +
                 (h_c51_idx_0_tmp_tmp * dc12.re -
                  mb_c51_idx_0_tmp_tmp * dc12.im) *
                     0.766044443118978) -
                (g_c51_idx_0_tmp_tmp * 0.0 - nb_c51_idx_0_tmp_tmp)) -
               (re * 0.0 - c51_idx_0_tmp_tmp_tmp)) +
              (e_c51_idx_0_tmp_tmp * dc17.re - f_c51_idx_0_tmp_tmp * dc17.im) *
                  0.766044443118978) -
             (b_re * b_c10_tmp_tmp.re - im * b_c10_tmp_tmp.im) *
                 0.766044443118978) -
            (f_re * 0.0 - b_im)) +
           (c_re * b_c10_tmp_tmp.re - c_im * b_c10_tmp_tmp.im) *
               0.766044443118978) -
          (g_re * b_c10_tmp_tmp.re - p_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.im) *
              0.766044443118978) +
         (d_re * 0.0 - ib_c51_idx_0_tmp_tmp)) +
        (e_re * b_c10_tmp_tmp.re - pb_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.im) *
            0.766044443118978;
    scr0 =
        (((((((((((((((i_re + kb_c51_idx_0_tmp_tmp * 0.0) + 2865.868017263489) +
                     (-7482.2500000000064 * dc8.im +
                      -12959.63715493223 * dc8.re) *
                         0.766044443118978) +
                    (j_re + lb_c51_idx_0_tmp_tmp * 0.0)) +
                   (-7482.2499999999964 * dc10.im +
                    12959.637154932234 * dc10.re) *
                       0.766044443118978) +
                  2865.8680172634845) +
                 (h_c51_idx_0_tmp_tmp * dc12.im +
                  mb_c51_idx_0_tmp_tmp * dc12.re) *
                     0.766044443118978) -
                (g_c51_idx_0_tmp_tmp + nb_c51_idx_0_tmp_tmp * 0.0)) -
               (re + c51_idx_0_tmp_tmp_tmp * 0.0)) +
              (e_c51_idx_0_tmp_tmp * dc17.im + f_c51_idx_0_tmp_tmp * dc17.re) *
                  0.766044443118978) -
             (b_re * b_c10_tmp_tmp.im + im * b_c10_tmp_tmp.re) *
                 0.766044443118978) -
            (f_re + b_im * 0.0)) +
           (c_re * b_c10_tmp_tmp.im + c_im * b_c10_tmp_tmp.re) *
               0.766044443118978) -
          (g_re * b_c10_tmp_tmp.im + p_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.re) *
              0.766044443118978) +
         (d_re + ib_c51_idx_0_tmp_tmp * 0.0)) +
        (e_re * b_c10_tmp_tmp.im + pb_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.re) *
            0.766044443118978;
    if (scr0 == 0.0) {
      if (sc4 == 0.0) {
        dc1.re = cc4 / cphi;
        dc1.im = 0.0;
      } else if (cc4 == 0.0) {
        dc1.re = 0.0;
        dc1.im = sc4 / cphi;
      } else {
        dc1.re = cc4 / cphi;
        dc1.im = sc4 / cphi;
      }
    } else if (cphi == 0.0) {
      if (cc4 == 0.0) {
        dc1.re = sc4 / scr0;
        dc1.im = 0.0;
      } else if (sc4 == 0.0) {
        dc1.re = 0.0;
        dc1.im = -(cc4 / scr0);
      } else {
        dc1.re = sc4 / scr0;
        dc1.im = -(cc4 / scr0);
      }
    } else {
      ccr0 = fabs(cphi);
      ccp0 = fabs(scr0);
      if (ccr0 > ccp0) {
        scp0 = scr0 / cphi;
        ccp0 = cphi + scp0 * scr0;
        dc1.re = (cc4 + scp0 * sc4) / ccp0;
        dc1.im = (sc4 - scp0 * cc4) / ccp0;
      } else if (ccp0 == ccr0) {
        if (cphi > 0.0) {
          scp0 = 0.5;
        } else {
          scp0 = -0.5;
        }
        if (scr0 > 0.0) {
          ccp0 = 0.5;
        } else {
          ccp0 = -0.5;
        }
        dc1.re = (cc4 * scp0 + sc4 * ccp0) / ccr0;
        dc1.im = (sc4 * scp0 - cc4 * ccp0) / ccr0;
      } else {
        scp0 = cphi / scr0;
        ccp0 = scr0 + scp0 * cphi;
        dc1.re = (scp0 * cc4 + sc4) / ccp0;
        dc1.im = (scp0 * sc4 - cc4) / ccp0;
      }
    }
    b_log(&dc1);
    m_re = dc.re * 0.0 - dc.im;
    n_re = dc1.re * 0.0 - dc1.im;
    dc.re = crs * 0.0;
    dc.im = crs * 2.0;
    b_exp(&dc);
    dc1.re = cys * 0.0;
    dc1.im = cys * 2.0;
    b_exp(&dc1);
    dc2.re = crs * 0.0;
    dc2.im = crs * 4.0;
    b_exp(&dc2);
    dc3.re = cys * 0.0;
    dc3.im = cys;
    b_exp(&dc3);
    dc4.re = crs * 0.0;
    dc4.im = crs * 4.0;
    b_exp(&dc4);
    dc5.re = cys * 0.0;
    dc5.im = cys * 2.0;
    b_exp(&dc5);
    dc6.re = crs * 0.0;
    dc6.im = crs * 2.0;
    b_exp(&dc6);
    dc7.re = cys * 0.0;
    dc7.im = cys * 4.0;
    b_exp(&dc7);
    dc8.re = crs * 0.0;
    dc8.im = crs * 4.0;
    b_exp(&dc8);
    dc9.re = cys * 0.0;
    dc9.im = cys * 3.0;
    b_exp(&dc9);
    dc10.re = crs * 0.0;
    dc10.im = crs * 4.0;
    b_exp(&dc10);
    dc11.re = cys * 0.0;
    dc11.im = cys * 4.0;
    b_exp(&dc11);
    dc12.re = crs * 0.0;
    dc12.im = crs * 2.0;
    b_exp(&dc12);
    dc13.re = crs * 0.0;
    dc13.im = crs * 2.0;
    b_exp(&dc13);
    dc14.re = cys * 0.0;
    dc14.im = cys * 2.0;
    b_exp(&dc14);
    dc15.re = cys * 0.0;
    dc15.im = cys * 2.0;
    b_exp(&dc15);
    dc16.re = crs * 0.0;
    dc16.im = crs * 2.0;
    b_exp(&dc16);
    dc17.re = cys * 0.0;
    dc17.im = cys;
    b_exp(&dc17);
    dc18.re = crs * 0.0;
    dc18.im = crs;
    b_exp(&dc18);
    dc19.re = cys * 0.0;
    dc19.im = cys * 2.0;
    b_exp(&dc19);
    dc20.re = crs * 0.0;
    dc20.im = crs * 2.0;
    b_exp(&dc20);
    dc21.re = cys * 0.0;
    dc21.im = cys * 2.0;
    b_exp(&dc21);
    c_c51_idx_0_tmp_tmp =
        g_c30_tmp.re * c_c30_tmp_tmp.re - g_c30_tmp.im * c_c30_tmp_tmp.im;
    d_c51_idx_0_tmp_tmp =
        g_c30_tmp.re * c_c30_tmp_tmp.im + g_c30_tmp.im * c_c30_tmp_tmp.re;
    b_c51_idx_0_tmp_tmp =
        i_c30_tmp.re * e_c30_tmp_tmp.re - i_c30_tmp.im * e_c30_tmp_tmp.im;
    y_c51_idx_0_tmp_tmp =
        i_c30_tmp.re * e_c30_tmp_tmp.im + i_c30_tmp.im * e_c30_tmp_tmp.re;
    v3_idx_0 = d_c30_tmp.re * d_c10_tmp.re - d_c30_tmp.im * d_c10_tmp.im;
    fb_c51_idx_0_tmp_tmp =
        d_c30_tmp.re * d_c10_tmp.im + d_c30_tmp.im * d_c10_tmp.re;
    gb_c51_idx_0_tmp_tmp =
        c_c30_tmp.re * b_c10_tmp.re - c_c30_tmp.im * b_c10_tmp.im;
    hb_c51_idx_0_tmp_tmp =
        c_c30_tmp.re * b_c10_tmp.im + c_c30_tmp.im * b_c10_tmp.re;
    c51_idx_0_tmp_tmp = gb_c51_idx_0_tmp_tmp * c_c30_tmp_tmp.re -
                        hb_c51_idx_0_tmp_tmp * c_c30_tmp_tmp.im;
    hb_c51_idx_0_tmp_tmp = gb_c51_idx_0_tmp_tmp * c_c30_tmp_tmp.im +
                           hb_c51_idx_0_tmp_tmp * c_c30_tmp_tmp.re;
    i_re = 3.35904390375E+8 * b_c30_tmp.re;
    d_im = 3.35904390375E+8 * b_c30_tmp.im;
    j_re = i_re * d_c10_tmp.re - d_im * d_c10_tmp.im;
    d_im = i_re * d_c10_tmp.im + d_im * d_c10_tmp.re;
    gb_c51_idx_0_tmp_tmp =
        c30_tmp.re * e_c30_tmp.re - c30_tmp.im * e_c30_tmp.im;
    scp0 = c30_tmp.re * e_c30_tmp.im + c30_tmp.im * e_c30_tmp.re;
    scr0 = c_c30_tmp.re * f_c30_tmp.re - c_c30_tmp.im * f_c30_tmp.im;
    ccr0 = c_c30_tmp.re * f_c30_tmp.im + c_c30_tmp.im * f_c30_tmp.re;
    cphi = scr0 * e_c30_tmp_tmp.re - ccr0 * e_c30_tmp_tmp.im;
    ccr0 = scr0 * e_c30_tmp_tmp.im + ccr0 * e_c30_tmp_tmp.re;
    scr0 = c_c30_tmp.re * e_c30_tmp.re - c_c30_tmp.im * e_c30_tmp.im;
    sc4 = c_c30_tmp.re * e_c30_tmp.im + c_c30_tmp.im * e_c30_tmp.re;
    cc4 = g_c30_tmp.re * c30_tmp_tmp.re - g_c30_tmp.im * c30_tmp_tmp.im;
    v3_idx_2 = g_c30_tmp.re * c30_tmp_tmp.im + g_c30_tmp.im * c30_tmp_tmp.re;
    w1_idx_0 = cc4 * c_c30_tmp_tmp.re - v3_idx_2 * c_c30_tmp_tmp.im;
    v3_idx_2 = cc4 * c_c30_tmp_tmp.im + v3_idx_2 * c_c30_tmp_tmp.re;
    i_re = 2.2393626025E+8 * d_c10_tmp.re;
    o_c51_idx_0_tmp_tmp = 2.2393626025E+8 * d_c10_tmp.im;
    h_c51_idx_0_tmp_tmp =
        i_re * b_c10_tmp_tmp.re - o_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.im;
    o_c51_idx_0_tmp_tmp =
        i_re * b_c10_tmp_tmp.im + o_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.re;
    cc4 = h_c30_tmp.re * c30_tmp_tmp.re - h_c30_tmp.im * c30_tmp_tmp.im;
    w1_idx_2 = h_c30_tmp.re * c30_tmp_tmp.im + h_c30_tmp.im * c30_tmp_tmp.re;
    w1_idx_1 = i_c30_tmp.re * c30_tmp_tmp.re - i_c30_tmp.im * c30_tmp_tmp.im;
    w1_idx_3 = i_c30_tmp.re * c30_tmp_tmp.im + i_c30_tmp.im * c30_tmp_tmp.re;
    v1_idx_0 = w1_idx_1 * e_c30_tmp_tmp.re - w1_idx_3 * e_c30_tmp_tmp.im;
    w1_idx_3 = w1_idx_1 * e_c30_tmp_tmp.im + w1_idx_3 * e_c30_tmp_tmp.re;
    i_re = 1.11968130125E+8 * e_c30_tmp.re;
    kb_c51_idx_0_tmp_tmp = 1.11968130125E+8 * e_c30_tmp.im;
    e_c51_idx_0_tmp_tmp =
        i_re * b_c10_tmp_tmp.re - kb_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.im;
    kb_c51_idx_0_tmp_tmp =
        i_re * b_c10_tmp_tmp.im + kb_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.re;
    w1_idx_1 = j_c30_tmp.re * c30_tmp_tmp.re - j_c30_tmp.im * c30_tmp_tmp.im;
    v1_idx_1 = j_c30_tmp.re * c30_tmp_tmp.im + j_c30_tmp.im * c30_tmp_tmp.re;
    i_re = 8.957450409999994E+8 * c10_tmp.re;
    lb_c51_idx_0_tmp_tmp = 8.957450409999994E+8 * c10_tmp.im;
    g_c51_idx_0_tmp_tmp =
        i_re * d_c10_tmp.re - lb_c51_idx_0_tmp_tmp * d_c10_tmp.im;
    lb_c51_idx_0_tmp_tmp =
        i_re * d_c10_tmp.im + lb_c51_idx_0_tmp_tmp * d_c10_tmp.re;
    i_re = g_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.re -
           lb_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.im;
    lb_c51_idx_0_tmp_tmp = g_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.im +
                           lb_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.re;
    g_c51_idx_0_tmp_tmp = 1.3436175615E+9 * c10_tmp.re;
    mb_c51_idx_0_tmp_tmp = 1.3436175615E+9 * c10_tmp.im;
    re = g_c51_idx_0_tmp_tmp * d_c10_tmp.re -
         mb_c51_idx_0_tmp_tmp * d_c10_tmp.im;
    mb_c51_idx_0_tmp_tmp = g_c51_idx_0_tmp_tmp * d_c10_tmp.im +
                           mb_c51_idx_0_tmp_tmp * d_c10_tmp.re;
    g_c51_idx_0_tmp_tmp =
        re * b_c10_tmp_tmp.re - mb_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.im;
    mb_c51_idx_0_tmp_tmp =
        re * b_c10_tmp_tmp.im + mb_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.re;
    re = 2.2393626025E+8 * dc.re;
    nb_c51_idx_0_tmp_tmp = 2.2393626025E+8 * dc.im;
    b_re = re * dc1.re - nb_c51_idx_0_tmp_tmp * dc1.im;
    nb_c51_idx_0_tmp_tmp = re * dc1.im + nb_c51_idx_0_tmp_tmp * dc1.re;
    re = b_re * c30_tmp_tmp.re - nb_c51_idx_0_tmp_tmp * c30_tmp_tmp.im;
    nb_c51_idx_0_tmp_tmp =
        b_re * c30_tmp_tmp.im + nb_c51_idx_0_tmp_tmp * c30_tmp_tmp.re;
    b_re = 5.59840650625E+7 * dc2.re;
    c51_idx_0_tmp_tmp_tmp = 5.59840650625E+7 * dc2.im;
    c_re = b_re * dc3.re - c51_idx_0_tmp_tmp_tmp * dc3.im;
    c51_idx_0_tmp_tmp_tmp = b_re * dc3.im + c51_idx_0_tmp_tmp_tmp * dc3.re;
    b_re = c_re * c30_tmp_tmp.re - c51_idx_0_tmp_tmp_tmp * c30_tmp_tmp.im;
    c51_idx_0_tmp_tmp_tmp =
        c_re * c30_tmp_tmp.im + c51_idx_0_tmp_tmp_tmp * c30_tmp_tmp.re;
    c_re = b_re * c_c30_tmp_tmp.re - c51_idx_0_tmp_tmp_tmp * c_c30_tmp_tmp.im;
    c51_idx_0_tmp_tmp_tmp =
        b_re * c_c30_tmp_tmp.im + c51_idx_0_tmp_tmp_tmp * c_c30_tmp_tmp.re;
    b_re = 2.2393626025E+8 * b_c30_tmp.re;
    f_c51_idx_0_tmp_tmp = 2.2393626025E+8 * b_c30_tmp.im;
    f_re = b_re * d_c10_tmp.re - f_c51_idx_0_tmp_tmp * d_c10_tmp.im;
    f_c51_idx_0_tmp_tmp =
        b_re * d_c10_tmp.im + f_c51_idx_0_tmp_tmp * d_c10_tmp.re;
    b_re = f_re * b_c10_tmp_tmp.re - f_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.im;
    f_c51_idx_0_tmp_tmp =
        f_re * b_c10_tmp_tmp.im + f_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.re;
    ccp0 = d_c30_tmp.re * e_c30_tmp.re - d_c30_tmp.im * e_c30_tmp.im;
    w2_idx_0 = d_c30_tmp.re * e_c30_tmp.im + d_c30_tmp.im * e_c30_tmp.re;
    w2_idx_2 = ccp0 * b_c10_tmp_tmp.re - w2_idx_0 * b_c10_tmp_tmp.im;
    w2_idx_0 = ccp0 * b_c10_tmp_tmp.im + w2_idx_0 * b_c10_tmp_tmp.re;
    f_re = 3.35904390375E+8 * dc4.re;
    im = 3.35904390375E+8 * dc4.im;
    d_re = f_re * dc5.re - im * dc5.im;
    im = f_re * dc5.im + im * dc5.re;
    f_re = d_re * c30_tmp_tmp.re - im * c30_tmp_tmp.im;
    im = d_re * c30_tmp_tmp.im + im * c30_tmp_tmp.re;
    d_re = 1.11968130125E+8 * dc6.re;
    b_im = 1.11968130125E+8 * dc6.im;
    g_re = d_re * dc7.re - b_im * dc7.im;
    b_im = d_re * dc7.im + b_im * dc7.re;
    d_re = g_re * c30_tmp_tmp.re - b_im * c30_tmp_tmp.im;
    b_im = g_re * c30_tmp_tmp.im + b_im * c30_tmp_tmp.re;
    g_re = 5.59840650625E+7 * dc8.re;
    c_im = 5.59840650625E+7 * dc8.im;
    h_re = g_re * dc9.re - c_im * dc9.im;
    c_im = g_re * dc9.im + c_im * dc9.re;
    g_re = h_re * c30_tmp_tmp.re - c_im * c30_tmp_tmp.im;
    c_im = h_re * c30_tmp_tmp.im + c_im * c30_tmp_tmp.re;
    h_re = g_re * e_c30_tmp_tmp.re - c_im * e_c30_tmp_tmp.im;
    c_im = g_re * e_c30_tmp_tmp.im + c_im * e_c30_tmp_tmp.re;
    ccp0 = k_c30_tmp.re * e_c30_tmp.re - k_c30_tmp.im * e_c30_tmp.im;
    w2_idx_1 = k_c30_tmp.re * e_c30_tmp.im + k_c30_tmp.im * e_c30_tmp.re;
    w2_idx_3 = ccp0 * b_c10_tmp_tmp.re - w2_idx_1 * b_c10_tmp_tmp.im;
    w2_idx_1 = ccp0 * b_c10_tmp_tmp.im + w2_idx_1 * b_c10_tmp_tmp.re;
    g_re = 5.59840650625E+7 * dc10.re;
    p_c51_idx_0_tmp_tmp = 5.59840650625E+7 * dc10.im;
    e_re = g_re * dc11.re - p_c51_idx_0_tmp_tmp * dc11.im;
    p_c51_idx_0_tmp_tmp = g_re * dc11.im + p_c51_idx_0_tmp_tmp * dc11.re;
    g_re = e_re * c30_tmp_tmp.re - p_c51_idx_0_tmp_tmp * c30_tmp_tmp.im;
    p_c51_idx_0_tmp_tmp =
        e_re * c30_tmp_tmp.im + p_c51_idx_0_tmp_tmp * c30_tmp_tmp.re;
    e_re = 3.5829801639999986E+9 * c10_tmp.re;
    ib_c51_idx_0_tmp_tmp = 3.5829801639999986E+9 * c10_tmp.im;
    jb_c51_idx_0_tmp_tmp =
        e_re * d_c10_tmp.re - ib_c51_idx_0_tmp_tmp * d_c10_tmp.im;
    ib_c51_idx_0_tmp_tmp =
        e_re * d_c10_tmp.im + ib_c51_idx_0_tmp_tmp * d_c10_tmp.re;
    e_re = jb_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.re -
           ib_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.im;
    ib_c51_idx_0_tmp_tmp = jb_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.im +
                           ib_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.re;
    b_c30_tmp.re =
        (((((((((((((((((((((((((((((((((((c30_tmp.re + c_c30_tmp.re) -
                                          5.5984065062500015E+7) -
                                         2.7992032531249989E+7) +
                                        5.59840650625E+7) -
                                       (d_c30_tmp.re * b_c10_tmp_tmp.re -
                                        d_c30_tmp.im * b_c10_tmp_tmp.im)) +
                                      (c30_tmp.re * c30_tmp_tmp.re -
                                       c30_tmp.im * c30_tmp_tmp.im)) -
                                     (k_c30_tmp.re * b_c10_tmp_tmp.re -
                                      k_c30_tmp.im * b_c10_tmp_tmp.im)) +
                                    (c_c30_tmp.re * c30_tmp_tmp.re -
                                     c_c30_tmp.im * c30_tmp_tmp.im)) +
                                   (c_c51_idx_0_tmp_tmp * 0.0 -
                                    d_c51_idx_0_tmp_tmp * 4.0)) -
                                  (h_c30_tmp.re * b_c30_tmp_tmp.re -
                                   h_c30_tmp.im * b_c30_tmp_tmp.im)) -
                                 (b_c51_idx_0_tmp_tmp * 0.0 -
                                  y_c51_idx_0_tmp_tmp * 4.0)) +
                                (j_c30_tmp.re * d_c30_tmp_tmp.re -
                                 j_c30_tmp.im * d_c30_tmp_tmp.im)) +
                               (v3_idx_0 * b_c30_tmp_tmp.re -
                                fb_c51_idx_0_tmp_tmp * b_c30_tmp_tmp.im)) -
                              (c51_idx_0_tmp_tmp * 0.0 -
                               hb_c51_idx_0_tmp_tmp * 4.0)) -
                             (j_re * b_c30_tmp_tmp.re -
                              d_im * b_c30_tmp_tmp.im)) +
                            (gb_c51_idx_0_tmp_tmp * d_c30_tmp_tmp.re -
                             scp0 * d_c30_tmp_tmp.im)) +
                           (cphi * 0.0 - ccr0 * 4.0)) +
                          (scr0 * d_c30_tmp_tmp.re - sc4 * d_c30_tmp_tmp.im)) -
                         (w1_idx_0 * 0.0 - v3_idx_2 * 4.0)) -
                        (h_c51_idx_0_tmp_tmp * b_c30_tmp_tmp.re -
                         o_c51_idx_0_tmp_tmp * b_c30_tmp_tmp.im)) -
                       (cc4 * b_c30_tmp_tmp.re - w1_idx_2 * b_c30_tmp_tmp.im)) +
                      (v1_idx_0 * 0.0 - w1_idx_3 * 4.0)) -
                     (e_c51_idx_0_tmp_tmp * d_c30_tmp_tmp.re -
                      kb_c51_idx_0_tmp_tmp * d_c30_tmp_tmp.im)) +
                    (w1_idx_1 * d_c30_tmp_tmp.re -
                     v1_idx_1 * d_c30_tmp_tmp.im)) +
                   (i_re * b_c30_tmp_tmp.re -
                    lb_c51_idx_0_tmp_tmp * b_c30_tmp_tmp.im)) +
                  (g_c51_idx_0_tmp_tmp * b_c30_tmp_tmp.re -
                   mb_c51_idx_0_tmp_tmp * b_c30_tmp_tmp.im)) +
                 (re * b_c30_tmp_tmp.re -
                  nb_c51_idx_0_tmp_tmp * b_c30_tmp_tmp.im)) +
                (c_re * 0.0 - c51_idx_0_tmp_tmp_tmp * 4.0)) -
               (b_re * b_c30_tmp_tmp.re -
                f_c51_idx_0_tmp_tmp * b_c30_tmp_tmp.im)) -
              (w2_idx_2 * d_c30_tmp_tmp.re - w2_idx_0 * d_c30_tmp_tmp.im)) -
             (f_re * b_c30_tmp_tmp.re - im * b_c30_tmp_tmp.im)) +
            (d_re * d_c30_tmp_tmp.re - b_im * d_c30_tmp_tmp.im)) -
           (h_re * 0.0 - c_im * 4.0)) -
          (w2_idx_3 * d_c30_tmp_tmp.re - w2_idx_1 * d_c30_tmp_tmp.im)) +
         (g_re * d_c30_tmp_tmp.re - p_c51_idx_0_tmp_tmp * d_c30_tmp_tmp.im)) -
        (e_re * b_c30_tmp_tmp.re - ib_c51_idx_0_tmp_tmp * b_c30_tmp_tmp.im);
    b_c30_tmp.im =
        ((((((((((((((((((((((((((((((((((c30_tmp.im + c_c30_tmp.im) -
                                         9.6967245102491692E+7) +
                                        4.8483622551245853E+7) -
                                       (d_c30_tmp.re * b_c10_tmp_tmp.im +
                                        d_c30_tmp.im * b_c10_tmp_tmp.re)) +
                                      (c30_tmp.re * c30_tmp_tmp.im +
                                       c30_tmp.im * c30_tmp_tmp.re)) -
                                     (k_c30_tmp.re * b_c10_tmp_tmp.im +
                                      k_c30_tmp.im * b_c10_tmp_tmp.re)) +
                                    (c_c30_tmp.re * c30_tmp_tmp.im +
                                     c_c30_tmp.im * c30_tmp_tmp.re)) +
                                   (c_c51_idx_0_tmp_tmp * 4.0 +
                                    d_c51_idx_0_tmp_tmp * 0.0)) -
                                  (h_c30_tmp.re * b_c30_tmp_tmp.im +
                                   h_c30_tmp.im * b_c30_tmp_tmp.re)) -
                                 (b_c51_idx_0_tmp_tmp * 4.0 +
                                  y_c51_idx_0_tmp_tmp * 0.0)) +
                                (j_c30_tmp.re * d_c30_tmp_tmp.im +
                                 j_c30_tmp.im * d_c30_tmp_tmp.re)) +
                               (v3_idx_0 * b_c30_tmp_tmp.im +
                                fb_c51_idx_0_tmp_tmp * b_c30_tmp_tmp.re)) -
                              (c51_idx_0_tmp_tmp * 4.0 +
                               hb_c51_idx_0_tmp_tmp * 0.0)) -
                             (j_re * b_c30_tmp_tmp.im +
                              d_im * b_c30_tmp_tmp.re)) +
                            (gb_c51_idx_0_tmp_tmp * d_c30_tmp_tmp.im +
                             scp0 * d_c30_tmp_tmp.re)) +
                           (cphi * 4.0 + ccr0 * 0.0)) +
                          (scr0 * d_c30_tmp_tmp.im + sc4 * d_c30_tmp_tmp.re)) -
                         (w1_idx_0 * 4.0 + v3_idx_2 * 0.0)) -
                        (h_c51_idx_0_tmp_tmp * b_c30_tmp_tmp.im +
                         o_c51_idx_0_tmp_tmp * b_c30_tmp_tmp.re)) -
                       (cc4 * b_c30_tmp_tmp.im + w1_idx_2 * b_c30_tmp_tmp.re)) +
                      (v1_idx_0 * 4.0 + w1_idx_3 * 0.0)) -
                     (e_c51_idx_0_tmp_tmp * d_c30_tmp_tmp.im +
                      kb_c51_idx_0_tmp_tmp * d_c30_tmp_tmp.re)) +
                    (w1_idx_1 * d_c30_tmp_tmp.im +
                     v1_idx_1 * d_c30_tmp_tmp.re)) +
                   (i_re * b_c30_tmp_tmp.im +
                    lb_c51_idx_0_tmp_tmp * b_c30_tmp_tmp.re)) +
                  (g_c51_idx_0_tmp_tmp * b_c30_tmp_tmp.im +
                   mb_c51_idx_0_tmp_tmp * b_c30_tmp_tmp.re)) +
                 (re * b_c30_tmp_tmp.im +
                  nb_c51_idx_0_tmp_tmp * b_c30_tmp_tmp.re)) +
                (c_re * 4.0 + c51_idx_0_tmp_tmp_tmp * 0.0)) -
               (b_re * b_c30_tmp_tmp.im +
                f_c51_idx_0_tmp_tmp * b_c30_tmp_tmp.re)) -
              (w2_idx_2 * d_c30_tmp_tmp.im + w2_idx_0 * d_c30_tmp_tmp.re)) -
             (f_re * b_c30_tmp_tmp.im + im * b_c30_tmp_tmp.re)) +
            (d_re * d_c30_tmp_tmp.im + b_im * d_c30_tmp_tmp.re)) -
           (h_re * 4.0 + c_im * 0.0)) -
          (w2_idx_3 * d_c30_tmp_tmp.im + w2_idx_1 * d_c30_tmp_tmp.re)) +
         (g_re * d_c30_tmp_tmp.im + p_c51_idx_0_tmp_tmp * d_c30_tmp_tmp.re)) -
        (e_re * b_c30_tmp_tmp.im + ib_c51_idx_0_tmp_tmp * b_c30_tmp_tmp.re);
    dc = power(b_c30_tmp);
    i_re = 29928.999999999989 * c_c10_tmp.re - m_c51_idx_0_tmp_tmp;
    d_im = 29928.999999999989 * c_c10_tmp.im + n_c51_idx_0_tmp_tmp;
    j_re = i_re * b_c10_tmp.re - d_im * b_c10_tmp.im;
    d_im = i_re * b_c10_tmp.im + d_im * b_c10_tmp.re;
    i_re = j_re * c_c10_tmp_tmp.re - d_im * c_c10_tmp_tmp.im;
    d_im = j_re * c_c10_tmp_tmp.im + d_im * c_c10_tmp_tmp.re;
    j_re = 59858.0 * c_c10_tmp.re - m_c51_idx_0_tmp_tmp;
    o_c51_idx_0_tmp_tmp = 59858.0 * c_c10_tmp.im + n_c51_idx_0_tmp_tmp;
    h_c51_idx_0_tmp_tmp =
        j_re * b_c10_tmp.re - o_c51_idx_0_tmp_tmp * b_c10_tmp.im;
    o_c51_idx_0_tmp_tmp =
        j_re * b_c10_tmp.im + o_c51_idx_0_tmp_tmp * b_c10_tmp.re;
    j_re = h_c51_idx_0_tmp_tmp * c_c10_tmp_tmp.re -
           o_c51_idx_0_tmp_tmp * c_c10_tmp_tmp.im;
    o_c51_idx_0_tmp_tmp = h_c51_idx_0_tmp_tmp * c_c10_tmp_tmp.im +
                          o_c51_idx_0_tmp_tmp * c_c10_tmp_tmp.re;
    c_c51_idx_0_tmp_tmp =
        l_c30_tmp.re * b_c10_tmp_tmp.re - l_c30_tmp.im * b_c10_tmp_tmp.im;
    d_c51_idx_0_tmp_tmp =
        l_c30_tmp.re * b_c10_tmp_tmp.im + l_c30_tmp.im * b_c10_tmp_tmp.re;
    h_c51_idx_0_tmp_tmp = 7482.25 * dc12.re;
    kb_c51_idx_0_tmp_tmp = 7482.25 * dc12.im;
    b_c51_idx_0_tmp_tmp =
        m_c30_tmp.re * c_c30_tmp_tmp.re - m_c30_tmp.im * c_c30_tmp_tmp.im;
    y_c51_idx_0_tmp_tmp =
        m_c30_tmp.re * c_c30_tmp_tmp.im + m_c30_tmp.im * c_c30_tmp_tmp.re;
    w1_idx_2 =
        k_c51_idx_0_tmp_tmp * b_c10_tmp.re - l_c51_idx_0_tmp_tmp * b_c10_tmp.im;
    v1_idx_0 =
        k_c51_idx_0_tmp_tmp * b_c10_tmp.im + l_c51_idx_0_tmp_tmp * b_c10_tmp.re;
    w1_idx_1 = w1_idx_2 * c_c30_tmp_tmp.re - v1_idx_0 * c_c30_tmp_tmp.im;
    v1_idx_0 = w1_idx_2 * c_c30_tmp_tmp.im + v1_idx_0 * c_c30_tmp_tmp.re;
    v3_idx_0 = l_c30_tmp.re * d_c10_tmp.re - l_c30_tmp.im * d_c10_tmp.im;
    fb_c51_idx_0_tmp_tmp =
        l_c30_tmp.re * d_c10_tmp.im + l_c30_tmp.im * d_c10_tmp.re;
    gb_c51_idx_0_tmp_tmp =
        v3_idx_0 * b_c30_tmp_tmp.re - fb_c51_idx_0_tmp_tmp * b_c30_tmp_tmp.im;
    fb_c51_idx_0_tmp_tmp =
        v3_idx_0 * b_c30_tmp_tmp.im + fb_c51_idx_0_tmp_tmp * b_c30_tmp_tmp.re;
    e_c51_idx_0_tmp_tmp = 7482.25 * dc13.re;
    lb_c51_idx_0_tmp_tmp = 7482.25 * dc13.im;
    g_c51_idx_0_tmp_tmp =
        e_c51_idx_0_tmp_tmp * dc14.re - lb_c51_idx_0_tmp_tmp * dc14.im;
    lb_c51_idx_0_tmp_tmp =
        e_c51_idx_0_tmp_tmp * dc14.im + lb_c51_idx_0_tmp_tmp * dc14.re;
    v3_idx_0 =
        m_c30_tmp.re * b_c10_tmp_tmp.re - m_c30_tmp.im * b_c10_tmp_tmp.im;
    hb_c51_idx_0_tmp_tmp =
        m_c30_tmp.re * b_c10_tmp_tmp.im + m_c30_tmp.im * b_c10_tmp_tmp.re;
    c51_idx_0_tmp_tmp =
        v3_idx_0 * c_c30_tmp_tmp.re - hb_c51_idx_0_tmp_tmp * c_c30_tmp_tmp.im;
    hb_c51_idx_0_tmp_tmp =
        v3_idx_0 * c_c30_tmp_tmp.im + hb_c51_idx_0_tmp_tmp * c_c30_tmp_tmp.re;
    e_c51_idx_0_tmp_tmp = 7482.25 * dc15.re;
    mb_c51_idx_0_tmp_tmp = 7482.25 * dc15.im;
    re = e_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.re -
         mb_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.im;
    mb_c51_idx_0_tmp_tmp = e_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.im +
                           mb_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.re;
    e_c51_idx_0_tmp_tmp = 7482.25 * dc16.re;
    nb_c51_idx_0_tmp_tmp = 7482.25 * dc16.im;
    b_re = e_c51_idx_0_tmp_tmp * dc17.re - nb_c51_idx_0_tmp_tmp * dc17.im;
    nb_c51_idx_0_tmp_tmp =
        e_c51_idx_0_tmp_tmp * dc17.im + nb_c51_idx_0_tmp_tmp * dc17.re;
    e_c51_idx_0_tmp_tmp =
        b_re * b_c10_tmp_tmp.re - nb_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.im;
    nb_c51_idx_0_tmp_tmp =
        b_re * b_c10_tmp_tmp.im + nb_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.re;
    b_re = e_c51_idx_0_tmp_tmp * c_c30_tmp_tmp.re -
           nb_c51_idx_0_tmp_tmp * c_c30_tmp_tmp.im;
    nb_c51_idx_0_tmp_tmp = e_c51_idx_0_tmp_tmp * c_c30_tmp_tmp.im +
                           nb_c51_idx_0_tmp_tmp * c_c30_tmp_tmp.re;
    e_c51_idx_0_tmp_tmp = 7482.25 * dc18.re;
    c51_idx_0_tmp_tmp_tmp = 7482.25 * dc18.im;
    c_re = e_c51_idx_0_tmp_tmp * dc19.re - c51_idx_0_tmp_tmp_tmp * dc19.im;
    c51_idx_0_tmp_tmp_tmp =
        e_c51_idx_0_tmp_tmp * dc19.im + c51_idx_0_tmp_tmp_tmp * dc19.re;
    e_c51_idx_0_tmp_tmp =
        c_re * b_c10_tmp_tmp.re - c51_idx_0_tmp_tmp_tmp * b_c10_tmp_tmp.im;
    c51_idx_0_tmp_tmp_tmp =
        c_re * b_c10_tmp_tmp.im + c51_idx_0_tmp_tmp_tmp * b_c10_tmp_tmp.re;
    c_re = e_c51_idx_0_tmp_tmp * b_c30_tmp_tmp.re -
           c51_idx_0_tmp_tmp_tmp * b_c30_tmp_tmp.im;
    c51_idx_0_tmp_tmp_tmp = e_c51_idx_0_tmp_tmp * b_c30_tmp_tmp.im +
                            c51_idx_0_tmp_tmp_tmp * b_c30_tmp_tmp.re;
    e_c51_idx_0_tmp_tmp = 7482.25 * dc20.re;
    f_c51_idx_0_tmp_tmp = 7482.25 * dc20.im;
    f_re = e_c51_idx_0_tmp_tmp * dc21.re - f_c51_idx_0_tmp_tmp * dc21.im;
    f_c51_idx_0_tmp_tmp =
        e_c51_idx_0_tmp_tmp * dc21.im + f_c51_idx_0_tmp_tmp * dc21.re;
    e_c51_idx_0_tmp_tmp =
        f_re * b_c10_tmp_tmp.re - f_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.im;
    f_c51_idx_0_tmp_tmp =
        f_re * b_c10_tmp_tmp.im + f_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.re;
    cc4 = ((c10_tmp_tmp.re * dc.re - c10_tmp_tmp.im * dc.im) -
           (i_re * c_c30_tmp_tmp.re - d_im * c_c30_tmp_tmp.im)) +
          (j_re * c_c30_tmp_tmp.re - o_c51_idx_0_tmp_tmp * c_c30_tmp_tmp.im);
    sc4 = ((c10_tmp_tmp.re * dc.im + c10_tmp_tmp.im * dc.re) -
           (i_re * c_c30_tmp_tmp.im + d_im * c_c30_tmp_tmp.re)) +
          (j_re * c_c30_tmp_tmp.im + o_c51_idx_0_tmp_tmp * c_c30_tmp_tmp.re);
    cphi =
        (((((((((((((((l_c30_tmp.re * 0.0 - l_c30_tmp.im * 2.0) -
                      k_c51_idx_0_tmp_tmp) -
                     3741.1250000000009) +
                    7482.25) -
                   (c_c51_idx_0_tmp_tmp * 0.0 - d_c51_idx_0_tmp_tmp * 2.0)) +
                  (h_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.re -
                   kb_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.im)) +
                 (b_c51_idx_0_tmp_tmp * 0.0 - y_c51_idx_0_tmp_tmp * 2.0)) -
                (i_c51_idx_0_tmp_tmp * b_c30_tmp_tmp.re -
                 j_c51_idx_0_tmp_tmp * b_c30_tmp_tmp.im)) +
               (w1_idx_1 * 0.0 - v1_idx_0 * 2.0)) +
              (gb_c51_idx_0_tmp_tmp * 0.0 - fb_c51_idx_0_tmp_tmp * 2.0)) +
             (g_c51_idx_0_tmp_tmp * b_c30_tmp_tmp.re -
              lb_c51_idx_0_tmp_tmp * b_c30_tmp_tmp.im)) +
            (c51_idx_0_tmp_tmp * 0.0 - hb_c51_idx_0_tmp_tmp * 2.0)) +
           (re * b_c30_tmp_tmp.re - mb_c51_idx_0_tmp_tmp * b_c30_tmp_tmp.im)) +
          (b_re * 0.0 - nb_c51_idx_0_tmp_tmp * 2.0)) -
         (c_re * 0.0 - c51_idx_0_tmp_tmp_tmp * 2.0)) -
        (e_c51_idx_0_tmp_tmp * b_c30_tmp_tmp.re -
         f_c51_idx_0_tmp_tmp * b_c30_tmp_tmp.im);
    scr0 =
        ((((((((((((((l_c30_tmp.re * 2.0 + l_c30_tmp.im * 0.0) -
                     l_c51_idx_0_tmp_tmp) -
                    6479.818577466116) -
                   (c_c51_idx_0_tmp_tmp * 2.0 + d_c51_idx_0_tmp_tmp * 0.0)) +
                  (h_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.im +
                   kb_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.re)) +
                 (b_c51_idx_0_tmp_tmp * 2.0 + y_c51_idx_0_tmp_tmp * 0.0)) -
                (i_c51_idx_0_tmp_tmp * b_c30_tmp_tmp.im +
                 j_c51_idx_0_tmp_tmp * b_c30_tmp_tmp.re)) +
               (w1_idx_1 * 2.0 + v1_idx_0 * 0.0)) +
              (gb_c51_idx_0_tmp_tmp * 2.0 + fb_c51_idx_0_tmp_tmp * 0.0)) +
             (g_c51_idx_0_tmp_tmp * b_c30_tmp_tmp.im +
              lb_c51_idx_0_tmp_tmp * b_c30_tmp_tmp.re)) +
            (c51_idx_0_tmp_tmp * 2.0 + hb_c51_idx_0_tmp_tmp * 0.0)) +
           (re * b_c30_tmp_tmp.im + mb_c51_idx_0_tmp_tmp * b_c30_tmp_tmp.re)) +
          (b_re * 2.0 + nb_c51_idx_0_tmp_tmp * 0.0)) -
         (c_re * 2.0 + c51_idx_0_tmp_tmp_tmp * 0.0)) -
        (e_c51_idx_0_tmp_tmp * b_c30_tmp_tmp.im +
         f_c51_idx_0_tmp_tmp * b_c30_tmp_tmp.re);
    if (scr0 == 0.0) {
      if (sc4 == 0.0) {
        dc.re = cc4 / cphi;
        dc.im = 0.0;
      } else if (cc4 == 0.0) {
        dc.re = 0.0;
        dc.im = sc4 / cphi;
      } else {
        dc.re = cc4 / cphi;
        dc.im = sc4 / cphi;
      }
    } else if (cphi == 0.0) {
      if (cc4 == 0.0) {
        dc.re = sc4 / scr0;
        dc.im = 0.0;
      } else if (sc4 == 0.0) {
        dc.re = 0.0;
        dc.im = -(cc4 / scr0);
      } else {
        dc.re = sc4 / scr0;
        dc.im = -(cc4 / scr0);
      }
    } else {
      ccr0 = fabs(cphi);
      ccp0 = fabs(scr0);
      if (ccr0 > ccp0) {
        scp0 = scr0 / cphi;
        ccp0 = cphi + scp0 * scr0;
        dc.re = (cc4 + scp0 * sc4) / ccp0;
        dc.im = (sc4 - scp0 * cc4) / ccp0;
      } else if (ccp0 == ccr0) {
        if (cphi > 0.0) {
          scp0 = 0.5;
        } else {
          scp0 = -0.5;
        }
        if (scr0 > 0.0) {
          ccp0 = 0.5;
        } else {
          ccp0 = -0.5;
        }
        dc.re = (cc4 * scp0 + sc4 * ccp0) / ccr0;
        dc.im = (sc4 * scp0 - cc4 * ccp0) / ccr0;
      } else {
        scp0 = cphi / scr0;
        ccp0 = scr0 + scp0 * cphi;
        dc.re = (scp0 * cc4 + sc4) / ccp0;
        dc.im = (scp0 * sc4 - cc4) / ccp0;
      }
    }
    b_log(&dc);
    dc1.re = crs * 0.0;
    dc1.im = crs * 2.0;
    b_exp(&dc1);
    dc2.re = crs * 0.0;
    dc2.im = crs * 4.0;
    b_exp(&dc2);
    dc3.re = crs * 0.0;
    dc3.im = crs * 2.0;
    b_exp(&dc3);
    dc4.re = crs * 0.0;
    dc4.im = crs * 2.0;
    b_exp(&dc4);
    dc5.re = crs * 0.0;
    dc5.im = crs * 4.0;
    b_exp(&dc5);
    dc6.re = crs * 0.0;
    dc6.im = crs * 4.0;
    b_exp(&dc6);
    dc7.re = cys * 0.0;
    dc7.im = cys;
    b_exp(&dc7);
    dc8.re = cys * 0.0;
    dc8.im = cys * 2.0;
    b_exp(&dc8);
    dc9.re = cys * 0.0;
    dc9.im = cys * 3.0;
    b_exp(&dc9);
    dc10.re = cys * 0.0;
    dc10.im = cys * 4.0;
    b_exp(&dc10);
    dc11.re = crs * 0.0;
    dc11.im = crs * 2.0;
    b_exp(&dc11);
    dc12.re = cys * 0.0;
    dc12.im = cys * 2.0;
    b_exp(&dc12);
    dc13.re = crs * 0.0;
    dc13.im = crs * 4.0;
    b_exp(&dc13);
    dc14.re = cys * 0.0;
    dc14.im = cys;
    b_exp(&dc14);
    dc15.re = crs * 0.0;
    dc15.im = crs * 4.0;
    b_exp(&dc15);
    dc16.re = cys * 0.0;
    dc16.im = cys * 2.0;
    b_exp(&dc16);
    dc17.re = crs * 0.0;
    dc17.im = crs * 2.0;
    b_exp(&dc17);
    dc18.re = cys * 0.0;
    dc18.im = cys * 4.0;
    b_exp(&dc18);
    dc19.re = crs * 0.0;
    dc19.im = crs * 4.0;
    b_exp(&dc19);
    dc20.re = cys * 0.0;
    dc20.im = cys * 3.0;
    b_exp(&dc20);
    dc21.re = crs * 0.0;
    dc21.im = crs * 4.0;
    b_exp(&dc21);
    dc22.re = cys * 0.0;
    dc22.im = cys * 4.0;
    b_exp(&dc22);
    dc23.re = cys * 0.0;
    dc23.im = cys;
    b_exp(&dc23);
    dc24.re = cys * 0.0;
    dc24.im = cys * 2.0;
    b_exp(&dc24);
    dc25.re = cys * 0.0;
    dc25.im = cys * 2.0;
    b_exp(&dc25);
    dc26.re = cys * 0.0;
    dc26.im = cys * 3.0;
    b_exp(&dc26);
    b_a.re = cys * 0.0;
    b_a.im = cys * 4.0;
    b_exp(&b_a);
    e_c10_tmp.re = cys * 0.0;
    e_c10_tmp.im = cys * 4.0;
    b_exp(&e_c10_tmp);
    c30_tmp.re = crs * 0.0;
    c30_tmp.im = crs * 2.0;
    b_exp(&c30_tmp);
    b_c30_tmp.re = cys * 0.0;
    b_c30_tmp.im = cys * 2.0;
    b_exp(&b_c30_tmp);
    c_c30_tmp.re = crs * 0.0;
    c_c30_tmp.im = crs * 2.0;
    b_exp(&c_c30_tmp);
    d_c30_tmp.re = cys * 0.0;
    d_c30_tmp.im = cys * 2.0;
    b_exp(&d_c30_tmp);
    e_c30_tmp.re = crs * 0.0;
    e_c30_tmp.im = crs * 2.0;
    b_exp(&e_c30_tmp);
    f_c30_tmp.re = cys * 0.0;
    f_c30_tmp.im = cys * 2.0;
    b_exp(&f_c30_tmp);
    g_c30_tmp.re = crs * 0.0;
    g_c30_tmp.im = crs * 4.0;
    b_exp(&g_c30_tmp);
    h_c30_tmp.re = cys * 0.0;
    h_c30_tmp.im = cys;
    b_exp(&h_c30_tmp);
    i_c30_tmp.re = crs * 0.0;
    i_c30_tmp.im = crs * 4.0;
    b_exp(&i_c30_tmp);
    j_c30_tmp.re = cys * 0.0;
    j_c30_tmp.im = cys * 2.0;
    b_exp(&j_c30_tmp);
    k_c30_tmp.re = crs * 0.0;
    k_c30_tmp.im = crs * 2.0;
    b_exp(&k_c30_tmp);
    l_c30_tmp.re = cys * 0.0;
    l_c30_tmp.im = cys * 4.0;
    b_exp(&l_c30_tmp);
    m_c30_tmp.re = crs * 0.0;
    m_c30_tmp.im = crs * 4.0;
    b_exp(&m_c30_tmp);
    b_c20_tmp.re = cys * 0.0;
    b_c20_tmp.im = cys * 2.0;
    b_exp(&b_c20_tmp);
    c10_tmp.re = crs * 0.0;
    c10_tmp.im = crs * 2.0;
    b_exp(&c10_tmp);
    b_c10_tmp.re = cys * 0.0;
    b_c10_tmp.im = cys * 4.0;
    b_exp(&b_c10_tmp);
    c_c10_tmp.re = crs * 0.0;
    c_c10_tmp.im = crs * 4.0;
    b_exp(&c_c10_tmp);
    d_c10_tmp.re = cys * 0.0;
    d_c10_tmp.im = cys * 3.0;
    b_exp(&d_c10_tmp);
    f_c10_tmp.re = crs * 0.0;
    f_c10_tmp.im = crs * 4.0;
    b_exp(&f_c10_tmp);
    g_c10_tmp.re = cys * 0.0;
    g_c10_tmp.im = cys * 4.0;
    b_exp(&g_c10_tmp);
    h_c10_tmp.re = crs * 0.0;
    h_c10_tmp.im = crs * 4.0;
    b_exp(&h_c10_tmp);
    i_c10_tmp.re = cys * 0.0;
    i_c10_tmp.im = cys * 4.0;
    b_exp(&i_c10_tmp);
    j_c10_tmp.re = crs * 0.0;
    j_c10_tmp.im = crs * 2.0;
    b_exp(&j_c10_tmp);
    c20_tmp.re = cys * 0.0;
    c20_tmp.im = cys * 2.0;
    b_exp(&c20_tmp);
    c_c20_tmp.re = crs * 0.0;
    c_c20_tmp.im = crs;
    b_exp(&c_c20_tmp);
    dc27.re = cys * 0.0;
    dc27.im = cys;
    b_exp(&dc27);
    dc28.re = crs * 0.0;
    dc28.im = crs;
    b_exp(&dc28);
    dc29.re = cys * 0.0;
    dc29.im = cys;
    b_exp(&dc29);
    dc30.re = crs * 0.0;
    dc30.im = crs;
    b_exp(&dc30);
    dc31.re = crs * 0.0;
    dc31.im = crs * 2.0;
    b_exp(&dc31);
    dc32.re = crs * 0.0;
    dc32.im = crs;
    b_exp(&dc32);
    dc33.re = crs * 0.0;
    dc33.im = crs * 2.0;
    b_exp(&dc33);
    dc34.re = cys * 0.0;
    dc34.im = cys;
    b_exp(&dc34);
    dc35.re = cys * 0.0;
    dc35.im = cys * 2.0;
    b_exp(&dc35);
    dc36.re = crs * 0.0;
    dc36.im = crs * 2.0;
    b_exp(&dc36);
    dc37.re = cys * 0.0;
    dc37.im = cys;
    b_exp(&dc37);
    dc38.re = crs * 0.0;
    dc38.im = crs;
    b_exp(&dc38);
    dc39.re = cys * 0.0;
    dc39.im = cys * 2.0;
    b_exp(&dc39);
    dc40.re = crs * 0.0;
    dc40.im = crs * 2.0;
    b_exp(&dc40);
    dc41.re = cys * 0.0;
    dc41.im = cys * 2.0;
    b_exp(&dc41);
    dc42.re = cys * 0.0;
    dc42.im = cys;
    b_exp(&dc42);
    dc43.re = cys * 0.0;
    dc43.im = cys * 2.0;
    b_exp(&dc43);
    dc44.re = crs * 0.0;
    dc44.im = crs * 2.0;
    b_exp(&dc44);
    dc45.re = cys * 0.0;
    dc45.im = cys;
    b_exp(&dc45);
    dc46.re = crs * 0.0;
    dc46.im = crs;
    b_exp(&dc46);
    dc47.re = cys * 0.0;
    dc47.im = cys * 2.0;
    b_exp(&dc47);
    dc48.re = crs * 0.0;
    dc48.im = crs * 2.0;
    b_exp(&dc48);
    dc49.re = cys * 0.0;
    dc49.im = cys * 2.0;
    b_exp(&dc49);
    i_re = 2.2393626025E+8 * dc3.re;
    d_im = 2.2393626025E+8 * dc3.im;
    j_re = 1.11968130125E+8 * dc4.re;
    o_c51_idx_0_tmp_tmp = 1.11968130125E+8 * dc4.im;
    h_c51_idx_0_tmp_tmp = 1.11968130125E+8 * dc5.re;
    kb_c51_idx_0_tmp_tmp = 1.11968130125E+8 * dc5.im;
    e_c51_idx_0_tmp_tmp = 5.59840650625E+7 * dc6.re;
    lb_c51_idx_0_tmp_tmp = 5.59840650625E+7 * dc6.im;
    g_c51_idx_0_tmp_tmp = 5.59840650625E+7 * dc7.re;
    mb_c51_idx_0_tmp_tmp = 5.59840650625E+7 * dc7.im;
    re = g_c51_idx_0_tmp_tmp * c_c30_tmp_tmp.re -
         mb_c51_idx_0_tmp_tmp * c_c30_tmp_tmp.im;
    mb_c51_idx_0_tmp_tmp = g_c51_idx_0_tmp_tmp * c_c30_tmp_tmp.im +
                           mb_c51_idx_0_tmp_tmp * c_c30_tmp_tmp.re;
    g_c51_idx_0_tmp_tmp = 3.35904390375E+8 * dc8.re;
    nb_c51_idx_0_tmp_tmp = 3.35904390375E+8 * dc8.im;
    b_re = 5.59840650625E+7 * dc9.re;
    c51_idx_0_tmp_tmp_tmp = 5.59840650625E+7 * dc9.im;
    c_re = b_re * e_c30_tmp_tmp.re - c51_idx_0_tmp_tmp_tmp * e_c30_tmp_tmp.im;
    c51_idx_0_tmp_tmp_tmp =
        b_re * e_c30_tmp_tmp.im + c51_idx_0_tmp_tmp_tmp * e_c30_tmp_tmp.re;
    b_re = 5.59840650625E+7 * dc10.re;
    f_c51_idx_0_tmp_tmp = 5.59840650625E+7 * dc10.im;
    f_re = 2.2393626025E+8 * dc11.re;
    im = 2.2393626025E+8 * dc11.im;
    d_re = f_re * dc12.re - im * dc12.im;
    im = f_re * dc12.im + im * dc12.re;
    f_re = 5.59840650625E+7 * dc13.re;
    b_im = 5.59840650625E+7 * dc13.im;
    g_re = f_re * dc14.re - b_im * dc14.im;
    b_im = f_re * dc14.im + b_im * dc14.re;
    f_re = g_re * c_c30_tmp_tmp.re - b_im * c_c30_tmp_tmp.im;
    b_im = g_re * c_c30_tmp_tmp.im + b_im * c_c30_tmp_tmp.re;
    g_re = 3.35904390375E+8 * dc15.re;
    c_im = 3.35904390375E+8 * dc15.im;
    h_re = g_re * dc16.re - c_im * dc16.im;
    c_im = g_re * dc16.im + c_im * dc16.re;
    g_re = 1.11968130125E+8 * dc17.re;
    p_c51_idx_0_tmp_tmp = 1.11968130125E+8 * dc17.im;
    e_re = g_re * dc18.re - p_c51_idx_0_tmp_tmp * dc18.im;
    p_c51_idx_0_tmp_tmp = g_re * dc18.im + p_c51_idx_0_tmp_tmp * dc18.re;
    g_re = 5.59840650625E+7 * dc19.re;
    ib_c51_idx_0_tmp_tmp = 5.59840650625E+7 * dc19.im;
    jb_c51_idx_0_tmp_tmp = g_re * dc20.re - ib_c51_idx_0_tmp_tmp * dc20.im;
    ib_c51_idx_0_tmp_tmp = g_re * dc20.im + ib_c51_idx_0_tmp_tmp * dc20.re;
    g_re = jb_c51_idx_0_tmp_tmp * e_c30_tmp_tmp.re -
           ib_c51_idx_0_tmp_tmp * e_c30_tmp_tmp.im;
    ib_c51_idx_0_tmp_tmp = jb_c51_idx_0_tmp_tmp * e_c30_tmp_tmp.im +
                           ib_c51_idx_0_tmp_tmp * e_c30_tmp_tmp.re;
    jb_c51_idx_0_tmp_tmp = 5.59840650625E+7 * dc21.re;
    pb_c51_idx_0_tmp_tmp = 5.59840650625E+7 * dc21.im;
    q_c51_idx_0_tmp_tmp =
        jb_c51_idx_0_tmp_tmp * dc22.re - pb_c51_idx_0_tmp_tmp * dc22.im;
    pb_c51_idx_0_tmp_tmp =
        jb_c51_idx_0_tmp_tmp * dc22.im + pb_c51_idx_0_tmp_tmp * dc22.re;
    jb_c51_idx_0_tmp_tmp = 5.59840650625E+7 * dc23.re;
    b_sc5_tmp_tmp = 5.59840650625E+7 * dc23.im;
    s_c51_idx_0_tmp_tmp =
        jb_c51_idx_0_tmp_tmp * c30_tmp_tmp.re - b_sc5_tmp_tmp * c30_tmp_tmp.im;
    b_sc5_tmp_tmp =
        jb_c51_idx_0_tmp_tmp * c30_tmp_tmp.im + b_sc5_tmp_tmp * c30_tmp_tmp.re;
    jb_c51_idx_0_tmp_tmp = s_c51_idx_0_tmp_tmp * c_c30_tmp_tmp.re -
                           b_sc5_tmp_tmp * c_c30_tmp_tmp.im;
    b_sc5_tmp_tmp = s_c51_idx_0_tmp_tmp * c_c30_tmp_tmp.im +
                    b_sc5_tmp_tmp * c_c30_tmp_tmp.re;
    s_c51_idx_0_tmp_tmp = 2.2393626025E+8 * dc24.re;
    x_c51_idx_0_tmp_tmp = 2.2393626025E+8 * dc24.im;
    u_c51_idx_0_tmp_tmp = s_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.re -
                          x_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.im;
    x_c51_idx_0_tmp_tmp = s_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.im +
                          x_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.re;
    s_c51_idx_0_tmp_tmp = 3.35904390375E+8 * dc25.re;
    d_c51_idx_0_tmp_tmp = 3.35904390375E+8 * dc25.im;
    r_c51_idx_0_tmp_tmp = s_c51_idx_0_tmp_tmp * c30_tmp_tmp.re -
                          d_c51_idx_0_tmp_tmp * c30_tmp_tmp.im;
    d_c51_idx_0_tmp_tmp = s_c51_idx_0_tmp_tmp * c30_tmp_tmp.im +
                          d_c51_idx_0_tmp_tmp * c30_tmp_tmp.re;
    s_c51_idx_0_tmp_tmp = 5.59840650625E+7 * dc26.re;
    b_c51_idx_0_tmp_tmp = 5.59840650625E+7 * dc26.im;
    ob_c51_idx_0_tmp_tmp = s_c51_idx_0_tmp_tmp * c30_tmp_tmp.re -
                           b_c51_idx_0_tmp_tmp * c30_tmp_tmp.im;
    b_c51_idx_0_tmp_tmp = s_c51_idx_0_tmp_tmp * c30_tmp_tmp.im +
                          b_c51_idx_0_tmp_tmp * c30_tmp_tmp.re;
    s_c51_idx_0_tmp_tmp = ob_c51_idx_0_tmp_tmp * e_c30_tmp_tmp.re -
                          b_c51_idx_0_tmp_tmp * e_c30_tmp_tmp.im;
    b_c51_idx_0_tmp_tmp = ob_c51_idx_0_tmp_tmp * e_c30_tmp_tmp.im +
                          b_c51_idx_0_tmp_tmp * e_c30_tmp_tmp.re;
    ob_c51_idx_0_tmp_tmp = 1.11968130125E+8 * b_a.re;
    y_c51_idx_0_tmp_tmp = 1.11968130125E+8 * b_a.im;
    ccp0 = ob_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.re -
           y_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.im;
    y_c51_idx_0_tmp_tmp = ob_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.im +
                          y_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.re;
    ob_c51_idx_0_tmp_tmp = 5.59840650625E+7 * e_c10_tmp.re;
    t_c51_idx_0_tmp_tmp = 5.59840650625E+7 * e_c10_tmp.im;
    scp0 = ob_c51_idx_0_tmp_tmp * c30_tmp_tmp.re -
           t_c51_idx_0_tmp_tmp * c30_tmp_tmp.im;
    t_c51_idx_0_tmp_tmp = ob_c51_idx_0_tmp_tmp * c30_tmp_tmp.im +
                          t_c51_idx_0_tmp_tmp * c30_tmp_tmp.re;
    ob_c51_idx_0_tmp_tmp = 8.957450409999994E+8 * c30_tmp.re;
    v_c51_idx_0_tmp_tmp = 8.957450409999994E+8 * c30_tmp.im;
    scr0 = ob_c51_idx_0_tmp_tmp * b_c30_tmp.re -
           v_c51_idx_0_tmp_tmp * b_c30_tmp.im;
    v_c51_idx_0_tmp_tmp = ob_c51_idx_0_tmp_tmp * b_c30_tmp.im +
                          v_c51_idx_0_tmp_tmp * b_c30_tmp.re;
    ob_c51_idx_0_tmp_tmp =
        scr0 * b_c10_tmp_tmp.re - v_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.im;
    v_c51_idx_0_tmp_tmp =
        scr0 * b_c10_tmp_tmp.im + v_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.re;
    scr0 = 1.3436175615E+9 * c_c30_tmp.re;
    w_c51_idx_0_tmp_tmp = 1.3436175615E+9 * c_c30_tmp.im;
    ccr0 = scr0 * d_c30_tmp.re - w_c51_idx_0_tmp_tmp * d_c30_tmp.im;
    w_c51_idx_0_tmp_tmp =
        scr0 * d_c30_tmp.im + w_c51_idx_0_tmp_tmp * d_c30_tmp.re;
    scr0 = ccr0 * b_c10_tmp_tmp.re - w_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.im;
    w_c51_idx_0_tmp_tmp =
        ccr0 * b_c10_tmp_tmp.im + w_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.re;
    ccr0 = 2.2393626025E+8 * e_c30_tmp.re;
    cphi = 2.2393626025E+8 * e_c30_tmp.im;
    sc4 = ccr0 * f_c30_tmp.re - cphi * f_c30_tmp.im;
    cphi = ccr0 * f_c30_tmp.im + cphi * f_c30_tmp.re;
    ccr0 = sc4 * c30_tmp_tmp.re - cphi * c30_tmp_tmp.im;
    cphi = sc4 * c30_tmp_tmp.im + cphi * c30_tmp_tmp.re;
    sc4 = 5.59840650625E+7 * g_c30_tmp.re;
    cc4 = 5.59840650625E+7 * g_c30_tmp.im;
    v3_idx_2 = sc4 * h_c30_tmp.re - cc4 * h_c30_tmp.im;
    cc4 = sc4 * h_c30_tmp.im + cc4 * h_c30_tmp.re;
    sc4 = v3_idx_2 * c30_tmp_tmp.re - cc4 * c30_tmp_tmp.im;
    cc4 = v3_idx_2 * c30_tmp_tmp.im + cc4 * c30_tmp_tmp.re;
    v3_idx_2 = sc4 * c_c30_tmp_tmp.re - cc4 * c_c30_tmp_tmp.im;
    cc4 = sc4 * c_c30_tmp_tmp.im + cc4 * c_c30_tmp_tmp.re;
    sc4 = 2.2393626025E+8 * i_c30_tmp.re;
    w1_idx_0 = 2.2393626025E+8 * i_c30_tmp.im;
    w1_idx_2 = sc4 * j_c30_tmp.re - w1_idx_0 * j_c30_tmp.im;
    w1_idx_0 = sc4 * j_c30_tmp.im + w1_idx_0 * j_c30_tmp.re;
    sc4 = w1_idx_2 * b_c10_tmp_tmp.re - w1_idx_0 * b_c10_tmp_tmp.im;
    w1_idx_0 = w1_idx_2 * b_c10_tmp_tmp.im + w1_idx_0 * b_c10_tmp_tmp.re;
    w1_idx_2 = 2.2393626025E+8 * k_c30_tmp.re;
    w1_idx_1 = 2.2393626025E+8 * k_c30_tmp.im;
    w1_idx_3 = w1_idx_2 * l_c30_tmp.re - w1_idx_1 * l_c30_tmp.im;
    w1_idx_1 = w1_idx_2 * l_c30_tmp.im + w1_idx_1 * l_c30_tmp.re;
    w1_idx_2 = w1_idx_3 * b_c10_tmp_tmp.re - w1_idx_1 * b_c10_tmp_tmp.im;
    w1_idx_1 = w1_idx_3 * b_c10_tmp_tmp.im + w1_idx_1 * b_c10_tmp_tmp.re;
    w1_idx_3 = 3.35904390375E+8 * m_c30_tmp.re;
    v1_idx_0 = 3.35904390375E+8 * m_c30_tmp.im;
    v1_idx_1 = w1_idx_3 * b_c20_tmp.re - v1_idx_0 * b_c20_tmp.im;
    v1_idx_0 = w1_idx_3 * b_c20_tmp.im + v1_idx_0 * b_c20_tmp.re;
    w1_idx_3 = v1_idx_1 * c30_tmp_tmp.re - v1_idx_0 * c30_tmp_tmp.im;
    v1_idx_0 = v1_idx_1 * c30_tmp_tmp.im + v1_idx_0 * c30_tmp_tmp.re;
    v1_idx_1 = 1.11968130125E+8 * c10_tmp.re;
    w2_idx_0 = 1.11968130125E+8 * c10_tmp.im;
    w2_idx_2 = v1_idx_1 * b_c10_tmp.re - w2_idx_0 * b_c10_tmp.im;
    w2_idx_0 = v1_idx_1 * b_c10_tmp.im + w2_idx_0 * b_c10_tmp.re;
    v1_idx_1 = w2_idx_2 * c30_tmp_tmp.re - w2_idx_0 * c30_tmp_tmp.im;
    w2_idx_0 = w2_idx_2 * c30_tmp_tmp.im + w2_idx_0 * c30_tmp_tmp.re;
    w2_idx_2 = 5.59840650625E+7 * c_c10_tmp.re;
    w2_idx_1 = 5.59840650625E+7 * c_c10_tmp.im;
    w2_idx_3 = w2_idx_2 * d_c10_tmp.re - w2_idx_1 * d_c10_tmp.im;
    w2_idx_1 = w2_idx_2 * d_c10_tmp.im + w2_idx_1 * d_c10_tmp.re;
    w2_idx_2 = w2_idx_3 * c30_tmp_tmp.re - w2_idx_1 * c30_tmp_tmp.im;
    w2_idx_1 = w2_idx_3 * c30_tmp_tmp.im + w2_idx_1 * c30_tmp_tmp.re;
    w2_idx_3 = w2_idx_2 * e_c30_tmp_tmp.re - w2_idx_1 * e_c30_tmp_tmp.im;
    w2_idx_1 = w2_idx_2 * e_c30_tmp_tmp.im + w2_idx_1 * e_c30_tmp_tmp.re;
    w2_idx_2 = 1.11968130125E+8 * f_c10_tmp.re;
    v3_idx_0 = 1.11968130125E+8 * f_c10_tmp.im;
    fb_c51_idx_0_tmp_tmp = w2_idx_2 * g_c10_tmp.re - v3_idx_0 * g_c10_tmp.im;
    v3_idx_0 = w2_idx_2 * g_c10_tmp.im + v3_idx_0 * g_c10_tmp.re;
    w2_idx_2 =
        fb_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.re - v3_idx_0 * b_c10_tmp_tmp.im;
    v3_idx_0 =
        fb_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.im + v3_idx_0 * b_c10_tmp_tmp.re;
    fb_c51_idx_0_tmp_tmp = 5.59840650625E+7 * h_c10_tmp.re;
    gb_c51_idx_0_tmp_tmp = 5.59840650625E+7 * h_c10_tmp.im;
    hb_c51_idx_0_tmp_tmp = fb_c51_idx_0_tmp_tmp * i_c10_tmp.re -
                           gb_c51_idx_0_tmp_tmp * i_c10_tmp.im;
    gb_c51_idx_0_tmp_tmp = fb_c51_idx_0_tmp_tmp * i_c10_tmp.im +
                           gb_c51_idx_0_tmp_tmp * i_c10_tmp.re;
    fb_c51_idx_0_tmp_tmp = hb_c51_idx_0_tmp_tmp * c30_tmp_tmp.re -
                           gb_c51_idx_0_tmp_tmp * c30_tmp_tmp.im;
    gb_c51_idx_0_tmp_tmp = hb_c51_idx_0_tmp_tmp * c30_tmp_tmp.im +
                           gb_c51_idx_0_tmp_tmp * c30_tmp_tmp.re;
    hb_c51_idx_0_tmp_tmp = 3.5829801639999986E+9 * j_c10_tmp.re;
    c51_idx_0_tmp_tmp = 3.5829801639999986E+9 * j_c10_tmp.im;
    c_c51_idx_0_tmp_tmp =
        hb_c51_idx_0_tmp_tmp * c20_tmp.re - c51_idx_0_tmp_tmp * c20_tmp.im;
    c51_idx_0_tmp_tmp =
        hb_c51_idx_0_tmp_tmp * c20_tmp.im + c51_idx_0_tmp_tmp * c20_tmp.re;
    hb_c51_idx_0_tmp_tmp = c_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.re -
                           c51_idx_0_tmp_tmp * b_c10_tmp_tmp.im;
    c51_idx_0_tmp_tmp = c_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.im +
                        c51_idx_0_tmp_tmp * b_c10_tmp_tmp.re;
    dc3.re =
        (((((((((((((((((((((((((((((((((((1.11968130125E+8 * dc1.re +
                                           5.59840650625E+7 * dc2.re) -
                                          5.5984065062500015E+7) -
                                         2.7992032531249989E+7) +
                                        5.59840650625E+7) -
                                       (i_re * b_c10_tmp_tmp.re -
                                        d_im * b_c10_tmp_tmp.im)) +
                                      (j_re * c30_tmp_tmp.re -
                                       o_c51_idx_0_tmp_tmp * c30_tmp_tmp.im)) -
                                     (h_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.re -
                                      kb_c51_idx_0_tmp_tmp *
                                          b_c10_tmp_tmp.im)) +
                                    (e_c51_idx_0_tmp_tmp * c30_tmp_tmp.re -
                                     lb_c51_idx_0_tmp_tmp * c30_tmp_tmp.im)) +
                                   (re * 0.0 - mb_c51_idx_0_tmp_tmp * 4.0)) -
                                  (g_c51_idx_0_tmp_tmp * b_c30_tmp_tmp.re -
                                   nb_c51_idx_0_tmp_tmp * b_c30_tmp_tmp.im)) -
                                 (c_re * 0.0 - c51_idx_0_tmp_tmp_tmp * 4.0)) +
                                (b_re * d_c30_tmp_tmp.re -
                                 f_c51_idx_0_tmp_tmp * d_c30_tmp_tmp.im)) +
                               (d_re * b_c30_tmp_tmp.re -
                                im * b_c30_tmp_tmp.im)) -
                              (f_re * 0.0 - b_im * 4.0)) -
                             (h_re * b_c30_tmp_tmp.re -
                              c_im * b_c30_tmp_tmp.im)) +
                            (e_re * d_c30_tmp_tmp.re -
                             p_c51_idx_0_tmp_tmp * d_c30_tmp_tmp.im)) +
                           (g_re * 0.0 - ib_c51_idx_0_tmp_tmp * 4.0)) +
                          (q_c51_idx_0_tmp_tmp * d_c30_tmp_tmp.re -
                           pb_c51_idx_0_tmp_tmp * d_c30_tmp_tmp.im)) -
                         (jb_c51_idx_0_tmp_tmp * 0.0 - b_sc5_tmp_tmp * 4.0)) -
                        (u_c51_idx_0_tmp_tmp * b_c30_tmp_tmp.re -
                         x_c51_idx_0_tmp_tmp * b_c30_tmp_tmp.im)) -
                       (r_c51_idx_0_tmp_tmp * b_c30_tmp_tmp.re -
                        d_c51_idx_0_tmp_tmp * b_c30_tmp_tmp.im)) +
                      (s_c51_idx_0_tmp_tmp * 0.0 - b_c51_idx_0_tmp_tmp * 4.0)) -
                     (ccp0 * d_c30_tmp_tmp.re -
                      y_c51_idx_0_tmp_tmp * d_c30_tmp_tmp.im)) +
                    (scp0 * d_c30_tmp_tmp.re -
                     t_c51_idx_0_tmp_tmp * d_c30_tmp_tmp.im)) +
                   (ob_c51_idx_0_tmp_tmp * b_c30_tmp_tmp.re -
                    v_c51_idx_0_tmp_tmp * b_c30_tmp_tmp.im)) +
                  (scr0 * b_c30_tmp_tmp.re -
                   w_c51_idx_0_tmp_tmp * b_c30_tmp_tmp.im)) +
                 (ccr0 * b_c30_tmp_tmp.re - cphi * b_c30_tmp_tmp.im)) +
                (v3_idx_2 * 0.0 - cc4 * 4.0)) -
               (sc4 * b_c30_tmp_tmp.re - w1_idx_0 * b_c30_tmp_tmp.im)) -
              (w1_idx_2 * d_c30_tmp_tmp.re - w1_idx_1 * d_c30_tmp_tmp.im)) -
             (w1_idx_3 * b_c30_tmp_tmp.re - v1_idx_0 * b_c30_tmp_tmp.im)) +
            (v1_idx_1 * d_c30_tmp_tmp.re - w2_idx_0 * d_c30_tmp_tmp.im)) -
           (w2_idx_3 * 0.0 - w2_idx_1 * 4.0)) -
          (w2_idx_2 * d_c30_tmp_tmp.re - v3_idx_0 * d_c30_tmp_tmp.im)) +
         (fb_c51_idx_0_tmp_tmp * d_c30_tmp_tmp.re -
          gb_c51_idx_0_tmp_tmp * d_c30_tmp_tmp.im)) -
        (hb_c51_idx_0_tmp_tmp * b_c30_tmp_tmp.re -
         c51_idx_0_tmp_tmp * b_c30_tmp_tmp.im);
    dc3.im =
        ((((((((((((((((((((((((((((((((((1.11968130125E+8 * dc1.im +
                                          5.59840650625E+7 * dc2.im) -
                                         9.6967245102491692E+7) +
                                        4.8483622551245853E+7) -
                                       (i_re * b_c10_tmp_tmp.im +
                                        d_im * b_c10_tmp_tmp.re)) +
                                      (j_re * c30_tmp_tmp.im +
                                       o_c51_idx_0_tmp_tmp * c30_tmp_tmp.re)) -
                                     (h_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.im +
                                      kb_c51_idx_0_tmp_tmp *
                                          b_c10_tmp_tmp.re)) +
                                    (e_c51_idx_0_tmp_tmp * c30_tmp_tmp.im +
                                     lb_c51_idx_0_tmp_tmp * c30_tmp_tmp.re)) +
                                   (re * 4.0 + mb_c51_idx_0_tmp_tmp * 0.0)) -
                                  (g_c51_idx_0_tmp_tmp * b_c30_tmp_tmp.im +
                                   nb_c51_idx_0_tmp_tmp * b_c30_tmp_tmp.re)) -
                                 (c_re * 4.0 + c51_idx_0_tmp_tmp_tmp * 0.0)) +
                                (b_re * d_c30_tmp_tmp.im +
                                 f_c51_idx_0_tmp_tmp * d_c30_tmp_tmp.re)) +
                               (d_re * b_c30_tmp_tmp.im +
                                im * b_c30_tmp_tmp.re)) -
                              (f_re * 4.0 + b_im * 0.0)) -
                             (h_re * b_c30_tmp_tmp.im +
                              c_im * b_c30_tmp_tmp.re)) +
                            (e_re * d_c30_tmp_tmp.im +
                             p_c51_idx_0_tmp_tmp * d_c30_tmp_tmp.re)) +
                           (g_re * 4.0 + ib_c51_idx_0_tmp_tmp * 0.0)) +
                          (q_c51_idx_0_tmp_tmp * d_c30_tmp_tmp.im +
                           pb_c51_idx_0_tmp_tmp * d_c30_tmp_tmp.re)) -
                         (jb_c51_idx_0_tmp_tmp * 4.0 + b_sc5_tmp_tmp * 0.0)) -
                        (u_c51_idx_0_tmp_tmp * b_c30_tmp_tmp.im +
                         x_c51_idx_0_tmp_tmp * b_c30_tmp_tmp.re)) -
                       (r_c51_idx_0_tmp_tmp * b_c30_tmp_tmp.im +
                        d_c51_idx_0_tmp_tmp * b_c30_tmp_tmp.re)) +
                      (s_c51_idx_0_tmp_tmp * 4.0 + b_c51_idx_0_tmp_tmp * 0.0)) -
                     (ccp0 * d_c30_tmp_tmp.im +
                      y_c51_idx_0_tmp_tmp * d_c30_tmp_tmp.re)) +
                    (scp0 * d_c30_tmp_tmp.im +
                     t_c51_idx_0_tmp_tmp * d_c30_tmp_tmp.re)) +
                   (ob_c51_idx_0_tmp_tmp * b_c30_tmp_tmp.im +
                    v_c51_idx_0_tmp_tmp * b_c30_tmp_tmp.re)) +
                  (scr0 * b_c30_tmp_tmp.im +
                   w_c51_idx_0_tmp_tmp * b_c30_tmp_tmp.re)) +
                 (ccr0 * b_c30_tmp_tmp.im + cphi * b_c30_tmp_tmp.re)) +
                (v3_idx_2 * 4.0 + cc4 * 0.0)) -
               (sc4 * b_c30_tmp_tmp.im + w1_idx_0 * b_c30_tmp_tmp.re)) -
              (w1_idx_2 * d_c30_tmp_tmp.im + w1_idx_1 * d_c30_tmp_tmp.re)) -
             (w1_idx_3 * b_c30_tmp_tmp.im + v1_idx_0 * b_c30_tmp_tmp.re)) +
            (v1_idx_1 * d_c30_tmp_tmp.im + w2_idx_0 * d_c30_tmp_tmp.re)) -
           (w2_idx_3 * 4.0 + w2_idx_1 * 0.0)) -
          (w2_idx_2 * d_c30_tmp_tmp.im + v3_idx_0 * d_c30_tmp_tmp.re)) +
         (fb_c51_idx_0_tmp_tmp * d_c30_tmp_tmp.im +
          gb_c51_idx_0_tmp_tmp * d_c30_tmp_tmp.re)) -
        (hb_c51_idx_0_tmp_tmp * b_c30_tmp_tmp.im +
         c51_idx_0_tmp_tmp * b_c30_tmp_tmp.re);
    dc1 = power(dc3);
    i_re = 29928.999999999989 * c_c20_tmp.re - 0.0 * c_c20_tmp.im;
    d_im = 29928.999999999989 * c_c20_tmp.im + 0.0 * c_c20_tmp.re;
    j_re = i_re * dc27.re - d_im * dc27.im;
    d_im = i_re * dc27.im + d_im * dc27.re;
    i_re = j_re * c_c10_tmp_tmp.re - d_im * c_c10_tmp_tmp.im;
    d_im = j_re * c_c10_tmp_tmp.im + d_im * c_c10_tmp_tmp.re;
    j_re = 59858.0 * dc28.re - 0.0 * dc28.im;
    o_c51_idx_0_tmp_tmp = 59858.0 * dc28.im + 0.0 * dc28.re;
    h_c51_idx_0_tmp_tmp = j_re * dc29.re - o_c51_idx_0_tmp_tmp * dc29.im;
    o_c51_idx_0_tmp_tmp = j_re * dc29.im + o_c51_idx_0_tmp_tmp * dc29.re;
    j_re = h_c51_idx_0_tmp_tmp * c_c10_tmp_tmp.re -
           o_c51_idx_0_tmp_tmp * c_c10_tmp_tmp.im;
    o_c51_idx_0_tmp_tmp = h_c51_idx_0_tmp_tmp * c_c10_tmp_tmp.im +
                          o_c51_idx_0_tmp_tmp * c_c10_tmp_tmp.re;
    h_c51_idx_0_tmp_tmp = 7482.25 * dc30.re;
    kb_c51_idx_0_tmp_tmp = 7482.25 * dc30.im;
    e_c51_idx_0_tmp_tmp = 7482.25 * dc32.re;
    lb_c51_idx_0_tmp_tmp = 7482.25 * dc32.im;
    g_c51_idx_0_tmp_tmp = e_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.re -
                          lb_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.im;
    lb_c51_idx_0_tmp_tmp = e_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.im +
                           lb_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.re;
    e_c51_idx_0_tmp_tmp = 7482.25 * dc33.re;
    mb_c51_idx_0_tmp_tmp = 7482.25 * dc33.im;
    re = 7482.25 * dc34.re;
    nb_c51_idx_0_tmp_tmp = 7482.25 * dc34.im;
    b_re = re * c_c30_tmp_tmp.re - nb_c51_idx_0_tmp_tmp * c_c30_tmp_tmp.im;
    nb_c51_idx_0_tmp_tmp =
        re * c_c30_tmp_tmp.im + nb_c51_idx_0_tmp_tmp * c_c30_tmp_tmp.re;
    re = 7482.25 * dc35.re;
    c51_idx_0_tmp_tmp_tmp = 7482.25 * dc35.im;
    c_re = 7482.25 * dc36.re;
    f_c51_idx_0_tmp_tmp = 7482.25 * dc36.im;
    f_re = c_re * dc37.re - f_c51_idx_0_tmp_tmp * dc37.im;
    f_c51_idx_0_tmp_tmp = c_re * dc37.im + f_c51_idx_0_tmp_tmp * dc37.re;
    c_re = f_re * c_c30_tmp_tmp.re - f_c51_idx_0_tmp_tmp * c_c30_tmp_tmp.im;
    f_c51_idx_0_tmp_tmp =
        f_re * c_c30_tmp_tmp.im + f_c51_idx_0_tmp_tmp * c_c30_tmp_tmp.re;
    f_re = 7482.25 * dc38.re;
    im = 7482.25 * dc38.im;
    d_re = f_re * dc39.re - im * dc39.im;
    im = f_re * dc39.im + im * dc39.re;
    f_re = d_re * b_c30_tmp_tmp.re - im * b_c30_tmp_tmp.im;
    im = d_re * b_c30_tmp_tmp.im + im * b_c30_tmp_tmp.re;
    d_re = 7482.25 * dc40.re;
    b_im = 7482.25 * dc40.im;
    g_re = d_re * dc41.re - b_im * dc41.im;
    b_im = d_re * dc41.im + b_im * dc41.re;
    d_re = 7482.25 * dc42.re;
    c_im = 7482.25 * dc42.im;
    h_re = d_re * b_c10_tmp_tmp.re - c_im * b_c10_tmp_tmp.im;
    c_im = d_re * b_c10_tmp_tmp.im + c_im * b_c10_tmp_tmp.re;
    d_re = h_re * c_c30_tmp_tmp.re - c_im * c_c30_tmp_tmp.im;
    c_im = h_re * c_c30_tmp_tmp.im + c_im * c_c30_tmp_tmp.re;
    h_re = 7482.25 * dc43.re;
    p_c51_idx_0_tmp_tmp = 7482.25 * dc43.im;
    e_re = h_re * b_c10_tmp_tmp.re - p_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.im;
    p_c51_idx_0_tmp_tmp =
        h_re * b_c10_tmp_tmp.im + p_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.re;
    h_re = 7482.25 * dc44.re;
    ib_c51_idx_0_tmp_tmp = 7482.25 * dc44.im;
    jb_c51_idx_0_tmp_tmp = h_re * dc45.re - ib_c51_idx_0_tmp_tmp * dc45.im;
    ib_c51_idx_0_tmp_tmp = h_re * dc45.im + ib_c51_idx_0_tmp_tmp * dc45.re;
    h_re = jb_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.re -
           ib_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.im;
    ib_c51_idx_0_tmp_tmp = jb_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.im +
                           ib_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.re;
    jb_c51_idx_0_tmp_tmp =
        h_re * c_c30_tmp_tmp.re - ib_c51_idx_0_tmp_tmp * c_c30_tmp_tmp.im;
    ib_c51_idx_0_tmp_tmp =
        h_re * c_c30_tmp_tmp.im + ib_c51_idx_0_tmp_tmp * c_c30_tmp_tmp.re;
    h_re = 7482.25 * dc46.re;
    pb_c51_idx_0_tmp_tmp = 7482.25 * dc46.im;
    q_c51_idx_0_tmp_tmp = h_re * dc47.re - pb_c51_idx_0_tmp_tmp * dc47.im;
    pb_c51_idx_0_tmp_tmp = h_re * dc47.im + pb_c51_idx_0_tmp_tmp * dc47.re;
    h_re = q_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.re -
           pb_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.im;
    pb_c51_idx_0_tmp_tmp = q_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.im +
                           pb_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.re;
    q_c51_idx_0_tmp_tmp =
        h_re * b_c30_tmp_tmp.re - pb_c51_idx_0_tmp_tmp * b_c30_tmp_tmp.im;
    pb_c51_idx_0_tmp_tmp =
        h_re * b_c30_tmp_tmp.im + pb_c51_idx_0_tmp_tmp * b_c30_tmp_tmp.re;
    h_re = 7482.25 * dc48.re;
    b_sc5_tmp_tmp = 7482.25 * dc48.im;
    s_c51_idx_0_tmp_tmp = h_re * dc49.re - b_sc5_tmp_tmp * dc49.im;
    b_sc5_tmp_tmp = h_re * dc49.im + b_sc5_tmp_tmp * dc49.re;
    h_re = s_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.re -
           b_sc5_tmp_tmp * b_c10_tmp_tmp.im;
    b_sc5_tmp_tmp = s_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.im +
                    b_sc5_tmp_tmp * b_c10_tmp_tmp.re;
    cc4 = -(((c10_tmp_tmp.re * dc1.re - c10_tmp_tmp.im * dc1.im) +
             (i_re * c_c30_tmp_tmp.re - d_im * c_c30_tmp_tmp.im)) -
            (j_re * c_c30_tmp_tmp.re - o_c51_idx_0_tmp_tmp * c_c30_tmp_tmp.im));
    sc4 = -(((c10_tmp_tmp.re * dc1.im + c10_tmp_tmp.im * dc1.re) +
             (i_re * c_c30_tmp_tmp.im + d_im * c_c30_tmp_tmp.re)) -
            (j_re * c_c30_tmp_tmp.im + o_c51_idx_0_tmp_tmp * c_c30_tmp_tmp.re));
    cphi =
        (((((((((((((((h_c51_idx_0_tmp_tmp * 0.0 - kb_c51_idx_0_tmp_tmp * 2.0) -
                      7482.25 * dc31.re) -
                     3741.1250000000009) +
                    7482.25) -
                   (g_c51_idx_0_tmp_tmp * 0.0 - lb_c51_idx_0_tmp_tmp * 2.0)) +
                  (e_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.re -
                   mb_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.im)) +
                 (b_re * 0.0 - nb_c51_idx_0_tmp_tmp * 2.0)) -
                (re * b_c30_tmp_tmp.re -
                 c51_idx_0_tmp_tmp_tmp * b_c30_tmp_tmp.im)) +
               (c_re * 0.0 - f_c51_idx_0_tmp_tmp * 2.0)) +
              (f_re * 0.0 - im * 2.0)) +
             (g_re * b_c30_tmp_tmp.re - b_im * b_c30_tmp_tmp.im)) +
            (d_re * 0.0 - c_im * 2.0)) +
           (e_re * b_c30_tmp_tmp.re - p_c51_idx_0_tmp_tmp * b_c30_tmp_tmp.im)) +
          (jb_c51_idx_0_tmp_tmp * 0.0 - ib_c51_idx_0_tmp_tmp * 2.0)) -
         (q_c51_idx_0_tmp_tmp * 0.0 - pb_c51_idx_0_tmp_tmp * 2.0)) -
        (h_re * b_c30_tmp_tmp.re - b_sc5_tmp_tmp * b_c30_tmp_tmp.im);
    scr0 =
        ((((((((((((((h_c51_idx_0_tmp_tmp * 2.0 + kb_c51_idx_0_tmp_tmp * 0.0) -
                     7482.25 * dc31.im) -
                    6479.818577466116) -
                   (g_c51_idx_0_tmp_tmp * 2.0 + lb_c51_idx_0_tmp_tmp * 0.0)) +
                  (e_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.im +
                   mb_c51_idx_0_tmp_tmp * b_c10_tmp_tmp.re)) +
                 (b_re * 2.0 + nb_c51_idx_0_tmp_tmp * 0.0)) -
                (re * b_c30_tmp_tmp.im +
                 c51_idx_0_tmp_tmp_tmp * b_c30_tmp_tmp.re)) +
               (c_re * 2.0 + f_c51_idx_0_tmp_tmp * 0.0)) +
              (f_re * 2.0 + im * 0.0)) +
             (g_re * b_c30_tmp_tmp.im + b_im * b_c30_tmp_tmp.re)) +
            (d_re * 2.0 + c_im * 0.0)) +
           (e_re * b_c30_tmp_tmp.im + p_c51_idx_0_tmp_tmp * b_c30_tmp_tmp.re)) +
          (jb_c51_idx_0_tmp_tmp * 2.0 + ib_c51_idx_0_tmp_tmp * 0.0)) -
         (q_c51_idx_0_tmp_tmp * 2.0 + pb_c51_idx_0_tmp_tmp * 0.0)) -
        (h_re * b_c30_tmp_tmp.im + b_sc5_tmp_tmp * b_c30_tmp_tmp.re);
    if (scr0 == 0.0) {
      if (sc4 == 0.0) {
        dc1.re = cc4 / cphi;
        dc1.im = 0.0;
      } else if (cc4 == 0.0) {
        dc1.re = 0.0;
        dc1.im = sc4 / cphi;
      } else {
        dc1.re = cc4 / cphi;
        dc1.im = sc4 / cphi;
      }
    } else if (cphi == 0.0) {
      if (cc4 == 0.0) {
        dc1.re = sc4 / scr0;
        dc1.im = 0.0;
      } else if (sc4 == 0.0) {
        dc1.re = 0.0;
        dc1.im = -(cc4 / scr0);
      } else {
        dc1.re = sc4 / scr0;
        dc1.im = -(cc4 / scr0);
      }
    } else {
      ccr0 = fabs(cphi);
      ccp0 = fabs(scr0);
      if (ccr0 > ccp0) {
        scp0 = scr0 / cphi;
        ccp0 = cphi + scp0 * scr0;
        dc1.re = (cc4 + scp0 * sc4) / ccp0;
        dc1.im = (sc4 - scp0 * cc4) / ccp0;
      } else if (ccp0 == ccr0) {
        if (cphi > 0.0) {
          scp0 = 0.5;
        } else {
          scp0 = -0.5;
        }
        if (scr0 > 0.0) {
          ccp0 = 0.5;
        } else {
          ccp0 = -0.5;
        }
        dc1.re = (cc4 * scp0 + sc4 * ccp0) / ccr0;
        dc1.im = (sc4 * scp0 - cc4 * ccp0) / ccr0;
      } else {
        scp0 = cphi / scr0;
        ccp0 = scr0 + scp0 * cphi;
        dc1.re = (scp0 * cc4 + sc4) / ccp0;
        dc1.im = (scp0 * sc4 - cc4) / ccp0;
      }
    }
    b_log(&dc1);
    i_re = dc.re * 0.0 - dc.im;
    j_re = dc1.re * 0.0 - dc1.im;
    w1_idx_0 =
        0.766044443118978 * cos((1.298210328476112 - k_re) - 1.298210328476112);
    w1_idx_2 =
        0.766044443118978 * sin((1.298210328476112 - k_re) - 1.298210328476112);
    w1_idx_1 =
        0.766044443118978 * cos((1.298210328476112 - l_re) - 1.298210328476112);
    w1_idx_3 =
        0.766044443118978 * sin((1.298210328476112 - l_re) - 1.298210328476112);
    ccp0 = OBL_tmp_tmp * 0.0 - d_OBL_tmp_tmp * c_OBL_tmp_tmp;
    scp0 = 0.0 * c_OBL_tmp_tmp + OBL_tmp_tmp * d_OBL_tmp_tmp;
    v1_idx_0 = -(0.49999999999999994 * (6.123233995736766E-17 * ccp0 - scp0) -
                 b_OBL_tmp_tmp * 0.86602540378443871);
    scr0 = OBL_tmp_tmp + 0.0 * d_OBL_tmp_tmp * c_OBL_tmp_tmp;
    ccr0 = c_OBL_tmp_tmp - OBL_tmp_tmp * 0.0 * d_OBL_tmp_tmp;
    cphi = b_OBL_tmp_tmp * 0.86602540378443871 * 0.0;
    v1_idx_1 =
        0.49999999999999994 * (6.123233995736766E-17 * scr0 - ccr0) + cphi;
    sc4 = b_OBL_tmp_tmp * OBL_tmp_tmp;
    gb_c51_idx_0_tmp_tmp =
        0.49999999999999994 *
            (6.123233995736766E-17 * b_OBL_tmp_tmp * c_OBL_tmp_tmp + sc4) -
        0.86602540378443871 * d_OBL_tmp_tmp;
    w2_idx_0 =
        0.766044443118978 * cos((1.52502572060903 - m_re) - 1.52502572060903);
    w2_idx_2 =
        0.766044443118978 * sin((1.52502572060903 - m_re) - 1.52502572060903);
    w2_idx_1 =
        0.766044443118978 * cos((1.52502572060903 - n_re) - 1.52502572060903);
    w2_idx_3 =
        0.766044443118978 * sin((1.52502572060903 - n_re) - 1.52502572060903);
    fb_c51_idx_0_tmp_tmp = b_OBL_tmp_tmp * 0.86602540378443871;
    v2[0] = -(0.49999999999999994 *
                  (-0.49999999999999978 * ccp0 + 0.86602540378443871 * scp0) -
              fb_c51_idx_0_tmp_tmp);
    v2[1] = 0.49999999999999994 *
                (-0.49999999999999978 * scr0 + 0.86602540378443871 * ccr0) +
            cphi;
    cc4 = 0.86602540378443871 * d_OBL_tmp_tmp;
    hb_c51_idx_0_tmp_tmp =
        0.49999999999999994 *
            (-0.49999999999999978 * b_OBL_tmp_tmp * c_OBL_tmp_tmp -
             sc4 * 0.86602540378443871) -
        cc4;
    c51_idx_0_tmp_tmp = sin((0.30696770204475443 - i_re) - 0.30696770204475443);
    b_c51_idx_0_tmp_tmp =
        cos((0.30696770204475443 - i_re) - 0.30696770204475443);
    c_c51_idx_0_tmp_tmp =
        sin((0.30696770204475443 - j_re) - 0.30696770204475443);
    d_c51_idx_0_tmp_tmp =
        cos((0.30696770204475443 - j_re) - 0.30696770204475443);
    w3[0] = -c51_idx_0_tmp_tmp;
    w3[2] = b_c51_idx_0_tmp_tmp;
    w3[4] = 0.0;
    w3[1] = -c_c51_idx_0_tmp_tmp;
    w3[3] = d_c51_idx_0_tmp_tmp;
    w3[5] = 0.0;
    /* %此向量本来在c3坐标系中，为了便于下面的干涉检查计算，做统一坐标系处理 */
    v3_idx_0 = -(0.49999999999999994 *
                     (0.50000000000000011 * ccp0 - -0.8660254037844386 * scp0) -
                 fb_c51_idx_0_tmp_tmp);
    cphi += 0.49999999999999994 *
            (0.50000000000000011 * scr0 - -0.8660254037844386 * ccr0);
    v3_idx_2 = 0.49999999999999994 *
                   (sc4 * -0.8660254037844386 +
                    b_OBL_tmp_tmp * c_OBL_tmp_tmp * 0.50000000000000011) -
               cc4;
    /* 此向量本来在c3坐标系中，为了便于下面的干涉检查计算，做统一坐标系处理 */
    /*  eq1=w3(1)*v3(1)+w3(2)*v3(2)+w3(3)*v3(3)-R^2*cos(gama); */
    /*  v1=[OBL(1),OBL(2),OBL(3)]; */
    /*  v2=[OBR(1),OBR(2),OBR(3)]; */
    /*  v3=[OBM(1),OBM(2),OBM(3)]; */
    /*  %
     * w1=[sin(alpha)*cos(c1+c0L),sin(alpha)*sin(c1+c0L),cos(alpha)];OAL=[R*sin(alpha)*cos(c1+c0L),R*sin(alpha)*sin(c1+c0L),R*cos(alpha)];
     */
    /*  % w2=[sin(alpha)*cos(c2+c0R),sin(alpha)*sin(c2+c0R),-cos(alpha)]; */
    /*  % w3=OAM=[cos(c3+c0M),sin(c3+c0M),0]; */
    /*  A1=-v1(1)*sin(alpha)+v1(3)*cos(alpha)-cos(gama); */
    /*  B1=2*v1(2)*sin(alpha); */
    /*  C1=v1(1)*sin(alpha)+v1(3)*cos(alpha)-cos(gama); */
    /*   */
    /*  A2=-v2(1)*sin(alpha)-v2(3)*cos(alpha)-cos(gama); */
    /*  B2=2*v2(2)*sin(alpha); */
    /*  C2=v2(1)*sin(alpha)-v2(3)*cos(alpha)-cos(gama); */
    /*   */
    /*  A3=-v3(1)-cos(gama); */
    /*  B3=2*v3(2); */
    /*  C3=v3(1)-cos(gama); */
    /*   */
    /*  Index1=B1^2-4*A1*C1; */
    /*  Index2=B2^2-4*A2*C2; */
    /*  Index3=B3^2-4*A3*C3; */
    guard1 = false;
    guard2 = false;
    guard3 = false;
    *flag = 1.0;
    if (((0.0 - w1_idx_2) * v1_idx_0 + w1_idx_0 * v1_idx_1) +
            (0.0 * w1_idx_2 - w1_idx_0 * 0.0) * gb_c51_idx_0_tmp_tmp >=
        0.0) {
      scr0 = 1.298210328476112 - k_re;
      guard3 = true;
    } else if (((0.0 - w1_idx_3) * v1_idx_0 + w1_idx_1 * v1_idx_1) +
                   (0.0 * w1_idx_3 - w1_idx_1 * 0.0) * gb_c51_idx_0_tmp_tmp >=
               0.0) {
      scr0 = 1.298210328476112 - l_re;
      guard3 = true;
    } else {
      *flag = 0.0;
      printf("interference constraint not satisfied\n");
    }
    if (guard3) {
      if (((-0.0 - w2_idx_2) * v2[0] + w2_idx_0 * v2[1]) +
              (0.0 * w2_idx_2 - w2_idx_0 * 0.0) * hb_c51_idx_0_tmp_tmp >=
          0.0) {
        scp0 = 1.52502572060903 - m_re;
        guard2 = true;
      } else if (((-0.0 - w2_idx_3) * v2[0] + w2_idx_1 * v2[1]) +
                     (0.0 * w2_idx_3 - w2_idx_1 * 0.0) * hb_c51_idx_0_tmp_tmp >=
                 0.0) {
        scp0 = 1.52502572060903 - n_re;
        guard2 = true;
      } else {
        *flag = 0.0;
        printf("interference constraint not satisfied\n");
      }
    }
    if (guard2) {
      if (((b_c51_idx_0_tmp_tmp * v3_idx_2 - cphi * 0.0) * 0.0 +
           (v3_idx_0 * 0.0 - -c51_idx_0_tmp_tmp * v3_idx_2) * 0.0) +
              (-c51_idx_0_tmp_tmp * cphi - v3_idx_0 * b_c51_idx_0_tmp_tmp) <=
          0.0) {
        ccp0 = 0.30696770204475443 - i_re;
        IM = 0;
        guard1 = true;
      } else if (((v3_idx_2 * d_c51_idx_0_tmp_tmp - cphi * 0.0) * 0.0 +
                  (v3_idx_0 * 0.0 - -c_c51_idx_0_tmp_tmp * v3_idx_2) * 0.0) +
                     (cphi * -c_c51_idx_0_tmp_tmp -
                      v3_idx_0 * d_c51_idx_0_tmp_tmp) <=
                 0.0) {
        ccp0 = 0.30696770204475443 - j_re;
        IM = 1;
        guard1 = true;
      } else {
        *flag = 0.0;
        printf("interference constraint not satisfied\n");
      }
    }
    if (guard1) {
      if (scr0 > 3.1415926535897931) {
        scr0 -= 6.2831853071795862;
      } else if (scp0 > 3.1415926535897931) {
        scp0 -= 6.2831853071795862;
      }
      OBL[0] = 86.5 * b_OBL_tmp_tmp;
      OBL[1] = 86.5 * b_OBL_tmp_tmp * 0.0;
      OBL[2] = -86.5 * d_OBL_tmp_tmp;
      v2[0] = cphi * OBL[2] - OBL[1] * v3_idx_2;
      v2[1] = OBL[0] * v3_idx_2 - v3_idx_0 * OBL[2];
      v2[2] = v3_idx_0 * OBL[1] - OBL[0] * cphi;
      ccr0 = w3[IM + 2];
      OBL[0] = ccr0 * v3_idx_2 - cphi * 0.0;
      OBL[1] = v3_idx_0 * 0.0 - w3[IM] * v3_idx_2;
      OBL[2] = w3[IM] * cphi - v3_idx_0 * ccr0;
      if (((OBL[0] * v2[0] + OBL[1] * v2[1]) + OBL[2] * v2[2]) / b_norm(OBL) /
              b_norm(v2) >=
          -0.64278760968653936) {
        c[0] = scr0 + cps;
        c[1] = scp0 + cps;
        c[2] = ccp0 + cps;
      } else {
        c[0] = 0.0;
        c[1] = 0.0;
        c[2] = 0.0;
      }
      
      /* 姿态约束 */
      if ((crs > 0.26179938779914941) || (crs < -0.87266462599716477) ||
          (cps > 2.8274333882308138) || (cps < -0.47123889803846897) ||
          (cys > 1.0471975511965976) || (cys < -1.0122909661567112) ||
          (crw > 0.52359877559829882) || (crw < -0.3490658503988659) ||
          (cpw > 0.43633231299858238) || (cpw < -0.52359877559829882) ||
          (cyw > 1.0471975511965976) || (cyw < -1.0122909661567112) ||
          (c4 > 2.1816615649929116) || (c4 < 0.0)) {
        *flag = 0.0;
        printf("orientation constraint not satisfied\n");
      }
      /* 肩耦合约束 */
      scr0 = sin(cps);
      scp0 = cos(cps);
      ccr0 = scp0 * OBL_tmp_tmp;
      ccp0 = OBL_tmp_tmp * scr0;
      sc4 = ccp0 - scp0 * d_OBL_tmp_tmp * c_OBL_tmp_tmp;
      cc4 = scr0 * c_OBL_tmp_tmp + ccr0 * d_OBL_tmp_tmp;
      cphi = scp0 * b_OBL_tmp_tmp * 0.86602540378443871;
      OBL[0] =
          -(0.49999999999999994 * (6.123233995736766E-17 * sc4 - cc4) - cphi);
      v3_idx_2 = ccr0 + scr0 * d_OBL_tmp_tmp * c_OBL_tmp_tmp;
      scp0 = scp0 * c_OBL_tmp_tmp - ccp0 * d_OBL_tmp_tmp;
      ccp0 = fb_c51_idx_0_tmp_tmp * scr0;
      scr0 = 0.49999999999999994 *
                 (0.50000000000000011 * v3_idx_2 - -0.8660254037844386 * scp0) +
             ccp0;
      v2[0] = -(0.49999999999999994 *
                    (-0.49999999999999978 * sc4 + 0.86602540378443871 * cc4) -
                cphi);
      /*  w1=[sin(alpha)*cos(c1+c0L),sin(alpha)*sin(c1+c0L),cos(alpha)];OAL=[R*sin(alpha)*cos(c1+c0L),R*sin(alpha)*sin(c1+c0L),R*cos(alpha)];
       */
      /*  w2=[sin(alpha)*cos(c2+c0R),sin(alpha)*sin(c2+c0R),-cos(alpha)]; */
      /*  w3=OAM=[cos(c3+c0M),sin(c3+c0M),0]; */
      ccr0 = 2.0 *
             (0.49999999999999994 * (6.123233995736766E-17 * v3_idx_2 - scp0) +
              ccp0) *
             0.766044443118978;
      scp0 = 2.0 *
             (0.49999999999999994 * (-0.49999999999999978 * v3_idx_2 +
                                     0.86602540378443871 * scp0) +
              ccp0) *
             0.766044443118978;
      ccp0 = 2.0 * (0.49999999999999994 * (0.50000000000000011 * sc4 -
                                           -0.8660254037844386 * cc4) -
                    cphi);
      if ((ccr0 * ccr0 - 4.0 *
                             ((-OBL[0] * 0.766044443118978 +
                               gb_c51_idx_0_tmp_tmp * 0.64278760968653936) -
                              0.50000000000000011) *
                             ((OBL[0] * 0.766044443118978 +
                               gb_c51_idx_0_tmp_tmp * 0.64278760968653936) -
                              0.50000000000000011) <
           0.0) ||
          (scp0 * scp0 - 4.0 *
                             ((-v2[0] * 0.766044443118978 -
                               hb_c51_idx_0_tmp_tmp * 0.64278760968653936) -
                              0.50000000000000011) *
                             ((v2[0] * 0.766044443118978 -
                               hb_c51_idx_0_tmp_tmp * 0.64278760968653936) -
                              0.50000000000000011) <
           0.0) ||
          (ccp0 * ccp0 - 4.0 * (-scr0 - 0.50000000000000011) *
                             (scr0 - 0.50000000000000011) <
           0.0)) {
        *flag = 0.0;
        printf("shoulder constraint not satisfied\n");
      }
      /* 腕肘耦合约束 */
      c51_idx_0_tmp_tmp = c51_idx_0 + c4;
      b_c51_idx_0_tmp_tmp = c61_idx_0 + c4;
      if ((fabs(c51_idx_0 - c61_idx_0) > 0.69813170079773179) ||
          (c51_idx_0 > 0.48869219055841229) ||
          (c61_idx_0 > 0.48869219055841229) ||
          (c51_idx_0 < -0.87266462599716477) ||
          (c61_idx_0 < -0.87266462599716477)) {
        *flag = 0.0;
        printf("wrist-elbow coupling constraint not satisfied\n");
      } else {
        
        // if (c51_idx_0_tmp_tmp > 3.1415926535897931) {
        //   *flag = 0.0;
        //   printf("wrist-elbow coupling constraint not satisfied2\n");
        // } else {
          
        //   if ((b_c51_idx_0_tmp_tmp > 3.1415926535897931) ||
        //       (c51_idx_0_tmp_tmp < 0.0) || (b_c51_idx_0_tmp_tmp < 0.0)) {
        //     *flag = 0.0;
        //     printf("wrist-elbow coupling constraint not satisfied3\n");
        //   }
        // }
      }
      /*  try */
      /*      T=FK_7DOF(C); */
      /*  catch */
      /*      flag = 0; */
      /*      T=zeros(4,4); */
      /*  end */
      /*  T(1:3,1:3); */
      /*  sum(sum(abs(T(1:3,1:3)-T17)))+abs(T(1,4)-Px/1000)+abs(T(2,4)-Py/1000)+abs(T(3,4)-Pz/1000);
       */
      /*  if(sum(sum(abs(T(1:3,1:3)-T17)))+abs(T(1,4)-Px/1000)+abs(T(2,4)-Py/1000)+abs(T(3,4)-Pz/1000)>tol)
       */
      /*      flag=0; */
      /*  end */
      c[3] = c4;
      c[4] = c51_idx_0;
      c[5] = c61_idx_0;
      c[6] = cyw;
    }
}

/* End of code generation (IK_7DOF.c) */

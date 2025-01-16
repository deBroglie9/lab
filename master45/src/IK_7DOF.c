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
#include "IK_7DOF.h"
#include "IK_7DOF_data.h"
#include "IK_7DOF_initialize.h"
#include "exp.h"
#include "log.h"
#include "norm.h"
#include "power.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */
void IK_7DOF(const double R[16], double phi, double l1, double l2, double Px,
             double Py, double Pz, double *c1, double *c2, double *c3,
             double *c4, double *c5, double *c6, double *c7)
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
  double OBM[3];
  double v1[3];
  double OBL_tmp;
  double OBL_tmp_tmp;
  double ab_scp0_idx_0_tmp;
  double ab_scp0_idx_0_tmp_tmp;
  double b_OBL_tmp_tmp;
  double b_im;
  double b_re;
  double b_sc5_tmp_tmp;
  double b_scp0_idx_0_tmp;
  double b_scp0_idx_0_tmp_tmp;
  double bb_scp0_idx_0_tmp_tmp;
  double c_OBL_tmp_tmp;
  double c_im;
  double c_re;
  double c_sc5_tmp_tmp;
  double c_scp0_idx_0_tmp;
  double c_scp0_idx_0_tmp_tmp;
  double cb_scp0_idx_0_tmp_tmp;
  double cc4;
  double cc4_tmp;
  double ccr0;
  double cp01_idx_0;
  double cp02_idx_0;
  double cphi;
  double cps;
  double crs;
  double crw;
  double cys;
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
  double d4;
  double d5;
  double d6;
  double d7;
  double d8;
  double d9;
  double d_im;
  double d_re;
  double d_sc5_tmp_tmp;
  double d_scp0_idx_0_tmp;
  double d_scp0_idx_0_tmp_tmp;
  double db_scp0_idx_0_tmp_tmp;
  double e_im;
  double e_re;
  double e_sc5_tmp_tmp;
  double e_scp0_idx_0_tmp;
  double e_scp0_idx_0_tmp_tmp;
  double eb_scp0_idx_0_tmp_tmp;
  double f_im;
  double f_re;
  double f_sc5_tmp_tmp;
  double f_scp0_idx_0_tmp;
  double f_scp0_idx_0_tmp_tmp;
  double fb_scp0_idx_0_tmp_tmp;
  double g_re;
  double g_scp0_idx_0_tmp;
  double g_scp0_idx_0_tmp_tmp;
  double gb_scp0_idx_0_tmp_tmp;
  double h_re;
  double h_scp0_idx_0_tmp;
  double h_scp0_idx_0_tmp_tmp;
  double hb_scp0_idx_0_tmp_tmp;
  double i_re;
  double i_scp0_idx_0_tmp;
  double i_scp0_idx_0_tmp_tmp;
  double ib_scp0_idx_0_tmp_tmp;
  double im;
  double j_re;
  double j_scp0_idx_0_tmp;
  double j_scp0_idx_0_tmp_tmp;
  double jb_scp0_idx_0_tmp_tmp;
  double k_re;
  double k_scp0_idx_0_tmp;
  double k_scp0_idx_0_tmp_tmp;
  double kb_scp0_idx_0_tmp_tmp;
  double l_re;
  double l_scp0_idx_0_tmp;
  double l_scp0_idx_0_tmp_tmp;
  double lb_scp0_idx_0_tmp_tmp;
  double m_re;
  double m_scp0_idx_0_tmp;
  double m_scp0_idx_0_tmp_tmp;
  double mb_scp0_idx_0_tmp_tmp;
  double n_re;
  double n_scp0_idx_0_tmp;
  double n_scp0_idx_0_tmp_tmp;
  double nb_scp0_idx_0_tmp_tmp;
  double o_re;
  double o_scp0_idx_0_tmp;
  double o_scp0_idx_0_tmp_tmp;
  double ob_scp0_idx_0_tmp_tmp;
  double p_re;
  double p_scp0_idx_0_tmp;
  double p_scp0_idx_0_tmp_tmp;
  double q_scp0_idx_0_tmp;
  double q_scp0_idx_0_tmp_tmp;
  double r_scp0_idx_0_tmp;
  double r_scp0_idx_0_tmp_tmp;
  double re;
  double s_scp0_idx_0_tmp;
  double s_scp0_idx_0_tmp_tmp;
  double sc4;
  double sc5_tmp_tmp;
  double scp0_idx_0_tmp;
  double scp0_idx_0_tmp_tmp;
  double scp0_idx_0_tmp_tmp_tmp;
  double scr0;
  double t_scp0_idx_0_tmp;
  double t_scp0_idx_0_tmp_tmp;
  double u_scp0_idx_0_tmp;
  double u_scp0_idx_0_tmp_tmp;
  double v2_idx_0;
  double v2_idx_1;
  double v2_idx_2;
  double v3_idx_0;
  double v_scp0_idx_0_tmp;
  double v_scp0_idx_0_tmp_tmp;
  double w1_idx_1;
  double w1_idx_2;
  double w1_idx_3;
  double w2_idx_0;
  double w2_idx_1;
  double w2_idx_2;
  double w2_idx_3;
  double w_scp0_idx_0_tmp;
  double w_scp0_idx_0_tmp_tmp;
  double x_scp0_idx_0_tmp;
  double x_scp0_idx_0_tmp_tmp;
  double y_scp0_idx_0_tmp;
  double y_scp0_idx_0_tmp_tmp;
  int IL;
  int IM;
  int a_tmp_tmp;
  int aoffset;
  int coffset;
  if (!isInitialized_IK_7DOF) {
    IK_7DOF_initialize();
  }
  /*  l1=320;l2=235; */
  /*  phi=-14.05*pi/180; */
  /*  T17=[-0.0550   -0.9904    0.1270  316.1736; */
  /*        0.9179   -0.0001    0.3967  285.6146; */
  /*       -0.3929    0.1384    0.9091   46.9064; */
  /*             0         0         0    1.0000]; */
  /*  Px=T17(1,4); */
  /*  Py=T17(2,4); */
  /*  Pz=T17(3,4); */
  crw = Px * Px;
  cphi = l2 * l2;
  cp01_idx_0 = l1 * l1;
  cc4_tmp = (crw + Py * Py) + Pz * Pz;
  cc4 = ((cc4_tmp - cp01_idx_0) - cphi) / (2.0 * l1 * l2);
  cp02_idx_0 = cc4 * cc4;
  sc4 = sqrt(1.0 - cp02_idx_0);
  scr0 = -Pz / (l1 + l2 * cc4);
  ccr0 = sqrt(1.0 - scr0 * scr0);
  /*  T150=[ccp0,-scp0,0,0;scp0,ccp,0,0;0,0,1,0;0,0,0,1]*[ccr0,0,scr0,0;0,1,0,0;-scr0,0,ccr0,0;0,0,0,1]*[1,0,0,0;0,1,0,0;0,0,1,0;0,0,0,1]*[1,0,0,l1;0,1,0,0;0,0,1,0;0,0,0,1]*[cc4,-sc4,0,0;sc4,cc4,0,0;0,0,1,0;0,0,0,1]*[1,0,0,l2;0,1,0,0;0,0,1,0;0,0,0,1];
   */
  /*   */
  /*  eq1=T150(1,4)-Px; */
  /*  eq2=scp0^2+ccp0^2-1; */
  /*   */
  /*  [scp0,ccp0]=solve(eq1,eq2,[scp0,ccp0]); */
  scp0_idx_0_tmp = ccr0 * ccr0;
  b_scp0_idx_0_tmp = cp02_idx_0 * scp0_idx_0_tmp * cphi;
  c_scp0_idx_0_tmp = 2.0 * cc4 * scp0_idx_0_tmp * l1 * l2;
  scp0_idx_0_tmp *= cp01_idx_0;
  d_scp0_idx_0_tmp = cphi * (sc4 * sc4);
  scp0_idx_0_tmp_tmp = l2 * sc4;
  b_scp0_idx_0_tmp_tmp = Px * ccr0 * l1;
  c_scp0_idx_0_tmp_tmp =
      scp0_idx_0_tmp_tmp *
      sqrt((((-crw + b_scp0_idx_0_tmp) + c_scp0_idx_0_tmp) + scp0_idx_0_tmp) +
           d_scp0_idx_0_tmp);
  d_scp0_idx_0_tmp_tmp = Px * cc4 * ccr0 * l2;
  e_scp0_idx_0_tmp =
      (c_scp0_idx_0_tmp_tmp + b_scp0_idx_0_tmp_tmp) + d_scp0_idx_0_tmp_tmp;
  scp0_idx_0_tmp = ((b_scp0_idx_0_tmp + c_scp0_idx_0_tmp) + scp0_idx_0_tmp) +
                   d_scp0_idx_0_tmp;
  b_scp0_idx_0_tmp = ccr0 * l1;
  c_scp0_idx_0_tmp = cc4 * ccr0 * l2;
  *c5 = ((b_scp0_idx_0_tmp * e_scp0_idx_0_tmp / scp0_idx_0_tmp - Px) +
         c_scp0_idx_0_tmp * e_scp0_idx_0_tmp / scp0_idx_0_tmp) /
        scp0_idx_0_tmp_tmp;
  cphi = (b_scp0_idx_0_tmp_tmp - c_scp0_idx_0_tmp_tmp) + d_scp0_idx_0_tmp_tmp;
  *c6 = e_scp0_idx_0_tmp / scp0_idx_0_tmp;
  cp01_idx_0 = acos(*c6);
  cp02_idx_0 = asin(*c5);
  if ((!(cp01_idx_0 >= -0.43633231299858238)) ||
      (!(cp01_idx_0 <= 3.1415926535897931)) ||
      (!(cp02_idx_0 >= -0.43633231299858238)) ||
      (!(cp02_idx_0 <= 3.1415926535897931))) {
    *c6 = cphi / scp0_idx_0_tmp;
    *c5 = ((b_scp0_idx_0_tmp * cphi / scp0_idx_0_tmp - Px) +
           c_scp0_idx_0_tmp * cphi / scp0_idx_0_tmp) /
          scp0_idx_0_tmp_tmp;
  }
  Pskew[0] = *c6;
  Pskew[3] = -*c5;
  Pskew[6] = 0.0;
  Pskew[1] = *c5;
  Pskew[4] = *c6;
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
  for (IL = 0; IL < 3; IL++) {
    e_scp0_idx_0_tmp_tmp = Pskew[IL];
    f_scp0_idx_0_tmp_tmp = Pskew[IL + 3];
    IM = (int)Pskew[IL + 6];
    for (coffset = 0; coffset < 3; coffset++) {
      Aw[IL + 3 * coffset] = (e_scp0_idx_0_tmp_tmp * Cs[3 * coffset] +
                              f_scp0_idx_0_tmp_tmp * Cs[3 * coffset + 1]) +
                             (double)IM * Cs[3 * coffset + 2];
    }
    e_scp0_idx_0_tmp_tmp = Aw[IL];
    f_scp0_idx_0_tmp_tmp = Aw[IL + 3];
    g_scp0_idx_0_tmp_tmp = Aw[IL + 6];
    for (IM = 0; IM < 3; IM++) {
      R130[IL + 3 * IM] = (e_scp0_idx_0_tmp_tmp * (double)b[3 * IM] +
                           f_scp0_idx_0_tmp_tmp * (double)b[3 * IM + 1]) +
                          g_scp0_idx_0_tmp_tmp * (double)b[3 * IM + 2];
    }
  }
  /*  Pskew=[0,-Pz/(Px^2+Py^2+Pz^2)^0.5,Py/(Px^2+Py^2+Pz^2)^0.5;Pz/(Px^2+Py^2+Pz^2)^0.5,0,-Px/(Px^2+Py^2+Pz^2)^0.5;-Py/(Px^2+Py^2+Pz^2)^0.5,Px/(Px^2+Py^2+Pz^2)^0.5,0];
   */
  cp02_idx_0 = sqrt(cc4_tmp);
  Pskew[0] = 0.0 / cp02_idx_0;
  Pskew[3] = -Pz / cp02_idx_0;
  Pskew[6] = Py / cp02_idx_0;
  Pskew[1] = Pz / cp02_idx_0;
  Pskew[4] = 0.0 / cp02_idx_0;
  Pskew[7] = -Px / cp02_idx_0;
  Pskew[2] = -Py / cp02_idx_0;
  Pskew[5] = Px / cp02_idx_0;
  Pskew[8] = 0.0 / cp02_idx_0;
  for (IL = 0; IL < 3; IL++) {
    e_scp0_idx_0_tmp_tmp = Pskew[IL + 3];
    f_scp0_idx_0_tmp_tmp = Pskew[IL + 6];
    for (IM = 0; IM < 3; IM++) {
      coffset = 3 * IM + 1;
      aoffset = 3 * IM + 2;
      a_tmp_tmp = IL + 3 * IM;
      a_tmp[a_tmp_tmp] =
          (Pskew[IL] * Pskew[3 * IM] + e_scp0_idx_0_tmp_tmp * Pskew[coffset]) +
          f_scp0_idx_0_tmp_tmp * Pskew[aoffset];
      As[a_tmp_tmp] =
          (Pskew[IL] * R130[3 * IM] + e_scp0_idx_0_tmp_tmp * R130[coffset]) +
          f_scp0_idx_0_tmp_tmp * R130[aoffset];
    }
  }
  for (IL = 0; IL < 9; IL++) {
    Pskew[IL] = -a_tmp[IL];
  }
  for (IL = 0; IL < 3; IL++) {
    e_scp0_idx_0_tmp_tmp = Pskew[IL];
    f_scp0_idx_0_tmp_tmp = Pskew[IL + 3];
    g_scp0_idx_0_tmp_tmp = Pskew[IL + 6];
    for (IM = 0; IM < 3; IM++) {
      Bs[IL + 3 * IM] = (e_scp0_idx_0_tmp_tmp * R130[3 * IM] +
                         f_scp0_idx_0_tmp_tmp * R130[3 * IM + 1]) +
                        g_scp0_idx_0_tmp_tmp * R130[3 * IM + 2];
    }
  }
  for (IL = 0; IL < 9; IL++) {
    a_tmp[IL] += (double)b[IL];
  }
  cp02_idx_0 = sin(phi);
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
  for (IL = 0; IL < 3; IL++) {
    e_scp0_idx_0_tmp_tmp = a_tmp[IL];
    f_scp0_idx_0_tmp_tmp = a_tmp[IL + 3];
    g_scp0_idx_0_tmp_tmp = a_tmp[IL + 6];
    for (IM = 0; IM < 3; IM++) {
      Cs[IL + 3 * IM] = (e_scp0_idx_0_tmp_tmp * R130[3 * IM] +
                         f_scp0_idx_0_tmp_tmp * R130[3 * IM + 1]) +
                        g_scp0_idx_0_tmp_tmp * R130[3 * IM + 2];
    }
    Pskew[3 * IL + 2] = a[IL];
  }
  R130[0] = R[0];
  R130[3] = R[4];
  R130[6] = R[8];
  R130[1] = R[1];
  R130[4] = R[5];
  R130[7] = R[9];
  R130[2] = R[2];
  R130[5] = R[6];
  R130[8] = R[10];
  for (IL = 0; IL < 3; IL++) {
    coffset = IL * 3;
    e_scp0_idx_0_tmp_tmp = As[IL];
    f_scp0_idx_0_tmp_tmp = As[IL + 3];
    g_scp0_idx_0_tmp_tmp = As[IL + 6];
    for (IM = 0; IM < 3; IM++) {
      aoffset = IM * 3;
      a_tmp[coffset + IM] = (Pskew[aoffset] * e_scp0_idx_0_tmp_tmp +
                             Pskew[aoffset + 1] * f_scp0_idx_0_tmp_tmp) +
                            Pskew[aoffset + 2] * g_scp0_idx_0_tmp_tmp;
    }
  }
  for (IL = 0; IL < 3; IL++) {
    e_scp0_idx_0_tmp_tmp = a_tmp[IL];
    f_scp0_idx_0_tmp_tmp = a_tmp[IL + 3];
    g_scp0_idx_0_tmp_tmp = a_tmp[IL + 6];
    for (IM = 0; IM < 3; IM++) {
      Aw[IL + 3 * IM] = (e_scp0_idx_0_tmp_tmp * R130[3 * IM] +
                         f_scp0_idx_0_tmp_tmp * R130[3 * IM + 1]) +
                        g_scp0_idx_0_tmp_tmp * R130[3 * IM + 2];
    }
  }
  for (IL = 0; IL < 3; IL++) {
    coffset = IL * 3;
    e_scp0_idx_0_tmp_tmp = Bs[IL];
    f_scp0_idx_0_tmp_tmp = Bs[IL + 3];
    g_scp0_idx_0_tmp_tmp = Bs[IL + 6];
    for (IM = 0; IM < 3; IM++) {
      aoffset = IM * 3;
      a_tmp[coffset + IM] = (Pskew[aoffset] * e_scp0_idx_0_tmp_tmp +
                             Pskew[aoffset + 1] * f_scp0_idx_0_tmp_tmp) +
                            Pskew[aoffset + 2] * g_scp0_idx_0_tmp_tmp;
    }
  }
  for (IL = 0; IL < 3; IL++) {
    e_scp0_idx_0_tmp_tmp = a_tmp[IL];
    f_scp0_idx_0_tmp_tmp = a_tmp[IL + 3];
    g_scp0_idx_0_tmp_tmp = a_tmp[IL + 6];
    for (IM = 0; IM < 3; IM++) {
      Bw[IL + 3 * IM] = (e_scp0_idx_0_tmp_tmp * R130[3 * IM] +
                         f_scp0_idx_0_tmp_tmp * R130[3 * IM + 1]) +
                        g_scp0_idx_0_tmp_tmp * R130[3 * IM + 2];
    }
  }
  for (IL = 0; IL < 3; IL++) {
    coffset = IL * 3;
    e_scp0_idx_0_tmp_tmp = Cs[IL];
    f_scp0_idx_0_tmp_tmp = Cs[IL + 3];
    g_scp0_idx_0_tmp_tmp = Cs[IL + 6];
    for (IM = 0; IM < 3; IM++) {
      aoffset = IM * 3;
      a_tmp[coffset + IM] = (Pskew[aoffset] * e_scp0_idx_0_tmp_tmp +
                             Pskew[aoffset + 1] * f_scp0_idx_0_tmp_tmp) +
                            Pskew[aoffset + 2] * g_scp0_idx_0_tmp_tmp;
    }
  }
  for (IL = 0; IL < 3; IL++) {
    e_scp0_idx_0_tmp_tmp = a_tmp[IL];
    f_scp0_idx_0_tmp_tmp = a_tmp[IL + 3];
    g_scp0_idx_0_tmp_tmp = a_tmp[IL + 6];
    for (IM = 0; IM < 3; IM++) {
      Pskew[IL + 3 * IM] = (e_scp0_idx_0_tmp_tmp * R130[3 * IM] +
                            f_scp0_idx_0_tmp_tmp * R130[3 * IM + 1]) +
                           g_scp0_idx_0_tmp_tmp * R130[3 * IM + 2];
    }
  }
  cps = atan(((As[1] * cp02_idx_0 + Bs[1] * cphi) + Cs[1]) /
             ((As[0] * cp02_idx_0 + Bs[0] * cphi) + Cs[0]));
  crs = asin((-As[2] * cp02_idx_0 - Bs[2] * cphi) - Cs[2]);
  cys = atan(((As[5] * cp02_idx_0 + Bs[5] * cphi) + Cs[5]) /
             ((As[8] * cp02_idx_0 + Bs[8] * cphi) + Cs[8]));
  cp01_idx_0 = atan(((Aw[1] * cp02_idx_0 + Bw[1] * cphi) + Pskew[1]) /
                    ((Aw[0] * cp02_idx_0 + Bw[0] * cphi) + Pskew[0]));
  crw = asin((-Aw[2] * cp02_idx_0 - Bw[2] * cphi) - Pskew[2]);
  *c7 = atan(((Aw[5] * cp02_idx_0 + Bw[5] * cphi) + Pskew[5]) /
             ((Aw[8] * cp02_idx_0 + Bw[8] * cphi) + Pskew[8]));
  *c4 = acos(cc4);
  sc5_tmp_tmp = cos(crw);
  b_sc5_tmp_tmp = cos(cp01_idx_0);
  c_sc5_tmp_tmp = sin(crw);
  d_sc5_tmp_tmp = sin(cp01_idx_0);
  cc4_tmp = cos(2.0 * cp01_idx_0);
  e_sc5_tmp_tmp = cos(2.0 * crw);
  sc4 = sin(2.0 * cp01_idx_0);
  f_sc5_tmp_tmp = sin(2.0 * crw);
  e_scp0_idx_0_tmp_tmp = cos(3.0 * cp01_idx_0);
  f_scp0_idx_0_tmp_tmp = cos(3.0 * crw);
  g_scp0_idx_0_tmp_tmp = cos(4.0 * cp01_idx_0);
  h_scp0_idx_0_tmp_tmp = cos(4.0 * crw);
  cp02_idx_0 = sin(3.0 * cp01_idx_0);
  ccr0 = sin(3.0 * crw);
  cp01_idx_0 = sin(4.0 * cp01_idx_0);
  d = 5.8381403164454094E+31 * h_scp0_idx_0_tmp_tmp;
  d1 = 4.7577974638953085E+33 * e_scp0_idx_0_tmp_tmp;
  d2 = 1.3165759884703893E+33 * g_scp0_idx_0_tmp_tmp;
  d3 = 2.8055965393075818E+33 * e_sc5_tmp_tmp;
  d4 = 7.230165143290478E+32 * f_scp0_idx_0_tmp_tmp;
  d5 = 1.2013213277109155E+34 * cc4_tmp;
  d6 = 4.2421596723753285E+33 * sc4;
  d7 = 6.248394006115564E+33 * cp02_idx_0;
  d8 = 2.2805102969368449E+33 * cp01_idx_0;
  d9 = 5.755069824220681E+33 * f_sc5_tmp_tmp;
  d10 = 6.8604407893722155E+33 * ccr0;
  scr0 = sin(4.0 * crw);
  im = 7.4666930876448766E+31 * scr0;
  re = 5.3827097350021916E+33 * b_sc5_tmp_tmp;
  cphi = 3.320119296E+32 * h_scp0_idx_0_tmp_tmp;
  b_im = 5.4585717593756787E+34 * sc5_tmp_tmp;
  b_re = 5.7836147512096631E+34 * d_sc5_tmp_tmp;
  c_im = 3.4116073496097991E+34 * c_sc5_tmp_tmp;
  c_re = 4.4018717431374439E+34 * d_sc5_tmp_tmp * c_sc5_tmp_tmp;
  d_im = 4.2115871289802583E+32 * cc4_tmp * sc5_tmp_tmp;
  d_re = 3.984961976290063E+34 * e_sc5_tmp_tmp * b_sc5_tmp_tmp;
  e_im = 1.0002055389144305E+34 * e_scp0_idx_0_tmp_tmp * sc5_tmp_tmp;
  e_re = 2.1538820478179424E+33 * f_scp0_idx_0_tmp_tmp * b_sc5_tmp_tmp;
  f_re = 2.851090864560278E+32 * g_scp0_idx_0_tmp_tmp * sc5_tmp_tmp;
  g_re = 9.584133931008E+32 * h_scp0_idx_0_tmp_tmp * b_sc5_tmp_tmp;
  h_re = 2.5138324558498092E+34 * cc4_tmp * c_sc5_tmp_tmp;
  i_re = 1.5011763324084408E+34 * e_sc5_tmp_tmp * d_sc5_tmp_tmp;
  j_re = 4.5110938138299357E+34 * sc4 * sc5_tmp_tmp;
  f_im = 1.5970952038019443E+34 * f_sc5_tmp_tmp * b_sc5_tmp_tmp;
  OBL_tmp_tmp = 1.5461961503813042E+34 * e_scp0_idx_0_tmp_tmp * c_sc5_tmp_tmp;
  k_re = 1.4484787331476195E+33 * f_scp0_idx_0_tmp_tmp * d_sc5_tmp_tmp;
  l_re = 7.290286633136127E+33 * cp02_idx_0 * sc5_tmp_tmp;
  m_re = 1.0050559156466503E+33 * ccr0 * b_sc5_tmp_tmp;
  n_re = 4.561745383296445E+32 * g_scp0_idx_0_tmp_tmp * c_sc5_tmp_tmp;
  o_re = cphi * d_sc5_tmp_tmp;
  p_re = 1.6459815060994205E+32 * cp01_idx_0 * sc5_tmp_tmp;
  OBL_tmp = 7.4937483091968E+32 * scr0 * b_sc5_tmp_tmp;
  b_OBL_tmp_tmp = 5.1448096851990978E+34 * sc4 * c_sc5_tmp_tmp;
  c_OBL_tmp_tmp = 2.7279702322102641E+33 * f_sc5_tmp_tmp * d_sc5_tmp_tmp;
  d11 = 1.197697563497588E+34 * cp02_idx_0 * c_sc5_tmp_tmp;
  d12 = 2.3986669841642266E+33 * ccr0 * d_sc5_tmp_tmp;
  d13 = 2.6335704097590729E+32 * cp01_idx_0 * c_sc5_tmp_tmp;
  d14 = 2.5959714816E+32 * scr0 * d_sc5_tmp_tmp;
  d15 = 7.6013589615016022E+33 * cc4_tmp * e_sc5_tmp_tmp;
  d16 = 1.2652334671024526E+33 * cc4_tmp * f_scp0_idx_0_tmp_tmp;
  d17 = 6.5320207674613464E+33 * e_scp0_idx_0_tmp_tmp * e_sc5_tmp_tmp;
  d18 = 2.1670445446114592E+32 * cc4_tmp * h_scp0_idx_0_tmp_tmp;
  d19 = 2.3312948427725356E+33 * e_scp0_idx_0_tmp_tmp * f_scp0_idx_0_tmp_tmp;
  d20 = 8.1087809380215283E+32 * g_scp0_idx_0_tmp_tmp * e_sc5_tmp_tmp;
  d21 = 1.916759310336E+32 * e_scp0_idx_0_tmp_tmp * h_scp0_idx_0_tmp_tmp;
  d22 = 1.442837002176E+33 * g_scp0_idx_0_tmp_tmp * f_scp0_idx_0_tmp_tmp;
  d23 = 7.02514173312E+31 * g_scp0_idx_0_tmp_tmp * h_scp0_idx_0_tmp_tmp;
  d24 = 2.3239558679214674E+34 * cc4_tmp * f_sc5_tmp_tmp;
  d25 = 2.175118764509379E+34 * e_sc5_tmp_tmp * sc4;
  d26 = 5.6690400989117193E+33 * cc4_tmp * ccr0;
  d27 = 8.894636240240254E+33 * e_scp0_idx_0_tmp_tmp * f_sc5_tmp_tmp;
  d28 = 3.1751514780100186E+33 * e_sc5_tmp_tmp * cp02_idx_0;
  d29 = 1.7704355146323878E+33 * f_scp0_idx_0_tmp_tmp * sc4;
  d30 = 2.7715429305955123E+32 * cc4_tmp * scr0;
  d31 = 2.579873238604677E+33 * e_scp0_idx_0_tmp_tmp * ccr0;
  d32 = 1.6633396795941595E+33 * g_scp0_idx_0_tmp_tmp * f_sc5_tmp_tmp;
  d33 = 1.4045644601378208E+33 * e_sc5_tmp_tmp * cp01_idx_0;
  d34 = 2.1008624605599006E+33 * f_scp0_idx_0_tmp_tmp * cp02_idx_0;
  d35 = 1.1140092418990081E+32 * h_scp0_idx_0_tmp_tmp * sc4;
  scp0_idx_0_tmp_tmp = 1.4986969030656E+32 * e_scp0_idx_0_tmp_tmp * scr0;
  b_scp0_idx_0_tmp_tmp = 1.520594684928E+32 * g_scp0_idx_0_tmp_tmp * ccr0;
  c_scp0_idx_0_tmp_tmp =
      8.32973459884416E+32 * f_scp0_idx_0_tmp_tmp * cp01_idx_0;
  d_scp0_idx_0_tmp_tmp = cphi * cp02_idx_0;
  i_scp0_idx_0_tmp_tmp = 8.9848092672E+31 * g_scp0_idx_0_tmp_tmp * scr0;
  j_scp0_idx_0_tmp_tmp = 1.216861632E+32 * h_scp0_idx_0_tmp_tmp * cp01_idx_0;
  k_scp0_idx_0_tmp_tmp = 3.7357559421952747E+33 * sc4 * f_sc5_tmp_tmp;
  l_scp0_idx_0_tmp_tmp = 4.4732281067087635E+33 * sc4 * ccr0;
  m_scp0_idx_0_tmp_tmp = 1.4315405241766194E+34 * cp02_idx_0 * f_sc5_tmp_tmp;
  n_scp0_idx_0_tmp_tmp = 1.42476279349248E+32 * sc4 * scr0;
  o_scp0_idx_0_tmp_tmp = 1.1261520652071705E+33 * cp02_idx_0 * ccr0;
  p_scp0_idx_0_tmp_tmp = 2.8811578669493762E+33 * cp01_idx_0 * f_sc5_tmp_tmp;
  q_scp0_idx_0_tmp_tmp = 2.5959714816E+32 * cp02_idx_0 * scr0;
  r_scp0_idx_0_tmp_tmp = 8.77864245147648E+31 * cp01_idx_0 * ccr0;
  s_scp0_idx_0_tmp_tmp = 1.55630592E+32 * cp01_idx_0 * scr0;
  t_scp0_idx_0_tmp_tmp = 5.6796146972541731E+34 * b_sc5_tmp_tmp * sc5_tmp_tmp;
  u_scp0_idx_0_tmp_tmp = 4.1449201019212249E+34 * b_sc5_tmp_tmp * c_sc5_tmp_tmp;
  v_scp0_idx_0_tmp_tmp = 6.2558774135182555E+34 * sc5_tmp_tmp * d_sc5_tmp_tmp;
  w_scp0_idx_0_tmp_tmp = 3.5135919432E+18 * cc4_tmp;
  x_scp0_idx_0_tmp_tmp = 5.685887301744E+18 * e_sc5_tmp_tmp;
  y_scp0_idx_0_tmp_tmp = 1.56128E+17 * h_scp0_idx_0_tmp_tmp;
  ab_scp0_idx_0_tmp_tmp = 1.166335856768E+19 * f_sc5_tmp_tmp;
  v2_idx_1 = 1.9968E+17 * scr0;
  v2_idx_2 = 4.5825876776813044E+19 * d_sc5_tmp_tmp;
  w1_idx_2 = 3.2064E+18 * f_scp0_idx_0_tmp_tmp * b_sc5_tmp_tmp;
  w1_idx_1 = 2.59391808E+18 * e_sc5_tmp_tmp * d_sc5_tmp_tmp;
  w1_idx_3 = 9.976608E+18 * sc4 * sc5_tmp_tmp;
  cphi = 3.3792E+17 * ccr0 * b_sc5_tmp_tmp;
  cp01_idx_0 = 1.59625728E+19 * sc4 * c_sc5_tmp_tmp;
  cp02_idx_0 = 5.3208576E+18 * f_sc5_tmp_tmp * d_sc5_tmp_tmp;
  scr0 = 2.2464E+18 * cc4_tmp * e_sc5_tmp_tmp;
  ccr0 = 4.608E+18 * cc4_tmp * f_sc5_tmp_tmp;
  cc4 = 2.81663946288E+19 * b_sc5_tmp_tmp * sc5_tmp_tmp;
  crw = 4.506623140608E+19 * b_sc5_tmp_tmp * c_sc5_tmp_tmp;
    scp0_idx_0_tmp = sqrt(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((d5 + d1) + d2) + d3) + d4) - d) + d6) - d7) + d8) - d9) + d10) - im) + re) + b_im) - b_re) - c_im) - c_re) - d_im) + d_re) + e_im) + e_re) - f_re) - g_re) + h_re) + i_re) - j_re) + f_im) + OBL_tmp_tmp) - k_re) + l_re) - m_re) - n_re) - o_re) + p_re) + OBL_tmp) - b_OBL_tmp_tmp) + c_OBL_tmp_tmp) + d11) + d12) + d13) + d14) - d15) + d16) - d17) + d18) + d19) - d20) - d21) - d22) + d23) - d24) + d25) + d26) + d27) + d28) + d29) + d30) - d31) + d32) - d33) + d34) - d35) + scp0_idx_0_tmp_tmp) + b_scp0_idx_0_tmp_tmp) + c_scp0_idx_0_tmp_tmp) - d_scp0_idx_0_tmp_tmp) + i_scp0_idx_0_tmp_tmp) + j_scp0_idx_0_tmp_tmp) + k_scp0_idx_0_tmp_tmp) + l_scp0_idx_0_tmp_tmp) - m_scp0_idx_0_tmp_tmp) - n_scp0_idx_0_tmp_tmp) + o_scp0_idx_0_tmp_tmp) + p_scp0_idx_0_tmp_tmp) + q_scp0_idx_0_tmp_tmp) - r_scp0_idx_0_tmp_tmp) + s_scp0_idx_0_tmp_tmp) - t_scp0_idx_0_tmp_tmp) - u_scp0_idx_0_tmp_tmp) + v_scp0_idx_0_tmp_tmp) - 3.9051323059259638E+34) / ((((((((((((((((ab_scp0_idx_0_tmp_tmp - x_scp0_idx_0_tmp_tmp) - y_scp0_idx_0_tmp_tmp) - w_scp0_idx_0_tmp_tmp) - v2_idx_1) + v2_idx_2) - w1_idx_2) - w1_idx_1) + w1_idx_3) + cphi) + cp01_idx_0) + cp02_idx_0) - scr0) + ccr0) + cc4) + crw) + 4.440199560734525E+19));
    b_scp0_idx_0_tmp = 2.4E+9 * b_sc5_tmp_tmp * sc5_tmp_tmp;
    c_scp0_idx_0_tmp = 3.84E+9 * b_sc5_tmp_tmp * c_sc5_tmp_tmp;
    bb_scp0_idx_0_tmp_tmp =
        2.9999106E+7 * d_sc5_tmp_tmp - 1.73205E+7 * b_sc5_tmp_tmp;
    cb_scp0_idx_0_tmp_tmp = 1.6E+7 * d_sc5_tmp_tmp * c_sc5_tmp_tmp;
    db_scp0_idx_0_tmp_tmp = 1.732E+7 * b_sc5_tmp_tmp * sc5_tmp_tmp;
    eb_scp0_idx_0_tmp_tmp = 2.7712E+7 * b_sc5_tmp_tmp * c_sc5_tmp_tmp;
    fb_scp0_idx_0_tmp_tmp = 1.0E+7 * sc5_tmp_tmp * d_sc5_tmp_tmp;
    d_scp0_idx_0_tmp =
        (((((4.15692E+9 * d_sc5_tmp_tmp - 2.048E+9 * sc5_tmp_tmp) +
            1.28E+9 * c_sc5_tmp_tmp) +
           b_scp0_idx_0_tmp) +
          c_scp0_idx_0_tmp) +
         5.247928481E+9) /
        (80.0 * (((((bb_scp0_idx_0_tmp_tmp + cb_scp0_idx_0_tmp_tmp) +
                    db_scp0_idx_0_tmp_tmp) +
                   eb_scp0_idx_0_tmp_tmp) +
                  fb_scp0_idx_0_tmp_tmp) +
                 5.196E+7));
    w2_idx_0 = 1.4999553E+7 * b_sc5_tmp_tmp / 500000.0 +
               34641.0 * d_sc5_tmp_tmp / 2000.0;
    w2_idx_2 = 3464.0 * d_sc5_tmp_tmp * c_sc5_tmp_tmp / 125.0;
    w2_idx_1 = 10.0 * b_sc5_tmp_tmp * sc5_tmp_tmp;
    w2_idx_3 = 16.0 * b_sc5_tmp_tmp * c_sc5_tmp_tmp;
    v2_idx_0 = 433.0 * sc5_tmp_tmp * d_sc5_tmp_tmp / 25.0;
    e_scp0_idx_0_tmp =
        1.5625E+15 *
        (((((w2_idx_0 - w2_idx_2) + w2_idx_1) + w2_idx_3) - v2_idx_0) + 30.0);
    v3_idx_0 = 1.463996643E+9 * cc4_tmp / 100000.0;
    e_scp0_idx_0_tmp_tmp = 6.33910546419E+11 * sc4 / 2.5E+7;
    g_scp0_idx_0_tmp_tmp = 7.8716581390969E+16 * b_sc5_tmp_tmp / 5.0E+11;
    h_scp0_idx_0_tmp_tmp = 4.31208690510321E+14 * d_sc5_tmp_tmp / 2.0E+9;
    f_scp0_idx_0_tmp_tmp =
        1.925943032273E+12 * d_sc5_tmp_tmp * c_sc5_tmp_tmp / 1.5625E+7;
    f_scp0_idx_0_tmp =
        (((((((e_scp0_idx_0_tmp_tmp - 9360.0 * e_sc5_tmp_tmp) - v3_idx_0) +
             19200.0 * f_sc5_tmp_tmp) +
            g_scp0_idx_0_tmp_tmp) -
           61440.0 * sc5_tmp_tmp) +
          h_scp0_idx_0_tmp_tmp) +
         38400.0 * c_sc5_tmp_tmp) -
        f_scp0_idx_0_tmp_tmp;
    g_scp0_idx_0_tmp = 7.7951435732955246E+9 * scp0_idx_0_tmp / 1.0E+12;
    h_scp0_idx_0_tmp = 4.4998659E+7 * cc4_tmp * sc5_tmp_tmp / 625.0;
    i_scp0_idx_0_tmp = 20480.0 * e_sc5_tmp_tmp * b_sc5_tmp_tmp;
    j_scp0_idx_0_tmp = 3.59989272E+8 * cc4_tmp * c_sc5_tmp_tmp / 3125.0;
    k_scp0_idx_0_tmp = 886784.0 * e_sc5_tmp_tmp * d_sc5_tmp_tmp / 25.0;
    l_scp0_idx_0_tmp = 207846.0 * sc4 * sc5_tmp_tmp / 5.0;
    m_scp0_idx_0_tmp = 9984.0 * f_sc5_tmp_tmp * b_sc5_tmp_tmp;
    n_scp0_idx_0_tmp = 1.662768E+6 * sc4 * c_sc5_tmp_tmp / 25.0;
    o_scp0_idx_0_tmp = 2.161536E+6 * f_sc5_tmp_tmp * d_sc5_tmp_tmp / 125.0;
    p_scp0_idx_0_tmp = 9360.0 * cc4_tmp * e_sc5_tmp_tmp;
    q_scp0_idx_0_tmp = 19200.0 * cc4_tmp * f_sc5_tmp_tmp;
    r_scp0_idx_0_tmp = 405288.0 * e_sc5_tmp_tmp * sc4 / 25.0;
    s_scp0_idx_0_tmp = 166272.0 * sc4 * f_sc5_tmp_tmp / 5.0;
    t_scp0_idx_0_tmp =
        3.1520557861E+10 * b_sc5_tmp_tmp * sc5_tmp_tmp / 500000.0;
    u_scp0_idx_0_tmp =
        1.4847856961E+10 * b_sc5_tmp_tmp * c_sc5_tmp_tmp / 62500.0;
    v_scp0_idx_0_tmp =
        3.159162632273E+12 * sc5_tmp_tmp * d_sc5_tmp_tmp / 2.5E+7;
    w_scp0_idx_0_tmp =
        55.154328932550712 * e_sc5_tmp_tmp * scp0_idx_0_tmp / 125000.0;
    x_scp0_idx_0_tmp =
        2.8284271247461903 * f_sc5_tmp_tmp * scp0_idx_0_tmp / 3125.0;
    y_scp0_idx_0_tmp =
        146969.31604249918 * d_sc5_tmp_tmp * scp0_idx_0_tmp / 2.5E+7;
    gb_scp0_idx_0_tmp_tmp = 4.2426406871192857 * b_sc5_tmp_tmp * sc5_tmp_tmp;
    ab_scp0_idx_0_tmp = gb_scp0_idx_0_tmp_tmp * scp0_idx_0_tmp / 1250.0;
    hb_scp0_idx_0_tmp_tmp = 16.970562748477143 * b_sc5_tmp_tmp * c_sc5_tmp_tmp;
    scp0_idx_0_tmp = hb_scp0_idx_0_tmp_tmp * scp0_idx_0_tmp / 3125.0;
    scp0_idx_0_tmp_tmp_tmp = 4.15692E+9 * d_sc5_tmp_tmp;
    ib_scp0_idx_0_tmp_tmp =
        (scp0_idx_0_tmp_tmp_tmp - 6.24E+8 * (sc5_tmp_tmp * sc5_tmp_tmp)) +
        b_scp0_idx_0_tmp;
    jb_scp0_idx_0_tmp_tmp = 1.28E+9 * sc5_tmp_tmp * c_sc5_tmp_tmp;
    kb_scp0_idx_0_tmp_tmp =
        1.4999553E+7 * d_sc5_tmp_tmp - 8.66025E+6 * b_sc5_tmp_tmp;
    lb_scp0_idx_0_tmp_tmp = 8.0E+6 * d_sc5_tmp_tmp * c_sc5_tmp_tmp;
    mb_scp0_idx_0_tmp_tmp = 8.66E+6 * b_sc5_tmp_tmp * sc5_tmp_tmp;
    nb_scp0_idx_0_tmp_tmp = 1.3856E+7 * b_sc5_tmp_tmp * c_sc5_tmp_tmp;
    ob_scp0_idx_0_tmp_tmp = 5.0E+6 * sc5_tmp_tmp * d_sc5_tmp_tmp;
    b_sc5_tmp_tmp =
        249989.0 *
        (((ib_scp0_idx_0_tmp_tmp + c_scp0_idx_0_tmp) + jb_scp0_idx_0_tmp_tmp) +
         5.823998881E+9) *
        (((((kb_scp0_idx_0_tmp_tmp + lb_scp0_idx_0_tmp_tmp) +
            mb_scp0_idx_0_tmp_tmp) +
           nb_scp0_idx_0_tmp_tmp) +
          ob_scp0_idx_0_tmp_tmp) +
         2.598E+7);
    w1_idx_2 = sqrt(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((d - d1) - d2) - d3) - d4) - d5) - d6) + d7) - d8) - d9) + d10) - im) - re) - b_im) + b_re) - c_im) - c_re) + d_im) - d_re) - e_im) - e_re) + f_re) + g_re) + h_re) - i_re) + j_re) + f_im) + OBL_tmp_tmp) + k_re) - l_re) - m_re) - n_re) + o_re) - p_re) + OBL_tmp) - b_OBL_tmp_tmp) + c_OBL_tmp_tmp) + d11) + d12) + d13) + d14) + d15) - d16) + d17) - d18) - d19) + d20) + d21) + d22) - d23) - d24) - d25) + d26) + d27) - d28) - d29) + d30) - d31) + d32) + d33) - d34) + d35) + scp0_idx_0_tmp_tmp) + b_scp0_idx_0_tmp_tmp) - c_scp0_idx_0_tmp_tmp) + d_scp0_idx_0_tmp_tmp) + i_scp0_idx_0_tmp_tmp) - j_scp0_idx_0_tmp_tmp) + k_scp0_idx_0_tmp_tmp) + l_scp0_idx_0_tmp_tmp) - m_scp0_idx_0_tmp_tmp) - n_scp0_idx_0_tmp_tmp) + o_scp0_idx_0_tmp_tmp) + p_scp0_idx_0_tmp_tmp) + q_scp0_idx_0_tmp_tmp) - r_scp0_idx_0_tmp_tmp) + s_scp0_idx_0_tmp_tmp) + t_scp0_idx_0_tmp_tmp) - u_scp0_idx_0_tmp_tmp) - v_scp0_idx_0_tmp_tmp) + 3.9051323059259638E+34) / ((((((((((((((((w_scp0_idx_0_tmp_tmp + x_scp0_idx_0_tmp_tmp) + y_scp0_idx_0_tmp_tmp) + ab_scp0_idx_0_tmp_tmp) - v2_idx_1) - v2_idx_2) + w1_idx_2) + w1_idx_1) - w1_idx_3) + cphi) + cp01_idx_0) + cp02_idx_0) + scr0) + ccr0) - cc4) + crw) - 4.440199560734525E+19));
    crw = 1.5625E+15 *
          (((((w2_idx_0 + w2_idx_2) + w2_idx_1) - w2_idx_3) - v2_idx_0) + 30.0);
    sc4 = (((((((v3_idx_0 + 9360.0 * e_sc5_tmp_tmp) - e_scp0_idx_0_tmp_tmp) +
               19200.0 * f_sc5_tmp_tmp) -
              g_scp0_idx_0_tmp_tmp) +
             61440.0 * sc5_tmp_tmp) -
            h_scp0_idx_0_tmp_tmp) +
           38400.0 * c_sc5_tmp_tmp) -
          f_scp0_idx_0_tmp_tmp;
    cc4 = 7.7951435732955246E+9 * w1_idx_2 / 1.0E+12;
    cc4_tmp = 55.154328932550712 * e_sc5_tmp_tmp * w1_idx_2 / 125000.0;
    ccr0 = 2.8284271247461903 * f_sc5_tmp_tmp * w1_idx_2 / 3125.0;
    scr0 = 146969.31604249918 * d_sc5_tmp_tmp * w1_idx_2 / 2.5E+7;
    cp02_idx_0 = gb_scp0_idx_0_tmp_tmp * w1_idx_2 / 1250.0;
    w1_idx_2 = hb_scp0_idx_0_tmp_tmp * w1_idx_2 / 3125.0;
    cp01_idx_0 =
        249989.0 *
        (((ib_scp0_idx_0_tmp_tmp - c_scp0_idx_0_tmp) - jb_scp0_idx_0_tmp_tmp) +
         5.823998881E+9) *
        (((((kb_scp0_idx_0_tmp_tmp - lb_scp0_idx_0_tmp_tmp) +
            mb_scp0_idx_0_tmp_tmp) -
           nb_scp0_idx_0_tmp_tmp) +
          ob_scp0_idx_0_tmp_tmp) +
         2.598E+7);
    cphi = (((((2.048E+9 * sc5_tmp_tmp - scp0_idx_0_tmp_tmp_tmp) +
               1.28E+9 * c_sc5_tmp_tmp) -
              b_scp0_idx_0_tmp) +
             c_scp0_idx_0_tmp) -
            5.247928481E+9) /
           (80.0 * (((((bb_scp0_idx_0_tmp_tmp - cb_scp0_idx_0_tmp_tmp) +
                       db_scp0_idx_0_tmp_tmp) -
                      eb_scp0_idx_0_tmp_tmp) +
                     fb_scp0_idx_0_tmp_tmp) +
                    5.196E+7));
    *c5 = asin(d_scp0_idx_0_tmp -
               e_scp0_idx_0_tmp *
                   ((((((((((((((((((((((f_scp0_idx_0_tmp + g_scp0_idx_0_tmp) +
                                        h_scp0_idx_0_tmp) -
                                       i_scp0_idx_0_tmp) +
                                      j_scp0_idx_0_tmp) +
                                     k_scp0_idx_0_tmp) +
                                    l_scp0_idx_0_tmp) -
                                   m_scp0_idx_0_tmp) +
                                  n_scp0_idx_0_tmp) +
                                 o_scp0_idx_0_tmp) -
                                p_scp0_idx_0_tmp) +
                               q_scp0_idx_0_tmp) +
                              r_scp0_idx_0_tmp) -
                             s_scp0_idx_0_tmp) +
                            t_scp0_idx_0_tmp) +
                           u_scp0_idx_0_tmp) -
                          v_scp0_idx_0_tmp) -
                         w_scp0_idx_0_tmp) +
                        x_scp0_idx_0_tmp) +
                       y_scp0_idx_0_tmp) +
                      ab_scp0_idx_0_tmp) +
                     scp0_idx_0_tmp) +
                    214797.82086) /
                   b_sc5_tmp_tmp);
    *c6 = asin(crw *
                   ((((((((((((((((((((((sc4 - cc4) - h_scp0_idx_0_tmp) +
                                       i_scp0_idx_0_tmp) +
                                      j_scp0_idx_0_tmp) -
                                     k_scp0_idx_0_tmp) -
                                    l_scp0_idx_0_tmp) -
                                   m_scp0_idx_0_tmp) +
                                  n_scp0_idx_0_tmp) +
                                 o_scp0_idx_0_tmp) +
                                p_scp0_idx_0_tmp) +
                               q_scp0_idx_0_tmp) -
                              r_scp0_idx_0_tmp) -
                             s_scp0_idx_0_tmp) -
                            t_scp0_idx_0_tmp) +
                           u_scp0_idx_0_tmp) +
                          v_scp0_idx_0_tmp) +
                         cc4_tmp) +
                        ccr0) -
                       scr0) -
                      cp02_idx_0) +
                     w1_idx_2) -
                    214797.82086) /
                   cp01_idx_0 -
               cphi);
    if ((!(*c5 >= -1.0471975511965976)) || (!(*c5 <= 0.47123889803846897))) {
      *c5 =
          asin(d_scp0_idx_0_tmp -
               e_scp0_idx_0_tmp *
                   ((((((((((((((((((((((f_scp0_idx_0_tmp - g_scp0_idx_0_tmp) +
                                        h_scp0_idx_0_tmp) -
                                       i_scp0_idx_0_tmp) +
                                      j_scp0_idx_0_tmp) +
                                     k_scp0_idx_0_tmp) +
                                    l_scp0_idx_0_tmp) -
                                   m_scp0_idx_0_tmp) +
                                  n_scp0_idx_0_tmp) +
                                 o_scp0_idx_0_tmp) -
                                p_scp0_idx_0_tmp) +
                               q_scp0_idx_0_tmp) +
                              r_scp0_idx_0_tmp) -
                             s_scp0_idx_0_tmp) +
                            t_scp0_idx_0_tmp) +
                           u_scp0_idx_0_tmp) -
                          v_scp0_idx_0_tmp) +
                         w_scp0_idx_0_tmp) -
                        x_scp0_idx_0_tmp) -
                       y_scp0_idx_0_tmp) -
                      ab_scp0_idx_0_tmp) -
                     scp0_idx_0_tmp) +
                    214797.82086) /
                   b_sc5_tmp_tmp);
    }
    if ((!(*c6 >= -1.0471975511965976)) || (!(*c6 <= 0.47123889803846897))) {
      *c6 = asin(crw *
                     ((((((((((((((((((((((sc4 + cc4) - h_scp0_idx_0_tmp) +
                                         i_scp0_idx_0_tmp) +
                                        j_scp0_idx_0_tmp) -
                                       k_scp0_idx_0_tmp) -
                                      l_scp0_idx_0_tmp) -
                                     m_scp0_idx_0_tmp) +
                                    n_scp0_idx_0_tmp) +
                                   o_scp0_idx_0_tmp) +
                                  p_scp0_idx_0_tmp) +
                                 q_scp0_idx_0_tmp) -
                                r_scp0_idx_0_tmp) -
                               s_scp0_idx_0_tmp) -
                              t_scp0_idx_0_tmp) +
                             u_scp0_idx_0_tmp) +
                            v_scp0_idx_0_tmp) -
                           cc4_tmp) -
                          ccr0) +
                         scr0) +
                        cp02_idx_0) -
                       w1_idx_2) -
                      214797.82086) /
                     cp01_idx_0 -
                 cphi);
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
    OBL_tmp = sin(cys);
    OBL_tmp_tmp = cos(cys);
    b_OBL_tmp_tmp = sin(crs);
    c_OBL_tmp_tmp = cos(crs);
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
    cc4_tmp = 14964.5 * c_c10_tmp.re;
    sc4 = 14964.5 * c_c10_tmp.im;
    l_scp0_idx_0_tmp_tmp = 7482.25 * c10_tmp.re;
    m_scp0_idx_0_tmp_tmp = 7482.25 * c10_tmp.im;
    c_c10_tmp_tmp.re = 0.0;
    c_c10_tmp_tmp.im = 0.52359877559829882;
    b_exp(&c_c10_tmp_tmp);
    dc.re = crs * 0.0;
    dc.im = crs;
    b_exp(&dc);
    dc1.re = cys * 0.0;
    dc1.im = cys;
    b_exp(&dc1);
    n_scp0_idx_0_tmp_tmp =
        7.3304908103362271E-12 * c10_tmp_tmp.re - 119716.0 * c10_tmp_tmp.im;
    o_scp0_idx_0_tmp_tmp =
        7.3304908103362271E-12 * c10_tmp_tmp.im + 119716.0 * c10_tmp_tmp.re;
    m_re = n_scp0_idx_0_tmp_tmp * dc.re - o_scp0_idx_0_tmp_tmp * dc.im;
    f_im = n_scp0_idx_0_tmp_tmp * dc.im + o_scp0_idx_0_tmp_tmp * dc.re;
    n_re = m_re * dc1.re - f_im * dc1.im;
    f_im = m_re * dc1.im + f_im * dc1.re;
    g_c10_tmp.re = 0.64278760968653936 *
                   (n_re * c_c10_tmp_tmp.re - f_im * c_c10_tmp_tmp.im);
    g_c10_tmp.im = 0.64278760968653936 *
                   (n_re * c_c10_tmp_tmp.im + f_im * c_c10_tmp_tmp.re);
    dc.re = crs * 0.0;
    dc.im = crs;
    b_exp(&dc);
    dc1.re = cys * 0.0;
    dc1.im = cys;
    b_exp(&dc1);
    cc4 = 3.6652454051681135E-12 * c10_tmp_tmp.re - 59858.0 * c10_tmp_tmp.im;
    crw = 3.6652454051681135E-12 * c10_tmp_tmp.im + 59858.0 * c10_tmp_tmp.re;
    m_re = cc4 * dc.re - crw * dc.im;
    f_im = cc4 * dc.im + crw * dc.re;
    n_re = m_re * dc1.re - f_im * dc1.im;
    f_im = m_re * dc1.im + f_im * dc1.re;
    h_c10_tmp.re = 0.64278760968653936 *
                   (n_re * c_c10_tmp_tmp.re - f_im * c_c10_tmp_tmp.im);
    h_c10_tmp.im = 0.64278760968653936 *
                   (n_re * c_c10_tmp_tmp.im + f_im * c_c10_tmp_tmp.re);
    m_re = 3.6652454051681119E-12 * c10_tmp_tmp.re -
           59857.999999999978 * c10_tmp_tmp.im;
    f_im = 3.6652454051681119E-12 * c10_tmp_tmp.im +
           59857.999999999978 * c10_tmp_tmp.re;
    n_re = m_re * c_c10_tmp.re - f_im * c_c10_tmp.im;
    f_im = m_re * c_c10_tmp.im + f_im * c_c10_tmp.re;
    m_re = n_re * b_c10_tmp.re - f_im * b_c10_tmp.im;
    f_im = n_re * b_c10_tmp.im + f_im * b_c10_tmp.re;
    n_re = n_scp0_idx_0_tmp_tmp * c_c10_tmp.re -
           o_scp0_idx_0_tmp_tmp * c_c10_tmp.im;
    p_scp0_idx_0_tmp_tmp = n_scp0_idx_0_tmp_tmp * c_c10_tmp.im +
                           o_scp0_idx_0_tmp_tmp * c_c10_tmp.re;
    o_re = n_re * b_c10_tmp.re - p_scp0_idx_0_tmp_tmp * b_c10_tmp.im;
    p_scp0_idx_0_tmp_tmp =
        n_re * b_c10_tmp.im + p_scp0_idx_0_tmp_tmp * b_c10_tmp.re;
    b_a.re =
        ((((m_re * c_c10_tmp_tmp.re - f_im * c_c10_tmp_tmp.im) -
           (o_re * c_c10_tmp_tmp.re -
            p_scp0_idx_0_tmp_tmp * c_c10_tmp_tmp.im)) -
          0.86602540378443871 * g_c10_tmp.re * b_OBL_tmp_tmp) +
         OBL_tmp * (c_OBL_tmp_tmp * (6.123233995736766E-17 * g_c10_tmp.re)) *
             0.49999999999999994) +
        OBL_tmp_tmp * (c_OBL_tmp_tmp * g_c10_tmp.re) * 0.49999999999999994;
    b_a.im =
        ((((m_re * c_c10_tmp_tmp.im + f_im * c_c10_tmp_tmp.re) -
           (o_re * c_c10_tmp_tmp.im +
            p_scp0_idx_0_tmp_tmp * c_c10_tmp_tmp.re)) -
          0.86602540378443871 * g_c10_tmp.im * b_OBL_tmp_tmp) +
         OBL_tmp * (c_OBL_tmp_tmp * (6.123233995736766E-17 * g_c10_tmp.im)) *
             0.49999999999999994) +
        OBL_tmp_tmp * (c_OBL_tmp_tmp * g_c10_tmp.im) * 0.49999999999999994;
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
    n_scp0_idx_0_tmp_tmp = 0.0 * c_c10_tmp.im;
    o_scp0_idx_0_tmp_tmp = 0.0 * c_c10_tmp.re;
    m_re = 0.766044443118978 * (l_scp0_idx_0_tmp_tmp - 0.0 * c10_tmp.im);
    f_im = 0.766044443118978 * (m_scp0_idx_0_tmp_tmp + 0.0 * c10_tmp.re);
    cp01_idx_0 = 9.1631135129202838E-13 * c10_tmp_tmp.re;
    n_re = cp01_idx_0 - 14964.5 * c10_tmp_tmp.im;
    cphi = 9.1631135129202838E-13 * c10_tmp_tmp.im;
    p_scp0_idx_0_tmp_tmp = cphi + 14964.5 * c10_tmp_tmp.re;
    o_re = -7482.25 * c10_tmp_tmp.re - cphi;
    kb_scp0_idx_0_tmp_tmp = -7482.25 * c10_tmp_tmp.im + cp01_idx_0;
    p_re = 0.766044443118978 *
           (o_re * d_c10_tmp.re - kb_scp0_idx_0_tmp_tmp * d_c10_tmp.im);
    kb_scp0_idx_0_tmp_tmp =
        0.766044443118978 *
        (o_re * d_c10_tmp.im + kb_scp0_idx_0_tmp_tmp * d_c10_tmp.re);
    o_re = 14964.5 * dc.re - 0.0 * dc.im;
    lb_scp0_idx_0_tmp_tmp = 14964.5 * dc.im + 0.0 * dc.re;
    k_re = 7482.25 * dc1.re - 0.0 * dc1.im;
    mb_scp0_idx_0_tmp_tmp = 7482.25 * dc1.im + 0.0 * dc1.re;
    l_re = 0.766044443118978 *
           (k_re * b_c10_tmp_tmp.re - mb_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.im);
    mb_scp0_idx_0_tmp_tmp =
        0.766044443118978 *
        (k_re * b_c10_tmp_tmp.im + mb_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.re);
    k_re = 9.1631135129202838E-13 * dc2.re - 14964.5 * dc2.im;
    scp0_idx_0_tmp_tmp_tmp = 9.1631135129202838E-13 * dc2.im + 14964.5 * dc2.re;
    b_sc5_tmp_tmp = k_re * c10_tmp.re - scp0_idx_0_tmp_tmp_tmp * c10_tmp.im;
    scp0_idx_0_tmp_tmp_tmp =
        k_re * c10_tmp.im + scp0_idx_0_tmp_tmp_tmp * c10_tmp.re;
    k_re = -14964.5 * c10_tmp_tmp.re - 1.8326227025840568E-12 * c10_tmp_tmp.im;
    im = -14964.5 * c10_tmp_tmp.im + 1.8326227025840568E-12 * c10_tmp_tmp.re;
    re = k_re * c_c10_tmp.re - im * c_c10_tmp.im;
    im = k_re * c_c10_tmp.im + im * c_c10_tmp.re;
    k_re = -7482.25 * dc3.re - 9.1631135129202838E-13 * dc3.im;
    b_im = -7482.25 * dc3.im + 9.1631135129202838E-13 * dc3.re;
    b_re = k_re * c10_tmp.re - b_im * c10_tmp.im;
    b_im = k_re * c10_tmp.im + b_im * c10_tmp.re;
    k_re = 0.766044443118978 * (b_re * d_c10_tmp.re - b_im * d_c10_tmp.im);
    b_im = 0.766044443118978 * (b_re * d_c10_tmp.im + b_im * d_c10_tmp.re);
    b_re = 9.1631135129202838E-13 * dc4.re - 14964.5 * dc4.im;
    c_im = 9.1631135129202838E-13 * dc4.im + 14964.5 * dc4.re;
    c_re = b_re * dc5.re - c_im * dc5.im;
    c_im = b_re * dc5.im + c_im * dc5.re;
    b_re = -7482.25 * dc6.re - 9.1631135129202838E-13 * dc6.im;
    d_im = -7482.25 * dc6.im + 9.1631135129202838E-13 * dc6.re;
    d_re = b_re * dc7.re - d_im * dc7.im;
    d_im = b_re * dc7.im + d_im * dc7.re;
    b_re =
        0.766044443118978 * (d_re * b_c10_tmp_tmp.re - d_im * b_c10_tmp_tmp.im);
    d_im =
        0.766044443118978 * (d_re * b_c10_tmp_tmp.im + d_im * b_c10_tmp_tmp.re);
    d_re = 9.1631135129202838E-13 * dc8.re - 14964.5 * dc8.im;
    e_im = 9.1631135129202838E-13 * dc8.im + 14964.5 * dc8.re;
    e_re = d_re * dc9.re - e_im * dc9.im;
    e_im = d_re * dc9.im + e_im * dc9.re;
    d_re = e_re * dc10.re - e_im * dc10.im;
    e_im = e_re * dc10.im + e_im * dc10.re;
    e_re = -14964.5 * dc11.re - 1.8326227025840568E-12 * dc11.im;
    hb_scp0_idx_0_tmp_tmp =
        -14964.5 * dc11.im + 1.8326227025840568E-12 * dc11.re;
    h_re = e_re * dc12.re - hb_scp0_idx_0_tmp_tmp * dc12.im;
    hb_scp0_idx_0_tmp_tmp = e_re * dc12.im + hb_scp0_idx_0_tmp_tmp * dc12.re;
    e_re = h_re * dc13.re - hb_scp0_idx_0_tmp_tmp * dc13.im;
    hb_scp0_idx_0_tmp_tmp = h_re * dc13.im + hb_scp0_idx_0_tmp_tmp * dc13.re;
    h_re = -7482.25 * dc14.re - 9.1631135129202838E-13 * dc14.im;
    ib_scp0_idx_0_tmp_tmp =
        -7482.25 * dc14.im + 9.1631135129202838E-13 * dc14.re;
    f_re = h_re * dc15.re - ib_scp0_idx_0_tmp_tmp * dc15.im;
    ib_scp0_idx_0_tmp_tmp = h_re * dc15.im + ib_scp0_idx_0_tmp_tmp * dc15.re;
    h_re = f_re * dc16.re - ib_scp0_idx_0_tmp_tmp * dc16.im;
    ib_scp0_idx_0_tmp_tmp = f_re * dc16.im + ib_scp0_idx_0_tmp_tmp * dc16.re;
    f_re = 0.766044443118978 *
           (h_re * b_c10_tmp_tmp.re - ib_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.im);
    ib_scp0_idx_0_tmp_tmp =
        0.766044443118978 *
        (h_re * b_c10_tmp_tmp.im + ib_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.re);
    w1_idx_2 = 0.766044443118978 * l_scp0_idx_0_tmp_tmp;
    w2_idx_0 = 0.766044443118978 * m_scp0_idx_0_tmp_tmp;
    h_re = 0.766044443118978 *
           (-7482.25 * d_c10_tmp.re - 9.1631135129202838E-13 * d_c10_tmp.im);
    ob_scp0_idx_0_tmp_tmp =
        0.766044443118978 *
        (-7482.25 * d_c10_tmp.im + 9.1631135129202838E-13 * d_c10_tmp.re);
    w1_idx_1 = 0.766044443118978 * (l_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.re -
                                    m_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.im);
    scr0 = 0.766044443118978 * (l_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.im +
                                m_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.re);
    cp01_idx_0 = 9.1631135129202838E-13 * c10_tmp.re;
    i_re = cp01_idx_0 - 14964.5 * c10_tmp.im;
    cphi = 9.1631135129202838E-13 * c10_tmp.im;
    i_scp0_idx_0_tmp_tmp = cphi + 14964.5 * c10_tmp.re;
    j_re = -14964.5 * c_c10_tmp.re - 1.8326227025840568E-12 * c_c10_tmp.im;
    q_scp0_idx_0_tmp_tmp =
        -14964.5 * c_c10_tmp.im + 1.8326227025840568E-12 * c_c10_tmp.re;
    g_re = -7482.25 * c10_tmp.re - cphi;
    y_scp0_idx_0_tmp_tmp = -7482.25 * c10_tmp.im + cp01_idx_0;
    jb_scp0_idx_0_tmp_tmp =
        0.766044443118978 *
        (g_re * d_c10_tmp.re - y_scp0_idx_0_tmp_tmp * d_c10_tmp.im);
    y_scp0_idx_0_tmp_tmp =
        0.766044443118978 *
        (g_re * d_c10_tmp.im + y_scp0_idx_0_tmp_tmp * d_c10_tmp.re);
    g_re = 9.1631135129202838E-13 * dc17.re - 14964.5 * dc17.im;
    ab_scp0_idx_0_tmp_tmp =
        9.1631135129202838E-13 * dc17.im + 14964.5 * dc17.re;
    r_scp0_idx_0_tmp_tmp =
        -7482.25 * dc18.re - 9.1631135129202838E-13 * dc18.im;
    s_scp0_idx_0_tmp_tmp =
        -7482.25 * dc18.im + 9.1631135129202838E-13 * dc18.re;
    t_scp0_idx_0_tmp_tmp =
        0.766044443118978 * (r_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.re -
                             s_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.im);
    s_scp0_idx_0_tmp_tmp =
        0.766044443118978 * (r_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.im +
                             s_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.re);
    r_scp0_idx_0_tmp_tmp = 9.1631135129202838E-13 * dc19.re - 14964.5 * dc19.im;
    u_scp0_idx_0_tmp_tmp = 9.1631135129202838E-13 * dc19.im + 14964.5 * dc19.re;
    v_scp0_idx_0_tmp_tmp =
        r_scp0_idx_0_tmp_tmp * dc20.re - u_scp0_idx_0_tmp_tmp * dc20.im;
    u_scp0_idx_0_tmp_tmp =
        r_scp0_idx_0_tmp_tmp * dc20.im + u_scp0_idx_0_tmp_tmp * dc20.re;
    r_scp0_idx_0_tmp_tmp =
        -14964.5 * dc21.re - 1.8326227025840568E-12 * dc21.im;
    w_scp0_idx_0_tmp_tmp =
        -14964.5 * dc21.im + 1.8326227025840568E-12 * dc21.re;
    gb_scp0_idx_0_tmp_tmp =
        r_scp0_idx_0_tmp_tmp * dc22.re - w_scp0_idx_0_tmp_tmp * dc22.im;
    w_scp0_idx_0_tmp_tmp =
        r_scp0_idx_0_tmp_tmp * dc22.im + w_scp0_idx_0_tmp_tmp * dc22.re;
    r_scp0_idx_0_tmp_tmp =
        -7482.25 * dc23.re - 9.1631135129202838E-13 * dc23.im;
    x_scp0_idx_0_tmp_tmp =
        -7482.25 * dc23.im + 9.1631135129202838E-13 * dc23.re;
    nb_scp0_idx_0_tmp_tmp =
        r_scp0_idx_0_tmp_tmp * dc24.re - x_scp0_idx_0_tmp_tmp * dc24.im;
    x_scp0_idx_0_tmp_tmp =
        r_scp0_idx_0_tmp_tmp * dc24.im + x_scp0_idx_0_tmp_tmp * dc24.re;
    r_scp0_idx_0_tmp_tmp =
        0.766044443118978 * (nb_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.re -
                             x_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.im);
    x_scp0_idx_0_tmp_tmp =
        0.766044443118978 * (nb_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.im +
                             x_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.re);
    nb_scp0_idx_0_tmp_tmp = -(
        ((((((((((((((0.0 -
                      (cc4_tmp - n_scp0_idx_0_tmp_tmp) * 0.766044443118978) +
                     (m_re * 0.0 - f_im)) -
                    4963.8290136870392) +
                   (n_re * b_c10_tmp.re - p_scp0_idx_0_tmp_tmp * b_c10_tmp.im) *
                       0.766044443118978) +
                  (p_re * 0.0 - kb_scp0_idx_0_tmp_tmp)) +
                 (o_re * b_c10_tmp_tmp.re -
                  lb_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.im) *
                     0.766044443118978) -
                (l_re * 0.0 - mb_scp0_idx_0_tmp_tmp)) +
               (b_sc5_tmp_tmp * b_c10_tmp.re -
                scp0_idx_0_tmp_tmp_tmp * b_c10_tmp.im) *
                   0.766044443118978) -
              (re * d_c10_tmp.re - im * d_c10_tmp.im) * 0.766044443118978) -
             (k_re * 0.0 - b_im)) +
            (c_re * b_c10_tmp_tmp.re - c_im * b_c10_tmp_tmp.im) *
                0.766044443118978) -
           (b_re * 0.0 - d_im)) +
          (d_re * b_c10_tmp_tmp.re - e_im * b_c10_tmp_tmp.im) *
              0.766044443118978) +
         (e_re * b_c10_tmp_tmp.re - hb_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.im) *
             0.766044443118978) +
        (f_re * 0.0 - ib_scp0_idx_0_tmp_tmp));
    f_im = -(
        ((((((((((((((-5731.7360345269735 -
                      (sc4 + o_scp0_idx_0_tmp_tmp) * 0.766044443118978) +
                     (m_re + f_im * 0.0)) +
                    2865.8680172634872) +
                   (n_re * b_c10_tmp.im + p_scp0_idx_0_tmp_tmp * b_c10_tmp.re) *
                       0.766044443118978) +
                  (p_re + kb_scp0_idx_0_tmp_tmp * 0.0)) +
                 (o_re * b_c10_tmp_tmp.im +
                  lb_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.re) *
                     0.766044443118978) -
                (l_re + mb_scp0_idx_0_tmp_tmp * 0.0)) +
               (b_sc5_tmp_tmp * b_c10_tmp.im +
                scp0_idx_0_tmp_tmp_tmp * b_c10_tmp.re) *
                   0.766044443118978) -
              (re * d_c10_tmp.im + im * d_c10_tmp.re) * 0.766044443118978) -
             (k_re + b_im * 0.0)) +
            (c_re * b_c10_tmp_tmp.im + c_im * b_c10_tmp_tmp.re) *
                0.766044443118978) -
           (b_re + d_im * 0.0)) +
          (d_re * b_c10_tmp_tmp.im + e_im * b_c10_tmp_tmp.re) *
              0.766044443118978) +
         (e_re * b_c10_tmp_tmp.im + hb_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.re) *
             0.766044443118978) +
        (f_re + ib_scp0_idx_0_tmp_tmp * 0.0));
    cp02_idx_0 =
        (((((((((((((cc4_tmp * 0.766044443118978 +
                     (w1_idx_2 * 0.0 - w2_idx_0)) -
                    4963.8290136870392) +
                   (9.1631135129202838E-13 * b_c10_tmp.re -
                    14964.5 * b_c10_tmp.im) *
                       0.766044443118978) +
                  (h_re * 0.0 - ob_scp0_idx_0_tmp_tmp)) -
                 (cc4_tmp * b_c10_tmp_tmp.re - sc4 * b_c10_tmp_tmp.im) *
                     0.766044443118978) -
                (w1_idx_1 * 0.0 - scr0)) +
               (i_re * b_c10_tmp.re - i_scp0_idx_0_tmp_tmp * b_c10_tmp.im) *
                   0.766044443118978) +
              (j_re * d_c10_tmp.re - q_scp0_idx_0_tmp_tmp * d_c10_tmp.im) *
                  0.766044443118978) -
             (jb_scp0_idx_0_tmp_tmp * 0.0 - y_scp0_idx_0_tmp_tmp)) +
            (g_re * b_c10_tmp_tmp.re -
             ab_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.im) *
                0.766044443118978) -
           (t_scp0_idx_0_tmp_tmp * 0.0 - s_scp0_idx_0_tmp_tmp)) +
          (v_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.re -
           u_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.im) *
              0.766044443118978) -
         (gb_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.re -
          w_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.im) *
             0.766044443118978) +
        (r_scp0_idx_0_tmp_tmp * 0.0 - x_scp0_idx_0_tmp_tmp);
    w2_idx_0 =
        ((((((((((((((sc4 * 0.766044443118978 - 5731.7360345269735) +
                     (w1_idx_2 + w2_idx_0 * 0.0)) +
                    2865.8680172634872) +
                   (9.1631135129202838E-13 * b_c10_tmp.im +
                    14964.5 * b_c10_tmp.re) *
                       0.766044443118978) +
                  (h_re + ob_scp0_idx_0_tmp_tmp * 0.0)) -
                 (cc4_tmp * b_c10_tmp_tmp.im + sc4 * b_c10_tmp_tmp.re) *
                     0.766044443118978) -
                (w1_idx_1 + scr0 * 0.0)) +
               (i_re * b_c10_tmp.im + i_scp0_idx_0_tmp_tmp * b_c10_tmp.re) *
                   0.766044443118978) +
              (j_re * d_c10_tmp.im + q_scp0_idx_0_tmp_tmp * d_c10_tmp.re) *
                  0.766044443118978) -
             (jb_scp0_idx_0_tmp_tmp + y_scp0_idx_0_tmp_tmp * 0.0)) +
            (g_re * b_c10_tmp_tmp.im +
             ab_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.re) *
                0.766044443118978) -
           (t_scp0_idx_0_tmp_tmp + s_scp0_idx_0_tmp_tmp * 0.0)) +
          (v_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.im +
           u_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.re) *
              0.766044443118978) -
         (gb_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.im +
          w_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.re) *
             0.766044443118978) +
        (r_scp0_idx_0_tmp_tmp + x_scp0_idx_0_tmp_tmp * 0.0);
    cp01_idx_0 = b_a.re * b_a.re - b_a.im * b_a.im;
    cphi = b_a.re * b_a.im;
    cphi += cphi;
    if (cphi == 0.0) {
      cp01_idx_0 /= 4.0;
      cphi = 0.0;
    } else if (cp01_idx_0 == 0.0) {
      cp01_idx_0 = 0.0;
      cphi /= 4.0;
    } else {
      cp01_idx_0 /= 4.0;
      cphi /= 4.0;
    }
    dc.re = (nb_scp0_idx_0_tmp_tmp * cp02_idx_0 - f_im * w2_idx_0) + cp01_idx_0;
    dc.im = (nb_scp0_idx_0_tmp_tmp * w2_idx_0 + f_im * cp02_idx_0) + cphi;
    g_c10_tmp = power(dc);
    i_c10_tmp.re = b_OBL_tmp_tmp * (0.86602540378443871 * h_c10_tmp.re);
    i_c10_tmp.im = b_OBL_tmp_tmp * (0.86602540378443871 * h_c10_tmp.im);
    j_c10_tmp.re =
        0.49999999999999994 *
        (OBL_tmp * (c_OBL_tmp_tmp * (6.123233995736766E-17 * h_c10_tmp.re)));
    j_c10_tmp.im =
        0.49999999999999994 *
        (OBL_tmp * (c_OBL_tmp_tmp * (6.123233995736766E-17 * h_c10_tmp.im)));
    w1_idx_2 = c_OBL_tmp_tmp * h_c10_tmp.re;
    w2_idx_0 = c_OBL_tmp_tmp * h_c10_tmp.im;
    h_c10_tmp.re = 0.49999999999999994 * (OBL_tmp_tmp * w1_idx_2);
    h_c10_tmp.im = 0.49999999999999994 * (OBL_tmp_tmp * w2_idx_0);
    j_scp0_idx_0_tmp_tmp = 7482.25 * d_c10_tmp.re;
    k_scp0_idx_0_tmp_tmp = 7482.25 * d_c10_tmp.im;
    dc.re = crs * 0.0;
    dc.im = crs;
    b_exp(&dc);
    dc1.re = cys * 0.0;
    dc1.im = cys;
    b_exp(&dc1);
    cp01_idx_0 = -59857.999999999971 * c10_tmp_tmp.re -
                 103677.09723945787 * c10_tmp_tmp.im;
    cphi = -59857.999999999971 * c10_tmp_tmp.im +
           103677.09723945787 * c10_tmp_tmp.re;
    m_re = cp01_idx_0 * dc.re - cphi * dc.im;
    f_im = cp01_idx_0 * dc.im + cphi * dc.re;
    n_re = m_re * dc1.re - f_im * dc1.im;
    f_im = m_re * dc1.im + f_im * dc1.re;
    b_c20_tmp.re = 0.64278760968653936 *
                   (n_re * c_c10_tmp_tmp.re - f_im * c_c10_tmp_tmp.im);
    b_c20_tmp.im = 0.64278760968653936 *
                   (n_re * c_c10_tmp_tmp.im + f_im * c_c10_tmp_tmp.re);
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
    m_re = w1_idx_1 * dc.re - w1_idx_3 * dc.im;
    f_im = w1_idx_1 * dc.im + w1_idx_3 * dc.re;
    n_re = m_re * dc1.re - f_im * dc1.im;
    f_im = m_re * dc1.im + f_im * dc1.re;
    c_c20_tmp.re = 0.64278760968653936 *
                   (n_re * c_c10_tmp_tmp.re - f_im * c_c10_tmp_tmp.im);
    c_c20_tmp.im = 0.64278760968653936 *
                   (n_re * c_c10_tmp_tmp.im + f_im * c_c10_tmp_tmp.re);
    m_re = -29928.999999999975 * c10_tmp_tmp.re -
           51838.548619728914 * c10_tmp_tmp.im;
    f_im = -29928.999999999975 * c10_tmp_tmp.im +
           51838.548619728914 * c10_tmp_tmp.re;
    n_re = m_re * c_c10_tmp.re - f_im * c_c10_tmp.im;
    f_im = m_re * c_c10_tmp.im + f_im * c_c10_tmp.re;
    m_re = n_re * b_c10_tmp.re - f_im * b_c10_tmp.im;
    f_im = n_re * b_c10_tmp.im + f_im * b_c10_tmp.re;
    n_re = cp01_idx_0 * c_c10_tmp.re - cphi * c_c10_tmp.im;
    p_scp0_idx_0_tmp_tmp = cp01_idx_0 * c_c10_tmp.im + cphi * c_c10_tmp.re;
    o_re = n_re * b_c10_tmp.re - p_scp0_idx_0_tmp_tmp * b_c10_tmp.im;
    p_scp0_idx_0_tmp_tmp =
        n_re * b_c10_tmp.im + p_scp0_idx_0_tmp_tmp * b_c10_tmp.re;
    b_a.re =
        ((((m_re * c_c10_tmp_tmp.re - f_im * c_c10_tmp_tmp.im) -
           (o_re * c_c10_tmp_tmp.re -
            p_scp0_idx_0_tmp_tmp * c_c10_tmp_tmp.im)) +
          0.86602540378443871 * b_c20_tmp.re * b_OBL_tmp_tmp) -
         OBL_tmp * (c_OBL_tmp_tmp * (-0.49999999999999978 * b_c20_tmp.re)) *
             0.49999999999999994) +
        0.86602540378443871 * (OBL_tmp_tmp * (c_OBL_tmp_tmp * b_c20_tmp.re)) *
            0.49999999999999994;
    b_a.im =
        ((((m_re * c_c10_tmp_tmp.im + f_im * c_c10_tmp_tmp.re) -
           (o_re * c_c10_tmp_tmp.im +
            p_scp0_idx_0_tmp_tmp * c_c10_tmp_tmp.re)) +
          0.86602540378443871 * b_c20_tmp.im * b_OBL_tmp_tmp) -
         OBL_tmp * (c_OBL_tmp_tmp * (-0.49999999999999978 * b_c20_tmp.im)) *
             0.49999999999999994) +
        0.86602540378443871 * (OBL_tmp_tmp * (c_OBL_tmp_tmp * b_c20_tmp.im)) *
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
    m_re = 0.766044443118978 * (j_scp0_idx_0_tmp_tmp - 0.0 * d_c10_tmp.im);
    f_im = 0.766044443118978 * (k_scp0_idx_0_tmp_tmp + 0.0 * d_c10_tmp.re);
    n_re = -7482.2500000000064 * c10_tmp_tmp.re -
           -12959.63715493223 * c10_tmp_tmp.im;
    p_scp0_idx_0_tmp_tmp = -7482.2500000000064 * c10_tmp_tmp.im +
                           -12959.63715493223 * c10_tmp_tmp.re;
    o_re = -3741.1250000000032 * c10_tmp_tmp.re -
           -6479.8185774661151 * c10_tmp_tmp.im;
    kb_scp0_idx_0_tmp_tmp = -3741.1250000000032 * c10_tmp_tmp.im +
                            -6479.8185774661151 * c10_tmp_tmp.re;
    p_re = 0.766044443118978 *
           (o_re * c10_tmp.re - kb_scp0_idx_0_tmp_tmp * c10_tmp.im);
    kb_scp0_idx_0_tmp_tmp =
        0.766044443118978 *
        (o_re * c10_tmp.im + kb_scp0_idx_0_tmp_tmp * c10_tmp.re);
    o_re = -7482.2499999999964 * c10_tmp_tmp.re -
           12959.637154932234 * c10_tmp_tmp.im;
    lb_scp0_idx_0_tmp_tmp = -7482.2499999999964 * c10_tmp_tmp.im +
                            12959.637154932234 * c10_tmp_tmp.re;
    k_re = 14964.5 * dc.re - 0.0 * dc.im;
    mb_scp0_idx_0_tmp_tmp = 14964.5 * dc.im + 0.0 * dc.re;
    l_re = 7482.25 * dc1.re - 0.0 * dc1.im;
    scp0_idx_0_tmp_tmp_tmp = 7482.25 * dc1.im + 0.0 * dc1.re;
    b_sc5_tmp_tmp = 0.766044443118978 * (l_re * d_c10_tmp.re -
                                         scp0_idx_0_tmp_tmp_tmp * d_c10_tmp.im);
    scp0_idx_0_tmp_tmp_tmp =
        0.766044443118978 *
        (l_re * d_c10_tmp.im + scp0_idx_0_tmp_tmp_tmp * d_c10_tmp.re);
    l_re = 7482.25 * dc2.re - 0.0 * dc2.im;
    im = 7482.25 * dc2.im + 0.0 * dc2.re;
    re = 0.766044443118978 * (l_re * b_c10_tmp_tmp.re - im * b_c10_tmp_tmp.im);
    im = 0.766044443118978 * (l_re * b_c10_tmp_tmp.im + im * b_c10_tmp_tmp.re);
    l_re = -7482.2499999999964 * dc3.re - 12959.637154932234 * dc3.im;
    b_im = -7482.2499999999964 * dc3.im + 12959.637154932234 * dc3.re;
    b_re = l_re * c10_tmp.re - b_im * c10_tmp.im;
    b_im = l_re * c10_tmp.im + b_im * c10_tmp.re;
    l_re = -7482.2500000000064 * dc4.re - -12959.63715493223 * dc4.im;
    c_im = -7482.2500000000064 * dc4.im + -12959.63715493223 * dc4.re;
    c_re = l_re * dc5.re - c_im * dc5.im;
    c_im = l_re * dc5.im + c_im * dc5.re;
    l_re = -3741.1250000000032 * dc6.re - -6479.8185774661151 * dc6.im;
    d_im = -3741.1250000000032 * dc6.im + -6479.8185774661151 * dc6.re;
    d_re = l_re * dc7.re - d_im * dc7.im;
    d_im = l_re * dc7.im + d_im * dc7.re;
    l_re =
        0.766044443118978 * (d_re * b_c10_tmp_tmp.re - d_im * b_c10_tmp_tmp.im);
    d_im =
        0.766044443118978 * (d_re * b_c10_tmp_tmp.im + d_im * b_c10_tmp_tmp.re);
    d_re = -7482.2499999999964 * dc8.re - 12959.637154932234 * dc8.im;
    e_im = -7482.2499999999964 * dc8.im + 12959.637154932234 * dc8.re;
    e_re = d_re * dc9.re - e_im * dc9.im;
    e_im = d_re * dc9.im + e_im * dc9.re;
    d_re = 14964.5 * dc10.re - 0.0 * dc10.im;
    hb_scp0_idx_0_tmp_tmp = 14964.5 * dc10.im + 0.0 * dc10.re;
    h_re = d_re * dc11.re - hb_scp0_idx_0_tmp_tmp * dc11.im;
    hb_scp0_idx_0_tmp_tmp = d_re * dc11.im + hb_scp0_idx_0_tmp_tmp * dc11.re;
    d_re = 7482.25 * dc12.re - 0.0 * dc12.im;
    ib_scp0_idx_0_tmp_tmp = 7482.25 * dc12.im + 0.0 * dc12.re;
    f_re = d_re * dc13.re - ib_scp0_idx_0_tmp_tmp * dc13.im;
    ib_scp0_idx_0_tmp_tmp = d_re * dc13.im + ib_scp0_idx_0_tmp_tmp * dc13.re;
    d_re = 0.766044443118978 *
           (f_re * b_c10_tmp_tmp.re - ib_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.im);
    ib_scp0_idx_0_tmp_tmp =
        0.766044443118978 *
        (f_re * b_c10_tmp_tmp.im + ib_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.re);
    f_re = -7482.2499999999964 * dc14.re - 12959.637154932234 * dc14.im;
    ob_scp0_idx_0_tmp_tmp =
        -7482.2499999999964 * dc14.im + 12959.637154932234 * dc14.re;
    i_re = f_re * dc15.re - ob_scp0_idx_0_tmp_tmp * dc15.im;
    ob_scp0_idx_0_tmp_tmp = f_re * dc15.im + ob_scp0_idx_0_tmp_tmp * dc15.re;
    f_re = i_re * dc16.re - ob_scp0_idx_0_tmp_tmp * dc16.im;
    ob_scp0_idx_0_tmp_tmp = i_re * dc16.im + ob_scp0_idx_0_tmp_tmp * dc16.re;
    cphi = 0.766044443118978 * j_scp0_idx_0_tmp_tmp;
    ccr0 = 0.766044443118978 * k_scp0_idx_0_tmp_tmp;
    i_re = 0.766044443118978 * (-3741.1250000000032 * c10_tmp.re -
                                -6479.8185774661151 * c10_tmp.im);
    i_scp0_idx_0_tmp_tmp =
        0.766044443118978 *
        (-3741.1250000000032 * c10_tmp.im + -6479.8185774661151 * c10_tmp.re);
    w1_idx_2 = 0.766044443118978 * (l_scp0_idx_0_tmp_tmp * d_c10_tmp.re -
                                    m_scp0_idx_0_tmp_tmp * d_c10_tmp.im);
    w2_idx_0 = 0.766044443118978 * (l_scp0_idx_0_tmp_tmp * d_c10_tmp.im +
                                    m_scp0_idx_0_tmp_tmp * d_c10_tmp.re);
    cp01_idx_0 = 0.766044443118978 * (j_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.re -
                                      k_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.im);
    scr0 = 0.766044443118978 * (j_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.im +
                                k_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.re);
    j_re = -7482.2499999999964 * c10_tmp.re - 12959.637154932234 * c10_tmp.im;
    q_scp0_idx_0_tmp_tmp =
        -7482.2499999999964 * c10_tmp.im + 12959.637154932234 * c10_tmp.re;
    g_re = -7482.2500000000064 * dc17.re - -12959.63715493223 * dc17.im;
    y_scp0_idx_0_tmp_tmp =
        -7482.2500000000064 * dc17.im + -12959.63715493223 * dc17.re;
    jb_scp0_idx_0_tmp_tmp =
        -3741.1250000000032 * dc18.re - -6479.8185774661151 * dc18.im;
    ab_scp0_idx_0_tmp_tmp =
        -3741.1250000000032 * dc18.im + -6479.8185774661151 * dc18.re;
    r_scp0_idx_0_tmp_tmp =
        0.766044443118978 * (jb_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.re -
                             ab_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.im);
    ab_scp0_idx_0_tmp_tmp =
        0.766044443118978 * (jb_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.im +
                             ab_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.re);
    jb_scp0_idx_0_tmp_tmp =
        -7482.2499999999964 * dc19.re - 12959.637154932234 * dc19.im;
    s_scp0_idx_0_tmp_tmp =
        -7482.2499999999964 * dc19.im + 12959.637154932234 * dc19.re;
    t_scp0_idx_0_tmp_tmp = 14964.5 * dc20.re;
    u_scp0_idx_0_tmp_tmp = 14964.5 * dc20.im;
    v_scp0_idx_0_tmp_tmp =
        t_scp0_idx_0_tmp_tmp * dc21.re - u_scp0_idx_0_tmp_tmp * dc21.im;
    u_scp0_idx_0_tmp_tmp =
        t_scp0_idx_0_tmp_tmp * dc21.im + u_scp0_idx_0_tmp_tmp * dc21.re;
    t_scp0_idx_0_tmp_tmp = 7482.25 * dc22.re;
    w_scp0_idx_0_tmp_tmp = 7482.25 * dc22.im;
    gb_scp0_idx_0_tmp_tmp =
        t_scp0_idx_0_tmp_tmp * dc23.re - w_scp0_idx_0_tmp_tmp * dc23.im;
    w_scp0_idx_0_tmp_tmp =
        t_scp0_idx_0_tmp_tmp * dc23.im + w_scp0_idx_0_tmp_tmp * dc23.re;
    t_scp0_idx_0_tmp_tmp =
        0.766044443118978 * (gb_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.re -
                             w_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.im);
    w_scp0_idx_0_tmp_tmp =
        0.766044443118978 * (gb_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.im +
                             w_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.re);
    gb_scp0_idx_0_tmp_tmp =
        -7482.2499999999964 * dc24.re - 12959.637154932234 * dc24.im;
    x_scp0_idx_0_tmp_tmp =
        -7482.2499999999964 * dc24.im + 12959.637154932234 * dc24.re;
    nb_scp0_idx_0_tmp_tmp =
        gb_scp0_idx_0_tmp_tmp * dc25.re - x_scp0_idx_0_tmp_tmp * dc25.im;
    x_scp0_idx_0_tmp_tmp =
        gb_scp0_idx_0_tmp_tmp * dc25.im + x_scp0_idx_0_tmp_tmp * dc25.re;
    gb_scp0_idx_0_tmp_tmp = -(
        (((((((((((((((m_re * 0.0 - f_im) - 4963.8290136870382) -
                     (n_re * c_c10_tmp.re -
                      p_scp0_idx_0_tmp_tmp * c_c10_tmp.im) *
                         0.766044443118978) +
                    (p_re * 0.0 - kb_scp0_idx_0_tmp_tmp)) +
                   (o_re * b_c10_tmp.re -
                    lb_scp0_idx_0_tmp_tmp * b_c10_tmp.im) *
                       0.766044443118978) +
                  4963.8290136870419) -
                 (k_re * d_c10_tmp.re - mb_scp0_idx_0_tmp_tmp * d_c10_tmp.im) *
                     0.766044443118978) -
                (b_sc5_tmp_tmp * 0.0 - scp0_idx_0_tmp_tmp_tmp)) -
               (re * 0.0 - im)) +
              (b_re * b_c10_tmp.re - b_im * b_c10_tmp.im) * 0.766044443118978) +
             (c_re * b_c10_tmp_tmp.re - c_im * b_c10_tmp_tmp.im) *
                 0.766044443118978) -
            (l_re * 0.0 - d_im)) +
           (e_re * b_c10_tmp_tmp.re - e_im * b_c10_tmp_tmp.im) *
               0.766044443118978) +
          (h_re * b_c10_tmp_tmp.re - hb_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.im) *
              0.766044443118978) +
         (d_re * 0.0 - ib_scp0_idx_0_tmp_tmp)) +
        (f_re * b_c10_tmp_tmp.re - ob_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.im) *
            0.766044443118978);
    f_im = -(
        (((((((((((((((m_re + f_im * 0.0) + 2865.868017263489) -
                     (n_re * c_c10_tmp.im +
                      p_scp0_idx_0_tmp_tmp * c_c10_tmp.re) *
                         0.766044443118978) +
                    (p_re + kb_scp0_idx_0_tmp_tmp * 0.0)) +
                   (o_re * b_c10_tmp.im +
                    lb_scp0_idx_0_tmp_tmp * b_c10_tmp.re) *
                       0.766044443118978) +
                  2865.8680172634845) -
                 (k_re * d_c10_tmp.im + mb_scp0_idx_0_tmp_tmp * d_c10_tmp.re) *
                     0.766044443118978) -
                (b_sc5_tmp_tmp + scp0_idx_0_tmp_tmp_tmp * 0.0)) -
               (re + im * 0.0)) +
              (b_re * b_c10_tmp.im + b_im * b_c10_tmp.re) * 0.766044443118978) +
             (c_re * b_c10_tmp_tmp.im + c_im * b_c10_tmp_tmp.re) *
                 0.766044443118978) -
            (l_re + d_im * 0.0)) +
           (e_re * b_c10_tmp_tmp.im + e_im * b_c10_tmp_tmp.re) *
               0.766044443118978) +
          (h_re * b_c10_tmp_tmp.im + hb_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.re) *
              0.766044443118978) +
         (d_re + ib_scp0_idx_0_tmp_tmp * 0.0)) +
        (f_re * b_c10_tmp_tmp.im + ob_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.re) *
            0.766044443118978);
    cp02_idx_0 =
        (((((((((((((((cphi * 0.0 - ccr0) - 4963.8290136870382) +
                     (-7482.2500000000064 * c_c10_tmp.re -
                      -12959.63715493223 * c_c10_tmp.im) *
                         0.766044443118978) +
                    (i_re * 0.0 - i_scp0_idx_0_tmp_tmp)) +
                   (-7482.2499999999964 * b_c10_tmp.re -
                    12959.637154932234 * b_c10_tmp.im) *
                       0.766044443118978) +
                  4963.8290136870419) +
                 (cc4_tmp * d_c10_tmp.re - sc4 * d_c10_tmp.im) *
                     0.766044443118978) -
                (w1_idx_2 * 0.0 - w2_idx_0)) -
               (cp01_idx_0 * 0.0 - scr0)) +
              (j_re * b_c10_tmp.re - q_scp0_idx_0_tmp_tmp * b_c10_tmp.im) *
                  0.766044443118978) -
             (g_re * b_c10_tmp_tmp.re -
              y_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.im) *
                 0.766044443118978) -
            (r_scp0_idx_0_tmp_tmp * 0.0 - ab_scp0_idx_0_tmp_tmp)) +
           (jb_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.re -
            s_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.im) *
               0.766044443118978) -
          (v_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.re -
           u_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.im) *
              0.766044443118978) +
         (t_scp0_idx_0_tmp_tmp * 0.0 - w_scp0_idx_0_tmp_tmp)) +
        (nb_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.re -
         x_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.im) *
            0.766044443118978;
    ccr0 = (((((((((((((((cphi + ccr0 * 0.0) + 2865.868017263489) +
                        (-7482.2500000000064 * c_c10_tmp.im +
                         -12959.63715493223 * c_c10_tmp.re) *
                            0.766044443118978) +
                       (i_re + i_scp0_idx_0_tmp_tmp * 0.0)) +
                      (-7482.2499999999964 * b_c10_tmp.im +
                       12959.637154932234 * b_c10_tmp.re) *
                          0.766044443118978) +
                     2865.8680172634845) +
                    (cc4_tmp * d_c10_tmp.im + sc4 * d_c10_tmp.re) *
                        0.766044443118978) -
                   (w1_idx_2 + w2_idx_0 * 0.0)) -
                  (cp01_idx_0 + scr0 * 0.0)) +
                 (j_re * b_c10_tmp.im + q_scp0_idx_0_tmp_tmp * b_c10_tmp.re) *
                     0.766044443118978) -
                (g_re * b_c10_tmp_tmp.im +
                 y_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.re) *
                    0.766044443118978) -
               (r_scp0_idx_0_tmp_tmp + ab_scp0_idx_0_tmp_tmp * 0.0)) +
              (jb_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.im +
               s_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.re) *
                  0.766044443118978) -
             (v_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.im +
              u_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.re) *
                 0.766044443118978) +
            (t_scp0_idx_0_tmp_tmp + w_scp0_idx_0_tmp_tmp * 0.0)) +
           (nb_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.im +
            x_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.re) *
               0.766044443118978;
    cp01_idx_0 = b_a.re * b_a.re - b_a.im * b_a.im;
    cphi = b_a.re * b_a.im;
    cphi += cphi;
    if (cphi == 0.0) {
      cp01_idx_0 /= 4.0;
      cphi = 0.0;
    } else if (cp01_idx_0 == 0.0) {
      cp01_idx_0 = 0.0;
      cphi /= 4.0;
    } else {
      cp01_idx_0 /= 4.0;
      cphi /= 4.0;
    }
    dc.re = (gb_scp0_idx_0_tmp_tmp * cp02_idx_0 - f_im * ccr0) + cp01_idx_0;
    dc.im = (gb_scp0_idx_0_tmp_tmp * ccr0 + f_im * cp02_idx_0) + cphi;
    b_c20_tmp = power(dc);
    b_a.re = b_OBL_tmp_tmp * (0.86602540378443871 * c_c20_tmp.re);
    b_a.im = b_OBL_tmp_tmp * (0.86602540378443871 * c_c20_tmp.im);
    e_c10_tmp.re =
        0.49999999999999994 *
        (OBL_tmp * (c_OBL_tmp_tmp * (-0.49999999999999978 * c_c20_tmp.re)));
    e_c10_tmp.im =
        0.49999999999999994 *
        (OBL_tmp * (c_OBL_tmp_tmp * (-0.49999999999999978 * c_c20_tmp.im)));
    cphi = OBL_tmp_tmp * (c_OBL_tmp_tmp * c_c20_tmp.re);
    ccr0 = OBL_tmp_tmp * (c_OBL_tmp_tmp * c_c20_tmp.im);
    c_c20_tmp.re = 0.49999999999999994 * (0.86602540378443871 * cphi);
    c_c20_tmp.im = 0.49999999999999994 * (0.86602540378443871 * ccr0);
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
    m_re = 1.832622702584056E-12 * c10_tmp_tmp.re -
           29928.999999999989 * c10_tmp_tmp.im;
    f_im = 1.832622702584056E-12 * c10_tmp_tmp.im +
           29928.999999999989 * c10_tmp_tmp.re;
    n_re = m_re * c_c10_tmp.re - f_im * c_c10_tmp.im;
    f_im = m_re * c_c10_tmp.im + f_im * c_c10_tmp.re;
    m_re = n_re * b_c10_tmp.re - f_im * b_c10_tmp.im;
    f_im = n_re * b_c10_tmp.im + f_im * b_c10_tmp.re;
    n_re = cc4 * c_c10_tmp.re - crw * c_c10_tmp.im;
    p_scp0_idx_0_tmp_tmp = cc4 * c_c10_tmp.im + crw * c_c10_tmp.re;
    o_re = n_re * b_c10_tmp.re - p_scp0_idx_0_tmp_tmp * b_c10_tmp.im;
    p_scp0_idx_0_tmp_tmp =
        n_re * b_c10_tmp.im + p_scp0_idx_0_tmp_tmp * b_c10_tmp.re;
    n_re = 14964.5 * dc.re;
    kb_scp0_idx_0_tmp_tmp = 14964.5 * dc.im;
    p_re = 0.766044443118978 * (7482.25 * dc1.re);
    lb_scp0_idx_0_tmp_tmp = 0.766044443118978 * (7482.25 * dc1.im);
    k_re = 0.766044443118978 *
           (-7482.25 * dc3.re - 9.1631135129202838E-13 * dc3.im);
    mb_scp0_idx_0_tmp_tmp =
        0.766044443118978 *
        (-7482.25 * dc3.im + 9.1631135129202838E-13 * dc3.re);
    l_re = 14964.5 * dc4.re;
    scp0_idx_0_tmp_tmp_tmp = 14964.5 * dc4.im;
    b_sc5_tmp_tmp = 7482.25 * dc5.re;
    im = 7482.25 * dc5.im;
    re = 0.766044443118978 *
         (b_sc5_tmp_tmp * b_c10_tmp_tmp.re - im * b_c10_tmp_tmp.im);
    im = 0.766044443118978 *
         (b_sc5_tmp_tmp * b_c10_tmp_tmp.im + im * b_c10_tmp_tmp.re);
    b_sc5_tmp_tmp = 9.1631135129202838E-13 * dc6.re - 14964.5 * dc6.im;
    b_im = 9.1631135129202838E-13 * dc6.im + 14964.5 * dc6.re;
    b_re = -14964.5 * dc8.re - 1.8326227025840568E-12 * dc8.im;
    c_im = -14964.5 * dc8.im + 1.8326227025840568E-12 * dc8.re;
    c_re = -7482.25 * dc10.re - 9.1631135129202838E-13 * dc10.im;
    d_im = -7482.25 * dc10.im + 9.1631135129202838E-13 * dc10.re;
    d_re = 0.766044443118978 * (c_re * dc11.re - d_im * dc11.im);
    d_im = 0.766044443118978 * (c_re * dc11.im + d_im * dc11.re);
    c_re = 9.1631135129202838E-13 * dc12.re - 14964.5 * dc12.im;
    e_im = 9.1631135129202838E-13 * dc12.im + 14964.5 * dc12.re;
    e_re = -7482.25 * dc13.re - 9.1631135129202838E-13 * dc13.im;
    hb_scp0_idx_0_tmp_tmp =
        -7482.25 * dc13.im + 9.1631135129202838E-13 * dc13.re;
    h_re = 0.766044443118978 *
           (e_re * b_c10_tmp_tmp.re - hb_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.im);
    hb_scp0_idx_0_tmp_tmp =
        0.766044443118978 *
        (e_re * b_c10_tmp_tmp.im + hb_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.re);
    e_re = 9.1631135129202838E-13 * dc14.re - 14964.5 * dc14.im;
    ib_scp0_idx_0_tmp_tmp =
        9.1631135129202838E-13 * dc14.im + 14964.5 * dc14.re;
    f_re = e_re * dc15.re - ib_scp0_idx_0_tmp_tmp * dc15.im;
    ib_scp0_idx_0_tmp_tmp = e_re * dc15.im + ib_scp0_idx_0_tmp_tmp * dc15.re;
    e_re = -14964.5 * dc16.re - 1.8326227025840568E-12 * dc16.im;
    ob_scp0_idx_0_tmp_tmp =
        -14964.5 * dc16.im + 1.8326227025840568E-12 * dc16.re;
    i_re = e_re * dc17.re - ob_scp0_idx_0_tmp_tmp * dc17.im;
    ob_scp0_idx_0_tmp_tmp = e_re * dc17.im + ob_scp0_idx_0_tmp_tmp * dc17.re;
    e_re = -7482.25 * dc18.re - 9.1631135129202838E-13 * dc18.im;
    i_scp0_idx_0_tmp_tmp =
        -7482.25 * dc18.im + 9.1631135129202838E-13 * dc18.re;
    j_re = e_re * dc19.re - i_scp0_idx_0_tmp_tmp * dc19.im;
    i_scp0_idx_0_tmp_tmp = e_re * dc19.im + i_scp0_idx_0_tmp_tmp * dc19.re;
    e_re = 0.766044443118978 *
           (j_re * b_c10_tmp_tmp.re - i_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.im);
    i_scp0_idx_0_tmp_tmp =
        0.766044443118978 *
        (j_re * b_c10_tmp_tmp.im + i_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.re);
    cc4_tmp = ((((g_c10_tmp.re -
                  (m_re * c_c10_tmp_tmp.re - f_im * c_c10_tmp_tmp.im)) +
                 (o_re * c_c10_tmp_tmp.re -
                  p_scp0_idx_0_tmp_tmp * c_c10_tmp_tmp.im)) +
                i_c10_tmp.re) -
               j_c10_tmp.re) -
              h_c10_tmp.re;
    ccr0 = ((((g_c10_tmp.im -
               (m_re * c_c10_tmp_tmp.im + f_im * c_c10_tmp_tmp.re)) +
              (o_re * c_c10_tmp_tmp.im +
               p_scp0_idx_0_tmp_tmp * c_c10_tmp_tmp.re)) +
             i_c10_tmp.im) -
            j_c10_tmp.im) -
           h_c10_tmp.im;
    scr0 =
        (((((((((((((n_re * 0.766044443118978 +
                     (p_re * 0.0 - lb_scp0_idx_0_tmp_tmp)) -
                    4963.8290136870392) +
                   (9.1631135129202838E-13 * dc2.re - 14964.5 * dc2.im) *
                       0.766044443118978) +
                  (k_re * 0.0 - mb_scp0_idx_0_tmp_tmp)) -
                 (l_re * b_c10_tmp_tmp.re -
                  scp0_idx_0_tmp_tmp_tmp * b_c10_tmp_tmp.im) *
                     0.766044443118978) -
                (re * 0.0 - im)) +
               (b_sc5_tmp_tmp * dc7.re - b_im * dc7.im) * 0.766044443118978) +
              (b_re * dc9.re - c_im * dc9.im) * 0.766044443118978) -
             (d_re * 0.0 - d_im)) +
            (c_re * b_c10_tmp_tmp.re - e_im * b_c10_tmp_tmp.im) *
                0.766044443118978) -
           (h_re * 0.0 - hb_scp0_idx_0_tmp_tmp)) +
          (f_re * b_c10_tmp_tmp.re - ib_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.im) *
              0.766044443118978) -
         (i_re * b_c10_tmp_tmp.re - ob_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.im) *
             0.766044443118978) +
        (e_re * 0.0 - i_scp0_idx_0_tmp_tmp);
    cp02_idx_0 =
        ((((((((((((((kb_scp0_idx_0_tmp_tmp * 0.766044443118978 -
                      5731.7360345269735) +
                     (p_re + lb_scp0_idx_0_tmp_tmp * 0.0)) +
                    2865.8680172634872) +
                   (9.1631135129202838E-13 * dc2.im + 14964.5 * dc2.re) *
                       0.766044443118978) +
                  (k_re + mb_scp0_idx_0_tmp_tmp * 0.0)) -
                 (l_re * b_c10_tmp_tmp.im +
                  scp0_idx_0_tmp_tmp_tmp * b_c10_tmp_tmp.re) *
                     0.766044443118978) -
                (re + im * 0.0)) +
               (b_sc5_tmp_tmp * dc7.im + b_im * dc7.re) * 0.766044443118978) +
              (b_re * dc9.im + c_im * dc9.re) * 0.766044443118978) -
             (d_re + d_im * 0.0)) +
            (c_re * b_c10_tmp_tmp.im + e_im * b_c10_tmp_tmp.re) *
                0.766044443118978) -
           (h_re + hb_scp0_idx_0_tmp_tmp * 0.0)) +
          (f_re * b_c10_tmp_tmp.im + ib_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.re) *
              0.766044443118978) -
         (i_re * b_c10_tmp_tmp.im + ob_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.re) *
             0.766044443118978) +
        (e_re + i_scp0_idx_0_tmp_tmp * 0.0);
    if (cp02_idx_0 == 0.0) {
      if (ccr0 == 0.0) {
        dc.re = cc4_tmp / scr0;
        dc.im = 0.0;
      } else if (cc4_tmp == 0.0) {
        dc.re = 0.0;
        dc.im = ccr0 / scr0;
      } else {
        dc.re = cc4_tmp / scr0;
        dc.im = ccr0 / scr0;
      }
    } else if (scr0 == 0.0) {
      if (cc4_tmp == 0.0) {
        dc.re = ccr0 / cp02_idx_0;
        dc.im = 0.0;
      } else if (ccr0 == 0.0) {
        dc.re = 0.0;
        dc.im = -(cc4_tmp / cp02_idx_0);
      } else {
        dc.re = ccr0 / cp02_idx_0;
        dc.im = -(cc4_tmp / cp02_idx_0);
      }
    } else {
      crw = fabs(scr0);
      cphi = fabs(cp02_idx_0);
      if (crw > cphi) {
        cp01_idx_0 = cp02_idx_0 / scr0;
        cphi = scr0 + cp01_idx_0 * cp02_idx_0;
        dc.re = (cc4_tmp + cp01_idx_0 * ccr0) / cphi;
        dc.im = (ccr0 - cp01_idx_0 * cc4_tmp) / cphi;
      } else if (cphi == crw) {
        if (scr0 > 0.0) {
          cp01_idx_0 = 0.5;
        } else {
          cp01_idx_0 = -0.5;
        }
        if (cp02_idx_0 > 0.0) {
          cphi = 0.5;
        } else {
          cphi = -0.5;
        }
        dc.re = (cc4_tmp * cp01_idx_0 + ccr0 * cphi) / crw;
        dc.im = (ccr0 * cp01_idx_0 - cc4_tmp * cphi) / crw;
      } else {
        cp01_idx_0 = scr0 / cp02_idx_0;
        cphi = cp02_idx_0 + cp01_idx_0 * scr0;
        dc.re = (cp01_idx_0 * cc4_tmp + ccr0) / cphi;
        dc.im = (cp01_idx_0 * ccr0 - cc4_tmp) / cphi;
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
    m_re = 1.832622702584056E-12 * dc1.re - 29928.999999999989 * dc1.im;
    f_im = 1.832622702584056E-12 * dc1.im + 29928.999999999989 * dc1.re;
    n_re = m_re * dc2.re - f_im * dc2.im;
    f_im = m_re * dc2.im + f_im * dc2.re;
    m_re = n_re * dc3.re - f_im * dc3.im;
    f_im = n_re * dc3.im + f_im * dc3.re;
    n_re = 3.6652454051681135E-12 * dc4.re - 59858.0 * dc4.im;
    p_scp0_idx_0_tmp_tmp = 3.6652454051681135E-12 * dc4.im + 59858.0 * dc4.re;
    o_re = n_re * dc5.re - p_scp0_idx_0_tmp_tmp * dc5.im;
    p_scp0_idx_0_tmp_tmp = n_re * dc5.im + p_scp0_idx_0_tmp_tmp * dc5.re;
    n_re = o_re * dc6.re - p_scp0_idx_0_tmp_tmp * dc6.im;
    p_scp0_idx_0_tmp_tmp = o_re * dc6.im + p_scp0_idx_0_tmp_tmp * dc6.re;
    o_re = 0.766044443118978 * (7482.25 * dc8.re);
    kb_scp0_idx_0_tmp_tmp = 0.766044443118978 * (7482.25 * dc8.im);
    p_re = 0.766044443118978 *
           (-7482.25 * dc10.re - 9.1631135129202838E-13 * dc10.im);
    lb_scp0_idx_0_tmp_tmp =
        0.766044443118978 *
        (-7482.25 * dc10.im + 9.1631135129202838E-13 * dc10.re);
    k_re = 14964.5 * dc11.re;
    mb_scp0_idx_0_tmp_tmp = 14964.5 * dc11.im;
    l_re = 7482.25 * dc12.re;
    scp0_idx_0_tmp_tmp_tmp = 7482.25 * dc12.im;
    b_sc5_tmp_tmp =
        0.766044443118978 *
        (l_re * b_c10_tmp_tmp.re - scp0_idx_0_tmp_tmp_tmp * b_c10_tmp_tmp.im);
    scp0_idx_0_tmp_tmp_tmp =
        0.766044443118978 *
        (l_re * b_c10_tmp_tmp.im + scp0_idx_0_tmp_tmp_tmp * b_c10_tmp_tmp.re);
    l_re = 9.1631135129202838E-13 * dc13.re - 14964.5 * dc13.im;
    im = 9.1631135129202838E-13 * dc13.im + 14964.5 * dc13.re;
    re = -14964.5 * dc15.re - 1.8326227025840568E-12 * dc15.im;
    b_im = -14964.5 * dc15.im + 1.8326227025840568E-12 * dc15.re;
    b_re = -7482.25 * dc17.re - 9.1631135129202838E-13 * dc17.im;
    c_im = -7482.25 * dc17.im + 9.1631135129202838E-13 * dc17.re;
    c_re = 0.766044443118978 * (b_re * dc18.re - c_im * dc18.im);
    c_im = 0.766044443118978 * (b_re * dc18.im + c_im * dc18.re);
    b_re = 9.1631135129202838E-13 * dc19.re - 14964.5 * dc19.im;
    d_im = 9.1631135129202838E-13 * dc19.im + 14964.5 * dc19.re;
    d_re = -7482.25 * dc20.re - 9.1631135129202838E-13 * dc20.im;
    e_im = -7482.25 * dc20.im + 9.1631135129202838E-13 * dc20.re;
    e_re =
        0.766044443118978 * (d_re * b_c10_tmp_tmp.re - e_im * b_c10_tmp_tmp.im);
    e_im =
        0.766044443118978 * (d_re * b_c10_tmp_tmp.im + e_im * b_c10_tmp_tmp.re);
    d_re = 9.1631135129202838E-13 * dc21.re - 14964.5 * dc21.im;
    hb_scp0_idx_0_tmp_tmp =
        9.1631135129202838E-13 * dc21.im + 14964.5 * dc21.re;
    h_re = d_re * dc22.re - hb_scp0_idx_0_tmp_tmp * dc22.im;
    hb_scp0_idx_0_tmp_tmp = d_re * dc22.im + hb_scp0_idx_0_tmp_tmp * dc22.re;
    d_re = -14964.5 * dc23.re - 1.8326227025840568E-12 * dc23.im;
    ib_scp0_idx_0_tmp_tmp =
        -14964.5 * dc23.im + 1.8326227025840568E-12 * dc23.re;
    f_re = d_re * dc24.re - ib_scp0_idx_0_tmp_tmp * dc24.im;
    ib_scp0_idx_0_tmp_tmp = d_re * dc24.im + ib_scp0_idx_0_tmp_tmp * dc24.re;
    d_re = -7482.25 * dc25.re - 9.1631135129202838E-13 * dc25.im;
    ob_scp0_idx_0_tmp_tmp =
        -7482.25 * dc25.im + 9.1631135129202838E-13 * dc25.re;
    i_re = d_re * dc26.re - ob_scp0_idx_0_tmp_tmp * dc26.im;
    ob_scp0_idx_0_tmp_tmp = d_re * dc26.im + ob_scp0_idx_0_tmp_tmp * dc26.re;
    d_re = 0.766044443118978 *
           (i_re * b_c10_tmp_tmp.re - ob_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.im);
    ob_scp0_idx_0_tmp_tmp =
        0.766044443118978 *
        (i_re * b_c10_tmp_tmp.im + ob_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.re);
    cc4_tmp = -(((((g_c10_tmp.re +
                    (m_re * c_c10_tmp_tmp.re - f_im * c_c10_tmp_tmp.im)) -
                   (n_re * c_c10_tmp_tmp.re -
                    p_scp0_idx_0_tmp_tmp * c_c10_tmp_tmp.im)) -
                  i_c10_tmp.re) +
                 j_c10_tmp.re) +
                h_c10_tmp.re);
    ccr0 = -(((((g_c10_tmp.im +
                 (m_re * c_c10_tmp_tmp.im + f_im * c_c10_tmp_tmp.re)) -
                (n_re * c_c10_tmp_tmp.im +
                 p_scp0_idx_0_tmp_tmp * c_c10_tmp_tmp.re)) -
               i_c10_tmp.im) +
              j_c10_tmp.im) +
             h_c10_tmp.im);
    scr0 =
        (((((((((((((14964.5 * dc7.re * 0.766044443118978 +
                     (o_re * 0.0 - kb_scp0_idx_0_tmp_tmp)) -
                    4963.8290136870392) +
                   (9.1631135129202838E-13 * dc9.re - 14964.5 * dc9.im) *
                       0.766044443118978) +
                  (p_re * 0.0 - lb_scp0_idx_0_tmp_tmp)) -
                 (k_re * b_c10_tmp_tmp.re -
                  mb_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.im) *
                     0.766044443118978) -
                (b_sc5_tmp_tmp * 0.0 - scp0_idx_0_tmp_tmp_tmp)) +
               (l_re * dc14.re - im * dc14.im) * 0.766044443118978) +
              (re * dc16.re - b_im * dc16.im) * 0.766044443118978) -
             (c_re * 0.0 - c_im)) +
            (b_re * b_c10_tmp_tmp.re - d_im * b_c10_tmp_tmp.im) *
                0.766044443118978) -
           (e_re * 0.0 - e_im)) +
          (h_re * b_c10_tmp_tmp.re - hb_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.im) *
              0.766044443118978) -
         (f_re * b_c10_tmp_tmp.re - ib_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.im) *
             0.766044443118978) +
        (d_re * 0.0 - ob_scp0_idx_0_tmp_tmp);
    cp02_idx_0 =
        ((((((((((((((14964.5 * dc7.im * 0.766044443118978 -
                      5731.7360345269735) +
                     (o_re + kb_scp0_idx_0_tmp_tmp * 0.0)) +
                    2865.8680172634872) +
                   (9.1631135129202838E-13 * dc9.im + 14964.5 * dc9.re) *
                       0.766044443118978) +
                  (p_re + lb_scp0_idx_0_tmp_tmp * 0.0)) -
                 (k_re * b_c10_tmp_tmp.im +
                  mb_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.re) *
                     0.766044443118978) -
                (b_sc5_tmp_tmp + scp0_idx_0_tmp_tmp_tmp * 0.0)) +
               (l_re * dc14.im + im * dc14.re) * 0.766044443118978) +
              (re * dc16.im + b_im * dc16.re) * 0.766044443118978) -
             (c_re + c_im * 0.0)) +
            (b_re * b_c10_tmp_tmp.im + d_im * b_c10_tmp_tmp.re) *
                0.766044443118978) -
           (e_re + e_im * 0.0)) +
          (h_re * b_c10_tmp_tmp.im + hb_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.re) *
              0.766044443118978) -
         (f_re * b_c10_tmp_tmp.im + ib_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.re) *
             0.766044443118978) +
        (d_re + ob_scp0_idx_0_tmp_tmp * 0.0);
    if (cp02_idx_0 == 0.0) {
      if (ccr0 == 0.0) {
        dc1.re = cc4_tmp / scr0;
        dc1.im = 0.0;
      } else if (cc4_tmp == 0.0) {
        dc1.re = 0.0;
        dc1.im = ccr0 / scr0;
      } else {
        dc1.re = cc4_tmp / scr0;
        dc1.im = ccr0 / scr0;
      }
    } else if (scr0 == 0.0) {
      if (cc4_tmp == 0.0) {
        dc1.re = ccr0 / cp02_idx_0;
        dc1.im = 0.0;
      } else if (ccr0 == 0.0) {
        dc1.re = 0.0;
        dc1.im = -(cc4_tmp / cp02_idx_0);
      } else {
        dc1.re = ccr0 / cp02_idx_0;
        dc1.im = -(cc4_tmp / cp02_idx_0);
      }
    } else {
      crw = fabs(scr0);
      cphi = fabs(cp02_idx_0);
      if (crw > cphi) {
        cp01_idx_0 = cp02_idx_0 / scr0;
        cphi = scr0 + cp01_idx_0 * cp02_idx_0;
        dc1.re = (cc4_tmp + cp01_idx_0 * ccr0) / cphi;
        dc1.im = (ccr0 - cp01_idx_0 * cc4_tmp) / cphi;
      } else if (cphi == crw) {
        if (scr0 > 0.0) {
          cp01_idx_0 = 0.5;
        } else {
          cp01_idx_0 = -0.5;
        }
        if (cp02_idx_0 > 0.0) {
          cphi = 0.5;
        } else {
          cphi = -0.5;
        }
        dc1.re = (cc4_tmp * cp01_idx_0 + ccr0 * cphi) / crw;
        dc1.im = (ccr0 * cp01_idx_0 - cc4_tmp * cphi) / crw;
      } else {
        cp01_idx_0 = scr0 / cp02_idx_0;
        cphi = cp02_idx_0 + cp01_idx_0 * scr0;
        dc1.re = (cp01_idx_0 * cc4_tmp + ccr0) / cphi;
        dc1.im = (cp01_idx_0 * ccr0 - cc4_tmp) / cphi;
      }
    }
    b_log(&dc1);
    m_re = dc.re * 0.0 - dc.im;
    n_re = dc1.re * 0.0 - dc1.im;
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
    o_re = -14964.499999999987 * c10_tmp_tmp.re -
           25919.274309864457 * c10_tmp_tmp.im;
    f_im = -14964.499999999987 * c10_tmp_tmp.im +
           25919.274309864457 * c10_tmp_tmp.re;
    p_re = o_re * c_c10_tmp.re - f_im * c_c10_tmp.im;
    f_im = o_re * c_c10_tmp.im + f_im * c_c10_tmp.re;
    o_re = p_re * b_c10_tmp.re - f_im * b_c10_tmp.im;
    f_im = p_re * b_c10_tmp.im + f_im * b_c10_tmp.re;
    p_re = w1_idx_1 * c_c10_tmp.re - w1_idx_3 * c_c10_tmp.im;
    p_scp0_idx_0_tmp_tmp = w1_idx_1 * c_c10_tmp.im + w1_idx_3 * c_c10_tmp.re;
    k_re = p_re * b_c10_tmp.re - p_scp0_idx_0_tmp_tmp * b_c10_tmp.im;
    p_scp0_idx_0_tmp_tmp =
        p_re * b_c10_tmp.im + p_scp0_idx_0_tmp_tmp * b_c10_tmp.re;
    p_re = 0.766044443118978 * (7482.25 * dc.re);
    kb_scp0_idx_0_tmp_tmp = 0.766044443118978 * (7482.25 * dc.im);
    l_re = 0.766044443118978 *
           (-3741.1250000000032 * dc2.re - -6479.8185774661151 * dc2.im);
    lb_scp0_idx_0_tmp_tmp = 0.766044443118978 * (-3741.1250000000032 * dc2.im +
                                                 -6479.8185774661151 * dc2.re);
    b_sc5_tmp_tmp = 14964.5 * dc4.re;
    mb_scp0_idx_0_tmp_tmp = 14964.5 * dc4.im;
    re = 7482.25 * dc6.re;
    scp0_idx_0_tmp_tmp_tmp = 7482.25 * dc6.im;
    b_re = 0.766044443118978 * (re * dc7.re - scp0_idx_0_tmp_tmp_tmp * dc7.im);
    scp0_idx_0_tmp_tmp_tmp =
        0.766044443118978 * (re * dc7.im + scp0_idx_0_tmp_tmp_tmp * dc7.re);
    re = 7482.25 * dc8.re;
    im = 7482.25 * dc8.im;
    c_re = 0.766044443118978 * (re * b_c10_tmp_tmp.re - im * b_c10_tmp_tmp.im);
    im = 0.766044443118978 * (re * b_c10_tmp_tmp.im + im * b_c10_tmp_tmp.re);
    re = -7482.2499999999964 * dc9.re - 12959.637154932234 * dc9.im;
    b_im = -7482.2499999999964 * dc9.im + 12959.637154932234 * dc9.re;
    d_re = -7482.2500000000064 * dc11.re - -12959.63715493223 * dc11.im;
    c_im = -7482.2500000000064 * dc11.im + -12959.63715493223 * dc11.re;
    e_re = -3741.1250000000032 * dc12.re - -6479.8185774661151 * dc12.im;
    d_im = -3741.1250000000032 * dc12.im + -6479.8185774661151 * dc12.re;
    h_re =
        0.766044443118978 * (e_re * b_c10_tmp_tmp.re - d_im * b_c10_tmp_tmp.im);
    d_im =
        0.766044443118978 * (e_re * b_c10_tmp_tmp.im + d_im * b_c10_tmp_tmp.re);
    e_re = -7482.2499999999964 * dc13.re - 12959.637154932234 * dc13.im;
    e_im = -7482.2499999999964 * dc13.im + 12959.637154932234 * dc13.re;
    f_re = 14964.5 * dc14.re;
    hb_scp0_idx_0_tmp_tmp = 14964.5 * dc14.im;
    i_re = f_re * dc15.re - hb_scp0_idx_0_tmp_tmp * dc15.im;
    hb_scp0_idx_0_tmp_tmp = f_re * dc15.im + hb_scp0_idx_0_tmp_tmp * dc15.re;
    f_re = 7482.25 * dc16.re;
    ib_scp0_idx_0_tmp_tmp = 7482.25 * dc16.im;
    j_re = f_re * dc17.re - ib_scp0_idx_0_tmp_tmp * dc17.im;
    ib_scp0_idx_0_tmp_tmp = f_re * dc17.im + ib_scp0_idx_0_tmp_tmp * dc17.re;
    f_re = 0.766044443118978 *
           (j_re * b_c10_tmp_tmp.re - ib_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.im);
    ib_scp0_idx_0_tmp_tmp =
        0.766044443118978 *
        (j_re * b_c10_tmp_tmp.im + ib_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.re);
    j_re = -7482.2499999999964 * dc18.re - 12959.637154932234 * dc18.im;
    ob_scp0_idx_0_tmp_tmp =
        -7482.2499999999964 * dc18.im + 12959.637154932234 * dc18.re;
    g_re = j_re * dc19.re - ob_scp0_idx_0_tmp_tmp * dc19.im;
    ob_scp0_idx_0_tmp_tmp = j_re * dc19.im + ob_scp0_idx_0_tmp_tmp * dc19.re;
    cc4_tmp = ((((b_c20_tmp.re -
                  (o_re * c_c10_tmp_tmp.re - f_im * c_c10_tmp_tmp.im)) +
                 (k_re * c_c10_tmp_tmp.re -
                  p_scp0_idx_0_tmp_tmp * c_c10_tmp_tmp.im)) -
                b_a.re) +
               e_c10_tmp.re) -
              c_c20_tmp.re;
    ccr0 = ((((b_c20_tmp.im -
               (o_re * c_c10_tmp_tmp.im + f_im * c_c10_tmp_tmp.re)) +
              (k_re * c_c10_tmp_tmp.im +
               p_scp0_idx_0_tmp_tmp * c_c10_tmp_tmp.re)) -
             b_a.im) +
            e_c10_tmp.im) -
           c_c20_tmp.im;
    scr0 =
        (((((((((((((((p_re * 0.0 - kb_scp0_idx_0_tmp_tmp) -
                      4963.8290136870382) +
                     (-7482.2500000000064 * dc1.re -
                      -12959.63715493223 * dc1.im) *
                         0.766044443118978) +
                    (l_re * 0.0 - lb_scp0_idx_0_tmp_tmp)) +
                   (-7482.2499999999964 * dc3.re -
                    12959.637154932234 * dc3.im) *
                       0.766044443118978) +
                  4963.8290136870419) +
                 (b_sc5_tmp_tmp * dc5.re - mb_scp0_idx_0_tmp_tmp * dc5.im) *
                     0.766044443118978) -
                (b_re * 0.0 - scp0_idx_0_tmp_tmp_tmp)) -
               (c_re * 0.0 - im)) +
              (re * dc10.re - b_im * dc10.im) * 0.766044443118978) -
             (d_re * b_c10_tmp_tmp.re - c_im * b_c10_tmp_tmp.im) *
                 0.766044443118978) -
            (h_re * 0.0 - d_im)) +
           (e_re * b_c10_tmp_tmp.re - e_im * b_c10_tmp_tmp.im) *
               0.766044443118978) -
          (i_re * b_c10_tmp_tmp.re - hb_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.im) *
              0.766044443118978) +
         (f_re * 0.0 - ib_scp0_idx_0_tmp_tmp)) +
        (g_re * b_c10_tmp_tmp.re - ob_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.im) *
            0.766044443118978;
    cp02_idx_0 =
        (((((((((((((((p_re + kb_scp0_idx_0_tmp_tmp * 0.0) +
                      2865.868017263489) +
                     (-7482.2500000000064 * dc1.im +
                      -12959.63715493223 * dc1.re) *
                         0.766044443118978) +
                    (l_re + lb_scp0_idx_0_tmp_tmp * 0.0)) +
                   (-7482.2499999999964 * dc3.im +
                    12959.637154932234 * dc3.re) *
                       0.766044443118978) +
                  2865.8680172634845) +
                 (b_sc5_tmp_tmp * dc5.im + mb_scp0_idx_0_tmp_tmp * dc5.re) *
                     0.766044443118978) -
                (b_re + scp0_idx_0_tmp_tmp_tmp * 0.0)) -
               (c_re + im * 0.0)) +
              (re * dc10.im + b_im * dc10.re) * 0.766044443118978) -
             (d_re * b_c10_tmp_tmp.im + c_im * b_c10_tmp_tmp.re) *
                 0.766044443118978) -
            (h_re + d_im * 0.0)) +
           (e_re * b_c10_tmp_tmp.im + e_im * b_c10_tmp_tmp.re) *
               0.766044443118978) -
          (i_re * b_c10_tmp_tmp.im + hb_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.re) *
              0.766044443118978) +
         (f_re + ib_scp0_idx_0_tmp_tmp * 0.0)) +
        (g_re * b_c10_tmp_tmp.im + ob_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.re) *
            0.766044443118978;
    if (cp02_idx_0 == 0.0) {
      if (ccr0 == 0.0) {
        dc.re = cc4_tmp / scr0;
        dc.im = 0.0;
      } else if (cc4_tmp == 0.0) {
        dc.re = 0.0;
        dc.im = ccr0 / scr0;
      } else {
        dc.re = cc4_tmp / scr0;
        dc.im = ccr0 / scr0;
      }
    } else if (scr0 == 0.0) {
      if (cc4_tmp == 0.0) {
        dc.re = ccr0 / cp02_idx_0;
        dc.im = 0.0;
      } else if (ccr0 == 0.0) {
        dc.re = 0.0;
        dc.im = -(cc4_tmp / cp02_idx_0);
      } else {
        dc.re = ccr0 / cp02_idx_0;
        dc.im = -(cc4_tmp / cp02_idx_0);
      }
    } else {
      crw = fabs(scr0);
      cphi = fabs(cp02_idx_0);
      if (crw > cphi) {
        cp01_idx_0 = cp02_idx_0 / scr0;
        cphi = scr0 + cp01_idx_0 * cp02_idx_0;
        dc.re = (cc4_tmp + cp01_idx_0 * ccr0) / cphi;
        dc.im = (ccr0 - cp01_idx_0 * cc4_tmp) / cphi;
      } else if (cphi == crw) {
        if (scr0 > 0.0) {
          cp01_idx_0 = 0.5;
        } else {
          cp01_idx_0 = -0.5;
        }
        if (cp02_idx_0 > 0.0) {
          cphi = 0.5;
        } else {
          cphi = -0.5;
        }
        dc.re = (cc4_tmp * cp01_idx_0 + ccr0 * cphi) / crw;
        dc.im = (ccr0 * cp01_idx_0 - cc4_tmp * cphi) / crw;
      } else {
        cp01_idx_0 = scr0 / cp02_idx_0;
        cphi = cp02_idx_0 + cp01_idx_0 * scr0;
        dc.re = (cp01_idx_0 * cc4_tmp + ccr0) / cphi;
        dc.im = (cp01_idx_0 * ccr0 - cc4_tmp) / cphi;
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
    o_re = -14964.499999999987 * dc1.re - 25919.274309864457 * dc1.im;
    f_im = -14964.499999999987 * dc1.im + 25919.274309864457 * dc1.re;
    p_re = o_re * dc2.re - f_im * dc2.im;
    f_im = o_re * dc2.im + f_im * dc2.re;
    o_re = p_re * dc3.re - f_im * dc3.im;
    f_im = p_re * dc3.im + f_im * dc3.re;
    p_re = -29928.999999999985 * dc4.re - 51838.548619728936 * dc4.im;
    p_scp0_idx_0_tmp_tmp =
        -29928.999999999985 * dc4.im + 51838.548619728936 * dc4.re;
    k_re = p_re * dc5.re - p_scp0_idx_0_tmp_tmp * dc5.im;
    p_scp0_idx_0_tmp_tmp = p_re * dc5.im + p_scp0_idx_0_tmp_tmp * dc5.re;
    p_re = k_re * dc6.re - p_scp0_idx_0_tmp_tmp * dc6.im;
    p_scp0_idx_0_tmp_tmp = k_re * dc6.im + p_scp0_idx_0_tmp_tmp * dc6.re;
    k_re = 0.766044443118978 * (7482.25 * dc7.re);
    kb_scp0_idx_0_tmp_tmp = 0.766044443118978 * (7482.25 * dc7.im);
    l_re = 0.766044443118978 *
           (-3741.1250000000032 * dc9.re - -6479.8185774661151 * dc9.im);
    lb_scp0_idx_0_tmp_tmp = 0.766044443118978 * (-3741.1250000000032 * dc9.im +
                                                 -6479.8185774661151 * dc9.re);
    b_sc5_tmp_tmp = 14964.5 * dc11.re;
    mb_scp0_idx_0_tmp_tmp = 14964.5 * dc11.im;
    re = 7482.25 * dc13.re;
    scp0_idx_0_tmp_tmp_tmp = 7482.25 * dc13.im;
    b_re =
        0.766044443118978 * (re * dc14.re - scp0_idx_0_tmp_tmp_tmp * dc14.im);
    scp0_idx_0_tmp_tmp_tmp =
        0.766044443118978 * (re * dc14.im + scp0_idx_0_tmp_tmp_tmp * dc14.re);
    re = 7482.25 * dc15.re;
    im = 7482.25 * dc15.im;
    c_re = 0.766044443118978 * (re * b_c10_tmp_tmp.re - im * b_c10_tmp_tmp.im);
    im = 0.766044443118978 * (re * b_c10_tmp_tmp.im + im * b_c10_tmp_tmp.re);
    re = -7482.2499999999964 * dc16.re - 12959.637154932234 * dc16.im;
    b_im = -7482.2499999999964 * dc16.im + 12959.637154932234 * dc16.re;
    d_re = -7482.2500000000064 * dc18.re - -12959.63715493223 * dc18.im;
    c_im = -7482.2500000000064 * dc18.im + -12959.63715493223 * dc18.re;
    e_re = -3741.1250000000032 * dc19.re - -6479.8185774661151 * dc19.im;
    d_im = -3741.1250000000032 * dc19.im + -6479.8185774661151 * dc19.re;
    h_re =
        0.766044443118978 * (e_re * b_c10_tmp_tmp.re - d_im * b_c10_tmp_tmp.im);
    d_im =
        0.766044443118978 * (e_re * b_c10_tmp_tmp.im + d_im * b_c10_tmp_tmp.re);
    e_re = -7482.2499999999964 * dc20.re - 12959.637154932234 * dc20.im;
    e_im = -7482.2499999999964 * dc20.im + 12959.637154932234 * dc20.re;
    f_re = 14964.5 * dc21.re;
    hb_scp0_idx_0_tmp_tmp = 14964.5 * dc21.im;
    i_re = f_re * dc22.re - hb_scp0_idx_0_tmp_tmp * dc22.im;
    hb_scp0_idx_0_tmp_tmp = f_re * dc22.im + hb_scp0_idx_0_tmp_tmp * dc22.re;
    f_re = 7482.25 * dc23.re;
    ib_scp0_idx_0_tmp_tmp = 7482.25 * dc23.im;
    j_re = f_re * dc24.re - ib_scp0_idx_0_tmp_tmp * dc24.im;
    ib_scp0_idx_0_tmp_tmp = f_re * dc24.im + ib_scp0_idx_0_tmp_tmp * dc24.re;
    f_re = 0.766044443118978 *
           (j_re * b_c10_tmp_tmp.re - ib_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.im);
    ib_scp0_idx_0_tmp_tmp =
        0.766044443118978 *
        (j_re * b_c10_tmp_tmp.im + ib_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.re);
    j_re = -7482.2499999999964 * dc25.re - 12959.637154932234 * dc25.im;
    ob_scp0_idx_0_tmp_tmp =
        -7482.2499999999964 * dc25.im + 12959.637154932234 * dc25.re;
    g_re = j_re * dc26.re - ob_scp0_idx_0_tmp_tmp * dc26.im;
    ob_scp0_idx_0_tmp_tmp = j_re * dc26.im + ob_scp0_idx_0_tmp_tmp * dc26.re;
    cc4_tmp = -(((((b_c20_tmp.re +
                    (o_re * c_c10_tmp_tmp.re - f_im * c_c10_tmp_tmp.im)) -
                   (p_re * c_c10_tmp_tmp.re -
                    p_scp0_idx_0_tmp_tmp * c_c10_tmp_tmp.im)) +
                  b_a.re) -
                 e_c10_tmp.re) +
                c_c20_tmp.re);
    ccr0 = -(((((b_c20_tmp.im +
                 (o_re * c_c10_tmp_tmp.im + f_im * c_c10_tmp_tmp.re)) -
                (p_re * c_c10_tmp_tmp.im +
                 p_scp0_idx_0_tmp_tmp * c_c10_tmp_tmp.re)) +
               b_a.im) -
              e_c10_tmp.im) +
             c_c20_tmp.im);
    scr0 =
        (((((((((((((((k_re * 0.0 - kb_scp0_idx_0_tmp_tmp) -
                      4963.8290136870382) +
                     (-7482.2500000000064 * dc8.re -
                      -12959.63715493223 * dc8.im) *
                         0.766044443118978) +
                    (l_re * 0.0 - lb_scp0_idx_0_tmp_tmp)) +
                   (-7482.2499999999964 * dc10.re -
                    12959.637154932234 * dc10.im) *
                       0.766044443118978) +
                  4963.8290136870419) +
                 (b_sc5_tmp_tmp * dc12.re - mb_scp0_idx_0_tmp_tmp * dc12.im) *
                     0.766044443118978) -
                (b_re * 0.0 - scp0_idx_0_tmp_tmp_tmp)) -
               (c_re * 0.0 - im)) +
              (re * dc17.re - b_im * dc17.im) * 0.766044443118978) -
             (d_re * b_c10_tmp_tmp.re - c_im * b_c10_tmp_tmp.im) *
                 0.766044443118978) -
            (h_re * 0.0 - d_im)) +
           (e_re * b_c10_tmp_tmp.re - e_im * b_c10_tmp_tmp.im) *
               0.766044443118978) -
          (i_re * b_c10_tmp_tmp.re - hb_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.im) *
              0.766044443118978) +
         (f_re * 0.0 - ib_scp0_idx_0_tmp_tmp)) +
        (g_re * b_c10_tmp_tmp.re - ob_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.im) *
            0.766044443118978;
    cp02_idx_0 =
        (((((((((((((((k_re + kb_scp0_idx_0_tmp_tmp * 0.0) +
                      2865.868017263489) +
                     (-7482.2500000000064 * dc8.im +
                      -12959.63715493223 * dc8.re) *
                         0.766044443118978) +
                    (l_re + lb_scp0_idx_0_tmp_tmp * 0.0)) +
                   (-7482.2499999999964 * dc10.im +
                    12959.637154932234 * dc10.re) *
                       0.766044443118978) +
                  2865.8680172634845) +
                 (b_sc5_tmp_tmp * dc12.im + mb_scp0_idx_0_tmp_tmp * dc12.re) *
                     0.766044443118978) -
                (b_re + scp0_idx_0_tmp_tmp_tmp * 0.0)) -
               (c_re + im * 0.0)) +
              (re * dc17.im + b_im * dc17.re) * 0.766044443118978) -
             (d_re * b_c10_tmp_tmp.im + c_im * b_c10_tmp_tmp.re) *
                 0.766044443118978) -
            (h_re + d_im * 0.0)) +
           (e_re * b_c10_tmp_tmp.im + e_im * b_c10_tmp_tmp.re) *
               0.766044443118978) -
          (i_re * b_c10_tmp_tmp.im + hb_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.re) *
              0.766044443118978) +
         (f_re + ib_scp0_idx_0_tmp_tmp * 0.0)) +
        (g_re * b_c10_tmp_tmp.im + ob_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.re) *
            0.766044443118978;
    if (cp02_idx_0 == 0.0) {
      if (ccr0 == 0.0) {
        dc1.re = cc4_tmp / scr0;
        dc1.im = 0.0;
      } else if (cc4_tmp == 0.0) {
        dc1.re = 0.0;
        dc1.im = ccr0 / scr0;
      } else {
        dc1.re = cc4_tmp / scr0;
        dc1.im = ccr0 / scr0;
      }
    } else if (scr0 == 0.0) {
      if (cc4_tmp == 0.0) {
        dc1.re = ccr0 / cp02_idx_0;
        dc1.im = 0.0;
      } else if (ccr0 == 0.0) {
        dc1.re = 0.0;
        dc1.im = -(cc4_tmp / cp02_idx_0);
      } else {
        dc1.re = ccr0 / cp02_idx_0;
        dc1.im = -(cc4_tmp / cp02_idx_0);
      }
    } else {
      crw = fabs(scr0);
      cphi = fabs(cp02_idx_0);
      if (crw > cphi) {
        cp01_idx_0 = cp02_idx_0 / scr0;
        cphi = scr0 + cp01_idx_0 * cp02_idx_0;
        dc1.re = (cc4_tmp + cp01_idx_0 * ccr0) / cphi;
        dc1.im = (ccr0 - cp01_idx_0 * cc4_tmp) / cphi;
      } else if (cphi == crw) {
        if (scr0 > 0.0) {
          cp01_idx_0 = 0.5;
        } else {
          cp01_idx_0 = -0.5;
        }
        if (cp02_idx_0 > 0.0) {
          cphi = 0.5;
        } else {
          cphi = -0.5;
        }
        dc1.re = (cc4_tmp * cp01_idx_0 + ccr0 * cphi) / crw;
        dc1.im = (ccr0 * cp01_idx_0 - cc4_tmp * cphi) / crw;
      } else {
        cp01_idx_0 = scr0 / cp02_idx_0;
        cphi = cp02_idx_0 + cp01_idx_0 * scr0;
        dc1.re = (cp01_idx_0 * cc4_tmp + ccr0) / cphi;
        dc1.im = (cp01_idx_0 * ccr0 - cc4_tmp) / cphi;
      }
    }
    b_log(&dc1);
    o_re = dc.re * 0.0 - dc.im;
    p_re = dc1.re * 0.0 - dc1.im;
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
    f_scp0_idx_0_tmp_tmp =
        g_c30_tmp.re * c_c30_tmp_tmp.re - g_c30_tmp.im * c_c30_tmp_tmp.im;
    y_scp0_idx_0_tmp_tmp =
        g_c30_tmp.re * c_c30_tmp_tmp.im + g_c30_tmp.im * c_c30_tmp_tmp.re;
    ab_scp0_idx_0_tmp_tmp =
        i_c30_tmp.re * e_c30_tmp_tmp.re - i_c30_tmp.im * e_c30_tmp_tmp.im;
    s_scp0_idx_0_tmp_tmp =
        i_c30_tmp.re * e_c30_tmp_tmp.im + i_c30_tmp.im * e_c30_tmp_tmp.re;
    v2_idx_2 = d_c30_tmp.re * d_c10_tmp.re - d_c30_tmp.im * d_c10_tmp.im;
    v3_idx_0 = d_c30_tmp.re * d_c10_tmp.im + d_c30_tmp.im * d_c10_tmp.re;
    e_scp0_idx_0_tmp_tmp =
        c_c30_tmp.re * b_c10_tmp.re - c_c30_tmp.im * b_c10_tmp.im;
    g_scp0_idx_0_tmp_tmp =
        c_c30_tmp.re * b_c10_tmp.im + c_c30_tmp.im * b_c10_tmp.re;
    h_scp0_idx_0_tmp_tmp = e_scp0_idx_0_tmp_tmp * c_c30_tmp_tmp.re -
                           g_scp0_idx_0_tmp_tmp * c_c30_tmp_tmp.im;
    g_scp0_idx_0_tmp_tmp = e_scp0_idx_0_tmp_tmp * c_c30_tmp_tmp.im +
                           g_scp0_idx_0_tmp_tmp * c_c30_tmp_tmp.re;
    k_re = 3.35904390375E+8 * b_c30_tmp.re;
    f_im = 3.35904390375E+8 * b_c30_tmp.im;
    l_re = k_re * d_c10_tmp.re - f_im * d_c10_tmp.im;
    f_im = k_re * d_c10_tmp.im + f_im * d_c10_tmp.re;
    e_scp0_idx_0_tmp_tmp =
        c30_tmp.re * e_c30_tmp.re - c30_tmp.im * e_c30_tmp.im;
    cp01_idx_0 = c30_tmp.re * e_c30_tmp.im + c30_tmp.im * e_c30_tmp.re;
    cp02_idx_0 = c_c30_tmp.re * f_c30_tmp.re - c_c30_tmp.im * f_c30_tmp.im;
    scr0 = c_c30_tmp.re * f_c30_tmp.im + c_c30_tmp.im * f_c30_tmp.re;
    ccr0 = cp02_idx_0 * e_c30_tmp_tmp.re - scr0 * e_c30_tmp_tmp.im;
    scr0 = cp02_idx_0 * e_c30_tmp_tmp.im + scr0 * e_c30_tmp_tmp.re;
    cp02_idx_0 = c_c30_tmp.re * e_c30_tmp.re - c_c30_tmp.im * e_c30_tmp.im;
    cc4_tmp = c_c30_tmp.re * e_c30_tmp.im + c_c30_tmp.im * e_c30_tmp.re;
    sc4 = g_c30_tmp.re * c30_tmp_tmp.re - g_c30_tmp.im * c30_tmp_tmp.im;
    cc4 = g_c30_tmp.re * c30_tmp_tmp.im + g_c30_tmp.im * c30_tmp_tmp.re;
    crw = sc4 * c_c30_tmp_tmp.re - cc4 * c_c30_tmp_tmp.im;
    cc4 = sc4 * c_c30_tmp_tmp.im + cc4 * c_c30_tmp_tmp.re;
    k_re = 2.2393626025E+8 * d_c10_tmp.re;
    p_scp0_idx_0_tmp_tmp = 2.2393626025E+8 * d_c10_tmp.im;
    b_sc5_tmp_tmp =
        k_re * b_c10_tmp_tmp.re - p_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.im;
    p_scp0_idx_0_tmp_tmp =
        k_re * b_c10_tmp_tmp.im + p_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.re;
    sc4 = h_c30_tmp.re * c30_tmp_tmp.re - h_c30_tmp.im * c30_tmp_tmp.im;
    w1_idx_2 = h_c30_tmp.re * c30_tmp_tmp.im + h_c30_tmp.im * c30_tmp_tmp.re;
    w1_idx_1 = i_c30_tmp.re * c30_tmp_tmp.re - i_c30_tmp.im * c30_tmp_tmp.im;
    w1_idx_3 = i_c30_tmp.re * c30_tmp_tmp.im + i_c30_tmp.im * c30_tmp_tmp.re;
    w2_idx_0 = w1_idx_1 * e_c30_tmp_tmp.re - w1_idx_3 * e_c30_tmp_tmp.im;
    w1_idx_3 = w1_idx_1 * e_c30_tmp_tmp.im + w1_idx_3 * e_c30_tmp_tmp.re;
    k_re = 1.11968130125E+8 * e_c30_tmp.re;
    kb_scp0_idx_0_tmp_tmp = 1.11968130125E+8 * e_c30_tmp.im;
    re = k_re * b_c10_tmp_tmp.re - kb_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.im;
    kb_scp0_idx_0_tmp_tmp =
        k_re * b_c10_tmp_tmp.im + kb_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.re;
    w1_idx_1 = j_c30_tmp.re * c30_tmp_tmp.re - j_c30_tmp.im * c30_tmp_tmp.im;
    w2_idx_2 = j_c30_tmp.re * c30_tmp_tmp.im + j_c30_tmp.im * c30_tmp_tmp.re;
    k_re = 8.957450409999994E+8 * c10_tmp.re;
    lb_scp0_idx_0_tmp_tmp = 8.957450409999994E+8 * c10_tmp.im;
    b_re = k_re * d_c10_tmp.re - lb_scp0_idx_0_tmp_tmp * d_c10_tmp.im;
    lb_scp0_idx_0_tmp_tmp =
        k_re * d_c10_tmp.im + lb_scp0_idx_0_tmp_tmp * d_c10_tmp.re;
    k_re = b_re * b_c10_tmp_tmp.re - lb_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.im;
    lb_scp0_idx_0_tmp_tmp =
        b_re * b_c10_tmp_tmp.im + lb_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.re;
    b_re = 1.3436175615E+9 * c10_tmp.re;
    mb_scp0_idx_0_tmp_tmp = 1.3436175615E+9 * c10_tmp.im;
    c_re = b_re * d_c10_tmp.re - mb_scp0_idx_0_tmp_tmp * d_c10_tmp.im;
    mb_scp0_idx_0_tmp_tmp =
        b_re * d_c10_tmp.im + mb_scp0_idx_0_tmp_tmp * d_c10_tmp.re;
    b_re = c_re * b_c10_tmp_tmp.re - mb_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.im;
    mb_scp0_idx_0_tmp_tmp =
        c_re * b_c10_tmp_tmp.im + mb_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.re;
    c_re = 2.2393626025E+8 * dc.re;
    scp0_idx_0_tmp_tmp_tmp = 2.2393626025E+8 * dc.im;
    d_re = c_re * dc1.re - scp0_idx_0_tmp_tmp_tmp * dc1.im;
    scp0_idx_0_tmp_tmp_tmp = c_re * dc1.im + scp0_idx_0_tmp_tmp_tmp * dc1.re;
    c_re = d_re * c30_tmp_tmp.re - scp0_idx_0_tmp_tmp_tmp * c30_tmp_tmp.im;
    scp0_idx_0_tmp_tmp_tmp =
        d_re * c30_tmp_tmp.im + scp0_idx_0_tmp_tmp_tmp * c30_tmp_tmp.re;
    d_re = 5.59840650625E+7 * dc2.re;
    im = 5.59840650625E+7 * dc2.im;
    e_re = d_re * dc3.re - im * dc3.im;
    im = d_re * dc3.im + im * dc3.re;
    d_re = e_re * c30_tmp_tmp.re - im * c30_tmp_tmp.im;
    im = e_re * c30_tmp_tmp.im + im * c30_tmp_tmp.re;
    e_re = d_re * c_c30_tmp_tmp.re - im * c_c30_tmp_tmp.im;
    im = d_re * c_c30_tmp_tmp.im + im * c_c30_tmp_tmp.re;
    d_re = 2.2393626025E+8 * b_c30_tmp.re;
    b_im = 2.2393626025E+8 * b_c30_tmp.im;
    h_re = d_re * d_c10_tmp.re - b_im * d_c10_tmp.im;
    b_im = d_re * d_c10_tmp.im + b_im * d_c10_tmp.re;
    d_re = h_re * b_c10_tmp_tmp.re - b_im * b_c10_tmp_tmp.im;
    b_im = h_re * b_c10_tmp_tmp.im + b_im * b_c10_tmp_tmp.re;
    cphi = d_c30_tmp.re * e_c30_tmp.re - d_c30_tmp.im * e_c30_tmp.im;
    w2_idx_1 = d_c30_tmp.re * e_c30_tmp.im + d_c30_tmp.im * e_c30_tmp.re;
    w2_idx_3 = cphi * b_c10_tmp_tmp.re - w2_idx_1 * b_c10_tmp_tmp.im;
    w2_idx_1 = cphi * b_c10_tmp_tmp.im + w2_idx_1 * b_c10_tmp_tmp.re;
    h_re = 3.35904390375E+8 * dc4.re;
    c_im = 3.35904390375E+8 * dc4.im;
    f_re = h_re * dc5.re - c_im * dc5.im;
    c_im = h_re * dc5.im + c_im * dc5.re;
    h_re = f_re * c30_tmp_tmp.re - c_im * c30_tmp_tmp.im;
    c_im = f_re * c30_tmp_tmp.im + c_im * c30_tmp_tmp.re;
    f_re = 1.11968130125E+8 * dc6.re;
    d_im = 1.11968130125E+8 * dc6.im;
    i_re = f_re * dc7.re - d_im * dc7.im;
    d_im = f_re * dc7.im + d_im * dc7.re;
    f_re = i_re * c30_tmp_tmp.re - d_im * c30_tmp_tmp.im;
    d_im = i_re * c30_tmp_tmp.im + d_im * c30_tmp_tmp.re;
    i_re = 5.59840650625E+7 * dc8.re;
    e_im = 5.59840650625E+7 * dc8.im;
    j_re = i_re * dc9.re - e_im * dc9.im;
    e_im = i_re * dc9.im + e_im * dc9.re;
    i_re = j_re * c30_tmp_tmp.re - e_im * c30_tmp_tmp.im;
    e_im = j_re * c30_tmp_tmp.im + e_im * c30_tmp_tmp.re;
    j_re = i_re * e_c30_tmp_tmp.re - e_im * e_c30_tmp_tmp.im;
    e_im = i_re * e_c30_tmp_tmp.im + e_im * e_c30_tmp_tmp.re;
    cphi = k_c30_tmp.re * e_c30_tmp.re - k_c30_tmp.im * e_c30_tmp.im;
    v2_idx_0 = k_c30_tmp.re * e_c30_tmp.im + k_c30_tmp.im * e_c30_tmp.re;
    v2_idx_1 = cphi * b_c10_tmp_tmp.re - v2_idx_0 * b_c10_tmp_tmp.im;
    v2_idx_0 = cphi * b_c10_tmp_tmp.im + v2_idx_0 * b_c10_tmp_tmp.re;
    i_re = 5.59840650625E+7 * dc10.re;
    hb_scp0_idx_0_tmp_tmp = 5.59840650625E+7 * dc10.im;
    g_re = i_re * dc11.re - hb_scp0_idx_0_tmp_tmp * dc11.im;
    hb_scp0_idx_0_tmp_tmp = i_re * dc11.im + hb_scp0_idx_0_tmp_tmp * dc11.re;
    i_re = g_re * c30_tmp_tmp.re - hb_scp0_idx_0_tmp_tmp * c30_tmp_tmp.im;
    hb_scp0_idx_0_tmp_tmp =
        g_re * c30_tmp_tmp.im + hb_scp0_idx_0_tmp_tmp * c30_tmp_tmp.re;
    g_re = 3.5829801639999986E+9 * c10_tmp.re;
    ib_scp0_idx_0_tmp_tmp = 3.5829801639999986E+9 * c10_tmp.im;
    jb_scp0_idx_0_tmp_tmp =
        g_re * d_c10_tmp.re - ib_scp0_idx_0_tmp_tmp * d_c10_tmp.im;
    ib_scp0_idx_0_tmp_tmp =
        g_re * d_c10_tmp.im + ib_scp0_idx_0_tmp_tmp * d_c10_tmp.re;
    g_re = jb_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.re -
           ib_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.im;
    ib_scp0_idx_0_tmp_tmp = jb_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.im +
                            ib_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.re;
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
                                   (f_scp0_idx_0_tmp_tmp * 0.0 -
                                    y_scp0_idx_0_tmp_tmp * 4.0)) -
                                  (h_c30_tmp.re * b_c30_tmp_tmp.re -
                                   h_c30_tmp.im * b_c30_tmp_tmp.im)) -
                                 (ab_scp0_idx_0_tmp_tmp * 0.0 -
                                  s_scp0_idx_0_tmp_tmp * 4.0)) +
                                (j_c30_tmp.re * d_c30_tmp_tmp.re -
                                 j_c30_tmp.im * d_c30_tmp_tmp.im)) +
                               (v2_idx_2 * b_c30_tmp_tmp.re -
                                v3_idx_0 * b_c30_tmp_tmp.im)) -
                              (h_scp0_idx_0_tmp_tmp * 0.0 -
                               g_scp0_idx_0_tmp_tmp * 4.0)) -
                             (l_re * b_c30_tmp_tmp.re -
                              f_im * b_c30_tmp_tmp.im)) +
                            (e_scp0_idx_0_tmp_tmp * d_c30_tmp_tmp.re -
                             cp01_idx_0 * d_c30_tmp_tmp.im)) +
                           (ccr0 * 0.0 - scr0 * 4.0)) +
                          (cp02_idx_0 * d_c30_tmp_tmp.re -
                           cc4_tmp * d_c30_tmp_tmp.im)) -
                         (crw * 0.0 - cc4 * 4.0)) -
                        (b_sc5_tmp_tmp * b_c30_tmp_tmp.re -
                         p_scp0_idx_0_tmp_tmp * b_c30_tmp_tmp.im)) -
                       (sc4 * b_c30_tmp_tmp.re - w1_idx_2 * b_c30_tmp_tmp.im)) +
                      (w2_idx_0 * 0.0 - w1_idx_3 * 4.0)) -
                     (re * d_c30_tmp_tmp.re -
                      kb_scp0_idx_0_tmp_tmp * d_c30_tmp_tmp.im)) +
                    (w1_idx_1 * d_c30_tmp_tmp.re -
                     w2_idx_2 * d_c30_tmp_tmp.im)) +
                   (k_re * b_c30_tmp_tmp.re -
                    lb_scp0_idx_0_tmp_tmp * b_c30_tmp_tmp.im)) +
                  (b_re * b_c30_tmp_tmp.re -
                   mb_scp0_idx_0_tmp_tmp * b_c30_tmp_tmp.im)) +
                 (c_re * b_c30_tmp_tmp.re -
                  scp0_idx_0_tmp_tmp_tmp * b_c30_tmp_tmp.im)) +
                (e_re * 0.0 - im * 4.0)) -
               (d_re * b_c30_tmp_tmp.re - b_im * b_c30_tmp_tmp.im)) -
              (w2_idx_3 * d_c30_tmp_tmp.re - w2_idx_1 * d_c30_tmp_tmp.im)) -
             (h_re * b_c30_tmp_tmp.re - c_im * b_c30_tmp_tmp.im)) +
            (f_re * d_c30_tmp_tmp.re - d_im * d_c30_tmp_tmp.im)) -
           (j_re * 0.0 - e_im * 4.0)) -
          (v2_idx_1 * d_c30_tmp_tmp.re - v2_idx_0 * d_c30_tmp_tmp.im)) +
         (i_re * d_c30_tmp_tmp.re - hb_scp0_idx_0_tmp_tmp * d_c30_tmp_tmp.im)) -
        (g_re * b_c30_tmp_tmp.re - ib_scp0_idx_0_tmp_tmp * b_c30_tmp_tmp.im);
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
                                   (f_scp0_idx_0_tmp_tmp * 4.0 +
                                    y_scp0_idx_0_tmp_tmp * 0.0)) -
                                  (h_c30_tmp.re * b_c30_tmp_tmp.im +
                                   h_c30_tmp.im * b_c30_tmp_tmp.re)) -
                                 (ab_scp0_idx_0_tmp_tmp * 4.0 +
                                  s_scp0_idx_0_tmp_tmp * 0.0)) +
                                (j_c30_tmp.re * d_c30_tmp_tmp.im +
                                 j_c30_tmp.im * d_c30_tmp_tmp.re)) +
                               (v2_idx_2 * b_c30_tmp_tmp.im +
                                v3_idx_0 * b_c30_tmp_tmp.re)) -
                              (h_scp0_idx_0_tmp_tmp * 4.0 +
                               g_scp0_idx_0_tmp_tmp * 0.0)) -
                             (l_re * b_c30_tmp_tmp.im +
                              f_im * b_c30_tmp_tmp.re)) +
                            (e_scp0_idx_0_tmp_tmp * d_c30_tmp_tmp.im +
                             cp01_idx_0 * d_c30_tmp_tmp.re)) +
                           (ccr0 * 4.0 + scr0 * 0.0)) +
                          (cp02_idx_0 * d_c30_tmp_tmp.im +
                           cc4_tmp * d_c30_tmp_tmp.re)) -
                         (crw * 4.0 + cc4 * 0.0)) -
                        (b_sc5_tmp_tmp * b_c30_tmp_tmp.im +
                         p_scp0_idx_0_tmp_tmp * b_c30_tmp_tmp.re)) -
                       (sc4 * b_c30_tmp_tmp.im + w1_idx_2 * b_c30_tmp_tmp.re)) +
                      (w2_idx_0 * 4.0 + w1_idx_3 * 0.0)) -
                     (re * d_c30_tmp_tmp.im +
                      kb_scp0_idx_0_tmp_tmp * d_c30_tmp_tmp.re)) +
                    (w1_idx_1 * d_c30_tmp_tmp.im +
                     w2_idx_2 * d_c30_tmp_tmp.re)) +
                   (k_re * b_c30_tmp_tmp.im +
                    lb_scp0_idx_0_tmp_tmp * b_c30_tmp_tmp.re)) +
                  (b_re * b_c30_tmp_tmp.im +
                   mb_scp0_idx_0_tmp_tmp * b_c30_tmp_tmp.re)) +
                 (c_re * b_c30_tmp_tmp.im +
                  scp0_idx_0_tmp_tmp_tmp * b_c30_tmp_tmp.re)) +
                (e_re * 4.0 + im * 0.0)) -
               (d_re * b_c30_tmp_tmp.im + b_im * b_c30_tmp_tmp.re)) -
              (w2_idx_3 * d_c30_tmp_tmp.im + w2_idx_1 * d_c30_tmp_tmp.re)) -
             (h_re * b_c30_tmp_tmp.im + c_im * b_c30_tmp_tmp.re)) +
            (f_re * d_c30_tmp_tmp.im + d_im * d_c30_tmp_tmp.re)) -
           (j_re * 4.0 + e_im * 0.0)) -
          (v2_idx_1 * d_c30_tmp_tmp.im + v2_idx_0 * d_c30_tmp_tmp.re)) +
         (i_re * d_c30_tmp_tmp.im + hb_scp0_idx_0_tmp_tmp * d_c30_tmp_tmp.re)) -
        (g_re * b_c30_tmp_tmp.im + ib_scp0_idx_0_tmp_tmp * b_c30_tmp_tmp.re);
    dc = power(b_c30_tmp);
    k_re = 29928.999999999989 * c_c10_tmp.re - n_scp0_idx_0_tmp_tmp;
    f_im = 29928.999999999989 * c_c10_tmp.im + o_scp0_idx_0_tmp_tmp;
    l_re = k_re * b_c10_tmp.re - f_im * b_c10_tmp.im;
    f_im = k_re * b_c10_tmp.im + f_im * b_c10_tmp.re;
    k_re = l_re * c_c10_tmp_tmp.re - f_im * c_c10_tmp_tmp.im;
    f_im = l_re * c_c10_tmp_tmp.im + f_im * c_c10_tmp_tmp.re;
    l_re = 59858.0 * c_c10_tmp.re - n_scp0_idx_0_tmp_tmp;
    p_scp0_idx_0_tmp_tmp = 59858.0 * c_c10_tmp.im + o_scp0_idx_0_tmp_tmp;
    b_sc5_tmp_tmp = l_re * b_c10_tmp.re - p_scp0_idx_0_tmp_tmp * b_c10_tmp.im;
    p_scp0_idx_0_tmp_tmp =
        l_re * b_c10_tmp.im + p_scp0_idx_0_tmp_tmp * b_c10_tmp.re;
    l_re = b_sc5_tmp_tmp * c_c10_tmp_tmp.re -
           p_scp0_idx_0_tmp_tmp * c_c10_tmp_tmp.im;
    p_scp0_idx_0_tmp_tmp = b_sc5_tmp_tmp * c_c10_tmp_tmp.im +
                           p_scp0_idx_0_tmp_tmp * c_c10_tmp_tmp.re;
    f_scp0_idx_0_tmp_tmp =
        l_c30_tmp.re * b_c10_tmp_tmp.re - l_c30_tmp.im * b_c10_tmp_tmp.im;
    y_scp0_idx_0_tmp_tmp =
        l_c30_tmp.re * b_c10_tmp_tmp.im + l_c30_tmp.im * b_c10_tmp_tmp.re;
    b_sc5_tmp_tmp = 7482.25 * dc12.re;
    kb_scp0_idx_0_tmp_tmp = 7482.25 * dc12.im;
    ab_scp0_idx_0_tmp_tmp =
        m_c30_tmp.re * c_c30_tmp_tmp.re - m_c30_tmp.im * c_c30_tmp_tmp.im;
    s_scp0_idx_0_tmp_tmp =
        m_c30_tmp.re * c_c30_tmp_tmp.im + m_c30_tmp.im * c_c30_tmp_tmp.re;
    w1_idx_2 = l_scp0_idx_0_tmp_tmp * b_c10_tmp.re -
               m_scp0_idx_0_tmp_tmp * b_c10_tmp.im;
    w2_idx_0 = l_scp0_idx_0_tmp_tmp * b_c10_tmp.im +
               m_scp0_idx_0_tmp_tmp * b_c10_tmp.re;
    w1_idx_1 = w1_idx_2 * c_c30_tmp_tmp.re - w2_idx_0 * c_c30_tmp_tmp.im;
    w2_idx_0 = w1_idx_2 * c_c30_tmp_tmp.im + w2_idx_0 * c_c30_tmp_tmp.re;
    v2_idx_2 = l_c30_tmp.re * d_c10_tmp.re - l_c30_tmp.im * d_c10_tmp.im;
    v3_idx_0 = l_c30_tmp.re * d_c10_tmp.im + l_c30_tmp.im * d_c10_tmp.re;
    e_scp0_idx_0_tmp_tmp =
        v2_idx_2 * b_c30_tmp_tmp.re - v3_idx_0 * b_c30_tmp_tmp.im;
    v3_idx_0 = v2_idx_2 * b_c30_tmp_tmp.im + v3_idx_0 * b_c30_tmp_tmp.re;
    re = 7482.25 * dc13.re;
    lb_scp0_idx_0_tmp_tmp = 7482.25 * dc13.im;
    b_re = re * dc14.re - lb_scp0_idx_0_tmp_tmp * dc14.im;
    lb_scp0_idx_0_tmp_tmp = re * dc14.im + lb_scp0_idx_0_tmp_tmp * dc14.re;
    v2_idx_2 =
        m_c30_tmp.re * b_c10_tmp_tmp.re - m_c30_tmp.im * b_c10_tmp_tmp.im;
    g_scp0_idx_0_tmp_tmp =
        m_c30_tmp.re * b_c10_tmp_tmp.im + m_c30_tmp.im * b_c10_tmp_tmp.re;
    h_scp0_idx_0_tmp_tmp =
        v2_idx_2 * c_c30_tmp_tmp.re - g_scp0_idx_0_tmp_tmp * c_c30_tmp_tmp.im;
    g_scp0_idx_0_tmp_tmp =
        v2_idx_2 * c_c30_tmp_tmp.im + g_scp0_idx_0_tmp_tmp * c_c30_tmp_tmp.re;
    re = 7482.25 * dc15.re;
    mb_scp0_idx_0_tmp_tmp = 7482.25 * dc15.im;
    c_re = re * b_c10_tmp_tmp.re - mb_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.im;
    mb_scp0_idx_0_tmp_tmp =
        re * b_c10_tmp_tmp.im + mb_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.re;
    re = 7482.25 * dc16.re;
    scp0_idx_0_tmp_tmp_tmp = 7482.25 * dc16.im;
    d_re = re * dc17.re - scp0_idx_0_tmp_tmp_tmp * dc17.im;
    scp0_idx_0_tmp_tmp_tmp = re * dc17.im + scp0_idx_0_tmp_tmp_tmp * dc17.re;
    re = d_re * b_c10_tmp_tmp.re - scp0_idx_0_tmp_tmp_tmp * b_c10_tmp_tmp.im;
    scp0_idx_0_tmp_tmp_tmp =
        d_re * b_c10_tmp_tmp.im + scp0_idx_0_tmp_tmp_tmp * b_c10_tmp_tmp.re;
    d_re = re * c_c30_tmp_tmp.re - scp0_idx_0_tmp_tmp_tmp * c_c30_tmp_tmp.im;
    scp0_idx_0_tmp_tmp_tmp =
        re * c_c30_tmp_tmp.im + scp0_idx_0_tmp_tmp_tmp * c_c30_tmp_tmp.re;
    re = 7482.25 * dc18.re;
    im = 7482.25 * dc18.im;
    e_re = re * dc19.re - im * dc19.im;
    im = re * dc19.im + im * dc19.re;
    re = e_re * b_c10_tmp_tmp.re - im * b_c10_tmp_tmp.im;
    im = e_re * b_c10_tmp_tmp.im + im * b_c10_tmp_tmp.re;
    e_re = re * b_c30_tmp_tmp.re - im * b_c30_tmp_tmp.im;
    im = re * b_c30_tmp_tmp.im + im * b_c30_tmp_tmp.re;
    re = 7482.25 * dc20.re;
    b_im = 7482.25 * dc20.im;
    h_re = re * dc21.re - b_im * dc21.im;
    b_im = re * dc21.im + b_im * dc21.re;
    re = h_re * b_c10_tmp_tmp.re - b_im * b_c10_tmp_tmp.im;
    b_im = h_re * b_c10_tmp_tmp.im + b_im * b_c10_tmp_tmp.re;
    cc4_tmp =
        ((c10_tmp_tmp.re * dc.re - c10_tmp_tmp.im * dc.im) -
         (k_re * c_c30_tmp_tmp.re - f_im * c_c30_tmp_tmp.im)) +
        (l_re * c_c30_tmp_tmp.re - p_scp0_idx_0_tmp_tmp * c_c30_tmp_tmp.im);
    ccr0 = ((c10_tmp_tmp.re * dc.im + c10_tmp_tmp.im * dc.re) -
            (k_re * c_c30_tmp_tmp.im + f_im * c_c30_tmp_tmp.re)) +
           (l_re * c_c30_tmp_tmp.im + p_scp0_idx_0_tmp_tmp * c_c30_tmp_tmp.re);
    scr0 =
        (((((((((((((((l_c30_tmp.re * 0.0 - l_c30_tmp.im * 2.0) -
                      l_scp0_idx_0_tmp_tmp) -
                     3741.1250000000009) +
                    7482.25) -
                   (f_scp0_idx_0_tmp_tmp * 0.0 - y_scp0_idx_0_tmp_tmp * 2.0)) +
                  (b_sc5_tmp_tmp * b_c10_tmp_tmp.re -
                   kb_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.im)) +
                 (ab_scp0_idx_0_tmp_tmp * 0.0 - s_scp0_idx_0_tmp_tmp * 2.0)) -
                (j_scp0_idx_0_tmp_tmp * b_c30_tmp_tmp.re -
                 k_scp0_idx_0_tmp_tmp * b_c30_tmp_tmp.im)) +
               (w1_idx_1 * 0.0 - w2_idx_0 * 2.0)) +
              (e_scp0_idx_0_tmp_tmp * 0.0 - v3_idx_0 * 2.0)) +
             (b_re * b_c30_tmp_tmp.re -
              lb_scp0_idx_0_tmp_tmp * b_c30_tmp_tmp.im)) +
            (h_scp0_idx_0_tmp_tmp * 0.0 - g_scp0_idx_0_tmp_tmp * 2.0)) +
           (c_re * b_c30_tmp_tmp.re -
            mb_scp0_idx_0_tmp_tmp * b_c30_tmp_tmp.im)) +
          (d_re * 0.0 - scp0_idx_0_tmp_tmp_tmp * 2.0)) -
         (e_re * 0.0 - im * 2.0)) -
        (re * b_c30_tmp_tmp.re - b_im * b_c30_tmp_tmp.im);
    cp02_idx_0 =
        ((((((((((((((l_c30_tmp.re * 2.0 + l_c30_tmp.im * 0.0) -
                     m_scp0_idx_0_tmp_tmp) -
                    6479.818577466116) -
                   (f_scp0_idx_0_tmp_tmp * 2.0 + y_scp0_idx_0_tmp_tmp * 0.0)) +
                  (b_sc5_tmp_tmp * b_c10_tmp_tmp.im +
                   kb_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.re)) +
                 (ab_scp0_idx_0_tmp_tmp * 2.0 + s_scp0_idx_0_tmp_tmp * 0.0)) -
                (j_scp0_idx_0_tmp_tmp * b_c30_tmp_tmp.im +
                 k_scp0_idx_0_tmp_tmp * b_c30_tmp_tmp.re)) +
               (w1_idx_1 * 2.0 + w2_idx_0 * 0.0)) +
              (e_scp0_idx_0_tmp_tmp * 2.0 + v3_idx_0 * 0.0)) +
             (b_re * b_c30_tmp_tmp.im +
              lb_scp0_idx_0_tmp_tmp * b_c30_tmp_tmp.re)) +
            (h_scp0_idx_0_tmp_tmp * 2.0 + g_scp0_idx_0_tmp_tmp * 0.0)) +
           (c_re * b_c30_tmp_tmp.im +
            mb_scp0_idx_0_tmp_tmp * b_c30_tmp_tmp.re)) +
          (d_re * 2.0 + scp0_idx_0_tmp_tmp_tmp * 0.0)) -
         (e_re * 2.0 + im * 0.0)) -
        (re * b_c30_tmp_tmp.im + b_im * b_c30_tmp_tmp.re);
    if (cp02_idx_0 == 0.0) {
      if (ccr0 == 0.0) {
        dc.re = cc4_tmp / scr0;
        dc.im = 0.0;
      } else if (cc4_tmp == 0.0) {
        dc.re = 0.0;
        dc.im = ccr0 / scr0;
      } else {
        dc.re = cc4_tmp / scr0;
        dc.im = ccr0 / scr0;
      }
    } else if (scr0 == 0.0) {
      if (cc4_tmp == 0.0) {
        dc.re = ccr0 / cp02_idx_0;
        dc.im = 0.0;
      } else if (ccr0 == 0.0) {
        dc.re = 0.0;
        dc.im = -(cc4_tmp / cp02_idx_0);
      } else {
        dc.re = ccr0 / cp02_idx_0;
        dc.im = -(cc4_tmp / cp02_idx_0);
      }
    } else {
      crw = fabs(scr0);
      cphi = fabs(cp02_idx_0);
      if (crw > cphi) {
        cp01_idx_0 = cp02_idx_0 / scr0;
        cphi = scr0 + cp01_idx_0 * cp02_idx_0;
        dc.re = (cc4_tmp + cp01_idx_0 * ccr0) / cphi;
        dc.im = (ccr0 - cp01_idx_0 * cc4_tmp) / cphi;
      } else if (cphi == crw) {
        if (scr0 > 0.0) {
          cp01_idx_0 = 0.5;
        } else {
          cp01_idx_0 = -0.5;
        }
        if (cp02_idx_0 > 0.0) {
          cphi = 0.5;
        } else {
          cphi = -0.5;
        }
        dc.re = (cc4_tmp * cp01_idx_0 + ccr0 * cphi) / crw;
        dc.im = (ccr0 * cp01_idx_0 - cc4_tmp * cphi) / crw;
      } else {
        cp01_idx_0 = scr0 / cp02_idx_0;
        cphi = cp02_idx_0 + cp01_idx_0 * scr0;
        dc.re = (cp01_idx_0 * cc4_tmp + ccr0) / cphi;
        dc.im = (cp01_idx_0 * ccr0 - cc4_tmp) / cphi;
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
    k_re = 2.2393626025E+8 * dc3.re;
    f_im = 2.2393626025E+8 * dc3.im;
    l_re = 1.11968130125E+8 * dc4.re;
    p_scp0_idx_0_tmp_tmp = 1.11968130125E+8 * dc4.im;
    b_sc5_tmp_tmp = 1.11968130125E+8 * dc5.re;
    kb_scp0_idx_0_tmp_tmp = 1.11968130125E+8 * dc5.im;
    re = 5.59840650625E+7 * dc6.re;
    lb_scp0_idx_0_tmp_tmp = 5.59840650625E+7 * dc6.im;
    b_re = 5.59840650625E+7 * dc7.re;
    mb_scp0_idx_0_tmp_tmp = 5.59840650625E+7 * dc7.im;
    c_re = b_re * c_c30_tmp_tmp.re - mb_scp0_idx_0_tmp_tmp * c_c30_tmp_tmp.im;
    mb_scp0_idx_0_tmp_tmp =
        b_re * c_c30_tmp_tmp.im + mb_scp0_idx_0_tmp_tmp * c_c30_tmp_tmp.re;
    b_re = 3.35904390375E+8 * dc8.re;
    scp0_idx_0_tmp_tmp_tmp = 3.35904390375E+8 * dc8.im;
    d_re = 5.59840650625E+7 * dc9.re;
    im = 5.59840650625E+7 * dc9.im;
    e_re = d_re * e_c30_tmp_tmp.re - im * e_c30_tmp_tmp.im;
    im = d_re * e_c30_tmp_tmp.im + im * e_c30_tmp_tmp.re;
    d_re = 5.59840650625E+7 * dc10.re;
    b_im = 5.59840650625E+7 * dc10.im;
    h_re = 2.2393626025E+8 * dc11.re;
    c_im = 2.2393626025E+8 * dc11.im;
    f_re = h_re * dc12.re - c_im * dc12.im;
    c_im = h_re * dc12.im + c_im * dc12.re;
    h_re = 5.59840650625E+7 * dc13.re;
    d_im = 5.59840650625E+7 * dc13.im;
    i_re = h_re * dc14.re - d_im * dc14.im;
    d_im = h_re * dc14.im + d_im * dc14.re;
    h_re = i_re * c_c30_tmp_tmp.re - d_im * c_c30_tmp_tmp.im;
    d_im = i_re * c_c30_tmp_tmp.im + d_im * c_c30_tmp_tmp.re;
    i_re = 3.35904390375E+8 * dc15.re;
    e_im = 3.35904390375E+8 * dc15.im;
    j_re = i_re * dc16.re - e_im * dc16.im;
    e_im = i_re * dc16.im + e_im * dc16.re;
    i_re = 1.11968130125E+8 * dc17.re;
    hb_scp0_idx_0_tmp_tmp = 1.11968130125E+8 * dc17.im;
    g_re = i_re * dc18.re - hb_scp0_idx_0_tmp_tmp * dc18.im;
    hb_scp0_idx_0_tmp_tmp = i_re * dc18.im + hb_scp0_idx_0_tmp_tmp * dc18.re;
    i_re = 5.59840650625E+7 * dc19.re;
    ib_scp0_idx_0_tmp_tmp = 5.59840650625E+7 * dc19.im;
    jb_scp0_idx_0_tmp_tmp = i_re * dc20.re - ib_scp0_idx_0_tmp_tmp * dc20.im;
    ib_scp0_idx_0_tmp_tmp = i_re * dc20.im + ib_scp0_idx_0_tmp_tmp * dc20.re;
    i_re = jb_scp0_idx_0_tmp_tmp * e_c30_tmp_tmp.re -
           ib_scp0_idx_0_tmp_tmp * e_c30_tmp_tmp.im;
    ib_scp0_idx_0_tmp_tmp = jb_scp0_idx_0_tmp_tmp * e_c30_tmp_tmp.im +
                            ib_scp0_idx_0_tmp_tmp * e_c30_tmp_tmp.re;
    jb_scp0_idx_0_tmp_tmp = 5.59840650625E+7 * dc21.re;
    ob_scp0_idx_0_tmp_tmp = 5.59840650625E+7 * dc21.im;
    r_scp0_idx_0_tmp_tmp =
        jb_scp0_idx_0_tmp_tmp * dc22.re - ob_scp0_idx_0_tmp_tmp * dc22.im;
    ob_scp0_idx_0_tmp_tmp =
        jb_scp0_idx_0_tmp_tmp * dc22.im + ob_scp0_idx_0_tmp_tmp * dc22.re;
    jb_scp0_idx_0_tmp_tmp = 5.59840650625E+7 * dc23.re;
    i_scp0_idx_0_tmp_tmp = 5.59840650625E+7 * dc23.im;
    t_scp0_idx_0_tmp_tmp = jb_scp0_idx_0_tmp_tmp * c30_tmp_tmp.re -
                           i_scp0_idx_0_tmp_tmp * c30_tmp_tmp.im;
    i_scp0_idx_0_tmp_tmp = jb_scp0_idx_0_tmp_tmp * c30_tmp_tmp.im +
                           i_scp0_idx_0_tmp_tmp * c30_tmp_tmp.re;
    jb_scp0_idx_0_tmp_tmp = t_scp0_idx_0_tmp_tmp * c_c30_tmp_tmp.re -
                            i_scp0_idx_0_tmp_tmp * c_c30_tmp_tmp.im;
    i_scp0_idx_0_tmp_tmp = t_scp0_idx_0_tmp_tmp * c_c30_tmp_tmp.im +
                           i_scp0_idx_0_tmp_tmp * c_c30_tmp_tmp.re;
    t_scp0_idx_0_tmp_tmp = 2.2393626025E+8 * dc24.re;
    q_scp0_idx_0_tmp_tmp = 2.2393626025E+8 * dc24.im;
    v_scp0_idx_0_tmp_tmp = t_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.re -
                           q_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.im;
    q_scp0_idx_0_tmp_tmp = t_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.im +
                           q_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.re;
    t_scp0_idx_0_tmp_tmp = 3.35904390375E+8 * dc25.re;
    y_scp0_idx_0_tmp_tmp = 3.35904390375E+8 * dc25.im;
    gb_scp0_idx_0_tmp_tmp = t_scp0_idx_0_tmp_tmp * c30_tmp_tmp.re -
                            y_scp0_idx_0_tmp_tmp * c30_tmp_tmp.im;
    y_scp0_idx_0_tmp_tmp = t_scp0_idx_0_tmp_tmp * c30_tmp_tmp.im +
                           y_scp0_idx_0_tmp_tmp * c30_tmp_tmp.re;
    t_scp0_idx_0_tmp_tmp = 5.59840650625E+7 * dc26.re;
    ab_scp0_idx_0_tmp_tmp = 5.59840650625E+7 * dc26.im;
    nb_scp0_idx_0_tmp_tmp = t_scp0_idx_0_tmp_tmp * c30_tmp_tmp.re -
                            ab_scp0_idx_0_tmp_tmp * c30_tmp_tmp.im;
    ab_scp0_idx_0_tmp_tmp = t_scp0_idx_0_tmp_tmp * c30_tmp_tmp.im +
                            ab_scp0_idx_0_tmp_tmp * c30_tmp_tmp.re;
    t_scp0_idx_0_tmp_tmp = nb_scp0_idx_0_tmp_tmp * e_c30_tmp_tmp.re -
                           ab_scp0_idx_0_tmp_tmp * e_c30_tmp_tmp.im;
    ab_scp0_idx_0_tmp_tmp = nb_scp0_idx_0_tmp_tmp * e_c30_tmp_tmp.im +
                            ab_scp0_idx_0_tmp_tmp * e_c30_tmp_tmp.re;
    nb_scp0_idx_0_tmp_tmp = 1.11968130125E+8 * b_a.re;
    s_scp0_idx_0_tmp_tmp = 1.11968130125E+8 * b_a.im;
    cphi = nb_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.re -
           s_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.im;
    s_scp0_idx_0_tmp_tmp = nb_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.im +
                           s_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.re;
    nb_scp0_idx_0_tmp_tmp = 5.59840650625E+7 * e_c10_tmp.re;
    u_scp0_idx_0_tmp_tmp = 5.59840650625E+7 * e_c10_tmp.im;
    cp01_idx_0 = nb_scp0_idx_0_tmp_tmp * c30_tmp_tmp.re -
                 u_scp0_idx_0_tmp_tmp * c30_tmp_tmp.im;
    u_scp0_idx_0_tmp_tmp = nb_scp0_idx_0_tmp_tmp * c30_tmp_tmp.im +
                           u_scp0_idx_0_tmp_tmp * c30_tmp_tmp.re;
    nb_scp0_idx_0_tmp_tmp = 8.957450409999994E+8 * c30_tmp.re;
    w_scp0_idx_0_tmp_tmp = 8.957450409999994E+8 * c30_tmp.im;
    cp02_idx_0 = nb_scp0_idx_0_tmp_tmp * b_c30_tmp.re -
                 w_scp0_idx_0_tmp_tmp * b_c30_tmp.im;
    w_scp0_idx_0_tmp_tmp = nb_scp0_idx_0_tmp_tmp * b_c30_tmp.im +
                           w_scp0_idx_0_tmp_tmp * b_c30_tmp.re;
    nb_scp0_idx_0_tmp_tmp =
        cp02_idx_0 * b_c10_tmp_tmp.re - w_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.im;
    w_scp0_idx_0_tmp_tmp =
        cp02_idx_0 * b_c10_tmp_tmp.im + w_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.re;
    cp02_idx_0 = 1.3436175615E+9 * c_c30_tmp.re;
    x_scp0_idx_0_tmp_tmp = 1.3436175615E+9 * c_c30_tmp.im;
    scr0 = cp02_idx_0 * d_c30_tmp.re - x_scp0_idx_0_tmp_tmp * d_c30_tmp.im;
    x_scp0_idx_0_tmp_tmp =
        cp02_idx_0 * d_c30_tmp.im + x_scp0_idx_0_tmp_tmp * d_c30_tmp.re;
    cp02_idx_0 =
        scr0 * b_c10_tmp_tmp.re - x_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.im;
    x_scp0_idx_0_tmp_tmp =
        scr0 * b_c10_tmp_tmp.im + x_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.re;
    scr0 = 2.2393626025E+8 * e_c30_tmp.re;
    ccr0 = 2.2393626025E+8 * e_c30_tmp.im;
    cc4_tmp = scr0 * f_c30_tmp.re - ccr0 * f_c30_tmp.im;
    ccr0 = scr0 * f_c30_tmp.im + ccr0 * f_c30_tmp.re;
    scr0 = cc4_tmp * c30_tmp_tmp.re - ccr0 * c30_tmp_tmp.im;
    ccr0 = cc4_tmp * c30_tmp_tmp.im + ccr0 * c30_tmp_tmp.re;
    cc4_tmp = 5.59840650625E+7 * g_c30_tmp.re;
    sc4 = 5.59840650625E+7 * g_c30_tmp.im;
    cc4 = cc4_tmp * h_c30_tmp.re - sc4 * h_c30_tmp.im;
    sc4 = cc4_tmp * h_c30_tmp.im + sc4 * h_c30_tmp.re;
    cc4_tmp = cc4 * c30_tmp_tmp.re - sc4 * c30_tmp_tmp.im;
    sc4 = cc4 * c30_tmp_tmp.im + sc4 * c30_tmp_tmp.re;
    cc4 = cc4_tmp * c_c30_tmp_tmp.re - sc4 * c_c30_tmp_tmp.im;
    sc4 = cc4_tmp * c_c30_tmp_tmp.im + sc4 * c_c30_tmp_tmp.re;
    cc4_tmp = 2.2393626025E+8 * i_c30_tmp.re;
    crw = 2.2393626025E+8 * i_c30_tmp.im;
    w1_idx_2 = cc4_tmp * j_c30_tmp.re - crw * j_c30_tmp.im;
    crw = cc4_tmp * j_c30_tmp.im + crw * j_c30_tmp.re;
    cc4_tmp = w1_idx_2 * b_c10_tmp_tmp.re - crw * b_c10_tmp_tmp.im;
    crw = w1_idx_2 * b_c10_tmp_tmp.im + crw * b_c10_tmp_tmp.re;
    w1_idx_2 = 2.2393626025E+8 * k_c30_tmp.re;
    w1_idx_1 = 2.2393626025E+8 * k_c30_tmp.im;
    w1_idx_3 = w1_idx_2 * l_c30_tmp.re - w1_idx_1 * l_c30_tmp.im;
    w1_idx_1 = w1_idx_2 * l_c30_tmp.im + w1_idx_1 * l_c30_tmp.re;
    w1_idx_2 = w1_idx_3 * b_c10_tmp_tmp.re - w1_idx_1 * b_c10_tmp_tmp.im;
    w1_idx_1 = w1_idx_3 * b_c10_tmp_tmp.im + w1_idx_1 * b_c10_tmp_tmp.re;
    w1_idx_3 = 3.35904390375E+8 * m_c30_tmp.re;
    w2_idx_0 = 3.35904390375E+8 * m_c30_tmp.im;
    w2_idx_2 = w1_idx_3 * b_c20_tmp.re - w2_idx_0 * b_c20_tmp.im;
    w2_idx_0 = w1_idx_3 * b_c20_tmp.im + w2_idx_0 * b_c20_tmp.re;
    w1_idx_3 = w2_idx_2 * c30_tmp_tmp.re - w2_idx_0 * c30_tmp_tmp.im;
    w2_idx_0 = w2_idx_2 * c30_tmp_tmp.im + w2_idx_0 * c30_tmp_tmp.re;
    w2_idx_2 = 1.11968130125E+8 * c10_tmp.re;
    w2_idx_1 = 1.11968130125E+8 * c10_tmp.im;
    w2_idx_3 = w2_idx_2 * b_c10_tmp.re - w2_idx_1 * b_c10_tmp.im;
    w2_idx_1 = w2_idx_2 * b_c10_tmp.im + w2_idx_1 * b_c10_tmp.re;
    w2_idx_2 = w2_idx_3 * c30_tmp_tmp.re - w2_idx_1 * c30_tmp_tmp.im;
    w2_idx_1 = w2_idx_3 * c30_tmp_tmp.im + w2_idx_1 * c30_tmp_tmp.re;
    w2_idx_3 = 5.59840650625E+7 * c_c10_tmp.re;
    v2_idx_0 = 5.59840650625E+7 * c_c10_tmp.im;
    v2_idx_1 = w2_idx_3 * d_c10_tmp.re - v2_idx_0 * d_c10_tmp.im;
    v2_idx_0 = w2_idx_3 * d_c10_tmp.im + v2_idx_0 * d_c10_tmp.re;
    w2_idx_3 = v2_idx_1 * c30_tmp_tmp.re - v2_idx_0 * c30_tmp_tmp.im;
    v2_idx_0 = v2_idx_1 * c30_tmp_tmp.im + v2_idx_0 * c30_tmp_tmp.re;
    v2_idx_1 = w2_idx_3 * e_c30_tmp_tmp.re - v2_idx_0 * e_c30_tmp_tmp.im;
    v2_idx_0 = w2_idx_3 * e_c30_tmp_tmp.im + v2_idx_0 * e_c30_tmp_tmp.re;
    w2_idx_3 = 1.11968130125E+8 * f_c10_tmp.re;
    v2_idx_2 = 1.11968130125E+8 * f_c10_tmp.im;
    v3_idx_0 = w2_idx_3 * g_c10_tmp.re - v2_idx_2 * g_c10_tmp.im;
    v2_idx_2 = w2_idx_3 * g_c10_tmp.im + v2_idx_2 * g_c10_tmp.re;
    w2_idx_3 = v3_idx_0 * b_c10_tmp_tmp.re - v2_idx_2 * b_c10_tmp_tmp.im;
    v2_idx_2 = v3_idx_0 * b_c10_tmp_tmp.im + v2_idx_2 * b_c10_tmp_tmp.re;
    v3_idx_0 = 5.59840650625E+7 * h_c10_tmp.re;
    e_scp0_idx_0_tmp_tmp = 5.59840650625E+7 * h_c10_tmp.im;
    g_scp0_idx_0_tmp_tmp =
        v3_idx_0 * i_c10_tmp.re - e_scp0_idx_0_tmp_tmp * i_c10_tmp.im;
    e_scp0_idx_0_tmp_tmp =
        v3_idx_0 * i_c10_tmp.im + e_scp0_idx_0_tmp_tmp * i_c10_tmp.re;
    v3_idx_0 = g_scp0_idx_0_tmp_tmp * c30_tmp_tmp.re -
               e_scp0_idx_0_tmp_tmp * c30_tmp_tmp.im;
    e_scp0_idx_0_tmp_tmp = g_scp0_idx_0_tmp_tmp * c30_tmp_tmp.im +
                           e_scp0_idx_0_tmp_tmp * c30_tmp_tmp.re;
    g_scp0_idx_0_tmp_tmp = 3.5829801639999986E+9 * j_c10_tmp.re;
    h_scp0_idx_0_tmp_tmp = 3.5829801639999986E+9 * j_c10_tmp.im;
    f_scp0_idx_0_tmp_tmp =
        g_scp0_idx_0_tmp_tmp * c20_tmp.re - h_scp0_idx_0_tmp_tmp * c20_tmp.im;
    h_scp0_idx_0_tmp_tmp =
        g_scp0_idx_0_tmp_tmp * c20_tmp.im + h_scp0_idx_0_tmp_tmp * c20_tmp.re;
    g_scp0_idx_0_tmp_tmp = f_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.re -
                           h_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.im;
    h_scp0_idx_0_tmp_tmp = f_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.im +
                           h_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.re;
    dc3.re =
        (((((((((((((((((((((((((((((((((((1.11968130125E+8 * dc1.re +
                                           5.59840650625E+7 * dc2.re) -
                                          5.5984065062500015E+7) -
                                         2.7992032531249989E+7) +
                                        5.59840650625E+7) -
                                       (k_re * b_c10_tmp_tmp.re -
                                        f_im * b_c10_tmp_tmp.im)) +
                                      (l_re * c30_tmp_tmp.re -
                                       p_scp0_idx_0_tmp_tmp * c30_tmp_tmp.im)) -
                                     (b_sc5_tmp_tmp * b_c10_tmp_tmp.re -
                                      kb_scp0_idx_0_tmp_tmp *
                                          b_c10_tmp_tmp.im)) +
                                    (re * c30_tmp_tmp.re -
                                     lb_scp0_idx_0_tmp_tmp * c30_tmp_tmp.im)) +
                                   (c_re * 0.0 - mb_scp0_idx_0_tmp_tmp * 4.0)) -
                                  (b_re * b_c30_tmp_tmp.re -
                                   scp0_idx_0_tmp_tmp_tmp * b_c30_tmp_tmp.im)) -
                                 (e_re * 0.0 - im * 4.0)) +
                                (d_re * d_c30_tmp_tmp.re -
                                 b_im * d_c30_tmp_tmp.im)) +
                               (f_re * b_c30_tmp_tmp.re -
                                c_im * b_c30_tmp_tmp.im)) -
                              (h_re * 0.0 - d_im * 4.0)) -
                             (j_re * b_c30_tmp_tmp.re -
                              e_im * b_c30_tmp_tmp.im)) +
                            (g_re * d_c30_tmp_tmp.re -
                             hb_scp0_idx_0_tmp_tmp * d_c30_tmp_tmp.im)) +
                           (i_re * 0.0 - ib_scp0_idx_0_tmp_tmp * 4.0)) +
                          (r_scp0_idx_0_tmp_tmp * d_c30_tmp_tmp.re -
                           ob_scp0_idx_0_tmp_tmp * d_c30_tmp_tmp.im)) -
                         (jb_scp0_idx_0_tmp_tmp * 0.0 -
                          i_scp0_idx_0_tmp_tmp * 4.0)) -
                        (v_scp0_idx_0_tmp_tmp * b_c30_tmp_tmp.re -
                         q_scp0_idx_0_tmp_tmp * b_c30_tmp_tmp.im)) -
                       (gb_scp0_idx_0_tmp_tmp * b_c30_tmp_tmp.re -
                        y_scp0_idx_0_tmp_tmp * b_c30_tmp_tmp.im)) +
                      (t_scp0_idx_0_tmp_tmp * 0.0 -
                       ab_scp0_idx_0_tmp_tmp * 4.0)) -
                     (cphi * d_c30_tmp_tmp.re -
                      s_scp0_idx_0_tmp_tmp * d_c30_tmp_tmp.im)) +
                    (cp01_idx_0 * d_c30_tmp_tmp.re -
                     u_scp0_idx_0_tmp_tmp * d_c30_tmp_tmp.im)) +
                   (nb_scp0_idx_0_tmp_tmp * b_c30_tmp_tmp.re -
                    w_scp0_idx_0_tmp_tmp * b_c30_tmp_tmp.im)) +
                  (cp02_idx_0 * b_c30_tmp_tmp.re -
                   x_scp0_idx_0_tmp_tmp * b_c30_tmp_tmp.im)) +
                 (scr0 * b_c30_tmp_tmp.re - ccr0 * b_c30_tmp_tmp.im)) +
                (cc4 * 0.0 - sc4 * 4.0)) -
               (cc4_tmp * b_c30_tmp_tmp.re - crw * b_c30_tmp_tmp.im)) -
              (w1_idx_2 * d_c30_tmp_tmp.re - w1_idx_1 * d_c30_tmp_tmp.im)) -
             (w1_idx_3 * b_c30_tmp_tmp.re - w2_idx_0 * b_c30_tmp_tmp.im)) +
            (w2_idx_2 * d_c30_tmp_tmp.re - w2_idx_1 * d_c30_tmp_tmp.im)) -
           (v2_idx_1 * 0.0 - v2_idx_0 * 4.0)) -
          (w2_idx_3 * d_c30_tmp_tmp.re - v2_idx_2 * d_c30_tmp_tmp.im)) +
         (v3_idx_0 * d_c30_tmp_tmp.re -
          e_scp0_idx_0_tmp_tmp * d_c30_tmp_tmp.im)) -
        (g_scp0_idx_0_tmp_tmp * b_c30_tmp_tmp.re -
         h_scp0_idx_0_tmp_tmp * b_c30_tmp_tmp.im);
    dc3.im =
        ((((((((((((((((((((((((((((((((((1.11968130125E+8 * dc1.im +
                                          5.59840650625E+7 * dc2.im) -
                                         9.6967245102491692E+7) +
                                        4.8483622551245853E+7) -
                                       (k_re * b_c10_tmp_tmp.im +
                                        f_im * b_c10_tmp_tmp.re)) +
                                      (l_re * c30_tmp_tmp.im +
                                       p_scp0_idx_0_tmp_tmp * c30_tmp_tmp.re)) -
                                     (b_sc5_tmp_tmp * b_c10_tmp_tmp.im +
                                      kb_scp0_idx_0_tmp_tmp *
                                          b_c10_tmp_tmp.re)) +
                                    (re * c30_tmp_tmp.im +
                                     lb_scp0_idx_0_tmp_tmp * c30_tmp_tmp.re)) +
                                   (c_re * 4.0 + mb_scp0_idx_0_tmp_tmp * 0.0)) -
                                  (b_re * b_c30_tmp_tmp.im +
                                   scp0_idx_0_tmp_tmp_tmp * b_c30_tmp_tmp.re)) -
                                 (e_re * 4.0 + im * 0.0)) +
                                (d_re * d_c30_tmp_tmp.im +
                                 b_im * d_c30_tmp_tmp.re)) +
                               (f_re * b_c30_tmp_tmp.im +
                                c_im * b_c30_tmp_tmp.re)) -
                              (h_re * 4.0 + d_im * 0.0)) -
                             (j_re * b_c30_tmp_tmp.im +
                              e_im * b_c30_tmp_tmp.re)) +
                            (g_re * d_c30_tmp_tmp.im +
                             hb_scp0_idx_0_tmp_tmp * d_c30_tmp_tmp.re)) +
                           (i_re * 4.0 + ib_scp0_idx_0_tmp_tmp * 0.0)) +
                          (r_scp0_idx_0_tmp_tmp * d_c30_tmp_tmp.im +
                           ob_scp0_idx_0_tmp_tmp * d_c30_tmp_tmp.re)) -
                         (jb_scp0_idx_0_tmp_tmp * 4.0 +
                          i_scp0_idx_0_tmp_tmp * 0.0)) -
                        (v_scp0_idx_0_tmp_tmp * b_c30_tmp_tmp.im +
                         q_scp0_idx_0_tmp_tmp * b_c30_tmp_tmp.re)) -
                       (gb_scp0_idx_0_tmp_tmp * b_c30_tmp_tmp.im +
                        y_scp0_idx_0_tmp_tmp * b_c30_tmp_tmp.re)) +
                      (t_scp0_idx_0_tmp_tmp * 4.0 +
                       ab_scp0_idx_0_tmp_tmp * 0.0)) -
                     (cphi * d_c30_tmp_tmp.im +
                      s_scp0_idx_0_tmp_tmp * d_c30_tmp_tmp.re)) +
                    (cp01_idx_0 * d_c30_tmp_tmp.im +
                     u_scp0_idx_0_tmp_tmp * d_c30_tmp_tmp.re)) +
                   (nb_scp0_idx_0_tmp_tmp * b_c30_tmp_tmp.im +
                    w_scp0_idx_0_tmp_tmp * b_c30_tmp_tmp.re)) +
                  (cp02_idx_0 * b_c30_tmp_tmp.im +
                   x_scp0_idx_0_tmp_tmp * b_c30_tmp_tmp.re)) +
                 (scr0 * b_c30_tmp_tmp.im + ccr0 * b_c30_tmp_tmp.re)) +
                (cc4 * 4.0 + sc4 * 0.0)) -
               (cc4_tmp * b_c30_tmp_tmp.im + crw * b_c30_tmp_tmp.re)) -
              (w1_idx_2 * d_c30_tmp_tmp.im + w1_idx_1 * d_c30_tmp_tmp.re)) -
             (w1_idx_3 * b_c30_tmp_tmp.im + w2_idx_0 * b_c30_tmp_tmp.re)) +
            (w2_idx_2 * d_c30_tmp_tmp.im + w2_idx_1 * d_c30_tmp_tmp.re)) -
           (v2_idx_1 * 4.0 + v2_idx_0 * 0.0)) -
          (w2_idx_3 * d_c30_tmp_tmp.im + v2_idx_2 * d_c30_tmp_tmp.re)) +
         (v3_idx_0 * d_c30_tmp_tmp.im +
          e_scp0_idx_0_tmp_tmp * d_c30_tmp_tmp.re)) -
        (g_scp0_idx_0_tmp_tmp * b_c30_tmp_tmp.im +
         h_scp0_idx_0_tmp_tmp * b_c30_tmp_tmp.re);
    dc1 = power(dc3);
    k_re = 29928.999999999989 * c_c20_tmp.re - 0.0 * c_c20_tmp.im;
    f_im = 29928.999999999989 * c_c20_tmp.im + 0.0 * c_c20_tmp.re;
    l_re = k_re * dc27.re - f_im * dc27.im;
    f_im = k_re * dc27.im + f_im * dc27.re;
    k_re = l_re * c_c10_tmp_tmp.re - f_im * c_c10_tmp_tmp.im;
    f_im = l_re * c_c10_tmp_tmp.im + f_im * c_c10_tmp_tmp.re;
    l_re = 59858.0 * dc28.re - 0.0 * dc28.im;
    p_scp0_idx_0_tmp_tmp = 59858.0 * dc28.im + 0.0 * dc28.re;
    b_sc5_tmp_tmp = l_re * dc29.re - p_scp0_idx_0_tmp_tmp * dc29.im;
    p_scp0_idx_0_tmp_tmp = l_re * dc29.im + p_scp0_idx_0_tmp_tmp * dc29.re;
    l_re = b_sc5_tmp_tmp * c_c10_tmp_tmp.re -
           p_scp0_idx_0_tmp_tmp * c_c10_tmp_tmp.im;
    p_scp0_idx_0_tmp_tmp = b_sc5_tmp_tmp * c_c10_tmp_tmp.im +
                           p_scp0_idx_0_tmp_tmp * c_c10_tmp_tmp.re;
    b_sc5_tmp_tmp = 7482.25 * dc30.re;
    kb_scp0_idx_0_tmp_tmp = 7482.25 * dc30.im;
    re = 7482.25 * dc32.re;
    lb_scp0_idx_0_tmp_tmp = 7482.25 * dc32.im;
    b_re = re * b_c10_tmp_tmp.re - lb_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.im;
    lb_scp0_idx_0_tmp_tmp =
        re * b_c10_tmp_tmp.im + lb_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.re;
    re = 7482.25 * dc33.re;
    mb_scp0_idx_0_tmp_tmp = 7482.25 * dc33.im;
    c_re = 7482.25 * dc34.re;
    scp0_idx_0_tmp_tmp_tmp = 7482.25 * dc34.im;
    d_re = c_re * c_c30_tmp_tmp.re - scp0_idx_0_tmp_tmp_tmp * c_c30_tmp_tmp.im;
    scp0_idx_0_tmp_tmp_tmp =
        c_re * c_c30_tmp_tmp.im + scp0_idx_0_tmp_tmp_tmp * c_c30_tmp_tmp.re;
    c_re = 7482.25 * dc35.re;
    im = 7482.25 * dc35.im;
    e_re = 7482.25 * dc36.re;
    b_im = 7482.25 * dc36.im;
    h_re = e_re * dc37.re - b_im * dc37.im;
    b_im = e_re * dc37.im + b_im * dc37.re;
    e_re = h_re * c_c30_tmp_tmp.re - b_im * c_c30_tmp_tmp.im;
    b_im = h_re * c_c30_tmp_tmp.im + b_im * c_c30_tmp_tmp.re;
    h_re = 7482.25 * dc38.re;
    c_im = 7482.25 * dc38.im;
    f_re = h_re * dc39.re - c_im * dc39.im;
    c_im = h_re * dc39.im + c_im * dc39.re;
    h_re = f_re * b_c30_tmp_tmp.re - c_im * b_c30_tmp_tmp.im;
    c_im = f_re * b_c30_tmp_tmp.im + c_im * b_c30_tmp_tmp.re;
    f_re = 7482.25 * dc40.re;
    d_im = 7482.25 * dc40.im;
    i_re = f_re * dc41.re - d_im * dc41.im;
    d_im = f_re * dc41.im + d_im * dc41.re;
    f_re = 7482.25 * dc42.re;
    e_im = 7482.25 * dc42.im;
    j_re = f_re * b_c10_tmp_tmp.re - e_im * b_c10_tmp_tmp.im;
    e_im = f_re * b_c10_tmp_tmp.im + e_im * b_c10_tmp_tmp.re;
    f_re = j_re * c_c30_tmp_tmp.re - e_im * c_c30_tmp_tmp.im;
    e_im = j_re * c_c30_tmp_tmp.im + e_im * c_c30_tmp_tmp.re;
    j_re = 7482.25 * dc43.re;
    hb_scp0_idx_0_tmp_tmp = 7482.25 * dc43.im;
    g_re = j_re * b_c10_tmp_tmp.re - hb_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.im;
    hb_scp0_idx_0_tmp_tmp =
        j_re * b_c10_tmp_tmp.im + hb_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.re;
    j_re = 7482.25 * dc44.re;
    ib_scp0_idx_0_tmp_tmp = 7482.25 * dc44.im;
    jb_scp0_idx_0_tmp_tmp = j_re * dc45.re - ib_scp0_idx_0_tmp_tmp * dc45.im;
    ib_scp0_idx_0_tmp_tmp = j_re * dc45.im + ib_scp0_idx_0_tmp_tmp * dc45.re;
    j_re = jb_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.re -
           ib_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.im;
    ib_scp0_idx_0_tmp_tmp = jb_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.im +
                            ib_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.re;
    jb_scp0_idx_0_tmp_tmp =
        j_re * c_c30_tmp_tmp.re - ib_scp0_idx_0_tmp_tmp * c_c30_tmp_tmp.im;
    ib_scp0_idx_0_tmp_tmp =
        j_re * c_c30_tmp_tmp.im + ib_scp0_idx_0_tmp_tmp * c_c30_tmp_tmp.re;
    j_re = 7482.25 * dc46.re;
    ob_scp0_idx_0_tmp_tmp = 7482.25 * dc46.im;
    r_scp0_idx_0_tmp_tmp = j_re * dc47.re - ob_scp0_idx_0_tmp_tmp * dc47.im;
    ob_scp0_idx_0_tmp_tmp = j_re * dc47.im + ob_scp0_idx_0_tmp_tmp * dc47.re;
    j_re = r_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.re -
           ob_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.im;
    ob_scp0_idx_0_tmp_tmp = r_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.im +
                            ob_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.re;
    r_scp0_idx_0_tmp_tmp =
        j_re * b_c30_tmp_tmp.re - ob_scp0_idx_0_tmp_tmp * b_c30_tmp_tmp.im;
    ob_scp0_idx_0_tmp_tmp =
        j_re * b_c30_tmp_tmp.im + ob_scp0_idx_0_tmp_tmp * b_c30_tmp_tmp.re;
    j_re = 7482.25 * dc48.re;
    i_scp0_idx_0_tmp_tmp = 7482.25 * dc48.im;
    t_scp0_idx_0_tmp_tmp = j_re * dc49.re - i_scp0_idx_0_tmp_tmp * dc49.im;
    i_scp0_idx_0_tmp_tmp = j_re * dc49.im + i_scp0_idx_0_tmp_tmp * dc49.re;
    j_re = t_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.re -
           i_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.im;
    i_scp0_idx_0_tmp_tmp = t_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.im +
                           i_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.re;
    cc4_tmp =
        -(((c10_tmp_tmp.re * dc1.re - c10_tmp_tmp.im * dc1.im) +
           (k_re * c_c30_tmp_tmp.re - f_im * c_c30_tmp_tmp.im)) -
          (l_re * c_c30_tmp_tmp.re - p_scp0_idx_0_tmp_tmp * c_c30_tmp_tmp.im));
    ccr0 =
        -(((c10_tmp_tmp.re * dc1.im + c10_tmp_tmp.im * dc1.re) +
           (k_re * c_c30_tmp_tmp.im + f_im * c_c30_tmp_tmp.re)) -
          (l_re * c_c30_tmp_tmp.im + p_scp0_idx_0_tmp_tmp * c_c30_tmp_tmp.re));
    scr0 = (((((((((((((((b_sc5_tmp_tmp * 0.0 - kb_scp0_idx_0_tmp_tmp * 2.0) -
                         7482.25 * dc31.re) -
                        3741.1250000000009) +
                       7482.25) -
                      (b_re * 0.0 - lb_scp0_idx_0_tmp_tmp * 2.0)) +
                     (re * b_c10_tmp_tmp.re -
                      mb_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.im)) +
                    (d_re * 0.0 - scp0_idx_0_tmp_tmp_tmp * 2.0)) -
                   (c_re * b_c30_tmp_tmp.re - im * b_c30_tmp_tmp.im)) +
                  (e_re * 0.0 - b_im * 2.0)) +
                 (h_re * 0.0 - c_im * 2.0)) +
                (i_re * b_c30_tmp_tmp.re - d_im * b_c30_tmp_tmp.im)) +
               (f_re * 0.0 - e_im * 2.0)) +
              (g_re * b_c30_tmp_tmp.re -
               hb_scp0_idx_0_tmp_tmp * b_c30_tmp_tmp.im)) +
             (jb_scp0_idx_0_tmp_tmp * 0.0 - ib_scp0_idx_0_tmp_tmp * 2.0)) -
            (r_scp0_idx_0_tmp_tmp * 0.0 - ob_scp0_idx_0_tmp_tmp * 2.0)) -
           (j_re * b_c30_tmp_tmp.re - i_scp0_idx_0_tmp_tmp * b_c30_tmp_tmp.im);
    cp02_idx_0 =
        ((((((((((((((b_sc5_tmp_tmp * 2.0 + kb_scp0_idx_0_tmp_tmp * 0.0) -
                     7482.25 * dc31.im) -
                    6479.818577466116) -
                   (b_re * 2.0 + lb_scp0_idx_0_tmp_tmp * 0.0)) +
                  (re * b_c10_tmp_tmp.im +
                   mb_scp0_idx_0_tmp_tmp * b_c10_tmp_tmp.re)) +
                 (d_re * 2.0 + scp0_idx_0_tmp_tmp_tmp * 0.0)) -
                (c_re * b_c30_tmp_tmp.im + im * b_c30_tmp_tmp.re)) +
               (e_re * 2.0 + b_im * 0.0)) +
              (h_re * 2.0 + c_im * 0.0)) +
             (i_re * b_c30_tmp_tmp.im + d_im * b_c30_tmp_tmp.re)) +
            (f_re * 2.0 + e_im * 0.0)) +
           (g_re * b_c30_tmp_tmp.im +
            hb_scp0_idx_0_tmp_tmp * b_c30_tmp_tmp.re)) +
          (jb_scp0_idx_0_tmp_tmp * 2.0 + ib_scp0_idx_0_tmp_tmp * 0.0)) -
         (r_scp0_idx_0_tmp_tmp * 2.0 + ob_scp0_idx_0_tmp_tmp * 0.0)) -
        (j_re * b_c30_tmp_tmp.im + i_scp0_idx_0_tmp_tmp * b_c30_tmp_tmp.re);
    if (cp02_idx_0 == 0.0) {
      if (ccr0 == 0.0) {
        dc1.re = cc4_tmp / scr0;
        dc1.im = 0.0;
      } else if (cc4_tmp == 0.0) {
        dc1.re = 0.0;
        dc1.im = ccr0 / scr0;
      } else {
        dc1.re = cc4_tmp / scr0;
        dc1.im = ccr0 / scr0;
      }
    } else if (scr0 == 0.0) {
      if (cc4_tmp == 0.0) {
        dc1.re = ccr0 / cp02_idx_0;
        dc1.im = 0.0;
      } else if (ccr0 == 0.0) {
        dc1.re = 0.0;
        dc1.im = -(cc4_tmp / cp02_idx_0);
      } else {
        dc1.re = ccr0 / cp02_idx_0;
        dc1.im = -(cc4_tmp / cp02_idx_0);
      }
    } else {
      crw = fabs(scr0);
      cphi = fabs(cp02_idx_0);
      if (crw > cphi) {
        cp01_idx_0 = cp02_idx_0 / scr0;
        cphi = scr0 + cp01_idx_0 * cp02_idx_0;
        dc1.re = (cc4_tmp + cp01_idx_0 * ccr0) / cphi;
        dc1.im = (ccr0 - cp01_idx_0 * cc4_tmp) / cphi;
      } else if (cphi == crw) {
        if (scr0 > 0.0) {
          cp01_idx_0 = 0.5;
        } else {
          cp01_idx_0 = -0.5;
        }
        if (cp02_idx_0 > 0.0) {
          cphi = 0.5;
        } else {
          cphi = -0.5;
        }
        dc1.re = (cc4_tmp * cp01_idx_0 + ccr0 * cphi) / crw;
        dc1.im = (ccr0 * cp01_idx_0 - cc4_tmp * cphi) / crw;
      } else {
        cp01_idx_0 = scr0 / cp02_idx_0;
        cphi = cp02_idx_0 + cp01_idx_0 * scr0;
        dc1.re = (cp01_idx_0 * cc4_tmp + ccr0) / cphi;
        dc1.im = (cp01_idx_0 * ccr0 - cc4_tmp) / cphi;
      }
    }
    b_log(&dc1);
    k_re = dc.re * 0.0 - dc.im;
    l_re = dc1.re * 0.0 - dc1.im;
    crw =
        0.766044443118978 * cos((1.298210328476112 - m_re) - 1.298210328476112);
    w1_idx_2 =
        0.766044443118978 * sin((1.298210328476112 - m_re) - 1.298210328476112);
    w1_idx_1 =
        0.766044443118978 * cos((1.298210328476112 - n_re) - 1.298210328476112);
    w1_idx_3 =
        0.766044443118978 * sin((1.298210328476112 - n_re) - 1.298210328476112);
    cp01_idx_0 = OBL_tmp_tmp * 0.0 - b_OBL_tmp_tmp * OBL_tmp;
    cp02_idx_0 = 0.0 * OBL_tmp + OBL_tmp_tmp * b_OBL_tmp_tmp;
    v1[0] = -(0.49999999999999994 *
                  (6.123233995736766E-17 * cp01_idx_0 - cp02_idx_0) -
              c_OBL_tmp_tmp * 0.86602540378443871);
    scr0 = OBL_tmp_tmp + 0.0 * b_OBL_tmp_tmp * OBL_tmp;
    ccr0 = OBL_tmp - OBL_tmp_tmp * 0.0 * b_OBL_tmp_tmp;
    cc4_tmp = c_OBL_tmp_tmp * 0.86602540378443871 * 0.0;
    v1[1] =
        0.49999999999999994 * (6.123233995736766E-17 * scr0 - ccr0) + cc4_tmp;
    sc4 = c_OBL_tmp_tmp * OBL_tmp_tmp;
    v1[2] = 0.49999999999999994 *
                (6.123233995736766E-17 * c_OBL_tmp_tmp * OBL_tmp + sc4) -
            0.86602540378443871 * b_OBL_tmp_tmp;
    w2_idx_0 =
        0.766044443118978 * cos((1.52502572060903 - o_re) - 1.52502572060903);
    w2_idx_2 =
        0.766044443118978 * sin((1.52502572060903 - o_re) - 1.52502572060903);
    w2_idx_1 =
        0.766044443118978 * cos((1.52502572060903 - p_re) - 1.52502572060903);
    w2_idx_3 =
        0.766044443118978 * sin((1.52502572060903 - p_re) - 1.52502572060903);
    cphi = c_OBL_tmp_tmp * 0.86602540378443871;
    v2_idx_0 = -(0.49999999999999994 * (-0.49999999999999978 * cp01_idx_0 +
                                        0.86602540378443871 * cp02_idx_0) -
                 cphi);
    v2_idx_1 = 0.49999999999999994 *
                   (-0.49999999999999978 * scr0 + 0.86602540378443871 * ccr0) +
               cc4_tmp;
    cc4 = 0.86602540378443871 * b_OBL_tmp_tmp;
    v2_idx_2 =
        0.49999999999999994 * (-0.49999999999999978 * c_OBL_tmp_tmp * OBL_tmp -
                               sc4 * 0.86602540378443871) -
        cc4;
    e_scp0_idx_0_tmp_tmp =
        sin((0.30696770204475443 - k_re) - 0.30696770204475443);
    f_scp0_idx_0_tmp_tmp =
        cos((0.30696770204475443 - k_re) - 0.30696770204475443);
    g_scp0_idx_0_tmp_tmp =
        sin((0.30696770204475443 - l_re) - 0.30696770204475443);
    h_scp0_idx_0_tmp_tmp =
        cos((0.30696770204475443 - l_re) - 0.30696770204475443);
    w3[0] = -e_scp0_idx_0_tmp_tmp;
    w3[2] = f_scp0_idx_0_tmp_tmp;
    w3[4] = 0.0;
    w3[1] = -g_scp0_idx_0_tmp_tmp;
    w3[3] = h_scp0_idx_0_tmp_tmp;
    w3[5] = 0.0;
    /* %此向量本来在c3坐标系中，为了便于下面的干涉检查计算，做统一坐标系处理 */
    v3_idx_0 = -(0.49999999999999994 * (0.50000000000000011 * cp01_idx_0 -
                                        -0.8660254037844386 * cp02_idx_0) -
                 cphi);
    scr0 = 0.49999999999999994 *
               (0.50000000000000011 * scr0 - -0.8660254037844386 * ccr0) +
           cc4_tmp;
    cphi =
        0.49999999999999994 * (sc4 * -0.8660254037844386 +
                               c_OBL_tmp_tmp * OBL_tmp * 0.50000000000000011) -
        cc4;
    /* 此向量本来在c3坐标系中，为了便于下面的干涉检查计算，做统一坐标系处理 */
    /*  eq1=w3(1)*v3(1)+w3(2)*v3(2)+w3(3)*v3(3)-R^2*cos(gama); */
    if (((0.0 - w1_idx_2) * v1[0] + crw * v1[1]) +
            (0.0 * w1_idx_2 - crw * 0.0) * v1[2] >=
        0.0) {
      *c1 = 1.298210328476112 - m_re;
      IL = 1;
    } else if (((0.0 - w1_idx_3) * v1[0] + w1_idx_1 * v1[1]) +
                   (0.0 * w1_idx_3 - w1_idx_1 * 0.0) * v1[2] >=
               0.0) {
      *c1 = 1.298210328476112 - n_re;
      IL = 2;
    } else {
      *c1 = 0.0;
      IL = 0;
    }
    if (((-0.0 - w2_idx_2) * v2_idx_0 + w2_idx_0 * v2_idx_1) +
            (0.0 * w2_idx_2 - w2_idx_0 * 0.0) * v2_idx_2 >=
        0.0) {
      *c2 = 1.52502572060903 - o_re;
      coffset = 1;
    } else if (((-0.0 - w2_idx_3) * v2_idx_0 + w2_idx_1 * v2_idx_1) +
                   (0.0 * w2_idx_3 - w2_idx_1 * 0.0) * v2_idx_2 >=
               0.0) {
      *c2 = 1.52502572060903 - p_re;
      coffset = 2;
    } else {
      *c2 = 0.0;
      coffset = 0;
    }
    if (((f_scp0_idx_0_tmp_tmp * cphi - scr0 * 0.0) * 0.0 +
         (v3_idx_0 * 0.0 - -e_scp0_idx_0_tmp_tmp * cphi) * 0.0) +
            (-e_scp0_idx_0_tmp_tmp * scr0 - v3_idx_0 * f_scp0_idx_0_tmp_tmp) <=
        0.0) {
      *c3 = 0.30696770204475443 - k_re;
      IM = 0;
    } else if (((cphi * h_scp0_idx_0_tmp_tmp - scr0 * 0.0) * 0.0 +
                (v3_idx_0 * 0.0 - -g_scp0_idx_0_tmp_tmp * cphi) * 0.0) +
                   (scr0 * -g_scp0_idx_0_tmp_tmp -
                    v3_idx_0 * h_scp0_idx_0_tmp_tmp) <=
               0.0) {
      *c3 = 0.30696770204475443 - l_re;
      IM = 1;
    } else {
      *c3 = 0.0;
      IM = -1;
    }
    if ((IL != 0) && (coffset != 0) && (IM + 1 != 0)) {
      if (*c1 > 3.1415926535897931) {
        *c1 -= 6.2831853071795862;
      } else if (*c2 > 3.1415926535897931) {
        *c2 -= 6.2831853071795862;
      }
      OBM[0] = 86.5 * c_OBL_tmp_tmp;
      OBM[1] = 86.5 * c_OBL_tmp_tmp * 0.0;
      OBM[2] = -86.5 * b_OBL_tmp_tmp;
      v1[0] = scr0 * OBM[2] - OBM[1] * cphi;
      v1[1] = OBM[0] * cphi - v3_idx_0 * OBM[2];
      v1[2] = v3_idx_0 * OBM[1] - OBM[0] * scr0;
      cp01_idx_0 = w3[IM + 4];
      cp02_idx_0 = w3[IM + 2];
      OBM[0] = cp02_idx_0 * cphi - scr0 * cp01_idx_0;
      OBM[1] = v3_idx_0 * cp01_idx_0 - w3[IM] * cphi;
      OBM[2] = w3[IM] * scr0 - v3_idx_0 * cp02_idx_0;
      if (((OBM[0] * v1[0] + OBM[1] * v1[1]) + OBM[2] * v1[2]) / b_norm(OBM) /
              b_norm(v1) >=
          -0.64278760968653936) {
        *c1 += cps;
        *c2 += cps;
        *c3 += cps;
      } else {
        *c1 = 0.0;
        *c2 = 0.0;
        *c3 = 0.0;
      }
    } else {
      *c1 = 0.0;
      *c2 = 0.0;
      *c3 = 0.0;
    }
}

/* End of code generation (IK_7DOF.c) */

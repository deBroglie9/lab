#ifndef KINEMATICS_H
#define KINEMATICS_H

#include <Eigen/Dense>
#include <Eigen/Geometry>
#include <vector>

#define RIGHT_ARM 0
#define LEFT_ARM 1

static void FK(int arm, double c[7], double T[4][4]){
  double T_temp[16];
  if(arm==RIGHT_ARM){
    FK_7DOF(c, T_temp);   
  }
  else if(arm==LEFT_ARM){
    FK_7DOF(c, T_temp);
    T_temp[2]=-T_temp[2];
    T_temp[6]=-T_temp[6];
    T_temp[8]=-T_temp[8];
    T_temp[9]=-T_temp[9];
    T_temp[14]=-T_temp[14];
  }
  for(int i=0;i<4;i++){
    for(int j=0;j<4;j++){
      T[i][j]=T_temp[j*4+i];
    }
  }
};

static void IK(int arm, double R[3][3], double phi, double Px, double Py,
                    double Pz, double c[7], double *flag){
  double R_temp[9];
  if(arm==RIGHT_ARM){
    R_temp[0]=R[0][0];
    R_temp[1]=R[1][0];
    R_temp[2]=R[2][0];
    R_temp[3]=R[0][1];
    R_temp[4]=R[1][1];
    R_temp[5]=R[2][1];
    R_temp[6]=R[0][2];
    R_temp[7]=R[1][2];
    R_temp[8]=R[2][2];
    IK_7DOF(R_temp, phi, Px, Py, Pz, c, flag);
  }
  else if(arm==LEFT_ARM){
    R_temp[0]=R[0][0];
    R_temp[1]=R[1][0];
    R_temp[2]=-R[2][0];
    R_temp[3]=R[0][1];
    R_temp[4]=R[1][1];
    R_temp[5]=-R[2][1];
    R_temp[6]=-R[0][2];
    R_temp[7]=-R[1][2];
    R_temp[8]=R[2][2];
    Pz=-Pz;
    IK_7DOF(R_temp, phi, Px, Py, Pz, c, flag);
  }
};

Eigen::Vector3d axis_trans(Eigen::Matrix3d R){
  Eigen::Vector3d Posture=R.eulerAngles(2,1,0);//Z-Y-X
  return Posture;
}

Eigen::Matrix3d axis_itrans(Eigen::Vector3d Posture){
  Eigen::Matrix3d R;
  R=Eigen::AngleAxisd(Posture[2], Eigen::Vector3d::UnitZ()) // 绕Z轴旋转
    * Eigen::AngleAxisd(Posture[1], Eigen::Vector3d::UnitY()) // 绕Y轴旋转
    * Eigen::AngleAxisd(Posture[0], Eigen::Vector3d::UnitX()); // 绕X轴旋转
  return R;
}

#endif
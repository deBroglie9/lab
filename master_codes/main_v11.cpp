/*****************************************************************************
 * 2025/12/25
 * 电机可以正常使能并进行运动
 * 目前接入2个编码器 14个驱动器 代码目前可连接16个从站，2个编码器+14个驱动器，需要修改 DRIVER_NUMBER ENCODER_NUMBER DOMAIN_NUMBER
 * 驱动器顺序为右臂1-7 -> 左臂1-7
 * 设置driver_enable,drivesr_disable,reading_driver，reading_ssi，control_pid函数
 * 设置模式选择函数，通过ControlMode修改控制模式（待测试）
 * 加入逆运动学求解函数，读入X,Y,Z和R(3*3逐行读入)
 * EtherCAT.h库可使用，不使用可设置CONFIGURE_EC 0
 * 
 * 给定了一组轨迹，可读入并执行（已调试），注意修改轨迹时修改对应csv的数组大小 NUMBER
 * 轨迹中1-14依次为左臂1-7、右臂1-7的关节角
 * 
 *  $Id: main.c,v 6a6dec6fc806 2012/09/19 17:46:58 fp $
 *
 *  Copyright (C) 2007-2009  Florian Pose, Ingenieurgemeinschaft IgH
 *
 *  This file is part of the IgH EtherCAT Master.
 *
 *  The IgH EtherCAT Master is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License version 2, as
 *  published by the Free Software Foundation.
 *
 *  The IgH EtherCAT Master is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General
 *  Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with the IgH EtherCAT Master; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 *  ---
 *
 *  The license mentioned above concerns the source code only. Using the
 *  EtherCAT technology and brand is only permitted in compliance with the
 *  industrial property and similar rights of Beckhoff Automation GmbH.
 *
 ****************************************************************************/
#include <errno.h>
#include <iostream>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <time.h>
#include <math.h>
//kinematics
#include "IK_7DOF.h"
#include "IK_7DOF_terminate.h"
#include "rt_nonfinite.h"
#include "FK_7DOF.h"
#include "FK_7DOF_terminate.h"
#include "rtwtypes.h"
//ethercat
#include "ecrt.h"
#include "EtherCAT.h"
//others
#include "cmdpanel.h"
#include "lpf.h"
#include "poly_traj.h"
/****************************************************************************/
// #define NUMBER 350014//350014
// 任务周期（以 ns 为单位）
#define MAX_SAFE_STACK (8 * 1024) //保证安全访问而不会出现故障的最大堆栈大小
/****************************************************************************/
// Application parameters
#define FREQUENCY 1000
#define PRIORITY 1
#define MAX_VELOCITY_1 900000
#define MAX_VELOCITY_2 160000
#define MAX_VELOCITY_3 112000
#define PERIODS_PER_SECOND   200
#define INIT_TIME 2
#define ERROR 1
#define RUNNING_TIME 600/*seconds*/
#define NUMBER 98014//350014

#define RIGHT_ARM 0
#define LEFT_ARM 1

// // 任务周期（以 ns 为单位）
/****************************************************************************/
//控制部分变量
static float Target_Position[DRIVER_NUMBER]={0,0,0,0,0,0,0,0,0,0,0,0,0,0};
static float Actual_Position[DRIVER_NUMBER];   
static float target_p[DRIVER_NUMBER];
static float actual_p[DRIVER_NUMBER];
static float target_p_last[DRIVER_NUMBER];
static float actual_p_last[DRIVER_NUMBER];
static float max_velocity[DRIVER_NUMBER]={0.5*MAX_VELOCITY_1,0.5*MAX_VELOCITY_1,0.5*MAX_VELOCITY_1,0.5*MAX_VELOCITY_1,0.5*MAX_VELOCITY_2,0.5*MAX_VELOCITY_2,0.5*MAX_VELOCITY_3,
0.5*MAX_VELOCITY_1,0.5*MAX_VELOCITY_1,0.5*MAX_VELOCITY_1,0.5*MAX_VELOCITY_1,0.5*MAX_VELOCITY_2,0.5*MAX_VELOCITY_2,0.5*MAX_VELOCITY_3};

static float offset_ssi[DRIVER_NUMBER];
static float constant_Kp[DRIVER_NUMBER]={40000*19.36/360,40000*19.36/360,40000*19.36/360,40000*19.36/360,4000*6/360,4000*6/360,4000*10/360,
40000*19.36/360,40000*19.36/360,40000*19.36/360,40000*19.36/360,4000*6/360,4000*6/360,4000*10/360};
static float constant_Torque[DRIVER_NUMBER]={40.0,40.0,40.0,40.0,5,5,1,40.0,40.0,40.0,40.0,5,5,1};
static float Position_Kp[DRIVER_NUMBER]={15,15,15,15,15,15,15,15,15,15,15,15,15,15};
static float Position_Ki[DRIVER_NUMBER];
static float Position_Kd[DRIVER_NUMBER]={1,1,1,1,1,1,1,1,1,1,1,1,1,1};
static float Error[DRIVER_NUMBER];
static float Error_Last[DRIVER_NUMBER];
static float Delta_Error[DRIVER_NUMBER];
static float Delta_Error_Last[DRIVER_NUMBER];
static float Integral[DRIVER_NUMBER];
static float Target_Velocity[DRIVER_NUMBER];
static float Actual_Velocity[DRIVER_NUMBER];
static float Actual_Torque[DRIVER_NUMBER];

static int flag_offset=0;
static float offset[DRIVER_NUMBER]={238.77,174.82,178.31,258.35,280.66,304.76,185.04,250.04,180.47,179.60,294.33,90.44,97.28,236.85};
static float offset_temp[DRIVER_NUMBER];
//left-right
static double values[NUMBER]; 

static CmdPanel *cmdptr = NULL;

static FILE *fp;

//程序状态变量
static unsigned int counter = 0;
static unsigned int counter1 = 0;
static unsigned int counter_slave = 0;
static unsigned int counter_domain = 0;
static unsigned int counter_loop= 0;
static unsigned int blink = 0x00;
static unsigned int flag = 0;
static unsigned int flag2 = 0;
static unsigned int stage = 0;
static unsigned int command = 0L;
static unsigned int flag_init[DRIVER_NUMBER];
static unsigned int flag_init_all;
static unsigned int flag_stop[DRIVER_NUMBER];
static unsigned int flag_stop_all;
static unsigned int flag_first[DRIVER_NUMBER];

// Timer
static unsigned int sig_alarms = 0;
static unsigned int user_alarms = 0;

static struct timeval tv1;
static struct timeval tv2;
static double time_diff;
static double time_test1;
static double time_test2;

static int ssi;
static unsigned int ain1;
static unsigned long ssi1;
static unsigned long dri;

static BiquadFilter filter;
float sampleRate = 1000.0;    // 采样率 1000Hz
float cutoffFreq = 0.2;      // 截止频率 1Hz
// 计算滤波器系数
// 模拟输入信号（正弦波+高频噪声）
FILE *csvFile=NULL;
float input=0;
float output=0;

int fd=-1;
struct sockaddr_in saddr;
static double angle[48000];
static double angle1[48000];
static double angle2[48000];

// 添加模式枚举
typedef enum {
    MODE_JOINT_TRAJECTORY = 0,    // 模式1: 关节轨迹运动
    MODE_MANUAL_JOINT = 1,         // 模式2: 手动调节关节位置
    MODE_CARTESIAN_TRAJECTORY = 2, // 模式3: 末端轨迹运动
    MODE_MANUAL_CARTESIAN = 3      // 模式4: 手动控制末端位姿
} ControlMode;

static ControlMode current_mode = MODE_JOINT_TRAJECTORY;
static int mode_changed = 0;

// 添加逆运动学参数
static double target_position_xyz[3] = {0};  // X, Y, Z
static double target_rotation[9] = {1,0,0,0,1,0,0,0,1};  // 3x3旋转矩阵
static double ik_result[14] = {0};  // 逆运动学计算结果

// 手动关节控制参数
static float manual_joint_targets[DRIVER_NUMBER] = {0};
static float joint_increment = 1.0;  // 每次调整的关节角度增量

// 末端手动控制参数
static float cartesian_increment = 0.01;  // 位置增量(m)
static float rotation_increment = 5.0;    // 旋转增量(度)

/****************************************************************************/
// 电机使能/去使能
void driver_enable(uint16_t slave_position){
int i=0;
// while( (() & 0x6f) != 0x27){
if ((EC_READ_U16(domain_pd[slave_position]+off_bytes_0x6041[slave_position]) & 0x0250) == 592)
{
    printf("*********************Servo Power on*********************\n");
    EC_WRITE_U8(domain_pd[slave_position]+off_bytes_0x6060[slave_position], 0x03);//速度模式
    EC_WRITE_U16(domain_pd[slave_position]+off_bytes_0x6040[slave_position], 0x06);
}
if ((EC_READ_U16(domain_pd[slave_position]+off_bytes_0x6041[slave_position]) & 0x031) == 49)
    {
        if ((EC_READ_U16(domain_pd[slave_position]+off_bytes_0x6041[slave_position]) & 0x033) == 51)
        {   printf("*********************Servo Enable*********************\n");
            EC_WRITE_U16(domain_pd[slave_position]+off_bytes_0x6040[slave_position], 0x0f);

        }
        else
        {   printf("*********************Servo Waitting*********************\n");
            EC_WRITE_U16(domain_pd[slave_position]+off_bytes_0x6040[slave_position], 0x07);
        }    
    }
}


void driver_disable(uint16_t slave_position)
{
    EC_WRITE_U16(domain_pd[slave_position]+off_bytes_0x6040[slave_position],0x06);
}


// 反馈读取
void reading_ssi(){
    uint32_t data_pointer[1];
    float angle_all[1];
    float angle;
    unsigned int off_bytes[DRIVER_NUMBER]={off_bytes_ain_1[0],off_bytes_ain_2[0],off_bytes_ain_3[0],off_bytes_ain_4[0],
        off_bytes_ain_5[0],off_bytes_ain_6[0],off_bytes_ain_7[0],off_bytes_ssi[0],off_bytes_ssi_2[0],off_bytes_ssi_3[0],
        off_bytes_ssi_4[0],off_bytes_ssi_5[0],off_bytes_ssi_6[0],off_bytes_ssi_7[0]};
    //先右臂1-7，再左臂1-7，右臂为ain，左臂为ssi（不代表通讯类型，仅仅做区分）
    for(counter_slave=0;counter_slave<DRIVER_NUMBER;counter_slave++){
        ssi=EC_READ_U32(domain_pd[DRIVER_NUMBER] + off_bytes[counter_slave]);
        data_pointer[0]=ssi;
        memcpy(angle_all, data_pointer, sizeof(data_pointer));
        Actual_Position[counter_slave]=angle_all[0];   
    }   

    ssi=EC_READ_U32(domain_pd[DRIVER_NUMBER] + off_bytes_ain_1[0]);
    data_pointer[0]=ssi;
    memcpy(angle_all, data_pointer, sizeof(data_pointer));
    Actual_Position[0]=angle_all[0];   
    ssi=EC_READ_U32(domain_pd[DRIVER_NUMBER] + off_bytes_ain_2[0]);
    data_pointer[0]=ssi;
    memcpy(angle_all, data_pointer, sizeof(data_pointer));
    Actual_Position[1]=angle_all[0]; 
    ssi=EC_READ_U32(domain_pd[DRIVER_NUMBER] + off_bytes_ain_3[0]);
    data_pointer[0]=ssi;
    memcpy(angle_all, data_pointer, sizeof(data_pointer));
    Actual_Position[2]=angle_all[0];   
    ssi=EC_READ_U32(domain_pd[DRIVER_NUMBER] + off_bytes_ain_4[0]);
    data_pointer[0]=ssi;
    memcpy(angle_all, data_pointer, sizeof(data_pointer));
    Actual_Position[3]=angle_all[0];  
    ssi=EC_READ_U32(domain_pd[DRIVER_NUMBER] + off_bytes_ain_5[0]);
    data_pointer[0]=ssi;
    memcpy(angle_all, data_pointer, sizeof(data_pointer));
    Actual_Position[4]=angle_all[0];    
    ssi=EC_READ_U32(domain_pd[DRIVER_NUMBER] + off_bytes_ain_6[0]);
    data_pointer[0]=ssi;
    memcpy(angle_all, data_pointer, sizeof(data_pointer));
    Actual_Position[5]=angle_all[0];  
    ssi=EC_READ_U32(domain_pd[DRIVER_NUMBER] + off_bytes_ain_7[0]);
    data_pointer[0]=ssi;
    memcpy(angle_all, data_pointer, sizeof(data_pointer));
    Actual_Position[6]=angle_all[0];
    ssi=EC_READ_U32(domain_pd[DRIVER_NUMBER] + off_bytes_ssi[0]);
    data_pointer[0]=ssi;
    memcpy(angle_all, data_pointer, sizeof(data_pointer));
    Actual_Position[7]=angle_all[0];   
    ssi=EC_READ_U32(domain_pd[DRIVER_NUMBER] + off_bytes_ssi_2[0]);
    data_pointer[0]=ssi;
    memcpy(angle_all, data_pointer, sizeof(data_pointer));
    Actual_Position[8]=angle_all[0];
    ssi=EC_READ_U32(domain_pd[DRIVER_NUMBER] + off_bytes_ssi_3[0]);
    data_pointer[0]=ssi;
    memcpy(angle_all, data_pointer, sizeof(data_pointer));
    Actual_Position[9]=angle_all[0];     
    ssi=EC_READ_U32(domain_pd[DRIVER_NUMBER] + off_bytes_ssi_4[0]);
    data_pointer[0]=ssi;
    memcpy(angle_all, data_pointer, sizeof(data_pointer));
    Actual_Position[10]=angle_all[0];  
    ssi=EC_READ_U32(domain_pd[DRIVER_NUMBER] + off_bytes_ssi_5[0]);
    data_pointer[0]=ssi;
    memcpy(angle_all, data_pointer, sizeof(data_pointer));
    Actual_Position[11]=angle_all[0];  
    ssi=EC_READ_U32(domain_pd[DRIVER_NUMBER] + off_bytes_ssi_6[0]);
    data_pointer[0]=ssi;
    memcpy(angle_all, data_pointer, sizeof(data_pointer));
    Actual_Position[12]=angle_all[0];
    ssi=EC_READ_U32(domain_pd[DRIVER_NUMBER] + off_bytes_ssi_7[0]);
    data_pointer[0]=ssi;
    memcpy(angle_all, data_pointer, sizeof(data_pointer));
    Actual_Position[13]=angle_all[0];
    
    

    for(counter_slave=0;counter_slave<DRIVER_NUMBER;counter_slave++){
            ssi=EC_READ_U32(domain_pd[counter_slave] + off_bytes_0x606C[counter_slave]);
            Actual_Velocity[counter_slave]=(float)ssi;
    }

    // if(flag_offset<1){
    //     for(counter_slave=0;counter_slave<DRIVER_NUMBER;counter_slave++){
    //        offset_temp[counter_slave]= Actual_Position[counter_slave];
    //     }
    //     flag_offset=1;
    // }
    
    printf("motor position:");
    for(counter_slave=0;counter_slave<DRIVER_NUMBER;counter_slave++){

            Actual_Position[counter_slave]=Actual_Position[counter_slave]-offset_temp[counter_slave];
            // if(counter_slave==0||counter_slave==1||counter_slave==2||counter_slave==4||counter_slave==12||counter_slave==13){
            //     Actual_Position[counter_slave]=-Actual_Position[counter_slave];
            // }
        while( (Actual_Position[counter_slave]>180) || (Actual_Position[counter_slave]<-180)){
            if(Actual_Position[counter_slave]>180){
                Actual_Position[counter_slave]=Actual_Position[counter_slave]-360;
            }
            else if(Actual_Position[counter_slave]<-180){
                Actual_Position[counter_slave]=Actual_Position[counter_slave]+360;
            }
        }
        printf("%.2f  ",Actual_Position[counter_slave]);  
    }

    printf("\n");

    // printf("target position:");
    // for(counter_slave=0;counter_slave<DRIVER_NUMBER;counter_slave++){
    //     printf("%.2f  ",Target_Position[counter_slave]);  
    // }
    // printf("\n");
    // printf("motor velocity:");
    // for(counter_slave=0;counter_slave<DRIVER_NUMBER;counter_slave++){
    //     printf("%.6f  ",Actual_Velocity[counter_slave]);  
    // }
    //printf("\n");

}

void reading_driver(){
    uint32_t data_pointer[1];
    float angle_all[1];
    float angle;
    
    for(counter_slave=0;counter_slave<DRIVER_NUMBER;counter_slave++){
        ssi=EC_READ_U32(domain_pd[counter_slave] + off_bytes_0x6064[counter_slave]);
        Actual_Position[counter_slave]=(float)ssi;
        Actual_Position[counter_slave]=Actual_Position[counter_slave]/constant_Kp[counter_slave];
        // data_pointer[0]=ssi;
        // memcpy(angle_all, data_pointer, sizeof(data_pointer));
        // Actual_Position[counter_slave]=angle_all[0];  
    }

    for(counter_slave=0;counter_slave<DRIVER_NUMBER;counter_slave++){
        ssi=EC_READ_U32(domain_pd[counter_slave] + off_bytes_0x606C[counter_slave]);
        Actual_Velocity[counter_slave]=(float)ssi;
    }

    printf("motor position:");
    for(counter_slave=0;counter_slave<DRIVER_NUMBER;counter_slave++){
        while( (Actual_Position[counter_slave]>180) || (Actual_Position[counter_slave]<-180)){
        if(Actual_Position[counter_slave]>180){
            Actual_Position[counter_slave]=Actual_Position[counter_slave]-360;
        }
        else if(Actual_Position[counter_slave]<-180){
            Actual_Position[counter_slave]=Actual_Position[counter_slave]+360;
        }
        }
        printf("%.6f  ",Actual_Position[counter_slave]);  
    }
    printf("\n");
    // printf("target position:");
    // for(counter_slave=0;counter_slave<DRIVER_NUMBER;counter_slave++){
        // printf("%.6f  ",Target_Position[counter_slave]);  
    // }
    // printf("\n");
    // printf("motor velocity:");
    // for(counter_slave=0;counter_slave<DRIVER_NUMBER;counter_slave++){
        // printf("%.6f  ",Actual_Velocity[counter_slave]);  
    // }
    // printf("\n");
}

void reading_current(){
    int16_t tra;
    float torque;
    // printf("motor current:");
    for(counter_slave=0;counter_slave<DRIVER_NUMBER;counter_slave++){
        tra=EC_READ_S16(domain_pd[counter_slave] + off_bytes_0x6077[counter_slave]);
        torque=((float)tra)/1000.0;
        // printf("%.3f ",torque);         
        // input = torque; 
        // output = processSample(&filter, input);
        // Actual_Torque[counter_slave]=output*constant_Torque[counter_slave];
        Actual_Torque[counter_slave]=torque;
    }
    // printf("\n");
    // printf("%f ",(float)EC_READ_S16(domain_pd[3] + off_bytes_0x6077[3]));
}

// PID控制
void control_pid(uint16_t slave_position){
    if(!flag_first[slave_position]){
        target_p_last[slave_position]=Target_Position[slave_position];
        actual_p_last[slave_position]=Actual_Position[slave_position];
        flag_first[slave_position]=1;
    }

    target_p[slave_position]=Target_Position[slave_position];
    actual_p[slave_position]=Actual_Position[slave_position];


    if((abs(target_p[slave_position]-target_p_last[slave_position])>20)){
        target_p[slave_position]=target_p_last[slave_position];
    }
    if(abs(actual_p[slave_position]-actual_p_last[slave_position])>20){
        actual_p[slave_position]=actual_p_last[slave_position];
    }

    target_p_last[slave_position]=target_p[slave_position];
    actual_p_last[slave_position]=actual_p[slave_position];

    Error[slave_position]=target_p[slave_position]-actual_p[slave_position];
    if(Error[slave_position]>180){
        Error[slave_position]-=360;
    }
    else if(Error[slave_position]<-180){
        Error[slave_position]+=360;
    }
    //printf("Error = %f ,",Error[slave_position]);
    Delta_Error[slave_position]=Error[slave_position]-Error_Last[slave_position];
    Integral[slave_position]=Integral[slave_position]+Error[slave_position];
    //printf("Delta_Error = %f ,",Delta_Error[slave_position]);
    Target_Velocity[slave_position]=Position_Kp[slave_position]*Error[slave_position]+Position_Ki[slave_position]*Integral[slave_position]+Position_Kd[slave_position]*Delta_Error[slave_position];
    //速度限制
    Target_Velocity[slave_position]= constant_Kp[slave_position] * Target_Velocity[slave_position];
    if(Target_Velocity[slave_position]>max_velocity[slave_position]){
        Target_Velocity[slave_position]=max_velocity[slave_position];
    }
    else if(Target_Velocity[slave_position]<-max_velocity[slave_position]){
        Target_Velocity[slave_position]=-max_velocity[slave_position];
    }
    // printf("Target_Velocity = %f \n",Target_Velocity[slave_position]);
    
    Error_Last[slave_position]=Error[slave_position];
    Delta_Error_Last[slave_position]=Delta_Error[slave_position];
    // printf("Target_Position=%f ,",target_p[slave_position]);
    // printf("Actual_Position=%f\n ",actual_p[slave_position]);
    
    EC_WRITE_S32(domain_pd[slave_position]+off_bytes_0x60ff[slave_position],(int)Target_Velocity[slave_position]);
    // printf("Target_Velocity =%f \n",EC_READ_S32(domain_pd[slave_position]+off_bytes_0x60ff[slave_position]));
}

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

// 手动关节控制处理函数
void handle_manual_joint_control() {
    // 读取键盘控制
    char joint_cmd = cmdptr->getUserCmd();
    int joint_to_move = -1;
    int direction = 0;
    
    // 映射按键到关节
    switch (joint_cmd) {
        case 'q': joint_to_move = 0; direction = 1; break;  // 关节1+
        case 'a': joint_to_move = 0; direction = -1; break; // 关节1-
        case 'w': joint_to_move = 1; direction = 1; break;  // 关节2+
        case 's': joint_to_move = 1; direction = -1; break;
        // ... [其他关节映射] ...
        case 'e': joint_to_move = 2; direction = 1; break;
        case 'd': joint_to_move = 2; direction = -1; break;
        // ... 以此类推 ...
        case 'p': joint_increment += 0.5; break;  // 增大增量
        case 'l': joint_increment -= 0.5; break;  // 减小增量
    }
    
    // 更新目标位置
    if (joint_to_move >= 0 && joint_to_move < DRIVER_NUMBER) {
        manual_joint_targets[joint_to_move] += direction * joint_increment;
        // 角度限制
        if (manual_joint_targets[joint_to_move] > 180) 
            manual_joint_targets[joint_to_move] = 180;
        if (manual_joint_targets[joint_to_move] < -180)
            manual_joint_targets[joint_to_move] = -180;
        
        printf("关节%d: %.2f°, 增量: %.2f\n", 
               joint_to_move+1, manual_joint_targets[joint_to_move], joint_increment);
    }
    
    // 设置目标位置
    for (int i = 0; i < DRIVER_NUMBER; i++) {
        Target_Position[i] = manual_joint_targets[i];
    }
}

// 末端轨迹运动处理函数
void handle_cartesian_trajectory() {
    // 这里可以从文件读取末端轨迹，或实时生成
    // 示例：圆形轨迹
    static double t = 0;
    double radius = 0.1;
    double speed = 0.1;
    
    // 更新末端位置
    target_position_xyz[0] = radius * cos(t);
    target_position_xyz[1] = radius * sin(t);
    target_position_xyz[2] = 0.3;  // 固定高度
    
    // 调用逆运动学
    if (calculate_inverse_kinematics(target_position_xyz, target_rotation, ik_result)) {
        for (int i = 0; i < DRIVER_NUMBER; i++) {
            Target_Position[i] = ik_result[i] * 180.0 / M_PI;  // 弧度转度
        }
    }
    
    t += speed * 0.001;  // 假设1ms周期
    if (t > 2 * M_PI) t -= 2 * M_PI;
}

// 手动末端控制处理函数
void handle_manual_cartesian_control() {
    // 读取键盘控制
    char cartesian_cmd = cmdptr->getUserCmd();
    
    // 位置控制
    switch (cartesian_cmd) {
        case 'i': target_position_xyz[0] += cartesian_increment; break;  // X+
        case 'k': target_position_xyz[0] -= cartesian_increment; break;  // X-
        case 'j': target_position_xyz[1] -= cartesian_increment; break;  // Y-
        case 'l': target_position_xyz[1] += cartesian_increment; break;  // Y+
        case 'u': target_position_xyz[2] += cartesian_increment; break;  // Z+
        case 'o': target_position_xyz[2] -= cartesian_increment; break;  // Z-
        // TODO: 添加旋转控制
    }
    
    // 调用逆运动学
    if (calculate_inverse_kinematics(target_position_xyz, target_rotation, ik_result)) {
        for (int i = 0; i < DRIVER_NUMBER; i++) {
            Target_Position[i] = ik_result[i] * 180.0 / M_PI;
        }
    }
    
    printf("末端位置: X=%.3f, Y=%.3f, Z=%.3f\n", 
           target_position_xyz[0], target_position_xyz[1], target_position_xyz[2]);
}

// 逆运动学计算函数
int calculate_inverse_kinematics(double *position, double *rotation, double *joint_angles) {
    // 调用你已有的IK_7DOF函数
    // 这里需要根据你的逆运动学函数进行适配
    
    // 示例调用（需要根据实际函数调整）
    // main_IK_7DOF();
    // 将结果复制到joint_angles
    
    // 暂时返回固定值
    for (int i = 0; i < 14; i++) {
        joint_angles[i] = 0.0;
    }
    return 1;  // 成功
}

/*****************************************************************************/
void cyclic_task()
{   
    // printf("%d\n",cmdptr->getUserCmd());
    // printf("%x\n",cmdptr->uservalue.Starttime);
    //逆运动学计算时间测试
    // double time1;
    // double time2;
    // gettimeofday(&tv2, NULL);
    // time_diff = (double)( tv2.tv_sec - tv1.tv_sec + (double)(tv2.tv_usec - tv1.tv_usec)/ 1000000);
    // time1=time_diff;
    // // printf("calculate start Time: %.4f s\n", time_diff);
    // main_IK_7DOF();
    // gettimeofday(&tv2, NULL);
    // time_diff = (double)( tv2.tv_sec - tv1.tv_sec + (double)(tv2.tv_usec - tv1.tv_usec)/ 1000000);
    // time2=time_diff;
    // // printf("calculate stop Time: %.4f s\n", time_diff);
    // printf("calculate time: %.6f s\n", time2-time1);
        //     reading_ssi();
        //     char sendBuf[1024];
        //     sprintf(sendBuf, "d:%f,%f,%f,%f,%f,%f,%f,  %f,%f,%f,%f,%f,%f,%f,  %f,%f,%f,%f,%f,%f,%f,  %f,%f,%f,%f,%f,%f,%f,  %f,%f,%f,%f,%f,%f,%f,  %f,%f,%f,%f,%f,%f,%f,  %f,%f,%f,%f,%f,%f,%f,  %f,%f,%f,%f,%f,%f,%f,  %f,%f,%f,%f,%f,%f,%f,  %f,%f,%f,%f,%f,%f,%f\n",
        //     Actual_Position[0],Actual_Position[1],Actual_Position[2],Actual_Position[3],Actual_Position[4],Actual_Position[5],Actual_Position[6],
        //     Actual_Position[7],Actual_Position[8],Actual_Position[9],Actual_Position[10],Actual_Position[11],Actual_Position[12],Actual_Position[13],
        //     Target_Position[0],Target_Position[1],Target_Position[2],Target_Position[3],Target_Position[4],Target_Position[5],Target_Position[6],
        //     Target_Position[7],Target_Position[8],Target_Position[9],Target_Position[10],Target_Position[11],Target_Position[12],Target_Position[13],
        //     Target_Velocity[0],Target_Velocity[1],Target_Velocity[2],Target_Velocity[3],Target_Velocity[4],Target_Velocity[5],Target_Velocity[6],
        //     Target_Velocity[7],Target_Velocity[8],Target_Velocity[9],Target_Velocity[10],Target_Velocity[11],Target_Velocity[12],Target_Velocity[13],
        //     Actual_Velocity[0],Actual_Velocity[1],Actual_Velocity[2],Actual_Velocity[3],Actual_Velocity[4],Actual_Velocity[5],Actual_Velocity[6],
        //     Actual_Velocity[7],Actual_Velocity[8],Actual_Velocity[9],Actual_Velocity[10],Actual_Velocity[11],Actual_Velocity[12],Actual_Velocity[13],
        //     Actual_Torque[0],Actual_Torque[1],Actual_Torque[2],Actual_Torque[3],Actual_Torque[4],Actual_Torque[5],Actual_Torque[6],
        //     Actual_Torque[7],Actual_Torque[8],Actual_Torque[9],Actual_Torque[10],Actual_Torque[11],Actual_Torque[12],Actual_Torque[13]);
        // sendto(fd, sendBuf, strlen(sendBuf) + 1, 0, (struct sockaddr *)&saddr, sizeof(saddr));
    // receive process data
    ecrt_master_receive(master);
    for(counter_domain=0;counter_domain<DOMAIN_NUMBER;counter_domain++){
        ecrt_domain_process(domain[counter_domain]);
    }
    for(counter_domain=0;counter_domain<DOMAIN_NUMBER;counter_domain++){
        check_domain_state(counter_domain);
    }

    if (counter)
    {
        counter--;
    }
    else
    {   

        counter = FREQUENCY/PERIODS_PER_SECOND-1;
        // calculate new process data
        // blink++;
        // main_IK_7DOF();

        if(counter1){
                counter1--;
        }
        else{
                counter1 = PERIODS_PER_SECOND-1;
                //每秒输打印时间
                gettimeofday(&tv2, NULL);
                time_diff = (double)( tv2.tv_sec - tv1.tv_sec + (double)(tv2.tv_usec - tv1.tv_usec)/ 1000000);
                printf("Time: %.4f s\n", time_diff);
                // printf("%x\n",cmdptr->uservalue.Starttime);
                // printf("%x\n",cmdptr->uservalue.Starttime);
        }



        //初始化通信
        if(time_diff < INIT_TIME){
            for(counter_domain=0;counter_domain<DOMAIN_NUMBER;counter_domain++){
                ecrt_domain_queue(domain[counter_domain]);
            }
            ecrt_master_send(master);
            return;
        }


        //电机使能
        if(cmdptr->uservalue.Preparetime && !cmdptr->uservalue.Starttime && !cmdptr->uservalue.Stoptime){
        // printf("motors enabling\n");
        if((time_diff < RUNNING_TIME) && (flag_init_all!=1) ){

            //!(flag_init[0]&flag_init[1]&flag_init[2]&flag_init[3]&flag_init[4]&flag_init[5]&flag_init[6]&flag_init[7]&flag_init[8]&flag_init[9]&flag_init[10]&flag_init[11]&flag_init[12]&flag_init[13])==1

            // driver_enable(6);
            // if((EC_READ_U16(domain_pd[0]+off_bytes_0x6041[0]) & 0x037) == 55){
            // flag_init[6] = 1; 
            // }

            for(counter_slave=0;counter_slave<DRIVER_NUMBER;counter_slave++)
            {   if(!flag_init[counter_slave]){
                driver_enable(counter_slave);
                if((EC_READ_U16(domain_pd[counter_slave]+off_bytes_0x6041[counter_slave]) & 0x037) == 55){
                    flag_init[counter_slave] = 1; 
                    EC_WRITE_U8(domain_pd[counter_slave]+off_bytes_0x6060[counter_slave], 0x03);
                }
                break;
                }
                printf("%d ",counter_slave);
            }
            printf("\n");

            for(counter_slave=0;counter_slave<DRIVER_NUMBER;counter_slave++){
                if(flag_init[counter_slave]){
                    flag_init_all=1;
                }
                else{
                    flag_init_all=0;
                    break;
                }
            }

        }
        }
        
        //控制部分
        if(cmdptr->uservalue.Starttime  && !cmdptr->uservalue.Stoptime){
        // printf("%d\n",cmdptr->uservalue.Stage);
        if((time_diff < RUNNING_TIME)&&(flag_init_all==1)&&(flag_stop_all!=1)){
            
            //((flag_init[0]&flag_init[1]&flag_init[2]&flag_init[3]&flag_init[4]&flag_init[5]&flag_init[6]&flag_init[7]&flag_init[8]&flag_init[9]&flag_init[10]&flag_init[11]&flag_init[12]&flag_init[13])==1)
            
            float trans; 
            for(counter_slave=0;counter_slave<DRIVER_NUMBER;counter_slave++)
            {   
                EC_WRITE_U8(domain_pd[counter_slave]+off_bytes_0x6060[counter_slave], 0x03);
            }

            //读取反馈
            reading_driver();
            // reading_ssi();
            reading_current();

            //模式选择
            switch (current_mode) {
                    case MODE_JOINT_TRAJECTORY:
                        // 原有轨迹跟踪代码
                        if (cmdptr->uservalue.Stage == 1) {
                            switch (stage){
                                    case 0: printf("initialization finished, start to reset the position\n");
                                            // scanf("%s",command);
                                            stage = 2; 
                                            counter_loop=0;
                                            // for(counter_slave=0;counter_slave<DRIVER_NUMBER;counter_slave++){
                                            //     Position_Kp[counter_slave]=2;
                                            //     Target_Position[counter_slave]=180/3.1415926536*values[14*2000+counter_slave];
                                            // }
                                            //     Target_Position[4]=Target_Position[4]+Target_Position[3];
                                            //     Target_Position[5]=Target_Position[5]+Target_Position[3];
                                            //     Target_Position[11]=Target_Position[11]+Target_Position[10];
                                            //     Target_Position[12]=Target_Position[12]+Target_Position[10];
                                            break;
                                    case 1: counter_loop++;
                                        // EC_WRITE_S32(domain_pd[13]+off_bytes_0x60ff[13],1000);
                                            // if(counter_loop>5000){
                                            //     counter_loop=0;
                                            //     stage = 2;
                                            // }
                                            // control_pid(0);
                                            for(counter_slave=0;counter_slave<DRIVER_NUMBER;counter_slave++){
                                                control_pid(counter_slave);
                                            }
                                            if((Error[0]<ERROR)&&(Error[1]<ERROR)&&(Error[2]<ERROR)&&(Error[3]<ERROR)&&(Error[4]<ERROR)&&(Error[5]<ERROR)&&(Error[6]<ERROR)&&(Error[7]<ERROR)&&(Error[8]<ERROR)&&(Error[9]<ERROR)&&(Error[10]<ERROR)&&(Error[11]<ERROR)&&(Error[12]<ERROR)&&(Error[13]<ERROR)&&(counter_loop>5000)){
                                                printf("reset finished, start moving\n");
                                                for(counter_slave=0;counter_slave<DRIVER_NUMBER;counter_slave++){
                                                    Position_Kp[counter_slave]=5;

                                                // Position_Kd[counter_slave]=0.3;
                                                }

                                                counter_loop=0;
                                                stage = 2;
                                            }
                                            break;
                                    case 2: 
                                            printf("stage 2: %d\n",counter_loop);
                                            if(cmdptr->uservalue.Stage==1){
                                                counter_loop++;
                                                counter_loop++;
                                                if(counter_loop<9600){
                                            // printf(" target %f %f %f %f %f %f %f\n",values[7*counter_loop],values[7*counter_loop+1],values[7*counter_loop+2]
                                            //        ,values[7*counter_loop+3],values[7*counter_loop+4],values[7*counter_loop+5],values[7*counter_loop+6]);
                                                    //for(counter_slave=0;counter_slave<DRIVER_NUMBER;counter_slave++){

                                                    // Target_Position[counter_slave]=180/3.1415926536*values[14*counter_loop+counter_slave];
                                                    //}

                                                        //举重
                                                        // Target_Position[3]=angle[counter_loop];
                                                        // Target_Position[4]=angle[counter_loop];
                                                        // Target_Position[5]=angle[counter_loop];
                                                        // Target_Position[10]=angle[counter_loop];
                                                        // Target_Position[11]=angle[counter_loop];
                                                        // Target_Position[12]=angle[counter_loop];

                                                        //跑步
                                                        Target_Position[3]=angle1[counter_loop];
                                                        Target_Position[4]=angle1[counter_loop];
                                                        Target_Position[5]=angle1[counter_loop];
                                                        Target_Position[10]=angle1[counter_loop];
                                                        Target_Position[11]=angle1[counter_loop];
                                                        Target_Position[12]=angle1[counter_loop];
                                                        Target_Position[0]=-angle2[counter_loop];
                                                        Target_Position[1]=-angle2[counter_loop];
                                                        Target_Position[2]=-angle2[counter_loop];
                                                        Target_Position[7]=angle2[counter_loop];
                                                        Target_Position[8]=angle2[counter_loop];
                                                        Target_Position[9]=angle2[counter_loop];



                                                        std::cout << angle[counter_loop] << std::endl;
                                                }  
                                                else{
                                                    counter_loop=9600;
                                                    for(counter_slave=0;counter_slave<DRIVER_NUMBER;counter_slave++){
                                                    // Target_Position[counter_slave]=180/3.1415926536*values[14*counter_loop+counter_slave];
                                                    }
                                                }

                                                // Target_Position[4]=Target_Position[4]+Target_Position[3];
                                                // Target_Position[5]=Target_Position[5]+Target_Position[3];
                                                // Target_Position[11]=Target_Position[11]+Target_Position[10];
                                                // Target_Position[12]=Target_Position[12]+Target_Position[10];
                                                // if(counter_loop % 10 == 0){
                                                for(counter_slave=0;counter_slave<DRIVER_NUMBER;counter_slave++){
                                                    control_pid(counter_slave);
                                                }
                                                //}
                                            }
                                            // else if(cmdptr->uservalue.Stage==2){
                                            //     counter_loop+=2;
                                            //     if(counter_loop<10000){
                                            // // printf(" target %f %f %f %f %f %f %f\n",values[7*counter_loop],values[7*counter_loop+1],values[7*counter_loop+2]
                                            // //        ,values[7*counter_loop+3],values[7*counter_loop+4],values[7*counter_loop+5],values[7*counter_loop+6]);
                                            //         for(counter_slave=0;counter_slave<DRIVER_NUMBER;counter_slave++){
                                            //         Target_Position[counter_slave]=180/3.1415926536*values[14*(12000-counter_loop)+counter_slave];
                                            //         }
                                            //     }
                                            //     else if(counter_loop<14000){
                                            //         for(counter_slave=0;counter_slave<DRIVER_NUMBER;counter_slave++){
                                            //         Target_Position[counter_slave]=180/3.1415926536*values[14*(counter_loop-8000)+counter_slave];
                                            //         }
                                            //     }
                                            //     else if(counter_loop<18000){
                                            //         for(counter_slave=0;counter_slave<DRIVER_NUMBER;counter_slave++){
                                            //         Target_Position[counter_slave]=180/3.1415926536*values[14*(20000-counter_loop)+counter_slave];
                                            //         }
                                            //     }
                                            //     else if(counter_loop<22000){
                                            //         for(counter_slave=0;counter_slave<DRIVER_NUMBER;counter_slave++){
                                            //         Target_Position[counter_slave]=180/3.1415926536*values[14*(counter_loop-16000)+counter_slave];
                                            //         }
                                            //     }
                                            //     else{
                                            //         counter_loop=22000;
                                            //         for(counter_slave=0;counter_slave<DRIVER_NUMBER;counter_slave++){
                                            //         Target_Position[counter_slave]=180/3.1415926536*values[14*(counter_loop-16000)+counter_slave];
                                            //         }
                                            //     }

                                            //     Target_Position[4]=Target_Position[4]+Target_Position[3];
                                            //     Target_Position[5]=Target_Position[5]+Target_Position[3];
                                            //     Target_Position[11]=Target_Position[11]+Target_Position[10];
                                            //     Target_Position[12]=Target_Position[12]+Target_Position[10];
                                            //     for(counter_slave=0;counter_slave<DRIVER_NUMBER;counter_slave++){
                                            //         control_pid(counter_slave);
                                            //     }
                                            // }
                                            else if(cmdptr->uservalue.Stage==3){
                                                counter_loop=0;
                                                stage = 3;
                                            }
                                            else
                                            {
                                                // printf("please set the stage correctly\n");
                                            }
                                            // printf("%d\n",counter_loop);
                                                

                                                // if ( counter_loop % 2 == 0) {
                                                //     for(counter_slave=0;counter_slave<7;counter_slave++){
                                                //         control_pid(counter_slave);
                                                //     }
                                                // }
                                                // else{
                                                //     for(counter_slave=7;counter_slave<14;counter_slave++){
                                                //注意腕关节受肘关节自由度影响，需要额外加角度！


                                                //     }
                                                // }
                                            
                                            
                                            // printf("target %f %f %f %f %f %f %f  %f %f %f %f %f %f %f\n", Target_Position[0],Target_Position[1],Target_Position[2],Target_Position[3],Target_Position[4],Target_Position[5],
                                            //     Target_Position[6],Target_Position[7],Target_Position[8],Target_Position[9],Target_Position[10],Target_Position[11],Target_Position[12],Target_Position[13]);
                                            

                                            break;
                                case 3: printf("******end******\n"); 
                                        // EC_WRITE_S32(domain_pd[13]+off_bytes_0x60ff[13],0);
                                        for(counter_slave=0;counter_slave<DRIVER_NUMBER;counter_slave++){
                                            control_pid(counter_slave);
                                        }
                                        stage=4;
                                        break;
                                case 4:                
                                        for(counter_slave=0;counter_slave<DRIVER_NUMBER;counter_slave++)
                                            {   
                                                if(Error[0]<ERROR){
                                                        driver_disable(counter_slave);
                                                        flag_stop[counter_slave]=1;
                                                    }
                                                else{
                                                        control_pid(counter_slave);
                                                    }
                                            }
                                        for(counter_slave=0;counter_slave<DRIVER_NUMBER;counter_slave++){
                                            if(flag_stop[counter_slave]){
                                                flag_stop_all=1;
                                            }
                                            else{
                                                flag_stop_all=0;
                                                break;
                                            }
                                        }
                                default: break;
                                }
                        }
                        break;
                        
                    case MODE_MANUAL_JOINT:
                        // 手动关节控制
                        handle_manual_joint_control();
                        break;
                        
                    case MODE_CARTESIAN_TRAJECTORY:
                        // 末端轨迹运动
                        handle_cartesian_trajectory();
                        break;
                        
                    case MODE_MANUAL_CARTESIAN:
                        // 手动末端控制
                        handle_manual_cartesian_control();
                        break;
                }
            
        // printf("%f\n",Actual_Torque[3]);

        //udp通信
        char sendBuf[1024];
        sprintf(sendBuf, "d:%f,%f,%f,%f,%f,%f,%f,  %f,%f,%f,%f,%f,%f,%f,  %f,%f,%f,%f,%f,%f,%f,  %f,%f,%f,%f,%f,%f,%f,  %f,%f,%f,%f,%f,%f,%f,  %f,%f,%f,%f,%f,%f,%f,  %f,%f,%f,%f,%f,%f,%f,  %f,%f,%f,%f,%f,%f,%f,  %f,%f,%f,%f,%f,%f,%f,  %f,%f,%f,%f,%f,%f,%f\n",
            Actual_Position[0],Actual_Position[1],Actual_Position[2],Actual_Position[3],Actual_Position[4],Actual_Position[5],Actual_Position[6],
            Actual_Position[7],Actual_Position[8],Actual_Position[9],Actual_Position[10],Actual_Position[11],Actual_Position[12],Actual_Position[13],
            Target_Position[0],Target_Position[1],Target_Position[2],Target_Position[3],Target_Position[4],Target_Position[5],Target_Position[6],
            Target_Position[7],Target_Position[8],Target_Position[9],Target_Position[10],Target_Position[11],Target_Position[12],Target_Position[13],
            Target_Velocity[0],Target_Velocity[1],Target_Velocity[2],Target_Velocity[3],Target_Velocity[4],Target_Velocity[5],Target_Velocity[6],
            Target_Velocity[7],Target_Velocity[8],Target_Velocity[9],Target_Velocity[10],Target_Velocity[11],Target_Velocity[12],Target_Velocity[13],
            Actual_Velocity[0],Actual_Velocity[1],Actual_Velocity[2],Actual_Velocity[3],Actual_Velocity[4],Actual_Velocity[5],Actual_Velocity[6],
            Actual_Velocity[7],Actual_Velocity[8],Actual_Velocity[9],Actual_Velocity[10],Actual_Velocity[11],Actual_Velocity[12],Actual_Velocity[13],
            Actual_Torque[0],Actual_Torque[1],Actual_Torque[2],Actual_Torque[3],Actual_Torque[4],Actual_Torque[5],Actual_Torque[6],
            Actual_Torque[7],Actual_Torque[8],Actual_Torque[9],Actual_Torque[10],Actual_Torque[11],Actual_Torque[12],Actual_Torque[13]);
        sendto(fd, sendBuf, strlen(sendBuf) + 1, 0, (struct sockaddr *)&saddr, sizeof(saddr));


            
        }
        else if((time_diff > RUNNING_TIME) && (flag_stop_all==1)){
                // fclose(fp);
                for(counter_slave=0;counter_slave<DRIVER_NUMBER;counter_slave++)
            {
                driver_disable(counter_slave);
                printf("%d stop\n",counter_slave);
            }
        }  
                //频率测试部分
                if(time_test1==0){
                    gettimeofday(&tv2, NULL);
                    time_test1 = (double)( tv2.tv_sec - tv1.tv_sec + (double)(tv2.tv_usec - tv1.tv_usec)/ 1000000);
                }
                else if((time_test1==0)){
                    gettimeofday(&tv2, NULL);
                    time_test2 = (double)( tv2.tv_sec - tv1.tv_sec + (double)(tv2.tv_usec - tv1.tv_usec)/ 1000000);
                }
        }

        if(cmdptr->uservalue.Stoptime){
            for(counter_slave=0;counter_slave<DRIVER_NUMBER;counter_slave++)
            {
                driver_disable(counter_slave);
                printf("%d stop\n",counter_slave);
                flag_stop[counter_slave]=1;
            }
            for(counter_slave=0;counter_slave<DRIVER_NUMBER;counter_slave++){
                        if(flag_stop[counter_slave]){
                            flag_stop_all=1;
                        }
                        else{
                            flag_stop_all=0;
                            break;
                        }
            }
        }

        check_master_state();
        for(counter_slave=0;counter_slave<DOMAIN_NUMBER;counter_slave++){
                check_slave_config_states(counter_slave);
            }
        }
    
    //  send process data
    for(counter_domain=0;counter_domain<DOMAIN_NUMBER;counter_domain++){
        ecrt_domain_queue(domain[counter_domain]);
    }
    ecrt_master_send(master);
}

/****************************************************************************/

void signal_handler(int signum)
{
    switch (signum)
    {
    case SIGALRM:
        sig_alarms++;
        break;
    }
}


void stack_prefault(void)
{
    unsigned char dummy[MAX_SAFE_STACK];

    memset(dummy, 0, MAX_SAFE_STACK);
}
/****************************************************************************/

int main(int argc, char **argv)
{
    printf("test1\n");
    cmdptr = new KeyBoard();

    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd == -1)
    {
        perror("socket");
        exit(-1);
    }
    // 服务器的地址信息
    memset(&saddr,0,sizeof(saddr));
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(9999);
    if(inet_pton(AF_INET, "192.168.7.1", &saddr.sin_addr.s_addr)<0){
        perror("inet_pton");
    };

    int i;
    FILE *file;
    char line[512]; 
    char *token;

    int count = 0;
    for(i=0;i<48000;i++){angle[i]=41-40*cos(3.1415926536*i/1200);
    angle[i]=floor(angle[i] * 1000000.000f + 0.5) / 1000000.000f;
    }

    for(i=0;i<48000;i++){
        if(i<2400){
            angle1[i]=i/2400.0*60;
        }
        else{
            angle1[i]=60;
        }

    }

    for(i=0;i<48000;i++){
        if(i<2400){
            angle2[i]=0;
        }
        else{
            angle2[i]=20*sin(3.1415926536*i/1200*6);
        }

    }

    
    

    // 打开文件
    file = fopen("traj_lift.csv", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // 逐行读取文件
    while (fgets(line, sizeof(line), file)) {
        // 使用strtok分割每行的字符串
        //printf("%s\n",line );
        token = strtok(line, ",");
        while (token != NULL) {
            // 将字符串转换为double
            values[count] = strtod(token, NULL);
            count++;
            token = strtok(NULL, ",");
            // printf("%f\n",count);
            if(count>NUMBER)break;
        }
        if(count>NUMBER)break;
    }
    // int j=0;
 	// printf("%d\n",sizeof(values));
    // for(i=0;i<20;i++){
    //     for(j=0;j<14;j++){
    //         printf("%f  ",values[14*i+j]);
    // }
    //     printf("\n");
    // }
    
    // 关闭文件
    fclose(file);
    printf("read finished\n");
    
    
    struct sigaction sa;
    struct itimerval tv;
    master = ecrt_request_master(0);
    if (!master)
        return -1;
    // 建立一个域，参数是master
    for(counter_domain=0;counter_domain<DOMAIN_NUMBER;counter_domain++){
        domain[counter_domain] = ecrt_master_create_domain(master);
        if (!domain[counter_domain])
            return -1;
    }

        // ⽤宏定义配置master和slave 数字信号输⼊的从站/供应商ID产品代码
    if(config()){
        printf("config fail...\n");
        return -1;
    };

    printf("Activating master...\n");
    if (ecrt_master_activate(master))
    {
        printf("ecrt_master_activate fail...\n");
        return -1;
    }
    for(counter_domain=0;counter_domain<DOMAIN_NUMBER;counter_domain++){
    if (!(domain_pd[counter_domain] = ecrt_domain_data(domain[counter_domain])))
        {
            printf("ecrt_domain%d_data fail...\n",counter_domain);
            return -1;
        }
    }



    for(i=0;i<0xffffff;i++);
    for(i=0;i<0xffffff;i++);
    for(i=0;i<0xffffff;i++);

    butterworthLPF(&filter, cutoffFreq, sampleRate);
    initFilter(&filter);

    sa.sa_handler = signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGALRM, &sa, 0))
    {
        fprintf(stderr, "Failed to install signal handler!\n");
        return -1;
    }

    printf("Starting timer...\n");
    tv.it_interval.tv_sec = 0;
    tv.it_interval.tv_usec = 1000000 / FREQUENCY;//启动后的定时器每隔1ms唤醒一次
    tv.it_value.tv_sec = 0;
    tv.it_value.tv_usec = 2000;//定时器在2s后启动
    if (setitimer(ITIMER_REAL, &tv, NULL))
    {
        fprintf(stderr, "Failed to start timer: %s\n", strerror(errno));
        return 1;
    }

    printf("Started.\n");
    gettimeofday(&tv1, NULL);

    // fp = fopen("tmp.csv", "w+");
    // if (fp == NULL) {
    //     fprintf(stderr, "fopen() failed.\n");
    //     exit(EXIT_FAILURE);
    // }
    // fprintf(fp, "time,target_p,actual_p\n");
    printf("**********press p to enable**********\n");
    printf("**********press a to start**********\n");
    printf("**********press s to stop**********\n");
    while (1)
    {
        pause();
        while (sig_alarms != user_alarms)
        {       
            cyclic_task();
            user_alarms++;
            if(time_diff > RUNNING_TIME || flag_stop_all){
                delete cmdptr;
                system("stty echo");
                printf("over.\n");return 0;}
        }
        
    }
    return 0;
}


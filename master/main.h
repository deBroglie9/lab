#ifndef MAIN_H
#define MAIN_H

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
#include "kinematics.h"
//ethercat
#include "ecrt.h"
#include "EtherCAT.h"
//others
#include "cmdpanel.h"
#include "lpf.h"
#include "poly_traj.h"
#include "teaching.h"
#include <vector>
#include <Eigen/Dense>
#include <Eigen/Geometry>
//control
#include "joint_state.h"
#include "pid_controller.h"
#include "admittance_controller.h"

// #define NUMBER 350014//350014
// 任务周期（以 ns 为单位）
#define MAX_SAFE_STACK (8 * 1024) //保证安全访问而不会出现故障的最大堆栈大小
/****************************************************************************/
// Application parameters
#define FREQUENCY 1000
#define PRIORITY 1
#define MAX_VELOCITY_1 90000
#define MAX_VELOCITY_2 160000
#define MAX_VELOCITY_3 112000
#define PERIODS_PER_SECOND   1000
#define PERIODS_PER_SECOND_L   50
#define INIT_TIME 2
#define ERROR 1
#define RUNNING_TIME 3600/*seconds*/
#define NUMBER 98014//350014

static float Target_Position[DRIVER_NUMBER]={0,0,0,0,0,0,0,0,0,0,0,0,0,0};
static float Actual_Position[DRIVER_NUMBER];  
static float Target_Velocity[DRIVER_NUMBER];
static float Actual_Velocity[DRIVER_NUMBER];
static float Actual_Torque[DRIVER_NUMBER]; 
JointState joint_state[DRIVER_NUMBER];
PIDController pid_controller[DRIVER_NUMBER];

AdmittanceController admittance[2];
std::array<double,6> F_ext[2];     // Fx Fy Fz Mx My Mz
std::array<double,6> F_ext_offset[2]={0,0,0,0,0,0,89.346200,4.520300,205.619800,-0.368600,3.729000,1.232900};
std::array<double,6> x_current[2]; // 当前末端位姿
std::array<double,6> x_target[2];  // 输出目标位姿
float dt = 0.02;
std::vector<std::array<double, 7>> joint_trajectory;

static float max_velocity[DRIVER_NUMBER]={0.2*MAX_VELOCITY_1,0.2*MAX_VELOCITY_1,0.2*MAX_VELOCITY_1,0.2*MAX_VELOCITY_1,0.2*MAX_VELOCITY_2,0.2*MAX_VELOCITY_2,0.2*MAX_VELOCITY_3,
0.2*MAX_VELOCITY_1,0.2*MAX_VELOCITY_1,0.2*MAX_VELOCITY_1,0.2*MAX_VELOCITY_1,0.2*MAX_VELOCITY_2,0.2*MAX_VELOCITY_2,0.2*MAX_VELOCITY_3};

static float offset_ssi[DRIVER_NUMBER];
static float constant_Kp[DRIVER_NUMBER]={40000*19.36/360,40000*19.36/360,40000*19.36/360,40000*19.36/360,4000*6/360,4000*6/360,4000*10/360,
40000*19.36/360,40000*19.36/360,40000*19.36/360,40000*19.36/360,4000*6/360,4000*6/360,4000*10/360};
static float constant_Torque[DRIVER_NUMBER]={40.0,40.0,40.0,40.0,5,5,1,40.0,40.0,40.0,40.0,5,5,1};

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
static unsigned int counter2 = 0;
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
// static unsigned int flag_first[DRIVER_NUMBER];

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
    MODE_MANUAL_CARTESIAN = 3,      // 模式4: 手动控制末端位姿           
    MODE_TEACH_REPLAY = 4              // 模式5: 示教演示
} ControlMode;

static ControlMode current_mode =  MODE_TEACH_REPLAY;

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
//vofa通信输出数据
void UDP_send(){
        char sendBuf[1024];
        sprintf(sendBuf, "d:%f,%f,%f,%f,%f,%f,%f,  %f,%f,%f,%f,%f,%f,%f,  %f,%f,%f,%f,%f,%f,%f,  %f,%f,%f,%f,%f,%f,%f,  %f,%f,%f,%f,%f,%f,%f,  %f,%f,%f,%f,%f,%f,%f,  %f,%f,%f,%f,%f,%f,%f,  %f,%f,%f,%f,%f,%f,%f,  %f,%f,%f,%f,%f,%f,%f,  %f,%f,%f,%f,%f,%f,%f,  %f,%f,%f, %f,%f,%f, %f,%f,%f\n",
            Actual_Position[0],Actual_Position[1],Actual_Position[2],Actual_Position[3],Actual_Position[4],Actual_Position[5],Actual_Position[6],
            Actual_Position[7],Actual_Position[8],Actual_Position[9],Actual_Position[10],Actual_Position[11],Actual_Position[12],Actual_Position[13],
            Target_Position[0],Target_Position[1],Target_Position[2],Target_Position[3],Target_Position[4],Target_Position[5],Target_Position[6],
            Target_Position[7],Target_Position[8],Target_Position[9],Target_Position[10],Target_Position[11],Target_Position[12],Target_Position[13],
            Target_Velocity[0],Target_Velocity[1],Target_Velocity[2],Target_Velocity[3],Target_Velocity[4],Target_Velocity[5],Target_Velocity[6],
            Target_Velocity[7],Target_Velocity[8],Target_Velocity[9],Target_Velocity[10],Target_Velocity[11],Target_Velocity[12],Target_Velocity[13],
            Actual_Velocity[0],Actual_Velocity[1],Actual_Velocity[2],Actual_Velocity[3],Actual_Velocity[4],Actual_Velocity[5],Actual_Velocity[6],
            Actual_Velocity[7],Actual_Velocity[8],Actual_Velocity[9],Actual_Velocity[10],Actual_Velocity[11],Actual_Velocity[12],Actual_Velocity[13],
            Actual_Torque[0],Actual_Torque[1],Actual_Torque[2],Actual_Torque[3],Actual_Torque[4],Actual_Torque[5],Actual_Torque[6],
            Actual_Torque[7],Actual_Torque[8],Actual_Torque[9],Actual_Torque[10],Actual_Torque[11],Actual_Torque[12],Actual_Torque[13],
            F_ext[LEFT_ARM][0],F_ext[LEFT_ARM][1],F_ext[LEFT_ARM][2],
            x_current[LEFT_ARM][0],x_current[LEFT_ARM][1],x_current[LEFT_ARM][2],
            x_target[LEFT_ARM][0],x_target[LEFT_ARM][1],x_target[LEFT_ARM][2]);
        sendto(fd, sendBuf, strlen(sendBuf) + 1, 0, (struct sockaddr *)&saddr, sizeof(saddr));
}

/****************************************************************************/
// 电机使能/去使能
void driver_enable(uint16_t slave_position){
int i=0;
// while( (() & 0x6f) != 0x27){
if ((EC_READ_U16(domain_pd[slave_position]+off_bytes_0x6041[slave_position]) & 0x0250) == 592)
{
    //printf("*********************Servo Power on*********************\n");
    EC_WRITE_U8(domain_pd[slave_position]+off_bytes_0x6060[slave_position], 0x03);//速度模式
    EC_WRITE_U16(domain_pd[slave_position]+off_bytes_0x6040[slave_position], 0x06);
}
if ((EC_READ_U16(domain_pd[slave_position]+off_bytes_0x6041[slave_position]) & 0x031) == 49)
    {
        if ((EC_READ_U16(domain_pd[slave_position]+off_bytes_0x6041[slave_position]) & 0x033) == 51)
        {   //printf("*********************Servo Enable*********************\n");
            EC_WRITE_U16(domain_pd[slave_position]+off_bytes_0x6040[slave_position], 0x0f);

        }
        else
        {   //printf("*********************Servo Waitting*********************\n");
            EC_WRITE_U16(domain_pd[slave_position]+off_bytes_0x6040[slave_position], 0x07);
        }    
    }
}

void driver_disable(uint16_t slave_position)
{
    EC_WRITE_U16(domain_pd[slave_position]+off_bytes_0x6040[slave_position],0x06);
}

/****************************************************************************/
// 反馈读取
void reading_ssi(){
    uint32_t data_pointer[1];
    float angle_all[1];
    float angle;
    unsigned int off_bytes[DRIVER_NUMBER]={off_bytes_ain_1[0],off_bytes_ain_2[0],off_bytes_ain_3[0],off_bytes_ain_4[0],
        off_bytes_ssi_8[0],off_bytes_ain_6[0],off_bytes_ain_7[0],off_bytes_ssi[0],off_bytes_ssi_2[0],off_bytes_ssi_3[0],
        off_bytes_ssi_4[0],off_bytes_ssi_5[0],off_bytes_ssi_6[0],off_bytes_ssi_7[0]};
    //先右臂1-7，再左臂1-7，右臂为ain，左臂为ssi（不代表通讯类型，仅仅做区分） 右臂5为ssi_8（特殊）
    for(counter_slave=0;counter_slave<DRIVER_NUMBER;counter_slave++){
        ssi=EC_READ_U32(domain_pd[DRIVER_NUMBER] + off_bytes[counter_slave]);
        data_pointer[0]=ssi;
        memcpy(angle_all, data_pointer, sizeof(data_pointer));
        Actual_Position[counter_slave]=angle_all[0];   
    }   

    for(counter_slave=0;counter_slave<DRIVER_NUMBER;counter_slave++){
            ssi=EC_READ_U32(domain_pd[counter_slave] + off_bytes_0x606C[counter_slave]);
            Actual_Velocity[counter_slave]=(float)ssi;
    }
    offset_temp[13]=-20;
    //printf("motor position:");
    for(counter_slave=0;counter_slave<DRIVER_NUMBER;counter_slave++){
        
            Actual_Position[counter_slave]=Actual_Position[counter_slave]-offset_temp[counter_slave];
        while( (Actual_Position[counter_slave]>180) || (Actual_Position[counter_slave]<-180)){
            if(Actual_Position[counter_slave]>180){
                Actual_Position[counter_slave]=Actual_Position[counter_slave]-360;
            }
            else if(Actual_Position[counter_slave]<-180){
                Actual_Position[counter_slave]=Actual_Position[counter_slave]+360;
            }
        }
        //printf("%.4f  ",Actual_Position[counter_slave]);  
    }

    //printf("\n");

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

void reading_force_torque(){
    F_ext[LEFT_ARM][0]=(float)EC_READ_S32(domain_pd[DRIVER_NUMBER+ENCODER_NUMBER] + off_bytes_0x4000[0])/10000.0-F_ext_offset[LEFT_ARM][0];
    F_ext[LEFT_ARM][1]=(float)EC_READ_S32(domain_pd[DRIVER_NUMBER+ENCODER_NUMBER] + off_bytes_0x4001[0])/10000.0-F_ext_offset[LEFT_ARM][1];
    F_ext[LEFT_ARM][2]=(float)EC_READ_S32(domain_pd[DRIVER_NUMBER+ENCODER_NUMBER] + off_bytes_0x4002[0])/10000.0-F_ext_offset[LEFT_ARM][2];
    F_ext[LEFT_ARM][3]=(float)EC_READ_S32(domain_pd[DRIVER_NUMBER+ENCODER_NUMBER] + off_bytes_0x4003[0])/10000.0-F_ext_offset[LEFT_ARM][3];
    F_ext[LEFT_ARM][4]=(float)EC_READ_S32(domain_pd[DRIVER_NUMBER+ENCODER_NUMBER] + off_bytes_0x4004[0])/10000.0-F_ext_offset[LEFT_ARM][4];
    F_ext[LEFT_ARM][5]=(float)EC_READ_S32(domain_pd[DRIVER_NUMBER+ENCODER_NUMBER] + off_bytes_0x4005[0])/10000.0-F_ext_offset[LEFT_ARM][5];
    //printf("%f,%f,%f,%f,%f,%f\n",F_ext[LEFT_ARM][0],F_ext[LEFT_ARM][1],F_ext[LEFT_ARM][2],F_ext[LEFT_ARM][3],F_ext[LEFT_ARM][4],F_ext[LEFT_ARM][5]);
}
/****************************************************************************/
// PID控制
void control_pid(uint16_t slave_position)
{
    JointState& joint = joint_state[slave_position];

    // 更新状态
    joint.updateTarget(Target_Position[slave_position]);
    joint.updateActual(Actual_Position[slave_position]);

    float target = joint.getTarget();
    float actual = joint.getActual();

    // PID计算
    float velocity =
        pid_controller[slave_position].update(target,actual);

    velocity *= constant_Kp[slave_position];

    // 速度限制
    if(velocity > max_velocity[slave_position])
        velocity = max_velocity[slave_position];
    else if(velocity < -max_velocity[slave_position])
        velocity = -max_velocity[slave_position];

    Target_Velocity[slave_position] = velocity;

    int velocity_int = (int)velocity;
}

void write_all_velocity_to_ethercat()
{
    for(int i=0;i<DRIVER_NUMBER;i++)
    {
        int velocity_int = (int)Target_Velocity[i];

        EC_WRITE_S32(domain_pd[i] + off_bytes_0x60ff[i],velocity_int);
    }
}

void handle_joint_trajectory(){
    if (cmdptr->uservalue.Stage == 1) {
        switch (stage){
            case 0: printf("initialization finished, start to reset the position\n");
                // scanf("%s",command);
                stage = 1; 
                counter_loop=0;
                // for(counter_slave=0;counter_slave<DRIVER_NUMBER;counter_slave++){
                //     Position_Kp[counter_slave]=2;
                //     Target_Position[counter_slave]=180/3.1415926536*values[14*2000+counter_slave];
                // }
                //     Target_Position[4]=Target_Position[4]+Target_Position[3];
                //     Target_Position[5]=Target_Position[5]+Target_Position[3];
                //     Target_Position[11]=Target_Position[11]+Target_Position[10];
                //     Target_Position[12]=Target_Position[12]+Target_Position[10];

                //举重
                Target_Position[3]=angle[0];
                Target_Position[4]=angle[0];
                Target_Position[5]=angle[0];
                Target_Position[10]=angle[0];
                Target_Position[11]=angle[0];
                Target_Position[12]=angle[0];
                break;
            case 1: 
            {   counter_loop++;
                // EC_WRITE_S32(domain_pd[13]+off_bytes_0x60ff[13],1000);
                // if(counter_loop>5000){
                //     counter_loop=0;
                //     stage = 2;
                // }
                // control_pid(0);
                for(counter_slave=0;counter_slave<DRIVER_NUMBER;counter_slave++){
                    control_pid(counter_slave);
                }

                bool reach_target = true;
                for(int i=0;i<DRIVER_NUMBER;i++)
                {
                    if(fabs(pid_controller[i].getError()) > ERROR)
                    {
                        reach_target = false;
                        break;
                    }
                }

                if(reach_target)
                {
                    // 到达目标
                    printf("reset finished, start moving\n");
                    for(counter_slave=0;counter_slave<DRIVER_NUMBER;counter_slave++){
                    pid_controller[counter_slave].setParam(5,0,0);
                    counter_loop=0;
                    stage = 2;
                    }
                }
            }
                break;
            case 2:
            {
                for(counter_slave=0;counter_slave<DRIVER_NUMBER;counter_slave++){
                    control_pid(counter_slave);
                }
            }
            default: break;
        }
    }
    if (cmdptr->uservalue.Stage == 2) {
        switch (stage){
            case 2: 
                printf("stage 2: %d\n",counter_loop);
                if(cmdptr->uservalue.Stage==2){
                    counter_loop++;
                    if(counter_loop<18000){
                        //for(counter_slave=0;counter_slave<DRIVER_NUMBER;counter_slave++){
                        // Target_Position[counter_slave]=180/3.1415926536*values[14*counter_loop+counter_slave];
                        //}

                        //举重
                        Target_Position[3]=angle[counter_loop];
                        Target_Position[4]=angle[counter_loop];
                        Target_Position[5]=angle[counter_loop];
                        Target_Position[10]=angle[counter_loop];
                        Target_Position[11]=angle[counter_loop];
                        Target_Position[12]=angle[counter_loop];

                        //跑步
                        // Target_Position[3]=angle1[counter_loop];
                        // Target_Position[4]=angle1[counter_loop];
                        // Target_Position[5]=angle1[counter_loop];
                        // Target_Position[10]=angle1[counter_loop];
                        // Target_Position[11]=angle1[counter_loop];
                        // Target_Position[12]=angle1[counter_loop];
                        // Target_Position[0]=-angle2[counter_loop];
                        // Target_Position[1]=-angle2[counter_loop];
                        // Target_Position[2]=-angle2[counter_loop];
                        // Target_Position[7]=angle2[counter_loop];
                        // Target_Position[8]=angle2[counter_loop];
                        // Target_Position[9]=angle2[counter_loop];



                        std::cout << angle[counter_loop] << std::endl;
                    }  
                    else{
                        counter_loop=18000;
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
                            if(fabs(pid_controller[counter_slave].getError())<ERROR){
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

}
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

static double t_start=0;
static int count=0;
static int flag_running=0;



// std::vector<double> current_pose(6);

// current_pose.head<3>() = pos;
// current_pose.tail<3>() = rotvec;

// 末端轨迹运动处理函数
void handle_cartesian_trajectory() {
    if(counter2){
    counter2--;
    }
    else{
        counter2 = PERIODS_PER_SECOND/PERIODS_PER_SECOND_L-1;
        double time1;
        static double t = 0;
        char input;
        //offset_temp[11]=-10;
        if(cmdptr->uservalue.state==0){
            for(counter_slave=0;counter_slave<7;counter_slave++){
                pid_controller[counter_slave].setParam(1,0,0);
            }
        }
        else{
            for(counter_slave=0;counter_slave<7;counter_slave++){
                pid_controller[counter_slave].setParam(1,0,0);
            }
        }
        //末端导纳控制
        std::array<double,6> x_offset;
        std::array<double,6> x_output;
        Eigen::Matrix3d R_base2end;
        Eigen::Matrix3d R_end2tool;
        Eigen::Matrix3d R_base2tool;
        Eigen::Matrix3d R_90;
        Eigen::Matrix3d R_trans;
        Eigen::Vector3d Posture;
        Eigen::Vector3d Position;
        double Px=Position[0];
        double Py=Position[1];
        double Pz=Position[2];
        double c[7];
        double flag=0;
        double phi=0;

        x_offset={-0.160000,-0.277128,0.235000,-1.570796,2.094395,0.000000};//90 degree
        //x_offset={0,0,0,0,0,0};//90 degree
        double c_l[7]={Actual_Position[7]*3.1415926535/180,Actual_Position[8]*3.1415926535/180,Actual_Position[9]*3.1415926535/180,Actual_Position[10]*3.1415926535/180,Actual_Position[11]*3.1415926535/180,Actual_Position[12]*3.1415926535/180,Actual_Position[13]*3.1415926535/180};
        //double c_l[7]={0,0,0,3.1415926535/2,0,0,0};
        double c_r[7]={Actual_Position[0],Actual_Position[1],Actual_Position[2],Actual_Position[3],Actual_Position[4],Actual_Position[5],Actual_Position[6]};
        double T_l[4][4];
        double T_r[4][4];

        FK(LEFT_ARM,c_l,T_l);
        FK(RIGHT_ARM,c_r,T_r);
        
        //printf("%f,%f,%f,%f,%f,%f,%f\n",c_l[0],c_l[1],c_l[2],c_l[3],c_l[4],c_l[5],c_l[6]);
        //printf("%f,%f,%f\n %f,%f,%f\n %f,%f,%f\n",T_l[0][0],T_l[0][1],T_l[0][2],T_l[1][0],T_l[1][1],T_l[1][2],T_l[2][0],T_l[2][1],T_l[2][2]);
        
        R_base2end<<T_l[0][0],T_l[0][1],T_l[0][2],T_l[1][0],T_l[1][1],T_l[1][2],T_l[2][0],T_l[2][1],T_l[2][2];
        R_end2tool<<0,0,1,sin(M_PI/6),cos(M_PI/6),0,-cos(M_PI/6),sin(M_PI/6),0;
        R_base2tool << R_base2end * R_end2tool;//base to tool
        R_90<<0,-1,0,1,0,0,0,0,1;
        
        
        //coordinate of tool
        Position<<T_l[0][3],T_l[1][3],T_l[2][3];
        Position=R_base2tool.inverse()*Position;
        Posture=axis_trans(R_base2tool);

        //printf("%f,%f,%f\n",Position(0),Position(1),Position(2));
        //printf("%f,%f,%f\n",Posture(0),Posture(1),Posture(2));

        //位置导纳
        for(int i = 0; i < 3; i ++)
        {
            x_current[1][i] = Position(i); 
            x_current[1][i+3] = Posture(i); 
            
        }
        printf("current %f,%f,%f,%f,%f,%f\n",x_current[1][0],x_current[1][1],x_current[1][2],x_current[1][3],x_current[1][4],x_current[1][5]);
        printf("F:%f,%f,%f,%f,%f,%f\n",F_ext[1][0],F_ext[1][1],F_ext[1][2],F_ext[1][3],F_ext[1][4],F_ext[1][5]);
        admittance[1].update(F_ext[1], x_current[1], x_target[1], dt); 
        


        //coordinate of base
        printf("output:");
        for (int i = 0; i < 6; i ++){
            x_output[i] = x_target[1][i];
            printf("%f ",x_output[i]);
        }
        printf("\n");
        x_output[3]=0;x_output[4]=0;x_output[5]=0;
        Posture<<x_output[3],x_output[4],x_output[5];
        Position<<x_output[0],x_output[1],x_output[2];
        Position=R_base2tool*Position;
        R_trans<<R_90;
        double R[3][3]={R_trans(0,0),R_trans(0,1),R_trans(0,2),R_trans(1,0),R_trans(1,1),R_trans(1,2),R_trans(2,0),R_trans(2,1),R_trans(2,2)};

        Px=Position[0];
        Py=Position[1];
        Pz=Position[2];
        printf("INPUT\n %f,%f,%f\n",Px,Py,Pz);
        IK(LEFT_ARM, R, phi,  Px,  Py,  Pz,  c, &flag);
        if(flag == 1){
            //printf("%f,%f,%f,%f,%f,%f,%f\n",c[0],c[1],c[2],c[3],c[4],c[5],c[6]);
        }
        else{
            printf("no match angles\n");
        }
        Target_Position[7]=180/3.1415926535*c[0];
        Target_Position[8]=180/3.1415926535*c[1];
        Target_Position[9]=180/3.1415926535*c[2];
        Target_Position[10]=180/3.1415926535*c[3];
        Target_Position[11]=180/3.1415926535*c[4];
        Target_Position[12]=180/3.1415926535*c[5];
        Target_Position[13]=180/3.1415926535*c[6];

        //重复定位精度测试
        // printf("程序将重复执行函数30次，每次执行前需要按任意键继续...\n");
        // printf("按Ctrl+C可以提前终止程序\n\n");
        
        // //计算时间测试
        // if(count>cmdptr->uservalue.state){
        //     printf("press q to continue NO.%d loop\n",count);
        //     flag_running=0;
        // }
        // else if(!flag_running){
        //     gettimeofday(&tv2, NULL);
        //     time_diff = (double)( tv2.tv_sec - tv1.tv_sec + (double)(tv2.tv_usec - tv1.tv_usec)/ 1000000);
        //     t_start=time_diff;
        //     flag_running=1;
        // }
        // else{
        //     gettimeofday(&tv2, NULL);
        //     time_diff = (double)( tv2.tv_sec - tv1.tv_sec + (double)(tv2.tv_usec - tv1.tv_usec)/ 1000000);
        //     time1=time_diff;
        //     t=time1-t_start;
        //     if(count % 2 == 0){
        //         // printf("set\n");
        //         double phi=0*3.1415926535/180;
        //         double Px=0.320;
        //         double Py=0.235;
        //         double Pz=0;
        //         double flag=0;
        //         // wrist roll
        //         // double R[3][3] = { 0,     -1,      0,
        //         //                   cos(20*3.1415926535/180*t/4),    0,    -sin(20*3.1415926535/180*t/4),
        //         //                   sin(20*3.1415926535/180*t/4),    0,    cos(20*3.1415926535/180*t/4)};
        //         // wrist pitch
        //         // double R[3][3] = {-sin(-45*3.1415926535/180*t/4),   -cos(-45*3.1415926535/180*t/4),    0,
        //         //                   cos(-45*3.1415926535/180*t/4),    -sin(-45*3.1415926535/180*t/4),    0,
        //         //                   0,    0,    1};
        //         // wrist yaw
        //         // double c[7]={0,0,0,0,0,0,0};
        //         // c[3]=3.1415926535/2;
        //         // c[6]=3.1415926535 -3.1415926535/2 - 3.1415926535/6*t/4;
                
        //         // elbow
        //         // phi=0;
        //         // Px=0.3199+0.235*cos((85*t/4+5)*3.1415926535/180);
        //         // Py=0.235*sin((85*t/4+5)*3.1415926535/180);
        //         // Pz=0;
        //         // double R[3][3] ={cos((85*t/4+5)*3.1415926535/180),    -sin((85*t/4+5)*3.1415926535/180),    0,
        //         //                 sin((85*t/4+5)*3.1415926535/180),    cos((85*t/4+5)*3.1415926535/180),    0,
        //         //                 0,    0,    1};

        //         //shoulder pitch
        //         double c[7]={0,0,0,0,0,0,0};
        //         c[0]= 3.1415926535/6*t/4;
        //         c[1]= 3.1415926535/6*t/4;
        //         c[2]= 3.1415926535/6*t/4;
        //         // shoulder yaw
        //         // phi=-30*t/4*3.1415926535/180+10*3.1415926535/180;
        //         // Px=0.320;
        //         // Py=0.235*cos(-30*t/4*3.1415926535/180+10*3.1415926535/180);
        //         // Pz=0.235*sin(-30*t/4*3.1415926535/180+10*3.1415926535/180);
        
        //         // double R[3][3] = { 0,     -1,      0,
        //         //                   cos(-30*t/4*3.1415926535/180+10*3.1415926535/180),    0,    -sin(-30*t/4*3.1415926535/180+10*3.1415926535/180),
        //         //                   sin(-30*t/4*3.1415926535/180+10*3.1415926535/180),    0,    cos(-30*t/4*3.1415926535/180+10*3.1415926535/180)};
        //         // shoulder roll
        //         // phi=0*3.1415926535/180;
        //         // Px=0.5549*cos(10*3.1415926535/180*t/4+10*3.1415926535/180);
        //         // Py=0;
        //         // Pz=0.5549*sin(10*3.1415926535/180*t/4+10*3.1415926535/180);
        
        //         // double R[3][3] = {cos(10*3.1415926535/180*t/4+10*3.1415926535/180),    0,    -sin(10*3.1415926535/180*t/4+10*3.1415926535/180),
        //         //                   0,    1,    0,
        //         //                   sin(10*3.1415926535/180*t/4+10*3.1415926535/180),    0,    cos(10*3.1415926535/180*t/4+10*3.1415926535/180)};

        //         // double c[7];

        //         // IK(RIGHT_ARM, R, phi, Px, Py, Pz, c, &flag);



        //         printf("time: %.4f s, IK flag: %.0f Joint Angles (degrees): ", t, flag);
                
        //         for (counter_slave = 0; counter_slave < 7; counter_slave++) {
        //             Target_Position[counter_slave] = c[counter_slave] * 180.0 / 3.1415926535;
        //             printf("%.4f ",Target_Position[counter_slave]);
        //         }
        //         Target_Position[4]=Target_Position[4]+Target_Position[3];
        //         Target_Position[5]=Target_Position[5]+Target_Position[3];
        //         printf("\n");
        //     }
        //     else{
        //         // printf("reset\n");
        //         double phi=0*3.1415926535/180;
        //         double Px=0.325;
        //         double Py=0.230;
        //         double Pz=0;
        //         double flag=0;
        //         // wrist roll
        //         // double R[3][3] = { 0,     -1,      0,
        //         //                   cos(20*3.1415926535/180*(4.0-t)/4),    0,    -sin(20*3.1415926535/180*(4.0-t)/4),
        //         //                   sin(20*3.1415926535/180*(4.0-t)/4),    0,    cos(20*3.1415926535/180*(4.0-t)/4)};
        //         // wrist pitch
        //         // double R[3][3] = {-sin(-45*3.1415926535/180*(4.0-t)/4),   -cos(-45*3.1415926535/180*(4.0-t)/4),    0,
        //         //                   cos(-45*3.1415926535/180*(4.0-t)/4),    -sin(-45*3.1415926535/180*(4.0-t)/4),    0,
        //         //                   0,    0,    1};                              
        //         // wrist yaw
        //         // double c[7]={0,0,0,0,0,0,0};
        //         // c[3]=3.1415926535/2;
        //         // c[6]=3.1415926535 -3.1415926535/2- 3.1415926535/6*(4.0-t)/4;

        //         // elbow
        //         // phi=0;
        //         // Px=0.3199+0.235*cos((85*(4.0-t)/4+5)*3.1415926535/180);
        //         // Py=0.235*sin((85*(4.0-t)/4+5)*3.1415926535/180);
        //         // Pz=0;
        //         // double R[3][3] ={cos((85*(4.0-t)/4+5)*3.1415926535/180),    -sin((85*(4.0-t)/4+5)*3.1415926535/180),    0,
        //         //                 sin((85*(4.0-t)/4+5)*3.1415926535/180),    cos((85*(4.0-t)/4+5)*3.1415926535/180),    0,
        //         //                 0,    0,    1};

        //         //shoulder pitch
        //         double c[7]={0,0,0,0,0,0,0};
        //         c[0]= 3.1415926535/6*(4.0-t)/4;
        //         c[1]= 3.1415926535/6*(4.0-t)/4;
        //         c[2]= 3.1415926535/6*(4.0-t)/4;
        //         // shoulder yaw
        //         // phi=-30*(4-t)/4*3.1415926535/180+10*3.1415926535/180;
        //         // Px=0.320;
        //         // Py=0.235*cos(-30*(4-t)/4*3.1415926535/180+10*3.1415926535/180);
        //         // Pz=0.235*sin(-30*(4-t)/4*3.1415926535/180+10*3.1415926535/180);
        
        //         // double R[3][3] = { 0,     -1,      0,
        //         //                   cos(-30*(4-t)/4*3.1415926535/180+10*3.1415926535/180),    0,    -sin(-30*(4-t)/4*3.1415926535/180+10*3.1415926535/180),
        //         //                   sin(-30*(4-t)/4*3.1415926535/180+10*3.1415926535/180),    0,    cos(-30*(4-t)/4*3.1415926535/180+10*3.1415926535/180)};
        //         // shoulder roll
        //         // phi=0*3.1415926535/180;
        //         // Px=0.5549*cos(10*3.1415926535/180*(4-t)/4+10*3.1415926535/180);
        //         // Py=0;
        //         // Pz=0.5549*sin(10*3.1415926535/180*(4-t)/4+10*3.1415926535/180);
        
        //         // double R[3][3] = {cos(10*3.1415926535/180*(4-t)/4+10*3.1415926535/180),    0,    -sin(10*3.1415926535/180*(4-t)/4+10*3.1415926535/180),
        //         //                   0,    1,    0,
        //         //                   sin(10*3.1415926535/180*(4-t)/4+10*3.1415926535/180),    0,    cos(10*3.1415926535/180*(4-t)/4+10*3.1415926535/180)};

        //         // double c[7];

        //         // IK(RIGHT_ARM, R, phi, Px, Py, Pz, c, &flag);



        //         printf("time: %.4f s, IK flag: %.0f Joint Angles (degrees): ", t, flag);
                
        //         for (counter_slave = 0; counter_slave < 7; counter_slave++) {
        //             Target_Position[counter_slave] = c[counter_slave] * 180.0 / 3.1415926535;
        //             printf("%.4f ",Target_Position[counter_slave]);
        //         }
        //         Target_Position[4]=Target_Position[4]+Target_Position[3];
        //         Target_Position[5]=Target_Position[5]+Target_Position[3];
        //         printf("\n");
        //     }

        //     //running code//
        //     // printf("running\n");
        //     if(t>4){
        //         count++;
        //         flag_running=0;
        //         printf("finished\n");
        //     }
        // }
    }

        for (counter_slave = 0; counter_slave < DRIVER_NUMBER; counter_slave++) {
            control_pid(counter_slave);
        // printf("pid %d\n",counter_slave);
        }
}


// 手动末端控制处理函数
void handle_manual_cartesian_control(){
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
    // if (calculate_inverse_kinematics(target_position_xyz, target_rotation, ik_result)) {
    //     for (int i = 0; i < DRIVER_NUMBER; i++) {
    //         Target_Position[i] = ik_result[i] * 180.0 / M_PI;
    //     }
    // }
    
    printf("末端位置: X=%.3f, Y=%.3f, Z=%.3f\n", 
           target_position_xyz[0], target_position_xyz[1], target_position_xyz[2]);
}

//示教读取
void teaching_record(){
    joint_trajectory.push_back({ Actual_Position[0], Actual_Position[1],
                                Actual_Position[2], Actual_Position[3],
                                Actual_Position[4], Actual_Position[5],
                                Actual_Position[6], });
    //printf("%d\n",joint_trajectory.size());
}

//示教复现
void replay_record(){
    // counter_loop=0;
    if(counter_loop<=joint_trajectory.size()){
        for(counter_slave=0;counter_slave<7;counter_slave++){
            Target_Position[counter_slave]=joint_trajectory[counter_loop][counter_slave];
        }
        printf("counter:%d %f, %f, %f, %f, %f, %f, %f\n",counter_loop,Target_Position[0],Target_Position[1],Target_Position[2],
                                                    Target_Position[3],Target_Position[4],
                                                    Target_Position[5],Target_Position[6]);
        counter_loop++;
    }
    else{
        printf("replay complete\n");
    }

    for(counter_slave=0;counter_slave<7;counter_slave++){
        control_pid(counter_slave);
    }
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

#endif
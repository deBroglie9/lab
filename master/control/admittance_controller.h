#ifndef ADMITTANCE_CONTROLLER_H
#define ADMITTANCE_CONTROLLER_H

#include <array>



class AdmittanceController
{
public:

    AdmittanceController()
    {
        for(int i=0;i<6;i++)
        {
            M[i] = 500.0;
            B[i] = 50.0;
            K[i] = 0.0;   // 纯导纳可设为0

            x[i] = 0.0;
            dx[i] = 0.0;
            ddx[i] = 0.0;
        }
    }

    // 设置参数
    void setParam(int i, double m, double b, double k)
    {
        M[i] = m;
        B[i] = b;
        K[i] = k;
    }

    // ===========================
    // 核心函数
    // ===========================
    // 输入：外力 + 当前位姿
    // 输出：修正后的目标位姿
    // ===========================
    void update(
        const std::array<double,6>& F_ext,
        const std::array<double,6>& x_current,
        std::array<double,6>& x_target,
        double dt)
    {
        for(int i=0;i<3;i++)
        {
            // 导纳动力学
            //printf("F:%f,%f,%f,%f,%f,%f\n",x_current[0],x_current[1],x_current[2],x_current[3],x_current[4],x_current[5]);
            ddx[i] = (F_ext[i] - B[i]*(dx[i]-dx_d[i]) - K[i]*(x_current[i]-x_d[i])) / M[i];
            //printf("ddx: %f\n",ddx[i]);
            dx[i] += ddx[i] * dt;
            //printf("dx: %f\n",dx[i]);
            x[i] = x_current[i] + dx[i] * dt;
            //printf("x: %f\n",x[i]);
            // 输出目标位姿
            x_target[i] = x[i];
        }
        x_target[3]=0;
        x_target[4]=0;
        x_target[5]=0;

        //边界限制
        d_x= x_target[0]-offset_x;
        d_y= x_target[1]-offset_y;
        d_z= x_target[2]-offset_z;
        distance= sqrt( d_x*d_x + d_y*d_y + d_z*d_z);
        //printf("dx: %f  dy: %f  dz: %f  d: %f\n",d_x,d_y,d_z,distance);
        if(distance > buffer_start){
            if(distance >= distance_limit){
                // 超出硬边界：限制位置并完全停止
                d_x=d_x*distance_limit/distance;
                x[0]=d_x+offset_x;
                dx[0]=0;
                ddx[0]=0;

                d_y=d_y*distance_limit/distance;
                x[1]=d_y+offset_y;
                dx[1]=0;
                ddx[1]=0;

                d_z=d_z*distance_limit/distance;
                x[2]=d_z+offset_z;
                dx[2]=0;
                ddx[2]=0;

                x_target[0]=x[0];
                x_target[1]=x[1];
                x_target[2]=x[2];
                distance = distance_limit;
                //printf("dx: %f  dy: %f  dz: %f  d: %f\n",d_x,d_y,d_z,distance);
            }
            else
            {
            // 在缓冲区内：线性衰减速度，不直接限制位置
            double t = (distance - buffer_start) / (distance_limit - buffer_start);
            double damping = 1.0 - t;   // 从1线性衰减到0
            dx[0] *= damping;
            dx[1] *= damping;
            dx[2] *= damping;
            }


        }
        printf("pos: %.3f,%.3f,%.3f | dist: %.3f | vel: %.3f,%.3f,%.3f\n", 
        x_target[0], x_target[1], x_target[2], distance, dx[0], dx[1], dx[2]);
    }

    void reset()
    {
        for(int i=0;i<6;i++)
        {
            x[i] = 0;
            dx[i] = 0;
            ddx[i] = 0;
        }
    }

private:

    double M[6];   // 虚拟质量
    double B[6];   // 阻尼
    double K[6];   // 刚度

    double x[6];   // 位移
    double dx[6];  // 速度
    double ddx[6]; // 加速度

    double x_d[6]={-0.160000,-0.277128,0.235000};   // 位移
    double dx_d[6]={0,0,0,0,0,0};  // 速度

    double d_x,d_y,d_z;
    double offset_x=-0.160000;
    double offset_y=-0.277128;
    double offset_z=0.235000;
    double distance;
    double distance_limit=0.08;
    double buffer_ratio = 0.9;            // 缓冲区比例（距离限制的90%开始减速）
    double buffer_start = distance_limit * buffer_ratio;
};

#endif
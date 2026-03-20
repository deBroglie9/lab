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
            M[i] = 1.0;
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
        for(int i=0;i<6;i++)
        {
            // 导纳动力学
            ddx[i] = (F_ext[i] - B[i]*dx[i] - K[i]*x[i]) / M[i];

            dx[i] += ddx[i] * dt;
            x[i]  += dx[i] * dt;

            // 输出目标位姿
            x_target[i] = x_current[i] + x[i];
        }
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
};

#endif
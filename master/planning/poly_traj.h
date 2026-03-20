#ifndef POLY_TRAJ_H_
#define POLY_TRAJ_H_
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// 轨迹点结构体
typedef struct {
    double position;    // 位置
    double velocity;    // 速度
    double acceleration; // 加速度
} TrajectoryPoint;

// 五次多项式系数结构体
typedef struct {
    double a0, a1, a2, a3, a4, a5;
} QuinticCoefficients;

// 计算五次多项式系数
QuinticCoefficients calculate_quintic_coefficients(double q0, double qf, double v0, double vf, double a0, double af, double tf) {
    QuinticCoefficients coeff;
    
    if (tf <= 0) {
        printf("错误：时间必须大于0\n");
        return coeff;
    }
    
    // 计算五次多项式系数
    coeff.a0 = q0;
    coeff.a1 = v0;
    coeff.a2 = a0 / 2.0;
    
    double tf2 = tf * tf;
    double tf3 = tf2 * tf;
    double tf4 = tf3 * tf;
    double tf5 = tf4 * tf;
    
    // 构建矩阵方程的解
    double h = qf - q0;
    
    coeff.a3 = (20 * h - (8 * vf + 12 * v0) * tf - (3 * a0 - af) * tf2) / (2 * tf3);
    coeff.a4 = (-30 * h + (14 * vf + 16 * v0) * tf + (3 * a0 - 2 * af) * tf2) / (2 * tf4);
    coeff.a5 = (12 * h - 6 * (vf + v0) * tf + (af - a0) * tf2) / (2 * tf5);
    
    return coeff;
}

// 计算五次多项式在时间t的值
TrajectoryPoint evaluate_quintic_polynomial(QuinticCoefficients coeff, double t) {
    TrajectoryPoint point;
    
    // 位置：s(t) = a0 + a1*t + a2*t^2 + a3*t^3 + a4*t^4 + a5*t^5
    point.position = coeff.a0 + coeff.a1 * t + coeff.a2 * t * t + 
                    coeff.a3 * t * t * t + coeff.a4 * t * t * t * t + 
                    coeff.a5 * t * t * t * t * t;
    
    // 速度：v(t) = a1 + 2*a2*t + 3*a3*t^2 + 4*a4*t^3 + 5*a5*t^4
    point.velocity = coeff.a1 + 2 * coeff.a2 * t + 3 * coeff.a3 * t * t + 
                    4 * coeff.a4 * t * t * t + 5 * coeff.a5 * t * t * t * t;
    
    // 加速度：a(t) = 2*a2 + 6*a3*t + 12*a4*t^2 + 20*a5*t^3
    point.acceleration = 2 * coeff.a2 + 6 * coeff.a3 * t + 
                        12 * coeff.a4 * t * t + 20 * coeff.a5 * t * t * t;
    
    return point;
}

// 生成轨迹点
void generate_trajectory(QuinticCoefficients coeff, double tf, int num_points) {
    printf("时间\t位置\t速度\t加速度\n");
    printf("----\t----\t----\t----\n");
    
    for (int i = 0; i <= num_points; i++) {
        double t = (double)i * tf / num_points;
        TrajectoryPoint point = evaluate_quintic_polynomial(coeff, t);
        
        printf("%.2f\t%.4f\t%.4f\t%.4f\n", 
               t, point.position, point.velocity, point.acceleration);
    }
}

// 验证边界条件
void verify_boundary_conditions(QuinticCoefficients coeff, 
                               double q0, double qf, double v0, double vf, 
                               double a0, double af, double tf) {
    
    TrajectoryPoint start = evaluate_quintic_polynomial(coeff, 0);
    TrajectoryPoint end = evaluate_quintic_polynomial(coeff, tf);
    
    printf("\n边界条件验证:\n");
    printf("起始点 - 位置: 期望 %.2f, 实际 %.2f, 误差: %.6f\n", 
           q0, start.position, fabs(q0 - start.position));
    printf("起始点 - 速度: 期望 %.2f, 实际 %.2f, 误差: %.6f\n", 
           v0, start.velocity, fabs(v0 - start.velocity));
    printf("起始点 - 加速度: 期望 %.2f, 实际 %.2f, 误差: %.6f\n", 
           a0, start.acceleration, fabs(a0 - start.acceleration));
    
    printf("结束点 - 位置: 期望 %.2f, 实际 %.2f, 误差: %.6f\n", 
           qf, end.position, fabs(qf - end.position));
    printf("结束点 - 速度: 期望 %.2f, 实际 %.2f, 误差: %.6f\n", 
           vf, end.velocity, fabs(vf - end.velocity));
    printf("结束点 - 加速度: 期望 %.2f, 实际 %.2f, 误差: %.6f\n", 
           af, end.acceleration, fabs(af - end.acceleration));
}

// int main() {
//     // 轨迹参数
//     double q0 = 0.0;      // 起始位置
//     double qf = 10.0;     // 结束位置
//     double v0 = 0.0;      // 起始速度
//     double vf = 0.0;      // 结束速度
//     double a0 = 0.0;      // 起始加速度
//     double af = 0.0;      // 结束加速度
//     double tf = 5.0;      // 总时间
//     int num_points = 20;  // 轨迹点数
    
//     printf("五次多项式轨迹规划示例\n");
//     printf("====================\n");
//     printf("起始位置: %.2f\n", q0);
//     printf("结束位置: %.2f\n", qf);
//     printf("起始速度: %.2f\n", v0);
//     printf("结束速度: %.2f\n", vf);
//     printf("起始加速度: %.2f\n", a0);
//     printf("结束加速度: %.2f\n", af);
//     printf("总时间: %.2f\n", tf);
    
//     // 计算五次多项式系数
//     QuinticCoefficients coeff = calculate_quintic_coefficients(q0, qf, v0, vf, a0, af, tf);
    
//     printf("\n五次多项式系数:\n");
//     printf("a0 = %.6f\n", coeff.a0);
//     printf("a1 = %.6f\n", coeff.a1);
//     printf("a2 = %.6f\n", coeff.a2);
//     printf("a3 = %.6f\n", coeff.a3);
//     printf("a4 = %.6f\n", coeff.a4);
//     printf("a5 = %.6f\n", coeff.a5);
    
//     // 生成轨迹
//     printf("\n轨迹数据:\n");
//     generate_trajectory(coeff, tf, num_points);
    
//     // 验证边界条件
//     verify_boundary_conditions(coeff, q0, qf, v0, vf, a0, af, tf);
    
//     // 示例2：非零边界条件
//     printf("\n\n示例2：非零边界条件\n");
//     printf("====================\n");
    
//     q0 = 2.0;
//     qf = 8.0;
//     v0 = 1.0;
//     vf = -1.0;
//     a0 = 0.5;
//     af = -0.5;
//     tf = 4.0;
    
//     printf("起始位置: %.2f\n", q0);
//     printf("结束位置: %.2f\n", qf);
//     printf("起始速度: %.2f\n", v0);
//     printf("结束速度: %.2f\n", vf);
//     printf("起始加速度: %.2f\n", a0);
//     printf("结束加速度: %.2f\n", af);
//     printf("总时间: %.2f\n", tf);
    
//     coeff = calculate_quintic_coefficients(q0, qf, v0, vf, a0, af, tf);
    
//     printf("\n五次多项式系数:\n");
//     printf("a0 = %.6f\n", coeff.a0);
//     printf("a1 = %.6f\n", coeff.a1);
//     printf("a2 = %.6f\n", coeff.a2);
//     printf("a3 = %.6f\n", coeff.a3);
//     printf("a4 = %.6f\n", coeff.a4);
//     printf("a5 = %.6f\n", coeff.a5);
    
//     generate_trajectory(coeff, tf, num_points);
//     verify_boundary_conditions(coeff, q0, qf, v0, vf, a0, af, tf);
    
//     return 0;
// }

#endif
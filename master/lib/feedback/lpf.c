#include "lpf.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// 滤波器结构体
// typedef struct {
//     float a0, a1, a2; // 分母系数
//     float b0, b1, b2; // 分子系数
//     float x1, x2;     // 输入延迟线
//     float y1, y2;     // 输出延迟线
// } BiquadFilter;

// 计算巴特沃斯滤波器系数
void butterworthLPF(BiquadFilter* filter, float cutoffFreq, float sampleRate) {
    float omega = 2.0 * M_PI * cutoffFreq / sampleRate;
    float sinOmega = sin(omega);
    float cosOmega = cos(omega);
    float alpha = sinOmega / (2.0 * 0.7071); // 0.7071 = 1/sqrt(2) (Butterworth Q值)
    
    float b0 = (1 - cosOmega) / 2;
    float b1 = 1 - cosOmega;
    float b2 = (1 - cosOmega) / 2;
    float a0 = 1 + alpha;
    float a1 = -2 * cosOmega;
    float a2 = 1 - alpha;
    
    // 归一化系数
    filter->b0 = b0 / a0;
    filter->b1 = b1 / a0;
    filter->b2 = b2 / a0;
    filter->a1 = a1 / a0;
    filter->a2 = a2 / a0;
    filter->a0 = 1.0; // 归一化后a0总是1
}

// 初始化滤波器
void initFilter(BiquadFilter* filter) {
    filter->x1 = 0;
    filter->x2 = 0;
    filter->y1 = 0;
    filter->y2 = 0;
}

// 在线滤波处理函数
float processSample(BiquadFilter* filter, float input) {
    // 计算输出
    float output = filter->b0 * input + filter->b1 * filter->x1 + filter->b2 * filter->x2
                 - filter->a1 * filter->y1 - filter->a2 * filter->y2;
    
    // 更新延迟线
    filter->x2 = filter->x1;
    filter->x1 = input;
    filter->y2 = filter->y1;
    filter->y1 = output;
    
    return output;
}

// 读取CSV指定位置的float数据
// filename: 文件名
// start_row: 起始行（从1开始）
// col: 列号（从1开始，A=1,B=2,...,D=4）
// 返回值：读取到的float数据（失败返回0.0）
float read_csv_float(const char* filename, int start_row, int col) {
    FILE* fp = fopen(filename, "r");
    if (!fp) return 0.0f;
    char line[1024];
    int row = 0;
    float value = 0.0f;
    while (fgets(line, sizeof(line), fp)) {
        row++;
        if (row < start_row) continue;
        // 解析本行的第col列
        int current_col = 1;
        char* token = strtok(line, ",");
        while (token) {
            if (current_col == col) {
                value = (float)atof(token);
                fclose(fp);
                return value;
            }
            token = strtok(NULL, ",");
            current_col++;
        }
        break; // 只读取start_row这一行
    }
    fclose(fp);
    return 0.0f;
}

// 示例使用
// int main() {    
    
//     // printf("读取到的值: %.6f\n", val);
//     BiquadFilter filter;
//     float sampleRate = 50.0;    // 采样率 50Hz
//     float cutoffFreq = 0.2;      // 截止频率 1Hz
    
//     // 计算滤波器系数
//     butterworthLPF(&filter, cutoffFreq, sampleRate);
//     initFilter(&filter);
    
//     // 模拟输入信号（正弦波+高频噪声）
//     float frequency = 10.0;       // 信号频率 10Hz
//     float noiseFreq = 200.0;      // 噪声频率 200Hz
//     int numSamples = 1000;        // 处理1000个样本
    
//     // 打开CSV文件用于保存数据
//     FILE *csvFile = fopen("filter_data.csv", "w");
//     if (csvFile == NULL) {
//         printf("无法创建CSV文件!\n");
//         return 1;
//     }
    
//     // 写入CSV文件头部
//     fprintf(csvFile, "Sample,Time,Input,Filtered\n");
    
//     printf("正在处理数据并保存到filter_data.csv...\n");
    
//     for (int i = 0; i < numSamples; i++) {
//         float t = i / sampleRate;
//         // float signal = sin(2 * M_PI * frequency * t);
//         // float noise = 0.5 * sin(2 * M_PI * noiseFreq * t);
//         // float input = signal + noise;
//         float input = read_csv_float("current.csv", i+29, 4); // 读取current.csv第28行第4列（D28）
//         // 处理样本
//         float output = processSample(&filter, input);
        
//         // 输出到控制台
//         if (i % 100 == 0) { // 每100个样本输出一次，避免控制台输出过多
//             printf("Sample %d: Input=%.6f, Filtered=%.6f\n", i, input, output);
//         }
        
//         // 写入CSV文件
//         fprintf(csvFile, "%d,%.6f,%.6f,%.6f\n", i, t, input, output);
//     }
    
//     // 关闭文件
//     fclose(csvFile);
//     printf("数据处理完成， 结果已保存到filter_data.csv\n");
    
//     return 0;

// }
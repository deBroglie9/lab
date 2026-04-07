#ifndef TEACHING_H
#define TEACHING_H

#include <iostream>
#include <vector>
#include <cmath>
#include <thread>
#include <chrono>
#include <iomanip>
#include <fstream>
#include <array>

bool saveTrajectoryToCSV(const std::vector<std::array<double, 7>>& trajectory,
                         const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "无法打开文件: " << filename << std::endl;
        return false;
    }

    // 可选：写入表头
    file << "joint1,joint2,joint3,joint4,joint5,joint6,joint7\n";

    // 设置输出精度，保留足够的小数位（例如6位）
    file << std::fixed << std::setprecision(6);

    for (const auto& point : trajectory) {
        for (size_t i = 0; i < point.size(); ++i) {
            file << point[i];
            if (i < point.size() - 1) file << ',';   // 除最后一列外加逗号
        }
        file << '\n';
    }

    file.close();
    std::cout << "轨迹已保存到 " << filename << "，共 " << trajectory.size() << " 个点\n";
    return true;
}

bool loadTrajectoryFromCSV(std::vector<std::array<double, 7>>& trajectory,
                           const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "无法打开文件: " << filename << std::endl;
        return false;
    }

    trajectory.clear();
    std::string line;
    bool isFirstLine = true;  // 跳过表头（如果有）

    while (std::getline(file, line)) {
        if (isFirstLine) {
            // 简单检查第一行是否包含字母（可能是表头），如果包含则跳过
            if (line.find_first_not_of("0123456789.-+, ") == std::string::npos) {
                // 全是数字和分隔符，说明不是表头，当作数据行处理
                isFirstLine = false;
            } else {
                isFirstLine = false;
                continue;  // 跳过表头
            }
        }

        std::stringstream ss(line);
        std::array<double, 7> point;
        char comma;
        for (size_t i = 0; i < 7; ++i) {
            ss >> point[i];
            if (i < 6) ss >> comma;   // 读取逗号分隔符
            if (ss.fail()) {
                std::cerr << "解析错误，行内容: " << line << std::endl;
                return false;
            }
        }
        trajectory.push_back(point);
    }

    file.close();
    std::cout << "从 " << filename << " 加载轨迹，共 " << trajectory.size() << " 个点\n";
    return true;
}
// 3D 空间点（带时间戳可选）
// struct Point3D {
//     double x, y, z;
//     Point3D(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}
    
//     void print() const {
//         std::cout << std::fixed << std::setprecision(2) 
//                   << "(" << x << ", " << y << ", " << z << ")";
//     }
// };

// 连续轨迹示教器
// class ContinuousTrajectoryTeach {
// private:
//     std::vector<Point3D> trajectory;   // 轨迹点序列（密集）
//     bool isRecording = false;
    
//     // 线性插值：返回 p1 到 p2 之间的插值点，t ∈ [0,1]
//     Point3D interpolate(const Point3D& p1, const Point3D& p2, double t) {
//         return Point3D(
//             p1.x + (p2.x - p1.x) * t,
//             p1.y + (p2.y - p1.y) * t,
//             p1.z + (p2.z - p1.z) * t
//         );
//     }
    
// public:
//     // 开始记录连续轨迹（清空旧轨迹）
//     void startRecording() {
//         trajectory.clear();
//         isRecording = true;
//         std::cout << "[CP示教] 开始连续轨迹记录...\n";
//         std::cout << "提示：将自动生成演示曲线，实际使用时请替换为实时读取机械臂位姿\n";
//     }
    
//     // 模拟实时记录当前点位（在实际系统中应从机械臂API读取）
//     void recordCurrentPoint(const Point3D& point) {
//         if (!isRecording) {
//             std::cout << "[错误] 未处于记录模式\n";
//             return;
//         }
//         trajectory.push_back(point);
//         std::cout << "[记录] 已添加点 " << trajectory.size() << ": ";
//         point.print();
//         std::cout << std::endl;
//     }
    
//     // 结束记录
//     void stopRecording() {
//         isRecording = false;
//         std::cout << "[CP示教] 记录结束，共获取 " << trajectory.size() << " 个轨迹点\n";
//     }
    
//     // 生成一条示例连续轨迹（如正弦曲线在XY平面内，Z恒定）
//     void generateDemoTrajectory() {
//         trajectory.clear();
//         // 生成 XY 平面上的正弦曲线，x 从 0 到 10，步长 0.1
//         for (double x = 0; x <= 10; x += 0.1) {
//             double y = sin(x);
//             double z = 0.5;  // 固定高度
//             trajectory.emplace_back(x, y, z);
//         }
//         std::cout << "[生成] 已生成演示连续轨迹，包含 " << trajectory.size() << " 个点\n";
//     }
    
//     // 回放连续轨迹（直接按记录的点移动，模拟连续路径）
//     void playbackDirect(double stepDelayMs = 20) {
//         if (trajectory.empty()) {
//             std::cout << "[回放] 轨迹为空，请先记录或生成轨迹\n";
//             return;
//         }
//         std::cout << "[回放] 开始执行连续轨迹（直接逐点移动）...\n";
//         for (size_t i = 0; i < trajectory.size(); ++i) {
//             std::cout << "  移动至点 " << i+1 << " ";
//             trajectory[i].print();
//             std::cout << std::endl;
//             std::this_thread::sleep_for(std::chrono::milliseconds((int)stepDelayMs));
//         }
//         std::cout << "[回放] 轨迹执行完毕\n";
//     }
    
//     // 回放连续轨迹（带线性插值，使运动更平滑，适合记录点较稀疏的情况）
//     void playbackSmooth(int interpolationSteps = 5, double stepDelayMs = 5) {
//         if (trajectory.empty()) {
//             std::cout << "[回放] 轨迹为空，请先记录或生成轨迹\n";
//             return;
//         }
//         if (interpolationSteps < 1) interpolationSteps = 1;
        
//         std::cout << "[回放] 开始执行连续轨迹（平滑插值，每段插值 " << interpolationSteps << " 步）...\n";
//         for (size_t i = 0; i < trajectory.size() - 1; ++i) {
//             const auto& p1 = trajectory[i];
//             const auto& p2 = trajectory[i+1];
//             for (int step = 0; step <= interpolationSteps; ++step) {
//                 double t = (double)step / interpolationSteps;
//                 Point3D mid = interpolate(p1, p2, t);
//                 std::cout << "  移动至插值点 ";
//                 mid.print();
//                 std::cout << " (原始段 " << i+1 << " → " << i+2 << ")" << std::endl;
//                 std::this_thread::sleep_for(std::chrono::milliseconds((int)stepDelayMs));
//             }
//         }
//         // 确保最后一个点被移动到
//         std::cout << "  移动至终点 ";
//         trajectory.back().print();
//         std::cout << std::endl;
//         std::cout << "[回放] 轨迹执行完毕\n";
//     }
    
//     // 清除轨迹数据
//     void clearTrajectory() {
//         trajectory.clear();
//         std::cout << "[清除] 连续轨迹已删除\n";
//     }
    
//     // 显示轨迹信息
//     void showTrajectory() const {
//         if (trajectory.empty()) {
//             std::cout << "[信息] 当前无轨迹数据\n";
//             return;
//         }
//         std::cout << "[信息] 当前轨迹包含 " << trajectory.size() << " 个点，大致路径范围：\n";
//         double minX = trajectory[0].x, maxX = trajectory[0].x;
//         double minY = trajectory[0].y, maxY = trajectory[0].y;
//         double minZ = trajectory[0].z, maxZ = trajectory[0].z;
//         for (const auto& p : trajectory) {
//             if (p.x < minX) minX = p.x; if (p.x > maxX) maxX = p.x;
//             if (p.y < minY) minY = p.y; if (p.y > maxY) maxY = p.y;
//             if (p.z < minZ) minZ = p.z; if (p.z > maxZ) maxZ = p.z;
//         }
//         std::cout << "  X: [" << minX << ", " << maxX << "]\n";
//         std::cout << "  Y: [" << minY << ", " << maxY << "]\n";
//         std::cout << "  Z: [" << minZ << ", " << maxZ << "]\n";
//     }
    
//     // 手动添加一个点（用于构建自定义轨迹）
//     void addPointManually() {
//         double x, y, z;
//         std::cout << "输入点位坐标 (x y z): ";
//         std::cin >> x >> y >> z;
//         trajectory.emplace_back(x, y, z);
//         std::cout << "[手动] 已添加点 " << trajectory.size() << ": ";
//         trajectory.back().print();
//         std::cout << std::endl;
//     }
// };

// // 命令行菜单
// int main() {
//     ContinuousTrajectoryTeach cpRobot;
//     int choice;
//     double delay;
//     int interpSteps;
    
//     std::cout << "=== 机械臂连续轨迹(CP)示教模拟器 ===\n";
//     std::cout << "说明：连续轨迹用于喷涂、焊接、涂胶等需要精确路径跟随的任务\n";
    
//     while (true) {
//         std::cout << "\n请选择操作:\n";
//         std::cout << "1. 生成演示连续轨迹 (正弦曲线)\n";
//         std::cout << "2. 手动添加轨迹点 (可逐个添加)\n";
//         std::cout << "3. 开始记录模式 (清空后自动记录，本示例未连接真实机械臂)\n";
//         std::cout << "4. 停止记录模式\n";
//         std::cout << "5. 回放轨迹 (直接逐点移动)\n";
//         std::cout << "6. 回放轨迹 (平滑插值，适合稀疏轨迹)\n";
//         std::cout << "7. 显示轨迹信息\n";
//         std::cout << "8. 清除轨迹\n";
//         std::cout << "0. 退出\n";
//         std::cout << "输入数字: ";
//         std::cin >> choice;
        
//         switch (choice) {
//             case 1:
//                 cpRobot.generateDemoTrajectory();
//                 break;
//             case 2:
//                 cpRobot.addPointManually();
//                 break;
//             case 3:
//                 cpRobot.startRecording();
//                 // 注意：在实际系统中，这里应该循环读取机械臂实时位姿并调用 recordCurrentPoint
//                 // 此处仅提示用户手动添加点或使用生成函数代替
//                 std::cout << "实际使用时需要连接机械臂，在循环中不断读取关节角度并转换位姿\n";
//                 std::cout << "当前示例中请使用 '2. 手动添加轨迹点' 或 '1. 生成演示轨迹' 构建轨迹\n";
//                 cpRobot.stopRecording(); // 立即停止，避免空轨迹
//                 break;
//             case 4:
//                 cpRobot.stopRecording();
//                 break;
//             case 5:
//                 std::cout << "输入每步移动延迟(毫秒，默认20): ";
//                 std::cin >> delay;
//                 cpRobot.playbackDirect(delay > 0 ? delay : 20);
//                 break;
//             case 6:
//                 std::cout << "输入插值步数(每段原始点之间，默认5): ";
//                 std::cin >> interpSteps;
//                 std::cout << "输入每插值步延迟(毫秒，默认5): ";
//                 std::cin >> delay;
//                 cpRobot.playbackSmooth(interpSteps > 0 ? interpSteps : 5, 
//                                        delay > 0 ? delay : 5);
//                 break;
//             case 7:
//                 cpRobot.showTrajectory();
//                 break;
//             case 8:
//                 cpRobot.clearTrajectory();
//                 break;
//             case 0:
//                 std::cout << "退出程序\n";
//                 return 0;
//             default:
//                 std::cout << "无效输入，请重试\n";
//         }
//     }
//     return 0;
// }

#endif
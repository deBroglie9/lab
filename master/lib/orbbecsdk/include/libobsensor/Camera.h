#ifndef CAMERA_H
#define CAMERA_H

#include <thread>
#include <mutex>
#include <atomic>
#include <filesystem>
#include "libobsensor/hpp/Utils.hpp"
#include "libobsensor/hpp/Error.hpp"

#include <libobsensor/ObSensor.hpp>
#include "utils.hpp"
#include "utils_opencv.hpp"

void saveDepth(std::shared_ptr<ob::DepthFrame> depthFrame, int index) {
    std::vector<int> compression_params;
    compression_params.push_back(cv::IMWRITE_PNG_COMPRESSION);
    compression_params.push_back(0);
    compression_params.push_back(cv::IMWRITE_PNG_STRATEGY);
    compression_params.push_back(cv::IMWRITE_PNG_STRATEGY_DEFAULT);
    std::string depthName = "Depth_" + std::to_string(depthFrame->width()) + "x" + std::to_string(depthFrame->height()) + "_" + std::to_string(index) + "_"
                            + std::to_string(depthFrame->timeStamp()) + "ms.png";
    cv::Mat depthMat(depthFrame->height(), depthFrame->width(), CV_16UC1, depthFrame->data());
    cv::imwrite(depthName, depthMat, compression_params);
    std::cout << "Depth saved:" << depthName << std::endl;
}

// Save the color image in png format
void saveColor(std::shared_ptr<ob::ColorFrame> colorFrame, int index) {
    const std::string outputDir = "../captured_images";

    // 创建目录（如果不存在）
    std::filesystem::path dirPath(outputDir);
    if (!std::filesystem::exists(dirPath)) {
        std::filesystem::create_directories(dirPath);
        std::cout << "Created directory: " << outputDir << std::endl;
    }

    //构建文件名和完整路径
    std::string filename = "Color_" + std::to_string(colorFrame->width()) + "x" + std::to_string(colorFrame->height())
                         + "_" + std::to_string(index) + "_" + std::to_string(colorFrame->timeStamp()) + "ms.png";
    std::string fullPath = outputDir + "/" + filename;

    std::vector<int> compression_params;
    compression_params.push_back(cv::IMWRITE_PNG_COMPRESSION);
    compression_params.push_back(0);
    compression_params.push_back(cv::IMWRITE_PNG_STRATEGY);
    compression_params.push_back(cv::IMWRITE_PNG_STRATEGY_DEFAULT);

    // 将帧数据转换为 OpenCV Mat 并保存
    cv::Mat colorRawMat(colorFrame->height(), colorFrame->width(), CV_8UC3, colorFrame->data());
    cv::imwrite(fullPath, colorRawMat, compression_params);
    std::cout << "Color saved: " << fullPath << std::endl;
}

void runPipelineAndSave(ob::Pipeline& pipeline) {
    ob::FormatConvertFilter formatConvertFilter;
    //ob_smpl::CVWindow win("Color");
    int colorCount = 0;
    int frameCount = 0;
    while(true) {
        auto frameSet = pipeline.waitForFrameset();
        if(frameSet == nullptr) {
            std::cout << "The frameset is null!" << std::endl;
            continue;
        }
        auto colorFrame = frameSet->colorFrame();
        //win.pushFramesToView(colorFrame);

        if(frameCount < 5) {
            frameCount++;
            continue;
        }

        if(colorFrame != nullptr && colorCount < 1) {
            if(colorFrame->format() != OB_FORMAT_RGB) {
                if(colorFrame->format() == OB_FORMAT_MJPG) {
                    formatConvertFilter.setFormatConvertType(FORMAT_MJPG_TO_RGB888);
                }
                else if(colorFrame->format() == OB_FORMAT_UYVY) {
                    formatConvertFilter.setFormatConvertType(FORMAT_UYVY_TO_RGB888);
                }
                else if(colorFrame->format() == OB_FORMAT_YUYV) {
                    formatConvertFilter.setFormatConvertType(FORMAT_YUYV_TO_RGB888);
                }
                else {
                    std::cout << "Color format is not support!" << std::endl;
                    continue;
                }
                colorFrame = formatConvertFilter.process(colorFrame)->as<ob::ColorFrame>();
            }
            formatConvertFilter.setFormatConvertType(FORMAT_RGB888_TO_BGR);
            colorFrame = formatConvertFilter.process(colorFrame)->as<ob::ColorFrame>();
            saveColor(colorFrame, colorCount);
            colorCount++;
        }
        else{
            std::cout << "Output " << colorCount << " frames" << std::endl;
            break;
        }
    }
}

#endif // CAMERA_H
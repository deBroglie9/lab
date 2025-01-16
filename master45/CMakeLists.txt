cmake_minimum_required(VERSION 3.10.0) # CMake install : https://cmake.org/download/
project(Master)

# 指定目标系统
set(CMAKE_SYSTEM_NAME Linux)
# 指定目标平台
set(CMAKE_SYSTEM_PROCESSOR arm)

set(CMAKE_FIND_ROOT_PATH "/usr/local/arm/gcc-linaro-4.9.4-2017.01-x86_64_arm-linux-gnueabihf/")

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)

set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
# 指定交叉编译工具链的根路径
set(CROSS_CHAIN_PATH /usr/local/arm/gcc-linaro-4.9.4-2017.01-x86_64_arm-linux-gnueabihf)
# 指定C编译器
set(CMAKE_C_COMPILER "${CROSS_CHAIN_PATH}/bin/arm-linux-gnueabihf-gcc")
# 指定C++编译器
set(CMAKE_CXX_COMPILER "${CROSS_CHAIN_PATH}/bin/arm-linux-gnueabihf-g++")

aux_source_directory(src SRC_LIST)

include_directories(/root/output/include)
include_directories(/root/output/lib)
include_directories(/root/master45/inc)

LINK_LIBRARIES(m)

add_executable(master main.c ${SRC_LIST})

link_directories("/home/debian/output/lib")

target_link_libraries(master /root/output/lib/libethercat.so)


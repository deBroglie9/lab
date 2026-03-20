cmake_minimum_required(VERSION 3.10.0) # CMake install : https://cmake.org/download/
project(Master)

# 指定目标系统
set(CMAKE_SYSTEM_NAME Linux)
# 指定目标平台
set(CMAKE_SYSTEM_PROCESSOR arm)

list(APPEND INCLUDE_DIRS 
    "${CMAKE_CURRENT_SOURCE_DIR}/interface" 
    "${CMAKE_CURRENT_SOURCE_DIR}/EtherCAT"
    "${CMAKE_CURRENT_SOURCE_DIR}/feedback"
    "${CMAKE_CURRENT_SOURCE_DIR}/planning"
    "${CMAKE_CURRENT_SOURCE_DIR}/Kinematics"
    "${CMAKE_CURRENT_SOURCE_DIR}/control"
    "${CMAKE_CURRENT_SOURCE_DIR}/eigen"
    "${CMAKE_CURRENT_SOURCE_DIR}")
    # "${CMAKE_CURRENT_SOURCE_DIR}/Jacobian_S")
# message("包含目录：" "${INCLUDE_DIRS}")

include_directories("${INCLUDE_DIRS}")

aux_source_directory(. SRC_LIST)
file(GLOB_RECURSE SRC_FILE "*.cpp" "*.c")
file(GLOB_RECURSE BUILD_CPP_FILES "build/*.cpp" "build/*.c" "Jacobian_S/*.cpp" "Jacobian_S/*.c")
list(REMOVE_ITEM SRC_FILE ${BUILD_CPP_FILES})
# list(APPEND SRC_LIST "${CMAKE_CURRENT_SOURCE_DIR}/interface" "${CMAKE_CURRENT_SOURCE_DIR}/IK_7DOF")

# message("包含文件：" "${SRC_FILE}")

LINK_LIBRARIES(m)

add_executable(master ${SRC_FILE})

target_link_libraries(master /usr/local/lib/libethercat.so -pthread)

message(${CMAKE_CXX_COMPILER})
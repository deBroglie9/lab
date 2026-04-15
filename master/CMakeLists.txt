cmake_minimum_required(VERSION 3.10.0) # CMake install : https://cmake.org/download/
project(master)

# 指定目标系统
set(CMAKE_SYSTEM_NAME Linux)
# 指定目标平台
set(CMAKE_SYSTEM_PROCESSOR arm)

# 1. 查找 OpenCV（utils 中的 CVWindow 依赖它）
find_package(OpenCV REQUIRED)

# 2. 查找 Orbbec SDK（使用官方 config 文件）
set(OrbbecSDK_DIR "${CMAKE_SOURCE_DIR}/lib/orbbecsdk/lib")
find_package(OrbbecSDK REQUIRED)

# 3. 查找并设置线程库
find_package(Threads REQUIRED)

# 4. 收集所有源文件（排除 build 目录和可能不需要的测试文件）
# 添加源代码文件
file(GLOB_RECURSE SRC_FILES
    "*.cpp"
    "*.c"
)
# 排除 build Jacobian_S目录下的文件
file(GLOB_RECURSE BUILD_FILES "build/*.cpp" "build/*.c" "lib/Jacobian_S/*.cpp" "lib/Jacobian_S/*.c")
list(REMOVE_ITEM SRC_FILES ${BUILD_FILES})

# 5. 添加可执行文件（只生成一个）
add_executable(master ${SRC_FILES})

# 6. 添加所有需要的头文件搜索路径
target_include_directories(master PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/lib
    ${CMAKE_SOURCE_DIR}/lib/interface
    ${CMAKE_SOURCE_DIR}/lib/EtherCAT
    ${CMAKE_SOURCE_DIR}/lib/feedback
    ${CMAKE_SOURCE_DIR}/lib/planning
    ${CMAKE_SOURCE_DIR}/lib/Kinematics
    ${CMAKE_SOURCE_DIR}/lib/control
    ${CMAKE_SOURCE_DIR}/lib/Eigen
    ${CMAKE_SOURCE_DIR}/lib/orbbecsdk/include
    ${CMAKE_SOURCE_DIR}/lib/orbbecsdk/utils
    #${CMAKE_SOURCE_DIR}/lib/Jacobian_S   # 如果需要，保留
)

# 7. 链接库
target_link_libraries(master
    ob::OrbbecSDK
    ${OpenCV_LIBS}
    Threads::Threads
    m                           # 数学库
    /usr/local/lib/libethercat.so -pthread
    # 如果还有其他自定义库，在这里添加
)

# 8. 设置 RPATH 以便找到 Orbbec SDK 动态库
set_target_properties(master PROPERTIES
    INSTALL_RPATH "${CMAKE_SOURCE_DIR}/lib/orbbecsdk/lib"
    BUILD_RPATH "${CMAKE_SOURCE_DIR}/lib/orbbecsdk/lib"
)

# target_include_directories(${PROJECT_NAME} PRIVATE
#     ${CMAKE_SOURCE_DIR}/lib/orbbecsdk/include          # 用于 <libobsensor/ObSensor.hpp>
#     ${CMAKE_SOURCE_DIR}/lib/orbbecsdk/utils            # 用于 utils.hpp, utils_opencv.hpp 等
# )

# include_directories(lib/orbbecsdk/include)
# add_subdirectory(lib/orbbecsdk/utils)




# include_directories("${INCLUDE_DIRS}")

# aux_source_directory(. SRC_LIST)
# file(GLOB_RECURSE SRC_FILE "*.cpp" "*.c")
# file(GLOB_RECURSE BUILD_CPP_FILES "build/*.cpp" "build/*.c" "Jacobian_S/*.cpp" "Jacobian_S/*.c")
# list(REMOVE_ITEM SRC_FILE ${BUILD_CPP_FILES})
# # list(APPEND SRC_LIST "${CMAKE_CURRENT_SOURCE_DIR}/interface" "${CMAKE_CURRENT_SOURCE_DIR}/IK_7DOF")

# message("包含文件：" "${SRC_FILE}")

# LINK_LIBRARIES(m)

# add_executable(master ${SRC_FILE})

# target_link_libraries(master /usr/local/lib/libethercat.so -pthread)

# message(${CMAKE_CXX_COMPILER})
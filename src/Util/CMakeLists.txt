# 设置最低的 CMake 版本要求
cmake_minimum_required(VERSION 3.16)

# 定义项目名称和版本
project(Util VERSION 1.0 LANGUAGES CXX)

file(GLOB_RECURSE UTIL_HEADERS "*.h")

# 由于只有头文件，创建一个接口库
add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME} INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/include
)

find_package(nlohmann_json REQUIRED)

target_link_libraries(${PROJECT_NAME} INTERFACE
    nlohmann_json::nlohmann_json
)

message(STATUS "CMAKE_SOURCE_DIR is: ${CMAKE_SOURCE_DIR}")

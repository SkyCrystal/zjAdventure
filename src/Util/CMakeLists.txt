# 设置最低的 CMake 版本要求
cmake_minimum_required(VERSION 3.16)

# 定义项目名称和版本
project(Util VERSION 1.0 LANGUAGES CXX)

file(GLOB_RECURSE UTIL_HEADERS "*.h")
file(GLOB_RECURSE UTIL_SOURCES "*.cpp")

add_library(${PROJECT_NAME} STATIC ${UTIL_SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/include
)

find_package(nlohmann_json REQUIRED)

target_link_libraries(${PROJECT_NAME} PUBLIC
    nlohmann_json::nlohmann_json
)

message(STATUS "CMAKE_SOURCE_DIR is: ${CMAKE_SOURCE_DIR}")

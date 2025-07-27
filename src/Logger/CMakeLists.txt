# 设置最低的 CMake 版本要求
cmake_minimum_required(VERSION 3.16)

# 定义项目名称和版本
project(Logger VERSION 1.0 LANGUAGES CXX)

file(GLOB_RECURSE LOGGER_SOURCES "*.cpp")
file(GLOB_RECURSE LOGGER_HEADERS "*.h")

add_library(${PROJECT_NAME} STATIC ${LOGGER_SOURCES})

find_package(spdlog REQUIRED)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/include

)

target_link_libraries(${PROJECT_NAME} PUBLIC
    spdlog::spdlog
)

message(STATUS "CMAKE_SOURCE_DIR is: ${CMAKE_SOURCE_DIR}")

# 设置最低的 CMake 版本要求
cmake_minimum_required(VERSION 3.16)

# 定义项目名称和版本
project(Item VERSION 1.0 LANGUAGES CXX)

file(GLOB_RECURSE ITEM_SOURCES "*.cpp")
file(GLOB_RECURSE ITEM_HEADERS "*.h")

add_library(${PROJECT_NAME} SHARED ${ITEM_SOURCES})

find_package(nlohmann_json REQUIRED)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME} PUBLIC
    nlohmann_json::nlohmann_json
)

message(STATUS "CMAKE_SOURCE_DIR is: ${CMAKE_SOURCE_DIR}")

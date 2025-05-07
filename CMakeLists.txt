# 设置最低的 CMake 版本要求
cmake_minimum_required(VERSION 3.16)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 定义项目名称和版本
project(zjAdventure VERSION 1.0)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

add_executable(zjAdventure main.cpp)

target_include_directories(zjAdventure PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(src)

target_link_libraries(zjAdventure PRIVATE testlib)
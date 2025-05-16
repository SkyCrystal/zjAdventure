# 设置最低的 CMake 版本要求
cmake_minimum_required(VERSION 3.16)

# 定义项目名称和版本
project(src VERSION 1.0)

include_directories(Util)

add_subdirectory(testlib)

# add_subdirectory(Action)
add_subdirectory(Character)
add_subdirectory(Game)
# add_subdirectory(Item)

add_subdirectory(Util)


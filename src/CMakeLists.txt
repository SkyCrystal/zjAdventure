# 设置最低的 CMake 版本要求
cmake_minimum_required(VERSION 3.16)

# 定义项目名称和版本
project(src VERSION 1.0)

# 解决 Windows 下中文编码问题 (C4819 警告)
if(WIN32 AND MSVC)
    add_compile_options(/utf-8)
    add_compile_options(/wd4819) # 禁用 C4819 警告
endif()

include_directories(Util)

add_subdirectory(testlib)

# add_subdirectory(Action)
add_subdirectory(Character)
add_subdirectory(Game)
add_subdirectory(Item)

add_subdirectory(Util)


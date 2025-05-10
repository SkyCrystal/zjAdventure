# 设置最低的 CMake 版本要求
cmake_minimum_required(VERSION 3.16)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 定义项目名称和版本
project(zjAdventure VERSION 1.0)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# 查找必要的包
find_package(Crow REQUIRED)
find_package(nlohmann_json REQUIRED)

# 添加可执行文件
add_executable(zjAdventure main.cpp)

# 设置包含目录
target_include_directories(zjAdventure PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# 链接库
target_link_libraries(zjAdventure PRIVATE 
    Crow::Crow
    nlohmann_json::nlohmann_json
    Game
)

# 添加子目录
add_subdirectory(src)

# 复制前端文件到输出目录
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/templates DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug)
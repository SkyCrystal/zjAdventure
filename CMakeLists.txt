# 设置最低的 CMake 版本要求
cmake_minimum_required(VERSION 3.16)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 定义项目名称和版本
project(zjAdventure VERSION 1.0)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# 计算源文件路径偏移量，用于日志中的相对路径显示
string(LENGTH "${CMAKE_CURRENT_SOURCE_DIR}/" SOURCE_DIR_LENGTH)
add_compile_definitions(SOURCE_PATH_OFFSET=${SOURCE_DIR_LENGTH})

# 解决 Windows 下中文编码问题 (C4819 警告)
if(WIN32 AND MSVC)
    add_compile_options(/utf-8)
    add_compile_options(/wd4819) # 禁用 C4819 警告
    # 减少编译输出的详细信息
    add_compile_options(/nologo) # 不显示编译器版本信息
endif()

# 查找必要的包
find_package(Crow REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(spdlog REQUIRED)

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
    spdlog::spdlog
    Game
)

# 添加子目录
add_subdirectory(src)

# 复制前端文件到输出目录
add_custom_command(
    TARGET zjAdventure POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/web/
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)

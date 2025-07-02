@echo off
echo 正在安装vcpkg依赖...

REM 设置vcpkg目录
if "%VCPKG_ROOT%"=="" (
    echo 正在克隆vcpkg...
    git clone https://github.com/Microsoft/vcpkg.git C:\vcpkg
    set VCPKG_ROOT=C:\vcpkg
) else (
    echo 使用现有的vcpkg: %VCPKG_ROOT%
)

REM 进入vcpkg目录
cd /d "%VCPKG_ROOT%"

REM 构建vcpkg
if not exist "vcpkg.exe" (
    echo 正在构建vcpkg...
    call bootstrap-vcpkg.bat
)

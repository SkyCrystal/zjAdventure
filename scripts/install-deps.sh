#!/bin/bash
set -e

echo "正在安装vcpkg依赖..."

# 设置vcpkg目录
if [ -z "$VCPKG_ROOT" ]; then
    echo "正在克隆vcpkg..."
    git clone https://github.com/Microsoft/vcpkg.git /tmp/vcpkg
    export VCPKG_ROOT=/tmp/vcpkg
else
    echo "使用现有的vcpkg: $VCPKG_ROOT"
fi

# 进入vcpkg目录
cd "$VCPKG_ROOT"

# 构建vcpkg
if [ ! -f "vcpkg" ]; then
    echo "正在构建vcpkg..."
    ./bootstrap-vcpkg.sh
fi

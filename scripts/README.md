# 依赖安装脚本

这个目录包含用于安装项目依赖的脚本。

## 文件说明

- `install-deps.bat` - Windows批处理脚本
- `install-deps.sh` - Linux/macOS Shell脚本

## 使用方法

### Windows
```cmd
scripts\install-deps.bat
```

### Linux/macOS
```bash
./scripts/install-deps.sh
```

## GitHub Actions集成

项目的GitHub Actions工作流已经配置为自动安装依赖。工作流会：

1. 使用 `lukka/run-vcpkg@v11` action 设置vcpkg
2. 自动安装 `vcpkg.json` 中定义的依赖（crow, nlohmann-json）
3. 使用正确的工具链文件配置CMake
4. 构建项目

## 本地开发

如果需要在本地开发，请先运行相应的依赖安装脚本或正确设置VCPKG_ROOT，然后：

```bash
# 配置CMake
cmake -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=[vcpkg路径]/scripts/buildsystems/vcpkg.cmake

# 构建项目
cmake --build build --config Release
```

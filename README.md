# 高性能C++服务框架

## 项目简介
本项目是一个基于C++开发的高性能服务器框架，采用现代C++特性和CMake构建系统，提供了完整的网络服务、数据库访问等基础设施，适用于开发高并发、低延迟的服务器应用。

## 技术栈
### 开发语言和构建工具
- 语言：C++ (C++20)
- 构建系统：CMake 3.15+
- 编译器：Clang

### 核心依赖
- 网络库：Boost.Asio


## 模块
### 1. 网络模块 (wm-net)


### 2. 核心模块 (wm-core)


### 3. 应用模块 (wm-app)


## 项目结构

```
wm-root/                  # 项目根目录
├── CMakeLists.txt        # 主CMake配置文件
├── wm-net/               # 网络模块
│   ├── CMakeLists.txt
│   ├── src/              # 源文件
│   └── tests/            # 单元测试
├── wm-protocol/          # 协议封装层
│   ├── CMakeLists.txt
│   ├── src/              # 源文件
│   └── tests/            # 单元测试
└── wm-business/          # 业务模块
    ├── CMakeLists.txt
    ├── src/              # 源文件
    └── tests/            # 单元测试
```
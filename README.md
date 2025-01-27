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


## 核心模块
### 1. 网络模块 (wm-net)
- 基于Reactor模式的事件驱动架构
- 高性能线程池
- 异步IO操作支持
- 定时器管理
- TCP/UDP协议支持
- 长连接管理
- 断线重连机制
- 心跳检测

### 2. 协议封装层 (wm-protocol)
- 二进制协议序列化
- Protocol Buffers支持
- 自定义协议框架
- 消息编解码

### 3. 业务模块 (wm-business)
- 模块化设计
- 插件系统
- 业务逻辑隔离
- 可扩展接口

## 项目结构

wm-root/                   # 项目根目录
├── CMakeLists.txt        # 主CMake配置文件
├── wm-net/               # 网络模块
│   ├── CMakeLists.txt
│   ├── include/          # 公共头文件
│   │   └── wm-net/
│   ├── src/             # 源文件
│   └── tests/           # 单元测试
│       ├── core/        # 核心测试
│       ├── tcp/         # TCP测试
│       └── udp/         # UDP测试
├── wm-protocol/          # 协议封装层
│   ├── CMakeLists.txt
│   ├── include/         # 公共头文件
│   │   └── wm-protocol/
│   ├── src/            # 源文件
│   └── tests/          # 单元测试
└── wm-business/         # 业务模块
    ├── CMakeLists.txt
    ├── include/        # 公共头文件
    │   └── wm-business/
    ├── src/           # 源文件
    └── tests/         # 单元测试
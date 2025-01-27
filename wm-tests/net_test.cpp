#include <boost/asio.hpp>
#include <iostream>
#include <ctime>
#include <string>
#include <spdlog/spdlog.h>

int main(int argc, char *argv[])
{
    // 初始化spdlog
    spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%l] %v");
    spdlog::set_level(spdlog::level::debug);

    spdlog::info("Starting net_test...");
    
    try {
        // 示例代码
        spdlog::debug("Creating io_context...");
        boost::asio::io_context io_context;
        
        spdlog::info("Net test completed successfully");
    } catch (const std::exception& e) {
        spdlog::error("Exception occurred: {}", e.what());
        return 1;
    }

    return 0;
}
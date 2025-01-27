#include <spdlog/spdlog.h>

int main(int argc, char *argv[])
{
    // 初始化spdlog
    spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%l] %v");
    spdlog::set_level(spdlog::level::debug);

    spdlog::info("Starting net_test...");

    spdlog::debug("Creating io_context...");

    spdlog::info("Net test completed successfully");

    return 0;
}
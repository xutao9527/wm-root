#include <spdlog/spdlog.h>
#include <iostream>
#include <conf/server_conf.hpp>
#include <net/server.hpp>

int main() {
	Server server;
	// SetConsoleOutputCP(CP_UTF8);  // 设置控制台为 UTF-8
	// std::cout << "服务地址" << std::endl;
	// std::cout << "服务端口" << std::endl;
	// std::cout << "服务线程数" << std::endl;
	// spdlog::info("服务地址");
	// spdlog::info("服务端口");
	// spdlog::info("服务线程数");
    return 0;
}

	// try {
	
	// 	boost::property_tree::ptree pt;
	
	// 	boost::property_tree::ini_parser::read_ini("resources/config.ini", pt);
	
	// 	std::string address = pt.get<std::string>("ServerSettings.address", "127.0.0.1");
	// 	int port = pt.get<int>("ServerSettings.port", 8080);
	// 	int threadNum = pt.get<int>("ServerSettings.thread_num", 4);
	
	// 	spdlog::info("服务地址: {}", address);
	// 	spdlog::info("服务端口: {}", port);
	// 	spdlog::info("服务线程数: {}", threadNum);

	// }
	// catch (const std::exception& e) {
	// 	spdlog::error("读取配置文件失败: {}", e.what());

	// 	return 1;
	// }


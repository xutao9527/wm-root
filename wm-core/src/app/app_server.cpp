#include "app_server.hpp"

AppServer::AppServer()
{
    spdlog::info("AppServer");
    spdlog::info("address: {}", server_conf_.address);
    spdlog::info("port: {}", server_conf_.port);
    spdlog::info("thread_num: {}", server_conf_.thread_num);
    io_context_ = std::make_unique<boost::asio::io_context>(server_conf_.thread_num);
    tcp_server_ = std::make_shared<TcpServer>(*io_context_, server_conf_);
}

    

AppServer::~AppServer()
{
    spdlog::info("~AppServer");
}

void AppServer::run()
{
    spdlog::info("AppServer run");
}
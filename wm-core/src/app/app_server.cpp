#include "app_server.hpp"

AppServer::AppServer()
{
    io_context_ = std::make_unique<boost::asio::io_context>(server_conf_.thread_num);
    // work_guard_ = std::make_unique<boost::asio::executor_work_guard<boost::asio::io_context::executor_type>>(io_context_->get_executor());
    tcp_server_ = std::make_shared<TcpServer>(*io_context_, server_conf_);
    threads_.reserve(server_conf_.thread_num-1);
}

AppServer::~AppServer()
{
    spdlog::info("~AppServer");
}

void AppServer::run()
{
    spdlog::info("AppServer run");
    for (int i = 0; i < server_conf_.thread_num - 1; i++)
    {
        threads_.emplace_back([this]() { io_context_->run(); });
    }
    for (auto& thread : threads_)
    {
        thread.join();
    }
    io_context_->run();
}
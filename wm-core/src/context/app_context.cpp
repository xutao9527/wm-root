#include "app_context.hpp"

app_context::app_context()
{
    io_context_ = std::make_unique<boost::asio::io_context>(app_conf_.thread_num);
    // work_guard_ = std::make_unique<boost::asio::executor_work_guard<boost::asio::io_context::executor_type>>(io_context_->get_executor());
    tcp_server_ = std::make_shared<tcp_server>(*io_context_, app_conf_);
    threads_.reserve(app_conf_.thread_num-1);
}

app_context::~app_context()
{
    spdlog::info("~app_context");
}

void app_context::run()
{
    spdlog::info("app_context run");
    for (int i = 0; i < app_conf_.thread_num - 1; i++)
    {
        threads_.emplace_back([this]() { io_context_->run(); });
    }
    for (auto& thread : threads_)
    {
        thread.join();
    }
    io_context_->run();
}
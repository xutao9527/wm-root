#pragma once

#include "conf/app_conf.hpp"
#include "net/tcp_server.hpp"

class app_context
{
public:
    app_context();
    ~app_context();
    void run();

private:
    app_conf app_conf_;
    std::shared_ptr<tcp_server> tcp_server_;
    std::unique_ptr<boost::asio::io_context> io_context_;
    std::unique_ptr<boost::asio::executor_work_guard<boost::asio::io_context::executor_type>> work_guard_;
    std::vector<std::thread> threads_;
};

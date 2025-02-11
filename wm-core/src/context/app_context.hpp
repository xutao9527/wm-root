#pragma once

#include "conf/app_conf.hpp"
#include "net/listener.hpp"

class app_context
{
public:
    app_context()
    {
        io_context_ = std::make_unique<boost::asio::io_context>();
        // work_guard_ = std::make_unique<boost::asio::executor_work_guard<boost::asio::io_context::executor_type>>(io_context_->get_executor());
        listener_ = std::make_shared<listener>(*io_context_, app_conf_);
        worker_threads_.reserve(app_conf_.worker_threads);
        spdlog::debug("app_context");
    }

    ~app_context()
    {
        spdlog::debug("~app_context");
    }

    void run()
    {
        spdlog::debug("app_context run");
        listener_->run();
        
        for (int i = 0; i < app_conf_.worker_threads; i++)
        {
            worker_threads_.emplace_back([this]()
                                         { io_context_->run(); });
        }
        io_context_->run();
        for (auto &thread : worker_threads_)
        {
            thread.join();
        }
    }

private:
    app_conf app_conf_;
    std::shared_ptr<listener> listener_;
    std::unique_ptr<boost::asio::io_context> io_context_;
    // std::unique_ptr<boost::asio::executor_work_guard<boost::asio::io_context::executor_type>> work_guard_;
    std::vector<std::thread> worker_threads_;
};

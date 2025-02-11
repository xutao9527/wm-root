#pragma once

#include "conf/app_conf.hpp"
#include "net/listener.hpp"
#include <boost/asio.hpp>
#include <iostream>

class app_context
{
public:
	app_context()
	{
		spdlog::debug("app_context");
		io_context_ = std::make_unique<boost::asio::io_context>(app_conf_.worker_threads + 1);
		// work_guard_ = std::make_unique<boost::asio::executor_work_guard<boost::asio::io_context::executor_type>>(io_context_->get_executor());
		listener_ = std::make_shared<listener>(*io_context_, app_conf_);
		worker_threads_.reserve(app_conf_.worker_threads);
	}

	~app_context()
	{
		spdlog::debug("~app_context");
	}

	void start()
	{
		spdlog::debug("app_context run");
		listener_->run();
		for (int i = 0; i < app_conf_.worker_threads; i++)
		{
			worker_threads_.emplace_back([this]() {io_context_->run(); });
		}
		co_spawn(*io_context_, getInputUntilExit(), boost::asio::detached);
        co_spawn(*io_context_, [this]
			{ return this->getInputUntilExit(); }, boost::asio::detached);
		io_context_->run();
	}

	void stop()
	{
		spdlog::debug("app_context stop");
		io_context_->stop();
		for (auto& thread : worker_threads_)
		{
			thread.join();
		}
	}

private:
	// 处理终端输入的协程
	boost::asio::awaitable<void> getInputUntilExit()
	{
		std::string input;
		spdlog::info("Enter a string (type 'exit' to quit):");
		while (true)
		{   
			std::cout << "> ";
			std::getline(std::cin, input); // 获取一行输入
			if (input == "exit")
			{
				break;
			}   
			spdlog::info("You entered: {}", input);
		}
		spdlog::info("Program exited.");
		co_return;
	}

	app_conf app_conf_;
	std::shared_ptr<listener> listener_;
	std::unique_ptr<boost::asio::io_context> io_context_;
	// std::unique_ptr<boost::asio::executor_work_guard<boost::asio::io_context::executor_type>> work_guard_;
	std::vector<std::thread> worker_threads_;
};

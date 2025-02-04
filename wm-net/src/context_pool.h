#pragma once

#include "singleton.h"

class ContextPool : public Singleton<ContextPool> {
	friend class Singleton<ContextPool>;
private:
	std::vector<std::unique_ptr<boost::asio::io_context>> contexts_;
	std::vector<std::unique_ptr<boost::asio::executor_work_guard<boost::asio::io_context::executor_type>>> works_;
	std::vector<std::thread> threads_;
	std::size_t size = std::thread::hardware_concurrency();
protected:
	ContextPool(): contexts_(size), works_(size), threads_(size) {
		for (size_t i = 0; i < size; i++)
		{
			contexts_.push_back(std::make_unique<boost::asio::io_context>());
		}
		for (std::size_t i = 0; i < size; ++i) {
			works_.push_back(std::make_unique<boost::asio::executor_work_guard<boost::asio::io_context::executor_type>>(contexts_[i]->get_executor()));
		}
		for (std::size_t i = 0; i < size; ++i) {
			threads_.push_back(std::thread([this, i]() {
				contexts_[i]->run();
				}));
		}
		spdlog::info("ContextPool created");
	};



	~ContextPool() override{
		spdlog::info("ContextPool destroyed");
	};
public:
	boost::asio::io_context& get_context() {
		static std::size_t index = 0;
		auto& context = *contexts_[index];
		index = (index + 1) % size;
		return context;
	};

	void stop() {
		for (std::size_t i = 0; i < size; ++i) {
			contexts_[i]->stop();
		}
		for (std::size_t i = 0; i < size; ++i) {
			threads_[i].join();
		}
	};
};
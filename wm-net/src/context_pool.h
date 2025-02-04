#pragma once

#include "singleton.h"

class ContextPool : public Singleton<ContextPool> {
	friend class Singleton<ContextPool>;
public:
	using Work = boost::asio::executor_work_guard<boost::asio::io_context::executor_type>;
	using WorkPtr = std::unique_ptr<Work>;
	using IOContext = boost::asio::io_context;
	
private:
	std::vector<IOContext> contexts_;
	std::vector<WorkPtr> works_;
	std::vector<std::thread> threads_;
	size_t contextSize_;
	size_t contextIndex_;
protected:
	ContextPool(size_t size = std::thread::hardware_concurrency())
		: contexts_(size), works_(size), contextSize_(size), contextIndex_(0) {
		
		for (std::size_t i = 0; i < size; ++i) {
			works_[i] = std::make_unique<boost::asio::executor_work_guard<boost::asio::io_context::executor_type>>(contexts_[i].get_executor());
		}
		for (std::size_t i = 0; i < size; ++i) {
			threads_.push_back(std::thread([this, i]() {contexts_[i].run(); }));
		}
		spdlog::info("ContextPool created");
	};

	~ContextPool() override {
		spdlog::info("ContextPool destroyed");
	};
public:
	boost::asio::io_context& getContext() {
		auto& context = contexts_[contextIndex_++];
		if (contextIndex_ == contextSize_)
			contextIndex_ = 0;
		return context;
	};

	void stop() {
		for (auto& context : contexts_)
			context.stop();
		for (auto& thread : threads_) {
			thread.join();
		}
	};
};
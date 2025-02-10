#pragma once

#include "singleton.h"

boost::asio::awaitable<void> do_some_thing() {
	auto executor = co_await boost::asio::this_coro::executor;
	boost::asio::steady_timer timer(executor);
	while (true) {
		timer.expires_after(std::chrono::seconds(2));
		co_await timer.async_wait(boost::asio::use_awaitable);

		std::stringstream ss;
		ss << std::this_thread::get_id();
		spdlog::info("do some thing at work thread: {}", ss.str());
	}
}

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
	size_t contextSize_{ 0 };
	size_t contextIndex_;
protected:
	ContextPool(size_t size = 5)
		//ContextPool(size_t size = std::thread::hardware_concurrency())
		//: contexts_(size), works_(size), contextSize_(size), contextIndex_(0) {
		: contextSize_(size), contextIndex_(0), contexts_(size) {
		for (std::size_t i = 0; i < size; ++i) {
			works_.push_back(std::make_unique<boost::asio::executor_work_guard<boost::asio::io_context::executor_type>>(contexts_[i].get_executor()));
			//works_[i] = std::make_unique<boost::asio::executor_work_guard<boost::asio::io_context::executor_type>>(contexts_[i].get_executor());
		}
		for (std::size_t i = 0; i < size; ++i) {
			threads_.push_back(std::thread([this, i]() {
				co_spawn(contexts_[i], do_some_thing(), boost::asio::detached);
				contexts_[i].run();
				}));
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
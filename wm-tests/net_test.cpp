#include <boost/asio.hpp>
#include <spdlog/spdlog.h>
#include <csignal>
#include "context_pool.h"

using boost::asio::awaitable;
using boost::asio::use_awaitable;
using boost::asio::co_spawn;
using boost::asio::detached;


boost::asio::awaitable<void> print_h_periodically1() {
    auto executor = co_await boost::asio::this_coro::executor;
    boost::asio::steady_timer timer(executor);
    while (true) {
        timer.expires_after(std::chrono::seconds(1));
        co_await timer.async_wait(boost::asio::use_awaitable);
        std::stringstream ss;
        ss << std::this_thread::get_id();
        spdlog::info("h1, thread id: {}", ss.str());
    }
}

boost::asio::awaitable<void> print_h_periodically2() {
    auto executor = co_await boost::asio::this_coro::executor;
    boost::asio::steady_timer timer(executor);
    while (true) {
        timer.expires_after(std::chrono::seconds(1));
        co_await timer.async_wait(boost::asio::use_awaitable);
        std::stringstream ss;
        ss << std::this_thread::get_id();
        spdlog::info("h2, thread id: {}", std::hash<std::thread::id>{}(std::this_thread::get_id()));
        spdlog::info("h2, thread id: {}", ss.str());
    }
}

int main(int argc, char* argv[]) {
	spdlog::info("Application started");
    boost::asio::io_context io_context;
	boost::asio::executor_work_guard<boost::asio::io_context::executor_type> worker(io_context.get_executor());
    boost::asio::co_spawn(io_context, print_h_periodically1(), boost::asio::detached);
    boost::asio::co_spawn(io_context, print_h_periodically2(), boost::asio::detached);
	io_context.run();
	spdlog::info("Application stopped");
	return 0;
}

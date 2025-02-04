#include <spdlog/spdlog.h>
#include <boost/asio.hpp>
#include "tcp_server.h"
#include "context_pool.h"

boost::asio::awaitable<void> stop(boost::asio::io_context& io_context) {
    auto executor = co_await boost::asio::this_coro::executor;
    boost::asio::steady_timer timer(executor);
    timer.expires_after(std::chrono::seconds(2));
    co_await timer.async_wait(boost::asio::use_awaitable);
    io_context.stop();
    ContextPool::instance().stop();
    std::stringstream ss;
    ss << std::this_thread::get_id();
    spdlog::info("main stop at thread id : {}", ss.str());
}

int main(int argc, char* argv[]) {
    spdlog::info("Application started");
    boost::asio::io_context io_context;
    boost::asio::executor_work_guard<boost::asio::io_context::executor_type> worker(io_context.get_executor());
    ContextPool::instance();
    co_spawn(io_context, stop(io_context), boost::asio::detached);
    io_context.run();
    spdlog::info("Application stopped");
}
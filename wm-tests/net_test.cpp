#include <boost/asio.hpp>
#include <spdlog/spdlog.h>
#include <csignal>
#include "context_pool.h"

using boost::asio::awaitable;
using boost::asio::use_awaitable;
using boost::asio::co_spawn;
using boost::asio::detached;



int main(int argc, char* argv[]) {
	spdlog::info("Application started");
    boost::asio::io_context io_context;
	boost::asio::executor_work_guard<boost::asio::io_context::executor_type> worker(io_context.get_executor());
    ContextPool::instance();
	io_context.run();
	spdlog::info("Application stopped");
	return 0;
}

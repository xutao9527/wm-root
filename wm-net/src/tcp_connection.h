#pragma once

#include <boost/asio.hpp>
#include <atomic>
#include <spdlog/spdlog.h>
#include <thread>

using boost::asio::ip::tcp;
using boost::asio::awaitable;
using boost::asio::use_awaitable;

class tcp_connection
	: public std::enable_shared_from_this<tcp_connection>
{
private:
	tcp::socket socket_;
public:
	tcp_connection(tcp::socket socket)
		: socket_(std::move(socket))
	{
		spdlog::info("New connection from: {}", socket_.remote_endpoint().address().to_string());
	}

	void start()
	{
		co_spawn(socket_.get_executor(), [self = shared_from_this()] { return self->reader(); }, boost::asio::detached);
		co_spawn(socket_.get_executor(), [self = shared_from_this()] { return self->writer(); }, boost::asio::detached);
	}

private:
	awaitable<void> reader()
	{
		try
		{
			for (std::string read_msg;;)
			{
				std::size_t n = co_await boost::asio::async_read_until(socket_,
					boost::asio::dynamic_buffer(read_msg, 1024), '#', use_awaitable);
				std::string line = read_msg.substr(0, n);
				std::stringstream thread_id_converter;
				thread_id_converter << std::this_thread::get_id();
				spdlog::info("read message: {}, thread id {}", line, thread_id_converter.str());
				read_msg.erase(0, n);
			}
		}
		catch (const std::exception& ex)
		{
			spdlog::error("reader error: {}", ex.what());
		}
	}

	awaitable<void> writer()
	{
		try
		{
			boost::asio::steady_timer timer(socket_.get_executor());
			while (socket_.is_open())
			{
				std::string write_msg = "writer content#";
				co_await boost::asio::async_write(socket_,boost::asio::buffer(write_msg), use_awaitable);

				std::stringstream thread_id_converter;
				thread_id_converter << std::this_thread::get_id();
				spdlog::info("write message: {}, thread id {}", write_msg, thread_id_converter.str());

				timer.expires_after(std::chrono::seconds(1));
				co_await timer.async_wait(use_awaitable);
			}
		}
		catch (const std::exception& ex)
		{
			spdlog::error("writer error: {}", ex.what());
		}
	}

};
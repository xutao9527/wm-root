#pragma once

#include <boost/asio.hpp>

class tcp_connection : public std::enable_shared_from_this<tcp_connection>
{
private:
	boost::asio::ip::tcp::socket socket_;

public:
	tcp_connection(boost::asio::ip::tcp::socket socket)
		: socket_(std::move(socket))
	{
		spdlog::debug("tcp_connection constructor...");
	}

	~tcp_connection()
	{
		spdlog::debug("~tcp_connection destructor...");
		socket_.close();
	}

	void start()
	{
		co_spawn(socket_.get_executor(), [self = shared_from_this()]
			{ return self->reader(); }, boost::asio::detached);

	}

	boost::asio::awaitable<void> reader()
	{
		try
		{
			while (socket_.is_open())
			{
				std::string read_msg;
				std::size_t n = co_await boost::asio::async_read_until(socket_, boost::asio::dynamic_buffer(read_msg, 1024), '#', boost::asio::use_awaitable);
				std::string line = read_msg.substr(0, n);
				std::stringstream thread_id_converter;
				thread_id_converter << std::this_thread::get_id();
				spdlog::info("read message: {}, thread id {}", line, thread_id_converter.str());
				read_msg.erase(0, n);
				try
				{
					{
						std::string write_msg = "writer content#";
						co_await boost::asio::async_write(socket_, boost::asio::buffer(write_msg), boost::asio::use_awaitable);
						std::stringstream thread_id_converter;
						thread_id_converter << std::this_thread::get_id();
						spdlog::info("write message: {}, thread id {}", write_msg, thread_id_converter.str());
					}
				}
				catch (const boost::system::system_error& ex)
				{
					if (ex.code() == boost::asio::error::operation_aborted ||
						ex.code() == boost::asio::error::eof)
					{
						spdlog::debug("Client disconnected: {}", socket_.remote_endpoint().address().to_string());
					}
					else
					{
						spdlog::error("writer error: {}", ex.what());
					}
				}
				catch (const std::exception& ex)
				{
					spdlog::debug("writer error: {}", ex.what());
				}

			}
		}
		catch (const boost::system::system_error& ex)
		{
			if (ex.code() == boost::asio::error::operation_aborted ||
				ex.code() == boost::asio::error::eof)
			{
				spdlog::debug("Client disconnected: {}", socket_.remote_endpoint().address().to_string());
			}
			else
			{
				spdlog::error("reader error: {}", ex.what());
			}
		}
		catch (const std::exception& ex)
		{
			spdlog::debug("reader error: {}", ex.what());
		}
	}

	boost::asio::awaitable<void> writer()
	{
		try
		{
			std::string write_msg = "writer content#";
			co_await boost::asio::async_write(socket_, boost::asio::buffer(write_msg), boost::asio::use_awaitable);
			std::stringstream thread_id_converter;
			thread_id_converter << std::this_thread::get_id();
			spdlog::info("write message: {}, thread id {}", write_msg, thread_id_converter.str());
		}
		catch (const boost::system::system_error& ex)
		{
			if (ex.code() == boost::asio::error::operation_aborted ||
				ex.code() == boost::asio::error::eof)
			{
				spdlog::debug("Client disconnected: {}", socket_.remote_endpoint().address().to_string());
			}
			else
			{
				spdlog::error("writer error: {}", ex.what());
			}
		}
		catch (const std::exception& ex)
		{
			spdlog::debug("writer error: {}", ex.what());
		}
		co_return;
	}
};

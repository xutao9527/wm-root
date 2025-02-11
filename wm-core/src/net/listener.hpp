#pragma once

#include <boost/asio.hpp>
#include "conf/app_conf.hpp"
#include "net/tcp_connection.hpp"

class listener : public std::enable_shared_from_this<listener>
{
public:
	listener(boost::asio::io_context &io_context, app_conf &app_conf) : io_context_(io_context), app_conf_(app_conf)
	{
		spdlog::debug("listener");
		endpoint_ = boost::asio::ip::tcp::endpoint(boost::asio::ip::make_address(app_conf_.listen_address), app_conf_.http_port);
		acceptor_ = std::make_unique<boost::asio::ip::tcp::acceptor>(io_context_, endpoint_);
	}
	~listener()
	{
		spdlog::debug("~listener");
	}

	void run()
	{
		co_spawn(io_context_, [self = shared_from_this()]
				 { return self->accept_connections(); }, boost::asio::detached);
	}

protected:
	boost::asio::awaitable<void> accept_connections()
	{
		while (true)
		{
			try
			{
				boost::asio::ip::tcp::socket socket = co_await acceptor_->async_accept();
				std::stringstream thread_id_converter;
				thread_id_converter << std::this_thread::get_id();
				spdlog::info("new connection from: {} at thread id: {}", socket.remote_endpoint().address().to_string(), thread_id_converter.str());
				std::shared_ptr<tcp_connection> connection = std::make_shared<tcp_connection>(std::move(socket));
				connection->start();
			}
			catch (const std::exception &e)
			{
				spdlog::error("accept error: {}", e.what());
			}
		}
	}

private:
	boost::asio::io_context &io_context_;
	app_conf &app_conf_;
	std::unique_ptr<boost::asio::ip::tcp::acceptor> acceptor_;
	boost::asio::ip::tcp::endpoint endpoint_;
};

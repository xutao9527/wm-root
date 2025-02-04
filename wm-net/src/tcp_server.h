#pragma once

#include <boost/asio.hpp>
#include <boost/asio/awaitable.hpp>
#include "tcp_connection.h"

using boost::asio::ip::tcp;
using boost::asio::awaitable;


class tcp_server
{
public:
	tcp_server(boost::asio::io_context& io_context, short port)
		: io_context_(io_context),
		acceptor_(io_context, tcp::endpoint(tcp::v4(), port))
	{
		co_spawn(io_context_, accept_connections(), boost::asio::detached);
	}

private:
	awaitable<void> accept_connections()
	{
		while (true)
		{
			try
			{
				tcp::socket socket = co_await acceptor_.async_accept(use_awaitable);
				std::shared_ptr<tcp_connection> connection = std::make_shared<tcp_connection>(std::move(socket));
				connection->start();
			}
			catch (const std::exception& e)
			{
				spdlog::error("Accept error: {}", e.what());
			}
		}
	}
	boost::asio::io_context& io_context_;
	tcp::acceptor acceptor_;
};
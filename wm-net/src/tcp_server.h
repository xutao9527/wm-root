#pragma once

#include <boost/asio.hpp>
#include <boost/asio/awaitable.hpp>
#include "tcp_connection.h"
#include "context_pool.h"

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
				//auto& context = ContextPool::instance().getContext();
				tcp::socket socket = co_await acceptor_.async_accept(use_awaitable);
				std::stringstream thread_id_converter;
				thread_id_converter << std::this_thread::get_id();
				spdlog::info("client connected at thread id: {}", thread_id_converter.str());
				std::shared_ptr<tcp_connection> connection = std::make_shared<tcp_connection>(std::move(socket));
				connection->start();

			/*	auto& context = ContextPool::instance().getContext();
				std::shared_ptr<tcp_connection> connection = std::make_shared<tcp_connection>(context);
				co_await acceptor_.async_accept(connection->getSocket(), use_awaitable);
				connection->start();
				std::stringstream thread_id_converter;
				thread_id_converter << std::this_thread::get_id();
				spdlog::info("client connected at thread id: {}",  thread_id_converter.str());*/
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
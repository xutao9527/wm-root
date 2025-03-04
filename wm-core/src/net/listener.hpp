#pragma once

#include <boost/asio.hpp>
#include "conf/app_conf.hpp"
#include "net/tcp_connection.hpp"
#include "net/http_connection.hpp"

class listener : public std::enable_shared_from_this<listener>
{
private:
	boost::asio::io_context &io_context_;
	app_conf &app_conf_;
	std::unique_ptr<boost::asio::ip::tcp::acceptor> socket_acceptor_;
	std::unique_ptr<boost::asio::ip::tcp::acceptor> http_acceptor_;
	// std::unique_ptr<boost::asio::ip::tcp::acceptor> ws_acceptor_;

public:
	listener(boost::asio::io_context &io_context, app_conf &app_conf)
		: io_context_(io_context),
		  app_conf_(app_conf)
	{
		spdlog::debug("listener constructor...");
		auto socket_endpoint_ = boost::asio::ip::tcp::endpoint(boost::asio::ip::make_address(app_conf_.listen_address), app_conf_.socket_port);
		socket_acceptor_ = std::make_unique<boost::asio::ip::tcp::acceptor>(io_context_, socket_endpoint_);

		auto http_endpoint_ = boost::asio::ip::tcp::endpoint(boost::asio::ip::make_address(app_conf.listen_address), app_conf.http_port);
		http_acceptor_ = std::make_unique<boost::asio::ip::tcp::acceptor>(io_context, http_endpoint_);

		// auto ws_endpoint_ = boost::asio::ip::tcp::endpoint(boost::asio::ip::make_address(app_conf.listen_address), app_conf.ws_port);
		// ws_acceptor_ = std::make_unique<boost::asio::ip::tcp::acceptor>(io_context, ws_endpoint_);
	}

	~listener()
	{
		spdlog::debug("~listener destructor...");
	}

	void run()
	{
		co_spawn(io_context_, [self = shared_from_this()]
				 { return self->accept_socket_connections(); }, boost::asio::detached);
		co_spawn(io_context_, [self = shared_from_this()]
				 { return self->accept_http_connections(); }, boost::asio::detached);
		// co_spawn(io_context_, [self = shared_from_this()]
		// 		 { return self->accept_ws_connections(); }, boost::asio::detached);
	}

private:
	boost::asio::awaitable<void> accept_socket_connections()
	{
		while (true)
		{
			try
			{
				boost::asio::ip::tcp::socket socket = co_await socket_acceptor_->async_accept();
				std::stringstream thread_id_converter;
				thread_id_converter << std::this_thread::get_id();
				// spdlog::info("new socket connection from: {} at thread id: {}", socket.remote_endpoint().address().to_string(), thread_id_converter.str());
				std::shared_ptr<tcp_connection> connection = std::make_shared<tcp_connection>(std::move(socket));
				connection->start();
			}
			catch (const std::exception &e)
			{
				spdlog::error("socket accept error: {}", e.what());
			}
		}
	}

	boost::asio::awaitable<void> accept_http_connections()
	{
		while (true)
		{
			try
			{
				boost::asio::ip::tcp::socket socket = co_await http_acceptor_->async_accept();
				std::stringstream thread_id_converter;
				thread_id_converter << std::this_thread::get_id();
				spdlog::debug("new http connection from: {} at thread id: {}", socket.remote_endpoint().address().to_string(), thread_id_converter.str());
				std::shared_ptr<http_connection> connection = std::make_shared<http_connection>(std::move(socket), app_conf_);
				connection->start();
			}
			catch (const std::exception &e)
			{
				spdlog::error("http accept error: {}", e.what());
			}
		}
	}

	// boost::asio::awaitable<void> accept_ws_connections()
	// {
	// 	while (true)
	// 	{
	// 		try
	// 		{
	// 			boost::asio::ip::tcp::socket socket = co_await ws_acceptor_->async_accept();
	// 			std::stringstream thread_id_converter;
	// 			thread_id_converter << std::this_thread::get_id();
	// 			spdlog::debug("new websocket connection from: {} at thread id: {}", socket.remote_endpoint().address().to_string(), thread_id_converter.str());
	// 			std::shared_ptr<websocket_connection> connection = std::make_shared<websocket_connection>(std::move(socket));
	// 			connection->start();
	// 		}
	// 		catch (const std::exception &e)
	// 		{
	// 			spdlog::error("ws accept error: {}", e.what());
	// 		}
	// 	}
	// }
};

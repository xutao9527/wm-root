#pragma once

#include <boost/asio.hpp>
#include "conf/app_conf.hpp"

class tcp_server
{
public:
	tcp_server(boost::asio::io_context& io_context, app_conf& app_conf);
	~tcp_server();

protected:
	boost::asio::awaitable<void> accept_connections();

private:
	boost::asio::io_context& io_context_;
	app_conf& app_conf_;
	std::unique_ptr<boost::asio::ip::tcp::acceptor> acceptor_;
	boost::asio::ip::tcp::endpoint endpoint_;
};

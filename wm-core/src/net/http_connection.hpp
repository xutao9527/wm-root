#pragma once

#include <boost/asio.hpp>
#include <boost/beast.hpp>

class http_connection : public std::enable_shared_from_this<http_connection> {
private:
	boost::beast::tcp_stream stream_;

public:
	http_connection(boost::asio::ip::tcp::socket&& socket)
		: stream_(std::move(socket))
	{
		spdlog::debug("http_connection constructor...");
	}

	~http_connection()
	{
		spdlog::debug("~http_connection destructor...");
		stream_.close();
	}

	void start()
	{

	}



};
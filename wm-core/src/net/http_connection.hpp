#pragma once

#include <boost/asio.hpp>
#include <boost/beast.hpp>

class http_connection : public std::enable_shared_from_this<http_connection> {
private:
	boost::beast::tcp_stream stream_;
    boost::beast::flat_buffer buffer_;

public:
	http_connection(boost::asio::ip::tcp::socket&& socket)
		: stream_(std::move(socket))
	{
		spdlog::debug("http_connection constructor...");
	}

	~http_connection()
	{
		spdlog::debug("~http_connection destructor...");
	}

	void start()
	{
        co_spawn(stream_.get_executor(), [self = shared_from_this()]
			{ return self->reader(); }, boost::asio::detached);
	}

    boost::asio::awaitable<void> reader()
    {
        try
        {
            boost::beast::http::request<boost::beast::http::string_body> req;
            co_await boost::beast::http::async_read(stream_, buffer_, req, boost::asio::use_awaitable);
            spdlog::info("http request: {}", req.target());
        }
        catch (const std::exception& e)
        {
            spdlog::error("http reader error: {}", e.what());
        }
    }

};
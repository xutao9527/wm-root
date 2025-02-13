#pragma once

#include <boost/asio.hpp>
#include <boost/beast.hpp>

class websocket_connection : public std::enable_shared_from_this<websocket_connection>
{
private:
	boost::beast::flat_buffer buffer_;
	boost::beast::websocket::stream<boost::beast::tcp_stream> stream_;

public:
	websocket_connection(boost::asio::ip::tcp::socket socket)
		: stream_(std::move(socket))
	{
		spdlog::debug("websocket_connection constructor...");
	}

	~websocket_connection()
	{
		spdlog::debug("websocket_connection destructor...");
	}

	void start(std::optional<boost::beast::http::request<boost::beast::http::string_body>> req = std::nullopt) {
		spdlog::debug("websocket_connection start");
		stream_.set_option(
			boost::beast::websocket::stream_base::timeout::suggested(
				boost::beast::role_type::server));

		stream_.set_option(boost::beast::websocket::stream_base::decorator(
			[](boost::beast::websocket::response_type& res)
			{
				res.set(
					boost::beast::http::field::server,
					std::string(BOOST_BEAST_VERSION_STRING) +
					" websocket-server-coro");
			}));
		co_spawn(stream_.get_executor(), [self = shared_from_this(),req] { return self->reader(req); }, boost::asio::detached);
	}


	boost::asio::awaitable<void> reader(std::optional<boost::beast::http::request<boost::beast::http::string_body>> req = std::nullopt)
	{
		spdlog::debug("websocket_connection reader");
		if (req.has_value()) {
			co_await stream_.async_accept(req.value());
		} else {
			co_await stream_.async_accept();
		}
		while (true)
		{
			auto [ec, _] = co_await stream_.async_read(buffer_, boost::asio::as_tuple);
			if (ec == boost::beast::websocket::error::closed) {
				spdlog::debug("websocket_connection closed");
				co_return;
			}
			if (ec) {
				spdlog::error("websocket_connection error: {}", ec.message());
				co_return;
			}
			auto msg = boost::beast::buffers_to_string(buffer_.data());
			spdlog::debug("websocket_connection message: {}", msg);
			buffer_.consume(buffer_.size());
		}
	}
};

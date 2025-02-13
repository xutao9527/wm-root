#pragma once

#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include "websocket_connection.hpp"

class http_connection : public std::enable_shared_from_this<http_connection>
{
private:
    boost::beast::flat_buffer buffer_;
    boost::beast::tcp_stream stream_;
    

public:
    http_connection(boost::asio::ip::tcp::socket socket)
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
        while (true)
        {
            stream_.expires_after(std::chrono::seconds(1));
            boost::beast::http::request<boost::beast::http::string_body> req;
            co_await boost::beast::http::async_read(stream_, buffer_, req, boost::asio::use_awaitable);

            if(boost::beast::websocket::is_upgrade(req)){
                spdlog::debug("upgrade request to websocket");
                std::shared_ptr<websocket_connection> connection = std::make_shared<websocket_connection>(std::move(stream_.release_socket()));
				connection->start(std::move(req));
                co_return;
            }

            spdlog::debug("http request");
            boost::beast::http::message_generator msg = handle_request(req);
            bool keep_alive = msg.keep_alive();
            co_await boost::beast::async_write(stream_, std::move(msg));
            if (!keep_alive)
            {
                break;
            }
        }
        //stream_.socket().shutdown(boost::asio::ip::tcp::socket::shutdown_send);
    }

    boost::beast::http::message_generator handle_request(boost::beast::http::request<boost::beast::http::string_body> req)
    {
        auto const bad_request =
            [&req](boost::beast::string_view why)
        {
            boost::beast::http::response<boost::beast::http::string_body> res{boost::beast::http::status::bad_request, req.version()};
            res.set(boost::beast::http::field::server, BOOST_BEAST_VERSION_STRING);
            res.set(boost::beast::http::field::content_type, "text/html");
            res.keep_alive(req.keep_alive());
            res.body() = std::string(why);
            res.prepare_payload();
            return res;
        };

        auto const not_found =
            [&req](boost::beast::string_view target)
        {
            boost::beast::http::response<boost::beast::http::string_body> res{boost::beast::http::status::not_found, req.version()};
            res.set(boost::beast::http::field::server, BOOST_BEAST_VERSION_STRING);
            res.set(boost::beast::http::field::content_type, "text/html");
            res.keep_alive(req.keep_alive());
            res.body() = "The resource '" + std::string(target) + "' was not found.";
            res.prepare_payload();
            return res;
        };

        auto const ok =
            [&req](boost::beast::string_view target)
        {
            boost::beast::http::response<boost::beast::http::string_body> res{boost::beast::http::status::ok, req.version()};
            res.set(boost::beast::http::field::server, BOOST_BEAST_VERSION_STRING);
            res.set(boost::beast::http::field::content_type, "text/html");
            res.keep_alive(req.keep_alive());
            res.body() = "The resource '" + std::string(target) + "' was ok.";
            res.prepare_payload();
            return res;
        };
        return ok(req.target());
    }
};
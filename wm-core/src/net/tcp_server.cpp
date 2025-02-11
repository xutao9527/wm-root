#include "tcp_server.hpp"
#include "tcp_connection.hpp"

tcp_server::tcp_server(boost::asio::io_context &io_context, app_conf &app_conf)
    : io_context_(io_context), app_conf_(app_conf)
{
    spdlog::debug("tcp_server");
    endpoint_ = boost::asio::ip::tcp::endpoint(boost::asio::ip::make_address(app_conf_.address), app_conf_.port);
    acceptor_ = std::make_unique<boost::asio::ip::tcp::acceptor>(io_context_, endpoint_);
    co_spawn(io_context_, accept_connections(), boost::asio::detached);
}

tcp_server::~tcp_server()
{
    spdlog::debug("~tcp_server");
}

boost::asio::awaitable<void> tcp_server::accept_connections()
{
    while (true)
    {
        try
        {
            boost::asio::ip::tcp::socket socket = co_await acceptor_->async_accept(boost::asio::use_awaitable);
            std::stringstream thread_id_converter;
            thread_id_converter << std::this_thread::get_id();
            spdlog::debug("New connection from: {} at thread id: {}", socket.remote_endpoint().address().to_string(), thread_id_converter.str());
            std::shared_ptr<tcp_connection> connection = std::make_shared<tcp_connection>(std::move(socket));
            connection->start();
        }
        catch (const std::exception& e)
        {
            spdlog::error("Accept error: {}", e.what());
        }
      
    }
}

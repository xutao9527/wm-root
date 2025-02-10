#include "tcp_server.hpp"

TcpServer::TcpServer(boost::asio::io_context &io_context, ServerConf &server_conf)
    : io_context_(io_context), server_conf_(server_conf),
    acceptor_(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), server_conf_.port))
{
    spdlog::info("TcpServer");
    co_spawn(io_context_, accept_connections(), boost::asio::detached);
}


TcpServer::~TcpServer()

{
    spdlog::info("~TcpServer");
}

boost::asio::awaitable<void> TcpServer::accept_connections()
{
    while (true)
    {
        boost::asio::ip::tcp::socket socket = co_await acceptor_.async_accept(boost::asio::use_awaitable);
        spdlog::info("client connected");
        std::stringstream thread_id_converter;
        thread_id_converter << std::this_thread::get_id();
        spdlog::info("client connected at thread id: {}", thread_id_converter.str());
    }
}

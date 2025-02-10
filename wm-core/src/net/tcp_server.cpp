#include "tcp_server.hpp"

TcpServer::TcpServer(boost::asio::io_context &io_context, ServerConf &server_conf)
    : io_context_(io_context), server_conf_(server_conf)
{
    spdlog::info("TcpServer");
}

TcpServer::~TcpServer()
{
    spdlog::info("~TcpServer");
}

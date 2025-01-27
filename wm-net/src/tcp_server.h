#pragma once

#include <boost/asio.hpp>
#include "tcp_connection.h"

using boost::asio::ip::tcp;


class tcp_server
{
public:
  tcp_server(boost::asio::io_context &io_context, short port)
      : io_context_(io_context),
        acceptor_(io_context, tcp::endpoint(tcp::v4(), port))
  {
    co_spawn(io_context_, accept_connections(), boost::asio::detached);
  }

private:
  // 协程函数，用于接受连接
  boost::asio::awaitable<void> accept_connections()
  {
    while (true)
    {
      try
      {
        auto new_connection = tcp_connection::create(io_context_);
        co_await acceptor_.async_accept(new_connection->socket(), boost::asio::use_awaitable);
        new_connection->start();
      }
      catch (const std::exception& e)
      {
        spdlog::error("Accept error: {}", e.what());
      }
    }
  }

  boost::asio::io_context &io_context_;
  tcp::acceptor acceptor_;
};
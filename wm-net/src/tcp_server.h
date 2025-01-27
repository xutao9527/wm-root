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
    start_accept();
  }

private:
  void start_accept()
  {
    tcp_connection::pointer new_connection =
        tcp_connection::create(io_context_);

    acceptor_.async_accept(new_connection->socket(),
                           std::bind(&tcp_server::handle_accept, this, new_connection,
                                     boost::asio::placeholders::error));
  }

  void handle_accept(tcp_connection::pointer new_connection,
                     const boost::system::error_code &error)
  {
    if (!error)
    {
      new_connection->start();
    }

    start_accept();
  }

  boost::asio::io_context &io_context_;
  tcp::acceptor acceptor_;
};
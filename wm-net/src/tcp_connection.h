#pragma once

#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class tcp_connection
    : public std::enable_shared_from_this<tcp_connection>
{
public:
  typedef std::shared_ptr<tcp_connection> pointer;

  static pointer create(boost::asio::io_context &io_context)
  {
    return pointer(new tcp_connection(io_context));
  }

  tcp::socket &socket()
  {
    return socket_;
  }

  void start()
  {
    std::time_t now = std::time(nullptr);
    char buffer[26];
    ctime_s(buffer, sizeof(buffer), &now);
    message_ = std::string(buffer);

    boost::asio::async_write(socket_, boost::asio::buffer(message_),
                             std::bind(&tcp_connection::handle_write, shared_from_this()));
  }

private:
  tcp_connection(boost::asio::io_context &io_context)
      : socket_(io_context)
  {
  }

  void handle_write()
  {
  }

  tcp::socket socket_;
  std::string message_;
};
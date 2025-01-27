#pragma once

#include <boost/asio.hpp>
#include <atomic>
#include <spdlog/spdlog.h>

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
    // 启动定时器，每秒发送一个自增数字
    counter_ = 0;
    do_write();
    do_read();
  }

private:
  tcp_connection(boost::asio::io_context &io_context)
      : socket_(io_context), timer_(io_context)
  {
  }

  void do_write()
  {
    // 准备消息
    message_ = std::to_string(++counter_) + "\n";
    // 异步发送消息
    boost::asio::async_write(socket_, boost::asio::buffer(message_),
                             std::bind(&tcp_connection::handle_write, shared_from_this()));
  }

  void handle_write()
  {
    // 设置定时器，1秒后再次发送
    timer_.expires_from_now(boost::posix_time::seconds(1));
    timer_.async_wait(std::bind(&tcp_connection::do_write, shared_from_this()));
  }

  void do_read()
  {
    // 异步读取数据
    boost::asio::async_read_until(socket_, input_buffer_, '\n',
                                  std::bind(&tcp_connection::handle_read, shared_from_this(), std::placeholders::_1));
  }

  void handle_read(const boost::system::error_code &error)
  {
    if (!error) {
      // 读取到以 \n 结尾的消息
      std::istream is(&input_buffer_);
      std::string line;
      std::getline(is, line);
      spdlog::info("Received message: {}", line);

      // 继续读取下一条消息
      do_read();
    } else {
      spdlog::error("Read error: {}", error.message());
    }
  }

  tcp::socket socket_;
  boost::asio::deadline_timer timer_;
  boost::asio::streambuf input_buffer_;
  std::string message_;
  std::atomic<int> counter_{0};
};
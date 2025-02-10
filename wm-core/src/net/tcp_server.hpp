#include <boost/asio.hpp>
#include "conf/server_conf.hpp"

class TcpServer
{
public:
    TcpServer(boost::asio::io_context &io_context, ServerConf &server_conf);
    ~TcpServer();

protected:
    boost::asio::awaitable<void> accept_connections();

private:
    boost::asio::io_context &io_context_;
    ServerConf &server_conf_;
    boost::asio::ip::tcp::acceptor acceptor_;
    boost::asio::ip::tcp::endpoint endpoint_;
};

#include <boost/asio.hpp>
#include "conf/server_conf.hpp"

class TcpServer
{
public:
    TcpServer(boost::asio::io_context &io_context, ServerConf &server_conf);

    ~TcpServer();

private:
    boost::asio::io_context &io_context_;
    ServerConf &server_conf_;
};

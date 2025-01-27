#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class TcpServer
{
public:
    TcpServer(boost::asio::io_context &io_context)
        : io_context_(io_context),
          acceptor_(io_context, tcp::endpoint(tcp::v4(), 13))
    {
        start_accept();
    }

private:
    void start_accept()
    {
        
    }

    boost::asio::io_context &io_context_;
    tcp::acceptor acceptor_;
};
#include <spdlog/spdlog.h>
#include <boost/asio.hpp>
#include <tcp_server.h>

int main(int argc, char *argv[])
{
    boost::asio::io_context io_context;
    tcp_server server(io_context, 5678);
    io_context.run();
    return 0;
}
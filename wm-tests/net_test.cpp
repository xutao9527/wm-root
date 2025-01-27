#include <boost/asio.hpp>
#include <iostream>
#include <ctime>
#include <string>

using boost::asio::ip::tcp;

std::string make_daytime_string()
{
    using namespace std;
    time_t now = time(0);
    char buf[26];
    ctime_s(buf, sizeof(buf), &now);  // 使用安全的ctime_s
    return buf;
}

int main(int argc, char *argv[])
{
    try
    {
        boost::asio::io_context io_context;
        tcp::endpoint endpoint(tcp::v4(), 5858);
        tcp::acceptor acceptor(io_context, endpoint);
        for (;;)
        {
            tcp::socket socket(io_context);
            acceptor.accept(socket);
            std::string message = make_daytime_string();
            boost::system::error_code ignored_error;
            boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
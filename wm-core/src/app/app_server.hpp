#include "net/tcp_server.hpp"

class AppServer {
public:
    AppServer();
    ~AppServer();
    void run();
private:
    ServerConf server_conf_;
    std::shared_ptr<TcpServer> tcp_server_;
    std::unique_ptr<boost::asio::io_context> io_context_;
    std::vector<std::thread> threads_;


};


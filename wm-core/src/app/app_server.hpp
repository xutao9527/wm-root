#include "net/tcp_server.hpp"

class AppServer {
public:

    AppServer();
    ~AppServer();
    void run();

private:
    ServerConf serverConf;
    TcpServer tcpServer;
};


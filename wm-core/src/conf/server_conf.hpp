#pragma once

#include <string>

class ServerConf
{
    friend class AppServer;

public:
    ServerConf();
    ~ServerConf();

private:
    std::string address;
    int port;
    int thread_num;
};

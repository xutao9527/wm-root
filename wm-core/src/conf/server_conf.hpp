#pragma once

#include <string>

class ServerConf {
public:

    ServerConf();
    ~ServerConf();

private:
    std::string address;
    int port;
    int thread_num;
};



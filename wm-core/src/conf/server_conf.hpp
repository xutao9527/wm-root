#pragma once

#include <string>

class ServerConf
{
public:
    ServerConf();
    ~ServerConf();

public:
    std::string address;
    int port;
    int thread_num;
};

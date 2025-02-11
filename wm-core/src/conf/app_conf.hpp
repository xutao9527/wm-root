#pragma once

#include <string>

class app_conf
{
public:
    app_conf();
    ~app_conf();

public:
    std::string address;
    int port;
    int thread_num;
};

#pragma once

#include <string>

class app_conf
{
public:
    app_conf();
    ~app_conf();

public:
    std::string listen_address;
    int http_port;
    int ws_port;
    int socket_port;
    int worker_threads;
};

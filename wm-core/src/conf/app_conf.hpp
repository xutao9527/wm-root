#pragma once

#include <string>

class app_conf
{
public:
    app_conf();
    ~app_conf();

public:
    std::string listen_address;
    int socket_port;
    int http_port;
    bool enable_websocket;
    int worker_threads;
};

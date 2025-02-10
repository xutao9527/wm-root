#include "app_server.hpp"

AppServer::AppServer()
{
    spdlog::info("AppServer");
}


AppServer::~AppServer()
{
    spdlog::info("~AppServer");
}


void AppServer::run()
{
    spdlog::info("AppServer run");
}
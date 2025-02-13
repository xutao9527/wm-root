#include "app_conf.hpp"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

app_conf::app_conf()
{
    spdlog::debug("app_conf constructor...");
    try
    {
        boost::property_tree::ptree pt;
        boost::property_tree::ini_parser::read_ini("resources/config.ini", pt);
        listen_address = pt.get<std::string>("ServerSettings.listen_address", "127.0.0.1");
        http_port = pt.get<int>("ServerSettings.http_port", 8080);
        ws_port = pt.get<int>("ServerSettings.ws_port", 8080);
        socket_port = pt.get<int>("ServerSettings.socket_port", 5678);
        worker_threads = pt.get<int>("ServerSettings.worker_threads", 4);
        // spdlog::debug("read config file success: listen_address: {}, http_port: {}, ws_port: {}, socket_port: {}, worker_threads: {}", listen_address, http_port, ws_port, socket_port, worker_threads);
    }
    catch (const std::exception &e)
    {
        spdlog::error("read config file error: {}", e.what());
    }
}

app_conf::~app_conf()
{
    spdlog::debug("~app_conf destructor...");
}

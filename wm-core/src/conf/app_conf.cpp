#include "app_conf.hpp"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

app_conf::app_conf()
{
    spdlog::debug("app_conf");
    try
    {
        
        boost::property_tree::ptree pt;
        boost::property_tree::ini_parser::read_ini("resources/config.ini", pt);
        address = pt.get<std::string>("ServerSettings.address1", "127.0.0.1");
        port = pt.get<int>("ServerSettings.port", 5678);
        worker_threads = pt.get<int>("ServerSettings.worker_threads", 4);
        spdlog::debug("read config file success: address: {}, port: {}, net_worker_threads: {}", address, port, worker_threads);
    }
    catch (const std::exception &e)
    {
        spdlog::error("read config file error: {}", e.what());
    }
}

app_conf::~app_conf()
{
    spdlog::debug("~app_conf");
}

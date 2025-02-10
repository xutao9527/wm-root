#include "server_conf.hpp"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

ServerConf::ServerConf()
{
    try {
        spdlog::info("ServerConf");
        boost::property_tree::ptree pt;
        boost::property_tree::ini_parser::read_ini("resources/config.ini", pt);
        address = pt.get<std::string>("ServerSettings.address1", "127.0.0.1");
        port = pt.get<int>("ServerSettings.port", 5678);
        thread_num = pt.get<int>("ServerSettings.thread_num", 4);
        spdlog::info("read config file success: address: {}, port: {}, thread_num: {}", address, port, thread_num);
    } catch (const std::exception& e) {
        spdlog::error("read config file error: {}", e.what());
    }
}

ServerConf::~ServerConf()
{
    spdlog::info("~ServerConf");
}


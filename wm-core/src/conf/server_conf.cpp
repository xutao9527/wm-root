#include "server_conf.hpp"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

ServerConf::ServerConf()
{
    spdlog::info("ServerConf");
    boost::property_tree::ptree pt;
	boost::property_tree::ini_parser::read_ini("resources/config.ini", pt);
    address = pt.get<std::string>("ServerSettings.address", "127.0.0.1");
    port = pt.get<int>("ServerSettings.port", 5678);
    thread_num = pt.get<int>("ServerSettings.thread_num", 4);
}


ServerConf::~ServerConf()
{
    spdlog::info("~ServerConf");
}


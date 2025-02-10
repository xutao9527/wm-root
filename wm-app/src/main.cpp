#include <spdlog/spdlog.h>
#include <iostream>
#include <app/app_server.hpp>

int main() {
	spdlog::info("start app");
	AppServer appServer;
	appServer.run();
	spdlog::info("end app");
    return 0;
}





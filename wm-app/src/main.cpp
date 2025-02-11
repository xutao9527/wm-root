#include <spdlog/spdlog.h>
#include <iostream>
#include <context/app_context.hpp>

int main() {
	spdlog::set_level(spdlog::level::debug);
	app_context appServer;
	appServer.start();
    return 0;
}





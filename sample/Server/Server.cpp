#include <GenesisNet/GenesisNet.hpp>
#include <iostream>
#include <thread>

int main(int argc, char** argv) {
	genesis::GenesisNet::init();
	genesis::NetServer server;

	std::cout << "Binding server..." << std::endl;
	if(!server.bind(20176, 10, 1)) {
		std::cout << "Could not bind server!" << std::endl;
		std::cin.get();
		return 0;
	}

	std::cout << "Server running on port " << server.getPort() << std::endl;

	while(true) {
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		server.update();
	}

	server.unbind();
	genesis::GenesisNet::shutdown();
	return 0;
}

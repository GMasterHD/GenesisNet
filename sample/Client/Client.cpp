#include <GenesisNet/GenesisNet.hpp>
#include <iostream>
#include <thread>

int main(int argc, char** argv) {
	genesis::GenesisNet::init();
	genesis::NetClient client;

	std::cout << "Binding client..." << std::endl;
	if(!client.bind(1)) {
		std::cout << "Could not bind client socket!" << std::endl;
		std::cin.get();
		return 0;
	}

	std::cout << "Enter the address of your server\n> ";
	std::string str;
	std::getline(std::cin, str);
	genesis::NetAddress address(str);

	std::cout << "Connecting to " << str << "..." << std::endl;
	if(!client.connect(address)) {
		std::cout << "Could not connect to server!" << std::endl;
		std::cin.get();
		return 0;
	}
	std::cout << "Successfully connected!" << std::endl;

	genesis::Packet p;
	p << "Hello World!";
	client.send(p);

	while(true) {
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		client.update();
	}

	client.unbind();
	genesis::GenesisNet::shutdown();
	std::cin.get();
}

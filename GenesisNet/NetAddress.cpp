#include <GenesisNet/NetAddress.hpp>

namespace genesis {
	NetAddress::NetAddress(const std::string& s) {
		if(s.find(":") != std::string::npos) {
			address = s.substr(0, s.find(':'));
			port = std::stoi(s.substr(s.find(':') + 1));
		} else {
			address = s;
			port = 0;
		}
	}
	NetAddress::NetAddress(const std::string& address, uint16_t port) {
		this->address = address;
		this->port = port;
	}
}

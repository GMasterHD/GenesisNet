#include <GenesisNet/NetAddress.hpp>

namespace genesis {
	NetAddress::NetAddress(const std::string& s) {
		auto pos = s.find(":");
		if(pos != std::string::npos) {
			enet_address_set_host(&handle, s.substr(0, pos).c_str());
			handle.port = static_cast<uint16_t>(std::stoi(s.substr(pos + 1)));
		} else {
			enet_address_set_host(&handle, s.substr(0, pos).c_str());
		}
	}
	NetAddress::NetAddress(const std::string& address, uint16_t port) {
		enet_address_set_host(&handle, address.c_str());
		handle.port = port;
	}
}

#pragma once
#include <string>
#include <cstdint>

namespace genesis {
	class NetAddress {
	public:
		NetAddress(const std::string& s);
		NetAddress(const std::string& address, uint16_t port);

		const std::string& getAddress() const { return address; }
		uint16_t getPort() const { return port; }

	private:
		std::string address;
		uint16_t port;
	};
}

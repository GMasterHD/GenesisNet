#pragma once
#include <cstdint>
#include <enet/enet.h>
#include <string>

namespace genesis {
	class NetAddress {
	public:
		NetAddress(const std::string& s);
		NetAddress(const std::string& address, uint16_t port);

		inline void setPort(uint16_t port) { handle.port = port; }
		inline void setAddress(const std::string& address) { enet_address_set_host_ip(&handle, address.c_str()); }

		ENetAddress getHandle() const { return handle; }

	private:
		ENetAddress handle;
	};
}

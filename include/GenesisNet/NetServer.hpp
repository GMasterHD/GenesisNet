#pragma once
#include <cstdint>
#include <enet/enet.h>


namespace genesis {
	class NetServer {
	public:
		NetServer();

		bool bind(uint16_t port, uint32_t slots, uint32_t channels = 1);
		void update();
		void unbind();

		uint16_t getPort() const { return address.port; }

	private:
		bool bound;

		ENetAddress address;
		ENetHost* server;
	};
}

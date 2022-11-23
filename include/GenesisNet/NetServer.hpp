#pragma once
#include <enet/enet.h>
#include <cstdint>

namespace genesis {
	class NetServer {
	public:
		NetServer();

		bool bind(uint16_t port, uint32_t slots, uint32_t channels = 1);
		void update();
		void unbind();

	private:
		bool bound;

		ENetAddress address;
		ENetHost* server;
	};
}

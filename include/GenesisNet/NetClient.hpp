#pragma once
#include <enet/enet.h>
#include <GenesisNet/NetAddress.hpp>

namespace genesis {
	class NetClient {
	public:
		NetClient();

		bool bind(uint32_t channels = 1);
		bool connect(const NetAddress& address);
		void update();
		void disconnect();
		void unbind();

		bool isBound() const { return bound; }
		bool isConnected() const { return connected; }
		const NetAddress getRemoteAddres() const;

	private:
		bool bound, connected;
		
		ENetAddress serverAddress;
		ENetHost* client;
		ENetPeer* peer;

		uint32_t channels;
	};
}

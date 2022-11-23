#include <GenesisNet/NetServer.hpp>
#include <cstdio>

namespace genesis {
	NetServer::NetServer(): bound(false) {
	}

	bool NetServer::bind(uint16_t port, uint32_t slots, uint32_t channels) {
		if(bound) return false;
		
		address.host = ENET_HOST_ANY;
		address.port = port;

		server = enet_host_create(&address, slots, channels, 0, 0);

		if(server == NULL) {
			return false;
		}

		bound = true;
		return true;
	}

	void NetServer::update() {
		ENetEvent e;
		while(enet_host_service(server, &e, 0) > 0) {
			switch(e.type) {
				case ENET_EVENT_TYPE_CONNECT: {
					printf("Connection received!");
					break;
				}
				case ENET_EVENT_TYPE_DISCONNECT: {
					break;
				}
				case ENET_EVENT_TYPE_RECEIVE: {
					printf("A packet of length %u containing %s was received from %s on channel %u.\n",
						e.packet -> dataLength,
						e.packet -> data,
						e.peer -> data,
						e.channelID);
					break;
				}
			}
		}
	}

	void NetServer::unbind() {
		if(!bound) return;
		enet_host_destroy(server);
		bound = false;
	}
}

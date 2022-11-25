#include <GenesisNet/NetServer.hpp>
#include <GenesisNet/Packet.hpp>
#include <cstdio>
#include <iostream>

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
					std::cout << "Connection Received!" << std::endl;
					break;
				}
				case ENET_EVENT_TYPE_DISCONNECT: {
					std::cout << "Disconnection Received!" << std::endl;
					break;
				}
				case ENET_EVENT_TYPE_RECEIVE: {
					printf("A packet of length %u containing %s was received from %s on channel %u.\n",
					       e.packet->dataLength,
					       e.packet->data,
					       e.peer->data,
					       e.channelID);
					
					Packet packet;
					packet.onReceive(e.packet->data, e.packet->dataLength);
					std::string s;
					packet >> s;
					std::cout << "S: " << s << std::endl;
					
					break;
				}
			}
		}
	}

	void NetServer::on(uint32_t packetID, NetServer::PacketReceiveFunction f) {
		if(listeners.find(packetID) == listeners.end()) {
			listeners.insert(std::pair(packetID, std::vector<NetServer::PacketReceiveFunction>()));
		}
		listeners[packetID].push_back(f);
	}

	void NetServer::unbind() {
		if(!bound) return;
		enet_host_destroy(server);
		bound = false;
	}
}

#pragma once
#include <GenesisNet/NetClient.hpp>
#include <iostream>

namespace genesis {
	NetClient::NetClient(): bound(false), connected(false) {
	}

	bool NetClient::bind(uint32_t channels) {
		if(bound) return false;

		client = enet_host_create(NULL, 1, channels, 0, 0);

		if(client == NULL) {
			return false;
		}

		bound = true;
		this->channels = channels;
		return true;
	}
	bool NetClient::connect(const NetAddress& address) {
		serverAddress = address.getHandle();

		peer = enet_host_connect(client, &serverAddress, channels, 0);
		if(peer == NULL) {
			return false;
		}

		ENetEvent e;
		if(enet_host_service(client, &e, 5000) > 0 && e.type == ENET_EVENT_TYPE_CONNECT) {
			connected = true;
			return true;
		} else {
			enet_peer_reset(peer);
			return false;
		}
	}
	void NetClient::send(const Packet& p) {
		ENetPacket* packet = enet_packet_create(p.getData(), p.getSize(), ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 1, packet);
	}
	void NetClient::update() {
		ENetEvent e;
		while(enet_host_service(client, &e, 0) > 0) {
		}
	}
	void NetClient::disconnect() {
	}
	void NetClient::unbind() {
		if(!bound) return;
		enet_host_destroy(client);
	}
}

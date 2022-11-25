#pragma once
#include <GenesisNet/NetAddress.hpp>
#include <GenesisNet/Packet.hpp>
#include <enet/enet.h>

namespace genesis {
	class NetClient {
	public:
		NetClient();

		/**
		 * @brief Bind this socket to the os
		 * @param channels how many channels you want to use (same as server)
		 * @return true successfully bound
		 * @return false failed to bind
		 */
		bool bind(uint32_t channels = 1);
		/**
		 * @brief Send a connection request to a server
		 * @param address the addres
		 * @return true sccessfully connected
		 * @return false failed to connect
		 */
		bool connect(const NetAddress& address);
		/**
		 * @brief Update this peer
		 */
		void update();
		/**
		 * @brief Send a packet to the connected server
		 * @param p the packet
		 */
		void send(const Packet& p);
		/**
		 * @brief Disconnect this client from the server
		 */
		void disconnect();
		/**
		 * @brief Unbind this socket from the os
		 */
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

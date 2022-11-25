#pragma once
#include <cstdint>
#include <enet/enet.h>
#include <functional>
#include <vector>
#include <unordered_map>

namespace genesis {
	class Packet;

	class NetServer {
	public:
		using PacketReceiveFunction = std::function<bool(const Packet&)>;

		NetServer();

		/**
		 * @brief Bind this server to the os
		 * @param port the port the server will be bound on
		 * @param slots the number of clients that can connect
		 * @param channels the number of channels
		 * @return true successfully bound
		 * @return false failed to bind
		 */
		bool bind(uint16_t port, uint32_t slots, uint32_t channels = 1);
		/**
		 * @brief Update the server
		 */
		void update();
		/**
		 * @brief Unbind the server from the os
		 */
		void unbind();

		/**
		 * @brief Registers this function into the event listener
		 * 
		 * @param packetID the packet type
		 * @param f the callback function (return true for handled and false for unahndled)
		 */
		void on(uint32_t packetID, PacketReceiveFunction f);

		uint16_t getPort() const { return address.port; }

	private:
		bool bound;

		ENetAddress address;
		ENetHost* server;

		std::unordered_map<uint32_t, std::vector<PacketReceiveFunction>> listeners;
	};
}

#pragma once
#include "NetAddress.hpp"
#include "NetClient.hpp"
#include "NetServer.hpp"
#include "Packet.hpp"

namespace genesis {
	class GenesisNet {
	public:
		static void init();
		static void shutdown();
	};
}

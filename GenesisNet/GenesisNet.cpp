#include <GenesisNet/GenesisNet.hpp>
#include <enet/enet.h>

namespace genesis {
	void GenesisNet::init() {
		enet_initialize();
	}
	void GenesisNet::shutdown() {
		enet_deinitialize();
	}
}

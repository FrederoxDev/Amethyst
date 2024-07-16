#include <cstddef>
#include "GameConnectionType.hpp"

namespace Social {
	class GameConnectionInfo {
	public:
		ConnectionType mType;
        std::string mHostIpAddress;
        std::byte padding1[4];
        std::string mRakNetGUID;
        uint32_t mHostPort;
        std::byte padding2[20];
        uint64_t mNetherNetID;
	};
}
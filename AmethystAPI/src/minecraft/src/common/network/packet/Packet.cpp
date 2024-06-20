#include <minecraft/src/common/network/packet/Packet.hpp>

#ifdef min
#undef min
#endif

Packet::Packet() {
    mPriority = MEDIUM_PRIORITY;
    mReliability = NetworkPeer::Reliability::ReliableOrdered;
    mClientSubId = SubClientId::PrimaryClient;
    mIsHandled = false;
    mReceiveTimepoint = std::chrono::steady_clock::time_point::min();
    mHandler = 0;
    mCompressible = Compressibility::Compressible;
}

bool Packet::dissallowBatching() {
    return false;
}

bool Packet::isValid() {
    return true;
}
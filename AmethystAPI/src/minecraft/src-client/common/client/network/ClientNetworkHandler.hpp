#pragma once
#include <cstddef>
#include <minecraft/src/common/network/NetEventCallback.hpp>

class Level;

class ClientNetworkHandler : public NetEventCallback {
public:
    /* this + 24  */ std::byte padding24[112];
    /* this + 136 */ Level* mLevel;
};

static_assert(offsetof(ClientNetworkHandler, mLevel) == 136);
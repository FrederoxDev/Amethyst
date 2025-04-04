#pragma once
#include "minecraft/src/common/world/actor/Actor.hpp"

#pragma pack(push, 1)
class Mob : public Actor {
    std::byte _padding1096[416];

public:
    // 1.21.0.3 - 48 89 5C 24 ? 57 48 83 EC ? 48 8B 01 0F B6 DA BA
    void setSprinting(bool isSprinting);

    // virtuals
    void swing(); 
};
#pragma pack(pop)

// 1.21.0.3
static_assert(sizeof(Mob) == 1512);
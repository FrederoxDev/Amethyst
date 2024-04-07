#include "minecraft/src/common/world/actor/Actor.hpp"

class Mob : public Actor {
    std::byte _padding0[424];
};

static_assert(sizeof(Mob) == 1648);
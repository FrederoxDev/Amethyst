#include "minecraft/src/common/world/actor/Actor.h"

class Mob : public Actor {
    std::byte _padding0[424];
};

static_assert(sizeof(Mob) == 1648);
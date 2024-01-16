#include "common/world/actor/Actor.h"

class Mob : public Actor {
    bool _padding0[424];
};

static_assert(sizeof(Mob) == 1648);
#pragma once

#include "common/world/entity/EntityContext.h"
#include "common/world/entity/components/ActorHeadRotationComponent.h"
#include "common/world/entity/components/ActorRotationComponent.h"
#include "common/world/entity/components/StateVectorComponent.h"
#include "common/world/phys/Vec3.h"

class Actor {
private:
    uintptr_t** vtable;

public:
    EntityContext mEntityContext; // this + 8
private:
    bool padding[680];

public:
    StateVectorComponent* mStateVectorComponent; // this + 712
    bool padding1[504];

public:
    Vec3* getPosition();

    template <typename T>
    const T* tryGetComponent() const;

    template <typename T>
    T* tryGetComponent();
};

static_assert(sizeof(Actor) == 1224);
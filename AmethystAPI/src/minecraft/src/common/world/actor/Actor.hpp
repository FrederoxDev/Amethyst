#pragma once
#include "amethyst/Memory.hpp"
#include "minecraft/src/common/world/entity/EntityContext.hpp"
#include "minecraft/src/common/world/entity/components/ActorHeadRotationComponent.hpp"
#include "minecraft/src/common/world/entity/components/ActorRotationComponent.hpp"
#include "minecraft/src/common/world/entity/components/StateVectorComponent.hpp"
#include "minecraft/src/common/world/phys/Vec3.hpp"

class Actor {
private:
    uintptr_t** vtable;

public:
    EntityContext mEntityContext; // this + 8
private:
    std::byte padding[680];

public:
    StateVectorComponent* mStateVectorComponent; // this + 712
    std::byte padding1[504];

public:
    Vec3* getPosition();

    template <typename T>
    const T* tryGetComponent() const
    {
        const auto& registry = mEntityContext.getRegistry();
        return registry.try_get<T>(mEntityContext.mEntity);
    }

    template <typename T>
    T* tryGetComponent()
    {
        auto& registry = mEntityContext.getRegistry();
        return registry.try_get<T>(mEntityContext.mEntity);
    }
};

static_assert(sizeof(Actor) == 1224);
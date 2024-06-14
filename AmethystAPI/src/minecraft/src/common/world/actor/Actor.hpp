#pragma once
#include "amethyst/Memory.hpp"
#include "minecraft/src/common/world/entity/EntityContext.hpp"
#include "minecraft/src/common/world/entity/components/ActorHeadRotationComponent.hpp"
#include "minecraft/src/common/world/entity/components/ActorRotationComponent.hpp"
#include "minecraft/src/common/world/entity/components/StateVectorComponent.hpp"
#include "minecraft/src/common/world/phys/Vec3.hpp"

class Dimension;

class Actor {
public:
    /* this + 0   */ uintptr_t** vtable;
    /* this + 8   */ EntityContext mEntityContext;
    /* this + 32  */ std::byte padding32[544];
    /* this + 584 */ std::weak_ptr<Dimension> mDimension; // moved -8 in 1.21
    /* this + 592 */ std::byte padding592[632];

public:
    Vec3* getPosition();
    const Dimension& getDimensionConst() const;

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
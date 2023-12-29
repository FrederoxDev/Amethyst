#pragma once
#include "minecraft/src/common/world/entity/EntityId.h"
#include "minecraft/src/common/world/entity/EntityContext.h"
#include "amethyst/Memory.h"
#include "minecraft/src/common/world/level/BlockSource.h"
#include "minecraft/src/common/world/level/dimension/Dimension.h"
#include "minecraft/src/common/world/phys/Vec3.h"
#include "minecraft/src/common/world/entity/components/ActorHeadRotationComponent.h"

class Actor {
private:
    uintptr_t** vtable;
public:
    EntityContext mEntityContext; // this + 8
private:
    bool padding[680];

public:
    Vec3 mPos; // this + 712

public:
    template<typename T>
    const T* tryGetComponent() const;
};
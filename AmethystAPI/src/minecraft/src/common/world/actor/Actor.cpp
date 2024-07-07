#include "minecraft/src/common/world/actor/Actor.hpp"
#include "minecraft/src/common/world/entity/components/ActorHeadRotationComponent.hpp"
#include "minecraft/src/common/world/entity/components/ActorRotationComponent.hpp"
#include "minecraft/src/common/world/entity/components/StateVectorComponent.hpp"

Vec3* Actor::getPosition() const
{
    return &mBuiltInComponents.mStateVectorComponent->mPos;
}

Vec2* Actor::getHeadRot() const
{
    return &mBuiltInComponents.mActorRotationComponent->mHeadRot;
}

const Dimension& Actor::getDimensionConst() const
{
    return *mDimension.lock();
}

bool Actor::hasDimension() const
{
    return mDimension.lock() != nullptr;
}

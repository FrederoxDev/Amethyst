#include "minecraft/src/common/world/actor/Actor.hpp"

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

#include "minecraft/src/common/world/actor/Actor.hpp"

Vec3* Actor::getPosition()
{
    return &tryGetComponent<StateVectorComponent>()->mPos;
}
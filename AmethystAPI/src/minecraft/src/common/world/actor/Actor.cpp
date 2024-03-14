#include "minecraft/src/common/world/actor/Actor.h"

Vec3* Actor::getPosition()
{
    return &tryGetComponent<StateVectorComponent>()->mPos;
}
#pragma once
#include "minecraft/src/common/world/phys/Vec2.h"
#include "minecraft/src/common/world/phys/Vec3.h"

struct ActorHeadRotationComponent {
    float yaw;
    float yawLastTick;
};

struct ActorRotationComponent {
    Vec2 headRot;
    Vec2 headRotLastTick;
};

struct StateVectorComponent {
    Vec3 pos;
    Vec3 posLastTick;
    Vec3 velocity;
};
#pragma once
#include "minecraft/src/common/world/phys/Vec2.h"

struct ActorHeadRotationComponent {
    float yaw;
    float yawLastTick;
};

struct ActorRotationComponent {
    Vec2 headRot;
    Vec2 headRotLastTick;
};
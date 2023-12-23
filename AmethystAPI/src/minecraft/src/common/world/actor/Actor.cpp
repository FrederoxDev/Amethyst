#include "minecraft/src/common/world/actor/Actor.h"

Vec3* Actor::getPosition() {
    using function = Vec3* (__thiscall*)(Actor*);
    return reinterpret_cast<function>(this->vtable[23])(this);
}

Vec3* Actor::getHeadLookVector(float dist) {
    using function = Vec3 * (__thiscall*)(Actor*, float);
    return reinterpret_cast<function>(this->vtable[69])(this, dist);
}

Dimension* Actor::getDimension() {
    using function = Dimension*(__thiscall*)(Actor*);
    static auto func = reinterpret_cast<function>(SlideAddress(0x2E7C0F0));
    return func(this);
}
#include "minecraft/src/common/world/actor/Actor.h"

Vec3* Actor::getPosition() {
    using function = Vec3* (__thiscall*)();
    return reinterpret_cast<function>(this->vtable[23])();
}

Dimension* Actor::getDimension() {
    using function = Dimension*(__thiscall*)(Actor*);
    static auto func = reinterpret_cast<function>(SlideAddress(0x2E7C0F0));
    return func(this);
}
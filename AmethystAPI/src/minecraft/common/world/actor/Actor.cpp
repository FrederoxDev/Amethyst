#include "minecraft/common/world/actor/Actor.h"

// const BlockSource* Actor::getDimensionBlockSourceConst() {
//     typedef uintptr_t(__thiscall* _getV24)(void* self);
    
//     // Probably get dimension?
//     static auto func = reinterpret_cast<_getV24>(SlideAddress(0x2E7C0F0));
//     return reinterpret_cast<BlockSource*>(func(this) + 204);
// }

Dimension* Actor::getDimension() {
    using function = Dimension*(__thiscall*)(Actor*);
    static auto func = reinterpret_cast<function>(SlideAddress(0x2E7C0F0));
    return func(this);
}

//const BlockSource* Actor::getDimensionBlockSourceConst() {
//    return getDimension()->getBlockSourceFromMainChunkSource();
//}
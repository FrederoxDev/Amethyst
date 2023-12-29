#include "minecraft/src-client/common/client/game/ClientInstance.h"

BlockSource* ClientInstance::getRegion()
{
    using function = BlockSource*(__thiscall*)(ClientInstance*);
    return reinterpret_cast<function>(this->vtable[26])(this);
}

LocalPlayer* ClientInstance::getLocalPlayer()
{
    using function = LocalPlayer*(__thiscall*)(ClientInstance*);
    return reinterpret_cast<function>(this->vtable[27])(this);
}
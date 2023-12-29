#include "minecraft/src-client/common/client/game/ClientInstance.h"

LocalPlayer* ClientInstance::getLocalPlayer()
{
    using function = LocalPlayer*(__thiscall*)(ClientInstance*);
    return reinterpret_cast<function>(this->vtable[28])(this);
}
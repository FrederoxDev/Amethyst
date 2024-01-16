#include "common/client/game/ClientInstance.h"

class LocalPlayer* ClientInstance::getLocalPlayer()
{
    using function = LocalPlayer*(__thiscall*)(ClientInstance*);
    return reinterpret_cast<function>(this->vtable[28])(this);
}
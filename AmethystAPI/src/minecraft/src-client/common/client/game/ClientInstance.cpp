#include "minecraft/src-client/common/client/game/ClientInstance.h"

// void ClientInstance::requestLeaveGame(char switchScreen, char sync) {
//     using function = void(__thiscall*)(ClientInstance*, char, char);
//     return reinterpret_cast<function>(this->vtable[13])(this, switchScreen, sync);
// }

BlockSource* ClientInstance::getRegion() {
    using function = BlockSource*(__thiscall*)(ClientInstance*);
    return reinterpret_cast<function>(this->vtable[27])(this);
}

LocalPlayer* ClientInstance::getLocalPlayer()
{
    using function = LocalPlayer*(__thiscall*)(ClientInstance*);
    return reinterpret_cast<function>(this->vtable[28])(this);
}
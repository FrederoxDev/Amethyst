#include "minecraft/src-client/common/client/game/ClientInstance.hpp"

// void ClientInstance::requestLeaveGame(char switchScreen, char sync) {
//     using function = void(__thiscall*)(ClientInstance*, char, char);
//     return reinterpret_cast<function>(this->vtable[13])(this, switchScreen, sync);
// }

BlockSource* ClientInstance::getRegion() {
    using function = decltype(&ClientInstance::getRegion);
    auto func = std::bit_cast<function>(this->vtable[28]);
    return (this->*func)();
}

LocalPlayer* ClientInstance::getLocalPlayer()
{
    using function = decltype(&ClientInstance::getLocalPlayer);
    auto func = std::bit_cast<function>(this->vtable[29]);
    return (this->*func)();
}
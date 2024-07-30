#include "LocalPlayer.hpp"

void LocalPlayer::setSprinting(bool isSprinting)
{
    using function = decltype(&LocalPlayer::setSprinting);
    auto func = std::bit_cast<function>(this->vtable[153]);
    return (this->*func)(isSprinting);
}
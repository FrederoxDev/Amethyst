#include "Mob.hpp"

void Mob::setSprinting(bool isSprinting)
{
    using function = decltype(&Mob::setSprinting);
    auto func = std::bit_cast<function>(this->vtable[153]);
    return (this->*func)(isSprinting);
}
#include "Mob.hpp"

void Mob::setSprinting(bool isSprinting)
{
    using function = decltype(&Mob::setSprinting);
    auto func = std::bit_cast<function>(this->vtable[153]);
    return (this->*func)(isSprinting);
}

void Mob::swing() {
    using function = decltype(&Mob::swing);
    auto func = std::bit_cast<function>(this->vtable[117]);
    return (this->*func)();
}
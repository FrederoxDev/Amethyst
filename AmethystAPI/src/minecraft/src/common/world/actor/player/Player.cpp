#include <minecraft/src/common/world/actor/player/Player.hpp>

void Player::prepareRegion(ChunkSource& cs)
{
    using function = decltype(&Player::prepareRegion);
    static auto func = std::bit_cast<function>(this->vtable[190]);
    return (this->*func)(cs);
}
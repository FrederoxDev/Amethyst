#include <minecraft/src/common/world/actor/player/Player.hpp>
#include <minecraft/src/common/world/actor/player/PlayerInventory.hpp>

void Player::prepareRegion(ChunkSource& cs)
{
    using function = decltype(&Player::prepareRegion);
    static auto func = std::bit_cast<function>(this->vtable[190]);
    return (this->*func)(cs);
}

const PlayerInventory& Player::getSupplies() const
{
    return *this->playerInventory;
}

const ItemStack& Player::getSelectedItem() const
{
    return playerInventory->getSelectedItem();
}

PlayerEventCoordinator& Player::getPlayerEventCoordinator() {
    using function = decltype(&Player::getPlayerEventCoordinator);
    auto func = std::bit_cast<function>(this->vtable[244]);
    return (this->*func)();
}

void Player::sendInventoryTransaction(const InventoryTransaction& transaction)
{
    using function = decltype(&Player::sendInventoryTransaction);
    auto func = std::bit_cast<function>(this->vtable[242]);
    return (this->*func)(transaction);
}

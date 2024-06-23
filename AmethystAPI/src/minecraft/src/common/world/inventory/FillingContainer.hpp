#pragma once
#include "minecraft/src/common/world/Container.hpp"

class ListTag;
class SemVersion;
class Level;

class FillingContainer : public Container {
public:
    std::vector<ItemStack> mItems;
    Player* mPlayer;

public:
    FillingContainer(Player* player, int size, ContainerType type);
    virtual ~FillingContainer() = default;

public:
    void serverInitItemStackIds(int, int, std::function<void(int, const ItemStack&)>) override;
    const ItemStack& getItem(int slot) const override;
    void setItem(int slot, const ItemStack& item) override;
    void setItemWithForceBalance(int, const ItemStack&, bool) override;
    void removeItem(int, int) override;
    int getContainerSize() const override;
    int getMaxStackSize() const override;
    void startOpen(Player&) override;
    virtual void add(ItemStack& item);
    virtual bool canAdd(const ItemStack& item);
    virtual void clearSlot(int slot);
    virtual void clearInventory(int size);
    virtual void load(const ListTag& tag, const SemVersion& version, Level&);
};

// 1.21.0.3
static_assert(sizeof(FillingContainer) - sizeof(Container) == 32);
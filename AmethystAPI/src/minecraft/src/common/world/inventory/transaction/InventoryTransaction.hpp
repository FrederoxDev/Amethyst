#pragma once
#include <unordered_map>
#include <vector>
#include "minecraft/src/common/world/inventory/transaction/InventorySource.hpp"
#include "minecraft/src/common/world/inventory/transaction/InventoryTransactionItemGroup.hpp"
#include "minecraft/src/common/world/inventory/transaction/InventoryAction.hpp"


class InventoryTransaction {
public:
    std::unordered_map<InventorySource, std::vector<InventoryAction>> mActions;
    std::vector<InventoryTransactionItemGroup> mContents;

    void addAction(const InventoryAction& action)
    {
        using function = decltype(&InventoryTransaction::addAction);
        static auto func = std::bit_cast<function>(SigScan("48 89 5C 24 ? 48 89 74 24 ? 55 57 41 54 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 4C 8B F2 4C 8B F9"));
        (this->*func)(action);
    }
};
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
};
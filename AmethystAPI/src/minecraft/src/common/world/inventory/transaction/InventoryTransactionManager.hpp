#pragma once
#include <memory>
#include <vector>
#include "minecraft/src/common/world/inventory/transaction/InventoryTransaction.hpp"
#include "minecraft/src/common/world/inventory/transaction/InventoryAction.hpp"

class Player;

class InventoryTransactionManager { 
public:
    Player* mPlayer; 
    std::unique_ptr<InventoryTransaction> mCurrentTransaction;
    std::vector<InventoryAction> mExpectedActions;
    bool mEnableLogs; 

    void addExpectedAction(const InventoryAction& action)
    {
        this->mExpectedActions.push_back(action);
    }
};

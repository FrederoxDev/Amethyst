#pragma once
#include <cstdint>
#include "minecraft/src/common/world/inventory/transaction/InventoryTransaction.hpp"

class ComplexInventoryTransaction {
public:
    enum class Type {
        NormalTransaction = 0x0,
        InventoryMismatch = 0x1,
        ItemUseTransaction = 0x2,
        ItemUseOnEntityTransaction = 0x3,
        ItemReleaseTransaction = 0x4,
    };

    uint64_t vtable;
    Type mType;
    InventoryTransaction mTransaction;
};
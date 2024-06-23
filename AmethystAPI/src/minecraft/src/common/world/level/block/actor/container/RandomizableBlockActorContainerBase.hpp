#pragma once
#include "minecraft/src/common/world/level/block/actor/BlockActor.hpp"

class RandomizableBlockActorContainerBase : public BlockActor {
public:
    std::string mLootTable;
    int mLootTableSeed;

public:
    RandomizableBlockActorContainerBase(BlockActorType type, const std::string& id, const BlockPos& position);
    virtual ~RandomizableBlockActorContainerBase() = default;

public:
    void load(Level& a2, const CompoundTag& tag, DataLoadHelper& a4) override;
    bool save(CompoundTag& tag) const override;
    void eraseLootTable() override;
};

// 1.21.0.3
static_assert(sizeof(RandomizableBlockActorContainerBase) - sizeof(BlockActor) == 40);
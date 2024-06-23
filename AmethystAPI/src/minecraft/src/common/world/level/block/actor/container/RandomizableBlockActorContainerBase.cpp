#include "RandomizableBlockActorContainerBase.hpp"

// Implemented from the time that the game was created lmao (seriously, this class didn't change at all xD)
RandomizableBlockActorContainerBase::RandomizableBlockActorContainerBase(BlockActorType type, const std::string& id, const BlockPos& position) : BlockActor(type, position, id),
    mLootTable(""),
    mLootTableSeed(0)
{}


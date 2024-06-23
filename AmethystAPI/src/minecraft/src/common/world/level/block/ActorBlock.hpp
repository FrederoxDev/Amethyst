#pragma once
#include "BlockLegacy.hpp"

#pragma pack(push, 1)
class ActorBlock : public BlockLegacy {
public:
    ActorBlock(const std::string& nameId, short id, const Material& material) : BlockLegacy(nameId, id, material) {}
    virtual ~ActorBlock() = default;
    
public:
    void neighborChanged(BlockSource& region, const BlockPos& pos, const BlockPos& neighborPos) const override;
    void triggerEvent(BlockSource& region, const BlockPos& pos, int b0, int b1) const override;
};
#pragma pack(pop)
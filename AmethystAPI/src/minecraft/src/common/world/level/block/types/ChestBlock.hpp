#pragma once
#include "minecraft/src/common/world/level/block/ActorBlock.hpp"

#pragma pack(push, 1)
class ChestBlock : public ActorBlock {
public:
    enum class ChestType : int {
        Default = 0,
        Trapped = 1,
        Other = 2
    };
    
public:
    ChestType mChestType;
    
public:
    ChestBlock(const std::string& nameId, short id, ChestType type, MaterialType materialType);
    
public:
    virtual ~ChestBlock() = default;
    bool canProvideSupport(const Block& block, unsigned char face, BlockSupportType type) const override;
    bool isContainerBlock() const override;
    bool isSignalSource() const override;
    bool shouldConnectToRedstone(BlockSource&, const BlockPos&, Direction::Type) const override;
    bool dispense(BlockSource& region, Container& container, int slot, const Vec3& pos, unsigned char face) const override;
    void onMove(BlockSource& region, const BlockPos& from, const BlockPos& to) const override;
    bool detachesOnPistonMove(BlockSource&, BlockPos const&) const override;
    void setupRedstoneComponent(BlockSource& region, const BlockPos& pos) const override;
    bool breaksFallingBlocks(const Block& block, BaseGameVersion version) const override;
    bool getSecondPart(const IConstBlockSource&, const BlockPos&, BlockPos&) const override;
    bool hasComparatorSignal() const override;
    int getComparatorSignal(BlockSource& region, const BlockPos& pos, const Block& block, unsigned char dir) const override;
    unsigned char getMappedFace(unsigned char face, const Block& block) const override;
    BlockLegacy& init() override;
    void onRemove(BlockSource& region, const BlockPos& pos) const override;
    void onPlace(BlockSource& region, const BlockPos& pos) const override;
    bool isInteractive() const override;
    bool use(Player& player, const BlockPos& pos, unsigned char face) const override;
};
#pragma pack(pop)

// 1.21.0.3
// static_assert(sizeof(ChestBlock) == 992); its fun, the editor doesn't complain, the compiler complains but the game works file xD
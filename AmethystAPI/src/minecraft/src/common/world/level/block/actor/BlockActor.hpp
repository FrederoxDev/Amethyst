#pragma once
#include <string>
#include <vector>
#include <memory>

#include <minecraft/src/common/world/phys/AABB.hpp>
#include <minecraft/src-deps/core/utility/NonOwnerPointer.hpp>
#include <minecraft/src/common/world/level/BlockPos.hpp>
#include <minecraft/src/common/world/level/block/Block.hpp>
#include <minecraft/src/common/world/actor/ActorTerrainInterlockData.hpp>
#include <minecraft/src/common/world/level/block/actor/BlockActorRendererId.hpp>
#include <minecraft/src/common/network/packet/BlockActorDataPacket.hpp>
#include <gsl/gsl>

// Auto-generated: Unknown complete types
class UIProfanityContext {}; 

// Auto-generated: Forward declarations
class Level; 
class CompoundTag; 
class DataLoadHelper; 
class BlockSource; 
class BlockActor; 
class BlockPos; 
class IConstBlockSource; 
class Player; 
class BlockLegacy;

class BlockActor {
public:
    /* this + 8   */ int mTickCount;
    /* this + 16  */ const Block* mBlock;
    /* this + 24  */ float mDestroyTimer;
    /* this + 28  */ Vec3 mDestroyDirection;
    /* this + 40  */ float mDestroyProgress;
    /* this + 44  */ BlockPos mPosition;
    /* this + 56  */ AABB mBB;
    /* this + 80  */ const BlockActorType mType;
    /* this + 84  */ BlockActorRendererId mRendererId;
    /* this + 88  */ std::string mCustomName;
    /* this + 120 */ std::string mFilteredCustomName;
    /* this + 152 */ int mRepairCost;
    /* this + 156 */ bool mClientSideOnly;
    /* this + 157 */ bool mIsMovable;
    /* this + 158 */ bool mSaveCustomName;
    /* this + 159 */ bool mCanRenderCustomName;
    /* this + 160 */ const float signShadowRadius;
    /* this + 168 */ ActorTerrainInterlockData mTerrainInterlockData;
    /* this + 192 */ bool mChanged;

public:
	virtual ~BlockActor();
	virtual void load(Level& a2, const CompoundTag& tag, DataLoadHelper& a4);
	virtual bool save(CompoundTag& tag) const;
	virtual bool saveItemInstanceData(CompoundTag&) const;
	virtual void setUgcStrings(CompoundTag&, const std::vector<std::string>&) const;
	virtual void loadBlockData(const CompoundTag& a2, BlockSource& a3, DataLoadHelper& a4);
	virtual void onCustomTagLoadDone(BlockSource& a2);
	virtual void tick(BlockSource& region);
	virtual void onChanged(BlockSource& a2);
	virtual bool isMovable(BlockSource& a2);
	virtual bool isCustomNameSaved();

	/*
	Called whenever the BlockActor is spawned in the world
	- Called on both client and server side
	*/
	virtual void onPlace(BlockSource& a2);

    virtual void onMove();
	virtual void onRemoved(BlockSource& a2);
	virtual bool isPreserved(BlockSource& a2) const;
	virtual bool shouldPreserve(BlockSource& a2);
	virtual void triggerEvent(int a2, int a3) const;
	virtual void clearCache();
	virtual void onNeighborChanged(BlockSource& region, BlockPos const& position) const;
	virtual float getShadowRadius(BlockSource& a2) const;
	virtual bool hasAlphaLayer() const;
	virtual BlockActor* getCrackEntity(BlockSource& a2, const BlockPos& a3);
	virtual AABB getCollisionShape(const IConstBlockSource& a3) const;
	virtual void getDebugText(std::vector<std::string>& outputInfo, const BlockPos& debugPos);
	virtual const std::string& getCustomName() const;
	virtual const std::string& getFilteredCustomName(const gsl::not_null<Bedrock::NonOwnerPointer<UIProfanityContext>>&);
	virtual std::string getName() const;
	virtual void setCustomName(const std::string& name);
	virtual std::string getImmersiveReaderText(BlockSource&);
	virtual int getRepairCost() const;
	virtual void _unknown_30();
	virtual void _unknown_31();
	virtual void _unknown_32();
	virtual void _unknown_33();
	virtual void eraseLootTable();
	virtual void _unknown_35();
	virtual void _unknown_36();
	virtual std::vector<std::string> getUgcStrings(const CompoundTag&) const;
	virtual void _unknown_38();
	virtual void _unknown_39();

protected:
	virtual std::unique_ptr<BlockActorDataPacket> _getUpdatePacket(BlockSource& a2);
	virtual void _onUpdatePacket(const CompoundTag& a2, BlockSource& a3);
	virtual bool _playerCanUpdate(const Player& fromPlayer) const;

public:
	// 1.20.71.1 - 48 83 EC ? 45 33 C9 0F 29 34 24
	BlockActor(BlockActorType type, const BlockPos& pos, const std::string& id);
        void moveTo(const BlockPos& pos);
};

static_assert(sizeof(BlockActor) == 200);

class BlockActorFactory {
public:
    static std::shared_ptr<BlockActor> createBlockEntity(BlockActorType type, const BlockPos& pos, const BlockLegacy& block);
};
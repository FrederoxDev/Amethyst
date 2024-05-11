#pragma once
#include <functional>
#include <optional>
#include <string>
#include <vector>
#include <memory>

#include <minecraft/src-deps/core/math/Color.hpp>
#include <minecraft/src-deps/core/string/StringHash.hpp>
#include <minecraft/src-deps/core/utility/optional_ref.hpp>
#include <minecraft/src/common/resources/BaseGameVersion.hpp>
#include <minecraft/src/common/world/phys/Vec3.hpp>
#include <minecraft/src/common/world/level/block/components/BlockComponentStorage.hpp>
#include <minecraft/src/common/world/item/ItemStackBase.hpp>
#include <minecraft/src/common/world/item/ItemInstance.hpp>
#include <minecraft/src/common/CommonTypes.hpp>
#include <minecraft/src/common/world/level/material/Material.hpp>
#include <minecraft/src/common/world/phys/AABB.hpp>
#include <minecraft/src/common/world/level/block/BlockRenderLayer.hpp>
#include <minecraft/src/common/world/level/block/BlockState.hpp>

// Auto-generated: Unknown complete types
class BlockActor {};
class HitResult {};
enum ShapeType {};
class GetCollisionShapeInterface {};
enum BlockSupportType {};
namespace Direction {
enum Type {};
}
enum BlockProperty {};
enum FertilizerType {};
enum Flip {};

// Auto-generated: Forward declarations
class BlockPos;
class Block;
class BlockSource;
class IConstBlockSource;
class CopperBehavior;
class Actor;
class Container;
struct UpdateEntityAfterFallOnInterface;
class BlockLegacy;
struct ActorBlockSyncMessage;
class ItemStack;
class Player;
class Randomize;
class BlockItem;
class MobSpawnerData;
class SpawnConditions;
struct BlockGraphicsModeChangeContext;
class Random;
class Experiments;
class EntityContext;
struct ResourceDropsContext;


// other types
enum class FlameOdds : char {
    INSTANT = 60,
    EASY = 30,
    MEDIUM = 15,
    HARD = 5,
    NEVER = 0
};

enum class BurnOdds : char {
    INSTANT = 100,
    EASY = 60,
    MEDIUM = 20,
    HARD = 5,
    NEVER = 0
};

// struct_size = 944 is_virtual = True
//     hide_vtable = True
// #(Type, Name, Size(in bytes), Offset(in bytes))
//     struct
//     = [("BurnOdds", "mBurnOdds", 1, 95),
//        ("FlameOdds", "mFlameOdds", 1, 94),
//        ("bool", "mIsVanilla", 1, 544),
//        ("const Material&", "mMaterial", 8, 296),
//        ("unsigned short", "mID", 2, 422),
//        ("BaseGameVersion", "mMinRequiredBaseGameVersion", 120, 424),
//        ("unsigned char", "mLightEmission", 1, 374),
//        ("unsigned char", "mLightBlock", 1, 373),
//        ("mce::Color", "mMapColor", 16, 396)]

#pragma pack(push, 1)
class BlockLegacy : public BlockComponentStorage {
public:
    class AlteredStateCollection {
    public:
        std::reference_wrapper<const BlockState> mBlockState;

    public:
        virtual std::optional<int> getState(const BlockLegacy& blockLegacy, int blockData) const = 0;
        virtual const Block* setState(const BlockLegacy&, int, int) const = 0;
        virtual ~AlteredStateCollection() = default;
    };

public:
    /* this + 40  */ std::byte padding40[54];
    /* this + 94  */ FlameOdds mFlameOdds;
    /* this + 95  */ BurnOdds mBurnOdds;
    /* this + 96  */ std::byte padding96[200];
    /* this + 296 */ const Material& mMaterial;
    /* this + 304 */ std::byte padding304[69];
    /* this + 373 */ unsigned char mLightBlock;
    /* this + 374 */ unsigned char mLightEmission;
    /* this + 375 */ std::byte padding375[13];
    /* this + 388 */ float mDestroySpeed;
    /* this + 392 */ float mExplosionResistance;
    /* this + 396 */ mce::Color mMapColor;
    /* this + 412 */ std::byte padding412[10];
    /* this + 422 */ unsigned short mID;
    /* this + 424 */ BaseGameVersion mMinRequiredBaseGameVersion;
    /* this + 544 */ bool mIsVanilla;
    /* this + 545 */ std::byte padding545[135];
    /* this + 680 */ std::map<uint64_t, BlockStateInstance> mStates;
    /* this + 696 */ std::unordered_map<HashedString, uint64_t> mStateNameMap;
    /* this + 760 */ std::byte padding760[192];
    /* this + 952 */ std::vector<std::shared_ptr<BlockLegacy::AlteredStateCollection>> mAlteredStateCollections;
    /* this + 976 */ std::byte padding976[8];

    // aint that lovely, they're friends now
    friend class Block;

public:
    virtual ~BlockLegacy();
    virtual std::shared_ptr<BlockActor> newBlockEntity(const BlockPos& pos, const Block& block) const;
    virtual const Block* getNextBlockPermutation(const Block& currentBlock) const;
    virtual bool waterSpreadCausesSpawn() const;
    virtual HitResult clip(const Block&, const BlockSource&, const BlockPos&, const Vec3&, const Vec3&, ShapeType, optional_ref<const GetCollisionShapeInterface>) const;
    virtual AABB getCollisionShape(const Block&, const IConstBlockSource&, const BlockPos&, optional_ref<const GetCollisionShapeInterface>) const;
    virtual bool getCollisionShapeForCamera(AABB&, const Block&, const IConstBlockSource&, const BlockPos&) const;
    virtual bool addCollisionShapes(const Block&, const IConstBlockSource&, const BlockPos&, const AABB*, std::vector<AABB>&, optional_ref<const GetCollisionShapeInterface>) const;
    virtual void addAABBs(const Block&, const IConstBlockSource&, const BlockPos&, const AABB*, std::vector<AABB>&) const;
    virtual const AABB& getOutline(const Block&, const IConstBlockSource&, const BlockPos&, AABB&) const;
    virtual const AABB& getVisualShapeInWorld(const Block&, const IConstBlockSource&, const BlockPos&, AABB&) const;
    virtual const AABB& getVisualShape(const Block&, AABB&) const;
    virtual const AABB& getUIShape(const Block& block, AABB& bufferAABB) const;
    virtual bool getLiquidClipVolume(const Block&, BlockSource&, const BlockPos&, AABB&) const;
    virtual bool isObstructingChests(BlockSource& region, const BlockPos& pos, const Block& thisBlock) const;
    virtual Vec3 randomlyModifyPosition(const BlockPos& pos, int& seed) const;
    virtual Vec3 randomlyModifyPosition(const BlockPos& pos) const;
    virtual void onRedstoneUpdate(BlockSource& region, const BlockPos& pos, int strength, bool isFirstTime) const;
    virtual void onLightningHit(BlockSource& region, const BlockPos& pos) const;
    virtual bool liquidCanFlowIntoFromDirection(unsigned char, std::function<const Block&>(const BlockPos&));
    virtual void _unknown_20();
    virtual void _unknown_21();
    virtual void _unknown_22();
    virtual bool canProvideSupport(const Block& block, unsigned char face, BlockSupportType type) const;
    virtual bool canProvideMultifaceSupport(const Block& block, unsigned char face) const;
    virtual bool canConnect(const Block& otherBlock, unsigned char toOther, const Block& thisBlock) const;
    virtual const CopperBehavior* tryGetCopperBehavior() const;
    virtual void _unknown_27();
    virtual void _unknown_28();
    virtual void _unknown_29();
    virtual void _unknown_30();
    virtual void _unknown_31();
    virtual bool isWaterBlocking() const;
    virtual void _unknown_33();
    virtual void _unknown_34();
    virtual void _unknown_35();
    virtual void _unknown_36();
    virtual bool isStairBlock() const;
    virtual bool isSlabBlock() const;
    virtual bool isDoubleSlabBlock() const;
    virtual void _unknown_40();
    virtual void _unknown_41();
    virtual void _unknown_42();
    virtual void _unknown_43();
    virtual void _unknown_44();
    virtual void _unknown_45();
    virtual void _unknown_46();
    virtual bool canBeOriginalSurface() const;
    virtual void _unknown_48();
    virtual bool isValidAuxValue(int value) const;
    virtual bool canFillAtPos(BlockSource& region, const BlockPos& pos, const Block& block) const;
    virtual const Block& sanitizeFillBlock(const Block&) const;
    virtual void onFillBlock(BlockSource& region, const BlockPos& pos, const Block& block) const;
    virtual int getDirectSignal(BlockSource& region, const BlockPos& pos, int dir) const;
    virtual void _unknown_54();
    virtual void _unknown_55();
    virtual bool canContainLiquid() const;
    virtual std::optional<HashedString> getRequiredMedium() const;
    virtual bool shouldConnectToRedstone(BlockSource&, const BlockPos&, Direction::Type) const;
    virtual void handlePrecipitation(BlockSource& region, const BlockPos& pos, float downfallAmount, float temperature) const;
    virtual bool canBeUsedInCommands(const BaseGameVersion& baseGameVersion) const;
    virtual bool checkIsPathable(Actor& entity, const BlockPos& lastPathPos, const BlockPos& pathPos) const;
    virtual bool shouldDispense(BlockSource& region, Container& container) const;
    virtual bool dispense(BlockSource& region, Container& container, int slot, const Vec3& pos, unsigned char face) const;
    virtual void transformOnFall(BlockSource& region, const BlockPos& pos, Actor* entity, float fallDistance) const;
    virtual void _unknown_65();
    virtual void onMove(BlockSource& region, const BlockPos& from, const BlockPos& to) const;
    virtual void _unknown_67();
    virtual void movedByPiston(BlockSource& region, const BlockPos& pos) const;
    virtual void onStructureBlockPlace(BlockSource& region, const BlockPos& pos) const;
    virtual void onStructureNeighborBlockPlace(BlockSource& region, const BlockPos& pos) const;
    virtual void setupRedstoneComponent(BlockSource& region, const BlockPos& pos) const;
    virtual BlockProperty getRedstoneProperty(BlockSource& region, const BlockPos& pos) const;
    virtual void updateEntityAfterFallOn(const BlockPos& pos, UpdateEntityAfterFallOnInterface& entity) const;
    virtual void _unknown_74();
    virtual bool isPreservingMediumWhenPlaced(const BlockLegacy* medium) const;
    virtual bool isFilteredOut(BlockRenderLayer heldItemRenderLayer) const;
    virtual bool canRenderSelectionOverlay(BlockRenderLayer) const;
    virtual bool ignoreEntitiesOnPistonMove(const Block& block) const;
    virtual bool onFertilized(BlockSource& region, const BlockPos& pos, Actor* actor, FertilizerType fType) const;
    virtual bool mayConsumeFertilizer(BlockSource& region) const;
    virtual bool canBeFertilized(BlockSource& region, const BlockPos& pos, const Block& aboveBlock) const;
    virtual bool mayPick() const;
    virtual bool mayPick(const BlockSource& region, const Block& block, bool liquid) const;
    virtual bool mayPlace(BlockSource& region, const BlockPos& pos, unsigned char face) const;
    virtual bool mayPlace(BlockSource& region, const BlockPos& pos) const;
    virtual bool mayPlaceOn(BlockSource& region, const BlockPos& pos) const;
    virtual bool tryToPlace(BlockSource& region, const BlockPos& pos, const Block& block, const ActorBlockSyncMessage* syncMsg) const;
    virtual bool tryToTill(BlockSource& region, const BlockPos& pos, Actor& entity, ItemStack& item) const;
    virtual bool breaksFallingBlocks(const Block& block, BaseGameVersion version) const;
    virtual void destroy(BlockSource& region, const BlockPos& pos, const Block& block, Actor* entitySource) const;
    virtual bool getIgnoresDestroyPermissions(Actor& entity, const BlockPos& pos) const;
    virtual void neighborChanged(BlockSource& region, const BlockPos& pos, const BlockPos& neighborPos) const;
    virtual bool getSecondPart(const IConstBlockSource&, const BlockPos&, BlockPos&) const;
    virtual const Block* playerWillDestroy(Player& player, const BlockPos& pos, const Block& block) const;
    virtual ItemInstance asItemInstance(const Block& block, const BlockActor* a4) const;
    virtual void trySpawnResourcesOnExplosion(BlockSource&, const BlockPos&, const Block&, Randomize&, float) const;
    virtual const Block& getPlacementBlock(const Actor&, const BlockPos&, unsigned char, const Vec3&, int) const;
    virtual int calcVariant(BlockSource& region, const BlockPos& pos, const mce::Color& baseColor) const;
    virtual bool isAttachedTo(BlockSource& region, const BlockPos& pos, BlockPos& outAttachedTo) const;
    virtual bool attack(Player* player, const BlockPos& pos) const;
    virtual bool shouldTriggerEntityInside(BlockSource& region, const BlockPos& pos, Actor& entity) const;
    virtual bool canBeBuiltOver(BlockSource& region, const BlockPos& pos, const BlockItem& newItem) const;
    virtual bool canBeBuiltOver(BlockSource& region, const BlockPos& pos) const;
    virtual void triggerEvent(BlockSource& region, const BlockPos& pos, int b0, int b1) const;
    virtual void executeEvent(BlockSource& region, const BlockPos& pos, const Block& block, const std::string& eventName, Actor& sourceEntity) const;
    virtual const MobSpawnerData* getMobToSpawn(const SpawnConditions& conditions, BlockSource& region) const;
    virtual bool shouldStopFalling(Actor& entity) const;
    virtual void _unknown_108();
    virtual void _unknown_109();
    virtual void _unknown_110();
    virtual int getComparatorSignal(BlockSource& region, const BlockPos& pos, const Block& block, unsigned char dir) const;
    virtual bool canSlide(BlockSource& region, const BlockPos& pos) const;
    virtual void _unknown_113();
    virtual bool canSpawnAt(const BlockSource& region, const BlockPos& pos) const;
    virtual void notifySpawnedAt(BlockSource& region, const BlockPos& pos) const;
    virtual void _unknown_116();
    virtual int getIconYOffset() const;
    virtual std::string buildDescriptionId(const Block&) const;
    virtual bool isAuxValueRelevantForPicking() const;
    virtual int getColor(const Block& block) const;
    virtual int getColor(BlockSource& region, const BlockPos& pos, const Block& block) const;
    virtual int getColorAtPos(BlockSource& region, const BlockPos& pos) const;
    virtual int getColorForParticle(BlockSource& region, const BlockPos& pos, const Block& block) const;
    virtual bool isSeasonTinted(const Block& block, BlockSource& region, const BlockPos& p) const;
    virtual void onGraphicsModeChanged(const BlockGraphicsModeChangeContext& context);
    virtual float getShadeBrightness(const Block& block) const;
    virtual int telemetryVariant(BlockSource& region, const BlockPos& pos) const;
    virtual int getVariant(const Block& block) const;
    virtual bool canSpawnOn(Actor* a2) const;
    virtual const Block& getRenderBlock() const;
    virtual unsigned char getMappedFace(unsigned char face, const Block& block) const;
    virtual Flip getFaceFlip(unsigned char face, const Block& block) const;
    virtual void animateTickBedrockLegacy(BlockSource&, const BlockPos&, Random&) const;
    virtual void animateTick(BlockSource& region, const BlockPos& pos, Random& random) const;
    virtual BlockLegacy& init();

protected:
    virtual Brightness getLightEmission(const Block& a2) const;

public:
    virtual const Block* tryLegacyUpgrade(unsigned short a2) const;
    virtual bool dealsContactDamage(const Actor& actor, const Block& block, bool isPathFinding) const;
    virtual const Block* tryGetInfested(const Block& a2) const;
    virtual const Block* tryGetUninfested(const Block& a2) const;
    virtual void _addHardCodedBlockComponents(const Experiments&);

protected:
    virtual void onRemove(BlockSource& region, const BlockPos& pos) const;
    virtual void onExploded(BlockSource& region, const BlockPos& pos, Actor* entitySource) const;
    virtual void onStandOn(EntityContext& entity, const BlockPos& pos) const;
    virtual void onPlace(BlockSource& region, const BlockPos& pos) const;
    virtual void _unknown_146();
    virtual void tick(BlockSource& region, const BlockPos& pos, Random& random) const;
    virtual void randomTick(BlockSource& region, const BlockPos& pos, Random& random) const;
    virtual void _unknown_149();
    virtual bool use(Player&, const BlockPos&, unsigned char, std::optional<Vec3>) const;
    virtual bool use(Player& player, const BlockPos& pos, unsigned char face) const;
    virtual void _unknown_152();
    virtual bool canSurvive(BlockSource& region, const BlockPos& pos) const;
    virtual BlockRenderLayer getRenderLayer() const;
    virtual BlockRenderLayer getRenderLayer(const Block& block, BlockSource& a3, const BlockPos& pos) const;
    virtual int getExtraRenderLayers() const;
    virtual Brightness getLight(const Block&) const;
    virtual Brightness getEmissiveBrightness(const Block& a2) const;
    virtual mce::Color getMapColor(BlockSource& a2, const BlockPos& a3, const Block& a4) const;

private:
    virtual void _onHitByActivatingAttack(BlockSource&, const BlockPos&, Actor*) const;
    virtual void _spawnAfterBreak(BlockSource&, const Block&, const BlockPos&, const ResourceDropsContext&) const;
    virtual void entityInside(BlockSource& a2, const BlockPos& a3, Actor& a4) const;

public:
    BlockLegacy(const std::string& nameId, short id, const Material& material);
    short getBlockItemId();
    void setDestroyTime(float destroyTime, float explosionResistance);
    void addState(const BlockState& blockState);
    
private: 
    std::optional<int> _tryLookupAlteredStateCollection(uint64_t stateId, uint16_t blockData);
};
#pragma pack(pop)

//static_assert(sizeof(BlockLegacy) == 984);
/// @symbolgeneration
#pragma once
#include <amethyst/Imports.hpp>

#include <mc/src/common/world/Direction.hpp>
#include <mc/src/common/world/item/FertilizerType.hpp>
#include <mc/src-deps/core/math/Color.hpp>
#include <mc/src-deps/core/utility/optional_ref.hpp>
#include <mc/src/common/resources/BaseGameVersion.hpp>
#include <mc/src/common/world/level/block/components/BlockComponentStorage.hpp>
#include <mc/src/common/world/item/ItemStackBase.hpp>
#include <mc/src/common/world/item/ItemInstance.hpp>
#include <mc/src/common/CommonTypes.hpp>
#include <mc/src/common/world/level/material/Material.hpp>
#include <mc/src/common/world/phys/AABB.hpp>
#include <mc/src/common/world/level/block/BlockRenderLayer.hpp>
#include <mc/src/common/world/level/block/BlockState.hpp>
#include <mc/src/common/world/level/block/Block.hpp>
#include "actor/BlockActorRendererId.hpp"
#include <mc/src/common/world/level/block/actor/BlockActor.hpp>
#include <mc/src/common/world/phys/HitResult.hpp>
#include <mc/src/common/world/level/block/GetCollisionShapeInterface.hpp>
#include <mc/src/common/world/phys/ShapeType.hpp>
#include <mc/src/common/world/level/block/BlockProperty.hpp>
#include <mc/src/common/world/item/CreativeItemCategory.hpp>

// Auto-generated: Unknown complete types
enum BlockSupportType {};
enum Flip {};

// Auto-generated: Forward declarations
class BlockPos;
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
class BlockItem;
class MobSpawnerData;
class SpawnConditions;
struct BlockGraphicsModeChangeContext;
class Random;
class Experiments;
class EntityContext;
struct ResourceDropsContext;


// other types
enum class FlameOdds : int {
    INSTANT = 60,
    EASY = 30,
    MEDIUM = 15,
    HARD = 5,
    NEVER = 0
};

enum class BurnOdds : int {
    INSTANT = 100,
    EASY = 60,
    MEDIUM = 20,
    HARD = 5,
    NEVER = 0
};

enum class LavaFlammable : uint8_t {
    Always = 1,
    Never  = 0,
};

enum class TintMethod : int32_t {
    None             = 0,
    DefaultFoliage   = 1,
    BirchFoliage     = 2,
    EvergreenFoliage = 3,
    DryFoliage       = 4,
    Grass            = 5,
    Water            = 6,
    Stem             = 7,
    RedStoneWire     = 8,
    Size             = 9,
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

/// @vptr {0x4E0E500}
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

    struct NameInfo {
        HashedString mRawName;
        std::string mNamespaceName;
        HashedString mFullName;
        HashedString mPreFlatteningName;
    };

public:
    MC static uintptr_t $vtable_for_this;

	/* this + 40  */ std::string mDescriptionId;
    /* this + 72  */ BlockLegacy::NameInfo mNameInfo;
    /* this + 248 */ uint64_t mProperties;
    /* this + 256 */ bool mFancy;
    /* this + 260 */ BlockRenderLayer mRenderLayer;
    /* this + 264 */ bool mRenderLayerCanRenderAsOpaque;
    /* this + 268 */ BlockActorType mBlockEntityType;
    bool mAnimatedTexture;
    float mBrightnessGamma;
    float mThickness;
    bool mCanSlide;
    bool mCanReactToNeighborsDuringInstatick;
    bool mIsInteraction;
    float mGravity;
    /* this + 296 */ const Material& mMaterial;
    bool mFalling;
    float mParticleQuantityScalar;
    CreativeItemCategory mCreativeCategory;
    std::string mCreativeGroup;
    bool mIsHiddenInCommands;
    bool mAllowsRunes;
    bool mCanBeBrokenFromFalling;
    bool mCanBeOriginalSurface;
    bool mSolid;
    bool mPushesOutItems;
    bool mIgnoreBlockForInsideCubeRenderer;
    bool mIsTrapdoor;
    bool mIsDoor;
    bool mIsOpaqueFullBlock;
    float mTranslucency;
    bool mShouldRandomTick;
    bool mShouldRandomTickExtraLayer;
    bool mIsMobPiece;
    bool mCanBeExtraBlock;
    bool mCanPropagateBrightness;
    /* this + 373 */ unsigned char mLightBlock;
    /* this + 374 */ unsigned char mLightEmission;
    FlameOdds mFlameOdds;
    BurnOdds mBurnOdds;
    LavaFlammable mLavaFlammable;
    /* this + 388 */ float mDestroySpeed;
    /* this + 392 */ float mExplosionResistance;
    /* this + 396 */ mce::Color mMapColor;
    /* this + 412 */ float mFriction;
    /* this + 416 */ TintMethod mBlockTintTypeID;
    /* this + 4 */ bool mReturnDefaultBlockOnUnidentifiedBlockState;
    /* this + 422 */ unsigned short mID;
    /* this + 424 */ BaseGameVersion mMinRequiredBaseGameVersion;
    /* this + 544 */ bool mIsVanilla;
    // /* this + 545 */ std::byte padding545[135];
    std::vector<HashedString> mTags;
    std::byte mEventHandlers[64]; // std::unordered_map<std::string, DefinitionEvent> mEventHandlers;
    bool mDataDrivenVanillaBlocksAndItemsEnabled;
    AABB mVisualShape;
    uint32_t mBitsUsed;
    uint32_t mTotalBitsUsed;
    /* this + 680 */ std::map<uint64_t, BlockStateInstance> mStates;
    /* this + 696 */ std::unordered_map<HashedString, uint64_t> mStateNameMap;
    /* this + 760 */ uint64_t mCreativeEnumState;
    /* this + 768 */ std::vector<std::unique_ptr<Block>> mBlockPermutations;
    const Block *mDefaultState;
    /* this + 800 */ std::byte padding800[152];
    //std::vector<std::unique_ptr<BlockTrait::IGetPlacementBlockCallback>> mGetPlacementBlockCallbacks;
    //Core::Cache<unsigned short, Block const *, Block const *> mLegacyDataLookupTable;
    // std::unique_ptr<BlockStateGroup> mBlockStateGroup;
    // std::unique_ptr<IResourceDropsStrategy> mResourceDropsStrategy;
    // IntRange mExperienceDropRange;
    // bool mCanDropWithAnyTool;
    /* this + 952 */ std::vector<std::shared_ptr<BlockLegacy::AlteredStateCollection>> mAlteredStateCollections;
    /* this + 976 */ uint8_t mClientPredictionOverrides;

    // aint that lovely, they're friends now
    friend class Block;

public:
    /** @signature {48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 81 EC ? ? ? ? 49 8B F9 48 8B F2 } */
    MC BlockLegacy(const std::string& nameId, short id, const Material& material);

	// That's satisfying asf lmao
    /** @vidx {000} */ MC virtual ~BlockLegacy();
 	/** @vidx {001} */ MC virtual std::shared_ptr<BlockActor> newBlockEntity(const BlockPos& unk0, const Block& unk1) const;
 	/** @vidx {002} */ MC virtual const Block* getNextBlockPermutation(const Block& unk0) const;
	/** @vidx {003} */ MC virtual bool hasTag(BlockSource& unk0, const BlockPos& unk1, const Block& unk2, const std::string& unk3) const;
 	/** @vidx {004} */ MC virtual HitResult clip(const Block& unk0, const BlockSource& unk1, const BlockPos& unk2, const Vec3& unk3, const Vec3& unk4, ShapeType unk5, optional_ref<const GetCollisionShapeInterface> unk6) const;
 	/** @vidx {005} */ MC virtual AABB getCollisionShape(const Block& unk0, const IConstBlockSource& unk1, const BlockPos& unk2, optional_ref<const GetCollisionShapeInterface> unk3) const;
 	/** @vidx {006} */ MC virtual bool getCollisionShapeForCamera(AABB& unk0, const Block& unk1, const IConstBlockSource& unk2, const BlockPos& unk3) const;
 	/** @vidx {007} */ MC virtual bool addCollisionShapes(const Block& unk0, const IConstBlockSource& unk1, const BlockPos& unk2, const AABB* unk3, std::vector<AABB>& unk4, optional_ref<const GetCollisionShapeInterface> unk5) const;
 	/** @vidx {008} */ MC virtual void addAABBs(const Block& unk0, const IConstBlockSource& unk1, const BlockPos& unk2, const AABB* unk3, std::vector<AABB>& unk4) const;
 	/** @vidx {009} */ MC virtual const AABB& getOutline(const Block& unk0, const IConstBlockSource& unk1, const BlockPos& unk2, AABB& unk3) const;
 	/** @vidx {010} */ MC virtual const AABB& getVisualShapeInWorld(const Block& unk0, const IConstBlockSource& unk1, const BlockPos& unk2, AABB& unk3) const;
	/** @vidx {011} */ MC virtual const AABB& getVisualShape(const Block& unk0, AABB& unk1) const;
	/** @vidx {012} */ MC virtual const AABB& getUIShape(const Block& unk0, AABB& unk1) const;
	/** @vidx {013} */ MC virtual bool getLiquidClipVolume(const Block& unk0, BlockSource& unk1, const BlockPos& unk2, AABB& unk3) const;
	/** @vidx {014} */ MC virtual bool isObstructingChests(BlockSource& unk0, const BlockPos& unk1, const Block& unk2) const;
	/** @vidx {016} */ MC virtual Vec3 randomlyModifyPosition(const BlockPos& unk0, int& unk1) const;
	/** @vidx {015} */ MC virtual Vec3 randomlyModifyPosition(const BlockPos& unk0) const;
	/** @vidx {017} */ MC virtual void onProjectileHit(BlockSource& unk0, const BlockPos& unk1, const Actor& unk2) const;
	/** @vidx {018} */ MC virtual void onLightningHit(BlockSource& unk0, const BlockPos& unk1) const;
	/** @vidx {019} */ MC virtual UnknownReturn liquidCanFlowIntoFromDirection(unsigned char unk0, const std::function<const Block&(const BlockPos&)>& unk1, const BlockPos& unk2) const;
	/** @vidx {020} */ MC virtual bool hasVariableLighting() const;
	/** @vidx {021} */ MC virtual bool isStrippable(const Block& unk0) const;
	/** @vidx {022} */ MC virtual const Block& getStrippedBlock(const Block& unk0) const;
	/** @vidx {023} */ MC virtual bool canProvideSupport(const Block& unk0, unsigned char unk1, BlockSupportType unk2) const;
	/** @vidx {024} */ MC virtual bool canProvideMultifaceSupport(const Block& unk0, unsigned char unk1) const;
	/** @vidx {025} */ MC virtual bool canConnect(const Block& unk0, unsigned char unk1, const Block& unk2) const;
	/** @vidx {026} */ MC virtual bool isMovingBlock() const;
	/** @vidx {027} */ MC virtual const CopperBehavior* tryGetCopperBehavior() const;
	/** @vidx {028} */ MC virtual bool canDamperVibrations() const;
	/** @vidx {029} */ MC virtual bool canOccludeVibrations() const;
	/** @vidx {030} */ MC virtual bool isStemBlock() const;
	/** @vidx {031} */ MC virtual bool isContainerBlock() const;
	/** @vidx {032} */ MC virtual bool isCraftingBlock() const;
	/** @vidx {033} */ MC virtual bool isWaterBlocking() const;
	/** @vidx {034} */ MC virtual bool isFenceBlock() const;
	/** @vidx {035} */ MC virtual bool isFenceGateBlock() const;
	/** @vidx {036} */ MC virtual bool isThinFenceBlock() const;
	/** @vidx {037} */ MC virtual bool isWallBlock() const;
	/** @vidx {038} */ MC virtual bool isStairBlock() const;
	/** @vidx {039} */ MC virtual bool isSlabBlock() const;
	/** @vidx {040} */ MC virtual bool isDoubleSlabBlock() const;
	/** @vidx {041} */ MC virtual bool isDoorBlock() const;
	/** @vidx {042} */ MC virtual bool isRailBlock() const;
	/** @vidx {043} */ MC virtual bool isButtonBlock() const;
	/** @vidx {044} */ MC virtual bool isLeverBlock() const;
	/** @vidx {045} */ MC virtual bool isCandleCakeBlock() const;
	/** @vidx {046} */ MC virtual bool isMultifaceBlock() const;
	/** @vidx {047} */ MC virtual bool isSignalSource() const;
	/** @vidx {048} */ MC virtual bool canBeOriginalSurface() const;
	/** @vidx {049} */ MC virtual bool isSilentWhenJumpingOff() const;
	/** @vidx {050} */ MC virtual bool isValidAuxValue(int unk0) const;
	/** @vidx {051} */ MC virtual bool canFillAtPos(BlockSource& unk0, const BlockPos& unk1, const Block& unk2) const;
	/** @vidx {052} */ MC virtual const Block& sanitizeFillBlock(const Block& unk0) const;
	/** @vidx {053} */ MC virtual void onFillBlock(BlockSource& unk0, const BlockPos& unk1, const Block& unk2) const;
	/** @vidx {054} */ MC virtual int getDirectSignal(BlockSource& unk0, const BlockPos& unk1, int unk2) const;
	/** @vidx {055} */ MC virtual bool canBeDestroyedByWaterSpread() const;
	/** @vidx {056} */ MC virtual bool waterSpreadCausesSpawn() const;
	/** @vidx {057} */ MC virtual bool canContainLiquid() const;
	/** @vidx {058} */ MC virtual std::optional<HashedString> getRequiredMedium() const;
	/** @vidx {059} */ MC virtual bool shouldConnectToRedstone(BlockSource& unk0, const BlockPos& unk1, Direction::Type unk2) const;
	/** @vidx {060} */ MC virtual void handlePrecipitation(BlockSource& unk0, const BlockPos& unk1, float unk2, float unk3) const;
	/** @vidx {061} */ MC virtual bool canBeUsedInCommands(const BaseGameVersion& unk0) const;
	/** @vidx {062} */ MC virtual bool checkIsPathable(Actor& unk0, const BlockPos& unk1, const BlockPos& unk2) const;
	/** @vidx {063} */ MC virtual bool shouldDispense(BlockSource& unk0, Container& unk1) const;
	/** @vidx {064} */ MC virtual bool dispense(BlockSource& unk0, Container& unk1, int unk2, const Vec3& unk3, unsigned char unk4) const;
	/** @vidx {065} */ MC virtual void transformOnFall(BlockSource& unk0, const BlockPos& unk1, Actor* unk2, float unk3) const;
	/** @vidx {066} */ MC virtual void onRedstoneUpdate(BlockSource& unk0, const BlockPos& unk1, int unk2, bool unk3) const;
	/** @vidx {067} */ MC virtual void onMove(BlockSource& unk0, const BlockPos& unk1, const BlockPos& unk2) const;
	/** @vidx {068} */ MC virtual bool detachesOnPistonMove(BlockSource& unk0, const BlockPos& unk1) const;
	/** @vidx {069} */ MC virtual void movedByPiston(BlockSource& unk0, const BlockPos& unk1) const;
	/** @vidx {070} */ MC virtual void onStructureBlockPlace(BlockSource& unk0, const BlockPos& unk1) const;
	/** @vidx {071} */ MC virtual void onStructureNeighborBlockPlace(BlockSource& unk0, const BlockPos& unk1) const;
	/** @vidx {072} */ MC virtual void setupRedstoneComponent(BlockSource& unk0, const BlockPos& unk1) const;
	/** @vidx {073} */ MC virtual BlockProperty getRedstoneProperty(BlockSource& unk0, const BlockPos& unk1) const;
	/** @vidx {074} */ MC virtual void updateEntityAfterFallOn(const BlockPos& unk0, UpdateEntityAfterFallOnInterface& unk1) const;
	/** @vidx {075} */ MC virtual bool isBounceBlock() const;
	/** @vidx {076} */ MC virtual bool isPreservingMediumWhenPlaced(const BlockLegacy* unk0) const;
	/** @vidx {077} */ MC virtual bool isFilteredOut(BlockRenderLayer unk0) const;
	/** @vidx {078} */ MC virtual bool canRenderSelectionOverlay(BlockRenderLayer unk0) const;
	/** @vidx {079} */ MC virtual bool ignoreEntitiesOnPistonMove(const Block& unk0) const;
	/** @vidx {080} */ MC virtual bool onFertilized(BlockSource& unk0, const BlockPos& unk1, Actor* unk2, FertilizerType unk3) const;
	/** @vidx {081} */ MC virtual bool mayConsumeFertilizer(BlockSource& unk0) const;
	/** @vidx {082} */ MC virtual bool canBeFertilized(BlockSource& unk0, const BlockPos& unk1, const Block& unk2) const;
	/** @vidx {084} */ MC virtual bool mayPick() const;
	/** @vidx {083} */ MC virtual bool mayPick(const BlockSource& unk0, const Block& unk1, bool unk2) const;
	/** @vidx {086} */ MC virtual bool mayPlace(BlockSource& unk0, const BlockPos& unk1, unsigned char unk2) const;
	/** @vidx {085} */ MC virtual bool mayPlace(BlockSource& unk0, const BlockPos& unk1) const;
	/** @vidx {087} */ MC virtual bool mayPlaceOn(BlockSource& unk0, const BlockPos& unk1) const;
	/** @vidx {088} */ MC virtual bool tryToPlace(BlockSource& unk0, const BlockPos& unk1, const Block& unk2, const ActorBlockSyncMessage* unk3) const;
	/** @vidx {089} */ MC virtual bool tryToTill(BlockSource& unk0, const BlockPos& unk1, Actor& unk2, ItemStack& unk3) const;
	/** @vidx {090} */ MC virtual bool breaksFallingBlocks(const Block& unk0, BaseGameVersion unk1) const;
	/** @vidx {091} */ MC virtual void destroy(BlockSource& unk0, const BlockPos& unk1, const Block& unk2, Actor* unk3) const;
	/** @vidx {092} */ MC virtual bool getIgnoresDestroyPermissions(Actor& unk0, const BlockPos& unk1) const;
	/** @vidx {093} */ MC virtual void neighborChanged(BlockSource& unk0, const BlockPos& unk1, const BlockPos& unk2) const;
	/** @vidx {094} */ MC virtual bool getSecondPart(const IConstBlockSource& unk0, const BlockPos& unk1, BlockPos& unk2) const;
	/** @vidx {095} */ MC virtual const Block* playerWillDestroy(Player& unk0, const BlockPos& unk1, const Block& unk2) const;
	/** @vidx {096} */ MC virtual ItemInstance asItemInstance(const Block& unk0, const BlockActor* unk1) const;
	/** @vidx {097} */ MC virtual void spawnAfterBreak(BlockSource& unk0, const Block& unk1, const BlockPos& unk2, const ResourceDropsContext& unk3) const;
	/** @vidx {098} */ MC virtual const Block& getPlacementBlock(const Actor& unk0, const BlockPos& unk1, unsigned char unk2, const Vec3& unk3, int unk4) const;
	/** @vidx {099} */ MC virtual int calcVariant(BlockSource& unk0, const BlockPos& unk1, const mce::Color& unk2) const;
	/** @vidx {100} */ MC virtual bool isAttachedTo(BlockSource& unk0, const BlockPos& unk1, BlockPos& unk2) const;
	/** @vidx {101} */ MC virtual bool attack(Player* unk0, const BlockPos& unk1) const;
	/** @vidx {102} */ MC virtual bool shouldTriggerEntityInside(BlockSource& unk0, const BlockPos& unk1, Actor& unk2) const;
	/** @vidx {104} */ MC virtual bool canBeBuiltOver(BlockSource& unk0, const BlockPos& unk1, const BlockItem& unk2) const;
	/** @vidx {103} */ MC virtual bool canBeBuiltOver(BlockSource& unk0, const BlockPos& unk1) const;
	/** @vidx {105} */ MC virtual void triggerEvent(BlockSource& unk0, const BlockPos& unk1, int unk2, int unk3) const;
	/** @vidx {106} */ MC virtual void executeEvent(BlockSource& unk0, const BlockPos& unk1, const Block& unk2, const std::string& unk3, Actor& unk4) const;
	/** @vidx {107} */ MC virtual const MobSpawnerData* getMobToSpawn(const SpawnConditions& unk0, BlockSource& unk1) const;
	/** @vidx {108} */ MC virtual bool shouldStopFalling(Actor& unk0) const;
	/** @vidx {109} */ MC virtual bool pushesUpFallingBlocks() const;
	/** @vidx {110} */ MC virtual bool canHaveExtraData() const;
	/** @vidx {111} */ MC virtual bool hasComparatorSignal() const;
	/** @vidx {112} */ MC virtual int getComparatorSignal(BlockSource& unk0, const BlockPos& unk1, const Block& unk2, unsigned char unk3) const;
	/** @vidx {113} */ MC virtual bool canSlide(BlockSource& unk0, const BlockPos& unk1) const;
	/** @vidx {114} */ MC virtual bool canInstatick() const;
	/** @vidx {115} */ MC virtual bool canSpawnAt(const BlockSource& unk0, const BlockPos& unk1) const;
	/** @vidx {116} */ MC virtual void notifySpawnedAt(BlockSource& unk0, const BlockPos& unk1) const;
	/** @vidx {117} */ MC virtual bool causesFreezeEffect() const;
	/** @vidx {118} */ MC virtual int getIconYOffset() const;
	/** @vidx {119} */ MC virtual std::string buildDescriptionId(const Block& unk0) const;
	/** @vidx {120} */ MC virtual bool isAuxValueRelevantForPicking() const;
	/** @vidx {121} */ MC virtual int getColor(const Block& unk0) const;
	/** @vidx {122} */ MC virtual int getColorAtPos(BlockSource& unk0, const BlockPos& unk1) const;
	/** @vidx {123} */ MC virtual int getColor(BlockSource& unk0, const BlockPos& unk1, const Block& unk2) const;
	/** @vidx {124} */ MC virtual int getColorForParticle(BlockSource& unk0, const BlockPos& unk1, const Block& unk2) const;
	/** @vidx {125} */ MC virtual bool isSeasonTinted(const Block& unk0, BlockSource& unk1, const BlockPos& unk2) const;
	/** @vidx {126} */ MC virtual void onGraphicsModeChanged(const BlockGraphicsModeChangeContext& unk0);
	/** @vidx {127} */ MC virtual float getShadeBrightness(const Block& unk0) const;
	/** @vidx {128} */ MC virtual int telemetryVariant(BlockSource& unk0, const BlockPos& unk1) const;
	/** @vidx {129} */ MC virtual int getVariant(const Block& unk0) const;
	/** @vidx {130} */ MC virtual bool canSpawnOn(Actor* unk0) const;
	/** @vidx {131} */ MC virtual const Block& getRenderBlock() const;
	/** @vidx {132} */ MC virtual unsigned char getMappedFace(unsigned char unk0, const Block& unk1) const;
	/** @vidx {133} */ MC virtual Flip getFaceFlip(unsigned char unk0, const Block& unk1) const;
	/** @vidx {134} */ MC virtual void animateTickBedrockLegacy(BlockSource& unk0, const BlockPos& unk1, Random& unk2) const;
	/** @vidx {135} */ MC virtual void animateTick(BlockSource& unk0, const BlockPos& unk1, Random& unk2) const;
	/** @vidx {136} */ MC virtual BlockLegacy& init();
	/** @vidx {137} */ MC virtual Brightness getLightEmission(const Block& unk0) const;
	/** @vidx {138} */ MC virtual const Block* tryLegacyUpgrade(unsigned short unk0) const;
	/** @vidx {139} */ MC virtual bool dealsContactDamage(const Actor& unk0, const Block& unk1, bool unk2) const;
	/** @vidx {140} */ MC virtual const Block* tryGetInfested(const Block& unk0) const;
	/** @vidx {141} */ MC virtual const Block* tryGetUninfested(const Block& unk0) const;
	/** @vidx {142} */ MC virtual void _addHardCodedBlockComponents(const Experiments& unk0);
	/** @vidx {143} */ MC virtual void onRemove(BlockSource& unk0, const BlockPos& unk1) const;
	/** @vidx {144} */ MC virtual void onExploded(BlockSource& unk0, const BlockPos& unk1, Actor* unk2) const;
	/** @vidx {145} */ MC virtual void onStandOn(EntityContext& unk0, const BlockPos& unk1) const;
	/** @vidx {146} */ MC virtual void onPlace(BlockSource& unk0, const BlockPos& unk1) const;
	/** @vidx {147} */ MC virtual bool shouldTickOnSetBlock() const;
	/** @vidx {148} */ MC virtual void tick(BlockSource& unk0, const BlockPos& unk1, Random& unk2) const;
	/** @vidx {149} */ MC virtual void randomTick(BlockSource& unk0, const BlockPos& unk1, Random& unk2) const;
	/** @vidx {150} */ MC virtual bool isInteractiveBlock() const;
	/** @vidx {152} */ MC virtual bool use(Player& unk0, const BlockPos& unk1, unsigned char unk2, std::optional<Vec3> unk3) const;
	/** @vidx {151} */ MC virtual bool use(Player& unk0, const BlockPos& unk1, unsigned char unk2) const;
	/** @vidx {153} */ MC virtual bool allowStateMismatchOnPlacement(const Block& unk0, const Block& unk1) const;
	/** @vidx {154} */ MC virtual bool canSurvive(BlockSource& unk0, const BlockPos& unk1) const;
	/** @vidx {156} */ MC virtual BlockRenderLayer getRenderLayer() const;
	/** @vidx {155} */ MC virtual BlockRenderLayer getRenderLayer(const Block& unk0, BlockSource& unk1, const BlockPos& unk2) const;
	/** @vidx {157} */ MC virtual int getExtraRenderLayers() const;
	/** @vidx {158} */ MC virtual Brightness getLight(const Block& unk0) const;
	/** @vidx {159} */ MC virtual Brightness getEmissiveBrightness(const Block& unk0) const;
	/** @vidx {160} */ MC virtual mce::Color getMapColor(BlockSource& unk0, const BlockPos& unk1, const Block& unk2) const;
	/** @vidx {161} */ MC virtual void _onHitByActivatingAttack(BlockSource& unk0, const BlockPos& unk1, Actor* unk2) const;
    /** @vidx {162} */ MC virtual void entityInside(BlockSource& unk0, const BlockPos& unk1, Actor& unk2);

    short getBlockItemId();
    void setDestroyTime(float destroyTime, float explosionResistance);
    void addState(const BlockState& blockState);
    bool isAir() const;
    bool hasProperty(BlockProperty prop) const;
    bool isSnappableBlock() const;
    std::optional<int> _tryLookupAlteredStateCollection(uint64_t stateId, uint16_t blockData);
};

// 1.21.0.3
static_assert(sizeof(BlockLegacy) == 984);
static_assert(offsetof(BlockLegacy, mID) == 422);
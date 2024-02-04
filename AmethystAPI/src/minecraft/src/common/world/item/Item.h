#pragma once
#include "amethyst/Memory.h"
#include <cstdint>
#include <string>
#include "minecraft/src-deps/core/math/Color.h"
#include "minecraft/src-deps/core/headerIncludes/gsl_includes.h"
#include "minecraft/src-deps/core/string/StringHash.h"
#include "minecraft/src/common/SharedPtr.h"
#include "minecraft/src/common/world/item/UseAnim.h"
#include "minecraft/src/common/world/item/ItemCategory.h"
#include <cstddef>

class CompoundTag;
class Level;
class ItemStackBase;
namespace Json {
    class Value;
};
class Experiments;
class ItemStack;
class ItemStackBase;
class RenderParams;
class SemVersion;
class ItemComponent;
enum ItemColor {};
class IFoodItemComponent;
class BaseGameVersion;
enum BlockShape {};
class CompoundTag;
class Block;
class Level;
class ItemDescriptor;
struct ActorDefinitionIdentifier {};
class BlockSource;
class Player;
class ItemInstance;
class Actor;
class Container;
class Vec3;
enum ItemUseMethod {};
class Mob;
class BlockPos;
class ReadOnlyBinaryStream;
class IDataInput;
enum InHandUpdateType {};
enum ActorLocation {};
class InteractionResult {};
class IDataOutput;
struct Brightness;
struct ResolvedItemIconInfo {};
class BlockLegacy;

namespace Puv {
    namespace Legacy {
        enum LevelSoundEvent {};
    }; 
};

// vtable for Item 0x1453C9B70

// Item tag extends hashed string, doesn't declare anything so eh
using ItemTag = HashedString;
class FoodItemComponentLegacy;
class SeedItemComponentLegacy;
class CameraItemComponentLegacy;

class Item {
public:
    std::byte padding0[104];
    void* qword70; // this + 112
    std::byte padding1[24];
    void* qword90; // this + 144
    std::byte padding2[10];
    int16_t mId;        // this + 162
    int16_t mMaxDamage; // this + 164
    std::byte padding3[2];
    std::string* mItemName; // this + 168
    std::byte padding4[72];
    std::string mNamespace; // this + 248
    std::byte padding5[320];

    //
    // things seem misaligned? so leaving out for now..
    //

    /*std::string mTextureAtlasFile;
    int frameCount;
    bool mAnimatesInToolbar;
    bool mIsMirroredArt;
    UseAnimation mUseAnim;
    string_span mHoverTextColorFormat;
    int mIconFrame;
    int mAtlasFrame;
    int mAtlasTotalFrames;
    std::string mIconName;
    std::string mAtlasName;
    byte mMaxStackSize;
    short mId;
    std::string mDescriptionId;
    HashedString mRawNameId;
    std::string mNamespace;
    HashedString mFullName;
    short mMaxDamage;
    bool mIsGlint : 1;
    bool mHandEquipped : 1;
    bool mIsStackedByData : 1;
    bool mRequiresWorldBuilder : 1;
    bool mExplodable : 1;
    bool mFireResistant : 1;
    bool mShouldDespawn : 1;
    bool mAllowOffhand : 1;
    bool mIgnoresPermissions : 1;
    int mMaxUseDuration;
    std::byte mMinRequiredBaseGameVersion[120];
    WeakPtr<BlockLegacy> mLegacyBlock;
    CreativeItemCategory mCreativeCategory;
    Item* mCraftingRemainingItem;
    std::string mCreativeGroup;
    float mFurnaceBurnIntervalModifier;
    float mFurnaceXPmultiplier;
    std::weak_ptr<FoodItemComponentLegacy> mFoodComponentLegacy;
    std::weak_ptr<SeedItemComponentLegacy> mSeedComponent;
    std::weak_ptr<CameraItemComponentLegacy> mCameraComponentLegacy;
    std::byte mOnResetBAIcallbacks[24]; 
    std::vector<ItemTag> mTags;*/

//virtuals:
public:
    virtual ~Item();
    virtual bool initServer(Json::Value&, SemVersion const&, bool, Experiments const&);
    virtual void tearDown();
    virtual Item& setDescriptionId(std::string const&);
    virtual std::string const& getDescriptionId() const;
    virtual int getMaxUseDuration(ItemStack const*) const;
    virtual bool isMusicDisk() const;
    virtual void executeEvent(ItemStackBase&, std::string const&, RenderParams&) const;
    virtual bool isComponentBased() const;
    virtual bool isArmor() const;
    virtual bool isBlockPlanterItem() const;
    virtual bool isBucket() const;
    virtual bool isCandle() const;
    virtual bool isDamageable() const;
    virtual bool isDyeable() const;
    virtual bool isDye() const;
    virtual ItemColor getItemColor() const;
    virtual bool isFertilizer() const;
    virtual bool isFood() const;
    virtual bool isThrowable() const;
    virtual bool isUseable() const;
    virtual ItemComponent* getComponent(HashedString const&) const;
    virtual IFoodItemComponent* getFood() const;
    virtual Item& setMaxDamage(int);
    virtual Item& setMaxUseDuration(int);
    virtual std::unique_ptr<CompoundTag> buildNetworkTag() const;
    virtual void initializeFromNetwork(CompoundTag const&);
    virtual std::vector<std::string> validateFromNetwork(CompoundTag const&);
    virtual BlockShape getBlockShape() const;
    virtual bool canBeDepleted() const;
    virtual bool canDestroySpecial(Block const&) const;
    virtual int getLevelDataForAuxValue(int) const;
    virtual bool isStackedByData() const;
    virtual short getMaxDamage() const;
    virtual int getAttackDamage() const;
    virtual bool isHandEquipped() const;
    virtual bool isGlint(ItemStackBase const&) const;
    virtual bool isPattern() const;
    virtual int getPatternIndex() const;
    virtual bool showsDurabilityInCreative() const;
    virtual bool isWearableThroughLootTable(CompoundTag const*) const;
    virtual bool canDestroyInCreative() const;
    virtual bool isDestructive(int) const;
    virtual bool isLiquidClipItem() const;
    virtual bool shouldInteractionWithBlockBypassLiquid(Block const&) const;
    virtual bool requiresInteract() const;
    virtual void appendFormattedHovertext(ItemStackBase const&, Level&, std::string&, bool) const;
    virtual bool isValidRepairItem(ItemStackBase const&, ItemStackBase const&, BaseGameVersion const&) const;
    virtual int getEnchantSlot() const;
    virtual int getEnchantValue() const;
    virtual int getArmorValue() const;
    virtual int getToughnessValue() const;
    virtual bool isComplex() const;
    virtual bool isValidAuxValue(int) const;
    virtual int getDamageChance(int) const;
    virtual float getViewDamping() const;
    virtual bool uniqueAuxValues() const;
    virtual bool isActorPlacerItem() const;
    virtual bool isMultiColorTinted(ItemStack const&) const;
    virtual mce::Color getColor(CompoundTag const*, ItemDescriptor const&) const;
    virtual bool hasCustomColor(ItemStackBase const&) const;
    virtual bool hasCustomColor(CompoundTag const*) const;
    virtual void clearColor(ItemStackBase&) const;
    virtual void clearColor(CompoundTag*) const;
    virtual void setColor(ItemStackBase&, mce::Color const&) const;
    virtual mce::Color getBaseColor(ItemStack const&) const;
    virtual mce::Color getSecondaryColor(ItemStack const&) const;
    virtual ActorDefinitionIdentifier getActorIdentifier(ItemStack const&) const;
    virtual int buildIdAux(short, CompoundTag const*) const;
    virtual bool canUseOnSimTick() const;
    virtual ItemStack& use(ItemStack&, Player&) const;
    virtual bool dispense(BlockSource&, Container&, int, Vec3 const&, unsigned char) const;
    virtual ItemUseMethod useTimeDepleted(ItemStack&, Level*, Player*) const;
    virtual void releaseUsing(ItemStack&, Player*, int) const;
    virtual float getDestroySpeed(ItemStackBase const&, Block const&) const;
    virtual void hurtActor(ItemStack&, Actor&, Mob&) const;
    virtual void hitActor(ItemStack&, Actor&, Mob&) const;
    virtual void hitBlock(ItemStack&, Block const&, BlockPos const&, Mob&) const;
    virtual bool mineBlock(ItemInstance&, Block const&, int, int, int, Actor*) const;
    virtual bool mineBlock(ItemStack&, Block const&, int, int, int, Actor*) const;
    virtual std::string buildDescriptionName(ItemStackBase const&) const;
    virtual std::string buildDescriptionId(ItemDescriptor const&, CompoundTag const*) const;
    virtual std::string buildEffectDescriptionName(ItemStackBase const&) const;
    virtual void readUserData(ItemStackBase&, IDataInput&, ReadOnlyBinaryStream&) const;
    virtual void writeUserData(ItemStackBase const&, IDataOutput&) const;
    virtual unsigned char getMaxStackSize(ItemDescriptor const&) const;
    virtual bool inventoryTick(ItemStack&, Level&, Actor&, int, bool) const;
    virtual void refreshedInContainer(ItemStackBase const&, Level&) const;
    virtual HashedString const& getCooldownType() const;
    virtual int getCooldownTime() const;
    virtual void fixupCommon(ItemStackBase&) const;
    virtual void fixupCommon(ItemStackBase&, Level&) const;
    virtual InHandUpdateType getInHandUpdateType(Player const&, ItemInstance const&, ItemInstance const&, bool, bool) const;
    virtual InHandUpdateType getInHandUpdateType(Player const&, ItemStack const&, ItemStack const&, bool, bool) const;
    virtual bool validFishInteraction(int) const;
    virtual void enchantProjectile(ItemStackBase const&, Actor&) const;
    virtual ActorLocation getEquipLocation() const;
    virtual Puv::Legacy::LevelSoundEvent getEquipSound() const;
    virtual bool shouldSendInteractionGameEvents() const;
    virtual bool useInterruptedByAttacking() const;
    virtual bool hasSameRelevantUserData(ItemStackBase const&, ItemStackBase const&) const;
    virtual void initClient(Json::Value&, SemVersion const&, bool, Experiments const&);
    virtual Item& setIconInfo(std::string const&, int);
    virtual ResolvedItemIconInfo getIconInfo(ItemStackBase const&, int, bool) const;
    virtual std::string getInteractText(Player const&) const;
    virtual int getAnimationFrameFor(Mob*, bool, ItemStack const*, bool) const;
    virtual bool isEmissive(int) const;
    virtual Brightness getLightEmission(int) const;
    virtual int getIconYOffset() const;
    virtual bool canBeCharged() const;
    virtual void playSoundIncrementally(ItemStack const&, Mob&) const;
    virtual float getFurnaceXPmultiplier(ItemStackBase const&) const;
    virtual std::string getAuxValuesDescription() const;
    virtual bool calculatePlacePos(ItemStackBase&, Actor&, unsigned char&, BlockPos&) const;

private:
    virtual bool _checkUseOnPermissions(Actor&, ItemStackBase&, unsigned char const&, BlockPos const&) const;
    virtual bool _calculatePlacePos(ItemStackBase&, Actor&, unsigned char&, BlockPos&) const;
    virtual bool _shouldAutoCalculatePlacePos() const;
    virtual InteractionResult _useOn(ItemStack&, Actor&, BlockPos, unsigned char, Vec3 const&) const;

public:
    Item(const std::string&, short);
    short getDamageValue(CompoundTag* mUserData) const;
    

//hooks:
    // 40 55 53 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 49 8B F1 4C 89 44 24 ? 4C 8B F2 48 8B D9
    typedef void(__thiscall* _appendFormattedHovertext)(Item*, const ItemStackBase&, Level&, std::string&, uint8_t);
};

static_assert(sizeof(Item) == 600);
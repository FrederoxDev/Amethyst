#pragma once
#include <memory>
#include <string>
#include <vector>

#include <minecraft/src-deps/core/headerIncludes/gsl_includes.hpp>
#include <minecraft/src-deps/core/math/Color.hpp>
#include <minecraft/src-deps/core/string/StringHash.hpp>
#include <minecraft/src/common/SharedPtr.hpp>
#include <minecraft/src/common/nbt/CompoundTag.hpp>
#include <minecraft/src/common/world/item/ItemCategory.hpp>
#include <minecraft/src/common/world/level/BlockPos.hpp>
#include <minecraft/src/common/world/level/block/BlockLegacy.hpp>
#include <minecraft/src/common/world/item/registry/ItemRegistryRef.hpp>

// Auto-generated: Unknown complete types
enum ItemColor {};
enum BlockShape {};
struct ActorDefinitionIdentifier {};
enum ItemUseMethod {};
enum InHandUpdateType {};
enum ActorLocation {};
namespace Puv {
namespace Legacy {
enum LevelSoundEvent {};
}
} // namespace Puv
struct ResolvedItemIconInfo {};
struct Brightness {};
class InteractionResult {};

// Auto-generated: Forward declarations
namespace Json {
class Value;
}
class SemVersion;
class Experiments;
class Item;
class ItemStack;
class ItemStackBase;
class RenderParams;
class ItemComponent;
class HashedString;
class IFoodItemComponent;
class Block;
class Level;
class BaseGameVersion;
class ItemDescriptor;
class Player;
class BlockSource;
class Container;
class Vec3;
class Actor;
class Mob;
class IDataInput;
class ReadOnlyBinaryStream;
class IDataOutput;
class ItemInstance;

class Item {
public:
    /* this + 8   */ std::string mTextureAtlasFile;
    /* this + 40  */ std::byte padding40[4];
    /* this + 44  */ bool mIsMirroredArt;
    /* this + 45  */ std::byte padding45[19];
    /* this + 64  */ string_span mHoverTextColorFormat;
    /* this + 80  */ std::byte padding80[82];
    /* this + 162 */ short mId;
    /* this + 164 */ short mMaxDamage;
    /* this + 166 */ std::byte padding166[2];
    /* this + 168 */ std::string mDescriptionId;
    /* this + 200 */ HashedString mRawNameId;
    /* this + 248 */ std::string mNamespace;
    /* this + 280 */ std::byte padding280[48];
    /* this + 328 */ short mMaxUseDuration;
    /* this + 330 */ std::byte padding330[126];
    /* this + 456 */ WeakPtr<BlockLegacy> mLegacyBlock;
    /* this + 464 */ CreativeItemCategory mCreativeCategory;
    /* this + 468 */ std::byte padding468[132];

public:
    virtual ~Item();
    virtual bool initServer(Json::Value&, const SemVersion&, bool, const Experiments&);
    virtual void tearDown();
    virtual Item& setDescriptionId(const std::string& description);
    virtual const std::string& getDescriptionId() const;
    virtual int getMaxUseDuration(const ItemStack* instance) const;
    virtual bool isMusicDisk() const;
    virtual void executeEvent(ItemStackBase& item, const std::string& name, RenderParams& pars) const;
    virtual void _unknown_8() {};
    virtual bool isArmor() const;
    virtual bool isBlockPlanterItem() const;
    virtual void _unknown_11() {};
    virtual bool isCandle() const;
    virtual bool isDamageable() const;
    virtual bool isDyeable() const;
    virtual bool isDye() const;
    virtual ItemColor getItemColor() const;
    virtual bool isFertilizer() const;
    virtual bool isFood() const;
    virtual bool isThrowable() const;
    virtual bool isUseable() const;
    virtual bool isTrimAllowed() const;
    virtual ItemComponent* getComponent(const HashedString& a2) const;
    virtual IFoodItemComponent* getFood() const;
    virtual Item& setMaxDamage(int maxDamage);
    virtual Item& setMaxUseDuration(int maxUseDuration);
    virtual std::unique_ptr<CompoundTag> buildNetworkTag() const;
    virtual void initializeFromNetwork(const CompoundTag& tag);
    virtual std::vector<std::string> validateFromNetwork(const CompoundTag&);
    virtual BlockShape getBlockShape() const;
    virtual bool canBeDepleted() const;
    virtual bool canDestroySpecial(const Block& block) const;
    virtual int getLevelDataForAuxValue(int auxValue) const;
    virtual bool isStackedByData() const;
    virtual short getMaxDamage() const;
    virtual int getAttackDamage() const;
    virtual bool isHandEquipped() const;
    virtual bool isGlint(const ItemStackBase& stack) const;
    virtual bool isPattern() const;
    virtual int getPatternIndex() const;
    virtual void _unknown_40() {};
    virtual bool isWearableThroughLootTable(const CompoundTag* userData) const;
    virtual bool canDestroyInCreative() const;
    virtual bool isDestructive(int auxValue) const;
    virtual bool isLiquidClipItem() const;
    virtual bool shouldInteractionWithBlockBypassLiquid(const Block& block) const;
    virtual bool requiresInteract() const;
    virtual void appendFormattedHovertext(const ItemStackBase& stack, Level& level, std::string& hovertext, bool showCategory) const;
    virtual bool isValidRepairItem(const ItemStackBase& source, const ItemStackBase& repairItem, const BaseGameVersion& baseGameVersion) const;
    virtual int getEnchantSlot() const;
    virtual int getEnchantValue() const;
    virtual int getArmorValue() const;
    virtual int getToughnessValue() const;
    virtual void _unknown_53(){};
    virtual bool isValidAuxValue(int auxValue) const;
    virtual int getDamageChance(int unbreaking) const;
    virtual float getViewDamping() const;
    virtual void _unknown_57(){};
    virtual void _unknown_58(){};
    virtual void _unknown_59(){};
    virtual mce::Color getColor(const CompoundTag* userData, const ItemDescriptor& instance) const;
    virtual bool hasCustomColor(const CompoundTag* userData) const;
    virtual void _unknown_62(){};
    virtual void clearColor(ItemStackBase& instance) const;
    virtual void clearColor(CompoundTag* userData) const;
    virtual void setColor(ItemStackBase& instance, const mce::Color& color) const;
    virtual void _unknown_66(){};
    virtual void _unknown_67(){};
    virtual ActorDefinitionIdentifier getActorIdentifier(const ItemStack& a3) const;
    virtual int buildIdAux(short auxValue, const CompoundTag* a3) const;
    virtual bool canUseOnSimTick() const;
    virtual ItemStack& use(ItemStack& itemStack, Player& player) const;
    virtual bool dispense(BlockSource& region, Container& container, int slot, const Vec3& pos, unsigned char face) const;
    virtual ItemUseMethod useTimeDepleted(ItemStack& inoutInstance, Level* level, Player* player) const;
    virtual void releaseUsing(ItemStack& itemStack, Player* player, int durationLeft) const;
    virtual float getDestroySpeed(const ItemStackBase& itemStack, const Block& block) const;
    virtual void hurtActor(ItemStack& itemStack, Actor& actor, Mob& attacker) const;
    virtual void hitActor(ItemStack& itemStack, Actor& actor, Mob& attacker) const;
    virtual void hitBlock(ItemStack& instance, const Block& block, const BlockPos& blockPos, Mob& attacker) const;
    virtual bool mineBlock(ItemStack& instance, const Block& block, int x, int y, int z, Actor* owner) const;
    virtual std::string buildDescriptionName(const ItemStackBase&) const;
    virtual std::string buildDescriptionId(const ItemDescriptor&, const CompoundTag*) const;
    virtual std::string buildEffectDescriptionName(const ItemStackBase&) const;
    virtual void readUserData(ItemStackBase& stack, IDataInput& input, ReadOnlyBinaryStream& underlyingStream) const;
    virtual void writeUserData(const ItemStackBase& stack, IDataOutput& output) const;
    virtual unsigned char getMaxStackSize(const ItemDescriptor& item) const;
    virtual bool inventoryTick(ItemStack& itemStack, Level& level, Actor& owner, int slot, bool selected) const;
    virtual void refreshedInContainer(const ItemStackBase& stack, Level& level) const;
    virtual const HashedString& getCooldownType() const;
    virtual int getCooldownTime() const;
    virtual void fixupCommon(ItemStackBase& stack) const;
    virtual void fixupCommon(ItemStackBase& stack, Level& level) const;
    virtual InHandUpdateType getInHandUpdateType(const Player& player, const ItemInstance& oldItem, const ItemInstance& newItem, bool a5, bool a6) const;
    virtual InHandUpdateType getInHandUpdateType(const Player& player, const ItemStack& oldItem, const ItemStack& newItem, bool a5, bool a6) const;
    virtual bool validFishInteraction(int auxValue) const;
    virtual void enchantProjectile(const ItemStackBase& weapon, Actor& projectile) const;
    virtual ActorLocation getEquipLocation() const;
    virtual Puv::Legacy::LevelSoundEvent getEquipSound() const;
    virtual void _unknown_98(){};
    virtual void _unknown_99(){};
    virtual bool hasSameRelevantUserData(const ItemStackBase&, const ItemStackBase&) const;
    virtual void initClient(Json::Value&, const SemVersion&, bool, const Experiments&);
    virtual Item& setIconInfo(const std::string& name, int index);
    virtual ResolvedItemIconInfo getIconInfo(const ItemStackBase& a3, int a4, bool a5) const;
    virtual std::string getInteractText(const Player&) const;
    virtual int getAnimationFrameFor(Mob* holder, bool asItemEntity, const ItemStack* item, bool shouldAnimate) const { return 0; };
    virtual bool isEmissive(int auxValue) const;
    virtual Brightness getLightEmission(int auxValue) const;
    virtual int getIconYOffset() const;
    virtual bool canBeCharged() const;
    virtual void playSoundIncrementally(const ItemStack& itemStack, Mob& mob) const;
    virtual float getFurnaceXPmultiplier(const ItemStackBase& instance) const;
    virtual std::string getAuxValuesDescription() const;
    virtual bool calculatePlacePos(ItemStackBase& instance, Actor& entity, unsigned char& face, BlockPos& pos) const;

private:
    virtual bool _checkUseOnPermissions(Actor& entity, ItemStackBase& item, const unsigned char& face, const BlockPos& pos) const;
    virtual bool _calculatePlacePos(ItemStackBase& instance, Actor& entity, unsigned char& face, BlockPos& pos) const;
    virtual bool _shouldAutoCalculatePlacePos() const;
    virtual InteractionResult _useOn(ItemStack& instance, Actor& entity, BlockPos pos, unsigned char face, const Vec3& clickPos) const;

public:
    Item(const std::string&, short);
    short getDamageValue(CompoundTag* mUserData) const;
    const std::string& getRawNameId() const;

    // 1.20.51.1 - 48 89 4C 24 ? 53 48 81 EC ? ? ? ? 48 8B D9 45 33 C9
    static void addCreativeItem(ItemRegistryRef*, const Block*);
};
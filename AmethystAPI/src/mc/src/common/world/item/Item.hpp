/// @symbolgeneration
#pragma once
#include <amethyst/Imports.hpp>

#include <mc/src-deps/core/math/Color.hpp>
#include <mc/src/common/SharedPtr.hpp>
#include <mc/src/common/nbt/CompoundTag.hpp>
#include <mc/src/common/world/item/CreativeItemCategory.hpp>
#include <mc/src/common/world/level/block/BlockLegacy.hpp>
#include <mc/src/common/world/item/registry/ItemRegistryRef.hpp>
#include <mc/src/common/CommonTypes.hpp>
#include <mc/src/common/world/level/block/BlockShape.hpp>
#include <mc/src/common/world/item/ResolvedItemIconInfo.hpp>
#include <mc/src/common/world/item/UseAnim.hpp>
#include <mc/src-deps/shared_types/legacy/LevelSoundEvent.hpp>
#include <mc/src/common/world/item/ItemCommandVisibility.hpp>

// Auto-generated: Unknown complete types
enum ItemColor {};
struct ActorDefinitionIdentifier;
enum ItemUseMethod {};
enum InHandUpdateType {};
enum ActorLocation {};

class InteractionResult {
public:
    enum class Result : int32_t {
        SUCCESS = 1,
        SWING = 2,
    };

public:
    int mResult;

    InteractionResult() = default;
    InteractionResult(Result r) : mResult(static_cast<int32_t>(r)) {}
    InteractionResult(const InteractionResult&) = default;
    InteractionResult& operator=(const InteractionResult&) = default;

	operator Result() const { return static_cast<Result>(mResult); }
};

inline InteractionResult::Result operator|(InteractionResult::Result lhs, InteractionResult::Result rhs)
{
    return static_cast<InteractionResult::Result>(
        static_cast<std::underlying_type_t<InteractionResult::Result>>(lhs) |
        static_cast<std::underlying_type_t<InteractionResult::Result>>(rhs));
}

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
class FoodItemComponentLegacy {};
class SeedItemComponentLegacy {};
class CameraItemComponentLegacy {};
class CreativeItemGroupCategory;
class CreativeGroupInfo;

namespace Interactions::Mining {
    enum MineBlockItemEffectType : int32_t {};
}

class ItemTag : public HashedString {

};

/*
 * Represents a type of item in the game, including its properties, behaviors, and interactions.
 */
/** @vptr {48 8D 05 ? ? ? ? 48 89 01 48 83 C1 ? 0F 57 C0 0F 11 01 4C 89 61 ? 4C 89 61 ? 45 8D 44 24} */
class Item {
public:
	class Tier {
	public:
		const int32_t mLevel;
		const int32_t mUses;
		const float mSpeed;
		const int32_t mDamage;
		const int32_t mEnchantmentValue;

		Tier(int32_t level, int32_t uses, float speed, int32_t damage, int32_t enchantmentValue) :
			mLevel(level),
			mUses(uses),
			mSpeed(speed),
			mDamage(damage),
			mEnchantmentValue(enchantmentValue) 
		{
		}

		bool equals(const Tier& other) const {
			return mLevel == other.mLevel &&
				   mUses == other.mUses &&
				   mSpeed == other.mSpeed &&
				   mDamage == other.mDamage &&
				   mEnchantmentValue == other.mEnchantmentValue;
		}

		bool operator==(const Tier& other) const {
			return equals(other);
		}

		bool operator!=(const Tier& other) const {
			return !equals(other);
		}
	};

	class ScopedCreativeGroup {
    public:
		/// @sig {48 89 5C 24 ? 55 56 57 48 83 EC ? 49 8B E8 48 8B F2 48 8B F9 48 8D 4C 24, win-server}
        /// @sig {48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC ? 49 8B F0 48 8B EA 48 8B D9 48 8D 4C 24}
        MC ScopedCreativeGroup(const std::string& name, const ItemInstance& baseItem);

		/// @sig {48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC ? 41 0F B7 68, win-server}
		/// @signature {40 53 48 83 EC ? 49 8B 40 ? 48 8B D9 45 0F B7 48}
        MC ScopedCreativeGroup(const std::string& name, const Block* block, const CompoundTag* data);

		/// @sig {40 53 48 83 EC ? 48 8D 4C 24 ? E8 ? ? ? ? 48 8B C8, win-server}
		/// @sig {40 53 48 83 EC ? 48 8D 4C 24 ? E8 ? ? ? ? 48 8B C8, win-client}
        MC ~ScopedCreativeGroup(); 
	};

    MC static uintptr_t $vtable_for_this;
    std::string mTextureAtlasFile;
    int mFrameCount;
    bool mAnimatesInToolbar;
    bool mIsMirroredArt;
    UseAnim mUseAnim;
    std::string mHoverTextColorFormat;
    int mIconFrame;
    int mAtlasFrame;
    int mAtlasTotalFrames;
    std::string mIconName;
    std::string mAtlasName;
    uint8_t mMaxStackSize;
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
    BaseGameVersion mMinRequiredBaseGameVersion;
    WeakPtr<BlockLegacy> mLegacyBlock;
    CreativeItemCategory mCreativeCategory;
    Item* mCraftingRemainingItem;
    std::string mCreativeGroup;
    float mFurnaceBurnIntervalModifier;
    float mFurnaceXPmultiplier;
    bool mIsHiddenInCommands;
    Interactions::Mining::MineBlockItemEffectType mMineBlockType;
    std::unique_ptr<FoodItemComponentLegacy> mFoodComponentLegacy;
    std::unique_ptr<SeedItemComponentLegacy> mSeedComponent;
    std::unique_ptr<CameraItemComponentLegacy> mCameraComponentLegacy;
    std::vector<std::function<void()>> mOnResetBAIcallbacks;
    std::vector<ItemTag> mTags;

	/** @sig {E8 ? ? ? ? 88 9F ? ? ? ? 48 8D 05} */
    MC Item(const std::string& identifier, short numId);

	/** @sig {E8 ? ? ? ? 88 9F ? ? ? ? 48 8D 05} */
	MC static void $constructor(Item* self, const std::string& identifier, short numId);

    /** @vidx {000} */ MC virtual ~Item();
	/** @vidx {001} */ MC virtual bool initServer(const Json::Value& config, const SemVersion& version, bool unk2, const Experiments& experiments);
	/** @vidx {002} */ MC virtual void tearDown();
	/** @vidx {003} */ MC virtual Item& setDescriptionId(const std::string& descriptionId);
	/** @vidx {004} */ MC virtual const std::string& getDescriptionId() const;
	/** @vidx {005} */ MC virtual int getMaxUseDuration(const ItemStack* item) const;
	/** @vidx {006} */ MC virtual bool isMusicDisk() const;
	/** @vidx {007} */ MC virtual void executeEvent(ItemStackBase& stack, const std::string& eventName, RenderParams& renderParams) const;
	/** @vidx {008} */ MC virtual bool isComponentBased() const;
	/** @vidx {009} */ MC virtual bool isHumanoidArmor() const;
	/** @vidx {010} */ MC virtual bool isBlockPlanterItem() const;
	/** @vidx {011} */ MC virtual bool isBucket() const;
	/** @vidx {012} */ MC virtual bool isCandle() const;
	/** @vidx {013} */ MC virtual bool isDamageable() const;
	/** @vidx {014} */ MC virtual bool isDyeable() const;
	/** @vidx {015} */ MC virtual bool isDye() const;
	/** @vidx {016} */ MC virtual ItemColor getItemColor() const;
	/** @vidx {017} */ MC virtual bool isFertilizer() const;
	/** @vidx {018} */ MC virtual bool isFood() const;
	/** @vidx {019} */ MC virtual bool isThrowable() const;
	/** @vidx {020} */ MC virtual bool isUseable() const;
	/** @vidx {021} */ MC virtual bool isTrimAllowed() const;
	/** @vidx {022} */ MC virtual ItemComponent* getComponent(const HashedString& componentName) const;
	/** @vidx {023} */ MC virtual IFoodItemComponent* getFood() const;
	/** @vidx {024} */ MC virtual Item& setMaxDamage(int maxDamage);
	/** @vidx {025} */ MC virtual Item& setMaxUseDuration(int duration);
	/** @vidx {026} */ MC virtual std::unique_ptr<CompoundTag> buildNetworkTag() const;
	/** @vidx {027} */ MC virtual void initializeFromNetwork(const CompoundTag& userData);
	/** @vidx {028} */ MC virtual std::vector<std::string> validateFromNetwork(const CompoundTag& userData);
	/** @vidx {029} */ MC virtual BlockShape getBlockShape() const;
	/** @vidx {030} */ MC virtual bool canBeDepleted() const;
	/** @vidx {031} */ MC virtual bool canDestroySpecial(const Block& block) const;
	/** @vidx {032} */ MC virtual int getLevelDataForAuxValue(int auxValue) const;
	/** @vidx {033} */ MC virtual bool isStackedByData() const;
	/** @vidx {034} */ MC virtual short getMaxDamage() const;
	/** @vidx {035} */ MC virtual int getAttackDamage() const;
	/** @vidx {036} */ MC virtual float getAttackDamageBonus(const Actor& actor, float unk1) const;
	/** @vidx {037} */ MC virtual bool isHandEquipped() const;
	/** @vidx {038} */ MC virtual bool isGlint(const ItemStackBase& stack) const;
	/** @vidx {039} */ MC virtual bool isPattern() const;
	/** @vidx {040} */ MC virtual int getPatternIndex() const;
	/** @vidx {041} */ MC virtual bool showsDurabilityInCreative() const;
	/** @vidx {042} */ MC virtual bool isWearableThroughLootTable(const CompoundTag* unk0) const;
	/** @vidx {043} */ MC virtual bool canDestroyInCreative() const;
	/** @vidx {044} */ MC virtual bool isDestructive(int unk0) const;
	/** @vidx {045} */ MC virtual bool isLiquidClipItem() const;
	/** @vidx {046} */ MC virtual bool shouldInteractionWithBlockBypassLiquid(const Block& block) const;
	/** @vidx {047} */ MC virtual bool requiresInteract() const;
	/** @vidx {048} */ MC virtual void appendFormattedHovertext(const ItemStackBase& stack, Level& level, std::string& outText, bool showCategory) const;
	/** @vidx {049} */ MC virtual bool isValidRepairItem(const ItemStackBase& targetStack, const ItemStackBase& repairStack, const BaseGameVersion& version) const;
	/** @vidx {050} */ MC virtual int getEnchantSlot() const;
	/** @vidx {051} */ MC virtual int getEnchantValue() const;
	/** @vidx {052} */ MC virtual int getArmorValue() const;
	/** @vidx {053} */ MC virtual int getToughnessValue() const;
	/** @vidx {054} */ MC virtual Puv::Legacy::LevelSoundEvent getBreakSound() const;
	/** @vidx {055} */ MC virtual bool isComplex() const;
	/** @vidx {056} */ MC virtual bool isValidAuxValue(int auxValue) const;
	/** @vidx {057} */ MC virtual int getDamageChance(int unk0) const;
	/** @vidx {058} */ MC virtual float getViewDamping() const;
	/** @vidx {059} */ MC virtual bool uniqueAuxValues() const;
	/** @vidx {060} */ MC virtual bool isActorPlacerItem() const;
	/** @vidx {061} */ MC virtual bool isMultiColorTinted(const ItemStack& stack) const;
	/** @vidx {062} */ MC virtual mce::Color getColor(const CompoundTag* unk0, const ItemDescriptor& descriptor) const;
	/** @vidx {064} */ MC virtual bool hasCustomColor(const ItemStackBase& stack) const;
	/** @vidx {063} */ MC virtual bool hasCustomColor(const CompoundTag* unk0) const;
	/** @vidx {065} */ MC virtual void clearColor(ItemStackBase& stack) const;
	/** @vidx {066} */ MC virtual void setColor(ItemStackBase& stack, const mce::Color& color) const;
	/** @vidx {067} */ MC virtual mce::Color getBaseColor(const ItemStack& stack) const;
	/** @vidx {068} */ MC virtual mce::Color getSecondaryColor(const ItemStack& stack) const;
	/** @vidx {069} */ MC virtual ActorDefinitionIdentifier getActorIdentifier(const ItemStack& stack) const;
	/** @vidx {070} */ MC virtual int buildIdAux(short unk0, const CompoundTag* unk1) const;
	/** @vidx {071} */ MC virtual bool canUseOnSimTick() const;
	/** @vidx {072} */ MC virtual ItemStack& use(ItemStack& stack, Player& player) const;
	/** @vidx {073} */ MC virtual Actor* createProjectileActor(BlockSource& source, const ItemStack& stack, const Vec3& pos, const Vec3& velocity) const;
	/** @vidx {074} */ MC virtual bool dispense(BlockSource& source, Container& container, int slot, const Vec3& pos, FacingID facing) const;
	/** @vidx {075} */ MC virtual ItemUseMethod useTimeDepleted(ItemStack& stack, Level* level, Player* player) const;
	/** @vidx {076} */ MC virtual void releaseUsing(ItemStack& stack, Player* player, int duration) const;
	/** @vidx {077} */ MC virtual float getDestroySpeed(const ItemStackBase& stack, const Block& block) const;
	/** @vidx {078} */ MC virtual void hurtActor(ItemStack& stack, Actor& actor, Mob& attacker) const;
	/** @vidx {079} */ MC virtual void hitActor(ItemStack& stack, Actor& actor, Mob& attacker) const;
	/** @vidx {080} */ MC virtual void hitBlock(ItemStack& stack, const Block& block, const BlockPos& pos, Mob& mob) const;
	/** @vidx {081} */ MC virtual bool mineBlock(ItemStack& stack, const Block& block, int x, int y, int z, Actor* owner) const;
	/** @vidx {082} */ MC virtual std::string buildDescriptionName(const ItemStackBase& stack) const;
	/** @vidx {083} */ MC virtual std::string buildDescriptionId(const ItemDescriptor& descriptor, const CompoundTag* tag) const;
	/** @vidx {084} */ MC virtual std::string buildEffectDescriptionName(const ItemStackBase& stack) const;
	/** @vidx {085} */ MC virtual void readUserData(ItemStackBase& stack, IDataInput& input, ReadOnlyBinaryStream& stream) const;
	/** @vidx {086} */ MC virtual void writeUserData(const ItemStackBase& stack, IDataOutput& output) const;
	/** @vidx {087} */ MC virtual uint8_t getMaxStackSize(const ItemDescriptor& descriptor) const;
	/** @vidx {088} */ MC virtual bool inventoryTick(ItemStack& stack, Level& level, Actor& actor, int unk3, bool unk4) const;
	/** @vidx {089} */ MC virtual void refreshedInContainer(const ItemStackBase& stack, Level& level) const;
	/** @vidx {090} */ MC virtual const HashedString& getCooldownType() const;
	/** @vidx {091} */ MC virtual int getCooldownTime() const;
	/** @vidx {093} */ MC virtual void fixupCommon(ItemStackBase& stack) const;
    /** @vidx {092} */ MC virtual void fixupCommon(ItemStackBase& stack, Level& level) const;
	/** @vidx {094} */ MC virtual InHandUpdateType getInHandUpdateType(const Player& player, const ItemStack& currentStack, const ItemStack& prevStack, bool unk3, bool unk4) const;
	/** @vidx {095} */ MC virtual bool validFishInteraction(int unk0) const;
	/** @vidx {096} */ MC virtual void enchantProjectile(const ItemStackBase& stack, Actor& actor) const;
	/** @vidx {097} */ MC virtual ActorLocation getEquipLocation() const;
	/** @vidx {098} */ MC virtual Puv::Legacy::LevelSoundEvent getEquipSound() const;
	/** @vidx {099} */ MC virtual bool shouldSendInteractionGameEvents() const;
	/** @vidx {100} */ MC virtual bool useInterruptedByAttacking() const;
	/** @vidx {101} */ MC virtual bool hasSameRelevantUserData(const ItemStackBase& stack, const ItemStackBase& prevStack) const;
	/** @vidx {102} */ MC virtual void initClient(const Json::Value& config, const SemVersion& version, bool unk2, const Experiments& experiments);
	/** @vidx {103} */ MC virtual Item& setIconInfo(const std::string& iconName, int iconFrame);
	/** @vidx {104} */ MC virtual ResolvedItemIconInfo getIconInfo(const ItemStackBase& stack, int unk1, bool unk2) const;
	/** @vidx {105} */ MC virtual std::string getInteractText(const Player& player) const;
	/** @vidx {106} */ MC virtual int getAnimationFrameFor(Mob* mob, bool unk1, const ItemStack* stack, bool unk3) const;
	/** @vidx {107} */ MC virtual bool isEmissive(int unk0) const;
	/** @vidx {108} */ MC virtual Brightness getLightEmission(int unk0) const;
	/** @vidx {109} */ MC virtual int getIconYOffset() const;
	/** @vidx {110} */ MC virtual bool canBeCharged() const;
	/** @vidx {111} */ MC virtual void playSoundIncrementally(const ItemStack& stack, Mob& mob) const;
	/** @vidx {112} */ MC virtual float getFurnaceXPmultiplier(const ItemStackBase& stack) const;
	/** @vidx {113} */ MC virtual std::string getAuxValuesDescription() const;
	/** @vidx {114} */ MC virtual bool calculatePlacePos(ItemStackBase& stack, Actor& actor, FacingID& face, BlockPos& pos) const;
	/** @vidx {115} */ MC virtual bool _checkUseOnPermissions(Actor& actor, ItemStackBase& stack, const FacingID& face, const BlockPos& pos) const;
	/** @vidx {116} */ MC virtual bool _calculatePlacePos(ItemStackBase& stack, Actor& actor, FacingID& face, BlockPos& pos) const;
	/** @vidx {117} */ MC virtual bool _shouldAutoCalculatePlacePos() const;
	/** @vidx {118} */ MC virtual InteractionResult _useOn(ItemStack& stack, Actor& actor, BlockPos pos, FacingID face, const Vec3& hit) const;

	/// @sig {40 53 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 84 24 ? ? ? ? 48 8B D9 48 89 8C 24 ? ? ? ? 45 33 C9, win-server}
	/** @sig {48 89 4C 24 ? 53 48 81 EC ? ? ? ? 48 8B D9 45 33 C9} */
    MC static void addCreativeItem(ItemRegistryRef registry, const Block& block);

	/// @sig {48 89 5C 24 ? 55 56 57 41 56 41 57 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 84 24 ? ? ? ? 48 8B EA 48 8B F1 48 89 8C 24, win-server}
    /** @sig {48 89 5C 24 ? 48 89 74 24 ? 57 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 84 24 ? ? ? ? 48 8B FA 48 8B F1 48 89 8C 24} */
    MC static void addCreativeItem(ItemRegistryRef registry, const ItemInstance& item);

	//MC static std::unique_ptr<std::set<short>> mServerItemsUsedInCreativeItems;

	/// @address {0x3412640, win-server}
	/// @address {0x597AB10}
    MC static CreativeItemGroupCategory* mActiveCreativeItemCategory; 

	/// @address {0x3412630, win-server}
	/// @address {0x597AB18}
    MC static CreativeGroupInfo* mActiveCreativeGroupInfo;

	CreativeItemCategory getCreativeCategory() const;
	const std::string& getCreativeGroup() const;
	short getDamageValue(const CompoundTag* userData) const;
	int getFrameCount() const;
	const std::string& getFullItemName() const;
	const HashedString& getFullNameHash() const;
	float getFurnaceBurnIntervalMultipler() const;
	std::string getHoverTextColor(const ItemStackBase& stack) const;
	short getId() const;
	const WeakPtr<const BlockLegacy>& getLegacyBlock() const;
	Interactions::Mining::MineBlockItemEffectType getMineBlockType() const;
	const std::string& getNamespace() const;
	const HashedString& getRawNameHash() const;
	const std::string& getRawNameId() const;
	const BaseGameVersion& getRequiredBaseGameVersion() const;
	UseAnim getUseAnimation() const;
	void setDamageValue(ItemStackBase& stack, short value) const;
	Item& setAllowOffhand(bool allowOffhand);

	/// @signature {48 89 5C 24 ? 55 56 57 41 56 41 57 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 84 24 ? ? ? ? 44 8B FA}
	MC Item& setCategory(CreativeItemCategory category);

	Item& setCreativeGroup(const std::string& group);
	Item& setExplodable(bool isExplodable);
	Item& setFireResistant(bool isFireResistant);
	Item& setFurnaceBurnIntervalMultiplier(float multiplier);
	Item& setFurnaceXPmultiplier(float multiplier);
	Item& setHandEquipped();
	Item& setHoverTextColorFormat(std::string_view format);
	Item& setIsGlint(bool isGlint);
	Item& setIsHiddenInCommands(ItemCommandVisibility visibility);
	Item& setIsMirroredArt(bool isMirroredArt);
	Item& setMaxStackSize(uint8_t maxStackSize);
	Item& setMinRequiredBaseGameVersion(const BaseGameVersion& version);
	Item& setRequiresWorldBuilder(bool requiresWorldBuilder);
	Item& setShouldDespawn(bool shouldDespawn);
	Item& setStackedByData(bool stackedByData);
	Item& addTag(const ItemTag& tag);
	Item& addTag(const HashedString& tag);
    Item& addTags(std::initializer_list<std::reference_wrapper<const ItemTag>> tags);
	Item& setUseAnimation(UseAnim useAnim);
	bool hasTag(const ItemTag& tag) const;
	bool hasTag(const HashedString& tag) const;
	bool isAnimatedInToolbar() const;
	bool isCamera() const;
	bool isExplodable() const;
	bool isFireResistant() const;
	bool isMirroredArt() const;
	bool isSeed() const;
	bool shouldDespawn() const;
	bool allowOffhand() const;
	void clearTags();
};

static_assert(sizeof(Item) == 600);
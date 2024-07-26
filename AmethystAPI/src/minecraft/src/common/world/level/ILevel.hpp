#pragma once
#include <gsl/gsl>
#include <minecraft/src-deps/core/utility/NonOwnerPointer.hpp>
#include <minecraft/src-deps/core/utility/AutomaticID.hpp>
#include <minecraft/src/common/gamerefs/WeakRef.hpp>
#include <minecraft/src-deps/core/file/Path.hpp>
#include <minecraft/src/common/world/level/ChunkPos.hpp>
#include <minecraft/src/common/world/level/Tick.hpp>
#include <minecraft/src/common/world/level/storage/StorageVersion.hpp>
#include <minecraft/src/common/world/level/block/LevelEvent.hpp>
#include <minecraft/src/common/gamerefs/OwnerPtr.hpp>
#include <minecraft/src/common/world/phys/Vec3.hpp>

// Auto-generated: Forward declarations
namespace PlayerCapabilities { struct ISharedController; }
namespace PositionTrackingDB { class PositionTrackingDBClient; }
namespace cg { class ImageBuffer; }
namespace mce {class UUID; class Color; }
namespace Social { class GamePublishSetting; }
namespace Puv::Legacy { enum LevelSoundEvent; }
class EntityContext;
struct ActorUniqueID;
class LevelSettings;
class LevelData;
class Experiments;
class ChunkTickRangeManager;
class PortalForcer;
class Player;
class Actor;
class Spawner;
class ProjectileFactory;
class ActorDefinitionGroup;
class BlockDefinitionGroup;
class PropertyGroupManager;
class AutomationBehaviorTreeGroup;
class BehaviorFactory;
class InternalComponentRegistry;
class BlockSource;
class LevelChunk;
class Mob;
class IMinecraftEventing;
class BiomeManager;
class LevelListener;
class ActorDamageSource;
class Explosion;
class BlockPos;
class NavigationComponent;
class PhotoStorage;
class TickingAreasManager;
struct ActorDefinitionIdentifier;
class IConstBlockSource;
class PlayerEventCoordinator;
class ServerPlayerEventCoordinator;
class ClientPlayerEventCoordinator;
class ActorEventCoordinator;
class BlockEventCoordinator;
class ItemEventCoordinator;
class ServerNetworkEventCoordinator;
class ScriptingEventCoordinator;
class ScriptDeferredEventCoordinator;
class LevelEventCoordinator;
class CompoundTag;
class UserEntityIdentifierComponent;
class Block;
struct Bounds;
class ChunkSource;
class NetworkIdentifier;
class _TickPtr;
class Particle;
class HashedString;
class MolangVariableMap;
struct ResolvedItemIconInfo;
class SavedDataStorage;
class MapItemSavedData;
class TaskGroup;
class ActorInfoRegistry;
class EntitySystems;
class TagRegistry;
struct PlayerMovementSettings;
class SerializedSkin;
class PacketSender;
class HitResult;
struct AdventureSettings;
class GameRules;
class Abilities;
class PermissionsHandler;
struct ScreenshotOptions;
class LootTables;
class LayeredAbilities;
class Recipes;
class BlockReducer;
class ItemComponentPacket;
class BlockLegacy;
class Level;
class ChangeDimensionRequest;
class BossEventSubscriptionManager;
class ActorAnimationGroup;
class ActorAnimationControllerGroup;
class Difficulty;
class DimensionConversionData;
class StrictEntityContext;
class ActorRuntimeID;
class StructureManager;
class Path;
class PlayerSleepStatus;
class GameType;
class EducationLevelSettings;
class ActorEvent;
class IUnknownBlockTypeRegistry;
class NetEventCallback;
class LevelSoundManager;
class SoundPlayerInterface;
class BlockTypeRegistry;
class ChunkViewSource;
class WeakEntityRef;
class Dimension;
class TickingAreaList;
enum class ParticleType : int {};

class ILevel : public Bedrock::EnableNonOwnerReferences {
public:
    /**@vIndex {0}*/
    virtual ~ILevel();

    /**@vIndex {1}*/
    virtual bool initialize(const std::string&, const LevelSettings&, LevelData*, const Experiments&, const std::string*);

    /**@vIndex {2}*/
    virtual void startLeaveGame();

    /**@vIndex {3}*/
    virtual bool isLeaveGameDone();

    /**@vIndex {4}*/
    virtual WeakRef<Dimension> getOrCreateDimension(DimensionType);

    /**@vIndex {5}*/
    virtual WeakRef<Dimension> getDimension(DimensionType) const;

    /**
    * @vIndex {6}
    * @brief Validates that the DimensionType != Undefined, in that case resets it to the Overworld
    */
    virtual DimensionType getLastOrDefaultSpawnDimensionId(DimensionType) const;

    /**@vIndex {7}*/
    virtual void _unknown_7();

    /**@vIndex {8}*/
    virtual void _unknown_8();

    /**@vIndex {9}*/
    virtual void _unknown_9();

    /**@vIndex {10}*/
    virtual void _unknown_10();

    /**@vIndex {11}*/
    virtual unsigned int getChunkTickRange() const;

    /**@vIndex {12}*/
    virtual const ChunkTickRangeManager& getChunkTickRangeManager() const;

    /**@vIndex {13}*/
    virtual PortalForcer& getPortalForcer();

    /**@vIndex {14}*/
    virtual void requestPlayerChangeDimension(Player&, ChangeDimensionRequest&&);

    /**@vIndex {15}*/
    virtual void entityChangeDimension(Actor&, DimensionType, std::optional<Vec3>);

    /**@vIndex {16}*/
    virtual Spawner& getSpawner() const;

    /**@vIndex {17}*/
    virtual gsl::not_null<Bedrock::NonOwnerPointer<BossEventSubscriptionManager>> getBossEventSubscriptionManager();

    /**@vIndex {18}*/
    virtual ProjectileFactory& getProjectileFactory() const;

    /**@vIndex {19}*/
    virtual ActorDefinitionGroup* getEntityDefinitions() const;

    /**@vIndex {20}*/
    virtual gsl::not_null<Bedrock::NonOwnerPointer<ActorAnimationGroup>> getActorAnimationGroup() const;

    /**@vIndex {21}*/
    virtual Bedrock::NonOwnerPointer<ActorAnimationControllerGroup> getActorAnimationControllerGroup() const;

    /**@vIndex {22}*/
    virtual BlockDefinitionGroup* getBlockDefinitions() const;

    /**@vIndex {23}*/
    virtual void _unknown_23();

    /**@vIndex {24}*/
    virtual void _unknown_24();

    /**@vIndex {25}*/
    virtual PropertyGroupManager& getActorPropertyGroup() const;

    /**@vIndex {26}*/
    virtual void _unknown_26();

    /**@vIndex {27}*/
    virtual void _unknown_27();

    /**@vIndex {28}*/
    virtual bool getDisablePlayerInteractions() const;

    /**@vIndex {29}*/
    virtual void setDisablePlayerInteractions(bool);

    /**@vIndex {30}*/
    virtual AutomationBehaviorTreeGroup& getAutomationBehaviorTreeGroup() const;

    /**@vIndex {31}*/
    virtual BehaviorFactory& getBehaviorFactory() const;

    /**@vIndex {32}*/
    virtual Difficulty getDifficulty() const;

    /**@vIndex {33}*/
    virtual InternalComponentRegistry& getInternalComponentRegistry() const;

    /**@vIndex {34}*/
    virtual DimensionConversionData getDimensionConversionData() const;

    /**@vIndex {35}*/
    virtual float getSpecialMultiplier(DimensionType) const;

    /**@vIndex {36}*/
    virtual bool hasCommandsEnabled() const;

    /**@vIndex {37}*/
    virtual bool useMsaGamertagsOnly() const;

    /**@vIndex {38}*/
    virtual void setMsaGamertagsOnly(bool);

    /**@vIndex {39}*/
    virtual Actor* addEntity(BlockSource&, OwnerPtr<EntityContext>);

    /**@vIndex {40}*/
    virtual Actor* addGlobalEntity(BlockSource&, OwnerPtr<EntityContext>);

    /**@vIndex {41}*/
    virtual Actor* addAutonomousEntity(BlockSource&, OwnerPtr<EntityContext>);

    /**@vIndex {42}*/
    virtual void addUser(OwnerPtr<EntityContext>);

    /**@vIndex {43}*/
    virtual Actor* addDisplayEntity(BlockSource&, OwnerPtr<EntityContext>);

    /**@vIndex {44}*/
    virtual void removeDisplayEntity(WeakEntityRef);

    /**@vIndex {45}*/
    virtual void suspendPlayer(Player&);

    /**@vIndex {46}*/
    virtual void resumePlayer(Player&);

    /**@vIndex {47}*/
    virtual bool isPlayerSuspended(Player&) const;

    /**@vIndex {48}*/
    virtual OwnerPtr<EntityContext> removeActorAndTakeEntity(WeakEntityRef);

    /**@vIndex {49}*/
    virtual OwnerPtr<EntityContext> removeActorFromWorldAndTakeEntity(WeakEntityRef);

    /**@vIndex {50}*/
    virtual OwnerPtr<EntityContext> takeEntity(WeakEntityRef, LevelChunk&);

    /**@vIndex {51}*/
    virtual StrictEntityContext fetchStrictEntity(ActorUniqueID, bool) const;

    /**@vIndex {52}*/
    virtual Actor* fetchEntity(ActorUniqueID, bool) const;

    /**@vIndex {53}*/
    virtual Actor* getRuntimeEntity(ActorRuntimeID, bool) const;

    /**@vIndex {54}*/
    virtual Mob* getMob(ActorUniqueID) const;

    /**@vIndex {55}*/
    virtual Player* getPlayer(ActorUniqueID) const;

    /**@vIndex {56}*/
    virtual Player* getPlayer(const mce::UUID&) const;

    /**@vIndex {57}*/
    virtual Player* getPlayer(const std::string&) const;

    /**@vIndex {58}*/
    virtual Player* getPlayerByXuid(const std::string&) const;

    /**@vIndex {59}*/
    virtual Player* getPlatformPlayer(const std::string&) const;

    /**@vIndex {60}*/
    virtual Player* getPlayerFromServerId(const std::string&) const;

    /**@vIndex {61}*/
    virtual Player* getRuntimePlayer(ActorRuntimeID) const;

    /**@vIndex {62}*/
    virtual int getNumRemotePlayers();

    /**@vIndex {63}*/
    virtual Player* getPrimaryLocalPlayer() const;

    /**@vIndex {64}*/
    virtual IMinecraftEventing& getEventing();

    /**@vIndex {65}*/
    virtual mce::Color getPlayerColor(const Player&) const;

    /**@vIndex {66}*/
    virtual const Tick& getCurrentTick() const;

    /**@vIndex {67}*/
    virtual const Tick getCurrentServerTick() const;

    /**@vIndex {68}*/
    virtual void _unknown_68();

    /**@vIndex {69}*/
    virtual void _unknown_69();

    /**@vIndex {70}*/
    virtual void _unknown_70();

    /**@vIndex {71}*/
    virtual void _unknown_71();

    /**@vIndex {72}*/
    virtual void _unknown_72();

    /**@vIndex {73}*/
    virtual void _unknown_73();

    /**@vIndex {74}*/
    virtual void _unknown_74();

    /**@vIndex {75}*/
    virtual void _unknown_75();

    /**@vIndex {76}*/
    virtual void _unknown_76();

    /**@vIndex {77}*/
    virtual void _unknown_77();

    /**@vIndex {78}*/
    virtual gsl::not_null<Bedrock::NonOwnerPointer<StructureManager>> getStructureManager();

    /**@vIndex {79}*/
    virtual const gsl::not_null<Bedrock::NonOwnerPointer<StructureManager>> getStructureManager() const;

    /**@vIndex {80}*/
    virtual void _unknown_80();

    /**@vIndex {81}*/
    virtual void _unknown_81();

    /**@vIndex {82}*/
    virtual void _unknown_82();

    /**@vIndex {83}*/
    virtual void _unknown_83();

    /**@vIndex {84}*/
    virtual BiomeManager& getBiomeManager();

    /**@vIndex {85}*/
    virtual const BiomeManager& getBiomeManager() const;

    /**@vIndex {86}*/
    virtual void _unknown_86();

    /**@vIndex {87}*/
    virtual void _unknown_87();

    /**@vIndex {88}*/
    virtual void _unknown_88();

    /**@vIndex {89}*/
    virtual void _unknown_89();

    /**@vIndex {90}*/
    virtual void _unknown_90();

    /**@vIndex {91}*/
    virtual void _unknown_91();

    /**@vIndex {92}*/
    virtual void addListener(LevelListener&);

    /**@vIndex {93}*/
    virtual void removeListener(LevelListener&);

    /**@vIndex {94}*/
    virtual void tickEntities();

    /**@vIndex {95}*/
    virtual void tickEntitySystems();

    /**@vIndex {96}*/
    virtual void _unknown_96();

    /**@vIndex {97}*/
    virtual void _unknown_97();

    /**@vIndex {98}*/
    virtual void onPlayerDeath(Player&, const ActorDamageSource&);

    /**@vIndex {99}*/
    virtual void tick();

    /**@vIndex {100}*/
    virtual bool explode(Explosion&);

    /**@vIndex {101}*/
    virtual bool explode(BlockSource&, Actor*, const Vec3&, float, bool, bool, float, bool);

    /**@vIndex {102}*/
    virtual void spawnParticleEffect(const std::string&, const Vec3&, Dimension*);

    /**@vIndex {103}*/
    virtual void denyEffect(BlockSource&, const Vec3&);

    /**@vIndex {104}*/
    virtual void potionSplash(const Vec3&, const mce::Color&, bool);

    /**@vIndex {105}*/
    virtual bool extinguishFire(BlockSource&, const BlockPos&, unsigned char, Actor*);

    /**@vIndex {106}*/
    virtual std::unique_ptr<Path> findPath(Actor&, Actor&, NavigationComponent&);

    /**@vIndex {107}*/
    virtual std::unique_ptr<Path> findPath(Actor&, int, int, int, NavigationComponent&);

    /**@vIndex {108}*/
    virtual void updateSleepingPlayerList();

    /**@vIndex {109}*/
    virtual void setSleepStatus(const PlayerSleepStatus&);

    /**@vIndex {110}*/
    virtual PlayerSleepStatus getSleepStatus() const;

    /**@vIndex {111}*/
    virtual int getTime() const;

    /**@vIndex {112}*/
    virtual void setTime(int);

    /**@vIndex {113}*/
    virtual unsigned int getSeed();

    /**@vIndex {114}*/
    virtual const BlockPos& getDefaultSpawn() const;

    /**@vIndex {115}*/
    virtual void setDefaultSpawn(const BlockPos&);

    /**@vIndex {116}*/
    virtual void _unknown_116();

    /**@vIndex {117}*/
    virtual void setDefaultGameType(GameType);

    /**@vIndex {118}*/
    virtual GameType getDefaultGameType() const;

    /**@vIndex {119}*/
    virtual void setDifficulty(Difficulty);

    /**@vIndex {120}*/
    virtual void setMultiplayerGameIntent(bool);

    /**@vIndex {121}*/
    virtual bool getMultiplayerGameIntent() const;

    /**@vIndex {122}*/
    virtual void setMultiplayerGame(bool);

    /**@vIndex {123}*/
    virtual bool isMultiplayerGame() const;

    /**@vIndex {124}*/
    virtual void setLANBroadcastIntent(bool);

    /**@vIndex {125}*/
    virtual bool getLANBroadcastIntent() const;

    /**@vIndex {126}*/
    virtual void setLANBroadcast(bool);

    /**@vIndex {127}*/
    virtual bool getLANBroadcast() const;

    /**@vIndex {128}*/
    virtual void setXBLBroadcastIntent(Social::GamePublishSetting);

    /**@vIndex {129}*/
    virtual Social::GamePublishSetting getXBLBroadcastIntent() const;

    /**@vIndex {130}*/
    virtual bool hasXBLBroadcastIntent() const;

    /**@vIndex {131}*/
    virtual void setXBLBroadcastMode(Social::GamePublishSetting);

    /**@vIndex {132}*/
    virtual Social::GamePublishSetting getXBLBroadcastMode() const;

    /**@vIndex {133}*/
    virtual bool hasXBLBroadcast() const;

    /**@vIndex {134}*/
    virtual void setPlatformBroadcastIntent(Social::GamePublishSetting);

    /**@vIndex {135}*/
    virtual Social::GamePublishSetting getPlatformBroadcastIntent() const;

    /**@vIndex {136}*/
    virtual bool hasPlatformBroadcastIntent() const;

    /**@vIndex {137}*/
    virtual void setPlatformBroadcastMode(Social::GamePublishSetting);

    /**@vIndex {138}*/
    virtual Social::GamePublishSetting getPlatformBroadcastMode() const;

    /**@vIndex {139}*/
    virtual bool hasPlatformBroadcast() const;

    /**@vIndex {140}*/
    virtual void setHasLockedBehaviorPack(bool);

    /**@vIndex {141}*/
    virtual void setHasLockedResourcePack(bool);

    /**@vIndex {142}*/
    virtual void setCommandsEnabled(bool);

    /**@vIndex {143}*/
    virtual void setWorldTemplateOptionsUnlocked();

    /**@vIndex {144}*/
    virtual bool hasLevelStorage() const;

    /**@vIndex {145}*/
    virtual void _unknown_145();

    /**@vIndex {146}*/
    virtual void _unknown_146();

    /**@vIndex {147}*/
    virtual LevelData& getLevelData();

    /**@vIndex {148}*/
    virtual const LevelData& getLevelData() const;

    /**@vIndex {149}*/
    virtual PhotoStorage& getPhotoStorage();

    /**@vIndex {150}*/
    virtual void createPhotoStorage();

    /**@vIndex {151}*/
    virtual void setEducationLevelSettings(EducationLevelSettings);

    /**@vIndex {152}*/
    virtual const std::optional<EducationLevelSettings>& getEducationLevelSettings() const;

    /**@vIndex {153}*/
    virtual void save();

    /**@vIndex {154}*/
    virtual void saveLevelData();

    /**@vIndex {155}*/
    virtual void saveGameData();

    /**@vIndex {156}*/
    virtual std::shared_ptr<void*> requestTimedStorageDeferment();

    /**@vIndex {157}*/
    virtual TickingAreasManager& getTickingAreasMgr();

    /**@vIndex {158}*/
    virtual void addTickingAreaList(DimensionType, const std::shared_ptr<TickingAreaList>&);

    /**@vIndex {159}*/
    virtual void sendServerLegacyParticle(ParticleType, const Vec3&, const Vec3&, int);

    /**@vIndex {160}*/
    virtual void playSound(DimensionType, Puv::Legacy::LevelSoundEvent, const Vec3&, int, const ActorDefinitionIdentifier&, bool, bool);

    /**@vIndex {161}*/
    virtual void playSound(const IConstBlockSource&, Puv::Legacy::LevelSoundEvent, const Vec3&, int, const ActorDefinitionIdentifier&, bool, bool);

    /**@vIndex {162}*/
    virtual void playSound(const std::string&, const Vec3&, float, float);

    /**@vIndex {163}*/
    virtual void playSound(Puv::Legacy::LevelSoundEvent, const Vec3&, float, float);

    /**@vIndex {164}*/
    virtual void playSound(Puv::Legacy::LevelSoundEvent, const Vec3&, int, const ActorDefinitionIdentifier&, bool, bool);

    /**@vIndex {165}*/
    virtual PlayerEventCoordinator& getRemotePlayerEventCoordinator();

    /**@vIndex {166}*/
    virtual ServerPlayerEventCoordinator& getServerPlayerEventCoordinator();

    /**@vIndex {167}*/
    virtual ClientPlayerEventCoordinator& getClientPlayerEventCoordinator();

    /**@vIndex {168}*/
    virtual ActorEventCoordinator& getActorEventCoordinator();

    /**@vIndex {169}*/
    virtual BlockEventCoordinator& getBlockEventCoordinator();

    /**@vIndex {170}*/
    virtual ItemEventCoordinator& getItemEventCoordinator();

    /**@vIndex {171}*/
    virtual ServerNetworkEventCoordinator& getServerNetworkEventCoordinator();

    /**@vIndex {172}*/
    virtual ScriptingEventCoordinator& getScriptingEventCoordinator();

    /**@vIndex {173}*/
    virtual ScriptDeferredEventCoordinator& getScriptDeferredEventCoordinator();

    /**@vIndex {174}*/
    virtual LevelEventCoordinator& getLevelEventCoordinator();

    /**@vIndex {175}*/
    virtual void handleLevelEvent(LevelEvent, const CompoundTag&);

    /**@vIndex {176}*/
    virtual void handleLevelEvent(LevelEvent, const Vec3&, int);

    /**@vIndex {177}*/
    virtual void handleStopSoundEvent(const std::string&);

    /**@vIndex {178}*/
    virtual void handleStopAllSounds();

    /**@vIndex {179}*/
    virtual void broadcastLevelEvent(LevelEvent, const CompoundTag&, const UserEntityIdentifierComponent*);

    /**@vIndex {180}*/
    virtual void broadcastLevelEvent(LevelEvent, const Vec3&, int, const UserEntityIdentifierComponent*);

    /**@vIndex {181}*/
    virtual void broadcastLocalEvent(BlockSource&, LevelEvent, const Vec3&, const Block&);

    /**@vIndex {182}*/
    virtual void broadcastLocalEvent(BlockSource&, LevelEvent, const Vec3&, int);

    /**@vIndex {183}*/
    virtual void broadcastSoundEvent(Dimension&, Puv::Legacy::LevelSoundEvent, const Vec3&, int, const ActorDefinitionIdentifier&, bool, bool);

    /**@vIndex {184}*/
    virtual void broadcastSoundEvent(BlockSource&, Puv::Legacy::LevelSoundEvent, const Vec3&, int, const ActorDefinitionIdentifier&, bool, bool);

    /**@vIndex {185}*/
    virtual void broadcastSoundEvent(BlockSource&, Puv::Legacy::LevelSoundEvent, const Vec3&, const Block&, const ActorDefinitionIdentifier&, bool, bool);

    /**@vIndex {186}*/
    virtual void broadcastActorEvent(Actor&, ActorEvent, int) const;

    /**@vIndex {187}*/
    virtual void addChunkViewTracker(std::weak_ptr<ChunkViewSource>);

    /**@vIndex {188}*/
    virtual void onChunkReload(const Bounds&);

    /**@vIndex {189}*/
    virtual void onChunkReloaded(ChunkSource&, LevelChunk&);

    /**@vIndex {190}*/
    virtual int getActivePlayerCount() const;

    /**@vIndex {191}*/
    virtual int getActiveUsersCount() const;

    /**@vIndex {192}*/
    virtual void forEachPlayer(std::function<bool(const Player&)>) const;

    /**@vIndex {193}*/
    virtual void forEachPlayer(std::function<bool(Player&)>);

    /**@vIndex {194}*/
    virtual void forEachUser(std::function<bool(const EntityContext&)>) const;

    /**@vIndex {195}*/
    virtual void forEachUser(std::function<bool(EntityContext&)>);

    /**@vIndex {196}*/
    virtual Player* findPlayer(std::function<bool(const WeakEntityRef&)>) const;

    /**@vIndex {197}*/
    virtual Player* findPlayer(std::function<bool(const Player&)>) const;

    /**@vIndex {198}*/
    virtual int getUserCount() const;

    /**@vIndex {199}*/
    virtual int countUsersWithMatchingNetworkId(const NetworkIdentifier&) const;

    /**@vIndex {200}*/
    virtual const std::vector<OwnerPtr<EntityContext>>& getUsers() const;

    /**@vIndex {201}*/
    virtual const std::vector<OwnerPtr<EntityContext>>& getEntities() const;

    /**@vIndex {202}*/
    virtual void _unknown_202();

    /**@vIndex {203}*/
    virtual void onChunkLoaded(ChunkSource&, LevelChunk&);

    /**@vIndex {204}*/
    virtual void onChunkDiscarded(LevelChunk&);

    /**@vIndex {205}*/
    virtual void _unknown_205();

    /**@vIndex {206}*/
    virtual void queueEntityDestruction(OwnerPtr<EntityContext>);

    /**@vIndex {207}*/
    virtual OwnerPtr<EntityContext> removeEntity(WeakEntityRef);

    /**@vIndex {208}*/
    virtual OwnerPtr<EntityContext> removeEntity(Actor&);

    /**@vIndex {209}*/
    virtual void forceRemoveEntity(Actor&);

    /**@vIndex {210}*/
    virtual void forceRemoveEntityfromWorld(Actor&);

    /**@vIndex {211}*/
    virtual void forceFlushRemovedPlayers();

    /**@vIndex {212}*/
    virtual void _unknown_212();

    /**@vIndex {213}*/
    virtual void levelCleanupQueueEntityRemoval(OwnerPtr<EntityContext>);

    /**@vIndex {214}*/
    virtual void registerTemporaryPointer(_TickPtr&);

    /**@vIndex {215}*/
    virtual void unregisterTemporaryPointer(_TickPtr&);

    /**@vIndex {216}*/
    virtual bool destroyBlock(BlockSource&, const BlockPos&, bool);

    /**@vIndex {217}*/
    virtual void upgradeStorageVersion(StorageVersion);

    /**@vIndex {218}*/
    virtual void suspendAndSave();

    /**@vIndex {219}*/
    virtual Particle* addParticle(ParticleType, const Vec3&, const Vec3&, int, const CompoundTag*, bool);

    /**@vIndex {220}*/
    virtual void _destroyEffect(const BlockPos&, const Block&, int);

    /**@vIndex {221}*/
    virtual void addParticleEffect(const HashedString&, const Vec3&, const MolangVariableMap&);

    /**@vIndex {222}*/
    virtual void addTerrainParticleEffect(const BlockPos&, const Block&, const Vec3&, float, float, float);

    /**@vIndex {223}*/
    virtual void addTerrainSlideEffect(const BlockPos&, const Block&, const Vec3&, float, float, float);

    /**@vIndex {224}*/
    virtual void addBreakingItemParticleEffect(const Vec3&, ParticleType, const ResolvedItemIconInfo&);

    /**@vIndex {225}*/
    virtual ActorUniqueID getNewUniqueID();

    /**@vIndex {226}*/
    virtual ActorRuntimeID getNextRuntimeID();

    /**@vIndex {227}*/
    virtual const std::vector<ChunkPos>& getTickingOffsets() const;

    /**@vIndex {228}*/
    virtual const std::vector<ChunkPos>& getClientTickingOffsets() const;

    /**@vIndex {229}*/
    virtual std::vector<ChunkPos> getSortedPositionsFromClientOffsets(const std::vector<ChunkPos>&) const;

    /**@vIndex {230}*/
    virtual bool isExporting() const;

    /**@vIndex {231}*/
    virtual void setIsExporting(bool);

    /**@vIndex {232}*/
    virtual SavedDataStorage& getSavedData();

    /**@vIndex {233}*/
    virtual void _unknown_233();

    /**@vIndex {234}*/
    virtual void _unknown_234();

    /**@vIndex {235}*/
    virtual MapItemSavedData* getMapSavedData(ActorUniqueID);

    /**@vIndex {236}*/
    virtual void requestMapInfo(ActorUniqueID, bool);

    /**@vIndex {237}*/
    virtual ActorUniqueID expandMapByID(ActorUniqueID, bool);

    /**@vIndex {238}*/
    virtual bool copyAndLockMap(ActorUniqueID, ActorUniqueID);

    /**@vIndex {239}*/
    virtual MapItemSavedData& createMapSavedData(const std::vector<ActorUniqueID>&, const BlockPos&, DimensionType, int);

    /**@vIndex {240}*/
    virtual MapItemSavedData& createMapSavedData(const ActorUniqueID&, const BlockPos&, DimensionType, int);

    /**@vIndex {241}*/
    virtual Core::PathBuffer<std::string> getScreenshotsFolder() const;

    /**@vIndex {242}*/
    virtual std::string getLevelId() const;

    /**@vIndex {243}*/
    virtual void setLevelId(std::string);

    /**@vIndex {244}*/
    virtual TaskGroup& getSyncTasksGroup();

    /**@vIndex {245}*/
    virtual TaskGroup& getIOTasksGroup();

    /**@vIndex {246}*/
    virtual void _unknown_246();

    /**@vIndex {247}*/
    virtual void _unknown_247();

    /**@vIndex {248}*/
    virtual void _unknown_248();

    /**@vIndex {249}*/
    virtual void _unknown_249();

    /**@vIndex {250}*/
    virtual void _unknown_250();

    /**@vIndex {251}*/
    virtual bool isEdu() const;

    /**@vIndex {252}*/
    virtual void _unknown_252();

    /**@vIndex {253}*/
    virtual void _unknown_253();

    /**@vIndex {254}*/
    virtual ActorInfoRegistry* getActorInfoRegistry();

    /**@vIndex {255}*/
    //virtual StackRefResult<const EntityRegistry> getEntityRegistry() const;
    virtual void _unknown_255();

    /**@vIndex {256}*/
    //virtual StackRefResult<EntityRegistry> getEntityRegistry();
    virtual void _unknown_256();

    /**@vIndex {257}*/
    virtual EntitySystems& getEntitySystems();

    /**@vIndex {258}*/
    virtual WeakRef<EntityContext> getLevelEntity();

    /**@vIndex {259}*/
    virtual void _unknown_259();

    /**@vIndex {260}*/
    virtual void _unknown_260();

    /**@vIndex {261}*/
    virtual const PlayerCapabilities::ISharedController& getCapabilities() const;

    /**@vIndex {262}*/
    //virtual TagRegistry<IDType<LevelTagIDType>, IDType<LevelTagSetIDType>>& getTagRegistry();
    virtual void _unknown_262();

    /**@vIndex {263}*/
    virtual const PlayerMovementSettings& getPlayerMovementSettings() const;

    /**@vIndex {264}*/
    virtual void setPlayerMovementSettings(const PlayerMovementSettings&);

    /**@vIndex {265}*/
    virtual bool canUseSkin(const SerializedSkin&, const NetworkIdentifier&, const mce::UUID&, const ActorUniqueID&) const;

    /**@vIndex {266}*/
    virtual PositionTrackingDB::PositionTrackingDBClient* getPositionTrackerDBClient() const;

    /**@vIndex {267}*/
    virtual void _unknown_267();

    /**@vIndex {268}*/
    virtual void flushRunTimeLighting();

    /**@vIndex {269}*/
    virtual void loadBlockDefinitionGroup(const Experiments&);

    /**@vIndex {270}*/
    virtual void initializeBlockDefinitionGroup();

    /**@vIndex {271}*/
    virtual Bedrock::NonOwnerPointer<IUnknownBlockTypeRegistry> getUnknownBlockTypeRegistry();

    /**@vIndex {272}*/
    virtual bool isClientSide() const;

    /**@vIndex {273}*/
    virtual void _unknown_273();

    /**@vIndex {274}*/
    virtual void _unknown_274();

    /**@vIndex {275}*/
    virtual const std::string& getPlayerXUID(const mce::UUID&) const;

    /**@vIndex {276}*/
    virtual const std::string& getPlayerPlatformOnlineId(const mce::UUID&) const;

    /**@vIndex {277}*/
    virtual const std::vector<WeakEntityRef>& getActiveUsers() const;

    /**@vIndex {278}*/
    virtual std::vector<Actor*> getRuntimeActorList() const;

    /**@vIndex {279}*/
    virtual void _unknown_279();

    /**@vIndex {280}*/
    virtual void _unknown_280();

    /**@vIndex {281}*/
    virtual PacketSender* getPacketSender() const;

    /**@vIndex {282}*/
    virtual void setPacketSender(PacketSender*);

    /**@vIndex {283}*/
    virtual Bedrock::NonOwnerPointer<NetEventCallback> getNetEventCallback() const;

    /**@vIndex {284}*/
    virtual void setNetEventCallback(Bedrock::NonOwnerPointer<NetEventCallback>);

    /**@vIndex {285}*/
    virtual void _unknown_285();

    /**@vIndex {286}*/
    virtual void _unknown_286();

    /**@vIndex {287}*/
    virtual void _unknown_287();

    /**@vIndex {288}*/
    virtual HitResult& getHitResult();

    /**@vIndex {289}*/
    virtual HitResult& getLiquidHitResult();

    /**@vIndex {290}*/
    virtual const std::string& getImmersiveReaderString() const;

    /**@vIndex {291}*/
    virtual void setImmersiveReaderString(std::string);

    /**@vIndex {292}*/
    virtual const AdventureSettings& getAdventureSettings() const;

    /**@vIndex {293}*/
    virtual AdventureSettings& getAdventureSettings();

    /**@vIndex {294}*/
    virtual GameRules& getGameRules();

    /**@vIndex {295}*/
    virtual const GameRules& getGameRules() const;

    /**@vIndex {296}*/
    virtual bool hasStartWithMapEnabled() const;

    /**@vIndex {297}*/
    virtual bool isEditorWorld() const;

    /**@vIndex {298}*/
    virtual Abilities& getDefaultAbilities();

    /**@vIndex {299}*/
    virtual const PermissionsHandler& getDefaultPermissions() const;

    /**@vIndex {300}*/
    virtual PermissionsHandler& getDefaultPermissions();

    /**@vIndex {301}*/
    virtual bool getTearingDown() const;

    /**@vIndex {302}*/
    virtual void takePicture(cg::ImageBuffer&, Actor*, Actor*, ScreenshotOptions&);

    /**@vIndex {303}*/
    virtual gsl::not_null<Bedrock::NonOwnerPointer<LevelSoundManager>> getLevelSoundManager();

    /**@vIndex {304}*/
    virtual gsl::not_null<Bedrock::NonOwnerPointer<SoundPlayerInterface>> getSoundPlayer() const;

    /**@vIndex {305}*/
    virtual void setSimPaused(bool);

    /**@vIndex {306}*/
    virtual bool getSimPaused();

    /**@vIndex {307}*/
    virtual void setFinishedInitializing();

    /**@vIndex {308}*/
    virtual LootTables& getLootTables();

    /**@vIndex {309}*/
    virtual void updateWeather(float, int, float, int);

    /**@vIndex {310}*/
    virtual int getNetherScale() const;

    /**@vIndex {311}*/
    virtual void _unknown_311();

    /**@vIndex {312}*/
    virtual void _unknown_312();

    /**@vIndex {313}*/
    virtual void _unknown_313();

    /**@vIndex {314}*/
    virtual LayeredAbilities* getPlayerAbilities(const ActorUniqueID&);

    /**@vIndex {315}*/
    virtual void setPlayerAbilities(const ActorUniqueID&, const LayeredAbilities&);

    /**@vIndex {316}*/
    virtual void sendAllPlayerAbilities(const Player&);

    /**@vIndex {317}*/
    virtual Recipes& getRecipes() const;

    /**@vIndex {318}*/
    virtual BlockReducer* getBlockReducer() const;

    /**@vIndex {319}*/
    virtual void _unknown_319();

    /**@vIndex {320}*/
    virtual void _unknown_320();

    /**@vIndex {321}*/
    virtual void _unknown_321();

    /**@vIndex {322}*/
    virtual void _unknown_322();

    /**@vIndex {323}*/
    virtual void digestServerItemComponents(const ItemComponentPacket&);

    /**@vIndex {324}*/
    virtual const BlockLegacy& getRegisteredBorderBlock() const;

    /**@vIndex {325}*/
    virtual bool use3DBiomeMaps() const;

    /**@vIndex {326}*/
    virtual void addBlockSourceForValidityTracking(BlockSource*);

    /**@vIndex {327}*/
    virtual void removeBlockSourceFromValidityTracking(BlockSource*);

    /**@vIndex {328}*/
    virtual Level* asLevel();

    /**@vIndex {329}*/
    virtual void _unknown_329();

    /**@vIndex {330}*/
    virtual bool isClientSideGenerationEnabled();

    /**@vIndex {331}*/
    virtual bool blockNetworkIdsAreHashes();

    /**@vIndex {332}*/
    virtual ItemRegistryRef getItemRegistry() const;

    /**@vIndex {333}*/
    virtual std::weak_ptr<BlockTypeRegistry> getBlockRegistry() const;

    /**@vIndex {334}*/
    virtual void pauseAndFlushTaskGroups();

    /**@vIndex {335}*/
    virtual void _unknown_335();

    /**@vIndex {336}*/
    virtual void _unknown_336();

    /**@vIndex {337}*/
    virtual void _unknown_337();

    /**@vIndex {338}*/
    virtual void _unknown_338();

    /**@vIndex {339}*/
    virtual void _unknown_339();

protected:
    /**@vIndex {340}*/
    virtual void _subTick();

    /**@vIndex {341}*/
    virtual void _initializeMapDataManager();
};
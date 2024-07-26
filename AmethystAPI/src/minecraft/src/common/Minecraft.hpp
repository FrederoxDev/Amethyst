#pragma once
#include <string>
#include <gsl/pointers>
#include <chrono>
#include <minecraft/src-deps/core/utility/pubsub/Publisher.hpp>
#include <minecraft/src-deps/core/utility/pubsub/ThreadModel.hpp>
#include <minecraft/src/common/gamerefs/gamerefs_entity/IEntityRegistryOwner.hpp>
#include <minecraft/src/common/world/GameSession.hpp>

class GameCallbacks;
class IMinecraftEventing;
class ResourcePackManager;
class StructureManager;
class GameModuleServer;
class AllowList;
class PermissionsFile;
class PrivateKeyManager;
namespace Core { class FilePathManager; };
class ServerMetrics;
class MinecraftCommands;
class GameTestLevelListener;
class MinecraftGameTest;
class Timer;
class PacketSender;
class IMinecraftApp;
class Level;

class Minecraft : IEntityRegistryOwner {
public:
    /* this + 24  */ GameCallbacks& mGameCallbacks;
    /* this + 32  */ IMinecraftEventing& mEventing;
    /* this + 40  */ std::unique_ptr<ResourcePackManager> mResourceLoader;
    /* this + 48  */ std::unique_ptr<StructureManager> mStructureManager;
    /* this + 56  */ std::shared_ptr<GameModuleServer> mGameModuleServer;
    /* this + 72  */ AllowList* mAllowList;
    /* this + 80  */ PermissionsFile* mPermissionsFile;
    /* this + 88  */ std::unique_ptr<PrivateKeyManager> mServerKeys;
    /* this + 96  */ const std::string mSaveGamePath;
    /* this + 128 */ gsl::not_null<Bedrock::NonOwnerPointer<Core::FilePathManager>> mFilePathManager;
    /* this + 144 */ ServerMetrics* mServerMetrics;
    /* this + 152 */ bool mCorruptionDetected;
    /* this + 153 */ bool mFireOnLevelCorrupt;
    /* this + 160 */ long double mFrameDuration;
    /* this + 168 */ long double mLastFrameStart;
    /* this + 176 */ std::chrono::seconds mMaxPlayerIdleTime;
    /* this + 184 */ std::unique_ptr<MinecraftCommands> mCommands;
    /* this + 192 */ std::unique_ptr<GameSession> mGameSession;
    /* this + 200 */ std::unique_ptr<GameTestLevelListener> mGameTestLevelListener;
    /* this + 208 */ std::unique_ptr<MinecraftGameTest> mGameTest;
    /* this + 216 */ Timer* mSimTimer;
    /* this + 224 */ Timer* mRealTimer;
    /* this + 232 */ ClientOrServerNetworkSystemRef mNetwork;
    /* this + 248 */ PacketSender* mPacketSender;
    /* this + 256 */ IMinecraftApp* mApp;
    /* this + 264 */ SubClientId mClientSubId;
    /* this + 272 */ OwnerPtr<EntityRegistry> mEntityRegistry;
    /* this + 288 */ std::unique_ptr<Bedrock::PubSub::Publisher<void(Level*), Bedrock::PubSub::ThreadModel::SingleThreaded>> mLevelSubscribers;

public:
    virtual ~Minecraft();
    virtual StackRefResult<const EntityRegistry> getEntityRegistry() const override;
    virtual StackRefResult<EntityRegistry> getEntityRegistry() override;
    virtual void setSimTimePuase(bool pause);
    virtual void setSimTimeScale(float scale);
    virtual bool getSimPaused() const;
    virtual bool isOnlineClient() const;

    Level* getLevel() const;

    bool update(Minecraft*);
};
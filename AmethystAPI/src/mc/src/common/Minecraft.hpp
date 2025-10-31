/// @symbolgeneration
#pragma once
#include <string>
#include <gsl/pointers>
#include <chrono>
#include <mc/src-deps/core/utility/pubsub/Publisher.hpp>
#include <mc/src-deps/core/utility/pubsub/ThreadModel.hpp>
#include <mc/src-deps/ecs/gamerefs_entity/IEntityRegistryOwner.hpp>
#include <mc/src/common/world/GameSession.hpp>
#include <amethyst/Imports.hpp>

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
    /* this + 72  */ AllowList& mAllowList;
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
    /* this + 216 */ Timer& mSimTimer;
    /* this + 224 */ Timer& mRealTimer;
    /* this + 232 */ ClientOrServerNetworkSystemRef mNetwork;
    /* this + 248 */ PacketSender& mPacketSender;
    /* this + 256 */ IMinecraftApp& mApp;
    /* this + 264 */ SubClientId mClientSubId;
    /* this + 272 */ OwnerPtr<EntityRegistry> mEntityRegistry;
    /* this + 288 */ std::unique_ptr<Bedrock::PubSub::Publisher<void(Level*), Bedrock::PubSub::ThreadModel::SingleThreaded>> mLevelSubscribers;

public:
    virtual ~Minecraft();
    virtual StackRefResult<const EntityRegistry> getEntityRegistry() const override;
    virtual StackRefResult<EntityRegistry> getEntityRegistry() override;
    virtual void setSimTimePause(bool pause);
    virtual void setSimTimeScale(float scale);
    virtual bool getSimPaused() const;
    virtual bool isOnlineClient() const;

	/// @signature {48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 4C 89 4C 24, win-server}
    /// @signature {48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 4D 8B E1 49 8B D8 4C 8B EA}
    MC Minecraft* _Minecraft(Minecraft* a1, void* a2, void* a3, void* a4, void* a5, void* a6, void* a7, void* a8, void* a9, void* a10, char a11, void* a12, void* a13, void* a14, void* a15);

	/// @signature {48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8B D9 48 8D 05 ? ? ? ? 48 89 01 48 8B 89, win-server}
    /// @signature {48 89 5C 24 ? 57 48 83 EC ? 8B DA 48 8B F9 E8 ? ? ? ? F6 C3 ? 74 ? BA ? ? ? ? 48 8B CF E8 ? ? ? ? 48 8B 5C 24 ? 48 8B C7 48 83 C4 ? 5F C3 CC CC CC CC CC CC CC CC CC CC CC CC 48 89 5C 24 ? 57 48 83 EC ? 48 8B D9 48 8D 05 ? ? ? ? 48 89 01 E8 ? ? ? ? 48 8B 8B}
    MC void $dtor();

    Level* getLevel() const;

	/// @signature {48 8B C4 48 89 58 ? 48 89 70 ? 48 89 78 ? 55 41 54 41 55 41 56 41 57 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 0F 29 70 ? 0F 29 78 ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4C 8B E9 48 89 8D, win-server}
    /// @signature {48 8B C4 48 89 58 ? 48 89 70 ? 48 89 78 ? 55 41 54 41 55 41 56 41 57 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 0F 29 70 ? 0F 29 78 ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4C 8B E9 48 89 4C 24}
    MC bool update();
};
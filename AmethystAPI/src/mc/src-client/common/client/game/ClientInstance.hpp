/// @symbolgeneration
#pragma once
#include <cstdint>
#include <functional>
#include <string>
#include <memory>
#include <atomic>
#include <chrono>
#include "mc/src-deps/renderer/Camera.hpp"
#include "mc/src-client/common/client/renderer/TexturePtr.hpp"
#include "mc/src-deps/renderer/ViewportInfo.hpp"
#include "mc/src-deps/ecs/WeakEntityRef.hpp"
#include <amethyst/Imports.hpp>
#include "mc/src/common/world/phys/Vec3.hpp"
#include "mc/src/common/world/phys/Vec2.hpp"
#include "mc/src-deps/core/math/Color.hpp"
#include <mc/src/common/CommonTypes.hpp>
#include <mc/src-deps/core/threading/Mutex.hpp>
#include <mc/src-deps/core/utility/pubsub/Subscription.hpp>
#include <mc/src-client/common/client/social/GameConnectionInfo.hpp>
#include <mc/src-deps/core/utility/NonOwnerPointer.hpp>
#include <mc/src-client/common/client/game/IClientInstance.hpp>

class Minecraft;
class ClientInputHandler;
class ItemRenderer;
class BlockTessellator;
class FileDataRequest;
namespace Core { class Path; }
namespace Bedrock::Http { class Status; }
class MinecraftGame;
class GuiData;
class LocalPlayer;
class BlockSource;
class ToastManager; 

//is_virtual = True
//    hide_vtable = False
//        struct_size = 3232
//
//#(Type, Name, Size(in bytes), Offset(in bytes))
//    struct
//    = [("MinecraftGame*", "minecraftGame", 8, 200),
//       ("Minecraft*", "minecraft", 8, 208),
//       ("ClientInputHandler*", "inputHandler", 8, 272),
//       ("ItemRenderer*", "itemRenderer", 8, 1360),
//       ("GuiData*", "guiData", 8, 1368),
//       ("mce::Camera", "camera", 512, 624),
//       ("BlockTessellator*", "mBlockTessellator", 8, 1320)]

class LevelRenderer;
class LightTexture;
class LoopbackPacketSender;
class HolographicPlatform;
class VoiceSystem;
class ClientMoveInputHandler;
class MinecraftKeyboardManager;
class HitDetectSystem;
class UserAuthentication;
class SceneFactory;
class CachedScenes;
class BuildActionIntention;

struct ShaderColor {
    mce::Color mColor;
    bool mDirty;
};

enum class WYSIWYGState : int32_t {
    NoControlSelected = 0x0,
    ControlSelected = 0x1,
    ModifyingOpacity = 0x2,
    ModifyingScale = 0x3,
    ResetConfirmation = 0x4,
    CloseWithoutSavingConfirmation = 0x5,
    Exiting = 0x6,
};

struct WYSIWIGData
{
    std::set<unsigned int> mActiveControlOptions;
    bool mOtherConfigsExistInThisCategory;
    int mNumberOfActiveConfigs;
    int mNumberOfEnabledConfigs;
    WYSIWYGState mWYSIWYGState;
};

enum class PlayScreenDefaultTab : int32_t {
    World = 0x0000,
    Friends = 0x0001,
    Servers = 0x0002,
    Count = 0x0003,
};


enum class ClientPlayMode : int32_t {
    Normal = 0x0000,
    Teaser = 0x0001,
    Screen = 0x0002,
    Viewer = 0x0003,
    Reality = 0x0004,
    Placement = 0x0005,
    LivingRoom = 0x0006,
    ExitLevel = 0x0007,
    ExitLevelLivingRoom = 0x0008,
    NumModes = 0x0009,
};

class Actor;
class BlockActorRenderDispatcher;
class ActorRenderDispatcher;
class ActorBlockRenderer;
class ItemInHandRenderer;
class SceneStack;
namespace OreUI { class Router; }
namespace mce { class Texture; }
class ContentCatalogService;
class TextToSpeechClient;
class TTSEventManager;
class TaskGroup;
class GuidedFlowManager;
class MobEffectsLayout;
class SkinRepositoryClientInterface;
class ClientHMDState;
class FogDefinitionRegistry;
class FogManager;
class ScreenLoadTimeTracker;
class PlayerReportHandler;
class IGameConnectionListener;
class UIEventCoordinator;
class ClientHitDetectCoordinator;
class ClientNetworkEventCoordinator;
class HitDetectEventListener;
class ClientScriptEventCoordinator;
class EducationOptions;
namespace Core {
class FileStorageArea;
class FilePathManager;
}
class LatencyGraphDisplay;
class GameModuleClient;
class ClientInstanceEventCoordinator;
class ClientScriptManager;
namespace PlayerCapabilities {
class IClientController;
};
namespace ui { class ScreenTechStackSelector; }
class ClientRequirementVerifier;
class BlockTypeRegistry;
class DisconnectionRequestHandler;
namespace Editor { class IEditorManager; } 
class DebugInfoPacketHandler;

class HoloHudDriftDynamics {
	Matrix mMatrixPatch;
	Vec3 mHudDirPoseSpace;
	Vec3 mHudDirAVelPoseSpace;
	Vec3 mLastHudTargetDir;
	Vec3 mLastGazeToPoseDelta;
	long double mLastHudDirUpdateTime;
	bool mResetLastTargetDir;
	IClientInstance *mClient;
};

namespace mce { class RenderStage; }

enum class HoloUIToPoseSource : int32_t
{
    NonVR = 0x0,
    MainMenu = 0x1,
    LivingRoom = 0x2,
    VRTransition = 0x3,
    VRHeadlocked = 0x4,
    VRFloatingHUD = 0x5,
    VRHandheldHUD = 0x6,
};

class ClientHMDState {
public:
    class VRRotationResetState {
        bool mPendingReset;
        bool mForceNextReset;
    };

    IClientInstance *mClientInstance;
    HoloHudDriftDynamics mHoloHudDriftDynamics;
    struct mce::RenderStage* mUIStage;
    struct mce::RenderStage* mLevelStage;
    struct mce::Texture* mLevelTexture;
    struct mce::Texture* mUITexture;
    std::shared_ptr<mce::Texture> mUILayersTexture;
    float mHoloScreenCursorXCoordNorm;
    float mHoloScreenCursorYCoordNorm;
    Matrix mLastLevelViewMatrix;
    Matrix mLastLevelViewMatrixAbsolute;
    Matrix mLastLevelProjMatrix;
    Matrix mLastLevelWorldMatrix;
    Matrix mHUDMatrixPatch;
    Matrix mVRTransitionMatrixPatch;
    float mLastLevelViewMatrixVerticalShift;
    float mLastVRPitchAngle;
    float mVRRotationAdjustment;
    float mVRRotAdjYawTweak;
    float mGazeCursorPitchBoostAngle;
    float mFadeScreenAlpha;
    float mDesiredFadeScreenAlpha;
    float mRealityFrameModeWorldScale;
    float mHeadSetDirForSleeping;
    short mPointerX;
    short mPointerY;
    bool mHoloCursorOn;
    bool mAppJustResumed;
    ClientHMDState::VRRotationResetState mVRRotationResetState;
    bool mHoloTransformsHaveBeenUpdated;
    HoloUIToPoseSource mLastHoloUIToPoseSource;
};

namespace persona { class PersonaPieceCollectionModel; }
namespace PlayerCapabilities { class IClientController; }
namespace OreUI { class SceneProvider; class Telemetry { std::byte padding0[24]; }; }
namespace Social {
	class GameConnectionInfo; 
	class User; 
	class IUserManager;
	enum class MultiplayerServiceIdentifier;
}
class NetworkSessionOwner;
class IMinecraftApp;
class LevelListener;
class IAdvancedGraphicsOptions;
class NetworkSystem;
class Timer;
class IGameModuleApp;
using IMinecraftGame = MinecraftGame;

enum class ClientInstanceState : int32_t {
    Idle = 0x0000,
    WaitingForPlayer = 0x0001,
    WaitingToPlay = 0x0002,
    Playing = 0x0003,
};

// thx for the struct levilamina
// levilamina op

/** @vptr {48 8D 05 ? ? ? ? 48 89 06 48 8D 05 ? ? ? ? 48 89 46 ? 48 8D 05 ? ? ? ? 48 89 86} */
class ClientInstance {
public:
    class ClientRenderResources {
    public:
        void* mUITexture; // mce::Texture* mUITexture;
        mce::TexturePtr mUICursorTexture;
    };

    class PlayerJoinWorldTelemetryInfo {
    public:
        int joinAttemptId;
        int networkTypeOverride;
        std::string multiplayerCorrelationId;
    };

	MC static uintptr_t $vtable_for_this;
    /* this + 8    */ std::byte padding8[160 - 8]; // member variable of bases, not mapped out yet
    /* this + 160  */ ClientInstanceState mClientState;
    /* this + 168  */ IMinecraftApp* mApp;
    /* this + 176  */ LevelListener* mLevelListener;
    /* this + 184  */ gsl::not_null<Bedrock::NonOwnerPointer<IAdvancedGraphicsOptions>> mAdvancedGraphicsOptions;
    /* this + 200  */ MinecraftGame* mMinecraftGame;
    /* this + 208  */ Minecraft* mMinecraft;
    /* this + 216  */ bool mIsFullVanillaPackOnStack;
    /* this + 224  */ std::unique_ptr<LevelRenderer> mLevelRenderer;
    /* this + 232  */ std::unique_ptr<LightTexture> mLightTexture;
    /* this + 240  */ std::unique_ptr<LoopbackPacketSender> mPacketSender;
    /* this + 248  */ std::unique_ptr<HolographicPlatform> mHoloInput;
    /* this + 256  */ std::unique_ptr<VoiceSystem> mVoiceSystem;
    /* this + 264  */ std::unique_ptr<ClientMoveInputHandler> mClientMoveInputHandler;
    /* this + 272  */ std::unique_ptr<ClientInputHandler> mClientInputHandler;
    /* this + 280  */ std::unique_ptr<MinecraftKeyboardManager> mKeyboardManager;
    /* this + 288  */ std::unique_ptr<HitDetectSystem> mHitDetectSystem;
    /* this + 296  */ std::shared_ptr<UserAuthentication> mUserAuthentication;
    /* this + 312  */ std::unique_ptr<SceneFactory> mSceneFactory; 
    /* this + 320  */ std::unique_ptr<CachedScenes> mCachedScenes;
    /* this + 328  */ WeakEntityRef mCameraRef;
    /* this + 352  */ WeakEntityRef mCameraTargetRef; 
    /* this + 376  */ WeakEntityRef mLocalUser;
    /* this + 400  */ std::unique_ptr<BuildActionIntention> mInProgressBai;
    /* this + 408  */ float mHoloviewerScale;
    /* this + 412  */ float mRealityModeFrameFactor;
    /* this + 416  */ bool mRealityModeToggleTriggered;
    /* this + 420  */ ClientPlayMode mPlayMode;
    /* this + 424  */ bool mTickedLastFrame;
    /* this + 425  */ std::atomic<bool> mOpenControllerDisconnectScreen;
    /* this + 426  */ std::atomic<bool> mHandlingControllerDisconnect;
    /* this + 427  */ std::atomic<bool> mConnectGamepadScreenActive;
    /* this + 428  */ PlayScreenDefaultTab mDefaultPlayscreenTab;
    /* this + 432  */ bool mInGameInputEnabled;
    /* this + 433  */ bool mIsInUpdate;
    /* this + 434  */ bool mLivingRoomCredits;
    /* this + 440  */ std::function<void()> mCreditsCallback;
    /* this + 504  */ std::chrono::steady_clock::time_point mNoBlockBreakUntil;
    /* this + 512  */ bool mNewDictationString;
    /* this + 520  */ std::string mDictation;
    /* this + 552  */ ViewportInfo mViewportInfo;
    /* this + 576  */ ClientInstance::ClientRenderResources mClientRenderResources;
    /* this + 616  */ mce::Texture* mLevelTexture;
    /* this + 624  */ mce::Camera camera;
    /* this + 1136 */ ShaderColor mShaderColor;
    /* this + 1152 */ ShaderColor mDarkShaderColor;
    /* this + 1176 */ Vec3 mLastPointerLocation;
    /* this + 1192 */ WYSIWIGData mWYSIWYGData;
    /* this + 1224 */ std::map<int, Vec2> mTouchPointerLocations;
    /* this + 1240 */ int mActionPointerId;
    /* this + 1248 */ std::unique_ptr<SceneStack> mSceneStack;
    /* this + 1256 */ std::unique_ptr<OreUI::Router> mUIRouter;
    /* this + 1272 */ std::unique_ptr<ContentCatalogService> mServerService;
    /* this + 1280 */ std::shared_ptr<TextToSpeechClient> mTextToSpeechClient;
    /* this + 1296 */ std::shared_ptr<TTSEventManager> mTTSEventManager;
    /* this + 1304 */ std::unique_ptr<TaskGroup> mTaskGroup;
    /* this + 1312 */ std::unique_ptr<BlockTessellator> mBlockTessellator;
    /* this + 1320 */ std::unique_ptr<BlockActorRenderDispatcher> mBlockEntityRenderDispatcher;
    /* this + 1328 */ std::shared_ptr<ActorRenderDispatcher> mActorRenderDispatcher;
    /* this + 1344 */ std::unique_ptr<ActorBlockRenderer> mEntityBlockRenderer;
    /* this + 1352 */ std::unique_ptr<ItemInHandRenderer> mItemInHandRenderer;
    /* this + 1360 */ std::unique_ptr<ItemRenderer> mItemRenderer;
    /* this + 1368 */ std::unique_ptr<GuiData> mGuiData;
    /* this + 1376 */ std::unique_ptr<GuidedFlowManager> mGuidedFlowManager;
    /* this + 1388 */ std::unique_ptr<MobEffectsLayout> mMobEffectsLayout;
    /* this + 1392 */ std::shared_ptr<ToastManager> mToastManager;

    // anything below here not really tested extensively
    const SubClientId mClientSubId;
    void* mClipboardManager; // std::unique_ptr<ClipboardProxy<ApplicationSignal::ClipboardCopy, ApplicationSignal::ClipboardPasteRequest>>
    std::unique_ptr<SkinRepositoryClientInterface> mSkinRepositoryClientInterface;
    std::shared_ptr<persona::PersonaPieceCollectionModel> mPersonaPieceCollectionModel;
    ClientHMDState mHMDState;
    std::unique_ptr<FogDefinitionRegistry> mFogDefinitionRegistry;
    std::unique_ptr<FogManager> mFogManager;
    bool mIsSceneStackChanging;
    std::unique_ptr<ScreenLoadTimeTracker> mScreenLoadTimeTracker;
    float mRemoteServerTime;
    float mRemoteNetworkTime;
    std::shared_ptr<PlayerReportHandler> mPlayerReportHandler;
    bool mHasSwitchedScreen;
    bool mShouldLeaveGame;
    bool mPreparingToLeaveGame;
    bool mIsLeavingGame;
    bool mSyncLeaveGame;
    bool mDestroyingGame;
    bool mShuttingDown;
    std::optional<Social::GameConnectionInfo> mReconnectionInfo;
    bool mSuspendingCausedDisconnect;
    bool mUsingTripodNow;
    bool mDisconnectionRequestInProgress;
    std::atomic<int> mCriticalDiskTelemetrySentCount;
    std::atomic<bool> mUnrecoverableErrorTelemetrySent;
    std::chrono::steady_clock::time_point mServerConnectionTime;
    int mServerPingTime;
    std::deque<std::string> mSentMessageHistory;
    std::deque<std::string> mDevConsoleMessageHistory;
    std::shared_ptr<IGameConnectionListener> mGameConnectionListener;
    std::function<void (std::string const&, enum BehaviorStatus)> mBehaviorCommandStatusCallback;
    std::unique_ptr<UIEventCoordinator> mUIEventCoordinator;
    std::unique_ptr<ClientHitDetectCoordinator> mHitEventCoordinator;
    std::unique_ptr<ClientNetworkEventCoordinator> mClientNetworkEventCoordinator;
    std::unique_ptr<HitDetectEventListener> mHitDetectEventListener;
    std::unique_ptr<ClientScriptEventCoordinator> mClientScriptEventCoordinator;
    std::unique_ptr<EducationOptions> mEducationOptions;
    std::weak_ptr<Core::FileStorageArea> mStorageArea;
    glm::vec2 mPrevCursorPos;
    glm::vec2 mCurrentCursorPos;
    float mCursorPosAlpha;
    struct LatencyGraphDisplay* mLatencyGraphDisplay;
    std::unique_ptr<GameModuleClient> mGameModule;
    gsl::not_null<Bedrock::NonOwnerPointer<ClientInstanceEventCoordinator>> mEventCoordinator;
    std::unique_ptr<ClientScriptManager> mClientScriptManager;
    Bedrock::PubSub::Subscription mEnableClientScriptOptionObserver;
    std::unique_ptr<PlayerCapabilities::IClientController> mClientCapabilities;
    std::unique_ptr<OreUI::SceneProvider> mSceneProvider;
    std::unique_ptr<ui::ScreenTechStackSelector> mScreenTechStackSelector;
    OreUI::Telemetry mOreUITelemetry;
    std::shared_ptr<ClientRequirementVerifier> mClientRequirementVerifier;
    std::shared_ptr<BlockTypeRegistry> mBlockRegistry;
    std::unique_ptr<DisconnectionRequestHandler> mDisconnectionRequestHandler;
    std::unique_ptr<Editor::IEditorManager> mEditorManager;
    std::unique_ptr<DebugInfoPacketHandler> mDebugInfoPacketHandler;
    std::optional<ClientInstance::PlayerJoinWorldTelemetryInfo> mPlayerJoinWorldInfo;
    std::chrono::steady_clock::time_point mControlTipsTimeElapsedStart;
    gsl::not_null<Bedrock::NonOwnerPointer<NetworkSessionOwner>> mNetworkSessionOwner;
    bool mIsClientThrottleEnabled;
    int mClientThrottleRenderDistanceThreshold;
    float mClientThrottleRenderDistanceScalar;
    Bedrock::PubSub::Subscription mPerspectiveOptionChangeSubscription;
    Bedrock::Threading::Mutex mUserLock;
    std::shared_ptr<Social::User> mUser;

public:
	/** @sig {48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 49 8B F9 49 8B D8 4C 8B E2} */
    ClientInstance(
		IMinecraftGame& mg,
		IMinecraftApp& app,
		LevelListener& levelListener,
		SubClientId subid,
		const Bedrock::NotNullNonOwnerPtr<IAdvancedGraphicsOptions>& graphicsOptions,
		const Bedrock::NotNullNonOwnerPtr<ClientInstanceEventCoordinator>& coordinator,
		LatencyGraphDisplay* latencyGraphDisplay,
		const Bedrock::NotNullNonOwnerPtr<NetworkSessionOwner>& sessionOwner
	);
    
	/** @vidx {0} */ virtual ~ClientInstance();
	/** @vidx {1} */ virtual void unknown_1();
	/** @vidx {2} */ virtual void unknown_2();
	/** @vidx {3} */ 
	virtual void init(
		const Bedrock::NotNullNonOwnerPtr<Core::FilePathManager>& filePathManager,
		NetworkSystem& network,
		Timer& simTimer,
		Timer& realTimer,
		const Bedrock::NotNullNonOwnerPtr<Social::IUserManager>& userManager,
		uint32_t id,
		IGameModuleApp& gameModuleApp
	);


    /** @sig {48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 49 8B F9 49 8B D8 4C 8B E2} */
    MC static ClientInstance* $constructor(
		ClientInstance* self, 
		IMinecraftGame& mg, 
		IMinecraftApp& app, 
		LevelListener& levelListener, 
		SubClientId subid, 
		const Bedrock::NotNullNonOwnerPtr<IAdvancedGraphicsOptions>& graphicsOptions, 
		const Bedrock::NotNullNonOwnerPtr<ClientInstanceEventCoordinator>& coordinator,
		LatencyGraphDisplay* latencyGraphDisplay, 
		const Bedrock::NotNullNonOwnerPtr<NetworkSessionOwner>& sessionOwner
	);

    /** @signature {40 55 53 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 45 8B F1} */
    MC void* onStartJoinGame(bool unk0, const std::string& unk1, int unk2, Social::MultiplayerServiceIdentifier serviceId);

    /** @signature {48 89 5C 24 ? 48 89 74 24 ? 55 57 41 54 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 45 0F B6 F0 44 0F B6 FA} */
    MC void requestLeaveGame(bool switchScreen, bool sync);

    BlockSource* getRegion();
    LocalPlayer* getLocalPlayer();
    void grabMouse();
    void releaseMouse();
    bool isShowingLoadingScreen() const;
    void getRawCameraEntities(WeakEntityRef& outCamera, WeakEntityRef& outCameraTarget) const;

    // 1.21.0.3 - ? - 4C 8B DC 49 89 5B ? 4D 89 4B ? 49 89 53 ? 55 56 57 48 83 EC
    std::shared_ptr<FileDataRequest> getImageFromUrl(const std::string& imageUrl, std::function<void(Bedrock::Http::Status, const Core::Path&, uint64_t)> callback);
    EntityId getCameraEntity() const;
    Actor* getCameraActor() const;
};

static_assert(offsetof(ClientInstance, mClientState) == 160);
static_assert(offsetof(ClientInstance, mLevelRenderer) == 224);
static_assert(offsetof(ClientInstance, mViewportInfo) == 552);
static_assert(offsetof(ClientInstance, mGuiData) == 1368);
//static_assert(sizeof(ClientInstance) == 3232); // idk when this was from, could still be right? its not far off but i cant see what im missing.

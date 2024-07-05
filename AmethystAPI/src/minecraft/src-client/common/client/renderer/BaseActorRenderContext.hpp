#pragma once
#include <minecraft/src/common/world/phys/Vec3.hpp>
#include <minecraft/src/common/world/phys/AABB.hpp>

class ScreenContext;
class ClientInstance;
using IClientInstance = ClientInstance;

class MinecraftGame;
using IMinecraftGame = MinecraftGame;

class ItemRenderer;
struct SortedMeshDrawList;
class BlockActorRenderDispatcher;
class ActorRenderDispatcher;
class ItemInHandRenderer;
struct ActorBlockRenderer;
struct ParticleSystemEngine;

class BaseActorRenderContext {
public:
    /* this + 0   */ uintptr_t** vtable;
    /* this + 8   */ float mNumEntitiesRenderedThisFrame;
    /* this + 12  */ float mLastFrameTime;
    /* this + 16  */ SortedMeshDrawList* mSortedMeshDrawList;
    /* this + 24  */ ClientInstance* mClientInstance;
    /* this + 32  */ MinecraftGame* mMinecraftGame;
    /* this + 40  */ ScreenContext* mScreenContext;
    /* this + 48  */ BlockActorRenderDispatcher* mBlockEntityRenderDispatcher;
    /* this + 56  */ std::shared_ptr<ActorRenderDispatcher> mEntityRenderDispatcher;
    /* this + 72  */ ActorBlockRenderer* mEntityBlockRenderer;
    /* this + 80  */ ItemInHandRenderer* mItemInHandRenderer;
    /* this + 88  */ ItemRenderer* itemRenderer;
    /* this + 96  */ ParticleSystemEngine* mParticleEngineSystem;
    /* this + 104 */ std::optional<uint64_t> mRenderUniqueIdOverride;
    /* this + 120 */ Vec3 mCameraTargetPosition;
    /* this + 132 */ Vec3 mCameraPosition;
    /* this + 144 */ AABB mWorldClipRegion;
    /* this + 168 */ /*const*/ float mFrameAlpha;
    /* this + 172 */ bool mIsOnScreen;
    /* this + 173 */ bool mUpdateBonesAndEffects;
    /* this + 174 */ bool mUpdateEffects;
    /* this + 175 */ bool mIgnoresLighting;
    /* this + 176 */ bool mForceLightingOn;
    /* this + 177 */ std::byte mHistoricalFrameTimes[0x1E7];

public:
    BaseActorRenderContext(ScreenContext* screenContext, IClientInstance* clientInstance, IMinecraftGame* minecraftGame);
};

static_assert(sizeof(BaseActorRenderContext) == 0x298);
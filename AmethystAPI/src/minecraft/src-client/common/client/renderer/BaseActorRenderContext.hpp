#pragma once
#include "amethyst/Memory.hpp"

class ScreenContext;
class ClientInstance;
using IClientInstance = ClientInstance;

class MinecraftGame;
using IMinecraftGame = MinecraftGame;

class ItemRenderer;
struct SortedMeshDrawList;
struct BlockActorRenderDispatcher;
class ActorRenderDispatcher;
class ItemInHandRenderer;
struct ActorBlockRenderer;

class BaseActorRenderContext {
public:
    /* this + 0  */ uintptr_t** vtable;
    /* this + 8  */ float mNumEntitiesRenderedThisFrame;
    /* this + 12 */ float mLastFrameTime;
    /* this + 16 */ SortedMeshDrawList* mSortedMeshDrawList;
    /* this + 24 */ ClientInstance* mClientInstance;
    /* this + 32 */ MinecraftGame* mMinecraftGame;
    /* this + 40 */ ScreenContext* mScreenContext;
    /* this + 48 */ BlockActorRenderDispatcher* mBlockEntityRenderDispatcher;
    /* this + 56 */ std::shared_ptr<ActorRenderDispatcher> mEntityRenderDispatcher;
    /* this + 72 */ ActorBlockRenderer* mEntityBlockRenderer;
    /* this + 80 */ ItemInHandRenderer* mItemInHandRenderer;
    /* this + 88 */ ItemRenderer* itemRenderer;
    std::byte padding1[0x238];

public:
    BaseActorRenderContext(ScreenContext* screenContext, IClientInstance* clientInstance, IMinecraftGame* minecraftGame);
};

static_assert(sizeof(BaseActorRenderContext) == 0x298);
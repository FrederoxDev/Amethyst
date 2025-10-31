#include "hooks/Hooks.hpp"
#include <amethyst/runtime/events/RenderingEvents.hpp>
#include <mc/src/common/world/level/block/definition/BlockDefinitionGroup.hpp>
#include <amethyst/runtime/events/RegisterEvents.hpp>
#include <amethyst/runtime/events/GameEvents.hpp>
#include <mc/src-client/common/client/renderer/screen/MinecraftUIRenderContext.hpp>
#include <mc/src-client/common/client/renderer/blockActor/BlockActorRendererDispatcher.hpp>
#include <amethyst/runtime/ModContext.hpp>
#include <thread>

SafetyHookInline _ScreenView_setupAndRender;
SafetyHookInline _ClientInstance_onStartJoinGame;
SafetyHookInline _ClientInstance_requestLeaveGame;
SafetyHookInline _Minecraft_update;
SafetyHookInline _VanillaItems_registerItems;
SafetyHookInline _BlockDefinitionGroup_registerBlocks;
SafetyHookInline _ClientInstance__ClientInstance;
SafetyHookInline _BlockGraphics_initBlocks;
SafetyHookInline _BlockActorRenderDispatcher_initializeBlockEntityRenderers;

void ScreenView_setupAndRender(ScreenView* self, MinecraftUIRenderContext* ctx)
{
    auto& bus = Amethyst::GetEventBus();
    BeforeRenderUIEvent ev(*self, *ctx);
    bus.Invoke(ev);

    _ScreenView_setupAndRender.call(self, ctx);

    AfterRenderUIEvent afterEv(*self, *ctx);
    bus.Invoke(afterEv);
}


int64_t ClientInstance_onStartJoinGame(ClientInstance* self, int64_t a2, int64_t a3, uint64_t a4)
{
    OnStartJoinGameEvent event(*self);
    Amethyst::GetEventBus().Invoke(event);
    Amethyst::GetClientCtx().mIsInWorldOrLoading = true;
    return _ClientInstance_onStartJoinGame.call<int64_t, ClientInstance*, int64_t, int64_t, uint64_t>(self, a2, a3, a4);
}

void ClientInstance_requestLeaveGame(ClientInstance* self, char switchScreen, char sync)
{
    OnRequestLeaveGameEvent event(*self);
    Amethyst::GetEventBus().Invoke(event);
    Amethyst::GetClientCtx().mIsInWorldOrLoading = false;
    _ClientInstance_requestLeaveGame.thiscall(self, switchScreen, sync);
}

BOOL Minecraft_update(Minecraft* self)
{
    BOOL value = _Minecraft_update.call<BOOL, Minecraft*>(self);

    UpdateEvent event(*self);
    Amethyst::GetEventBus().Invoke(event);

    return value;
}

void VanillaItems_registerItems(
    void* a1,
    const ItemRegistryRef* itemRegistry,
    const BaseGameVersion* baseGameVersion,
    const Experiments* experiments) 
{
    // Allow Vanilla to register its own items first
    _VanillaItems_registerItems.fastcall(a1, itemRegistry, baseGameVersion, experiments);

    //std::shared_ptr<ItemRegistry> registry = itemRegistry.mItemRegistry.lock();
    ItemRegistry* registry = itemRegistry->mItemRegistry.lock().get();

    auto& shared = Amethyst::GetCurrentThreadCtx();

    RegisterItemsEvent event(*registry, shared.mCreativeRegistry);
    Amethyst::GetEventBus().Invoke(event);
}

void BlockDefinitionGroup_registerBlocks(BlockDefinitionGroup* self) {
    RegisterBlocksEvent event(*self);
    Amethyst::GetEventBus().Invoke(event);
    _BlockDefinitionGroup_registerBlocks.thiscall<void>(self);
}

void LevelEvent(Level* level) {
    if (level == nullptr) {
        OnLevelDestroyedEvent event;
        Amethyst::GetEventBus().Invoke(event);
        return;
    }

    OnLevelConstructedEvent event(*level);
    Amethyst::GetEventBus().Invoke(event);
}

void* ClientInstance__ClientInstance(ClientInstance* self, uint64_t a2, uint64_t a3, uint64_t a4, char a5, void* a6, void* a7, uint64_t a8, void* a9) {
    void* ret = _ClientInstance__ClientInstance.call<void*>(self, a2, a3, a4, a5, a6, a7, a8, a9);

    Amethyst::GetClientCtx().mClientInstance = self;

    return ret;
}

SafetyHookInline _Minecraft__Minecraft;

Minecraft* Minecraft__Minecraft(Minecraft* a1, void* a2, void* a3, void* a4, void* a5, void* a6, void* a7, void* a8, void* a9, void* a10, char a11, void* a12, void* a13, void* a14, void* a15) {
    _Minecraft__Minecraft.call<Minecraft*>(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15);
    AmethystContext& ctx = Amethyst::GetContext();

    // This is where the initial threads ids are found, so at this point Amethsyt::IsOnMainClietnThread and Amethyst::IsOnMainServerThread will start working.
    // But for this it does have to do a tiny bit of jank such that this can be setup
    
    if (Amethyst::IsOnMainClientThread()) {
        Amethyst::GetClientCtx().mMinecraft = a1;
        ctx.mMainClientThread = std::this_thread::get_id();
    }
    else {
        Amethyst::GetContext().mServerCtx = std::make_unique<Amethyst::ServerContext>();
        Amethyst::GetServerCtx().mMinecraft = a1;
        ctx.mMainServerThread = std::this_thread::get_id();
    }

    auto context = Bedrock::PubSub::SubscriptionContext::makeDefaultContext("Amethyst LevelEvent Subscriber");
    a1->mLevelSubscribers->_connectInternal(LevelEvent, Bedrock::PubSub::ConnectPosition::AtFront, std::move(context), std::nullopt);

    return a1;
}

SafetyHookInline _Minecraft_$dtor;

void* Minecraft_$dtor(Minecraft* a1, char a2) {
    Amethyst::GetContext().mServerCtx.reset();
    return _Minecraft_$dtor.call<void*>(a1, a2);
}

void BlockGraphics_initBlocks(ResourcePackManager& resources, const Experiments& experiments) {
    _BlockGraphics_initBlocks.call<void, ResourcePackManager&, const Experiments&>(resources, experiments);

    InitBlockGraphicsEvent event(resources, experiments);
    Amethyst::GetEventBus().Invoke(event);
}

void BlockActorRenderDispatcher_initializeBlockEntityRenderers(
    BlockActorRenderDispatcher* self,
    const Bedrock::NotNullNonOwnerPtr<GeometryGroup>& geometryGroup,
    std::shared_ptr<mce::TextureGroup> textures,
    BlockTessellator& blockTessellator,
    const Bedrock::NotNullNonOwnerPtr<const ActorResourceDefinitionGroup>& entityResourceDefGroup,
    ResourcePackManager& resourcePackManager,
    MinecraftGameplayGraphicsResources& gameplayGraphicsResources,
    Bedrock::NotNullNonOwnerPtr<ResourceLoadManager> resourceLoadManager,
    const BaseGameVersion& version,
    const Experiments& experiments)
{
    _BlockActorRenderDispatcher_initializeBlockEntityRenderers.thiscall<
        void,
        BlockActorRenderDispatcher*,
        const Bedrock::NotNullNonOwnerPtr<GeometryGroup>&,
        std::shared_ptr<mce::TextureGroup>,
        BlockTessellator&,
        const Bedrock::NotNullNonOwnerPtr<const ActorResourceDefinitionGroup>&,
        ResourcePackManager&,
        MinecraftGameplayGraphicsResources&,
        Bedrock::NotNullNonOwnerPtr<ResourceLoadManager>,
        const BaseGameVersion&,
        const Experiments&
    >(
        self, 
        geometryGroup, 
        textures, 
        blockTessellator, 
        entityResourceDefGroup, 
        resourcePackManager,
        gameplayGraphicsResources, 
        resourceLoadManager, 
        version, 
        experiments
    );

    InitBlockEntityRenderersEvent event(*self, geometryGroup, textures, blockTessellator, entityResourceDefGroup, resourcePackManager, gameplayGraphicsResources, resourceLoadManager, version, experiments);
    Amethyst::GetEventBus().Invoke(event);
}

void CreateModFunctionHooks() {
    Amethyst::HookManager& hooks = Amethyst::GetHookManager();

	#ifdef CLIENT
    HOOK(ClientInstance, onStartJoinGame);
    HOOK(ClientInstance, requestLeaveGame);
    HOOK(ClientInstance, _ClientInstance);
    HOOK(ScreenView, setupAndRender);
    HOOK(BlockGraphics, initBlocks);
    HOOK(BlockActorRenderDispatcher, initializeBlockEntityRenderers);
    #endif

    HOOK(Minecraft, update);
    HOOK(Minecraft, _Minecraft);
    HOOK(VanillaItems, registerItems);
    HOOK(BlockDefinitionGroup, registerBlocks);
    HOOK(Minecraft, $dtor);
}
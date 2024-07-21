#include "hooks/Hooks.hpp"
#include <amethyst/runtime/events/RenderingEvents.hpp>
#include <minecraft/src/common/world/level/block/definition/BlockDefinitionGroup.hpp>
#include <amethyst/runtime/events/RegisterEvents.hpp>
#include <amethyst/runtime/events/GameEvents.hpp>

SafetyHookInline _ScreenView_setupAndRender;
SafetyHookInline _ClientInstance_onStartJoinGame;
SafetyHookInline _ClientInstance_requestLeaveGame;
SafetyHookInline _Minecraft_update;
SafetyHookInline _VanillaItems_registerItems;
SafetyHookInline _BlockDefinitionGroup_registerBlocks;
SafetyHookInline _LevelRenderer_renderLevel;
SafetyHookInline _ClientInstance_ClientInstance;
SafetyHookInline _BlockGraphics_initBlocks;

void* ScreenView_setupAndRender(ScreenView* self, UIRenderContext* ctx)
{
    Amethyst::EventBus* eventBus = AmethystRuntime::getEventBus();
    BeforeRenderUIEvent ev(*self, *ctx);
    eventBus->Invoke(ev);

    void* res = _ScreenView_setupAndRender.call<void*, ScreenView*, UIRenderContext*>(self, ctx);

    AfterRenderUIEvent afterEv(*self, *ctx);
    eventBus->Invoke(afterEv);

    return res;
}


int64_t ClientInstance_onStartJoinGame(ClientInstance* self, int64_t a2, int64_t a3, uint64_t a4)
{
    OnStartJoinGameEvent event(*self);
    AmethystRuntime::getEventBus()->Invoke(event);
    return _ClientInstance_onStartJoinGame.call<int64_t, ClientInstance*, int64_t, int64_t, uint64_t>(self, a2, a3, a4);
}

void ClientInstance_requestLeaveGame(ClientInstance* self, char switchScreen, char sync)
{
    OnRequestLeaveGameEvent event(*self);
    AmethystRuntime::getEventBus()->Invoke(event);
    _ClientInstance_requestLeaveGame.thiscall(self, switchScreen, sync);
}

BOOL Minecraft_update(Minecraft* self)
{
    BOOL value = _Minecraft_update.call<BOOL, Minecraft*>(self);

    UpdateEvent event;
    AmethystRuntime::getEventBus()->Invoke(event);

    return value;
}

void* VanillaItems_registerItems(
    void* a1,
    const ItemRegistryRef itemRegistry,
    const BaseGameVersion* baseGameVersion,
    const Experiments* experiments) 
{
    // Allow Vanilla to register its own items first
    void* result = _VanillaItems_registerItems.fastcall<void*>(a1, &itemRegistry, baseGameVersion, experiments);

    std::shared_ptr<ItemRegistry> registry = itemRegistry.mItemRegistry.lock();
    RegisterItemsEvent event(*registry.get());

    AmethystRuntime::getEventBus()->Invoke(event);

    return result;
}

void BlockDefinitionGroup_registerBlocks(BlockDefinitionGroup* self) {
    RegisterBlocksEvent event(*self);
    AmethystRuntime::getEventBus()->Invoke(event);
    _BlockDefinitionGroup_registerBlocks.thiscall<void>(self);
}

void* ClientInstance_ClientInstance(ClientInstance* self, uint64_t a2, uint64_t a3, uint64_t a4, char a5, void* a6, void* a7, uint64_t a8, void* a9) {
    void* ret = _ClientInstance_ClientInstance.call<void*>(self, a2, a3, a4, a5, a6, a7, a8, a9);

    AmethystRuntime::getContext()->mClientInstance = self;

    return ret;
}

void BlockGraphics_initBlocks(ResourcePackManager& resources, const Experiments& experiments) {
    _BlockGraphics_initBlocks.call<void, ResourcePackManager&, const Experiments&>(resources, experiments);

    InitBlockGraphicsEvent event(resources, experiments);
    AmethystRuntime::getEventBus()->Invoke(event);
}

void CreateModFunctionHooks() {
    Amethyst::HookManager* hookManager = AmethystRuntime::getHookManager();

    hookManager->RegisterFunction<&ScreenView::setupAndRender>("48 8B C4 48 89 58 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 0F 29 70 ? 0F 29 78 ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4C 8B FA");
    hookManager->CreateHook<&ScreenView::setupAndRender>(_ScreenView_setupAndRender, &ScreenView_setupAndRender);

    hookManager->RegisterFunction<&Minecraft::update>("48 8B C4 48 89 58 ? 48 89 70 ? 48 89 78 ? 55 41 54 41 55 41 56 41 57 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 0F 29 70 ? 0F 29 78 ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4C 8B E9 48 89 4C 24");
    hookManager->CreateHook<&Minecraft::update>(_Minecraft_update, &Minecraft_update);

    hookManager->RegisterFunction<&ClientInstance::onStartJoinGame>("40 55 53 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 45 8B F1");
    hookManager->CreateHook<&ClientInstance::onStartJoinGame>(_ClientInstance_onStartJoinGame, &ClientInstance_onStartJoinGame);
    
    hookManager->RegisterFunction<&ClientInstance::requestLeaveGame>("48 89 5C 24 ? 48 89 74 24 ? 55 57 41 54 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 45 0F B6 F0 44 0F B6 FA");
    hookManager->CreateHook<&ClientInstance::requestLeaveGame>(_ClientInstance_requestLeaveGame, &ClientInstance_requestLeaveGame);
    
    hookManager->RegisterFunction<&ClientInstance::_ClientInstance>("48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 49 8B F9 49 8B D8 4C 8B E2");
    hookManager->CreateHook<&ClientInstance::_ClientInstance>(_ClientInstance_ClientInstance, &ClientInstance_ClientInstance);
    
    hookManager->RegisterFunction<&VanillaItems::registerItems>("40 55 53 56 57 41 54 41 56 41 57 48 8D AC 24 ? ? ? ? B8 ? ? ? ? E8 ? ? ? ? 48 2B E0 0F 29 B4 24");
    hookManager->CreateHook<&VanillaItems::registerItems>(_VanillaItems_registerItems, &VanillaItems_registerItems);
    
    hookManager->RegisterFunction<&BlockDefinitionGroup::registerBlocks>("48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 41 54 41 55 41 56 41 57 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 84 24 ? ? ? ? 45 33 E4");
    hookManager->CreateHook<&BlockDefinitionGroup::registerBlocks>(_BlockDefinitionGroup_registerBlocks, &BlockDefinitionGroup_registerBlocks);
    
    hookManager->RegisterFunction<&BlockGraphics::initBlocks>("48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4C 8B E2 48 89 95 ? ? ? ? 4C 8B F9 48 89 4D");
    hookManager->CreateHook<&BlockGraphics::initBlocks>(_BlockGraphics_initBlocks, &BlockGraphics_initBlocks);
}
#include "hooks/Hooks.hpp"

SafetyHookInline _ScreenView_setupAndRender;
SafetyHookInline _ClientInstance_onStartJoinGame;
SafetyHookInline _ClientInstance_requestLeaveGame;
SafetyHookInline _Minecraft_update;
SafetyHookInline _VanillaItems_registerItems;
SafetyHookInline _BlockDefinitionGroup_registerBlocks;
SafetyHookInline _LevelRenderer_renderLevel;
SafetyHookInline _ClientInstance_ClientInstance;

void* ScreenView_setupAndRender(ScreenView* self, UIRenderContext* ctx)
{
    Amethyst::EventManager* events = AmethystRuntime::getEventManager();
    events->beforeRenderUI.Invoke(self, ctx);
    void* res = _ScreenView_setupAndRender.call<void*, ScreenView*, UIRenderContext*>(self, ctx);
    events->afterRenderUI.Invoke(self, ctx);
    return res;
}

int64_t ClientInstance_onStartJoinGame(ClientInstance* self, int64_t a2, int64_t a3, uint64_t a4)
{
    Amethyst::EventManager* events = AmethystRuntime::getEventManager();
    events->onStartJoinGame.Invoke(self);

    return _ClientInstance_onStartJoinGame.call<int64_t, ClientInstance*, int64_t, int64_t, uint64_t>(self, a2, a3, a4);
}

void ClientInstance_requestLeaveGame(ClientInstance* self, char switchScreen, char sync)
{
    Amethyst::EventManager* events = AmethystRuntime::getEventManager();

    events->onRequestLeaveGame.Invoke();

    _ClientInstance_requestLeaveGame.thiscall(self, switchScreen, sync);
}

bool Minecraft_update(Minecraft* self) {
    Amethyst::EventManager* events = AmethystRuntime::getEventManager();

    bool value = _Minecraft_update.call<bool, Minecraft*>(self);
    events->update.Invoke();

    return value;
}

void* VanillaItems_registerItems(
    void* a1,
    const ItemRegistryRef itemRegistry,
    const BaseGameVersion* baseGameVersion,
    const Experiments* experiments) 
{
    Amethyst::EventManager* events = AmethystRuntime::getEventManager();

    // Allow Vanilla to register its own items first
    void* result = _VanillaItems_registerItems.fastcall<void*>(a1, &itemRegistry, baseGameVersion, experiments);

    std::shared_ptr<ItemRegistry> registry = itemRegistry.mItemRegistry.lock();

    events->registerItems.Invoke(registry.get());

    return result;
}

void BlockDefinitionGroup_registerBlocks(BlockDefinitionGroup* self) {
    Amethyst::EventManager* events = AmethystRuntime::getEventManager();

    events->registerBlocks.Invoke(self);

    _BlockDefinitionGroup_registerBlocks.thiscall<void>(self);
}

void* LevelRenderer_renderLevel(LevelRenderer* self, ScreenContext* screenContext, FrameRenderObject* frameRenderObject) {
    Amethyst::EventManager* events = AmethystRuntime::getEventManager();

    events->onRenderLevel.Invoke(self, screenContext, frameRenderObject);

    return _LevelRenderer_renderLevel.thiscall<void*>(self, screenContext, frameRenderObject);
}

void* ClientInstance_ClientInstance(ClientInstance* self, uint64_t a2, uint64_t a3, uint64_t a4, char a5, void* a6, void* a7, uint64_t a8, void* a9) {
    void* ret = _ClientInstance_ClientInstance.call<void*>(self, a2, a3, a4, a5, a6, a7, a8, a9);

    AmethystRuntime::getContext()->mClientInstance = self;

    return ret;
}

void CreateModFunctionHooks() {
    HookManager* hookManager = AmethystRuntime::getHookManager();

    Log::Info("jidwjekdf");

    hookManager->RegisterFunction<&ScreenView::setupAndRender>("48 8B C4 48 89 58 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 0F 29 70 ? 0F 29 78 ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4C 8B FA");
    hookManager->RegisterFunction<&Minecraft::update>("48 8B C4 48 89 58 ? 48 89 70 ? 48 89 78 ? 55 41 54 41 55 41 56 41 57 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 0F 29 70 ? 0F 29 78 ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4C 8B E9 48");
    hookManager->RegisterFunction<&ClientInstance::onStartJoinGame>("40 55 53 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 45 8B F1");
    hookManager->RegisterFunction<&ClientInstance::requestLeaveGame>("48 89 5C 24 ? 48 89 74 24 ? 55 57 41 54 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 45 0F B6 F0 44 0F B6 FA");
    hookManager->RegisterFunction<&ClientInstance::_ClientInstance>("48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 49 8B F9 49 8B D8 4C 8B E2");
    
    hookManager->RegisterFunction<&VanillaItems::registerItems>("40 55 53 56 57 41 54 41 56 41 57 48 8D AC 24 ? ? ? ? B8 ? ? ? ? E8 ? ? ? ? 48 2B E0 0F 29 B4 24");
    hookManager->RegisterFunction<&BlockDefinitionGroup::registerBlocks>("48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 41 54 41 55 41 56 41 57 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 84 24 ? ? ? ? 45 33 ED");
    //hookManager->RegisterFunction<&LevelRenderer::renderLevel>("48 89 5C 24 ? 48 89 74 24 ? 55 57 41 56 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 49 8B F0 48 8B DA 4C 8B F1");

    /* Make hooks */
    hookManager->CreateHook<&ScreenView::setupAndRender>(_ScreenView_setupAndRender, &ScreenView_setupAndRender);
    hookManager->CreateHook<&Minecraft::update>(_Minecraft_update, &Minecraft_update);
    hookManager->CreateHook<&ClientInstance::onStartJoinGame>(_ClientInstance_onStartJoinGame, &ClientInstance_onStartJoinGame);
    hookManager->CreateHook<&ClientInstance::requestLeaveGame>(_ClientInstance_requestLeaveGame, &ClientInstance_requestLeaveGame);
    hookManager->CreateHook<&ClientInstance::_ClientInstance>(_ClientInstance_ClientInstance, &ClientInstance_ClientInstance);

    hookManager->CreateHook<&VanillaItems::registerItems>(_VanillaItems_registerItems, &VanillaItems_registerItems);
    hookManager->CreateHook<&BlockDefinitionGroup::registerBlocks>(_BlockDefinitionGroup_registerBlocks, &BlockDefinitionGroup_registerBlocks);
    //hookManager->CreateHook<&LevelRenderer::renderLevel>(_LevelRenderer_renderLevel, &LevelRenderer_renderLevel);
}
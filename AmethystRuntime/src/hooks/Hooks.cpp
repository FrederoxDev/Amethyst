#include "hooks/Hooks.h"

ScreenView::_setupAndRender _ScreenView_setupAndRender;
static void* ScreenView_setupAndRender(ScreenView* self, UIRenderContext* ctx)
{
    Amethyst::EventManager* events = AmethystRuntime::getEventManager();
    events->onRenderUI.Invoke(self, ctx);
    return _ScreenView_setupAndRender(self, ctx);
}

ClientInstance::_onStartJoinGame _ClientInstance_onStartJoinGame;
static int64_t ClientInstance_onStartJoinGame(ClientInstance* self, int64_t a2, int64_t a3, uint64_t a4)
{
    Amethyst::EventManager* events = AmethystRuntime::getEventManager();
    events->onStartJoinGame.Invoke(self);
    return _ClientInstance_onStartJoinGame(self, a2, a3, a4);
}

Minecraft::_update _Minecraft_update;
static bool Minecraft_update(Minecraft* self) {
    Amethyst::EventManager* events = AmethystRuntime::getEventManager();

    events->beforeTick.Invoke();
    bool value = _Minecraft_update(self);
    events->afterTick.Invoke();

    return value;
}

void CreateModFunctionHooks() {
    HookManager* hookManager = AmethystRuntime::getHookManager();
    AmethystRuntime* runtime = AmethystRuntime::getInstance();

    hookManager->RegisterFunction(&ScreenView::setupAndRender, "48 8B C4 48 89 58 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 0F 29 70 ? 0F 29 78 ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4C 8B FA 48 89 54 24 ? 4C 8B E9 48 89 4C 24");
    hookManager->RegisterFunction(&Minecraft::update, "48 8B C4 48 89 58 ? 48 89 70 ? 48 89 78 ? 55 41 54 41 55 41 56 41 57 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 0F 29 70 ? 0F 29 78 ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4C 8B E9 48");
    hookManager->RegisterFunction(&ClientInstance::onStartJoinGame, "40 55 53 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 45 8B F1");

    /*hookManager->CreateHook(
        &ScreenView::setupAndRender,
        &ScreenView_setupAndRender, reinterpret_cast<void**>(&_ScreenView_setupAndRender));
    
    hookManager->CreateHook(
        &ClientInstance::onStartJoinGame,
        &ClientInstance_onStartJoinGame, reinterpret_cast<void**>(&_ClientInstance_onStartJoinGame));

    hookManager->CreateHook(
        &Minecraft::update,
        &Minecraft_update, reinterpret_cast<void**>(&_Minecraft_update));*/
}
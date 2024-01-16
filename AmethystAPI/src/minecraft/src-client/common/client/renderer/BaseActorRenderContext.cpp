#include "common/client/renderer/BaseActorRenderContext.h"

BaseActorRenderContext::BaseActorRenderContext(ScreenContext* screenContext, IClientInstance* clientInstance, IMinecraftGame* minecraftGame) {
    using function = void(__thiscall*)(BaseActorRenderContext*, ScreenContext*, IClientInstance*, IMinecraftGame*);
    static auto func = reinterpret_cast<function>(SigScan("48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 48 89 4C 24 ? 57 48 83 EC ? 49 8B F8 48 8B DA 48 8B F1 48 8D 05 ? ? ? ? 48 89 01 33 ED"));
    func(this, screenContext, clientInstance, minecraftGame);
}
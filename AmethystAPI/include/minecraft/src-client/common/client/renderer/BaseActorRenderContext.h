#pragma once
#include "amethyst/Memory.h"

class ScreenContext;
class ClientInstance;
using IClientInstance = ClientInstance;

class MinecraftGame;
using IMinecraftGame = MinecraftGame;

class BaseActorRenderContext {
private:
    bool padding[0x298];

public:
    BaseActorRenderContext(ScreenContext* screenContext, IClientInstance* clientInstance, IMinecraftGame* minecraftGame);
};

static_assert(sizeof(BaseActorRenderContext) == 0x298);
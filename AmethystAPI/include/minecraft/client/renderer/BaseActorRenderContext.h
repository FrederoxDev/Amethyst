#pragma once
#include "amethyst/Memory.h"

class ScreenContext;
class ClientInstance;
using IClientInstance = ClientInstance;

class MinecraftGame;
using IMinecraftGame = MinecraftGame;

class ItemRenderer;

class BaseActorRenderContext {
public:
    bool padding[0x58];
    ItemRenderer* itemRenderer;
    bool padding1[0x238];

public:
    BaseActorRenderContext(ScreenContext* screenContext, IClientInstance* clientInstance, IMinecraftGame* minecraftGame);
};

static_assert(sizeof(BaseActorRenderContext) == 0x298);
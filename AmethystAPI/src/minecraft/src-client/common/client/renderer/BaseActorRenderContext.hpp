#pragma once
#include "amethyst/Memory.hpp"

class ScreenContext;
class ClientInstance;
using IClientInstance = ClientInstance;

class MinecraftGame;
using IMinecraftGame = MinecraftGame;

class ItemRenderer;

class BaseActorRenderContext {
public:
    std::byte padding[0x58];
    ItemRenderer* itemRenderer;
    std::byte padding1[0x238];

public:
    BaseActorRenderContext(ScreenContext* screenContext, IClientInstance* clientInstance, IMinecraftGame* minecraftGame);
};

static_assert(sizeof(BaseActorRenderContext) == 0x298);
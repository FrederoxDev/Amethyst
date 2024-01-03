#pragma once
#include "amethyst/Memory.h"
#include "amethyst/HookManager.h"
#include "minecraft/src-client/common/client/input/RemappingLayout.h"
#include "minecraft/src-client/common/client/input/VanillaClientInputMappingFactory.h"
#include "minecraft/src-client/common/client/game/ClientInstance.h"
#include "minecraft/src-client/common/client/input/ClientInputHandler.h"
#include "minecraft/src-client/common/client/input/MinecraftInputHandler.h"

namespace Amethyst {
void CreateInputHooks(HookManager* hookManager);
};
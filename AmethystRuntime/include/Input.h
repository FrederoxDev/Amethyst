#pragma once
#include "amethyst/HookManager.h"
#include "amethyst/Memory.h"
#include "minecraft/src-client/common/client/game/ClientInstance.h"
#include "minecraft/src-client/common/client/input/ClientInputHandler.h"
#include "minecraft/src-client/common/client/input/MinecraftInputHandler.h"
#include "minecraft/src-client/common/client/input/RemappingLayout.h"
#include "minecraft/src-client/common/client/input/VanillaClientInputMappingFactory.h"

namespace Amethyst {
void CreateInputHooks(HookManager* hookManager);
};
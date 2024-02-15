#pragma once
#include "minecraft/src-client/common/client/game/ClientInstance.h"
#include "minecraft/src-client/common/client/gui/gui/GuiData.h"
#include "minecraft/src-client/common/client/renderer/Tessellator.h"

using IClientInstance = ClientInstance;

#pragma pack(push, 1)
class ScreenContext {
public:
    std::byte padding0[192];
    Tessellator& tessellator;
};
#pragma pack(pop)
#pragma once
#include "minecraft/src-client/common/client/game/ClientInstance.h"
#include "minecraft/src-client/common/client/gui/gui/GuiData.h"
#include "minecraft/src-client/common/client/renderer/Tessellator.h"
#include "minecraft/src-client/common/client/gui/screens/UIScreenContext.h"
#include "minecraft/src-deps/minecraftrenderer/renderer/MeshContext.h"

using IClientInstance = ClientInstance;

#pragma pack(push, 1)
class ScreenContext : public UIScreenContext, public mce::MeshContext {
public:
    std::byte padding0[168];
    Tessellator& tessellator; // this + 192
};
#pragma pack(pop)
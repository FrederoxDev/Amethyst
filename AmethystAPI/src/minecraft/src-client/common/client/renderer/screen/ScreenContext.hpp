#pragma once
#include "minecraft/src-client/common/client/game/ClientInstance.hpp"
#include "minecraft/src-client/common/client/gui/gui/GuiData.hpp"
#include "minecraft/src-client/common/client/renderer/Tessellator.hpp"
#include "minecraft/src-client/common/client/gui/screens/UIScreenContext.hpp"
#include "minecraft/src-deps/minecraftrenderer/renderer/MeshContext.hpp"

using IClientInstance = ClientInstance;

#pragma pack(push, 1)
class ScreenContext : public UIScreenContext, public mce::MeshContext {
public:
    std::byte padding0[160];
    Tessellator& tessellator; // this + 192
};
#pragma pack(pop)
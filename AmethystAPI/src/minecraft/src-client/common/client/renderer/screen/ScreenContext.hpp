#pragma once
#include "minecraft/src-client/common/client/gui/screens/UIScreenContext.hpp"
#include "minecraft/src-deps/minecraftrenderer/renderer/MeshContext.hpp"

class ClientInstance;
using IClientInstance = ClientInstance;
class Tessellator;

#pragma pack(push, 1)
class ScreenContext : public UIScreenContext, public mce::MeshContext {
public:
    std::byte padding0[160];
    Tessellator& tessellator; // this + 192
};
#pragma pack(pop)
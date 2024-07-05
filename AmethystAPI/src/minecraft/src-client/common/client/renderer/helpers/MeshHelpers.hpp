#pragma once

class ScreenContext;
class Tessellator;

namespace mce {
class MaterialPtr;
}

class Tessellator;

namespace MeshHelpers {
static void renderMeshImmediately(ScreenContext* screenContext, Tessellator* tessellator, const mce::MaterialPtr* material);
};
#include "minecraft/src-client/common/client/renderer/RenderMaterialGroup.hpp"
#include <amethyst/Memory.hpp>

mce::RenderMaterialGroupBase* mce::RenderMaterialGroup::switchable = reinterpret_cast<RenderMaterialGroupBase*>(SlideAddress(0x572BBB0));
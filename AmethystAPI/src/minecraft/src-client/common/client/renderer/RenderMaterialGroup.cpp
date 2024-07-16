#include "minecraft/src-client/common/client/renderer/RenderMaterialGroup.hpp"
#include <amethyst/Memory.hpp>

mce::RenderMaterialGroup* mce::RenderMaterialGroup::common = reinterpret_cast<RenderMaterialGroup*>(SlideAddress(0x59C02F0));
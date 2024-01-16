#pragma once
#include "amethyst/Memory.h"
#include <stdint.h>

class ItemStack;
class BaseActorRenderContext;

class ItemRenderer {
public:
    void renderGuiItemNew(BaseActorRenderContext* renderContext, const ItemStack* item, uint32_t frame, float x, float y, bool forceEnchantmentFoil, float transparency, float lightMultiplyer, float scale);

//hooks:
    // 48 8B C4 48 89 58 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 0F 29 70 ? 0F 29 78 ? 4C 8B FA
    typedef void*(__thiscall* _ItemRenderer)(ItemRenderer*, void*);
};
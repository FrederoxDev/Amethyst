#include "minecraft/src-client/common/client/renderer/actor/ItemRenderer.h"

void ItemRenderer::renderGuiItemNew(BaseActorRenderContext* renderContext, const ItemStack* item, uint64_t frame, float x, float y, float transparency, float lightMultiplyer, float scale, bool forceEnchantmentFoil) {
	using function = void(__thiscall*)(ItemRenderer*, BaseActorRenderContext*, const ItemStack*, uint64_t, float, float, float, float, float, bool);
    static auto func = reinterpret_cast<function>(SigScan("48 8B C4 53 55 56 57 41 54 41 55 41 56 41 57 48 81 EC ? ? ? ? 0F 29 70 ? 0F 29 78 ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 84 24 ? ? ? ? 45 8B E1"));
    func(this, renderContext, item, frame, x, y, transparency, lightMultiplyer, scale, forceEnchantmentFoil);
}
#pragma once
#include "amethyst/Memory.h"
#include <cstdint>

class ItemStack;
class BaseActorRenderContext;

class ItemRenderer {
public:
    void renderGuiItemNew(BaseActorRenderContext* BaseActorRenderCtx, ItemStack* item, int mode, float x, float y, float opacity, float scale, bool isEnchanted)
	{
		using fn = void(__fastcall*)(ItemRenderer*, BaseActorRenderContext*, ItemStack*, int, float, float, bool, float, float, float);
		static auto func = reinterpret_cast<fn>(FindSignature("48 8B ? 53 55 56 57 41 ? 41 ? 41 ? 41 ? 48 81 EC ? ? ? ? 0F 29 ? ? 0F 29 ? ? 48 8B ? ? ? ? ? 48 33 ? 48 89 ? ? ? ? ? ? 45 8B"));
		func(this, BaseActorRenderCtx, item, mode, x, y, isEnchanted, 1, opacity, scale);
	}

//hooks:
    // 48 8B C4 48 89 58 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 0F 29 70 ? 0F 29 78 ? 4C 8B FA
    typedef void*(__thiscall* _ItemRenderer)(ItemRenderer*, void*);
};

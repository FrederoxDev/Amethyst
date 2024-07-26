#pragma once
#include <amethyst/runtime/AmethystContext.hpp>

class Minecraft;
class Level;

namespace Amethyst {
	/**
	Initializes internal variables required for an Amethyst mod to function.
	 - This should be the first thing called in the ModFunction Initialize().
	*/
	void InitializeAmethystMod(AmethystContext& context);

	AmethystContext& GetContext();
	Amethyst::EventBus& GetEventBus();
	Amethyst::HookManager& GetHookManager();
	Amethyst::PatchManager& GetPatchManager();
	Amethyst::EnumAllocator& GetEnumAllocator();

	Minecraft* GetMinecraft();
	Level* GetLevel();
}
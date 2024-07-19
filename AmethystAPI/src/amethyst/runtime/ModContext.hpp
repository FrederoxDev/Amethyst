#pragma once
#include <amethyst/runtime/AmethystContext.hpp>

namespace Amethyst {
	/**
	Initializes internal variables required for an Amethyst mod to function.
	 - This should be the first thing called in the ModFunction Initialize().
	*/
	void InitializeAmethystMod(AmethystContext& context);

	/**
	* Returns the current instance of the Amethyst EventBus
	*/
	Amethyst::EventBus& GetEventBus();

	/**
	* Returns the current instance of the Amethyst HookManager
	*/
	Amethyst::HookManager& GetHookManager();
}
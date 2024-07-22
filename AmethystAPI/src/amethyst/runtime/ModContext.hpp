#pragma once
#include <amethyst/runtime/AmethystContext.hpp>

namespace Amethyst {
	/**
	Initializes internal variables required for an Amethyst mod to function.
	 - This should be the first thing called in the ModFunction Initialize().
	*/
	void InitializeAmethystMod(AmethystContext& context);

	/**
	* Returns the current instance of the AmethystContext
	*/
	AmethystContext& GetContext();

	/**
	* Returns the current instance of the Amethyst::EventBus
	*/
	Amethyst::EventBus& GetEventBus();

	/**
	* Returns the current instance of the Amethyst::HookManager
	*/
	Amethyst::HookManager& GetHookManager();

	/**
	* Returns the current instance of the Amethyst::PatchManager
	*/
	Amethyst::PatchManager& GetPatchManager();

	/**
	* Returns the current instance of the Amethyst::EnumAllocator
	*/
	Amethyst::EnumAllocator& GetEnumAllocator();

	/**
	* Returns the current instance of the Amethyst::RuntimeFeatures
	*/
	Amethyst::RuntimeFeatures& GetFeatures();

	/**
	* Returns the current instance of the Amethyst::InputManager
	*/
	Amethyst::InputManager& GetInputManager();
}
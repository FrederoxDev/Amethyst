#pragma once
#include <amethyst/runtime/AmethystContext.hpp>
#include <amethyst/runtime/mod/Mod.hpp>
#include <amethyst/runtime/utility/InlineHook.hpp>

class Minecraft;
class Level;

namespace Amethyst {
	/**
	Initializes internal variables required for an Amethyst mod to function.
	 - This should be the first thing called in the ModFunction Initialize().
	*/
    void InitializeAmethystMod(AmethystContext& context, const Mod& mod);

	AmethystContext& GetContext();
	Amethyst::EventBus& GetEventBus();
	Amethyst::HookManager& GetHookManager();
	Amethyst::PatchManager& GetPatchManager();
	Amethyst::EnumAllocator& GetEnumAllocator();
	Amethyst::NetworkManager& GetNetworkManager();
	Amethyst::Platform& GetPlatform();

	Amethyst::ClientContext& GetClientCtx();
	Amethyst::ServerContext& GetServerCtx();

	/**
	Asserts off the two main threads, where no side owns the calling thread and so there is no
	right answer to give. Call it only from code that knows which thread it is on, and reach for
	TryGetCurrentThreadCtx anywhere that has to cope with being called from anywhere.
	*/
	Amethyst::SharedContext& GetCurrentThreadCtx();

	/** The context owning the calling thread, or nullptr if it is not one of the main threads. */
	Amethyst::SharedContext* TryGetCurrentThreadCtx();

	Amethyst::ThreadClass GetCurrentThreadClass();

	/** The name the game gave the calling thread, empty if it never named itself. */
	std::string GetCurrentThreadName();

	bool IsOnAmethystThread();
	bool IsOnMainClientThread();
	bool IsOnMainServerThread();

	bool IsAmethystContextInitialized();

	const Mod* GetOwnMod();
}
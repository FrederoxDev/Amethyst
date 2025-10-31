#pragma once
#include <amethyst/runtime/AmethystContext.hpp>
#include <amethyst/runtime/mod/Mod.hpp>

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
	Amethyst::SharedContext& GetCurrentThreadCtx();

	bool IsOnAmethystThread();
	bool IsOnMainClientThread();
	bool IsOnMainServerThread();
	
	bool IsAmethystContextInitialized();

	const Mod* GetOwnMod();
}
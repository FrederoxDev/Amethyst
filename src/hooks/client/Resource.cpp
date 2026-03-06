// #ifdef CLIENT
// #include "hooks/client/Resource.hpp"

// #include <amethyst/runtime/ModContext.hpp>
// #include <amethyst/runtime/utility/InlineHook.hpp>

// #include <vanilla_client/common/module/VanillaGameModuleClient.hpp>

// namespace Amethyst::ClientHooks::ResourceHooks {
// 	Amethyst::InlineHook<decltype(&VanillaGameModuleClient::initializeResourceStack)> _VanillaGameModuleClient_initializeResourceStack;
// 	void VanillaGameModuleClient_initializeResourceStack(
// 		VanillaGameModuleClient* self,
// 		const Experiments& experiments,
// 		const Bedrock::NotNullNonOwnerPtr<ResourcePackRepository>& repository,
// 		ResourcePackStack& stack,
// 		const BaseGameVersion& baseGameVer,
// 		GameModuleClient::ResourceLoadingPhase loadingPhase
// 	) {
// 		auto& context = Amethyst::GetContext();
// 		context.mPackManager->AddResourcePacksToStack(repository, stack);
// 		_VanillaGameModuleClient_initializeResourceStack(self, experiments, repository, stack, baseGameVer, loadingPhase);
// 	}

// 	void Initialize() {
// 		auto& hooks = Amethyst::GetHookManager();
// 		// VHOOK(VanillaGameModuleClient, initializeResourceStack, this);
// 	}
// }
// #endif
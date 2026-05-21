#ifdef CLIENT
#include <amethyst/runtime/ModContext.hpp>
#include <amethyst/runtime/utility/InlineHook.hpp>

#include <module/VanillaGameModuleClient.hpp>

namespace Amethyst::ClientHooks::ResourceHooks {
	Amethyst::InlineHook<decltype(&VanillaGameModuleClient::initializeResourceStack)> _VanillaGameModuleClient_initializeResourceStack;
	void VanillaGameModuleClient_initializeResourceStack(
		VanillaGameModuleClient* self,
		const Experiments* experiments,
		const ::gsl::not_null<::Bedrock::NonOwnerPointer<IResourcePackRepository>>& repo,
		ResourcePackStack& stack,
		const BaseGameVersion& baseGameVersion,
		::GameModuleClient::ResourceLoadingPhase loadingPhase,
		bool includeEditorPacks
	) {
		auto& context = Amethyst::GetContext();
		context.mPackManager->AddResourcePacksToStack(repo, stack);
		_VanillaGameModuleClient_initializeResourceStack(self, experiments, repo, stack, baseGameVersion, loadingPhase, includeEditorPacks);
	}

	void Initialize() {
		auto& hooks = Amethyst::GetHookManager();
		VHOOK(VanillaGameModuleClient, initializeResourceStack, VanillaGameModuleClient::$vtable_for_VanillaGameModuleClient);
	}
}
#endif
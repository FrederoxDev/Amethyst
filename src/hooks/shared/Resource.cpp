#if defined(CLIENT) || defined(SERVER)
#include "hooks/shared/Resource.hpp"

#include <amethyst/runtime/utility/InlineHook.hpp>
#include <amethyst/runtime/ModContext.hpp>

#include <server/module/VanillaGameModuleServer.hpp>
#include <resources/IResourcePackRepository.hpp>
#include <resources/ResourcePackStack.hpp>

namespace Amethyst::SharedHooks::ResourceHooks {
	Amethyst::InlineHook<decltype(&VanillaGameModuleServer::initializeBehaviorStack)> _VanillaGameModuleServer_initializeBehaviorStack;
	void VanillaGameModuleServer_initializeBehaviorStack(
		VanillaGameModuleServer* self,
		const Experiments& experiments,
		const ::gsl::not_null<::Bedrock::NonOwnerPointer<IResourcePackRepository>>& repo,
		ResourcePackStack& stack,
		const BaseGameVersion& baseGameVersion,
		bool includeEditorPacks
	) {
		auto& context = Amethyst::GetContext();
		context.mPackManager->AddBehaviorPacksToStack(*repo, stack);
		_VanillaGameModuleServer_initializeBehaviorStack(self, experiments, repo, stack, baseGameVersion, includeEditorPacks);
	}

	void Initialize() {
		auto& hooks = Amethyst::GetHookManager();
		HOOK_DIRECT_VIRTUAL(VanillaGameModuleServer, initializeBehaviorStack);
	}
}
#endif

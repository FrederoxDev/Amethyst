#include "loader/RuntimeContext.hpp"
#include "game/client/CustomUIRendererRegistry.hpp"

RuntimeContext::RuntimeContext(std::unique_ptr<Amethyst::Platform> platform, std::thread::id amethystThread)
    : AmethystContext(std::move(platform), amethystThread) {}

void RuntimeContext::Start()
{
    mHookManager = std::make_unique<Amethyst::HookManager>();
    mEventBus = std::make_unique<Amethyst::EventBus>();
#ifdef CLIENT
    // mInputManager = std::make_unique<Amethyst::InputManager>(this);
	if (mClientCtx) {
		// mClientCtx->mCustomUIRendererRegistry = std::make_unique<CustomUIRendererRegistry>();
	}
#endif
    mPatchManager = std::make_unique<Amethyst::PatchManager>();
    mEnumAllocator = std::make_unique<Amethyst::EnumAllocator>();
    mPackManager = std::make_unique<Amethyst::PackManager>(this);
    // mNetworkManager = std::make_unique<Amethyst::NetworkManager>();
    mModRepository = std::make_unique<Amethyst::ModRepository>();
    mModGraph = std::make_unique<Amethyst::ModGraph>();
    mModLoader = std::make_unique<Amethyst::ModLoader>(this);
}

void RuntimeContext::Shutdown()
{
#ifdef CLIENT
	if (mClientCtx) {
		// mClientCtx->mCustomUIRendererRegistry.reset();
	}
#endif

    mHookManager.reset();
    mEventBus.reset();
    // mInputManager.reset();
    mPatchManager.reset();
    mEnumAllocator.reset();
    mPackManager.reset();
    // mNetworkManager.reset();
    mModRepository.reset();
    mModGraph.reset();
    mModLoader.reset();
}
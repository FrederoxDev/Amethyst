#include "AmethystContext.hpp"
#include "amethyst/runtime/importing/data/CanonicalSymbol.hpp"
#include "amethyst/runtime/importing/data/CanonicalHeader.hpp"

AmethystContext::AmethystContext(std::unique_ptr<Amethyst::Platform> platform, std::thread::id amethystThread) :
    mAmethystAbiHash(AmethystContext::GetAmethystAbiHash()),
    mPlatform(std::move(platform)),
    mAmethystThread(amethystThread),
    mClientCtx(nullptr),
    mServerCtx(nullptr)
	{
		#ifdef CLIENT
		mClientCtx = std::make_unique<Amethyst::ClientContext>();
		#endif
	}

uint64_t AmethystContext::GetAmethystAbiHash()
{
    std::string abiDescription;

    abiDescription += "sizeof(AmethystContext):" + std::to_string(sizeof(AmethystContext));
    abiDescription += "offsetof(mPlatform):" + std::to_string(offsetof(AmethystContext, mPlatform));
    abiDescription += "offsetof(mHookManager):" + std::to_string(offsetof(AmethystContext, mHookManager));
    abiDescription += "sizeof(Amethyst::SharedContext):" + std::to_string(sizeof(Amethyst::SharedContext));
    abiDescription += "sizeof(Amethyst::ClientContext):" + std::to_string(sizeof(Amethyst::ClientContext));
    abiDescription += "sizeof(Amethyst::ServerContext):" + std::to_string(sizeof(Amethyst::ServerContext));
	abiDescription += "sizeof(Amethyst::Importing::CanonicalSymbol):" + std::to_string(sizeof(Amethyst::Importing::CanonicalSymbol));
	abiDescription += "sizeof(Amethyst::Importing::CanonicalHeader):" + std::to_string(sizeof(Amethyst::Importing::CanonicalHeader));

    return HashedString::computeHash(abiDescription);
}

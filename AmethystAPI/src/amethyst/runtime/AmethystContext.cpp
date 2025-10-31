#include "AmethystContext.hpp"
#include "amethyst/runtime/importing/data/AbstractSymbol.hpp"
#include "amethyst/runtime/importing/data/AbstractHeader.hpp"

AmethystContext::AmethystContext(std::unique_ptr<Amethyst::Platform> platform, std::thread::id amethystThread) : 
    mAmethystAbiHash(AmethystContext::GetAmethystAbiHash()),
    mPlatform(std::move(platform)), 
    mAmethystThread(amethystThread), 
    mClientCtx(nullptr), 
    mServerCtx(nullptr) 
	{
		if (!mPlatform->IsDedicatedServer()) {
			mClientCtx = std::make_unique<Amethyst::ClientContext>();
		}
		
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
	abiDescription += "sizeof(Amethyst::Importing::AbstractSymbol):" + std::to_string(sizeof(Amethyst::Importing::AbstractSymbol));
	abiDescription += "sizeof(Amethyst::Importing::AbstractHeader):" + std::to_string(sizeof(Amethyst::Importing::AbstractHeader));
	abiDescription += "sizeof(Amethyst::Importing::SymbolType):" + std::to_string(sizeof(Amethyst::Importing::SymbolType));
	abiDescription += "sizeof(Amethyst::Importing::HeaderType):" + std::to_string(sizeof(Amethyst::Importing::HeaderType));

    return HashedString::computeHash(abiDescription);
}

#pragma once
#include "amethyst/runtime/ctx/SharedContext.hpp"
#include "amethyst/game/client/ICustomUIRendererRegistry.hpp"

class ClientInstance;
class MinecraftInputHandler;
class Options;

namespace Amethyst {

class ClientContext : public Amethyst::SharedContext {
public:
    ClientInstance* mClientInstance = nullptr;
    MinecraftInputHandler* mMcInputHandler = nullptr;
    Options* mOptions = nullptr;
    bool mIsInWorldOrLoading = false;

	// Amethyst Helpers
	// std::shared_ptr<ICustomUIRendererRegistry> mCustomUIRendererRegistry;
};

}
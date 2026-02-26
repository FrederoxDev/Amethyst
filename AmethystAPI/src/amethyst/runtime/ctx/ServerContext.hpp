#pragma once
#include "amethyst/runtime/ctx/SharedContext.hpp"

namespace Amethyst {

class ServerContext : public Amethyst::SharedContext {
public:
	ServerContext() = default;
};

}

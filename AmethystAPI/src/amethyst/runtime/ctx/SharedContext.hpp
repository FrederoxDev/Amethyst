#pragma once
class Minecraft;

namespace Amethyst {
class SharedContext {
public:
    // Minecraft Specifics
    Minecraft* mMinecraft = nullptr;

protected:
    SharedContext();
};
}
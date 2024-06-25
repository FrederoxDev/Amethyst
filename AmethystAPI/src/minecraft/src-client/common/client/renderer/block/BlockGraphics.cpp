#include "minecraft/src-client/common/client/renderer/block/BlockGraphics.hpp"
#include <amethyst/Memory.hpp>

void BlockGraphics::setTextureItem(std::string up, std::string down, std::string north, std::string south, std::string west, std::string east)
{
    using function = decltype(&BlockGraphics::setTextureItem);
    static auto func = std::bit_cast<function>(SigScan("48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 41 56 48 83 EC ? 4C 8B F2 48 B8"));
    (this->*func)(up, down, north, south, west, east);
}

void BlockGraphics::setDefaultCarriedTextures()
{
    // 1.21.0.3
    using function = decltype(&BlockGraphics::setDefaultCarriedTextures);
    static auto func = std::bit_cast<function>(SigScan("40 55 57 48 83 EC ? 48 8B 79"));
    (this->*func)();
}

BlockGraphics* BlockGraphics::createBlockGraphics(const HashedString& identifier, BlockShape shape)
{
    // 1.21.0.3
    using function = decltype(&BlockGraphics::createBlockGraphics);
    static auto func = std::bit_cast<function>(SigScan("48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 41 56 41 57 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 84 24 ? ? ? ? 44 8B FA"));
    return func(identifier, shape);
}
 
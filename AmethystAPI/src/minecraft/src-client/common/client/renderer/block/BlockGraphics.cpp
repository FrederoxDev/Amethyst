#include "minecraft/src-client/common/client/renderer/block/BlockGraphics.hpp"
#include <amethyst/Memory.hpp>

BlockGraphics BlockGraphics::createBlockGraphics(HashedString& identifier, BlockShape shape)
{
    using function = decltype(&BlockGraphics::createBlockGraphics);
    static auto func = std::bit_cast<function>(SigScan("48 89 5C 24 ? 48 89 6C 24 ? 56 57 41 56 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 84 24 ? ? ? ? 44 8B F2"));
    return func(identifier, shape);
}

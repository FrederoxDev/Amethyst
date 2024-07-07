#include <minecraft/src-client/common/client/world/item/ItemIconManager.hpp>
#include <amethyst/Memory.hpp>

TextureAtlasItem* ItemIconManager::getIcon(const ResolvedItemIconInfo& iconInfo)
{
    using function = decltype(&ItemIconManager::getIcon);
    static auto func = std::bit_cast<function>(SigScan("48 89 5C 24 ? 57 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 84 24 ? ? ? ? 48 8B D9 44 8B 49"));
    return func(iconInfo);
}
#pragma once
#include <minecraft/src/common/world/item/ResolvedItemIconInfo.hpp>
#include <minecraft/src-client/common/client/renderer/TexturePtr.hpp>
#include <minecraft/src-client/common/client/renderer/texture/TextureAtlasItem.hpp>

class ItemIconManager {
public:
    static TextureAtlasItem* getIcon(const ResolvedItemIconInfo& iconInfo /*, bool compiledOut*/);
};
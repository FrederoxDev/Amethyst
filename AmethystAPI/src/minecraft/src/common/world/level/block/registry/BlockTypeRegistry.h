#pragma once

#include <map>
#include <set>
#include "minecraft/src-deps/core/string/StringHash.h"
#include "minecraft/src/common/world/level/block/BlockLegacy.h"
#include "minecraft/src/common/SharedPtr.h"
#include "entt/container/dense_map.hpp"

typedef std::map<HashedString, SharedPtr<BlockLegacy>> BlockLookupMap;
typedef entt::dense_map<unsigned long, HashedString> BlockNameHashToHashedStringMap;

class BlockTypeRegistry {
public:
    // Found in BlockTypeRegistry::registerBlock
    // 1.20.51.1 - 0x573E700
    static std::set<std::string>* mKnownNamespaces() {
        static auto* knownNamespaces = reinterpret_cast<std::set<std::string>*>(SlideAddress(0x573E700));
        return knownNamespaces;
    }

    // Found in BlockTypeRegistry::forEachBlock
    // 1.20.51.1 - 0x573E6F0
    static BlockLookupMap* mBlockLookupMap() {
        static auto* lookupMap = reinterpret_cast<BlockLookupMap*>(SlideAddress(0x573E6F0));
        return lookupMap;
    }

    // Found in BlockTypeRegistry::getBlockNameFromNameHash
    // 1.20.51.1 - 0x551F010
    static BlockNameHashToHashedStringMap* mBlockNameHashToStringMap() {
        static auto* map = reinterpret_cast<BlockNameHashToHashedStringMap*>(SlideAddress(0x551F010));
        return map;
    }
};

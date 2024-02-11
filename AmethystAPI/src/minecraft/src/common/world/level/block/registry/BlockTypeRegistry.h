#pragma once

#include <map>
#include <set>
#include "minecraft/src-deps/core/string/StringHash.h"
#include "minecraft/src/common/world/level/block/BlockLegacy.h"
#include "minecraft/src/common/SharedPtr.h"
#include "entt/container/dense_map.hpp"
#include "minecraft/src-deps/core/utility/StringUtils.h"

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

    // Re-Implemented
    template<typename T, typename... Args>
    static WeakPtr<T> registerBlock(const std::string& blockName, Args&&... args) {
        HashedString hashedBlockName(blockName);

        // Ensure the block has a name
        if (blockName.empty()) {
            throw std::exception("BlockTypeRegistry: attempting to register a block without a name!");
        }

        // BlockTypeRegistry::lockForRegistryModifications();

        SharedPtr<T> block = SharedPtr<T>::make(blockName, std::forward<Args>(args)...);

        // Convert the string to lowercase and validate its namespace
        std::string lowercaseName = Util::toLower(blockName);
        size_t separator = lowercaseName.find(':');

        if (separator == std::string::npos) {
            throw std::exception("BlockTypeRegistry: attempting to register a block without a namespace!");
        }

        if (separator == 0) {
            throw std::exception("BlockTypeRegistry: attempting to register a block with an empty namespace!");
        }

        // Add the namespace to a set of known namespaces
        std::string blockNamespace = lowercaseName.substr(0, separator);
        std::set<std::string>* namespaceSet = BlockTypeRegistry::mKnownNamespaces();
        namespaceSet->insert(blockNamespace);

        // Add the block to the lookup map
        BlockLookupMap* blockLookupMap = BlockTypeRegistry::mBlockLookupMap();
        blockLookupMap->emplace(std::make_pair(hashedBlockName, block));

        // Add the hashed name to a lookup map
        BlockNameHashToHashedStringMap* hashedNameMap = BlockTypeRegistry::mBlockNameHashToStringMap();
        hashedNameMap->insert(std::make_pair((unsigned long)hashedBlockName.getHash(), hashedBlockName));

        return block;
    }
};

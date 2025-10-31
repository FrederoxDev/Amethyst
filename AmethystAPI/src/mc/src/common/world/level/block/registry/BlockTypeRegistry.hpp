/// @symbolgeneration
#pragma once
#include <amethyst/Imports.hpp>
#include "mc/src/common/world/level/block/BlockLegacy.hpp"
#include "mc/src/common/SharedPtr.hpp"
#include "entt/container/dense_map.hpp"
#include "mc/src/common/world/level/block/Block.hpp"
#include <mc/src-deps/core/utility/StringUtils.hpp>

typedef std::map<HashedString, SharedPtr<BlockLegacy>> BlockLookupMap;
typedef entt::dense_map<HashType64, HashedString> BlockNameHashToHashedStringMap;

class BlockTypeRegistry {
public:
    struct BlockComplexAliasBlockState {
        HashedString stateName;
        int value;
    };

    struct LookupByNameImplReturnType {
    public:
        WeakPtr<BlockLegacy> blockLegacy;
        std::vector<BlockComplexAliasBlockState> states;
    };

    enum class LookupByNameImplResolve : uint32_t {
        BlockLegacyResolve = 0,
        BlockResolve = 1
    };

    /// @address {0x59DF328}
    MC static std::set<std::string> mKnownNamespaces;

    /// @address {0x59DF300}
    MC static BlockLookupMap mBlockLookupMap;

    // Found in BlockTypeRegistry::getBlockNameFromNameHash
    /// @address {0x57D14E0}
    MC static BlockNameHashToHashedStringMap mBlockNameHashToStringMap; 

	/// @signature {48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 0F B6 DA 48 8B F9 0F 57 C0, win-server}
    /// @signature {48 89 5C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 55 48 8B EC 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 48 8B D9 0F 57 C0}
    MC static const Block* getDefaultBlockState(const HashedString& name);

    // Re-Implemented
    template<typename T, typename... Args>
    static WeakPtr<T> registerBlock(const HashedString& blockName, Args&&... args) {
        // BlockTypeRegistry::_lockRegistryModifications()
        const std::string& blockNameStr = blockName.getString();

        // Ensure the block has a name
        if (blockName.empty()) {
            throw std::exception("BlockTypeRegistry: attempting to register a block without a name!");
        }

        SharedPtr<T> block = SharedPtr<T>::make(blockNameStr, std::forward<Args>(args)...);

        // Convert the string to lowercase and validate its namespace
        std::string lowercaseName = Util::toLower(blockNameStr);
        size_t separator = lowercaseName.find(':');

        if (separator == std::string::npos) {
            throw std::exception("BlockTypeRegistry: attempting to register a block without a namespace!");
        }

        if (separator == 0) {
            throw std::exception("BlockTypeRegistry: attempting to register a block with an empty namespace!");
        }

        // Add the namespace to a set of known namespaces
        std::string blockNamespace = lowercaseName.substr(0, separator);
        BlockTypeRegistry::mKnownNamespaces.insert(blockNamespace);

        // Add the block to the lookup map
        BlockTypeRegistry::mBlockLookupMap.emplace(std::make_pair(blockName, block));

        // Add the hashed name to a lookup map
        BlockTypeRegistry::mBlockNameHashToStringMap.emplace(std::make_pair(blockName.getHash(), blockName));

        return block;
    }

    /// @signature {40 55 53 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 45 8B E0 44 89 44 24}
    MC static LookupByNameImplReturnType _lookupByNameImpl(const HashedString& name, int data, LookupByNameImplResolve resolve);
};

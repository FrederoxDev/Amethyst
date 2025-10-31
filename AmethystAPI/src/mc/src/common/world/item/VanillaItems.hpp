/// @symbolgeneration
#pragma once
#include <amethyst/Imports.hpp>

class BaseGameVersion;
class Experiments;
class ItemRegistryRef;
class CreativeItemRegistry;
class ActorInfoRegistry;
class BlockDefinitionGroup;


class VanillaItems {
public:
	/// @signature {40 55 53 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? B8 ? ? ? ? E8 ? ? ? ? 48 2B E0 0F 29 B4 24 ? ? ? ? 44 0F 29 84 24, win-server}
    /// @signature {40 55 53 56 57 41 54 41 56 41 57 48 8D AC 24 ? ? ? ? B8 ? ? ? ? E8 ? ? ? ? 48 2B E0 0F 29 B4 24}
    MC static void registerItems(VanillaItems* self, const ItemRegistryRef itemRegistry, const BaseGameVersion& baseGameVersion, const Experiments& experiments);

    /// @signature {48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4D 8B E1 49 8B F8 4C 8B F9 48 89 4D}
    MC static void serverInitCreativeItemsCallback(ItemRegistryRef ref, ActorInfoRegistry* actorInfo, BlockDefinitionGroup* blockDefs, CreativeItemRegistry* creativeReg, const BaseGameVersion& version, const Experiments& experiments);

	/// @signature {48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? B8 ? ? ? ? E8 ? ? ? ? 48 2B E0 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4D 8B F8 48 8B F2, win-server}
    /// @signature {48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4D 8B E8 4C 8B F2 48 8B D9}
    MC static void _addItemsCategory(CreativeItemRegistry* creativeRef, ItemRegistryRef ref, const BaseGameVersion& version, const Experiments& experiments);
    
	/// @signature {48 89 5C 24 ? 55 56 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 48 8B FA 48 8B D9 48 89 95, win-server}
    /// @signature {48 89 5C 24 ? 48 89 74 24 ? 55 57 41 56 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 48 8B FA 48 8B F1 48 89 55 ? 0F 57 C0}
    MC static void _addCommandOnlyCategory(CreativeItemRegistry* creativeRef, ItemRegistryRef ref, const BaseGameVersion& version, const Experiments& experiments);

	/// @signature {40 55 53 56 57 41 54 41 56 41 57 48 8D AC 24 ? ? ? ? B8 ? ? ? ? E8 ? ? ? ? 48 2B E0 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4D 8B F0, win-server}
    /// @signature {48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? B8 ? ? ? ? E8 ? ? ? ? 48 2B E0 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 49 8B F0 48 8B FA 48 8B D9}
    MC static void _addEquipmentCategory(CreativeItemRegistry* creativeRef, ItemRegistryRef ref, const BaseGameVersion& version, const Experiments& experiments);

	/// @signature {40 55 53 56 57 41 54 41 56 41 57 48 8D AC 24 ? ? ? ? B8 ? ? ? ? E8 ? ? ? ? 48 2B E0 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4D 8B F8, win-server}
    /// @signature {40 55 53 56 57 41 54 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4D 8B F8 48 8B F2 48 8B D9 48 89 95}
    MC static void _addNatureCategory(CreativeItemRegistry* creativeRef, ItemRegistryRef ref, const BaseGameVersion& version, const Experiments& experiments);

	/// @signature {48 89 5C 24 ? 48 89 54 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? B8, win-server}
    /// @signature {48 89 5C 24 ? 48 89 54 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? B8}
    MC static void _addConstructionCategory(CreativeItemRegistry* creativeRef, ItemRegistryRef ref, const BaseGameVersion& version, const Experiments& experiments);
};
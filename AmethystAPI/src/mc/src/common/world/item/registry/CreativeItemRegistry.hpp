/// @symbolgeneration
#pragma once
#include <amethyst/Imports.hpp>
#include <mc/src/common/world/item/CreativeItemCategory.hpp>

class CreativeItemGroupCategory;
class CreativeGroupInfo;
class CreativeItemEntry;
class ItemInstance;
class ItemRegistryRef;
class BaseGameVersion;

class CreativeItemRegistry : public Bedrock::EnableNonOwnerReferences {
public:
    std::vector<CreativeItemEntry> mCreativeItems;
    std::vector<CreativeGroupInfo> mCreativeGroups;
    std::unordered_map<CreativeItemCategory, CreativeItemGroupCategory> mCreativeGroupCategories;
    std::byte mCreativeNetIdIndex[64]; // std::unordered_map<TypedServerNetId<CreativeItemNetIdTag,unsigned int,0>,unsigned __int64,std::hash<TypedServerNetId<CreativeItemNetIdTag,unsigned int,0> >,std::equal_to<TypedServerNetId<CreativeItemNetIdTag,unsigned int,0> >,std::allocator<std::pair<TypedServerNetId<CreativeItemNetIdTag,unsigned int,0> const ,unsigned __int64> > > mCreativeNetIdIndex;

	/// @address {0x5A04140}
	MC static std::unique_ptr<CreativeItemRegistry> mCurrentRegistry;

public:
	/// @vidx {0}
	MC virtual ~CreativeItemRegistry() override;

//begin members:
	/// @signature {4C 8B C9 89 54 24 ? 48 B9 ? ? ? ? ? ? ? ? 44 0F B6 C2 48 B8 ? ? ? ? ? ? ? ? 4C 33 C0 0F B6 44 24 ? 4C 0F AF C1 4C 33 C0 0F B6 44 24 ? 4C 0F AF C1 4C 33 C0 0F B6 44 24 ? 4C 0F AF C1 4C 33 C0 4C 0F AF C1 49 8B 49 ? 49 23 C8 4D 8B 41 ? 48 C1 E1 ? 49 03 49 ? 45 33 C9 48 8B 41 ? 49 3B C0 74 ? 48 8B 09 3B 50 ? 74 ? 48 3B C1 74 ? 48 8B 40 ? 3B 50 ? 75 ? EB ? 49 8B C1 48 85 C0 49 0F 44 C0 49 3B C0 48 8D 48 ? 49 0F 44 C9 48 8B C1 C3 CC CC CC CC CC CC 48 8D 41, win-server}
	/// @signature {4C 8B C9 89 54 24 ? 48 B9 ? ? ? ? ? ? ? ? 44 0F B6 C2 48 B8 ? ? ? ? ? ? ? ? 4C 33 C0 0F B6 44 24 ? 4C 0F AF C1 4C 33 C0 0F B6 44 24 ? 4C 0F AF C1 4C 33 C0 0F B6 44 24 ? 4C 0F AF C1 4C 33 C0 4C 0F AF C1 49 8B 49 ? 49 23 C8 4D 8B 41 ? 48 C1 E1 ? 49 03 49 ? 45 33 C9 48 8B 41 ? 49 3B C0 74 ? 48 8B 09 3B 50 ? 74 ? 48 3B C1 74 ? 48 8B 40 ? 3B 50 ? 75 ? EB ? 49 8B C1 48 85 C0 49 0F 44 C0 49 3B C0 48 8D 48 ? 49 0F 44 C9 48 8B C1 C3 CC CC CC CC CC CC 89 54 24}
	MC CreativeItemGroupCategory* getCreativeCategory(CreativeItemCategory category);

	MC UnknownReturn getCreativeGroup(unsigned int groupIndex);

	MC const std::vector<CreativeItemEntry>& getCreativeItemEntries();

	MC CreativeItemEntry* getItemEntry(unsigned int entryIndex);

	MC UnknownReturn clear();

	CreativeItemEntry* findCreativeItemEntry(const ItemInstance& itemInstance);

	MC UnknownReturn forEachCreativeItemInstance(std::function<bool(const ItemInstance&)> callback) const;

	MC UnknownReturn logRegistry(const std::string& logPrefix);

	/// @signature {48 89 5C 24 ? 57 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 ? 48 8B FA 44 89 44 24, win-server}
	/// @signature {40 53 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 ? 4C 8B D2}
	MC CreativeItemGroupCategory* newCreativeCategory(const std::string& categoryName, CreativeItemCategory category);

	MC CreativeGroupInfo* newCreativeGroup(CreativeItemCategory category, const HashedString& groupName, const ItemInstance& iconItem);

	MC UnknownReturn newItemEntry(const ItemInstance& itemInstance);

	MC void resetGroups();

	MC UnknownReturn takeCreativeList(std::vector<CreativeItemEntry>&& newEntries);

	MC CreativeItemEntry* updateItemEntry(unsigned int entryIndex, const ItemInstance& newItemInstance);

	MC void updateNetIdMap();
};

static_assert(offsetof(CreativeItemRegistry, mCreativeItems) == 24);
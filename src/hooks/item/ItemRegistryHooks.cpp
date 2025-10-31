#include "ItemRegistryHooks.hpp"
#include <amethyst/runtime/ModContext.hpp>
#include <mc/src/common/world/item/VanillaItems.hpp>
#include <mc/src/common/world/item/Item.hpp>
#include <mc/src/common/world/item/registry/CreativeItemRegistry.hpp>
#include <mc/src/common/world/level/block/registry/BlockTypeRegistry.hpp>
#include <mc/src-client/common/client/gui/screens/controllers/CraftingScreenController.hpp>
#include <algorithm>
#include <mc/src-client/common/client/gui/screens/controllers/ContainerScreenController.hpp>
#include <mc/src/common/world/containers/ContainerEnumName.hpp>
#include <mc/src/common/world/containers/managers/models/CraftingContainerManagerModel.hpp>
#include <mc/src/common/world/actor/player/Player.hpp>
#include <mc/src/common/world/item/registry/ItemRegistry.hpp>
#include <mc/src/common/world/containers/ContainerFactory.hpp>
#include <mc/src/common/world/containers/managers/controllers/CreativeContainerController.hpp>
#include <mc/src/common/world/containers/models/FilteredContainerModel.hpp>
#include <mc/src/common/world/containers/FullContainerName.hpp>
#include <mc/src-client/common/client/player/LocalPlayer.hpp>
#include <mc/src/common/world/entity/components/UnlockedRecipesClientComponent.hpp>
#include <mc/src-client/common/client/gui/controls/UIPropertyBag.hpp>
#include <mc/src/common/world/item/registry/CreativeItemGroupCategory.hpp>

SafetyHookInline _VanillaItems__addItemsCategory;
SafetyHookInline _VanillaItems__addCommandOnlyCategory;
SafetyHookInline _VanillaItems__addEquipmentCategory;
SafetyHookInline _VanillaItems__addNatureCategory;
SafetyHookInline _VanillaItems__addConstructionCategory;

CreativeItemCategory testCategoryIdx = (CreativeItemCategory)8;
ContainerEnumName testCategoryEnumName = (ContainerEnumName)70;

void RegisterCreativeItems(ItemRegistryRef ref, CreativeItemCategory category) {
    auto& sharedCtx = Amethyst::GetCurrentThreadCtx();
    auto& vanillaCategory = sharedCtx.mCreativeRegistry.GetVanillaCategory(CreativeItemCategory::Construction);
    vanillaCategory._RegisterItems(ref);
}

void VanillaItems__addItemsCategory(
    CreativeItemRegistry* creative,
    ItemRegistryRef ref,
    const BaseGameVersion& version,
    const Experiments& experiments)
{
    _VanillaItems__addItemsCategory.call<void, CreativeItemRegistry*, ItemRegistryRef, const BaseGameVersion&, const Experiments&>(
        creative, ref, version, experiments);

    RegisterCreativeItems(ref, CreativeItemCategory::Items);
}

void VanillaItems__addCommandOnlyCategory(
    CreativeItemRegistry* creative,
    ItemRegistryRef ref,
    const BaseGameVersion& version,
    const Experiments& experiments)
{
    _VanillaItems__addCommandOnlyCategory.call<void, CreativeItemRegistry*, ItemRegistryRef, const BaseGameVersion&, const Experiments&>(
        creative, ref, version, experiments);
    RegisterCreativeItems(ref, CreativeItemCategory::ItemCommandOnly);
}

void VanillaItems__addEquipmentCategory(
    CreativeItemRegistry* creative,
    ItemRegistryRef ref,
    const BaseGameVersion& version,
    const Experiments& experiments)
{
    _VanillaItems__addEquipmentCategory.call<void, CreativeItemRegistry*, ItemRegistryRef, const BaseGameVersion&, const Experiments&>(
        creative, ref, version, experiments);
    RegisterCreativeItems(ref, CreativeItemCategory::Equipment);
}

void VanillaItems__addNatureCategory(
    CreativeItemRegistry* creative,
    ItemRegistryRef ref,
    const BaseGameVersion& version,
    const Experiments& experiments)
{
    _VanillaItems__addNatureCategory.call<void, CreativeItemRegistry*, ItemRegistryRef, const BaseGameVersion&, const Experiments&>(
        creative, ref, version, experiments);
    RegisterCreativeItems(ref, CreativeItemCategory::Nature);
}

void VanillaItems__addConstructionCategory(
    CreativeItemRegistry* creative,
    ItemRegistryRef ref,
    const BaseGameVersion& version,
    const Experiments& experiments)
{
    _VanillaItems__addConstructionCategory.call<void, CreativeItemRegistry*, ItemRegistryRef, const BaseGameVersion&, const Experiments&>(
        creative, ref, version, experiments);

    RegisterCreativeItems(ref, CreativeItemCategory::Construction);

    return;
    
    RegisterCustomCategories(creative, ref);
}


void RegisterCustomCategories(CreativeItemRegistry* creative, ItemRegistryRef ref) {
    Log::Info("VanillaItems::addConstructionCategory! {}", (uintptr_t)Item::mActiveCreativeItemCategory);
    Item::mActiveCreativeItemCategory = creative->newCreativeCategory("Test", testCategoryIdx);
    Item::mActiveCreativeGroupInfo = nullptr;

    const Block* testBlock = BlockTypeRegistry::getDefaultBlockState("tutorial_mod:test_block");
    const Block* testBlock2 = BlockTypeRegistry::getDefaultBlockState("tutorial_mod:test_block2");
    Item::ScopedCreativeGroup testGroup("itemGroup.name.test", testBlock, nullptr);

    Item::addCreativeItem(ref, *testBlock);
    Item::addCreativeItem(ref, *testBlock2);

}

#ifdef CLIENT
SafetyHookInline _CraftingScreenController__tabIndexToCollectionName;

std::string* CraftingScreenController__tabIndexToCollectionName(CraftingScreenController* self, std::string* res, InventoryLeftTabIndex tabIdx)
{
    _CraftingScreenController__tabIndexToCollectionName.call<std::string*, CraftingScreenController*, std::string*, InventoryLeftTabIndex>(self, res, tabIdx);

    if (tabIdx == (InventoryLeftTabIndex)testCategoryIdx) {
        *res = "recipe_test";
    }

    //Log::Info("{} offset {}", (uintptr_t)self, offsetof(CraftingScreenController, instance4848));

    /*

    for (auto& state : self->mTabStates) {
        Log::Info("Tab state: {} {}", (uint64_t)state.first, (uint64_t)state.second);
    }*/

    //Log::Info("_tabIndexToCollectionName: {} for tabIdx {}", *res, (int64_t)tabIdx);

    return res;
}

SafetyHookInline _lambda_ScreenController_registerTabNameBinding;

struct lambdaArgs {
    CraftingScreenController* self;
};

void* lambda_ScreenController_registerTabNameBinding(lambdaArgs* a1, void* a2)
{
    //Log::Info("tabsWaitingToBeAnimatedIn {}", CraftingScreenController::mTabsWaitingToBeAnimatedIn);

    //Log::Info("lambda_ScreenController_registerTabNameBinding something {}, tab states size {}", a1->self->something, a1->self->mTabStates.size());

    //for (auto& tabState : a1->self->mTabStates) {
    //    Log::Info("tabState idx {} is {}", (uint32_t)tabState.first, (uint32_t)tabState.second);
    //}

    //Log::Info("something: {}", *something); // seems to be some random thing each time for the test tab.

    // construction 2742786064

    std::string* res = _lambda_ScreenController_registerTabNameBinding.call<std::string*, void*, void*>(a1, a2);
    //Log::Info("something res '{}'", *res);

    if (res->size() == 0) {
        *res = "craftingScreen.tab.test";
        //CraftingScreenController::mTabsWaitingToBeAnimatedIn = 0xFF;
    }

    LocalPlayer* player = Amethyst::GetClientCtx().mClientInstance->getLocalPlayer();
    UnlockedRecipesClientComponent* component = player->tryGetComponent<UnlockedRecipesClientComponent>();
    component->mUnlockedCategories = 0x7FFFFFFF;
    component->mNewlyUnlockedCategories = 0x7FFFFFFF;

    //Log::Info("unlocked categories: {:b}, newly unlocked: {:b}", component->mUnlockedCategories, component->mNewlyUnlockedCategories);

    //std::string collectionName = a1->self->_tabIndexToCollectionName((InventoryLeftTabIndex)a1->self->something);
    //const ItemStack& firstStack = a1->self->mContainerManagerController->getItemStack(collectionName, 0);
    //Log::Info("Tab {} first stack {}", collectionName, firstStack.toDebugString());

    return (void*)res;
}

// This function is called sometimes on Keyboard + Mouse, but not everytime you change tab, so i dont think this is actually what handles changing the content.
// Altho it does actually call everytime on controller when you use bumpers to switch category. 
// called with recipe_(XYZ), 0
//SafetyHookInline _CraftingScreenController__focusCollectionItem;
//
//void CraftingScreenController__focusCollectionItem(
//    CraftingScreenController* self,
//    const std::string& item,
//    int unkn1)
//{
//    Log::Info("Focusing collection item: {}, unknown {}", item, unkn1);
//
//    _CraftingScreenController__focusCollectionItem.call<void, CraftingScreenController*, const std::string&, int>(
//        self, item, unkn1);
//}



SafetyHookInline _CraftingScreenController__showCategoryTab;

//Seems to get called once when the inventory opens, after that wont until screen is closed and reopened
//seems to allways call with someBool = false, someInt = 0
//Called 5 times once for each category

// seems to control if it renders the tab buttons at the top

void CraftingScreenController__showCategoryTab(
    CraftingScreenController* self,
    const CraftingScreenController::CategoryTabInfo& tabInfo,
    bool someBool,
    int someInt)
{
    auto it = std::find_if(
        CraftingScreenController::mCategoryTabs.begin(),
        CraftingScreenController::mCategoryTabs.end(),
        [&tabInfo](const auto& tab) {
            return tab.mCategory == tabInfo.mCategory;
        });

    Assert(it != CraftingScreenController::mCategoryTabs.end(), "Category tab not found for index {}", (uintptr_t)tabInfo.mCategory);

    UIPropertyBag propBag = UIPropertyBag();
    propBag.set<std::string>("name", tabInfo.mTabName);
    propBag.set<std::string>("control_id", tabInfo.mTabName);

    bool shouldAnimate = someBool || (someInt != 0);
    propBag.set<bool>("$animate", shouldAnimate);

    self->mControlCreateCallback(tabInfo.mTabFactoryName, propBag);
}

SafetyHookInline _CraftingContainerManagerModel__postInit;

ContainerScreenContext* CraftingContainerManagerModel__postInit(CraftingContainerManagerModel* self, ContainerScreenContext* res)
{
    _CraftingContainerManagerModel__postInit.call<ContainerScreenContext*, CraftingContainerManagerModel*, ContainerScreenContext*>(self, res);

    Log::Info("CraftingContainerManagerModel__postInit: {}", (uint64_t)res->mScreenContainerType);
    Level& level = *self->mPlayer.getLevel()->asLevel();

    //ItemRegistryRef itemRegRef = level.getItemRegistry();
    //std::shared_ptr<ItemRegistry> itemReg = itemRegRef._lockRegistry();

    CreativeItemRegistry* creativeItemReg = CreativeItemRegistry::mCurrentRegistry.get();
    
    CreativeItemGroupCategory* testCategory = nullptr;

    if (creativeItemReg) {
        testCategory = creativeItemReg->getCreativeCategory(testCategoryIdx);
        //testCategory = creativeItemReg->getCreativeCategory(CreativeItemCategory::Items);
    }

    Assert(testCategory != nullptr, "Failed to get testCategory!");

    ContainerEnumName testTabContainer = testCategoryEnumName;
    //ContainerEnumName testTabContainer = ContainerEnumName::RecipeItemsContainer;
    bool isCreativeMode = true;

    //Log::Info("{}", ContainerScreenController::ContainerCollectionNameMap.size());
    //for (const auto& test : ContainerScreenController::ContainerCollectionNameMap) {
    //    Log::Info("{} {}", (uint64_t)test.first, test.second);
    //}

    auto testContainerModel = self->_createContainerModel(testTabContainer, testCategory, isCreativeMode, [](const ItemInstance& item, bool someBool) {
        Log::Info("Callback called with {} and {}", item.mItem->mFullName.getString(), someBool);
        return FilterResult::Show;
    });

    Log::Info("Num items of test tab: {}", testCategory->getTotalNumberChildItems());

    //testContainerModel->m

    return res;
}

class ContainerController;

SafetyHookInline _ContainerFactory_createController;

std::shared_ptr<CreativeContainerController> testPanelController = nullptr;

//const std::string& reimplemented_getContainerName(ContainerController* controller) {
//    Assert(!controller->mContainerModel.expired(), "Container model lifetime is managed by controller creation and destruction");
//
//    auto containerModel = controller->mContainerModel.lock();
//    return containerModel->getContainerStringName();
//}

std::shared_ptr<ContainerController> ContainerFactory_createController(std::shared_ptr<ContainerModel> model)
{
    Assert(model != nullptr, "Invalid Model");

    Log::Info("createController model, id {}, string name '{}', item source: {}, items: {}, sparse container: {}",
              (uintptr_t)model->mContainerEnumName,
              model->mContainerStringName,
              model->mItemSource.size(),
              model->mItems.size(),
              model->mClientUIContainer == nullptr ? "nullptr" : "exists!");

    if (model->mContainerEnumName == testCategoryEnumName) {
        model->mContainerStringName = "recipe_test";
        testPanelController = std::make_shared<CreativeContainerController>(model);

        //Log::Info("res: {}, container name: {}", (uintptr_t)testPanelController.get(), testPanelController->getContainerName());

        return testPanelController;
    }

    std::shared_ptr<ContainerController> res = _ContainerFactory_createController.call<std::shared_ptr<ContainerController>>(model);
    
    //if (res.get() != nullptr) {
    //    Log::Info("Others {}", res->getContainerName());
    //}
    //else {
    //    Log::Info("others was nullptr!");
    //}

    /*Log::Info("ContainerFactory::createController with mContainerName as enum name {} and string name '{}', is client side: {}, returned controller ptr: {}", 
        (uintptr_t)model->mContainerEnumName, 
        model->mContainerStringName,
        model->mIsClientSide,
        (uintptr_t)res.get()
    );*/

    //Log::Info("res: {}", (uintptr_t)(res->get()));

    return res;
}

SafetyHookInline _FullContainerName_toString;

std::string FullContainerName_toString(const FullContainerName* self)
{
    Log::Info("FullContainerName_toString: {}", (uint64_t)self->mName);

    auto& map = ContainerScreenController::ContainerCollectionNameMap;
    auto it = map.find(self->mName);

    if (it != map.end()) {
        Log::Info("FullContainerName::toString() -> {}", it->second);
        return it->second;
    }

    // Handle missing entry gracefully
    Log::Warning("FullContainerName::toString(): Missing entry for key {}", (uint64_t)self->mName);

    // Fallback: call the original function to preserve vanilla behavior
    std::string fallback = "";
    Log::Info("FullContainerName::toString() (fallback) -> {}", fallback);

    return fallback;
}

SafetyHookInline _CraftingScreenController__registerBindings;

void CraftingScreenController__registerBindings(CraftingScreenController* self) {
    _CraftingScreenController__registerBindings.call<void>(self);

    self->bindBool(
        "#is_left_tab_test",
        [self]() {
            return self->something == (uint32_t)testCategoryIdx; 
        }, 
        []() { return true; }
    );
}

SafetyHookInline _StringFromCreativeItemCategory;

// used for appended hovertext only it seems
std::string StringFromCreativeItemCategory(CreativeItemCategory category) {
    if (category == testCategoryIdx) {
        return "test";
    }

    std::string result = _StringFromCreativeItemCategory.call<std::string>(category);
    //Log::Info("StringFromCreativeItemCategory with {} resulted in '{}'", (uint64_t)category, result);
    return result;
}

SafetyHookInline _CraftingScreenController__getCollectionName;

// Only seems to be called when hovering items
std::string* CraftingScreenController__getCollectionName(CraftingScreenController* self, std::string* res, UIPropertyBag* props) {
    _CraftingScreenController__getCollectionName.call<void, CraftingScreenController*, std::string*, UIPropertyBag*>(self, res, props);
    //Log::Info("CraftingScreenController__getCollectionName returned '{}'", *res);
    return res;
}

SafetyHookInline _CraftingScreenController__updateCategoryTabs;

void CraftingScreenController__updateCategoryTabs(CraftingScreenController* self)
{
    Log::Info("updateCategoryTabs!");
    _CraftingScreenController__updateCategoryTabs.call<void, CraftingScreenController*>(self);
}

SafetyHookInline _CraftingScreenController__updateCategoryTabsByRecipes;

// called every frame
uint32_t CraftingScreenController__updateCategoryTabsByRecipes(CraftingScreenController* self)
{
    //uint32_t something = self->mSomething;

    self->mSomething = 100;

    //Log::Info("_updateCategoryTabsByRecipes {}", something);

    return _CraftingScreenController__updateCategoryTabsByRecipes.call<uint32_t, CraftingScreenController*>(self);

    //if (something > 0) {
    //    self->mSomething = something - 1;
    //    return 0;
    //}

    //return 0;
}
#endif

void CreateItemRegistryHooks()
{
    Amethyst::HookManager& hooks = Amethyst::GetHookManager();
    HOOK(VanillaItems, _addItemsCategory);
    HOOK(VanillaItems, _addCommandOnlyCategory);
    HOOK(VanillaItems, _addEquipmentCategory);
    HOOK(VanillaItems, _addNatureCategory);
    HOOK(VanillaItems, _addConstructionCategory);

    return; // temp

	#ifdef CLIENT
    HOOK(CraftingScreenController, _tabIndexToCollectionName);
    HOOK(CraftingScreenController, _showCategoryTab);
    HOOK(ContainerFactory, createController);
    HOOK(CraftingScreenController, _updateCategoryTabs);
    HOOK(CraftingScreenController, _updateCategoryTabsByRecipes);

    HOOK(CraftingScreenController, _registerBindings);
    VHOOK(CraftingScreenController, _getCollectionName, this);

    VHOOK(CraftingContainerManagerModel, _postInit, this);

    hooks.CreateHookAbsolute(
        _lambda_ScreenController_registerTabNameBinding,
        SigScan("48 89 5C 24 ? 48 89 54 24 ? 57 48 83 EC ? 48 8B FA 48 8B D9 33 C0 89 44 24 ? 0F 57 C0 0F 11 02 48 89 42 ? 48 89 42 ? 48 8D 15"),
        &lambda_ScreenController_registerTabNameBinding
    );

    hooks.CreateHookAbsolute(
        _StringFromCreativeItemCategory,
        SigScan("48 89 5C 24 ? 89 54 24 ? 55 56 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 8B FA"),
        StringFromCreativeItemCategory
    );

    ContainerEnumName testTabContainer = testCategoryEnumName;

    CraftingScreenController::CategoryTabInfo testTab;
    testTab.mCategory = testCategoryIdx;
    testTab.mTabName = "test_tab";
    testTab.mTabFactoryName = "test_tab_factory";
    testTab.mCategoryBitmaskIndex = 5; // used as a bitmask, in game it does 1 << padding4 for writing into tabs to be animated in

    // Padding 4 values the game uses
    //[runtime][Amethyst - Runtime] construction_tab 1
    //[runtime][Amethyst - Runtime] equipment_tab 3
    //[runtime][Amethyst - Runtime] items_tab 4
    //[runtime][Amethyst - Runtime] nature_tab 2

    testTab.mContainerEnum = testTabContainer; 
    //testTab.padding12 = 0; // same as all other tabs

    for (auto& existingTabs : CraftingScreenController::mCategoryTabs) {
        Log::Info("{} {}", existingTabs.mTabName, existingTabs.mCategoryBitmaskIndex);
    }

    CraftingScreenController::mCategoryTabs.push_back(std::move(testTab));

    // Line that exploded the API
    //Log::Info("tab at index {}", CraftingScreenController::mCategoryTabs.at((uintptr_t)testCategoryIdx).mTabName);

    auto& elem = CraftingScreenController::mCategoryTabs.back();

    // pointer to padding4
    uint32_t* pPadding4 = &elem.mCategoryBitmaskIndex;

    size_t offset = offsetof(CraftingScreenController::CategoryTabInfo, mCategoryBitmaskIndex);
    uintptr_t addr = reinterpret_cast<uintptr_t>(pPadding4);

    Log::Info("CategoryTabInfo.padding4 offset = {}", offset);
    Log::Info("padding4 address = 0x{:X}", addr); // prints hex address

    ContainerScreenController::ContainerCollectionNameMap.emplace(
        testTabContainer,
        "recipe_test"
    );

    //for (auto& tab : CraftingScreenController::mCategoryTabs) {
    //    Log::Info("category: {}, padding4: {}, container enum {}, tab name {}, factory name {}", 
    //        (uint32_t)tab.mCategory, tab.padding4, (uint32_t)tab.mContainerEnum, tab.mTabName, tab.mTabFactoryName
    //    );
    //}

    /*for (auto& container : ContainerScreenController::ContainerCollectionNameMap) {
        Log::Info("container enum {} is '{}'", (uint64_t)container.first, container.second);
    }*/

	#endif
}

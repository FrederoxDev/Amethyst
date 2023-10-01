#include "Mod.h"

// Item::Item
typedef void(__thiscall* _Item_Item)(void*, const std::string&, short);
_Item_Item _item_Item;

static void Item_Item(void* self, const std::string& identifier, short id) {
    //Log::Info("Item::Item({}, {})\n", identifier, id);
    _item_Item(self, identifier, id);
}

// Item::setMaxStackSize
typedef void(__thiscall* _Item_setMaxStackSize)(void*, unsigned char);
_Item_setMaxStackSize _item_setMaxStackSize;

void Item_setMaxStackSize(void* self, unsigned char size) {
    //Log::Info("Item::setMaxStackSize({})\n", size);
    _item_setMaxStackSize(self, 13);
}

void ModInitializeHooks() {
    CreateHook(SlideAddress(0x3211fa0), Item_setMaxStackSize, _item_setMaxStackSize);
    CreateHook(SlideAddress(0x3210ec0), Item_Item, _item_Item);
}
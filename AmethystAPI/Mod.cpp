#include "Mod.h"

// Item::Item
typedef void(__thiscall* T_Item_Item)(void* self, const std::string& identifier, short id); 
T_Item_Item _Item_Item;

static void Item_Item(void* self, const std::string& identifier, short id) {
    _Item_Item(self, identifier, id);
}

// Item::appendFormattedHoverText
class ItemStackBase;
class Level;

typedef void(__thiscall* T_Item_appendFormattedHoverText)(void*, const ItemStackBase&, Level&, std::string&, bool);
T_Item_appendFormattedHoverText _Item_appendFormattedHoverText;

void Item_appendFormattedHoverText(void* self, const ItemStackBase& isb, Level& lvl, std::string& text, bool b) {
    _Item_appendFormattedHoverText(self, isb, lvl, text, b);
    text = "Hello, World!";
}

void ModInitializeHooks() {
    uintptr_t _Item_Item_Addr = SigScan("48 89 5C 24 10 48 89 74 24 18 48 89 7C 24 20 55 41 54 41 55 41 56 41 57 48 8D 6C 24 C9 48 81 EC 00 01 00 00 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 2F 41");
    CreateHook(_Item_Item_Addr, Item_Item, _Item_Item);

    /*uintptr_t _Item_appendFormattedHoverText_Addr = SigScan("40 55 53 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 D8 48 81 EC 28 01 00 00 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 10 49 8B F1 4C 89 44 24 30");
    CreateHook(_Item_appendFormattedHoverText_Addr, Item_appendFormattedHoverText, _Item_appendFormattedHoverText);*/
}
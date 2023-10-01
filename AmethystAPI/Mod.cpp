#include "Mod.h"

// Item::Item
typedef void(__thiscall* _Item_Item)(void*, const std::string&, short);
_Item_Item _item_Item;

static void Item_Item(void* self, const std::string& identifier, short id) {
    _item_Item(self, identifier, id);
}

class ItemStackBase;
class Level;

typedef void(__thiscall* _Item_appendFormattedHoverText)(void*, const ItemStackBase&, Level&, std::string&, bool);
_Item_appendFormattedHoverText _item_appendFormattedHoverText;

void Item_appendFormattedHoverText(void* self, const ItemStackBase& isb, Level& lvl, std::string& text, bool b) {
    _item_appendFormattedHoverText(self, isb, lvl, text, b);
    text = "Hello, World!";
}

void ModInitializeHooks() {
    CreateHook(SlideAddress(0x3210ec0), Item_Item, _item_Item);
    CreateHook(SlideAddress(0x3215CD0), Item_appendFormattedHoverText, _item_appendFormattedHoverText);
}
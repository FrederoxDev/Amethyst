#include "Mod.h"

typedef void(__thiscall* _ItemCtor)(void*, const std::string&, short);
_ItemCtor _itemCtor;

static void ItemCtor(void* self, const std::string& identifier, short id) {
    std::cout << identifier << std::endl;
    _itemCtor(self, identifier, id);
}

void ModInitializeHooks() {
    CreateHook(SlideAddress(0x3210ec0), ItemCtor, _itemCtor);
}
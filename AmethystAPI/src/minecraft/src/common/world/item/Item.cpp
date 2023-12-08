#include "minecraft/src/common/world/item/Item.h"

uint64_t Item::getDamageValue(void* a1) const {
	using function = uint64_t(__thiscall*)(const Item*, void*);
	return reinterpret_cast<function>(this->vtable[107])(this, a1);
}

uint64_t Item::getMaxDamage() const {
	using function = uint64_t(__thiscall*)(const Item*);
	return reinterpret_cast<function>(this->vtable[47])(this);
}
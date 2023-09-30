#include "Hook.h"

uintptr_t GetMinecraftBaseAddress() {
    return reinterpret_cast<uintptr_t>(GetModuleHandleA("Minecraft.Windows.exe"));
}   

uintptr_t SlideAddress(uintptr_t offset) {
	return GetMinecraftBaseAddress() + offset;
}
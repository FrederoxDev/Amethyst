#include "amethyst/Memory.h"
#include <libhat/Scanner.hpp>
#include <mutex>
#include <thread>

uintptr_t GetMinecraftBaseAddress()
{
    static uintptr_t mc = reinterpret_cast<uintptr_t>(GetModuleHandleA("Minecraft.Windows.exe"));
    return mc;
}

unsigned long GetMinecraftSize()
{
    HMODULE base = GetModuleHandleA("Minecraft.Windows.exe");
    if (base == nullptr) return 0;

    MODULEINFO moduleInfo;
    if (!GetModuleInformation(GetCurrentProcess(), base, &moduleInfo, sizeof(MODULEINFO))) return 0;

    return moduleInfo.SizeOfImage;
}

uintptr_t SlideAddress(uintptr_t offset)
{
    return GetMinecraftBaseAddress() + offset;
}

uintptr_t SigScan(std::string_view signature)
{
    const auto parsed = hat::parse_signature(signature);
    if (!parsed.has_value()) {
        Log::Error("Invalid signature! {:s}", signature);
        throw std::exception();
    }

    const auto begin = reinterpret_cast<std::byte*>(GetMinecraftBaseAddress());
    const auto end = begin + GetMinecraftSize();
    const auto result = hat::find_pattern(begin, end, parsed.value());

    if (!result.has_result()) {
        Log::Error("Sigscan failed! {:s}", signature);
        throw std::exception();
    }

    return reinterpret_cast<uintptr_t>(result.get());
}

size_t FindOffsetOfPointer(void* _base, void* _pointer, size_t maxSearchSize)
{
    uintptr_t base = reinterpret_cast<uintptr_t>(_base);
    uintptr_t pointer = reinterpret_cast<uintptr_t>(_pointer);

    for (size_t offset = 0; offset < maxSearchSize; offset++) {
        uintptr_t ptrAtOffset = *reinterpret_cast<uintptr_t*>(base + offset);
        if (ptrAtOffset == pointer) return offset;
    }

    return SIZE_MAX;
}
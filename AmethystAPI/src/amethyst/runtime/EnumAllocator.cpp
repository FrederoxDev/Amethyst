#include <amethyst/runtime/EnumAllocator.hpp>

void Amethyst::EnumAllocator::Shutdown() {
    mEnumsToCurrent.clear();
}
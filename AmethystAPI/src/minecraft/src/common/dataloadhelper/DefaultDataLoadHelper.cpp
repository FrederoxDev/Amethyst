#include <minecraft/src/common/dataloadhelper/DefaultDataLoadHelper.hpp>
#include <amethyst/MinecraftVtables.hpp>

DefaultDataLoadHelper::DefaultDataLoadHelper()
{
    this->vtable = (uintptr_t**)SlideAddress(0x4D79138);
}

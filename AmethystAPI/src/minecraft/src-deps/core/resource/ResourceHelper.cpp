#include <utility>

#include "core/resource/ResourceHelper.h"
#include "core/resource/ResourceUtil.h"

#include "amethyst/Memory.h"

ResourceLocation::ResourceLocation()
{
    using function = ResourceLocation*(__thiscall*)(ResourceLocation*);
    static auto func = reinterpret_cast<function>(SigScan("48 89 5C 24 ? 57 48 83 EC ? 48 8B D9 48 89 4C 24 ? 33 FF 48 8D 15"));
    func(this);
}

ResourceLocation::ResourceLocation(std::string path)
    : mFileSystem(ResourceFileSystem::UserPackage), mPath(std::move(path)) {}
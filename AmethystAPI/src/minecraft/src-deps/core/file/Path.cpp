#include "minecraft/src-deps/core/file/Path.hpp"

Core::Path::Path(const std::string& path)
{
    mPathPart.mUtf8StdString = path;
}
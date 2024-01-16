#include "core/file/Path.h"

Core::Path::Path(const std::string& path)
{
    mPathPart.mUtf8StdString = path;
}
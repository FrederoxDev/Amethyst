#pragma once
#include <string>

namespace Core {
class PathPart {
public:
    std::string mUtf8StdString;
};

template <class ContainerType>
class PathBuffer {
public:
    ContainerType mContainer;
};

class Path {
public:
    PathPart mPathPart;
    Path(const std::string&);
};
} // namespace Core

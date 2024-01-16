#pragma once
#include <string>

namespace Core {
class PathPart {
public:
    std::string mUtf8StdString;
};

template <class ContainerType>
class PathBuffer {
private:
    ContainerType mContainer;
};

class Path {
    PathPart mPathPart;

public:
    Path(const std::string&);
};
} // namespace Core

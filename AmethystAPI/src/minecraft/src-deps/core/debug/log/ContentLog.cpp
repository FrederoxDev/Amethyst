#include "ContentLog.hpp"

template<typename... Strings>
int ContentLog::Log(bool doNotRepeat, LogLevel logLevel, LogArea logArea, Strings... strings)
{
    using function = int (ContentLog::*)(bool, LogLevel, LogArea, Strings...);
    auto func = std::bit_cast<function>(SigScan("44 89 4C 24 ? 48 83 EC"));
    return (this->*func)(doNotRepeat, logLevel, logArea, strings...);
}
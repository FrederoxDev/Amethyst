#include "amethyst/runtime/ThreadRegistry.hpp"

std::string_view Amethyst::ToString(ThreadClass threadClass)
{
    switch (threadClass) {
    case ThreadClass::AmethystRuntime:
        return "AmethystRuntime";
    case ThreadClass::MainClient:
        return "MainClient";
    case ThreadClass::MainServer:
        return "MainServer";
    case ThreadClass::EngineNamed:
        return "EngineNamed";
    case ThreadClass::Unknown:
        break;
    }

    return "Unknown";
}

void Amethyst::ThreadRegistry::Record(std::thread::id thread, ThreadClass threadClass, std::string_view name)
{
    std::unique_lock lock(mLock);
    Entry& entry = mThreads[thread];

    if (threadClass != ThreadClass::Unknown)
        entry.mClass = threadClass;

    if (!name.empty())
        entry.mName.assign(name);
}

Amethyst::ThreadRegistry::Entry Amethyst::ThreadRegistry::Get(std::thread::id thread) const
{
    std::shared_lock lock(mLock);
    auto it = mThreads.find(thread);

    if (it == mThreads.end())
        return {};

    return it->second;
}

Amethyst::ThreadClass Amethyst::ThreadRegistry::GetClass(std::thread::id thread) const
{
    std::shared_lock lock(mLock);
    auto it = mThreads.find(thread);

    if (it == mThreads.end())
        return ThreadClass::Unknown;

    return it->second.mClass;
}

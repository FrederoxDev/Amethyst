#pragma once
#include <shared_mutex>
#include <string>
#include <string_view>
#include <thread>
#include <unordered_map>

namespace Amethyst {

/**
 * The kinds of thread the runtime can tell apart.
 *
 * Each one is recorded from a site the game itself only ever reaches on that thread, so a
 * class is a statement about where the code ran, never a guess from what it was doing. A
 * thread nothing has spoken for stays Unknown rather than being folded into a neighbour.
 */
enum class ThreadClass {
    /** Nothing has identified this thread. */
    Unknown,

    /** Amethyst's own thread, the one watching for hot-reloads. */
    AmethystRuntime,

    /** Drives the client's Minecraft, via ClientInstance::update. */
    MainClient,

    /** Drives the server's Minecraft. The game names it MC_SERVER. */
    MainServer,

    /**
     * Named itself through DebugUtils::setThreadName and is none of the above: a thread from
     * the game's background worker pool, or one of its networking and social threads. The
     * pool is shared, so such a thread is not tied to any one kind of work and GetThreadName
     * is as specific as this gets.
     */
    EngineNamed,
};

::std::string_view ToString(ThreadClass threadClass);

/** Remembers what is known about each thread. Every member is safe to call from any thread. */
class ThreadRegistry {
public:
    struct Entry {
        ThreadClass mClass = ThreadClass::Unknown;
        ::std::string mName;
    };

    /**
     * A class of Unknown leaves the recorded class alone and an empty name leaves the
     * recorded name alone, so the site that knows a thread's class and the site that knows
     * its name may run in either order, or only one of them run at all.
     */
    void Record(::std::thread::id thread, ThreadClass threadClass, ::std::string_view name);

    Entry Get(::std::thread::id thread) const;
    ThreadClass GetClass(::std::thread::id thread) const;

private:
    mutable ::std::shared_mutex mLock;
    ::std::unordered_map<::std::thread::id, Entry> mThreads;
};

}

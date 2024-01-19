#pragma once
#include <functional>
#include <vector>

namespace Amethyst {
template <typename... Args>
class Event {
public:
    using TCallback = std::function<void(Args...)>;

    /*
    Add a callback to the event that will be triggered whenever it is invoked.
    */
    void AddListener(TCallback callback)
    {
        mCallbacks.push_back(callback);
    }

    /*
    Invokes all added callbacks
    */
    void Invoke(Args... args)
    {
        for (const auto& callback : mCallbacks) {
            callback(args...);
        }
    }

    /*
    Removes all callbacks to the event
    */
    void Shutdown() {
        mCallbacks.clear();
    }

private:
    std::vector<TCallback> mCallbacks;
};
} // namespace Amethyst
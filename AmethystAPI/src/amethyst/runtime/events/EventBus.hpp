#pragma once
#include <functional>
#include <typeindex>

class BaseEvent {
public:
    BaseEvent() = default;
    virtual ~BaseEvent() = default;
};

class CancelableEvent : public BaseEvent {
private:
    bool mCanceled = false;

public:
    void Cancel() {
        mCanceled = true;
    }

    bool IsCanceled() const {
        return mCanceled;
    }
};

namespace Amethyst {
class EventBus {
public:
    template <typename EventType>
    using EventHandler = std::function<void(EventType&)>;

    /*
    * @brief Adds a callback that will be invoked anytime the event is triggered
    */
    template <typename EventType>
    void AddListener(EventHandler<EventType> handler)
    {
        static_assert(std::is_base_of<BaseEvent, EventType>::value, "EventType must inherit BaseEvent");
        auto typeId = std::type_index(typeid(EventType));

        mHandlers[typeId].push_back([handler](BaseEvent& event) {
            handler(static_cast<EventType&>(event));
        });
    }

    template <typename EventType>
    void Invoke(EventType& event)
    {
        static_assert(std::is_base_of<BaseEvent, EventType>::value, "EventType must inherit BaseEvent");
        auto typeId = std::type_index(typeid(EventType));

        if (mHandlers.find(typeId) != mHandlers.end()) {
            for (const auto& handler : mHandlers[typeId]) {
                handler(event);
            }
        }
    }

private:
    std::unordered_map<std::type_index, std::vector<std::function<void(BaseEvent&)>>> mHandlers;
};
} // namespace Amethyst
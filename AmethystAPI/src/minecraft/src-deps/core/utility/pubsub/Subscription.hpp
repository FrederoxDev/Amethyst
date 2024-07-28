#pragma once
#include <memory>
#include <minecraft/src-deps/core/utility/pubsub/detail/SubscriptionBody.hpp>

namespace Bedrock::PubSub {
    class SubscriptionBase {
    protected:
        std::weak_ptr<Bedrock::PubSub::Detail::SubscriptionBodyBase> mBody;

    public:
        void disconnect();
        void disconnect_async();
        bool connected() const;
    };

    class Subscription : public Bedrock::PubSub::SubscriptionBase {
    public:
        Subscription() : SubscriptionBase(){}; 
    };
};
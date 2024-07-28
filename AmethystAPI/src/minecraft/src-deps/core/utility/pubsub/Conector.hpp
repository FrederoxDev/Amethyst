#pragma once
#include <functional>
#include <minecraft/src-deps/core/utility/pubsub/Subscription.hpp>
#include <minecraft/src-deps/core/utility/pubsub/PublisherConfig.hpp>
#include <minecraft/src-deps/core/utility/pubsub/SubscriptionContext.hpp>

namespace Bedrock::PubSub {
    template <typename Signature>
    class Connector {
    protected:
        Connector();
        virtual ~Connector();

    private:
        typedef std::function<Signature> FunctionType;
        virtual Bedrock::PubSub::Subscription _connectInternal(FunctionType&& fn, Bedrock::PubSub::ConnectPosition at, Bedrock::PubSub::ContextType&& context, std::optional<int>);
    };
}

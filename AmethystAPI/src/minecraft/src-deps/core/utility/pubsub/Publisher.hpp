#pragma once
#include <minecraft/src-deps/core/utility/pubsub/detail/DispatchingPublisherBase.hpp>
#include <minecraft/src-deps/core/utility/pubsub/detail/SubscriptionBody.hpp>
#include <minecraft/src-deps/core/utility/pubsub/Conector.hpp>

namespace Bedrock::PubSub {
    template <typename Signature, typename ThreadingModel>
    class Publisher  : 
        public Bedrock::PubSub::Detail::DispatchingPublisherBase<ThreadingModel, Bedrock::PubSub::Detail::SubscriptionBody<Signature>>,
        public Bedrock::PubSub::Connector<Signature> 
    {
    public:
        typedef Bedrock::PubSub::Connector<Signature>::FunctionType FunctionType;
        virtual ~Publisher();

    private:
        virtual Bedrock::PubSub::Subscription _connectInternal(FunctionType&&, Bedrock::PubSub::ContextType&&, std::optional<int>);
    };
}
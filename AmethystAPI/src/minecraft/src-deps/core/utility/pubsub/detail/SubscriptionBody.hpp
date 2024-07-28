#pragma once
#include <functional>
#include <minecraft/src-deps/core/container/IntrusiveList.hpp>
#include <minecraft/src-deps/core/utility/pubsub/SubscriptionContext.hpp>

namespace Bedrock::PubSub::Detail {
    class SubscriptionBodyBase;

    class PublisherDisconnector {
    public:
        virtual ~PublisherDisconnector();
        virtual void _disconnect(Bedrock::PubSub::Detail::SubscriptionBodyBase&);
    };

    class SubscriptionBodyBase : public Bedrock::Intrusive::list_base_hook<Bedrock::PubSub::Detail::SubscriptionBodyBase> {
    protected:
        std::shared_ptr<Bedrock::PubSub::Detail::SubscriptionBodyBase> mStrongSelf;
        Bedrock::PubSub::Detail::PublisherDisconnector* mDisconnector;
        Bedrock::PubSub::ContextType mContext;
        Bedrock::PubSub::GroupType mGroup;
    };

    template <typename Signature>
    class SubscriptionBody : public SubscriptionBodyBase {
    private:
        typedef std::function<Signature> FunctionType;

    protected:
        FunctionType mFunction;

    public:
        const FunctionType& getFunction() const;
        SubscriptionBody(FunctionType&& function, Bedrock::PubSub::ContextType&& context);
    };
}
#pragma once

namespace Bedrock::PubSub::Detail {
    class SubscriptionBodyBase /*: public Bedrock::Intrusive::list_base_hook<Bedrock::PubSub::Detail::SubscriptionBodyBase> */ {
    protected:
        // std::shared_ptr<Bedrock::PubSub::Detail::SubscriptionBodyBase> mStrongSelf;
        // Bedrock::PubSub::Detail::PublisherDisconnector *mDisconnector;
        // Bedrock::PubSub::ContextType mContext;
        // Bedrock::PubSub::GroupType mGroup;
    };

    class PublisherDisconnector {
    public:
        virtual ~PublisherDisconnector();
        virtual void _disconnect(Bedrock::PubSub::Detail::SubscriptionBodyBase&);
    };
}
#pragma once

namespace Bedrock::PubSub::Detail {
    class SubscriptionBodyBase;

    class PublisherDisconnector {
    public:
        virtual ~PublisherDisconnector();
        virtual void _disconnect(Bedrock::PubSub::Detail::SubscriptionBodyBase&);
    };
}
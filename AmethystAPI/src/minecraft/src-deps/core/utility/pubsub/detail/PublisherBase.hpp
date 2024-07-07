#pragma once
#include <cstdint>
#include <minecraft/src-deps/core/utility/pubsub/detail/SubscriptionBody.hpp>
#include <minecraft/src-deps/core/container/IntrusiveList.hpp>

namespace Bedrock::PubSub::Detail {
    class PublisherBase : public Bedrock::PubSub::Detail::PublisherDisconnector {
    /*private:
        typedef Bedrock::Instrusive::list<Bedrock::PubSub::Detail::SubscriptionBodyBase> ConnectionList;

    public:
        ConnectionList mSubscriptions;
        uint32_t mSubscriberCount;*/
    };
}
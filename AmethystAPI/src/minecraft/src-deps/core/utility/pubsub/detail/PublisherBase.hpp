#pragma once
#include <cstdint>
#include <optional>
#include <minecraft/src-deps/core/container/IntrusiveList.hpp>
#include <minecraft/src-deps/core/utility/pubsub/detail/SubscriptionBody.hpp>
#include <minecraft/src-deps/core/utility/pubsub/PublisherConfig.hpp>

namespace Bedrock::PubSub::Detail {
    class PublisherBase : public Bedrock::PubSub::Detail::PublisherDisconnector {
    private:
        typedef Bedrock::Intrusive::list<Bedrock::PubSub::Detail::SubscriptionBodyBase> ConnectionList;

    public:
        ConnectionList mSubscriptions;
        uint32_t mSubscriberCount;

        bool empty() const;
        size_t size() const;

    protected:
        PublisherBase();
        PublisherBase(PublisherBase&&);
        PublisherBase(const PublisherBase&);
        PublisherBase& operator=(const PublisherBase&);
        void _clear();
        void _reparent();
        void _insertConnection(const std::shared_ptr<Bedrock::PubSub::Detail::SubscriptionBodyBase>&, Bedrock::PubSub::ConnectPosition, std::optional<int>);
        void _disconnectConnection(Bedrock::PubSub::Detail::SubscriptionBodyBase&);
    };
}
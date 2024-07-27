#pragma once
#include <minecraft/src-deps/core/utility/pubsub/detail/FastDispatcherPublisherBase.hpp>

namespace Bedrock::PubSub::Detail {
    template <typename ThreadingModel>
    class ThreadingPublisherBase : public Bedrock::PubSub::Detail::FastDispatchPublisherBase<ThreadingModel> {
    public:
        void clear();

    protected:
        virtual ~ThreadingPublisherBase();
        virtual void _disconnect(Bedrock::PubSub::Detail::SubscriptionBodyBase&);

        ThreadingPublisherBase();
        void _insert(const std::shared_ptr<Bedrock::PubSub::Detail::SubscriptionBodyBase>&, Bedrock::PubSub::ConnectPosition, std::optional<int>);
    };
};
 
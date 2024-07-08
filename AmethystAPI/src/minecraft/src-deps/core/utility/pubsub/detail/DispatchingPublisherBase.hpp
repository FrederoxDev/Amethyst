#pragma once
#include <minecraft/src-deps/core/utility/pubsub/detail/ThreadingPublisherBase.hpp>

namespace Bedrock::PubSub::Detail {
    template <typename ThreadingModel, typename SubscriptionBody>
    class DispatchingPublisherBase : public Bedrock::PubSub::Detail::ThreadingPublisherBase<ThreadingModel> {
        
    };
}
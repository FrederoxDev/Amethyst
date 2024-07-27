#pragma once
#include <minecraft/src-deps/core/utility/pubsub/ThreadModel.hpp>
#include <minecraft/src-deps/core/utility/pubsub/detail/PublisherBase.hpp>

namespace Bedrock::PubSub::Detail {
    class DispatchTargets;

    // Explictly declare templates for this class.
    template <typename ThreadModel>
    class FastDispatchPublisherBase;

    template <>
    class FastDispatchPublisherBase<Bedrock::PubSub::ThreadModel::SingleThreaded> : public PublisherBase, protected Bedrock::PubSub::ThreadModel::SingleThreaded::MutexType {
    protected:
        FastDispatchPublisherBase();
        bool _dispatchLock();
        bool _loadDispatchTargets(Bedrock::PubSub::Detail::DispatchTargets&);
        void _fastDispatchAddConnection();
        void _fastDispatchRemoveConnection();
        void _fastDispatchClearConnections();
    };
}
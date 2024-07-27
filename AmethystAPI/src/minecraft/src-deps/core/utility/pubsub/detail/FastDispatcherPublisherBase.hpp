#pragma once
#include <cstdint>
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
        std::byte gap20; // there seems to be an alignment byte which pushes the size of the class to 40 bytes.

        FastDispatchPublisherBase();
        bool _dispatchLock();
        bool _loadDispatchTargets(Bedrock::PubSub::Detail::DispatchTargets&);
        void _fastDispatchAddConnection();
        void _fastDispatchRemoveConnection();
        void _fastDispatchClearConnections();
    };
}

static_assert(sizeof(Bedrock::PubSub::Detail::FastDispatchPublisherBase<Bedrock::PubSub::ThreadModel::SingleThreaded>) == 40);
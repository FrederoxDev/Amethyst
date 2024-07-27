#pragma once
#include <mutex>

namespace Bedrock::PubSub::ThreadModel {
    struct SingleThreaded {
        class NullMutex {
        public:
            void lock();
            void try_lock();
            void unlock();
        };

        typedef Bedrock::PubSub::ThreadModel::SingleThreaded::NullMutex MutexType;
    };

    struct MultiThreaded {
        typedef std::mutex MutexType;
    };
}
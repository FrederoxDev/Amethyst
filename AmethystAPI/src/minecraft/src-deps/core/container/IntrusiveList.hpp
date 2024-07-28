#pragma once

namespace Bedrock::Intrusive {
    template <typename Tag>
    class list_base_hook {
    private:
        Bedrock::Intrusive::list_base_hook<Tag>* mNext;
        Bedrock::Intrusive::list_base_hook<Tag>* mPrev;
    };

    template <typename T>
    class list {
    private:
        typedef Bedrock::Intrusive::list_base_hook<T> hook_type;

    public:
        hook_type mSentinel;
    };
};
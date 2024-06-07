#pragma once

namespace Bedrock {
    template <typename E>
    class ErrorInfo {
    public:
        E mError;
        //CallStack mCallStack;
        //std::vector<ErrorInfo> mStackErrors;
    };
}

#pragma once
#include <memory>
#include <string>

namespace Bedrock::PubSub {
    class SubscriptionContext {
    public:
        static std::unique_ptr<Bedrock::PubSub::SubscriptionContext> makeDefaultContext(std::string&& description);
        virtual ~SubscriptionContext() = default;
        virtual std::string to_string() const = 0;
    };

    class BasicContext : public SubscriptionContext {
    public:
        std::string mDescription;

    public:
        BasicContext(std::string&& description);
        virtual std::string to_string() const override;
    };

    using ContextType = std::unique_ptr<Bedrock::PubSub::SubscriptionContext>;
    using GroupType = int;
}
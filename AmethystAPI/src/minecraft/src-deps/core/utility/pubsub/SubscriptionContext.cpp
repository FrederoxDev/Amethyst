#include "SubscriptionContext.hpp"

std::unique_ptr<Bedrock::PubSub::SubscriptionContext> Bedrock::PubSub::SubscriptionContext::makeDefaultContext(std::string&& description)
{
    return std::make_unique<Bedrock::PubSub::BasicContext>(std::move(description));
}

Bedrock::PubSub::BasicContext::BasicContext(std::string&& description)
    : mDescription(std::move(description)) {}

std::string Bedrock::PubSub::BasicContext::to_string() const
{
    return mDescription;
}

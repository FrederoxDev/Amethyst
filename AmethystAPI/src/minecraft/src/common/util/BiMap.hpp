#pragma once
#include <unordered_map>

template <typename LeftKeyType, typename RightKeyType>
class BidirectionalUnorderedMap {
public:
    std::unordered_map<LeftKeyType, RightKeyType> mRight;
    std::unordered_map<RightKeyType, LeftKeyType> mLeft;

    bool contains(const LeftKeyType& left) {
        return mRight.find(left) != mRight.end();
    }

    bool contains(const RightKeyType& right) {
        return mLeft.find(right) != mLeft.end();
    }

    bool emplace(const LeftKeyType& lhs, const RightKeyType& rhs) {
        if (contains(lhs) || contains(rhs)) return false;

        mLeft.emplace(rhs, lhs);
        mRight.emplace(lhs, rhs);
        return true;
    }

    bool emplace(const RightKeyType& lhs, const LeftKeyType& rhs)
    {
        if (contains(lhs) || contains(rhs)) return false;

        mRight.emplace(rhs, lhs);
        mLeft.emplace(lhs, rhs);
        return true;
    }

    void clear() {
        mLeft.clear();
        mRight.clear();
    }
};
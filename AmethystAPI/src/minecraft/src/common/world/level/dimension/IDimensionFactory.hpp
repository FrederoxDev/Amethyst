#pragma once
#include <string>
#include <minecraft/src/common/gamerefs/OwnerPtr.hpp>

class Dimension;

class IDimensionFactory {
public:
    virtual ~IDimensionFactory();
    virtual OwnerPtr<Dimension> create(const std::string&) const;
    virtual void initializeDimension(Dimension&) const;
};
#pragma once
#include <unordered_map>
#include <functional>
#include <minecraft/src/common/gamerefs/OwnerPtr.hpp>

template <typename Type, typename... Params>
class OwnerPtrFactory {
public:
    typedef std::function<OwnerPtr<Type>(Params&&...)> TypeCreator;
    typedef std::unordered_map<std::string, TypeCreator> FactoryMap;

public:
    /* this + 0 */ FactoryMap mFactoryMap;

public:
    bool hasType(const std::string& name) const
    {
        return mFactoryMap.find(name) != mFactoryMap.end();
    }

    OwnerPtr<Type> create(const std::string&, Params&&... rest);

    void registerFactory(const std::string& name, TypeCreator creator) {
        mFactoryMap[name] = creator;
    }

    std::vector<std::string> getRegisteredTypeNames() const;
};

template <typename Type, typename... Params>
class Factory {
public:
    typedef std::function<std::unique_ptr<Type>(Params&&...)> TypeCreator;
    typedef std::unordered_map<std::string, TypeCreator> FactoryMap;

public:
    /* this + 0 */ FactoryMap mFactoryMap;

public:
    bool hasType(const std::string& name) const
    {
        return mFactoryMap.find(name) != mFactoryMap.end();
    }

    void registerFactory(const std::string& name, TypeCreator creator)
    {
        mFactoryMap[name] = creator;
    }
};
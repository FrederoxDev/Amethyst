#include <resources/Pack.hpp>
#include <resources/ResourcePack.hpp>
#include <resources/ResourcePackStack.hpp>

const PackManifest& ResourcePack::getManifest() const
{
    return *mPack->mManifest;
}

void ResourcePackStack::add(
    PackInstance packInstance,
    const gsl::not_null<Bedrock::NonOwnerPointer<const IResourcePackRepository>>& repository,
    bool isDependent)
{
    _populateDependencies(mStack, packInstance, repository, isDependent);
}

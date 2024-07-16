#include "MaterialPtr.hpp"


mce::RenderMaterialInfo::RenderMaterialInfo(const HashedString& name)
{
    mHashedName = name;
}

mce::MaterialPtr::MaterialPtr(mce::RenderMaterialGroupBase& materialGroup, const HashedString& materialName)
{
    //auto& material = materialGroup.getMaterialInfo(materialName);
    mRenderMaterialInfoPtr = std::make_shared<mce::RenderMaterialInfo>(materialName);
}
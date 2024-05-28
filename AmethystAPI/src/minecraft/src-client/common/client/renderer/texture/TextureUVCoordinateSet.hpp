#pragma once
#include <minecraft/src-deps/core/resource/ResourceHelper.hpp>
#include "IsotropicFaceData.hpp"

class TextureUVCoordinateSet
{
  float weight;
  float _u0;
  float _v0;
  float _u1;
  float _v1;
  unsigned __int16 _texSizeW;
  unsigned __int16 _texSizeH;
  ResourceLocation sourceFileLocation;
  IsotropicFaceData mIsotropicFaceData;
  __int16 textureSetTranslationIndex;
  unsigned __int16 mPBRTextureDataHandle;
};
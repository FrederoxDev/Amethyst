#pragma once
#include <cstdint>
#include <set>
#include <map>
#include <minecraft/src/common/world/phys/Vec2.hpp>
#include <minecraft/src/common/world/phys/Vec3.hpp>
#include <minecraft/src-deps/core/semVer/SemVersion.hpp>
#include <minecraft/src/common/world/actor/ModelPartLocator.hpp>

struct SkinAdjustments
{
    uint32_t mAnimOverrideBitmask;
};

struct TextureOffset {
    uintptr_t** vtable; // why tf this need a vtable.
    int x;
    int y;
};

enum QuadUVRotation : __int8 {
    ZERO = 0x0,
    CW_90_DEG = 0x1,
    CW_180_DEG = 0x2,
    CW_270_DEG = 0x3,
    _COUNT = 0x4,
};

class Cube {
public:
    struct FaceUVData {
        Vec2 mUV;
        Vec2 mUVSize;
        int mMaterialInstanceListIndex;
        bool mFaceValid;
        QuadUVRotation mUvRotation;
    };
};

class Tessellator;

// This class has barely changed since china 1.16, yipee
class Geometry {
public:
    struct NodeTextureMesh {};

    class Box {
    public:
        bool mMirror;
        Vec3 mFrom;
        Vec3 mSize;
        Vec3 mRotation;
        Vec3 mPivot;
        TextureOffset mTex;
        std::array<Cube::FaceUVData, 6> mFaceUVs;
        float mInflate;
        bool mUsesFaceUVs;

        void Tessellate(Tessellator& tess, float textureWidth, float textureHeight) const;
    };

    struct NodeVertex {
        unsigned int mPositionIndex;
        unsigned int mNormalIndex;
        unsigned int mUVIndex;
    };

    __declspec(align(8)) struct NodePolyMesh {
        std::vector<Vec3> mPositions;
        std::vector<Vec3> mNormals;
        std::vector<Vec2> mUVs;
        std::vector<std::array<Geometry::NodeVertex, 3>> mTris;
        std::vector<std::array<Geometry::NodeVertex, 4>> mQuads;
        bool mAreUVsNormalized;
    };

    struct Node {
        std::set<std::string> mMixedCaseNames;
        bool mMirror;
        bool mNeverRender;
        Vec3 mPivot;
        Vec3 mRot;
        Vec3 mScale;
        Vec3 mBindPoseRotation;
        float mInflate;
        bool mPivotSubtractsParentPivot;
        std::vector<Geometry::Box> mBoxes;
        std::string mParentName;
        std::string mBoneBindingExpression;
        std::vector<ModelPartLocator> mLocators;
        Geometry::NodePolyMesh mMesh;
        std::vector<Geometry::NodeTextureMesh> mTextureMeshes;
        bool mDebug;
        unsigned int mSkinnedMeshGroupIdentifier;
        SemVersion mSourceFileVersion;
        SemVersion mSourceMinEngineVersion;
    };

public:
    SkinAdjustments mSkinAdjustments;
    Vec2 mRenderDim;
    Vec3 mRenderDimOffset;
    Vec3 mLeashOffset;
    Vec3 mScale;
    bool mUseModelData;
    bool mModified;
    Vec2 mTextureDimensions;
    std::string mSourceFilePathWithExtension;
    std::string mSerializableName;
    std::map<std::string, Geometry::Node> mNodes;
    SemVersion mMinEngineVersion;
    bool mIsFromBaseGamePack;
    std::vector<std::string> mMaterialInstanceList;
};
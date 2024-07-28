#include <minecraft/src-client/common/client/model/Geometry.hpp>
#include <minecraft/src-client/common/client/renderer/Tessellator.hpp>

std::array<std::array<char, 4>, 6> boxFaces = {{
    {6, 4, 0, 2}, // down 0, 2, 6, 4
    {5, 7, 3, 1}, // up 1, 5, 7, 3 90deg
    {4, 5, 1, 0}, // north
    {2, 3, 7, 6}, // south
    {6, 7, 5, 4},
    {0, 1, 3, 2}, 
}};

// d, u, n, s, w, e

void Geometry::Box::Tessellate(Tessellator& tess, float textureWidth, float textureHeight) const
{
    // Calculate vertices for the box
    std::array<Vec3, 8> boxVertices = {
        Vec3(mFrom.x, mFrom.y, mFrom.z),
        Vec3(mFrom.x, mFrom.y + mSize.y, mFrom.z),
        Vec3(mFrom.x + mSize.x, mFrom.y, mFrom.z),
        Vec3(mFrom.x + mSize.x, mFrom.y + mSize.y, mFrom.z),
        Vec3(mFrom.x, mFrom.y, mFrom.z + mSize.z),
        Vec3(mFrom.x, mFrom.y + mSize.y, mFrom.z + mSize.z),
        Vec3(mFrom.x + mSize.x, mFrom.y, mFrom.z + mSize.z),
        Vec3(mFrom.x + mSize.x, mFrom.y + mSize.y, mFrom.z + mSize.z)
    };

    // Add vertices to tessellator for each face
    /*for (auto& face : boxFaces) {
        tess.vertex(boxVertices[face[0]]);
        tess.vertex(boxVertices[face[1]]);
        tess.vertex(boxVertices[face[2]]);
        tess.vertex(boxVertices[face[3]]);
    }*/

    for (int face = 0; face < 6; face++) {
        auto& faceVertexes = boxFaces[face];
        auto& faceUV = mFaceUVs[face];

        float x1 = faceUV.mUV.x / textureWidth;
        float x2 = (faceUV.mUV.x + faceUV.mUVSize.x) / textureWidth;

        float y1 = faceUV.mUV.y / textureHeight;
        float y2 = (faceUV.mUV.y + faceUV.mUVSize.y) / textureHeight;

        //Log::Info("{} {} {} {} {} {}", face, x, x1, y, y1, this->mUsesFaceUVs ? "t" : "f");

        tess.vertexUV(boxVertices[faceVertexes[0]] / Vec3(16.f, 16.f, 16.f), x2, y2);
        tess.vertexUV(boxVertices[faceVertexes[1]] / Vec3(16.f, 16.f, 16.f), x2, y1);
        tess.vertexUV(boxVertices[faceVertexes[2]] / Vec3(16.f, 16.f, 16.f), x1, y1);
        tess.vertexUV(boxVertices[faceVertexes[3]] / Vec3(16.f, 16.f, 16.f), x1, y2);
    }
}
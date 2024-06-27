#include <minecraft/src-client/common/client/model/Geometry.hpp>
#include <minecraft/src-client/common/client/renderer/Tessellator.hpp>

std::array<std::array<char, 4>, 6> boxFaces = {{
    {0, 1, 3, 2}, 
    {2, 3, 7, 6},
    {6, 7, 5, 4},
    {4, 5, 1, 0},
    {4, 0, 2, 6},
    {1, 5, 7, 3}
}};

void Geometry::Box::Tessellate(Tessellator& tess) const
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
    for (auto& face : boxFaces) {
        tess.vertex(boxVertices[face[0]]);
        tess.vertex(boxVertices[face[1]]);
        tess.vertex(boxVertices[face[2]]);
        tess.vertex(boxVertices[face[3]]);
    }
}
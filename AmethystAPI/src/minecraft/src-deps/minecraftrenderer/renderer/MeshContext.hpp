#pragma once

namespace mce {
class Camera;
class RenderContext;
};

#pragma pack(push, 1)
namespace mce {
    class MeshContext {
    public:
        /* this + 0  */ mce::RenderContext& renderContext;
        /* this + 8  */ mce::Camera* camera;
    };
}
#pragma pack(pop)
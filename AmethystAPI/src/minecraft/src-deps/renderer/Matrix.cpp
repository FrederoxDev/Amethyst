#include "minecraft/src-deps/renderer/Matrix.h"

void Matrix::translate(float x, float y, float z) {
    glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
    _m = _m * translationMatrix;
}

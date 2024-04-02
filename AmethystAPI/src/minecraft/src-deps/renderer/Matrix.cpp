#include "minecraft/src-deps/renderer/Matrix.hpp"

void Matrix::translate(float x, float y, float z) 
{
    glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
    _m = _m * translationMatrix;
}

void Matrix::scale(float scaleX, float scaleY, float scaleZ)
{
    glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(scaleX, scaleY, scaleZ));
    _m = _m * scaleMatrix;
}
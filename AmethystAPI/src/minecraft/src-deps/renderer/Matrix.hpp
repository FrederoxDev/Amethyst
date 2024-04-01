#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Matrix {
public:
	glm::mat4x4 _m;

public:
	void translate(float x, float y, float z);
    void scale(float scaleX, float scaleY, float scaleZ);
};
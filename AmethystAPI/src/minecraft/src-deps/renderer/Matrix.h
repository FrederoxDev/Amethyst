#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Matrix {
public:
	glm::tmat4x4<float> _m;

public:
	void translate(float x, float y, float z);
};
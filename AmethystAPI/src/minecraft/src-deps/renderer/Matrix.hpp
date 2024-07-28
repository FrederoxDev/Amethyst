#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Matrix {
public:
	glm::mat4x4 _m;

public:
    static Matrix IDENTITY;

    Matrix() : _m(1.0f) {};
    Matrix(const glm::mat4& other) : _m(other) {};

	void translate(float x, float y, float z);
    void scale(float scaleX, float scaleY, float scaleZ);
    void rotate(float angleDeg, float x, float y, float z);
};
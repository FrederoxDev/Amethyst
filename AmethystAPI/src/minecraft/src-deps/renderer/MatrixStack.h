#pragma once
#include <stack>
#include "minecraft/src-deps/renderer/Matrix.h"

class MatrixStack {
public:
    std::stack<Matrix> stack;
};
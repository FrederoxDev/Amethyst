#pragma once
#include <stack>
#include "minecraft/src-deps/renderer/Matrix.hpp"

class MatrixStack {
public:
    /* this + 0  */ std::stack<Matrix, std::deque<Matrix>> stack;
    /* this + 41 */ std::byte padding41[16];
    /* this + 56 */ bool _isDirty;
    /* this + 57 */ std::byte padding57[7];
};

static_assert(sizeof(MatrixStack) == 64);
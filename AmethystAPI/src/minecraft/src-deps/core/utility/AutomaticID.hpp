#pragma once

template <typename T, typename ID_TYPE>
class AutomaticID {
public:
    ID_TYPE runtimeID;
};

using DimensionType = AutomaticID<class Dimension, int>;
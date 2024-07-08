#pragma once

template <typename T, typename ID_TYPE>
class AutomaticID {
public:
    ID_TYPE runtimeID;

    AutomaticID(ID_TYPE forcedValue) 
        : runtimeID(forcedValue) {}
};


// 0 - Overworld,
// 1 - Nether,
// 2 - TheEnd,
// 3 - Undefined
using DimensionType = AutomaticID<class Dimension, int>;
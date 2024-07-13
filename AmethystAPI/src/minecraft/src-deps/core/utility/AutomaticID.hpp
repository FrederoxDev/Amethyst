#pragma once

template <typename T, typename ID_TYPE>
class AutomaticID {
public:
    ID_TYPE runtimeID;

    AutomaticID(ID_TYPE forcedValue) 
        : runtimeID(forcedValue) {}

    bool operator==(const AutomaticID& other) const {
        return runtimeID == other.runtimeID;
    }
};

template <typename T, typename ID_TYPE>
struct std::hash<AutomaticID<T, ID_TYPE>> {
    size_t operator()(const AutomaticID<T, ID_TYPE>& id) const
    {
        return std::hash<ID_TYPE>()(id.runtimeID);
    }
};

// 0 - Overworld,
// 1 - Nether,
// 2 - TheEnd,
// 3 - Undefined
using DimensionType = AutomaticID<class Dimension, int>;
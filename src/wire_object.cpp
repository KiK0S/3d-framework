#include "wire_object.h"

namespace app {
template <typename T>
std::vector<Line4d<T>> WireObject<T>::lines() const {
    std::vector<Line4d<T>> result;
    for (auto [a, b] : edges_) {
        result.emplace_back(points_[a], points_[b]);
    }
    return result;
}

template <typename T>
WireObject<T>::~WireObject() {}
}
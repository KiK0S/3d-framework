#include "surface_object.h"

namespace app {

template <typename T>
std::vector<Triangle4d<T>> SurfaceObject<T>::triangles() const {
    std::vector<Triangle4d<T>> result;
    for (Triplet triplet : triangles_) {
        result.emplace_back(WireObject<T>::points_[triplet.a], WireObject<T>::points_[triplet.b], WireObject<T>::points_[triplet.c]);
    }
    return result;
}

}

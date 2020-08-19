#include "surface_object.h"

namespace app {

SurfaceObject::SurfaceObject(std::vector<Point4d> points,
                             std::vector<std::pair<int, int>> edges,
                             std::vector<Triplet> triangles):
    WireObject(points, edges), triangles_(triangles) {}

std::vector<Triangle4d> SurfaceObject::triangles() const {
    std::vector<Triangle4d> result;
    for (Triplet triplet : triangles_) {
        result.emplace_back(WireObject::points_[triplet.a], WireObject::points_[triplet.b], WireObject::points_[triplet.c]);
    }
    return result;
}

}

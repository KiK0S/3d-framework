#include "surface_object.h"

namespace app {

SurfaceObject::SurfaceObject(std::vector<Point4d> points,
                             std::vector<std::pair<int, int>> edges):
    WireObject(std::move(points), std::move(edges)) {}

SurfaceObject::SurfaceObject(std::vector<Point4d> points,
                             std::vector<std::pair<int, int>> edges,
                             std::vector<Triplet> triangles):
    WireObject(std::move(points), std::move(edges)), triangles_(std::move(triangles)) {}

std::vector<Triangle4d> SurfaceObject::triangles() const {
    std::vector<Triangle4d> result;
    for (Triplet triplet : triangles_) {
        result.emplace_back(WireObject::points_[triplet.a], WireObject::points_[triplet.b], WireObject::points_[triplet.c]);
    }
    return result;
}

}

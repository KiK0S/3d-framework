#include "wire_object.h"

namespace app {

WireObject::WireObject(std::vector<Point4d> points, std::vector<std::pair<int, int>> edges): points_(points), edges_(edges) {}

void WireObject::apply_transform(const Matrix4d& transform) {
    for (auto& point : points_) {
        point = transform * point;
    }
}

WireObject::~WireObject() {}

std::vector<std::pair<Point4d, Point4d>> WireObject::get_edges() const {
    std::vector<std::pair<Point4d, Point4d>> result;
    for (auto& [a, b] : edges_) {
        result.emplace_back(points_[a], points_[b]);
    }
    return result;
}

}

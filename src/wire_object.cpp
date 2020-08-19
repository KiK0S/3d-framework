#include "wire_object.h"

namespace app {

WireObject::WireObject(std::vector<Point4d> points, std::vector<std::pair<int, int>> edges): points_(points), edges_(edges) {}

std::vector<Line4d> WireObject::lines() const {
    std::vector<Line4d> result;
    for (auto [a, b] : edges_) {
        result.emplace_back(points_[a], points_[b]);
    }
    return result;
}

WireObject::~WireObject() {}

}

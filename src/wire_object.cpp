#include "wire_object.h"

namespace app {

WireObject::WireObject(std::vector<Point4d> points, std::vector<std::pair<int, int>> edges): points_(points), edges_(edges) {}

void WireObject::apply_transform(const Matrix4d& transform) {
    for (auto& point : points_) {
        point = transform * point;
    }
}

WireObject::~WireObject() {}

}

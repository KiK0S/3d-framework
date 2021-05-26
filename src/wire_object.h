#pragma once

#include "point.h"
#include "matrix.h"
#include <vector>
#include <utility>

namespace app {
/*!
    \brief Класс каркаса объекта в 3д.
    \version 1.0
    \date May 14 2021
    \author KiK0S
*/
class WireObject {
public:
    WireObject(std::vector<Point4d> points, std::vector<std::pair<int, int>> edges);
    virtual ~WireObject();

    Point4d operator [](size_t index) const {
        return points_[index];
    }

    typename std::vector<Point4d>::iterator begin() {
        return points_.begin();
    }
    typename std::vector<Point4d>::iterator end() {
        return points_.end();
    }

    void apply_transform(const Matrix4d& transform);

protected:
    std::vector<Point4d> points_;
    std::vector<std::pair<int, int>> edges_;
};

}

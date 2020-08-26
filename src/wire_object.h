#pragma once

#include "line.h"
#include "point.h"
#include <vector>
#include <utility>

namespace app {

class WireObject {
public:
    WireObject(std::vector<Point4d> points, std::vector<std::pair<int, int>> edges);
    virtual ~WireObject();

    std::vector<Line4d> lines() const;
    Point4d operator [](size_t index) const {
        return points_[index];
    }

    typename std::vector<Point4d>::iterator begin() {
        return points_.begin();
    }
    typename std::vector<Point4d>::iterator end() {
        return points_.end();
    }
protected:
    std::vector<Point4d> points_;
    std::vector<std::pair<int, int>> edges_;
};

}

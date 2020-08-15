#pragma once

#include <vector>
#include <utility>
#include "line.h"
#include "point.h"

namespace app {

template <typename T = double>
class WireObject {
public:
    WireObject() {}
    virtual ~WireObject();

    std::vector<Line4d<T>> lines() const;
    Point4d<T> operator [](size_t index) const {
        return points_[index];
    }

    typename std::vector<Point4d<T>>::iterator begin() {
        return points_.begin();
    }
    typename std::vector<Point4d<T>>::iterator end() {
        return points_.end();
    }
protected:
    std::vector<Point4d<T>> points_;
    std::vector<std::pair<int, int>> edges_;
};

}

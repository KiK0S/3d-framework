#pragma once

#include <vector>
#include "point.h"
#include "wire_object.h"
#include "triangle.h"

namespace app {

template<typename T = double>
class SurfaceObject : public WireObject<T> {
public:
    SurfaceObject() {}

    std::vector<Triangle4d<T>> triangles() const;

private:
    struct Triplet {
        int a, b, c;
        Triplet() = delete;
        Triplet(int a, int b, int c): a(a), b(b), c(c) {}
    };

protected:
    std::vector<Triplet> triangles_;
};

}

#pragma once

#include "point.h"
#include "triangle.h"
#include "wire_object.h"
#include <vector>

namespace app {

class SurfaceObject : public WireObject {
private:
    struct Triplet;

public:
    SurfaceObject(std::vector<Point4d> points,
                  std::vector<std::pair<int, int>> edges,
                  std::vector<Triplet> triangles);

    std::vector<Triangle4d> triangles() const;

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

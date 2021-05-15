#pragma once

#include "point.h"
#include "triangle.h"
#include "wire_object.h"
#include <vector>

namespace app {
/*!
    \brief Класс объекта в 3д.
    \author KiK0S
    \version 1.0
    \date May 14 2021
*/
class SurfaceObject : public WireObject {
private:
    struct Triplet;

public:
    SurfaceObject(std::vector<Point4d> points,
                  std::vector<std::pair<int, int>> edges);

    SurfaceObject(std::vector<Point4d> points,
                  std::vector<std::pair<int, int>> edges,
                  std::vector<Triplet> triangles);

/*!
    \brief Массив информации о триангуляции поверхностей фигуры
 */
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

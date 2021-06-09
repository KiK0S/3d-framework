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
public:
    struct Triplet {
        int a, b, c;
        sf::Color color;
        Triplet() = delete;
        Triplet(int a, int b, int c, sf::Color color = sf::Color::Black)
                : a(a) , b(b) , c(c) , color(color) {}
        
    };

    /*!
        \brief Конструктор объекта в пространстве
     */
    SurfaceObject(std::vector<Point4d> points = {},
                  std::vector<std::pair<int, int>> edges = {},
                  std::vector<Triplet> triangles = {});

    /*!
        \brief Массив информации о триангуляции поверхностей фигуры
     */
    std::vector<Triangle4d> get_triangles() const;

private:
    std::vector<Triplet> triangles_;
};

}

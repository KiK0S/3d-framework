#pragma once

#include "matrix.h"
#include "point.h"
#include <SFML/Graphics.hpp>
#include <array>

namespace app {

class Triangle4d {
public:
    Triangle4d() = delete;
    Triangle4d(Point4d a, Point4d b, Point4d c);
    Point4d a, b, c;
    void sort_points(std::array<int, 3>, Point4d& a, Point4d& b, Point4d& c) const ;
};

class Triangle2d {
public:
    Triangle2d() = delete;
    Triangle2d(sf::Vector2f a, sf::Vector2f b, sf::Vector2f c);
    sf::Vector2f a, b, c;
    bool inner_point(double x, double y);
    sf::Vector2f get_left_point() const ;
    sf::Vector2f get_right_point() const ;
    Matrix<2, 2> create_basis() const ;
    std::array<int, 3> get_order() const ;
    double square() const ;
};

}

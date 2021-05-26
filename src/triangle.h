#pragma once

#include "matrix.h"
#include "point.h"
#include <SFML/Graphics.hpp>
#include <array>

namespace app {
/*!
    \brief Класс треугольника в 4д.
    \version 1.0
    \date May 14 2021
    \author KiK0S
*/
class Triangle4d {
public:
    Triangle4d() = delete;
    Triangle4d(Point4d a, Point4d b, Point4d c);
    Point4d a, b, c;
    void assign_points(std::array<int, 3>, Point4d& a, Point4d& b, Point4d& c) const ;
};
/*!
    \brief Класс треугольника в 2д.
    \version 1.0
    \date May 14 2021
    \author KiK0S
*/
class Triangle2d {
public:
    Triangle2d() = delete;
    Triangle2d(sf::Vector2f a, sf::Vector2f b, sf::Vector2f c);
    sf::Vector2f a, b, c;
    std::array<int, 3> order_;
    bool inner_point(const sf::Vector2f& o) const ;
    sf::Vector2f get_left_point() const ;
    sf::Vector2f get_right_point() const ;
    double min_y_in_line(double x) const ;
    double max_y_in_line(double x) const ;
    Matrix<2, 2> create_basis() const ;
    std::array<int, 3> get_order();
    double square() const ;
    bool is_degenerate() const ;
};

}

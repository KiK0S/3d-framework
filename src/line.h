#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include "point.h"


namespace app {

class Line2d {
public:
    Line2d() = delete;
    Line2d(double length);
    Line2d(double length, double angle);
    Line2d(const sf::Vector2f& start, const sf::Vector2f& finish);

    sf::Color color_ = sf::Color::Black;
    double length_;
    double angle_;
    sf::Vector2f offset_;
    const float WIDTH = 1.5f;
};

template <typename T>
class Line3d {
public:
    Line3d() = delete;
    Line3d(const Point3d<T>& start, const Point3d<T>& finish);
    Point4d<T> start_, finish_;
};

template <typename T>
class Line4d {
public:
    Line4d() = delete;
    Line4d(const Point4d<T>& start, const Point4d<T>& finish);
    Point4d<T> start_, finish_;
};

}

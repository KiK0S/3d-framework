#pragma once

#include "point.h"
#include <SFML/Graphics.hpp>


namespace app {

class Line2d {
public:
    Line2d() = delete;
    Line2d(double length);
    Line2d(double length, double angle);
    Line2d(const sf::Vector2f& start, const sf::Vector2f& finish);

    constexpr static double kWidth = 1.5f;
    double length_;
    double angle_;
    sf::Color color_ = sf::Color::Red;
    sf::Vector2f offset_;
};

class Line4d {
public:
    Line4d() = delete;
    Line4d(const Point4d& start, const Point4d& finish);
    Point4d start_, finish_;
};

}

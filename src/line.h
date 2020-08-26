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

private:
    sf::Color color_ = sf::Color::Black;
    double length_;
    double angle_;
    sf::Vector2f offset_;
    const float WIDTH = 1.5f;
};

class Line4d {
public:
    Line4d() = delete;
    Line4d(const Point4d& start, const Point4d& finish);
    Point4d start_, finish_;
};

}

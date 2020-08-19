#pragma once

#include "point.h"
#include <SFML/Graphics.hpp>

namespace app {

class Triangle4d {
public:
    Triangle4d() = delete;
    Triangle4d(Point4d a, Point4d b, Point4d c);
    Point4d a, b, c;
};

class Triangle2d {
public:
    Triangle2d() = delete;
    Triangle2d(sf::Vector2f a, sf::Vector2f b, sf::Vector2f c);
    sf::Vector2f a, b, c;
    bool inner_point(int x, int y);
};

}

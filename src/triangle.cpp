#pragma once

#include "triangle.h"
#include "point.h"
#include "log.h"

namespace app {

template <typename T>
Triangle4d<T>::Triangle4d(Point4d<T> a, Point4d<T> b, Point4d<T> c): a(a), b(b), c(c) {}

Triangle2d::Triangle2d(sf::Vector2f a, sf::Vector2f b, sf::Vector2f c): a(a), b(b), c(c) {}

bool Triangle2d::inner_point(int x, int y) {
    sf::Vector2f o(x, y);
    // debug(a);
    // debug(b);
    // debug(c);
    // debug(o);
    if (scalar(o - a, b - a) < 0) {
        return false;
    }
    if (scalar(o - a, c - a) < 0) {
        return false;
    }
    if (scalar(o - b, a - b) < 0) {
        return false;
    }
    if (scalar(o - b, c - b) < 0) {
        return false;
    }
    bool f1 = cross(o - a, b - a) > 0;
    bool s1 = cross(o - a, c - a) > 0;
    if (cross(o - a, b - a) == 0 || cross(o - a, c - a) == 0) {
        f1 = true, s1 = false;
    }
    bool f2 = cross(o - b, a - b) > 0;
    bool s2 = cross(o - b, c - b) > 0;
    if (cross(o - b, a - b) == 0 || cross(o - b, c - b) == 0) {
        f2 = true, s2 = false;
    }
    // debug(std::to_string(f1) + " " + std::to_string(s1) + " " + std::to_string(f2) + " " + std::to_string(s2));
    // exit(0);
    return (f1 ^ s1) && (f2 ^ s2);
}

}

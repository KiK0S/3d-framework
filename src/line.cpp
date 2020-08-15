#include "line.h"
#include <cmath>

namespace app {

Line2d::Line2d(double length): length_(length) {}

Line2d::Line2d(double length, double angle): length_(length), angle_(angle) {}

Line2d::Line2d(const sf::Vector2f& start, const sf::Vector2f& finish) {
    offset_ = start;
    sf::Vector2f vector = finish - start;
    sf::Vector2f norm(-vector.y, vector.x);
    length_ = std::sqrt(vector.x * vector.x + vector.y * vector.y);
    angle_ = std::atan2(vector.y, vector.x) * 180 / atan2(0, -1);
    if (angle_ < 0) {
        angle_ += 360;
    }
}

template <typename T>
Line3d<T>::Line3d(const Point3d<T>& start, const Point3d<T>& finish): start_(start), finish_(finish) {}

template <typename T>
Line4d<T>::Line4d(const Point4d<T>& start, const Point4d<T>& finish): start_(start), finish_(finish) {}

}
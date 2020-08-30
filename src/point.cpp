#include "point.h"
#include <cmath>

namespace app {

Point4d::Point4d(sf::Vector3f v) : x(v.x), y(v.y), z(v.z), w(1) {}

Point4d& Point4d::operator += (const Point4d& other) {
    *this = *this + other;
    return *this;
}
Point4d& Point4d::operator -= (const Point4d& other) {
    *this = *this - other;
    return *this;
}
Point4d& Point4d::operator *= (double k) {
    *this = *this * k;
    return *this;
}
Point4d& Point4d::operator /= (double k) {
    *this = *this / k;
    return *this;
}

Point4d Point4d::operator + (const Point4d& p) const {
    return Point4d(x + p.x, y + p.y, z + p.z);
}

Point4d Point4d::operator - (const Point4d& p) const {
    return (*this) + (p * -1);
}

Point4d Point4d::operator * (double f) const {
    return Point4d(x * f, y * f, z * f);
}
Point4d Point4d::operator / (double f) const {
    return (*this) * (1.0 / f);
}

Point4d operator * (double f, const Point4d& p) {
    return p * f;
}

double Point4d::length() const {
    return std::sqrt(x * x + y * y + z * z);
}

double cross(const sf::Vector2f& a, const sf::Vector2f& b) {
    return a.x * b.y - a.y * b.x;
}

double scalar(const sf::Vector2f& a, const sf::Vector2f& b) {
    return a.x * b.x + a.y * b.y;
}

double scalar(const Vector4d& a, const Vector4d& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

}

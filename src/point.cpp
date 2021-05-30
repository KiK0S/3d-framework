#include "point.h"
#include <cassert>
#include <cmath>

namespace app {

Point4d::Point4d() : x(0), y(0), z(0), w(1) {}
Point4d::Point4d(const sf::Vector3f& v) : x(v.x), y(v.y), z(v.z), w(1) {}

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
    return Point4d(x / w + p.x / p.w, y / w + p.y / p.w, z / w + p.z / p.w);
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

void Point4d::normalize() {
    x /= w;
    y /= w;
    z /= w;
    w = 1;
}

void Point4d::resize(double d) {
    normalize();
    d /= length();
    x *= d;
    y *= d;
    z *= d;
}

double Point4d::operator[] (size_t i) const {
    if (i == 0) return x;
    if (i == 1) return y;
    if (i == 2) return z;
    if (i == 3) return w;
    assert(0);
    return -1;
}

double& Point4d::operator[] (size_t i) {
    if (i == 0) return x;
    if (i == 1) return y;
    if (i == 2) return z;
    if (i == 3) return w;
    assert(0);
    return x;
}


bool Point4d::is_collinear(const Vector4d& b) const {
    return std::abs(x * b.z - z * b.x) < 1e-5 && std::abs(y * b.x - x * b.y) < 1e-5;
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

sf::Vector2f& operator*= (sf::Vector2f& v, double d) {
    v.x *= d;
    v.y *= d;
    return v;
}

sf::Vector2f& operator/= (sf::Vector2f& v, double d) {
    v *= (1.0 / d);
    return v;
}

double length(const sf::Vector2f& v) {
    return std::sqrt(v.x * v.x + v.y * v.y);
}

}

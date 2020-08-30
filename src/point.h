#pragma once

#include <SFML/Graphics.hpp>

namespace app {


class Point4d {
public:
    double x, y, z, w;
    Point4d() = delete;
    constexpr Point4d(double x, double y, double z): x(x), y(y), z(z), w(1) {}
    Point4d(sf::Vector3f v);

    Point4d operator + (const Point4d& p) const ;
    Point4d operator - (const Point4d& p) const ;
    Point4d operator * (double f) const ;
    Point4d operator / (double f) const ;
    Point4d& operator += (const Point4d& p);
    Point4d& operator -= (const Point4d& p);
    Point4d& operator *= (double f);
    Point4d& operator /= (double f);
    double length() const ;
};

using Vector4d = Point4d;

Point4d operator * (double f, const Point4d& p);

double cross(const sf::Vector2f& a, const sf::Vector2f& b);
double scalar(const sf::Vector2f& a, const sf::Vector2f& b);
double scalar(const Vector4d& a, const Vector4d& b);

}

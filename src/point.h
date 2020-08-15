#pragma once

#include <SFML/Graphics.hpp>

namespace app {

template <typename T = double>
class Point3d {
public:
    T x, y, z;
    Point3d() = delete;
    Point3d(T x, T y, T z);
    Point3d(sf::Vector3f v);

    Point3d operator + (const Point3d& p) const ;
    Point3d operator - (const Point3d& p) const ;
    Point3d operator * (float f) const ;
    Point3d operator / (float f) const ;
};

template <typename T = double>
class Point4d {
public:
    T x, y, z, w;
    Point4d() = delete;
    Point4d(T x, T y, T z);
    Point4d(Point3d<T> p);
    Point4d(sf::Vector3f v);

    Point4d operator + (const Point4d& p) const ;
    Point4d operator - (const Point4d& p) const ;
    Point4d operator * (float f) const ;
    Point4d operator / (float f) const ;
    double length() const ;
};

using Vector3d = Point3d<double>;
using Vector4d = Point4d<double>;

double cross(const sf::Vector2f& a, const sf::Vector2f& b);

}

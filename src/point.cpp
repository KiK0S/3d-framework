#include "point.h"
#include <cmath>

namespace app {
template <typename T>
Point3d<T>::Point3d(T x, T y, T z) : x(x), y(y), z(z) {}

template <typename T>
Point3d<T>::Point3d(sf::Vector3f v) : x(v.x), y(v.y), z(v.z) {}

template <typename T>
Point3d<T> Point3d<T>::operator + (const Point3d<T>& p) const {
    return Point3d<T>(x + p.x, y + p.y, z + p.z);
}
template <typename T>
Point3d<T> Point3d<T>::operator - (const Point3d<T>& p) const {
    return (*this) + (p * -1);
}
template <typename T>
Point3d<T> Point3d<T>::operator * (float f) const {
    return Point3d<T>(x * f, y * f, z * f);
}

template <typename T>
Point3d<T> Point3d<T>::operator / (float f) const {
    return (*this) * (1 / f);
}

template <typename T>
Point4d<T>::Point4d(T x, T y, T z) : x(x), y(y), z(z), w(1) {}
template <typename T>
Point4d<T>::Point4d(Point3d<T> p): x(p.x), y(p.y), z(p.z), w(1) {}
template <typename T>
Point4d<T>::Point4d(sf::Vector3f v) : x(v.x), y(v.y), z(v.z), w(1) {}
template <typename T>
Point4d<T> Point4d<T>::operator + (const Point4d<T>& p) const {
    return Point4d<T>(x + p.x, y + p.y, z + p.z);
}
template <typename T>
Point4d<T> Point4d<T>::operator - (const Point4d<T>& p) const {
    return (*this) + (p * -1);
}
template <typename T>
Point4d<T> Point4d<T>::operator * (float f) const {
    return Point4d<T>(x * f, y * f, z * f);
}
template <typename T>
Point4d<T> Point4d<T>::operator / (float f) const {
    return (*this) * (1 / f);
}
template <typename T>
double Point4d<T>::length() const {
    return std::sqrt(x * x + y * y + z * z);
}
}
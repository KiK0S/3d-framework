#pragma once

#include <SFML/Graphics.hpp>

template <typename T = double>
class Point3d {
  public:
	T x, y, z;
	Point3d() = delete;
	Point3d(T x, T y, T z) : x(x), y(y), z(z) {}
	Point3d(sf::Vector3f v) : x(v.x), y(v.y), z(v.z) {}
	Point3d operator + (const Point3d& p) const {
		return Point3d(x + p.x, y + p.y, z + p.z);
	}
	Point3d operator - (const Point3d& p) const {
		return (*this) + (p * -1);
	}
	Point3d operator * (float f) const {
		return Point3d(x * f, y * f, z * f);
	}
	Point3d operator / (float f) const {
		return (*this) * (1 / f);
	}
};

using Vector3d = Point3d<double>;

template <typename T = double>
class Point4d {
  public:
	T x, y, z, w;
	Point4d() = delete;
	Point4d(T x, T y, T z) : x(x), y(y), z(z), w(1) {}
	Point4d(Point3d<T> p): x(p.x), y(p.y), z(p.z), w(1) {}
	Point4d(sf::Vector3f v) : x(v.x), y(v.y), z(v.z), w(1) {}
	Point4d operator + (const Point4d& p) const {
		return Point4d(x + p.x, y + p.y, z + p.z);
	}
	Point4d operator - (const Point4d& p) const {
		return (*this) + (p * -1);
	}
	Point4d operator * (float f) const {
		return Point4d(x * f, y * f, z * f);
	}
	Point4d operator / (float f) const {
		return (*this) * (1 / f);
	}
};

using Vector4d = Point4d<double>;
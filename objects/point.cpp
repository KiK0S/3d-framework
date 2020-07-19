#pragma once

template <typename T = double>
class Point3d {
  public:
	T x, y, z;
	Point3d() = delete;
	Point3d(T x, T y, T z) : x(x), y(y), z(z) {}
	Point3d operator + (const Point3d& p) const {
		return Point3d(x + p.x, y + p.y, z + p.z);
	}
	Point3d operator * (float f) const {
		return Point3d(x * f, y * f, z * f);
	}
	Point3d operator / (float f) const {
		return (*this) * (1 / f);
	}
};
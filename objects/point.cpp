#pragma once

template <typename T = double>
class Point3d {
  public:
	T x, y, z;
	Point3d() = delete;
	Point3d(T x, T y, T z) : x(x), y(y), z(z) {}
};
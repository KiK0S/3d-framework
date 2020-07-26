#pragma once

#include "../drawing/line.cpp"
#include "point.cpp"
#include "../camera/camera.cpp"
#include <vector>
#include <utility>


template <typename T = double>
class WireObject {
  public:
    virtual WireObject();
  private:
    std::vector<Point4d<T>> points;
    std::vector<std::pair<int, int>>
};


template <typename T = double>
class Tetraedr : WireObject {
  public:
  	Tetraedr() = delete;
    Tetraedr(Point4d<T> a, Point4d<T>b, Point4d<T> c, Point4d<T> d): a(a), b(b), c(c), d(d) {}
  	std::vector<Line4d<T>> lines() {
  		std::vector<Line4d<T>> result;
  		result.emplace_back(a, b);
      result.emplace_back(c, d);
      result.emplace_back(a, c);
      result.emplace_back(a, d);
      result.emplace_back(c, b);
      result.emplace_back(b, d);
  		return result;
  	}
  	Tetraedr operator +(const Tetraedr& t) const {
  		return Tetraedr(a + t.a, b + t.b, c + t.c, d + t.d);
  	}
    Tetraedr operator *(float f) const {
      return Tetraedr(a * f, b * f, c * f, d * f);
    }
    Tetraedr operator /(float f) const {
      return (*this) * (1 / f);
    }

  private:
  	Point4d<T> a;
  	Point4d<T> b;
  	Point4d<T> c;
  	Point4d<T> d;
};

template<typename T>
const Tetraedr<T> operator * (float f, Tetraedr<T> t) {
    return t * f;
}
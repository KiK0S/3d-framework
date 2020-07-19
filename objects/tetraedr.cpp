#pragma once

#include "../drawing/line.cpp"
#include "point.cpp"
#include "../camera/camera.cpp"
#include <vector>


template <typename T = double>
class Tetraedr {
  public:
  	Tetraedr() = delete;
  	Tetraedr(Point3d<T> a, Point3d<T>b, Point3d<T> c, Point3d<T> d): a(a), b(b), c(c), d(d) {}
  	std::vector<Line> lines() {
  		std::vector<Line> result;
  		result.push_back(Camera::projectLine(a, b));
  		result.push_back(Camera::projectLine(c, b));
  		result.push_back(Camera::projectLine(a, c));
  		result.push_back(Camera::projectLine(a, d));
  		result.push_back(Camera::projectLine(c, d));
  		result.push_back(Camera::projectLine(b, d));
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
  	Point3d<T> a;
  	Point3d<T> b;
  	Point3d<T> c;
  	Point3d<T> d;
};

template<typename T>
const Tetraedr<T> operator * (float f, Tetraedr<T> t) {
    return t * f;
}
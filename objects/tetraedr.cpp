#pragma once

#include "../drawing/line.cpp"
#include "point.cpp"
#include "../camera/camera.cpp"
#include <vector>
#include <utility>


template <typename T = double>
class WireObject {
  public:
    std::vector<Line4d<T>> lines() {
        std::vector<Line4d<T>> result;
        for (auto [a, b] : edges_) {
          result.emplace_back(points_[a], points_[b]);
        }
        return result;
    }
    virtual ~WireObject() {}
  protected:
    std::vector<Point4d<T>> points_;
    std::vector<std::pair<int, int>> edges_;
};


template <typename T = double>
class Tetraedr : public WireObject<T> {
  public:
  	Tetraedr() = delete;
    Tetraedr(Point4d<T> a, Point4d<T>b, Point4d<T> c, Point4d<T> d): a(a), b(b), c(c), d(d) {
      WireObject<T>::points_ = {a, b, c, d};
      for (int i = 0; i < 4; i++) {
         for (int j = i + 1; j < 4; j++) {
          WireObject<T>::edges_.emplace_back(i, j);
         }
      }
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
    ~Tetraedr(){}

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
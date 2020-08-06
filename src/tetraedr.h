#pragma once

#include "line.h"
#include "point.h"
#include "camera.h"
#include <vector>
#include <utility>


template <typename T = double>
class WireObject {
  public:
    std::vector<Line4d<T>> lines() const;
    virtual ~WireObject();
 
  protected:
    std::vector<Point4d<T>> points_;
    std::vector<std::pair<int, int>> edges_;
};


template <typename T = double>
class Tetraedr : public WireObject<T> {
  public:
  	Tetraedr() = delete;
    Tetraedr(Point4d<T> a, Point4d<T>b, Point4d<T> c, Point4d<T> d);
  	
  	Tetraedr operator +(const Tetraedr& t) const ;
    Tetraedr operator *(float f) const ;
    Tetraedr operator /(float f) const ;
    ~Tetraedr();
  
  private:
    Point4d<T> a;
    Point4d<T> b;
    Point4d<T> c;
    Point4d<T> d;
};

template<typename T>
const Tetraedr<T> operator * (float f, Tetraedr<T> t) ;
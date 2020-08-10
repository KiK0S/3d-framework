#pragma once

#include "line.h"
#include "point.h"
#include "camera.h"
#include "wire_object.h"
#include <vector>
#include <utility>


namespace app {
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
}
#pragma once

#include "camera.h"
#include "line.h"
#include "point.h"
#include "wire_object.h"
#include <vector>
#include <utility>


namespace app {

class Tetraedr : public WireObject {
public:
    Tetraedr(Point4d a, Point4d b, Point4d c, Point4d d);
    ~Tetraedr() = default;

    Tetraedr operator +(const Tetraedr& t) const ;
    Tetraedr operator *(float f) const ;
    Tetraedr operator /(float f) const ;

private:
    Point4d a;
    Point4d b;
    Point4d c;
    Point4d d;
};

const Tetraedr operator * (float f, Tetraedr t) ;

}

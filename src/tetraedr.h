#pragma once

#include "camera.h"
#include "line.h"
#include "point.h"
#include "surface_object.h"
#include <vector>
#include <utility>


namespace app {

class Tetraedr : public SurfaceObject {
public:
    Tetraedr(Point4d a, Point4d b, Point4d c, Point4d d);
    ~Tetraedr() = default;

private:
    Point4d a;
    Point4d b;
    Point4d c;
    Point4d d;
};

}

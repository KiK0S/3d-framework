#pragma once

#include "surface_object.h"
#include "point.h"

namespace app {

class Cube : public SurfaceObject {
public:
    Cube();
    ~Cube() = default;

private:
    static constexpr double kSize_ = 100;
    static constexpr Vector4d start = Vector4d(100, 100, 100);
};

}

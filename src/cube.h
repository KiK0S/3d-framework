#pragma once

#include "surface_object.h"

namespace app {

class Cube : public SurfaceObject {
public:
    Cube();
    ~Cube() = default;

private:
    static constexpr double kSize_ = 200;
};

}

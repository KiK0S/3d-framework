#pragma once

#include "surface_object.h"

namespace app {

class Chair : public SurfaceObject {
public:
    Chair();

private:
    static constexpr double kSize_ = 100;

};

}

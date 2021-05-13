#pragma once

#include "surface_object.h"

namespace app {

class Chair : public SurfaceObject {
public:
    Chair();
    ~Chair() = default;

private:
    static constexpr double kSize_ = 100;

};

}

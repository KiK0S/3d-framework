#pragma once

#include "surface_object.h"

namespace app {

class Chair : public SurfaceObject<double> {
public:
    Chair();
    ~Chair();

private:
    const int SIZE = 100;

};

}

#pragma once

#include "surface_object.h"
#include "point.h"

namespace app {

/*!
    \brief Класс куба.
    \author KiK0S
    \version 1.0
    \date May 14 2021
*/
class Cube : public SurfaceObject {
public:
    Cube();
    ~Cube() = default;

private:
    static constexpr double kSize_ = 100;
    static constexpr Vector4d start = Vector4d(100, 100, 100);
};

}

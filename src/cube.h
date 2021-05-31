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
    /*!
        \brief Расстояние до ближайшей плоскости обзора
        \param offset сдвиг куба относительно центра координат. По умолчанию (0, 0, 0)
     */
    Cube(const Point4d& offset = kStart_, sf::Color color = sf::Color::Black);

private:
    static constexpr double kSize_ = 100;
    static constexpr Vector4d kStart_ = Vector4d(0, 0, 0);
};

}

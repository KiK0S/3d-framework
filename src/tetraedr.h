#pragma once

#include "camera.h"
#include "point.h"
#include "surface_object.h"
#include <vector>
#include <utility>


namespace app {
/*!
    \brief Класс тетраедра в 3д.
    \author KiK0S
    \version 1.0
    \date May 14 2021
*/
class Tetraedr : public SurfaceObject {
public:

    /*!
        \brief Конструктор тетраедра
     */
    Tetraedr();

    /*!
        \brief Конструктор тетраедра
     */
    Tetraedr(Point4d a, Point4d b, Point4d c, Point4d d);
    ~Tetraedr() = default;

private:
    Point4d a;
    Point4d b;
    Point4d c;
    Point4d d;
};

}

#pragma once

#include "camera.h"
#include "pixel_screen.h"
#include "renderer.h"
#include "surface_object.h"
#include "tetraedr.h"
#include <SFML/Graphics.hpp>
#include <list>

namespace app {

class Renderer;
/*!
    \brief Класс мира в 3д.
    \version 1.0
    \date May 14 2021
    \author KiK0S
*/
class World {
public:
    void add_object(std::unique_ptr<SurfaceObject>&& w);

    std::list<std::unique_ptr<SurfaceObject>>::iterator begin();
    std::list<std::unique_ptr<SurfaceObject>>::iterator end();

private:
    std::list<std::unique_ptr<SurfaceObject>> objects_;
};

}

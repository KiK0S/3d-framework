#pragma once

#include "camera.h"
#include "log.h"
#include "pixel_screen.h"
#include "renderer.h"
#include "surface_object.h"
#include "tetraedr.h"
#include <SFML/Graphics.hpp>
#include <vector>

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
    World();

    void update();
    void add_object(SurfaceObject* w);

    std::vector<std::unique_ptr<SurfaceObject>>::iterator begin();
    std::vector<std::unique_ptr<SurfaceObject>>::iterator end();

private:
    std::vector<std::unique_ptr<SurfaceObject>> objects_;
};

}

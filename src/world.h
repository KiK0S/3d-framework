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

class World {
public:
    World();

    void update();
    void add_object(SurfaceObject* w);

    std::vector<SurfaceObject*>::iterator begin();
    std::vector<SurfaceObject*>::iterator end();

private:
    std::vector<SurfaceObject*> objects_;
};

}

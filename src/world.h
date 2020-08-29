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
    World(Renderer* renderer);

    void update();
    void add_object(SurfaceObject* w);

    std::vector<SurfaceObject*>::iterator begin();
    std::vector<SurfaceObject*>::iterator end();

private:
    Renderer * const renderer_ = nullptr;
    std::vector<SurfaceObject*> objects_;
};

}

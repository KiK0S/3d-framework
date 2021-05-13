#include "world.h"
#include "log.h"
#include "screen.h"
#include "surface_object.h"
#include "triangle.h"
#include <cassert>
#include <string>
#include <vector>

namespace app {

World::World() {}

void World::update() {}

void World::add_object(SurfaceObject* t) {
    objects_.push_back(t);
}

std::vector<SurfaceObject*>::iterator World::begin() {
    return objects_.begin();
}

std::vector<SurfaceObject*>::iterator World::end() {
    return objects_.end();
}

}

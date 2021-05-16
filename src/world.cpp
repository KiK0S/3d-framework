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

void World::add_object(std::unique_ptr<SurfaceObject>&& t) {
    objects_.emplace_back(std::move(t));
}

std::vector<std::unique_ptr<SurfaceObject>>::iterator World::begin() {
    return objects_.begin();
}

std::vector<std::unique_ptr<SurfaceObject>>::iterator World::end() {
    return objects_.end();
}

}

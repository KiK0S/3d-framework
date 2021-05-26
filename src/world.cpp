#include "world.h"
#include "screen.h"
#include "surface_object.h"
#include "triangle.h"
#include <cassert>
#include <string>
#include <vector>

namespace app {

void World::add_object(std::unique_ptr<SurfaceObject>&& t) {
    objects_.emplace_back(std::move(t));
}

std::list<std::unique_ptr<SurfaceObject>>::iterator World::begin() {
    return objects_.begin();
}

std::list<std::unique_ptr<SurfaceObject>>::iterator World::end() {
    return objects_.end();
}

}

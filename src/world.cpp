#include "world.h"
#include "screen.h"
#include "surface_object.h"
#include "triangle.h"
#include <cassert>
#include <string>
#include <vector>

namespace app {

World::ObjectPtrListIt World::add_object(ObjectPtr&& t) {
    return objects_.insert(objects_.begin(), std::move(t));
}

void World::erase_object(ObjectPtrListIt it) {
    objects_.erase(it);
}

World::ObjectPtrListIt World::begin() {
    return objects_.begin();
}

World::ObjectPtrListIt World::end() {
    return objects_.end();
}

}

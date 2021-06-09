#pragma once
#include "surface_object.h"

#include <string>

namespace app {

class Loader {
public:
	static SurfaceObject load(const std::string& filename);
};

}
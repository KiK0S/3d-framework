#pragma once

#include "wire_object.h"

namespace app {

class Cube : WireObject {
public:
    Cube();
    ~Cube() = default;

private:
    static constexpr double kSize_ = 200;
};

}

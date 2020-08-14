#pragma once

#include "wire_object.h"

namespace app {

template <typename T = double>
class Cube : public WireObject<T> {
public:
    Cube();

private:
    const double SIZE = 200;
};

}

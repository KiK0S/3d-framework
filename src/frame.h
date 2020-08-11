#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "classes.h"
#include "wire_object.h"
#include "tetraedr.h"
#include "log.h"
#include "camera.h"
#include "screen.h"

namespace app {
class Frame {
public:
    Frame() = delete;
    Frame(Screen& screen);
    void update();
    void add_object(WireObject<>& w);
    Screen& screen_;
    // private:
    std::vector<std::vector<bool>> color_;
    std::vector<WireObject<>> objects_;
};
}
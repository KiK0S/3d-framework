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
        Frame(Screen& screen): screen_(screen) {}
        void update();
        void addObject(WireObject<>& w);
        Screen& screen_;
      private:
        std::vector<WireObject<>> objects_;
    };
}
#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "pixel_screen.h"
#include "screen.h"
#include "wire_object.h"
#include "surface_object.h"
#include "tetraedr.h"
#include "log.h"
#include "camera.h"

namespace app {
class Screen;
class Frame {
public:
    Frame(Screen* screen);

    void update();
    void add_object(WireObject* w);

    void set_pixel(int x, int y, double z, sf::Color color);
    void clear();

    std::vector<WireObject*>::iterator begin();
    std::vector<WireObject*>::iterator end();

private:
    Screen* screen_ = nullptr;
    PixelScreen<sf::Color> color_;
    PixelScreen<double> z_value_;
    std::vector<WireObject*> objects_;
};

}

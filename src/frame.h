#pragma once

#include "camera.h"
#include "log.h"
#include "pixel_screen.h"
#include "screen.h"
#include "surface_object.h"
#include "tetraedr.h"
#include <SFML/Graphics.hpp>
#include <vector>

namespace app {
class Screen;
class Frame {
public:
    Frame(Screen* screen);

    void update();
    void add_object(SurfaceObject* w);

    void set_pixel(int x, int y, double z, sf::Color color);
    void clear();

    std::vector<SurfaceObject*>::iterator begin();
    std::vector<SurfaceObject*>::iterator end();

private:
    Screen* screen_ = nullptr;
    PixelScreen<sf::Color> color_;
    PixelScreen<double> z_value_;
    std::vector<SurfaceObject*> objects_;
};

}

#pragma once

#include "pixel_screen.h"
#include "renderer.h"
#include <SFML/Graphics.hpp>
#include <vector>

namespace app {

class Renderer;

class Screen {
public:
    Screen(Renderer* renderer);

    void set_pixel(int x, int y, double z, sf::Color color);
    void update();
    void clear();

private:
    Renderer* renderer_ = nullptr;
    PixelScreen<sf::Color> color_;
    PixelScreen<double> z_value_;

};

}
